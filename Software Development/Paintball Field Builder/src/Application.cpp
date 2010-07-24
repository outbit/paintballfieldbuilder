/**---------------------------------------------------------
 * @author: David Whiteside
 * @date: 09/20/09
 * @description: Main Application API that interfaces with OGRE
 * Copyright 2004-2009 Whiteside Solutions LLC (www.whitesidesolutions.com)
 * ---------------------------------------------------------
 */

#include "../inc/Application.h"
#include "../inc/Common.h"


PFBApplication::PFBApplication()
{
	mRoot = 0;
	// Provide a nice cross platform solution for locating the configuration files
	// On windows files are searched for in the current working directory, on OS X however
	// you must provide the full path, the helper function macBundlePath does this for us.
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
	mResourcePath = macBundlePath() + "/Contents/Resources/";
#else
	mResourcePath = "";
#endif

	mViewMode = TOP;
	mFIELDWIDTH = 16;
	mFIELDLENGTH = 30;
	mGRIDWIDTH = 16;
	mGRIDLENGTH = 30;
	mUnitM = WORLDUNITSPERYARD;
}

PFBApplication::~PFBApplication()
{
	if (mRoot)
		delete mRoot;
}

void PFBApplication::go(void)
{
	if (!setup())
		return;

	mWindow->setActive(true);
}

void PFBApplication::Render(void)
{
	// Check If Rendering Is Enabled
	if (this->mDoRender == false) {
		return;
	}

	mRoot->renderOneFrame();
}

void PFBApplication::stop()
{
	SaveSettings();
	destroyScene();
}


void PFBApplication::AddURSpot(UNDOREDO_ACT action, SceneNode *node)
{
	UNDOREDO tmpUndoRedo;

	// Clear Redo Stack
	while (!mRedoStack.empty()) { mRedoStack.pop(); }

	// Add Info To The New Undo/Redo Spot
	tmpUndoRedo.action = action;
	Entity *e = NULL;
	e = (Entity*)node->getAttachedObject(0);
	if (e) {
		tmpUndoRedo.entityname = e->getName();
		tmpUndoRedo.object.meshname = e->getMesh()->getName();
	} else {
		PFB_LOG("add spot - no entity");
		return;
	}
	tmpUndoRedo.object.or = node->getOrientation();
	tmpUndoRedo.object.pos = node->getPosition();
	tmpUndoRedo.node = node->getName();

	// Add To STACK
	mUndoStack.push(tmpUndoRedo);
}


void PFBApplication::MakeURChange(bool undo)
{
	UNDOREDO_ACT theaction = UR_NONE;
	std::stack<UNDOREDO> *thestack = 0;

	if ( true == undo ) {
		// undo
		if ( mUndoStack.empty() ) {
			PFB_LOG("redo stack is empty");
			return;
		}

		// set stack
		thestack = &mUndoStack;
		theaction = thestack->top().action;

		// Reverse Option for create/delete
		if (thestack->top().action == UR_CREATE) { theaction = UR_DELETE; }
		if (thestack->top().action == UR_DELETE) { theaction = UR_CREATE; }
	} else {
		// redo
		if ( mRedoStack.empty() ) {
			PFB_LOG("redo stack is empty");
			return;
		}

		// set stack
		thestack = &mRedoStack;
		theaction = thestack->top().action;
	}

	// Check for empty pointer
	if (!thestack) { PFB_LOG("BAD - no stack pointer"); return; }

	switch (theaction)
	{
	case UR_CREATE:
	{
		PFB_LOG("undo/redo - Create Object");
		PFB_LOG(thestack->top().object.meshname.c_str());
		PFB_LOG(thestack->top().entityname.c_str());
		if ( 1 == this->CreateObject(NULL, NULL, thestack->top().object.meshname, &thestack->top().object.pos/*, thestack->top().entityname*/) ) {
			if ( this->mSelectedObj ) {
				thestack->top().node = this->mSelectedObj->getName();

				// Update Information
				Entity *e = NULL;
				e = (Entity*)this->mSelectedObj->getAttachedObject(0);
				if (e) {
					thestack->top().entityname = e->getName();
				} else {
					PFB_LOG("undo/redo - add spot - no entity");
					return;
				}

			// Set position
			this->mSelectedObj->setOrientation(thestack->top().object.or);
			} else {
				PFB_LOG("undo/redo - failed to select object after creation, did it fail?");
			}
		} else {
			PFB_LOG("undo/redo - failed to create object");
		}
	PFB_LOG("finished creating object");
	} break;

	case UR_DELETE:
	{
		PFB_LOG("undo - Delete Object");
		PFB_LOG(thestack->top().object.meshname.c_str());
		PFB_LOG(thestack->top().entityname.c_str());

		// Delete Object
		SceneNode *n = this->mSceneMgr->getSceneNode(thestack->top().node);
		if (!n)
		{
			PFB_LOG("undo -failed to Find Scene Node");
			return;
		}
		if (this->mSelectedObj) {
			this->mSelectedObj->showBoundingBox(false);                         // de-select first
		}
		this->mSelectedObj = n;

		PFB_LOG("undo - Deleting Bunker");
		this->DeleteSelectedObj();
		PFB_LOG("finished deleting object");
	} break;

	case UR_CHANGE:
	{
		PFB_LOG("undo/redo - Changing Object");
		PFB_LOG(thestack->top().object.meshname.c_str());
		PFB_LOG(thestack->top().entityname.c_str());

		SceneNode *n = NULL;
		n = this->mSceneMgr->getSceneNode(thestack->top().node);
		if (!n)
		{
			PFB_LOG("undo - failed to Find Scene Node");
			return;
		}
		if (this->mSelectedObj)
			this->mSelectedObj->showBoundingBox(false);                         // de-select first
		this->mSelectedObj = n;

		PFB_LOG("undo - Setting Position");
		if (undo == false)
		{
			this->mSelectedObj->setPosition(thestack->top().object.pos);
			this->mSelectedObj->setOrientation(thestack->top().object.or);
		}
		else
		{
			this->mSelectedObj->setPosition(thestack->top().old_object.pos);
			this->mSelectedObj->setOrientation(thestack->top().old_object.or);
		}
		this->mSelectedObj->showBoundingBox(true);
		PFB_LOG("finished changing object");
	} break;

	case UR_NONE:
	{
		PFB_LOG("Warning - Nothing To Undo/Redo");
		return;                         // do Nothing At All
	} break;
	}
}


