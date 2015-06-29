/**
 * ---------------------------------------------------------
 * @author: David Whiteside
 * @date: 09/20/09
 * @description: Main Entry Point Of Applicaiton
 * Copyright 2004-2009 Whiteside Solutions LLC (www.whitesidesolutions.com)
 * ---------------------------------------------------------
 */
#ifndef PFB_MAIN_H
#define PFB_MAIN_H


#include <wx/wx.h>
#include <wx/image.h>
#include <wx/splash.h>
//#include <wskey.h>
//using namespace WSKey;

class guiParentWindow;
class guiRenderWindow;
class guiObjectWindow;
class PFBApplication;
class CWSLogFile;

enum CURSORTOOL
{
	MOVEVIEW = 0,
	ROTATEVIEW,
	MOVEOBJ,
	ROTATEOBJ,
	SELECTOBJ,
	CREATEOBJ,
	CLONEOBJ,
};

enum VIEWMODE
{
	TOP = 0,
	FIRSTPERSON,
	PERSPECTIVE
};

/** This Class is the entry point for the wxWidgets Application
	@remarks
	The main entry point is in OnInit().
*/
class MyApp : public wxApp
{
 private:
	// Parent Window
	guiParentWindow *m_ParentWindow;
	// Child Rendering Window
	guiRenderWindow *m_RenderWindow;
	// Child Object View Window
	guiObjectWindow *m_ObjectWindow;
	// Load Screen
	wxSplashScreen *m_LoadScreen;
	// Enable to Activate Full Features of Product
	bool m_IsRegistered;

 public:
	// OGRE Application
	static PFBApplication s_App;
	// Log File
	static CWSLogFile s_Log;
	// The Current Cursor Tool Mode
	static enum CURSORTOOL s_CursorTool;
	// The Current View Mode
	static VIEWMODE s_ViewMode;
	// Is dragging
	static bool s_IsDragging;
	// When the mouse enters the screen, but does NOT create a object
	static bool s_IsDraggingFailed;
	// License Key
	//static CWSKey s_Key;

	// Handle Initialization
	virtual bool OnInit();
	// Handle Cleanup On Exit
	virtual int OnExit();
	// Handle Idle Events (Rendering)
	void OnIdle(wxIdleEvent& event);
};


#endif // PFB_MAIN_H
