/**
 * ---------------------------------------------------------
 * @author: David Whiteside
 * @date: 09/20/09
 * @description: Main Entry Point Of Applicaiton
 * Copyright (c) 2015 David Whiteside
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