void PFBApplication::LoadSettings(void)
{
	std::ifstream file("info.pfbs", std::ofstream::in | std::ofstream::binary);
	if (!file)
	{
		mRenderer = PFB_DEFAULT_RENDER;
		strcpy(mLastFieldKit, "../fieldkits/default.pfk");
		this->mBackground = ColourValue(0.0f, 0.0f, 1.0f);     // Set Default Background Color
		mViewOptions._terrain = true;
		mViewOptions._yardlines = true;
		mViewOptions._skybox = true;
		mViewOptions._fiftyyardline = true;
		mViewOptions._shadows = true;
		mViewOptions._gouraud = true;
		mViewOptions._texture = true;
		mViewOptions._solid = true;
		mViewOptions._centeryardline = true;
		PFB_LOG("Failed To Read Renderer");
	} else {
		file.read((char*)&mRenderer, sizeof(mRenderer));
		file.read((char*)mLastFieldKit, sizeof(mLastFieldKit));
		file.read((char*)&mBackground, sizeof(mBackground));
		file.read((char*)&mViewOptions, sizeof(mViewOptions));
		file.close();
	}

	if ((mRenderer != PFB_RENDER_OPENGL) || (mRenderer != PFB_RENDER_DIRECT3D9)) {
		mRenderer = PFB_RENDER_DIRECT3D9;
	}
}

void PFBApplication::SaveSettings(void)
{
	std::ofstream file("info.pfbs", std::ofstream::out | std::ofstream::binary);
	if (!file)
	{
		PFB_LOG("Failed To Write Renderer");
	}
	else
	{
		file.write((char*)&mRenderer, sizeof(mRenderer));
		file.write((char*)&mLastFieldKit, sizeof(mLastFieldKit));
		file.write((char*)&mBackground, sizeof(mBackground));
		file.write((char*)&mViewOptions, sizeof(mViewOptions));
	}
	file.close();
}

bool PFBApplication::ChangeRenderer(char Renderer)
{
	if (mRenderer == Renderer) {
		return false;
	}

	if (IDYES == MessageBox(NULL, "You Selected A Different Rendering API That Will Take Effect When You Restart PFB, Would You Like To Restart PFB?", "Paintball Field Builder", MB_YESNO))
	{
		mRenderer = Renderer;
	}
	else
	{
		return false;
	}

	return true;
}

void PFBApplication::CheckRange(void)
{
	Real x, y, z;
	x = mCamera->getPosition().x;
	y = mCamera->getPosition().y;
	z = mCamera->getPosition().z;

	if (mCamera->getPosition().x < ((TERRAIN_S/2)-500))
		mCamera->setPosition(((TERRAIN_S/2)-500), y, z);
	if (mCamera->getPosition().x > ((TERRAIN_S/2)+500))
		mCamera->setPosition(((TERRAIN_S/2)+500), y, z);

	if (mCamera->getPosition().y < 20*SCALE)
		mCamera->setPosition(x, 20*SCALE, z);
	if (mCamera->getPosition().y > 1000)
		mCamera->setPosition(x, 1000, z);

	if (mCamera->getPosition().z < ((TERRAIN_S/2)-500))
		mCamera->setPosition(x, y, ((TERRAIN_S/2)-500));
	if (mCamera->getPosition().z > (TERRAIN_S/2)+500)
		mCamera->setPosition(x, y, (TERRAIN_S/2)+500);
}

void PFBApplication::MoveView(Real x, Real z, Real y)
{
	switch(mViewMode)
	{
	case TOP:
	{
		mCamera->moveRelative(Vector3(x, 0, z));
	} break;

	case FIRSTPERSON:
	{
		mCamera->moveRelative(Vector3(x, y, z));

		Real rx, ry, rz;
		rx = mCamera->getPosition().x;
		ry = mCamera->getPosition().y;
		rz = mCamera->getPosition().z;
		if (mCamera->getPosition().y > WORLDUNITSPERYARD*3*SCALE)
			mCamera->setPosition(rx, WORLDUNITSPERYARD*3*SCALE, rz);
	} break;

	case PERSPECTIVE:
	{
		Vector3 oldpos = mCamera->getPosition();
		mCamera->moveRelative(Vector3(x, 0, z));

		Vector3 distance(mCamera->getPosition().x-(TERRAIN_S/2), 0, mCamera->getPosition().z-(TERRAIN_S/2));
		if (distance.length() < 50)
		{
			mCamera->setPosition(oldpos);
		}
	} break;
	}

	CheckRange();
	RENDER();
}

void PFBApplication::RotateView(Real x, Real z)
{
	switch(mViewMode)
	{
	case TOP:
	{
		Radian f(x* -0.001f);
		Radian v(z* -0.001f);
		Quaternion q1(Degree(0), Vector3::UNIT_X);
		Quaternion q2(f, Vector3::UNIT_Y);
		Quaternion q3(Degree(0), Vector3::UNIT_Z);
		q1 = q1 * q2 * q3;
		mCamera->rotate(q1);
	} break;

	case FIRSTPERSON:
	{
		Radian f(x* -0.005f);
		Radian v(z* -0.005f);
		Quaternion q1(Degree(0), Vector3::UNIT_X);
		Quaternion q2(f, Vector3::UNIT_Y);
		Quaternion q3(Degree(0), Vector3::UNIT_Z);
		q1 = q1 * q2 * q3;
		mCamera->rotate(q1);
	} break;

	case PERSPECTIVE:
	{
		Vector3 oldpos = mCamera->getPosition();
		Quaternion oldo = mCamera->getOrientation();
		mCamera->moveRelative(Vector3(x, z, 0));

		Vector3 distance(mCamera->getPosition().x-(TERRAIN_S/2), 0, mCamera->getPosition().z-(TERRAIN_S/2));
		if (distance.length() < 50)
		{
			mCamera->setPosition(oldpos);
			mCamera->setOrientation(oldo);
		}
		PFB_LOG("app - rotating");
	}break;
	}

	CheckRange();
	RENDER();
}

void PFBApplication::LookView(void)
{
	switch(mViewMode)
	{
	case TOP:
	{
		LookTop();
		if (!this->mLast_top.x && !this->mLast_top.y && !this->mLast_top.z)
		{
		}
		else
		{
			this->mCamera->setPosition(this->mLast_top);
			this->mCamera->setOrientation(this->mLast_topo);
		}
	} break;

	case FIRSTPERSON:
	{
		LookFirstPerson();
		if (!this->mLast_firstperson.x && !this->mLast_firstperson.y && !this->mLast_firstperson.z)
		{
		}
		else
		{
			this->mCamera->setPosition(this->mLast_firstperson);
			this->mCamera->setOrientation(this->mLast_firstpersono);
		}
	} break;

	case PERSPECTIVE:
	{
		LookPerspective();
		if (!this->mLast_perspective.x && !this->mLast_perspective.y && !this->mLast_perspective.z)
		{
		}
		else
		{
			this->mCamera->setPosition(this->mLast_perspective);
			this->mCamera->setOrientation(this->mLast_perspectiveo);
		}
	} break;
	}
	RENDER();
}

void PFBApplication::ResetView(void)
{
	switch(mViewMode)
	{
	case TOP:
	{
		LookTop();
	} break;

	case FIRSTPERSON:
	{
		LookFirstPerson();
	} break;

	case PERSPECTIVE:
	{
		LookPerspective();
	} break;
	}
	this->SaveCurrentView();
	RENDER();
}

