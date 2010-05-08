/**
 * ---------------------------------------------------------
 * @author: David Whiteside
 * @date: 11/14/09
 * @description: Application Entry Point
 * Copyright 2004-2009 Whiteside Solutions LLC (www.whitesidesolutions.com)
 * ---------------------------------------------------------
 */

#include "../inc/main.h"
#include "../inc/guiParentWindow.h"
#include "../inc/guiRenderWindow.h"
#include "../inc/guiObjectWindow.h"
#include "../inc/Application.h"
#include "../inc/wsLogFile.h"

// Use MyApp Class for wxWidgets
IMPLEMENT_APP(MyApp)

// Static Class Variables
PFBApplication MyApp::s_App;
CWSLogFile MyApp::s_Log;
CURSORTOOL MyApp::s_CursorTool;
VIEWMODE MyApp::s_ViewMode;

bool MyApp::OnInit()
{
	// Parent/Main Window
	m_ParentWindow = new guiParentWindow(wxT("Paintball Field Builder"));
	m_ParentWindow->Show(true);
	m_ParentWindow->SetBackgroundColour(wxColour(0x70, 0x70, 0x70));
	m_ParentWindow->Maximize();
    
	// Render/OGRE Window
	m_RenderWindow = new guiRenderWindow(wxT("Paintball Field Builder"), m_ParentWindow);
	m_RenderWindow->Show(true);
	m_RenderWindow->SetBackgroundColour(wxColour(0x4d, 0x4d, 0x4d));	
	m_RenderWindow->SetAutoLayout(true);
	void *phandle = m_RenderWindow->GetHandle();
	if (phandle) {
		s_App.SetRenderWindow(phandle);
	} else {
		PFB_ERRORMESSAGE("Failed To Get HWND from window");
	}

	// Object Window
	m_ObjectWindow = new guiObjectWindow(wxT("Paintball Field Builder"), m_ParentWindow);
	m_ObjectWindow->Show(true);
	m_ObjectWindow->SetBackgroundColour(wxColour(0, 255, 0));
	m_ObjectWindow->SetAutoLayout(true);

   // Initialize OGRE
    try {
        s_App.go();
		PFB_LOG("OGRE WAS INITIALIZED");
		s_App.LookView();
		s_App.mDoRender = true;
		s_App.Render();
    } catch( Ogre::Exception& e ) {
		PFB_ERRORMESSAGE(e.getFullDescription().c_str());
		PFB_LOG("OGRE FAILED TO INITILISE");
		return 1;
    }

	// Rendering Loop
	Connect(wxEVT_IDLE, wxIdleEventHandler(MyApp::OnIdle));

	return true;
}

int MyApp::OnExit()
{
	// Cleanup
	return true;
}

void MyApp::OnIdle(wxIdleEvent& event)
{
   s_App.Render();
   event.RequestMore(true);
}
