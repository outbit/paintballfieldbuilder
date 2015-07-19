/**
 * ---------------------------------------------------------
 * @author: David Whiteside
 * @date: 07/05/10
 * @description: The Main Parent Window of EVERY other Window
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

#include "../inc/guiParentWindow.h"
#include "../inc/Common.h"				// Needed For Access to OGRE App
#include "../inc/guiNewFieldDialog.h"
#include "../inc/guiInfoDialog.h"
#include "../inc/guiRegisterDialog.h"
#include "../inc/guiViewOptionsDialog.h"
#include "../inc/guiResizeFieldDialog.h"
#include "../inc/guiObjectWindow.h"
#include "../inc/Application.h"
#include <wx/filename.h>
#include <wx/stdpaths.h>

guiParentWindow::guiParentWindow(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800,600))
{
    // Add Icon
    SetIcon(wxIconLocation(wxT("../media/gui/icon.bmp")));

    // Create MENU
    mMenubar = new wxMenuBar;

    // Create File Drop Down
    mFile = new wxMenu;
    mFile->Append(ID_FILE_OPEN, wxT("&Open"));
    mFile->Append(ID_FILE_NEW, wxT("&New"));
    mFile->Append(ID_FILE_SAVE, wxT("&Save"));
    mFile->Append(ID_FILE_SAVEAS, wxT("&Save As"));
    mFile->AppendSeparator();
    mFile->Append(ID_FILE_LOADFIELDKIT, wxT("&Load Field Kit"));
    mFile->AppendSeparator();
    mFile->Append(wxID_EXIT, wxT("&Exit"));
    mMenubar->Append(mFile, wxT("&File"));

    // Create Edit Drop Down
    mEdit = new wxMenu;
    mEdit->Append(ID_EDIT_UNDO, wxT("&Undo"));
    mEdit->Append(ID_EDIT_REDO, wxT("&Redo"));
    mEdit->AppendSeparator();
    mEdit->Append(ID_EDIT_DELETE, wxT("&Delete"));
    mEdit->Append(ID_EDIT_SELECTNONE, wxT("&Select None"));
    mEdit->AppendSeparator();
    mEdit->Append(ID_EDIT_MIRRORFIELD, wxT("&Mirror Field"));
    mEdit->Append(ID_EDIT_RESIZEFIELD, wxT("&Resize Field"));
    mMenubar->Append(mEdit, wxT("&Edit"));

    // Create View Drop Down
    mView = new wxMenu;
    mView->Append(ID_VIEW_TOP, wxT("&Top"));
    mView->Append(ID_VIEW_FIRSTPERSON, wxT("&First Person"));
    mView->Append(ID_VIEW_PERSPECTIVE, wxT("&Perspective"));
    mView->AppendSeparator();
    mView->Append(ID_VIEW_RESET, wxT("&Reset View"));
    mView->AppendSeparator();
    mView->Append(ID_VIEW_OPTIONS, wxT("&Options"));
    mMenubar->Append(mView, wxT("&View"));

    // Create Render Drop Down
    mRender = new wxMenu;
    mRender->Append(ID_RENDER_SAVESCREENSHOT, wxT("&Save ScreenShot"));
    mMenubar->Append(mRender, wxT("&Render"));

    // Create About Drop Down
    mAbout = new wxMenu;
    mAbout->Append(ID_ABOUT_HELP, wxT("&Help"));
    mAbout->AppendSeparator();
    mAbout->Append(ID_ABOUT_INFO, wxT("&Info"));
    mAbout->AppendSeparator();
    mAbout->Append(ID_ABOUT_REGISTER, wxT("&Register"));
    mMenubar->Append(mAbout, wxT("&About"));

    // Set the Menu Bar
    SetMenuBar(mMenubar);

    // Toolbar
    wxBitmap rotateview(wxT("../media/gui/rotateview.png"), wxBITMAP_TYPE_PNG);
    wxBitmap moveview(wxT("../media/gui/moveview.png"), wxBITMAP_TYPE_PNG);
    wxBitmap moveobj(wxT("../media/gui/moveobj.png"), wxBITMAP_TYPE_PNG);
    wxBitmap rotateobj(wxT("../media/gui/rotateobj.png"), wxBITMAP_TYPE_PNG);
    wxBitmap selectobj(wxT("../media/gui/selectobj.png"), wxBITMAP_TYPE_PNG);
    wxBitmap createobj(wxT("../media/gui/createobj.png"), wxBITMAP_TYPE_PNG);
    wxBitmap cloneobj(wxT("../media/gui/cloneobj.png"), wxBITMAP_TYPE_PNG);

    wxBitmap rotateview_s(wxT("../media/gui/rotateview_s.png"), wxBITMAP_TYPE_PNG);
    wxBitmap moveview_s(wxT("../media/gui/moveview_s.png"), wxBITMAP_TYPE_PNG);
    wxBitmap moveobj_s(wxT("../media/gui/moveobj_s.png"), wxBITMAP_TYPE_PNG);
    wxBitmap rotateobj_s(wxT("../media/gui/rotateobj_s.png"), wxBITMAP_TYPE_PNG);
    wxBitmap selectobj_s(wxT("../media/gui/selectobj_s.png"), wxBITMAP_TYPE_PNG);
    wxBitmap createobj_s(wxT("../media/gui/createobj_s.png"), wxBITMAP_TYPE_PNG);
    wxBitmap cloneobj_s(wxT("../media/gui/cloneobj_s.png"), wxBITMAP_TYPE_PNG);

    mToolbar = this->CreateToolBar();
    mToolbar->SetToolBitmapSize(wxSize(20,20));

    mToolbar->AddTool(ID_ROTATEVIEW, wxT(""), rotateview, rotateview_s, wxITEM_NORMAL, wxT("Rotate View"));
    mToolbar->AddTool(ID_MOVEVIEW, wxT(""), moveview, moveview_s, wxITEM_NORMAL, wxT("Move View"));
    mToolbar->AddSeparator();

    mToolbar->AddTool(ID_MOVEOBJ, wxT(""), moveobj, moveobj_s, wxITEM_NORMAL, wxT("Move Object"));
    mToolbar->AddTool(ID_ROTATEOBJ, wxT(""), rotateobj, rotateobj_s, wxITEM_NORMAL, wxT("Rotate Object"));
    mToolbar->AddTool(ID_SELECTOBJ, wxT(""), selectobj, selectobj_s, wxITEM_NORMAL, wxT("Select Object"));
    mToolbar->AddTool(ID_CREATEOBJ, wxT(""), createobj, createobj_s, wxITEM_NORMAL, wxT("Create Object"));
    mToolbar->AddTool(ID_CLONEOBJ, wxT(""), cloneobj, cloneobj_s, wxITEM_NORMAL, wxT("Clone Object"));

    // Set defaults
    mToolbar->EnableTool(ID_MOVEVIEW, false);

    // Set ToolBar
    mToolbar->Realize();

    // Event Handlers
    // File Open
    Connect(ID_FILE_OPEN, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(guiParentWindow::OnFileOpen));
    // File New
    Connect(ID_FILE_NEW, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(guiParentWindow::OnFileNew));
    // File Save
    Connect(ID_FILE_SAVE, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(guiParentWindow::OnFileSave));
    // File Save As
    Connect(ID_FILE_SAVEAS, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(guiParentWindow::OnFileSaveAs));
    // Load Field Kit
    Connect(ID_FILE_LOADFIELDKIT, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(guiParentWindow::OnLoadFieldKit));
    // Quit
    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(guiParentWindow::OnQuit));

    // Undo
    Connect(ID_EDIT_UNDO, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(guiParentWindow::OnUndo));
    // Redo
    Connect(ID_EDIT_REDO, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(guiParentWindow::OnRedo));
    // Delete
    Connect(ID_EDIT_DELETE, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(guiParentWindow::OnDelete));
    // Select None
    Connect(ID_EDIT_SELECTNONE, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(guiParentWindow::OnSelectNone));
    // Mirror Field
    Connect(ID_EDIT_MIRRORFIELD, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(guiParentWindow::OnMirrorField));
    // Resize Field
    Connect(ID_EDIT_RESIZEFIELD, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(guiParentWindow::OnResizeField));

    // Top View
    Connect(ID_VIEW_TOP, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(guiParentWindow::OnViewTop));
    // First Person
    Connect(ID_VIEW_FIRSTPERSON, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(guiParentWindow::OnViewFirstPerson));
    // Perspective
    Connect(ID_VIEW_PERSPECTIVE, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(guiParentWindow::OnViewPerspective));
    // Reset View
    Connect(ID_VIEW_RESET, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(guiParentWindow::OnViewReset));
    // View Options
    Connect(ID_VIEW_OPTIONS, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(guiParentWindow::OnViewOptions));

    // Save Screenshot
    Connect(ID_RENDER_SAVESCREENSHOT, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(guiParentWindow::OnSaveScreenshot));

    // Help
    Connect(ID_ABOUT_HELP, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(guiParentWindow::OnHelp));
    // Info
    Connect(ID_ABOUT_INFO, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(guiParentWindow::OnInfo));
    // Register
    Connect(ID_ABOUT_REGISTER, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(guiParentWindow::OnRegister));

    // Move View
    Connect(ID_MOVEVIEW, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(guiParentWindow::OnMoveView));
    // Rotate View
    Connect(ID_ROTATEVIEW, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(guiParentWindow::OnRotateView));
    // Move Object
    Connect(ID_MOVEOBJ, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(guiParentWindow::OnMoveObj));
    // Rotate Object
    Connect(ID_ROTATEOBJ, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(guiParentWindow::OnRotateObj));
    // Select Object
    Connect(ID_SELECTOBJ, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(guiParentWindow::OnSelectObj));
    // Create Object
    Connect(ID_CREATEOBJ, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(guiParentWindow::OnCreateObj));
    // Clone Object
    Connect(ID_CLONEOBJ, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(guiParentWindow::OnCloneObj));

    // Resize
    Connect(wxEVT_SIZE, wxSizeEventHandler(guiParentWindow::OnSize));

    // Key Down
    Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(guiParentWindow::OnKeyDown));

    // Center - Speak English!! ;)
    Centre();
}

guiParentWindow::~guiParentWindow()
{
    // File Open
    Disconnect(ID_FILE_OPEN, wxEVT_COMMAND_MENU_SELECTED,
               wxCommandEventHandler(guiParentWindow::OnFileOpen));

    // File New
    Disconnect(ID_FILE_NEW, wxEVT_COMMAND_MENU_SELECTED,
               wxCommandEventHandler(guiParentWindow::OnFileNew));
    // File Save
    Disconnect(ID_FILE_SAVE, wxEVT_COMMAND_MENU_SELECTED,
               wxCommandEventHandler(guiParentWindow::OnFileSave));
    // File Save As
    Disconnect(ID_FILE_SAVEAS, wxEVT_COMMAND_MENU_SELECTED,
               wxCommandEventHandler(guiParentWindow::OnFileSaveAs));
    // Load Field Kit
    Disconnect(ID_FILE_LOADFIELDKIT, wxEVT_COMMAND_MENU_SELECTED,
               wxCommandEventHandler(guiParentWindow::OnLoadFieldKit));
    // Quit
    Disconnect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,
               wxCommandEventHandler(guiParentWindow::OnQuit));

    // Undo
    Disconnect(ID_EDIT_UNDO, wxEVT_COMMAND_MENU_SELECTED,
               wxCommandEventHandler(guiParentWindow::OnUndo));
    // Redo
    Disconnect(ID_EDIT_REDO, wxEVT_COMMAND_MENU_SELECTED,
               wxCommandEventHandler(guiParentWindow::OnRedo));
    // Delete
    Disconnect(ID_EDIT_DELETE, wxEVT_COMMAND_MENU_SELECTED,
               wxCommandEventHandler(guiParentWindow::OnDelete));
    // Select None
    Disconnect(ID_EDIT_SELECTNONE, wxEVT_COMMAND_MENU_SELECTED,
               wxCommandEventHandler(guiParentWindow::OnSelectNone));
    // Mirror Field
    Disconnect(ID_EDIT_MIRRORFIELD, wxEVT_COMMAND_MENU_SELECTED,
               wxCommandEventHandler(guiParentWindow::OnMirrorField));
    // Resize Field
    Disconnect(ID_EDIT_RESIZEFIELD, wxEVT_COMMAND_MENU_SELECTED,
               wxCommandEventHandler(guiParentWindow::OnResizeField));

    // Top View
    Disconnect(ID_VIEW_TOP, wxEVT_COMMAND_MENU_SELECTED,
               wxCommandEventHandler(guiParentWindow::OnViewTop));
    // First Person
    Disconnect(ID_VIEW_FIRSTPERSON, wxEVT_COMMAND_MENU_SELECTED,
               wxCommandEventHandler(guiParentWindow::OnViewFirstPerson));
    // Perspective
    Disconnect(ID_VIEW_PERSPECTIVE, wxEVT_COMMAND_MENU_SELECTED,
               wxCommandEventHandler(guiParentWindow::OnViewPerspective));
    // Reset View
    Disconnect(ID_VIEW_RESET, wxEVT_COMMAND_MENU_SELECTED,
               wxCommandEventHandler(guiParentWindow::OnViewReset));
    // View Options
    Disconnect(ID_VIEW_OPTIONS, wxEVT_COMMAND_MENU_SELECTED,
               wxCommandEventHandler(guiParentWindow::OnViewOptions));

    // Save Screenshot
    Disconnect(ID_RENDER_SAVESCREENSHOT, wxEVT_COMMAND_MENU_SELECTED,
               wxCommandEventHandler(guiParentWindow::OnSaveScreenshot));

    // Help
    Disconnect(ID_ABOUT_HELP, wxEVT_COMMAND_MENU_SELECTED,
               wxCommandEventHandler(guiParentWindow::OnHelp));
    // Info
    Disconnect(ID_ABOUT_INFO, wxEVT_COMMAND_MENU_SELECTED,
               wxCommandEventHandler(guiParentWindow::OnInfo));
    // Register
    Disconnect(ID_ABOUT_REGISTER, wxEVT_COMMAND_MENU_SELECTED,
               wxCommandEventHandler(guiParentWindow::OnRegister));

    // Move View
    Disconnect(ID_MOVEVIEW, wxEVT_COMMAND_MENU_SELECTED,
               wxCommandEventHandler(guiParentWindow::OnMoveView));
    // Rotate View
    Disconnect(ID_ROTATEVIEW, wxEVT_COMMAND_MENU_SELECTED,
               wxCommandEventHandler(guiParentWindow::OnRotateView));
    // Move Object
    Disconnect(ID_MOVEOBJ, wxEVT_COMMAND_MENU_SELECTED,
               wxCommandEventHandler(guiParentWindow::OnMoveObj));
    // Rotate Object
    Disconnect(ID_ROTATEOBJ, wxEVT_COMMAND_MENU_SELECTED,
               wxCommandEventHandler(guiParentWindow::OnRotateObj));
    // Select Object
    Disconnect(ID_SELECTOBJ, wxEVT_COMMAND_MENU_SELECTED,
               wxCommandEventHandler(guiParentWindow::OnSelectObj));
    // Create Object
    Disconnect(ID_CREATEOBJ, wxEVT_COMMAND_MENU_SELECTED,
               wxCommandEventHandler(guiParentWindow::OnCreateObj));
    // Clone Object
    Disconnect(ID_CLONEOBJ, wxEVT_COMMAND_MENU_SELECTED,
               wxCommandEventHandler(guiParentWindow::OnCloneObj));

    // Resize
    Disconnect(wxEVT_SIZE, wxSizeEventHandler(guiParentWindow::OnSize));

    // Key Down
    Disconnect(wxEVT_KEY_DOWN, wxKeyEventHandler(guiParentWindow::OnKeyDown));
    Disconnect(wxEVT_KEY_UP, wxKeyEventHandler(guiParentWindow::OnKeyUp));
}

void guiParentWindow::EnableLastToolbar()
{
    int old_tool_id = 0;
    int val = (int)(MyApp::s_CursorTool);
    if (val == ROTATEVIEW) old_tool_id = ID_ROTATEVIEW;
    if (val == MOVEVIEW) old_tool_id = ID_MOVEVIEW;
    if (val == MOVEOBJ) old_tool_id = ID_MOVEOBJ;
    if (val == ROTATEOBJ) old_tool_id = ID_ROTATEOBJ;
    if (val == SELECTOBJ) old_tool_id = ID_SELECTOBJ;
    if (val == CREATEOBJ) old_tool_id = ID_CREATEOBJ;
    if (val == CLONEOBJ) old_tool_id = ID_CLONEOBJ;

    if (old_tool_id != 0) {
        mToolbar->EnableTool(old_tool_id, true);
    }
}

void guiParentWindow::OnSize(wxSizeEvent& WXUNUSED(event))
{
    // Update Children Windows during a resize
    wxList child_list = this->GetChildren();
    wxNode *node = child_list.GetFirst();
    while (node) {
        wxWindow *win = (wxWindow*)node->GetData();
        wxSizeEvent event;
        event.SetEventObject(win);
        win->GetEventHandler()->ProcessEvent(event);

        // Go to next node
        node = node->GetNext();
    }
}

void guiParentWindow::OnFileNew(wxCommandEvent& event)
{
    // Dialog
    wxDialog *window = new guiNewFieldDialog(this);
    window->Show(true);
    window->SetAutoLayout(true);
}

void guiParentWindow::OnFileOpen(wxCommandEvent& event)
{
    wxFileDialog *openFileDialog =
        new wxFileDialog( this, _("Open file"), wxStandardPaths::Get().GetExecutablePath(), "", "*.field",
                          wxOPEN, wxDefaultPosition);

    if ( openFileDialog->ShowModal() == wxID_OK ) {
        wxString path;
        path.append( openFileDialog->GetDirectory() );
        path.append( wxFileName::GetPathSeparator() );
        path.append( openFileDialog->GetFilename() );
        MyApp::s_App.LoadField(path.c_str());
    }
}

void guiParentWindow::OnFileSave(wxCommandEvent& event)
{
    if ( false == MyApp::s_App.SaveField() ) {
        this->OnFileSaveAs(event);
    }
}

void guiParentWindow::OnFileSaveAs(wxCommandEvent& event)
{
    wxFileDialog *openFileDialog =
        new wxFileDialog( this, _("Save file"), wxStandardPaths::Get().GetExecutablePath(),
                          "", "*.field", wxSAVE, wxDefaultPosition);

    if ( openFileDialog->ShowModal() == wxID_OK ) {
        wxString path;
        path.append( openFileDialog->GetDirectory() );
        path.append( wxFileName::GetPathSeparator() );
        path.append( openFileDialog->GetFilename() );
        MyApp::s_App.SaveField(path.c_str());
    }
}

void guiParentWindow::OnLoadFieldKit(wxCommandEvent& event)
{
    wxFileDialog *openFileDialog =
        new wxFileDialog( this, _("Open file"), wxStandardPaths::Get().GetExecutablePath(),
                          "", "*.pfk", wxOPEN, wxDefaultPosition);

    if ( openFileDialog->ShowModal() == wxID_OK ) {
        wxString path;
        path.append( openFileDialog->GetDirectory() );
        path.append( wxFileName::GetPathSeparator() );
        path.append( openFileDialog->GetFilename() );
        MyApp::s_App.mFieldKit.Load(path.c_str());
        // Redraw the Object Window
        guiObjectWindow::s_Redraw = true;
    }
}

void guiParentWindow::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void guiParentWindow::OnUndo(wxCommandEvent& event)
{
    // UNDO
    MyApp::s_App.Undo();
}

void guiParentWindow::OnRedo(wxCommandEvent& event)
{
    // REDO
    MyApp::s_App.Redo();
}

void guiParentWindow::OnDelete(wxCommandEvent& event)
{
    // Undo/Redo Delete
    MyApp::s_App.AddURSpotSelectedObj(UR_DELETE);
    MyApp::s_App.DeleteSelectedObj();
}

void guiParentWindow::OnSelectNone(wxCommandEvent& event)
{
    MyApp::s_App.SelectNone();
}
void guiParentWindow::OnMirrorField(wxCommandEvent& event)
{
    if ( false == MyApp::s_App.MirrorBunkers() ) {
        wxMessageBox("Mirror Failed, All the bunkers must only be on one side of the 50 yard line.");
    }
}

void guiParentWindow::OnResizeField(wxCommandEvent& event)
{
    wxDialog *window = new guiResizeFieldDialog(this);
    window->Show(true);
    window->SetAutoLayout(true);
}

void guiParentWindow::OnViewTop(wxCommandEvent& event)
{
    MyApp::s_App.mViewMode = MyApp::s_ViewMode = TOP;
    MyApp::s_App.LookTop();
}

void guiParentWindow::OnViewFirstPerson(wxCommandEvent& event)
{
    MyApp::s_App.mViewMode = MyApp::s_ViewMode = FIRSTPERSON;
    MyApp::s_App.LookFirstPerson();
}

void guiParentWindow::OnViewPerspective(wxCommandEvent& event)
{
    MyApp::s_App.mViewMode = MyApp::s_ViewMode = PERSPECTIVE;
    MyApp::s_App.LookPerspective();
}

void guiParentWindow::OnViewReset(wxCommandEvent& event)
{
    MyApp::s_App.ResetView();
}

void guiParentWindow::OnViewOptions(wxCommandEvent& event)
{
    // Dialog
    wxDialog *window = new guiViewOptionsDialog(this);
    window->Show(true);
    window->SetAutoLayout(true);
}

void guiParentWindow::OnSaveScreenshot(wxCommandEvent& event)
{
    wxFileDialog *openFileDialog =
        new wxFileDialog( this, _("Save Screenshot"), wxStandardPaths::Get().GetExecutablePath(),
                          "", "*.bmp", wxSAVE, wxDefaultPosition);

    if ( openFileDialog->ShowModal() == wxID_OK ) {
        wxString path;
        path.append( openFileDialog->GetDirectory() );
        path.append( wxFileName::GetPathSeparator() );
        path.append( openFileDialog->GetFilename() );
        if (!path.CmpNoCase(".bmp")) {
            path.append(".bmp");
        }
        MyApp::s_App.TakeScreenShot(path.c_str());
    }
}

void guiParentWindow::OnHelp(wxCommandEvent& WXUNUSED(event))
{
    // Open Web Browser To Paintball Field Builder Online Help
    wxLaunchDefaultBrowser(wxString("http://paintballfieldbuilder.com/documentation"));
}

void guiParentWindow::OnInfo(wxCommandEvent& WXUNUSED(event))
{
    // Dialog
    wxDialog *window = new guiInfoDialog(this);
    window->Show(true);
    window->SetAutoLayout(true);
}

void guiParentWindow::OnRegister(wxCommandEvent& WXUNUSED(event))
{
    // Dialog
    wxDialog *window = new guiRegisterDialog(this);
    window->Show(true);
    window->SetAutoLayout(true);
}

void guiParentWindow::OnMoveView(wxCommandEvent& event)
{
    this->EnableLastToolbar();
    MyApp::s_CursorTool = MOVEVIEW;
    mToolbar->EnableTool(ID_MOVEVIEW, false);
}

void guiParentWindow::OnRotateView(wxCommandEvent& event)
{
    this->EnableLastToolbar();
    MyApp::s_CursorTool = ROTATEVIEW;
    mToolbar->EnableTool(ID_ROTATEVIEW, false);
}

void guiParentWindow::OnMoveObj(wxCommandEvent& event)
{
    this->EnableLastToolbar();
    MyApp::s_CursorTool = MOVEOBJ;
    mToolbar->EnableTool(ID_MOVEOBJ, false);
}

void guiParentWindow::OnRotateObj(wxCommandEvent& event)
{
    this->EnableLastToolbar();
    MyApp::s_CursorTool = ROTATEOBJ;
    mToolbar->EnableTool(ID_ROTATEOBJ, false);
}

void guiParentWindow::OnSelectObj(wxCommandEvent& event)
{
    this->EnableLastToolbar();
    MyApp::s_CursorTool = SELECTOBJ;
    mToolbar->EnableTool(ID_SELECTOBJ, false);
}

void guiParentWindow::OnCreateObj(wxCommandEvent& event)
{
    this->EnableLastToolbar();
    MyApp::s_CursorTool = CREATEOBJ;
    mToolbar->EnableTool(ID_CREATEOBJ, false);
}

void guiParentWindow::OnCloneObj(wxCommandEvent& event)
{
    this->EnableLastToolbar();
    MyApp::s_CursorTool = CLONEOBJ;
    mToolbar->EnableTool(ID_CLONEOBJ, false);
}

void guiParentWindow::OnKeyDown(wxKeyEvent& event)
{
    int val = event.GetKeyCode();
    switch (val) {
    case WXK_F4:
        // alt+f4
        if (event.AltDown()) {
            this->Close(true);
        }
        break;

    case WXK_DELETE:
        PFB_LOG("wxk_delete");
        // Undo/Redo Delete
        MyApp::s_App.AddURSpotSelectedObj(UR_DELETE);
        MyApp::s_App.DeleteSelectedObj();
        break;

    case WXK_NUMPAD_DELETE:
        PFB_LOG("wxk_numpad_delete");
        // Undo/Redo Delete
        MyApp::s_App.AddURSpotSelectedObj(UR_DELETE);
        MyApp::s_App.DeleteSelectedObj();
        break;

        // DELETE KEY - BUG in wxWidgets for WIN32
    case 8:
        PFB_LOG("wxk_8bug_delete");
        // Undo/Redo Delete
        MyApp::s_App.AddURSpotSelectedObj(UR_DELETE);
        MyApp::s_App.DeleteSelectedObj();
        break;

    case WXK_LEFT:
        MyApp::s_App.RotateSelectedObj(-5.0f, 0);
        break;

    case WXK_RIGHT:
        MyApp::s_App.RotateSelectedObj(5.0f, 0);
        break;

    case WXK_UP:
        // Toggle bunker position
        break;

    case WXK_DOWN:
        // Toggle bunker position
        break;

    default:
        // Debug Key Codes
        /*
        wxString str = wxString::Format(wxT("key code: %i"), val);
        std::string stlstring = std::string(str.mb_str());
        PFB_LOG(stlstring.c_str());*/
        break;
    }
}

void guiParentWindow::OnKeyUp(wxKeyEvent& event)
{
    int val = event.GetKeyCode();
    switch (val) {
    case WXK_DELETE:
        break;
    case WXK_NUMPAD_DELETE:
        break;
        // DELETE KEY - BUG in wxWidgets for WIN32
    case 8:
        break;

    case WXK_LEFT:
        // How do i check this was down before??
        // Undo/Redo
        //MyApp::s_App.AddURSpotSelectedObj(UR_CHANGE);
        break;

    case WXK_RIGHT:
        // how do i check this was down before??
        // Undo/Redo
        //MyApp::s_App.AddURSpotSelectedObj(UR_CHANGE);
        break;

    case WXK_UP:
        break;

    case WXK_DOWN:
        break;

    default:
        // Debug Key Codes
        /*
        wxString str = wxString::Format(wxT("key code: %i"), val);
        std::string stlstring = std::string(str.mb_str());
        PFB_LOG(stlstring.c_str());*/
        break;
    }
}