void PFBApplication::SaveCurrentView(void)
{
	switch(mViewMode)
	{
	case TOP:
	{
		this->mLast_top = this->mCamera->getPosition();
		this->mLast_topo = this->mCamera->getOrientation();
	} break;

	case FIRSTPERSON:
	{
		this->mLast_firstperson = this->mCamera->getPosition();
		this->mLast_firstpersono = this->mCamera->getOrientation();
	} break;

	case PERSPECTIVE:
	{
		this->mLast_perspective = this->mCamera->getPosition();
		this->mLast_perspectiveo = this->mCamera->getOrientation();
	} break;
	}
}

void PFBApplication::SetBackgroundColor(ColourValue rgb)
{
	this->mBackground = rgb;
	this->mWindow->getViewport(0)->setBackgroundColour(this->mBackground);
	RENDER();
}

void PFBApplication::MoveSelectedObj(Real x, Real y)
{
	if (this->IsTerrainCreated() == false)
		return;

	if (!mSelectedObj)
	{
		this->SelectObject(x, y);

		if (!mSelectedObj)
			return;
	}

	// Setup the ray scene query
	Ray mouseRay = mCamera->getCameraToViewportRay(x, y);
	mRaySceneQuery->setRay(mouseRay);

	// Execute query
	RaySceneQueryResult &result = mRaySceneQuery->execute();
	RaySceneQueryResult::iterator itr = result.begin();

	// Get results, create a node/entity on the position
	if (itr != result.end() && itr->worldFragment)
	{
		if (itr->worldFragment->singleIntersection.y < MAX_BUNKERHEIGHT)
		{
			itr->worldFragment->singleIntersection.y = DEFAULT_BUNKERHEIGHT;
			// Dont Create Bunkers Ontop Of Bunkers
			mSelectedObj->setPosition(itr->worldFragment->singleIntersection);
		}
	}

	RENDER();
}

void PFBApplication::CloneSelectedObj(void)
{
	if (this->CloneObj(mSelectedObj) == true)
	{
		RENDER();
	}
}

void PFBApplication::RotateSelectedObj(Real x, Real y)
{
	if (this->RotateObj(mSelectedObj, x, y) == true)
	{
		RENDER();
	}
}

void PFBApplication::DeleteSelectedObj(void)
{
	if (this->DeleteObj(mSelectedObj) == true)
	{
		RENDER();
	}
}

bool PFBApplication::CloneObj(SceneNode *&node)
{
	if (this->IsTerrainCreated() == false)
	{
		return false;
	}
	if (!node)
	{
		return false;
	}

	Entity *ent = NULL;
	SceneNode *clone_node = NULL;
	char name[16] = {0};
	memset(name, NULL, sizeof(name));

	Entity *e = NULL;
	e = (Entity*)node->getAttachedObject(0);
	if (!e)
		return false;

	sprintf(name, "bunker_%d", mBunkerCount++);
	ent = mSceneMgr->createEntity(name, e->getMesh()->getName());
	if (!ent)
		return false;
	clone_node = mSceneMgr->getRootSceneNode()->createChildSceneNode("node_" + String(name), node->getPosition());
	if(!clone_node)
		return false;
	clone_node->attachObject(ent);
	clone_node->setOrientation(node->getOrientation());
	clone_node->setScale(node->getScale());

	return true;
}

bool PFBApplication::RotateObj(SceneNode *&node, Real x, Real y)
{
	if (node)
	{
		node->rotate(Vector3(0, 1, 0), Radian(x* -0.01f));
	} else {
		return false;
	}
	RENDER();

	return true;
}

bool PFBApplication::DeleteObj(SceneNode *&node)
{
	try
	{
		if (node)
		{
			node->showBoundingBox(false);
			this->mSceneMgr->destroyEntity((Entity*)node->getAttachedObject(0));
			node->detachAllObjects();
			node->removeAndDestroyAllChildren();
			this->mSceneMgr->destroySceneNode(node->getName());
			node = NULL;
		} else {
			return false;
		}
	}
	catch (Ogre::Exception ex)
	{
	}
	RENDER();
	return true;
}

void PFBApplication::TakeScreenShot(const char *file)
{
	if (this->mRenderer == PFB_RENDER_DIRECT3D9)
	{
		RenderTarget *t = NULL;
		t = (RenderTarget*)mWindow;
		PFB_Wait(1000);
		RENDER();
		t->writeContentsToFile(file);
	}
	else
	{
		PFB_ERROR("Cannot Take Screenshot In OpenGL Mode, Change To Direct3D9c Mode Under The View Options");
	}
}

void PFBApplication::ToggleTerrain(bool visible)
{
	this->mSceneMgr->getSceneNode("Terrain")->setVisible(visible, true);
	RENDER();
}

void PFBApplication::ReCreateScene(void)
{
	PFB_LOG("Save Current View");
	this->SaveCurrentView();

	PFB_LOG("Select None");
	this->SelectNone();         // Deselect ALL Object(s)

	PFB_LOG("Set Auto Tracking");
	mCamera->setAutoTracking(false);         // FIX BUG

	PFB_LOG("Save The Field");
	this->SaveField(String(TMPDIR) + String("tmp.field"));

	PFB_LOG("Remove All Children");
	mSceneMgr->getRootSceneNode()->removeAllChildren();

	PFB_LOG("Remove And Destroy All Children");
	mSceneMgr->getRootSceneNode()->removeAndDestroyAllChildren();

	PFB_LOG("Clear Scene");
	mSceneMgr->clearScene();

	PFB_LOG("Create Scene");
	this->createScene();

	PFB_LOG("Look View");
	this->LookView();

	PFB_LOG("Load Field");
	this->LoadField(String(TMPDIR) + String("tmp.field"));

	PFB_LOG("Done RE-Creating Scene");
}

void PFBApplication::ToggleYardLines(bool visible)
{
	unsigned short end = (unsigned short)mSceneMgr->getRootSceneNode()->numChildren(); //numAttachedObjects();
	// loop through the results
	for (unsigned short x = 0; x < end; x++)
	{
		try
		{
			Node *node;
			node = NULL;
			node = mSceneMgr->getRootSceneNode()->getChild(x);
			// Is this result a MovableObject?
			if (node && !NOTFIELDOBJ(node->getName()) && node->getName().find_first_not_of("sceneobject_mainyardline_node_"))                 // Do Not Select Field Or Yardlines
			{
				((SceneNode*)node)->setVisible(visible, true);
			}
		}
		catch (Ogre::Exception ex)
		{
			// The scenenode doesn't exist
		}
	}

	RENDER();
}

void PFBApplication::ToggleFiftyYardLine(bool visible)
{
	// Delete
	SceneNode *n = NULL;
	n = mSceneMgr->getSceneNode("50yrdline_node");
	if (n)
	{
		n->setVisible(visible, true);
	}
	RENDER();
}

void PFBApplication::ToggleCenterYardLine(bool visible)
{
	// Delete
	SceneNode *n = NULL;
	n = mSceneMgr->getSceneNode("C_yrdline_node");
	if (n)
	{
		n->setVisible(visible, true);
	}
	RENDER();
}

