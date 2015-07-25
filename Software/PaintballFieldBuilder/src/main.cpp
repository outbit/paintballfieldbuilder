/**
 * ---------------------------------------------------------
 * @author: David Whiteside
 * @date: 11/14/09
 * @description: Application Entry Point
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
enum CURSORTOOL MyApp::s_CursorTool = MOVEVIEW; // Also change the default selection toolbar, in guiParentWindow
VIEWMODE MyApp::s_ViewMode = PERSPECTIVE;
bool MyApp::s_IsDragging = false;
bool MyApp::s_IsDraggingFailed = false;
//CWSKey MyApp::s_Key;


bool MyApp::OnInit()
{
    // Splash Screen
    ::wxInitAllImageHandlers();
    wxBitmap bitmap;
    if (bitmap.LoadFile("../license/loadscreen.bmp", wxBITMAP_TYPE_BMP)) {
        m_LoadScreen = new wxSplashScreen(bitmap,
                                          wxSPLASH_CENTRE_ON_SCREEN|wxSPLASH_TIMEOUT,
                                          3000, NULL, -1, wxDefaultPosition, wxDefaultSize,
                                          wxSIMPLE_BORDER|wxSTAY_ON_TOP);
    }
    wxYield();

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
    m_ObjectWindow->SetBackgroundColour(wxColour(0x4d, 0x4d, 0x4d));
    m_ObjectWindow->Show(true);

    // Initialize OGRE
    try {
        s_App.go();
        s_App.mFieldKit.Load("../fieldkits/default.pfk");
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

    // END LOAD SCREEN
    if (m_LoadScreen) {
        m_LoadScreen->Destroy(); // Close and Free memory
    }

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
