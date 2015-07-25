/**
 * ---------------------------------------------------------
 * @author: David Whiteside
 * @date: 09/20/09
 * @description: OGRE Application API
 * Copyright (c) 2005-2015 David Whiteside
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
 * THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * ---------------------------------------------------------
 */

#ifndef _APPLICATION_
#define _APPLICATION_

#include "../inc/CommonTypes.h"
#include "../inc/UndoRedo.h"



struct VIEWOPTIONS
{
	bool _terrain;
	bool _fiftyyardline;
	bool _yardlines;
	bool _skybox;
	bool _centeryardline;
	bool _shadows;
	bool _gouraud;
	bool _texture;
	bool _solid;
};

#define RENDER() if (mDoRender) this->Render();
#define NOTFIELDOBJ(a) ( (String::npos != a.find("bunker_")) || (String::npos != a.find("node_bunker_")) )

#define TERRAIN_S 5000
#define LINE_EXTRA 12
#define LINE_EXTRA_ 10
#define WORLDUNITSPERYARD 20
#define WORLDUNITSPERMETER ((float)WORLDUNITSPERYARD*1.0936133f)
#define WORLDUNITSPERFOOT ((float)WORLDUNITSPERYARD/3.0f)
#define WORLDUNITSPERINCH ((float)WORLDUNITSPERFOOT/12.0f)
#define SCALE 0.3f
#define SCALEM(a) a->scale(SCALE, SCALE, SCALE);
#define Y_EXTRA 0.2f
#define MIRROR_SAFE 1*SCALE*WORLDUNITSPERYARD
#define MIRROR_MAX 1

#define MAX_BUNKERHEIGHT (float)5*SCALE
#define DEFAULT_BUNKERHEIGHT 0

#define MAX_FIELDWIDTH 150
#define MAX_FIELDLENGTH 150
#define MAX_GRIDWIDTH 150
#define MAX_GRIDLENGTH 150

#define MIN_FIELDWIDTH 5
#define MIN_FIELDLENGTH 5
#define MIN_GRIDWIDTH 5
#define MIN_GRIDLENGTH 5

// 0x01 - The First Version, Small Change In Version 1.0.1 that fixes bug in 1.0.0
// 0x02 - The 2nd Version, Added A Unit Of Measure
#define FIELDVER 0x02

#define PFB_RENDER_OPENGL		0x00
#define PFB_RENDER_DIRECT3D9    0x01

#define PFB_DEFAULT_RENDER      PFB_RENDER_DIRECT3D9


class PFBApplication : public CUndoRedo
{
protected:
// Core Stuff
Root *mRoot;
Camera *mCamera;
SceneManager *mSceneMgr;
RenderWindow *mWindow;
Ogre::String mResourcePath;

// Other stuff
RaySceneQuery *mRaySceneQuery;
size_t mBunkerCount;
Vector3 mLast_top;
Quaternion mLast_topo;
Vector3 mLast_firstperson;
Quaternion mLast_firstpersono;
Vector3 mLast_perspective;
Quaternion mLast_perspectiveo;
size_t mLightCount;

// Saved
char mRenderer;
char mLastFieldKit[MAXSTR];
String mLastField;

public:
SceneNode *mSelectedObj;

// Public Options
ColourValue mBackgroundColor;
Real mUnitM;
unsigned int mFIELDWIDTH;
unsigned int mFIELDLENGTH;
unsigned int mGRIDWIDTH;
unsigned int mGRIDLENGTH;
VIEWMODE mViewMode;						// The View Tool Mode
bool mDoRender;							// Used To Enable Disable Rendering
CFieldKit mFieldKit;					// The Loaded Field Kit
BunkerID mBunker;						// The Selected Bunker
void *mWindowHandle;

// Saved Settings
ColourValue mBackground;
VIEWOPTIONS mViewOptions;

// Setter/Getter
inline char GetRenderer(void) { return mRenderer; }
inline void SetLastFieldKit(const char *str) { if(strlen(str)<sizeof(mLastFieldKit))strcpy(mLastFieldKit, str); }
inline char *GetLastFieldKit(void) { return mLastFieldKit; }
inline void SetRenderWindow(void *handle) { this->mWindowHandle = handle; }

// Constructor/Destructor
PFBApplication();
virtual ~PFBApplication();

// OGRE Rendering
void go(void);
void Render(void);
void stop();

// UI Functions
void LoadSettings(void);
void SaveSettings(void);
bool ChangeRenderer(char Renderer);
void MoveView(Real x, Real z, Real y = 0);
void RotateView(Real x, Real z);
void LookView(void);
void ResetView(void);
void SaveCurrentView(void);
void SetBackgroundColor(ColourValue rgb);
void TakeScreenShot(const char *file);
void ToggleTerrain(bool visible);
void ReCreateScene(void);
void ToggleYardLines(bool visible);
void ToggleFiftyYardLine(bool visible);
void ToggleCenterYardLine(bool visible);
void ToggleSkyBox(bool visible);
void ToggleShadows(bool visible);
void ToggleGouraud(bool visible);
void ToggleTexture(bool visible);
void ToggleSolid(bool visible);
// Return 1 if sucessful, 0 for failed because no terrain, -1 for failed with errors
int CreateObject(Real x, Real y, Ogre::String meshname = "", Ogre::Vector3 *vec = 0, Ogre::String entityname = "");
void SelectObject(Real x, Real y);
void MoveSelectedObj(Real x, Real y);
void CloneSelectedObj(void);
void RotateSelectedObj(Real x, Real y);
void DeleteSelectedObj(void);
void SelectNone(void);
void DeleteAllBunkers(void);
void DeleteAllFieldObjects(void);
bool MirrorBunkers(void);
// If the field has been saved before then return true
bool SaveField()
{
	if (this->mLastField.size() > 0) {
		this->SaveField(this->mLastField);
		return true;
	}
	return false;
}
void SaveField(String name);
void LoadField(String name);
void LookTop(void);
void LookPerspective(void);
void LookFirstPerson(void);
bool BunkerClicked(Real x, Real y);
void MakeURChange(bool undo);

/*
Used by GUI to place undo/redo points for actions
*/
inline void AddURSpotSelectedObj(UNDOREDO_ACT action) {
	if (mSelectedObj) {
		this->AddURSpot(action, mSelectedObj);
	}
}

protected:
void AddURSpot(UNDOREDO_ACT action, SceneNode *node);
bool CloneObj(SceneNode *&node);
bool RotateObj(SceneNode *&node, Real x, Real y);
bool DeleteObj(SceneNode *&node);
void CheckRange(void);
bool IsTerrainCreated(void);
void createCamera(void);
void createViewports(void);
virtual void setupResources(void);
virtual void createResourceListener(void);
virtual void loadResources(void);
bool setup(void);
void createBasic(void);
void createScene(void);
void destroyScene(void);
bool configure(void);
};


#endif