void PFBApplication::ToggleSkyBox(bool visible)
{
	// Use the "Space" skybox
	mSceneMgr->setSkyBox(visible, "pfbskybox",3500,true);
	RENDER();
}

void PFBApplication::ToggleShadows(bool visible)
{
	if (visible)
		mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_MODULATIVE);
	else
		mSceneMgr->setShadowTechnique(SHADOWTYPE_NONE);
	RENDER();
}

void PFBApplication::ToggleGouraud(bool visible)
{
	if (visible)
		this->mRoot->getRenderSystem()->setShadingType(SO_GOURAUD);
	else
		this->mRoot->getRenderSystem()->setShadingType(SO_FLAT);
	RENDER();
}

void PFBApplication::ToggleTexture(bool visible)
{
/*
                if (visible)
                this->mCamera->setDetailLevel(SDL_SOLID);
                else
                this->mCamera->setDetailLevel(SDL_WIREFRAME);
 */
	RENDER();
}

void PFBApplication::ToggleSolid(bool visible)
{
	if (visible)
		this->mCamera->setPolygonMode(PM_SOLID);
	else
		this->mCamera->setPolygonMode(PM_WIREFRAME);
	RENDER();
}

int PFBApplication::CreateObject(Real x, Real y, Ogre::String meshname, Ogre::Vector3 *vec, Ogre::String entityname)
{
	if (this->IsTerrainCreated() == false)
	{
		PFB_LOG("warning - terrain not created");
		return -1;
	}

	if (((Bunker*)mFieldKit.GetBunker(mBunker)) == NULL)
	{
		PFB_LOG("warning - No Bunker Is Selected");
		return -1;
	}

	if (this->BunkerClicked(x, y) == true)
	{
		PFB_LOG("warning - Cannot create a bunker on top of a bunker");
		return 0;
	}

	// Setup the ray scene query
	Ray mouseRay = mCamera->getCameraToViewportRay(x, y);
	mRaySceneQuery->setRay(mouseRay);

	// Execute query
	RaySceneQueryResult &result = mRaySceneQuery->execute();
	RaySceneQueryResult::iterator itr = result.begin();

	// Get results, create a node/entity on the position
	if (itr != result.end() && itr->worldFragment)
	{
		if (itr->worldFragment->singleIntersection.y < MAX_BUNKERHEIGHT)
		{
			itr->worldFragment->singleIntersection.y = DEFAULT_BUNKERHEIGHT;

			Entity *ent = NULL;
			SceneNode *node = NULL;
			char name[16] = {0};
			memset(name, NULL, sizeof(name));

			if (entityname.size() == NULL)
			{
				sprintf(name, "bunker_%d", mBunkerCount++);
				PFB_LOG("warning - Manually Setting Bunker Name");
			}
			else
			{
				strcpy(name, entityname.c_str());
				PFB_LOG(name);
			}

			if (meshname.size() == NULL)
			{
				PFB_LOG("Info - Creating Current Entity");
				Bunker *bunker = mFieldKit.GetBunker(mBunker);
				if (!bunker) {
					PFB_LOG("Warning - Failed To Find Bunker");
					return -1;
				}

				// Debug
				String debug = String("Creating Bunker name: ") + name;
				debug += String(", model_name: ") + bunker->model_name;
				PFB_LOG(debug.c_str());

				ent = mSceneMgr->createEntity(name, bunker->model_name);
			}
			else
			{
				PFB_LOG("Info - Regular Creating Entity");

				// Debug
				String debug = String("Creating Bunker name: ") + name;
				debug += String(", model_name: ") + meshname;
				PFB_LOG(debug.c_str());

				ent = mSceneMgr->createEntity(name, meshname);
			}
			if (!ent)
			{
				PFB_LOG("warning - No Entity Could be Created, must be on terrain");
				return 0;
			}
			if (vec == NULL)
			{
				PFB_LOG("Info - Creating Node, Vec was NULL");
				node = mSceneMgr->getRootSceneNode()->createChildSceneNode("node_" + String(name), itr->worldFragment->singleIntersection);
			} else {
				PFB_LOG("Info - Creating Node");
				node = mSceneMgr->getRootSceneNode()->createChildSceneNode("node_" + String(name), *vec);
			}
			if(!node)
			{
				PFB_LOG("warning - A Node Could Not Be Created, must be on terrain");
				return 0;
			}
			node->attachObject(ent);
			SCALEM(node);

			this->SelectNone();
			this->mSelectedObj = node;
			this->mSelectedObj->showBoundingBox(true);
			PFB_LOG("Info - Entity Object Created");
		} else {
			// ground whre creating the Bunker is too tall...
			return 0;
		}
	} else {
		// Can not create a bunker in the AIR
		return 0;
	}

	RENDER();
	return 1;
}

bool PFBApplication::IsTerrainCreated(void)
{
	// Check For Terrain
	try
	{
		if (mSceneMgr->getSceneNode("Terrain") != NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	catch (Ogre::Exception ex)
	{
		return false;  // NO TERRAIN
	}
}

void PFBApplication::SelectObject(Real x, Real y)
{
	SceneNode *node = NULL;

	if (this->IsTerrainCreated() == false)
		return;

	// Setup the ray scene query
	Ray mouseRay = mCamera->getCameraToViewportRay(x, y);
	mRaySceneQuery->setRay(mouseRay);
	mRaySceneQuery->setSortByDistance(true);

	// Execute query
	RaySceneQueryResult &result = mRaySceneQuery->execute();
	RaySceneQueryResult::iterator itr = result.begin();

	// loop through the results
	for ( itr = result.begin( ); itr != result.end(); itr++ )
	{
		// Is this result a MovableObject?
		if (itr->movable && (itr->movable->getMovableType() == "Entity") &&
		    NOTFIELDOBJ(itr->movable->getName()))       // Do Not Select Field Or Yardlines
		{
			node = itr->movable->getParentSceneNode();
			if (node)
			{
				if (node == mSelectedObj) // Selected Object Twice
				{
					if (mSelectedObj)  // Deselect Old Object
						mSelectedObj->showBoundingBox(false);

					mSelectedObj = NULL;
					node = NULL;
					break; // Do Nothing Already Selected This Object
				}

				if (mSelectedObj) // Deselect Old Object
					mSelectedObj->showBoundingBox(false);

				node->showBoundingBox(true);
				mSelectedObj = node;
			}
			break;         // Only Select Closest Node
		}
	}
/* // Deselect When Nothing Is Found To Select
           if (node == NULL)
           {
                      if (mSelectedObj) // Deselect Current Object
                                  {
                        mSelectedObj->showBoundingBox(false);
                        mSelectedObj = NULL;
                                  }
           }
 */
	mRaySceneQuery->setSortByDistance(false);
	RENDER();
}

void PFBApplication::SelectNone(void)
{
	if (mSelectedObj)               // Deselect Current Object
	{
		mSelectedObj->showBoundingBox(false);
		mSelectedObj = NULL;
	}
	RENDER();
}

void PFBApplication::DeleteAllBunkers(void)
{
	unsigned short end = NULL;
	end = (unsigned short)mSceneMgr->getRootSceneNode()->numChildren();

	//if (end == 0)
	//return;

	// loop through the results
	for (unsigned short x = 0; x < end; x++)
	{
		try
		{
			Node *node = NULL;
			node = mSceneMgr->getRootSceneNode()->getChild(x);
			// Is this result a MovableObject?
			if (node && NOTFIELDOBJ(node->getName()))         // Do Not Select Field Or Yardlines
			{
				SceneNode *snode = this->mSceneMgr->getSceneNode(node->getName());
				snode->detachAllObjects();
				snode->removeAndDestroyAllChildren();
				//this->mSceneMgr->destroySceneNode(snode->getName());
			}
		}
		catch (Ogre::Exception ex)
		{
			// The scenenode doesn't exist
		}
	}
	RENDER();
}

void PFBApplication::DeleteAllFieldObjects(void)         // NOT WORKING 100% YET
{
	unsigned short end = NULL;
	end = (unsigned short)mSceneMgr->getRootSceneNode()->numChildren();

	//if (end == 0)
	//return;

	// loop through the results
	for (unsigned short x = 0; x < end; x++)
	{
		try
		{
			Node *node = NULL;
			node = mSceneMgr->getRootSceneNode()->getChild(x);
			// Is this result a MovableObject?
			if (node && strcmp("Terrain", node->getName().c_str()) && !NOTFIELDOBJ(node->getName()))         // Do Not Select Field Or Yardlines
			{
				SceneNode *snode = this->mSceneMgr->getSceneNode(node->getName());

				if ( strcmp("Terrain", snode->getName().c_str()) )
				{
					snode->detachAllObjects();
					snode->removeAndDestroyAllChildren();
					//this->mSceneMgr->destroySceneNode(snode->getName());
				}
			}
		}
		catch (Ogre::Exception ex)
		{
			// The scenenode doesn't exist
		}
	}
	RENDER();
}

bool PFBApplication::MirrorBunkers(void)
{
	Node *node = NULL;
	SceneNode *snode = NULL;
	unsigned short end = NULL;

	unsigned short top = NULL;
	unsigned short bottom = NULL;
	bool mirrortop = true;

	std::vector<BunkerInfo> mirrornodes;
	unsigned short mirrornodes_count = NULL;


	end = (unsigned short)mSceneMgr->getRootSceneNode()->numChildren();

	// Count Bunkers On Each Side Of Field
	for (unsigned short x = 0; x < end; x++)
	{
		try
		{
			node = NULL;
			snode = NULL;
			node = mSceneMgr->getRootSceneNode()->getChild(x);
			snode = mSceneMgr->getSceneNode(node->getName());

			// Is this result a MovableObject?
			if (snode && NOTFIELDOBJ(snode->getName())) // Do Not Select Field Or Yardlines
			{
				if (snode->getPosition().x > (TERRAIN_S/2)+MIRROR_SAFE)
				{
					Entity *e = 0;
					e = (Entity*)snode->getAttachedObject(0);
					if (e && NOTFIELDOBJ(e->getName()))
					{
						top++;
					}
				}
				else if (snode->getPosition().x < (TERRAIN_S/2)-MIRROR_SAFE)
				{
					Entity *e = 0;
					e = (Entity*)snode->getAttachedObject(0);
					if (e && NOTFIELDOBJ(e->getName()))
					{
						bottom++;
					}
				}
			}
		}
		catch (Ogre::Exception ex)
		{
		}
	}

	// Check Limits
	if (!top && !bottom)
		return false;
	if (top == bottom)
		return false;
	if (top > bottom)
	{
		if (bottom >= MIRROR_MAX)
		{
			return false;
		}
		mirrortop = true;
	}
	if (bottom > top)
	{
		if (top >= MIRROR_MAX)
		{
			return false;
		}
		mirrortop = false;
	}

	// Count Bunkers On Each Side Of Field
	for (x = 0; x < end; x++)
	{
		try
		{
			node = NULL;
			node = mSceneMgr->getRootSceneNode()->getChild(x);
			snode = NULL;
			snode = mSceneMgr->getSceneNode(node->getName());

			// Is this result a MovableObject?
			if (snode && NOTFIELDOBJ(snode->getName())) // Do Not Select Field Or Yardlines
			{
				Entity *e = NULL;
				BunkerInfo binfo;
				bool mirrorit = false;

				if (mirrortop == true)
					if ( snode->getPosition().x > (TERRAIN_S/2)+MIRROR_SAFE )
					{
						binfo.pos = snode->getPosition();
						binfo.or =  snode->getOrientation();
						binfo.pos.x += 2*((TERRAIN_S/2)-binfo.pos.x);
						mirrorit = true;
					}

				if (mirrortop == false)
					if ( snode->getPosition().x < (TERRAIN_S/2)-MIRROR_SAFE )
					{
						binfo.pos = snode->getPosition();
						binfo.or =  snode->getOrientation();
						binfo.pos.x += 2*((TERRAIN_S/2)-binfo.pos.x);
						mirrorit = true;
					}

				if (mirrorit == true)
				{
					e = (Entity*)snode->getAttachedObject(0);
					if (e && NOTFIELDOBJ(e->getName()))
					{
						binfo.meshname.clear();
						binfo.meshname.empty();
						binfo.meshname += e->getMesh()->getName();
					}
					mirrornodes.push_back(binfo);
					mirrornodes_count++;
				}
			}
		}
		catch (Ogre::Exception ex)
		{
		}
	}

	for (x = 0; x < mirrornodes_count; x++)
	{
		try
		{
			if (mirrornodes[x].meshname.size() != NULL)
			{
				// Create Entity
				Entity *mirent = NULL;
				SceneNode *mirnode = NULL;
				char bname[16] = {0};
				memset(bname, NULL, sizeof(bname));
				sprintf(bname, "bunker_%d", mBunkerCount++);                 // NOT TESTED
				mirent = mSceneMgr->createEntity(String(bname), mirrornodes[x].meshname);
				if (mirent)
				{
					mirnode = mSceneMgr->getRootSceneNode()->createChildSceneNode("node_" + String(bname));
					if (mirnode)
					{
						mirnode->attachObject(mirent);
						SCALEM(mirnode);
						mirnode->setPosition(mirrornodes[x].pos);
						mirnode->setOrientation(mirrornodes[x].or);
					}
				}
			}
		}
		catch (Ogre::Exception ex)
		{
			PFB_LOG("Failed To Mirror Field");
		}
	}
	RENDER();
	return true;
}

void PFBApplication::SaveField(String name)
{
	std::vector<BunkerInfo> bunker;

	Node *node = NULL;
	char header[10] = {'H', 'P', 'B', 'F', 'I', 'E', 'L', 'D', NULL, NULL};
	BYTE ver = FIELDVER;
	unsigned short bunkercount = 0;
	unsigned short end = 0;

	// If .field is not in file, name add it
	if (String::npos == name.find(".field"))
		name += ".field";

	// Just In Case
	PFB_Wait(500);

	end = (unsigned short)mSceneMgr->getRootSceneNode()->numChildren();        //numAttachedObjects();
	// loop through the results
	for (unsigned short x = 0; x < end; x++)
	{
		try
		{
			node = NULL;
			node = mSceneMgr->getRootSceneNode()->getChild(x);
			// Is this result a MovableObject?
			if (node && NOTFIELDOBJ(node->getName()))                 // Do Not Select Field Or Yardlines
			{
				Entity *e = NULL;
				e = (Entity*)((SceneNode*)node)->getAttachedObject(0);
				if (e && (e->getMovableType() == "Entity"))
				{
					BunkerInfo binfo;
					binfo.meshname.clear();
					binfo.meshname.empty();
					binfo.meshname += e->getMesh()->getName();
					binfo.pos = node->_getDerivedPosition();
					binfo.or = node->_getDerivedOrientation();
					if (binfo.meshname.size() != NULL)
					{
						bunkercount++;
						bunker.push_back(binfo);
					}
				}
			}
		}
		catch (Ogre::Exception ex)
		{
			// The scenenode doesn't exist
		}
	}

	std::ofstream file(name.c_str(), std::ofstream::out | std::ofstream::binary);
	file.write(header, sizeof(header));
	file.write((char*)&ver, sizeof(ver));
	file.write((char*)&bunkercount, sizeof(bunkercount));
	file.write((char*)&mFIELDWIDTH, sizeof(mFIELDWIDTH));
	file.write((char*)&mFIELDLENGTH, sizeof(mFIELDLENGTH));
	file.write((char*)&mGRIDWIDTH, sizeof(mGRIDWIDTH));
	file.write((char*)&mGRIDLENGTH, sizeof(mGRIDLENGTH));
	file.write((char*)&mUnitM, sizeof(mUnitM));

	// loop through the results
	for (unsigned short x = 0; x < bunkercount; x++)
	{
		try
		{
			if (bunker[x].meshname.size() != NULL)
			{
				char tname[MAXSTR] = {0};
				memset(tname, NULL, sizeof(tname));
				strcpy(tname, bunker[x].meshname.c_str());
				file.write(tname, sizeof(tname));
				file.write((char*)&bunker[x].pos, sizeof(bunker[x].pos));
				file.write((char*)&bunker[x].or, sizeof(bunker[x].or));
				PFB_LOG(tname);
			}
		}
		catch (Ogre::Exception ex)
		{
			PFB_LOG("Error Saving Field");
		}
	}

	file.close();

	this->mLastField = name;
}

void PFBApplication::LoadField(String name)
{
	char header[10] = {NULL};
	BYTE ver = 0;
	unsigned short end = 0;
	bool failed = false;
	String failed_names = "Failed To Find: ";

	// Just In Case
	PFB_Wait(500);

	std::ifstream file(name.c_str(), std::ofstream::in | std::ofstream::binary);
	file.read(header, sizeof(header));
	if (strcmp(header, "HPBFIELD"))
	{
		PFB_LOG("CORRUPT FILE, INCORRECT HEADER");
		file.close();
		return;
	}

	file.read((char*)&ver, sizeof(ver));
	if (ver > FIELDVER)
	{
		PFB_LOG("This Version Is Not Supported");
		file.close();
		return;
	}

	// Cleanup Bunkers that are left on field
	this->DeleteAllBunkers();

	file.read((char*)&end, sizeof(end));
/*
                if (!end)
                {
                        PFB_LOG("CORRUPT FILE, NO BUNKERS");
                        file.close();
                        return;
                }
 */

	file.read((char*)&mFIELDWIDTH, sizeof(mFIELDWIDTH));
	file.read((char*)&mFIELDLENGTH, sizeof(mFIELDLENGTH));
	file.read((char*)&mGRIDWIDTH, sizeof(mGRIDWIDTH));
	file.read((char*)&mGRIDLENGTH, sizeof(mGRIDLENGTH));
	if (ver == 0x01)
	{
		mUnitM  = WORLDUNITSPERYARD;
	}
	else if (ver == 0x02)
	{
		file.read((char*)&mUnitM, sizeof(mUnitM));
	}

	if (!mFIELDWIDTH || !mFIELDLENGTH || !mGRIDWIDTH || !mGRIDLENGTH)
	{
		PFB_LOG("CORRUPT FILE, INVALID GRID OR FIELD");
		file.close();
		return;
	}

	for (unsigned short x = 0; x < end; x++)
	{
		char bname[MAXSTR] = {0};
		char tname[MAXSTR] = {0};
		memset(bname, NULL, sizeof(bname));
		memset(tname, NULL, sizeof(tname));
		Vector3 pos;
		Quaternion or;
		try
		{
			// Read Entity
			file.read((char*)tname, sizeof(tname));
			file.read((char*)&pos, sizeof(pos));
			file.read((char*)&or, sizeof(or));

			// Create Entity
			Entity *ent = NULL;
			SceneNode *node = NULL;
			sprintf(bname, "bunker_%d", mBunkerCount++);
			ent = mSceneMgr->createEntity(String(bname), tname);
			node = mSceneMgr->getRootSceneNode()->createChildSceneNode("node_" + String(bname));
			node->attachObject(ent);
			SCALEM(node);
			node->setPosition(pos);
			node->setOrientation(or);
		}
		catch (Ogre::Exception ex)
		{
			// The scenenode doesn't exist
			failed_names += tname;
			failed_names += ", ";
			failed = true;
		}
	}
	file.close();

	if (failed)
	{
		String tmp;
		tmp +="Error While Loading Field, You Could Not Have A Field Kit That Is Required To Load The Field. ";
		tmp += failed_names;
		PFB_LOG(tmp.c_str());
	}

	RENDER();
}


void PFBApplication::LookTop(void)
{
	mCamera->setAutoTracking(false);
	mCamera->setPosition((TERRAIN_S/2)+1, 70*WORLDUNITSPERYARD*SCALE, TERRAIN_S/2);
	mCamera->lookAt(TERRAIN_S/2, 1, TERRAIN_S/2);
}


void PFBApplication::LookPerspective(void)
{
	mCamera->setAutoTracking(false);
	mCamera->setPosition((TERRAIN_S/2)+((mFIELDLENGTH+10)*WORLDUNITSPERYARD*SCALE), 20*WORLDUNITSPERYARD*SCALE, TERRAIN_S/2);
	mCamera->lookAt(TERRAIN_S/2, 1, TERRAIN_S/2);
	mCamera->setAutoTracking(true, this->mSceneMgr->getSceneNode("50yrdline_node"), Vector3(0, 32*SCALE, 0));
	this->CheckRange();
}


void PFBApplication::LookFirstPerson(void)
{
	mCamera->setAutoTracking(false);
	mCamera->setPosition((TERRAIN_S/2)+((mFIELDLENGTH+10)*WORLDUNITSPERYARD*SCALE), WORLDUNITSPERFOOT*5.0f*SCALE, TERRAIN_S/2);
	mCamera->lookAt(TERRAIN_S/2, WORLDUNITSPERFOOT*5.0f*SCALE, TERRAIN_S/2);
	this->CheckRange();
}


bool PFBApplication::BunkerClicked(Real x, Real y)
{
/*
           SceneNode *lastnode = 0;
           lastnode = this->mSelectedObj;
 */
	this->SelectNone();
	this->SelectObject(x, y);
	if (this->mSelectedObj)
	{
/*
                        this->mSelectedObj = lastnode;
                        if (this->mSelectedObj)
                        {
                                this->mSelectedObj->showBoundingBox(true);
                        }
 */
		return true;
	}
/*
           this->mSelectedObj = lastnode;
           if (this->mSelectedObj)
           {
                this->mSelectedObj->showBoundingBox(true);
           }
 */
	return false;
}


void PFBApplication::createCamera(void)
{
	// Create the camera
	mCamera = mSceneMgr->createCamera("PlayerCam");

	// Position it at 500 in Z direction
	mCamera->setPosition(Vector3(0,0,500));
	// Look back along -Z
	mCamera->lookAt(Vector3(0,0,-300));
	mCamera->setNearClipDistance(5);
	mCamera->setFarClipDistance(7000.00f);

}


void PFBApplication::createViewports(void)
{
	// Create one viewport, entire window
	Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(ColourValue(0,0,0));

	// Alter the camera aspect ratio to match the viewport
	mCamera->setAspectRatio(
	        Real(vp->getActualWidth()) / Real(vp->getActualHeight()));
}


/// Method which will define the source of resources (other than current folder)
void PFBApplication::setupResources(void)
{
	// Load resource paths from config file
	ConfigFile cf;
	cf.load(mResourcePath + "resources.cfg");

	// Go through all sections & settings in the file
	ConfigFile::SectionIterator seci = cf.getSectionIterator();

	String secName, typeName, archName;
	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		ConfigFile::SettingsMultiMap *settings = seci.getNext();
		ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;
			ResourceGroupManager::getSingleton().addResourceLocation(
			        archName, typeName, secName);
		}
	}
}


/// Optional override method where you can create resource listeners (e.g. for loading screens)
void PFBApplication::createResourceListener(void)
{

}


/// Optional override method where you can perform resource group loading
/// Must at least do ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
void PFBApplication::loadResources(void)
{
	// Initialise, parse scripts etc
	ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

}


bool PFBApplication::setup(void)
{
	String pluginsPath;
	// only use plugins.cfg if not static
#ifndef OGRE_STATIC_LIB
	pluginsPath = mResourcePath + "plugins.cfg";
#endif

	mRoot = new Root(pluginsPath,
	                 mResourcePath + "ogre.cfg", mResourcePath + "Ogre.log");

	setupResources();

	bool carryOn = configure();
	if (!carryOn) return false;

	// Get the SceneManager, in this case a generic one
	mSceneMgr = mRoot->createSceneManager("TerrainSceneManager");

	createCamera();
	createViewports();

	// Set default mipmap level (NB some APIs ignore this)
	TextureManager::getSingleton().setDefaultNumMipmaps(5);

	// Create any resource listeners (for loading screens)
	createResourceListener();

	// Load resources
	loadResources();

	// Create the scene
	createScene();

	// Create RaySceneQuery
	mRaySceneQuery = mSceneMgr->createRayQuery(Ray()); // ADDED FOR PICKING

	return true;
}


void PFBApplication::createBasic(void)
{
	// Terrain
	PFB_LOG("Set Viewport Color");
	this->mWindow->getViewport(0)->setBackgroundColour(this->mBackground);

	// Fog
	PFB_LOG("Set Fog Color");
	mSceneMgr->setFog(FOG_LINEAR, ColourValue::White, 0.09f, 2000.00f, 4000.00f);

	// Lights
	if (this->mRenderer == PFB_RENDER_DIRECT3D9)
	{
		//mSceneMgr->removeLight("light_1"); // BIG BUG FIX v1.0.6 CHANGE
		PFB_LOG("Create Light");
		Light *light = NULL;
		light = mSceneMgr->createLight("light_1");
		if (light)
		{
			light->setType(Ogre::Light::LT_POINT);
			light->setPosition((TERRAIN_S/2)+500,900,(TERRAIN_S/2)+1000);
			light->setDiffuseColour(10.0f,10.0f,10.0f);
			light->setSpecularColour(2.0f,2.0f,2.0f);
			light->setCastShadows(true);
		}

		// Shadows
		PFB_LOG("Setup Shadows");
		this->mSceneMgr->setShadowTechnique(SHADOWTYPE_TEXTURE_MODULATIVE);
		this->mSceneMgr->setShadowColour(ColourValue(0.5, 0.5, 0.5));
		//this->mSceneMgr->setShadowFarDistance(6000);
		//this->mSceneMgr->setShadowTextureSettings(512, 2);
	}

	// field node
	PFB_LOG("Create Field Node");
	SceneNode *fieldnode = mSceneMgr->getRootSceneNode()->createChildSceneNode("field_node", Vector3(TERRAIN_S/2, Y_EXTRA, TERRAIN_S/2));
	// Load field
	Entity *field = mSceneMgr->createEntity("field_entity", "field.mesh");
	fieldnode->attachObject(field);
	fieldnode->scale(mFIELDLENGTH*(mUnitM/WORLDUNITSPERYARD), 1, mFIELDWIDTH*(mUnitM/WORLDUNITSPERYARD));
	field->setCastShadows(false);

	// 50YardLine node
	PFB_LOG("Create 50 Yard Line");
	SceneNode *fiftyyardlinenode = mSceneMgr->getRootSceneNode()->createChildSceneNode("50yrdline_node", Vector3(TERRAIN_S/2, Y_EXTRA, TERRAIN_S/2));
	// field 50YardLine
	Entity *fiftyyardline = mSceneMgr->createEntity("50yrdline_entity", "50yardline.mesh");
	fiftyyardlinenode->attachObject(fiftyyardline);
	fiftyyardlinenode->scale(LINE_EXTRA+LINE_EXTRA_, 1, mFIELDWIDTH*(mUnitM/WORLDUNITSPERYARD));
	fiftyyardline->setCastShadows(false);


	// centerYardLines node
	PFB_LOG("Create Center Yard Line");
	SceneNode *centeryardlinenode = mSceneMgr->getRootSceneNode()->createChildSceneNode("C_yrdline_node", Vector3(TERRAIN_S/2, Y_EXTRA, TERRAIN_S/2));
	// field centerYardLines
	Entity *centeryardline = mSceneMgr->createEntity("C_yrdline_entity", "centeryardline.mesh");
	centeryardlinenode->attachObject(centeryardline);
	centeryardlinenode->scale(mFIELDLENGTH*(mUnitM/WORLDUNITSPERYARD), 1, LINE_EXTRA+LINE_EXTRA_);
	centeryardline->setCastShadows(false);

	// Scale Down
	PFB_LOG("Scale Field Objects");
	SCALEM(fieldnode);
	SCALEM(fiftyyardlinenode);
	SCALEM(centeryardlinenode);

	// Create Width Yard Lines
	PFB_LOG("Create Width Yard Lines");
	Real unit = mUnitM;
	Real a = (mGRIDLENGTH*mUnitM)+1;
	Real c = (TERRAIN_S/2)+((mGRIDLENGTH*mUnitM*SCALE)/2);
	char bname[MAXSTR] = {0};

	for (Real x = 0; x < a; x += unit)
	{
		if ( (x >= (TERRAIN_S/2)-2) || (x <= (TERRAIN_S/2)+2) )
		{
			sprintf(bname, "sceneobject_mainyardline_node_h_%d", (int)(x));
			String tname = String(bname) + String("Node");
			SceneNode *llnode = mSceneMgr->getRootSceneNode()->createChildSceneNode(bname, Vector3(c-(x*SCALE), Y_EXTRA, TERRAIN_S/2));
			Entity *llentity = mSceneMgr->createEntity(tname.c_str(), "yardline.mesh");
			llnode->attachObject(llentity);
			SCALEM(llnode);
			llnode->scale(LINE_EXTRA, 0.5f, (Real)mGRIDWIDTH*(Real)(mUnitM/(Real)WORLDUNITSPERYARD));
			llentity->setCastShadows(false);
		}
	}

	// Create Length Yard Lines
	PFB_LOG("Create Length Yard Lines");
	Real e = (mGRIDWIDTH*mUnitM)+1;
	Real g = (TERRAIN_S/2)+((mGRIDWIDTH*mUnitM*SCALE)/2);
	Degree d; d = 90;
	Radian r(d);
	for (Real x = 0; x < e; x += unit)
	{
		if ( (x >= (TERRAIN_S/2)-2) || (x <= (TERRAIN_S/2)+2) )
		{
			sprintf(bname, "sceneobject_mainyardline_node_w_%d", (int)(x));
			String tname = String(bname) + String("Node");
			SceneNode *llnode = mSceneMgr->getRootSceneNode()->createChildSceneNode(bname, Vector3(TERRAIN_S/2, Y_EXTRA, g-(x*SCALE)));
			Entity *llentity = mSceneMgr->createEntity(tname.c_str(), "yardline.mesh");
			llnode->attachObject(llentity);
			SCALEM(llnode);
			llnode->scale(LINE_EXTRA, 0.4f, (Real)mGRIDLENGTH*(Real)(mUnitM/(Real)WORLDUNITSPERYARD));
			llnode->rotate(Vector3(0, 1, 0), r, Ogre::Node::TransformSpace::TS_LOCAL);
			llentity->setCastShadows(false);
		}
	}
	PFB_LOG("Done Creating Basic Scene");

	// Default Values
	PFB_LOG("...Setting Default Settings");
	this->ToggleCenterYardLine(this->mViewOptions._centeryardline);
	this->ToggleFiftyYardLine(this->mViewOptions._fiftyyardline);
	this->ToggleGouraud(this->mViewOptions._gouraud);
	this->ToggleShadows(this->mViewOptions._shadows);
	this->ToggleSkyBox(this->mViewOptions._skybox);
	this->ToggleSolid(this->mViewOptions._solid);
	this->ToggleTerrain(this->mViewOptions._terrain);
	this->ToggleTexture(this->mViewOptions._texture);
	this->ToggleYardLines(this->mViewOptions._yardlines);
	PFB_LOG("Done Setting Default Settings");

	// Render
	RENDER();
	PFB_LOG("Rendered Scene");
}


void PFBApplication::createScene(void)
{
	// Load Terraing
	PFB_LOG("Creating Terrain");
	mSceneMgr->setWorldGeometry("terrain.cfg");

	// Turn Off Terrain
	PFB_LOG("Turn Off Terrain");
	this->ToggleTerrain(false);

	// Basic Layout
	PFB_LOG("Create Basic");
	this->createBasic();
	RENDER();
}


void PFBApplication::destroyScene(void)
{
	// Destroy RaySceneQuery
	delete mRaySceneQuery; // ADDED FOR PICKING
}


bool PFBApplication::configure(void)
{
	this->LoadSettings();
	char rendersystem[MAXSTR] = {0};
	memset(rendersystem, NULL, sizeof(rendersystem));

	// Find A RenderSystem
	Ogre::RenderSystemList *rsList = mRoot->getAvailableRenderers();
	size_t c=0;
	bool foundit = false;
	Ogre::RenderSystem *selectedRenderSystem=0;
	for (char x = 0; x < 2; x++)
	{
		try
		{
			switch (mRenderer)
			{
			case PFB_RENDER_OPENGL:
				strcpy(rendersystem, "OpenGL Rendering Subsystem");
				break;

			case PFB_RENDER_DIRECT3D9:
				strcpy(rendersystem, "Direct3D9 Rendering SubSystem");
				break;
			}

			while(c < rsList->size())
			{
				selectedRenderSystem = NULL;
				selectedRenderSystem = rsList->at(c);
				if(!selectedRenderSystem->getName().compare(rendersystem))
				{
					foundit=true;
					break;
				}
				c++;
			}

			if(!foundit) // return false; //we didn't find it...
				selectedRenderSystem = rsList->at(0); // Direct3D9 Render System

			//we found it, we might as well use it!
			mRoot->setRenderSystem(selectedRenderSystem);

			break;
		}
		catch (Ogre::Exception ex)
		{
			PFB_LOG("Failed To Find Renderer");

			switch (mRenderer)
			{
			case PFB_RENDER_OPENGL:
				mRenderer = PFB_RENDER_DIRECT3D9;
				break;

			case PFB_RENDER_DIRECT3D9:
				mRenderer = PFB_RENDER_OPENGL;
				break;
			}
		}
		PFB_LOG("One Loop For Renderer");
	}

	try
	{
		selectedRenderSystem->setConfigOption("Full Screen","No");
		selectedRenderSystem->setConfigOption("Video Mode","800 x 600 @ 16-bit colour");
		selectedRenderSystem->setConfigOption("Anti aliasing","None");
		selectedRenderSystem->setConfigOption("VSync","Yes");
		selectedRenderSystem->setConfigOption("Floating-point mode","Consistent");
	}
	catch (Ogre::Exception ex)
	{
		// Catch OGRE ERROR
	}

	// Once The Render Options Have Been Selected Go Ahead And Create Viewport Window
	NameValuePairList params;
	params["externalWindowHandle"] = StringConverter::toString((size_t)this->mWindowHandle);
	// Here we choose to let the system create a default rendering window by passing 'true'
	mRoot->initialise(false);
	mWindow = NULL;
	mWindow = mRoot->createRenderWindow("PFDEditClass", 800, 600, false, &params);

	if (!this->mWindow) {
		return false;
	}

	return true;
}