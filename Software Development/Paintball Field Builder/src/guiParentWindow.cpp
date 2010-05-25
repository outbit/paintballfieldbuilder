/**
 * ---------------------------------------------------------
 * @author: David Whiteside
 * @date: 09/20/09
 * @description: The Main Parent Window of EVERY other Window
 * Copyright 2004-2009 Whiteside Solutions LLC (www.whitesidesolutions.com)
 * ---------------------------------------------------------
 */

#include "../inc/guiParentWindow.h"
#include "../inc/Common.h"				// Needed For Access to OGRE App
#include "../inc/guiNewFieldDialog.h"
#include "../inc/guiInfoDialog.h"
#include "../inc/guiRegisterDialog.h"
#include "../inc/guiViewOptionsDialog.h"
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
	wxIcon rotateview(wxIconLocation(wxT("../media/gui/rotateview.bmp")));
	wxIcon moveview(wxIconLocation(wxT("../media/gui/moveview.bmp")));
	wxIcon moveobj(wxIconLocation(wxT("../media/gui/moveobj.bmp")));
	wxIcon rotateobj(wxIconLocation(wxT("../media/gui/rotateobj.bmp")));
	wxIcon selectobj(wxIconLocation(wxT("../media/gui/selectobj.bmp")));
	wxIcon createobj(wxIconLocation(wxT("../media/gui/createobj.bmp")));
	wxIcon cloneobj(wxIconLocation(wxT("../media/gui/cloneobj.bmp")));

	wxToolBar *mToolbar = this->CreateToolBar();

	mToolbar->AddTool(ID_ROTATEVIEW, rotateview, wxT("Rotate View"));
	mToolbar->AddTool(ID_MOVEVIEW, moveview, wxT("Move View"));
	mToolbar->AddSeparator();
	
	mToolbar->AddTool(ID_MOVEOBJ, moveobj, wxT("Move Object"));
	mToolbar->AddTool(ID_ROTATEOBJ, rotateobj, wxT("Rotate Object"));
	mToolbar->AddTool(ID_SELECTOBJ, selectobj, wxT("Select Object"));
	mToolbar->AddTool(ID_CREATEOBJ, createobj, wxT("Create Object"));
	mToolbar->AddTool(ID_CLONEOBJ, cloneobj, wxT("Clone Object"));

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
	// Create Object
	Connect(ID_CREATEOBJ, wxEVT_COMMAND_MENU_SELECTED, 
		wxCommandEventHandler(guiParentWindow::OnCreateObj));
	// Clone Object
	Connect(ID_CLONEOBJ, wxEVT_COMMAND_MENU_SELECTED, 
		wxCommandEventHandler(guiParentWindow::OnCloneObj));

	 // Resize
	Connect(wxEVT_SIZE, wxSizeEventHandler(guiParentWindow::Layout));
	
	// Center - Speak English!! ;)
	Centre();
}

guiParentWindow::~guiParentWindow()
{
	 // Resize
	Disconnect(wxEVT_SIZE, wxSizeEventHandler(guiParentWindow::Layout));
}

void guiParentWindow::Layout(wxSizeEvent& WXUNUSED(event))
{
	// Handle Resize
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
 
	if ( openFileDialog->ShowModal() == wxID_OK )
	{
		wxString path;
		path.append( openFileDialog->GetDirectory() );
		path.append( wxFileName::GetPathSeparator() );
		path.append( openFileDialog->GetFilename() );
		MyApp::s_App.LoadField(path.c_str());
	}
}

void guiParentWindow::OnFileSave(wxCommandEvent& event)
{
	MyApp::s_App.SaveField();
}

void guiParentWindow::OnFileSaveAs(wxCommandEvent& event)
{
wxFileDialog *openFileDialog =
		new wxFileDialog( this, _("Save file"), wxStandardPaths::Get().GetExecutablePath(),
							"", "*.field", wxSAVE, wxDefaultPosition);
 
	if ( openFileDialog->ShowModal() == wxID_OK )
	{
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
 
	if ( openFileDialog->ShowModal() == wxID_OK )
	{
		wxString path;
		path.append( openFileDialog->GetDirectory() );
		path.append( wxFileName::GetPathSeparator() );
		path.append( openFileDialog->GetFilename() );
		// DONT FORGET TO REDRAW THE MENU
		MyApp::s_App.mFieldKit.Load(path.c_str());
	}
}

void guiParentWindow::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	Close(true);
}

void guiParentWindow::OnUndo(wxCommandEvent& event)
{
	// UNDO
}

void guiParentWindow::OnRedo(wxCommandEvent& event)
{
	// REDO
}

void guiParentWindow::OnDelete(wxCommandEvent& event)
{
	MyApp::s_App.DeleteSelectedObj();
}

void guiParentWindow::OnSelectNone(wxCommandEvent& event)
{
	MyApp::s_App.SelectNone();
}
void guiParentWindow::OnMirrorField(wxCommandEvent& event)
{
	MyApp::s_App.MirrorBunkers();
}

void guiParentWindow::OnResizeField(wxCommandEvent& event)
{
	// Grap stuff and resize
}

void guiParentWindow::OnViewTop(wxCommandEvent& event)
{
	MyApp::s_ViewMode = TOP;
	MyApp::s_App.LookTop();
}

void guiParentWindow::OnViewFirstPerson(wxCommandEvent& event)
{
	MyApp::s_ViewMode = FIRSTPERSON;
	MyApp::s_App.LookFirstPerson();
}

void guiParentWindow::OnViewPerspective(wxCommandEvent& event)
{
	MyApp::s_ViewMode = PERSPECTIVE;
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
	MyApp::s_CursorTool = MOVEVIEW; 
}

void guiParentWindow::OnRotateView(wxCommandEvent& event)
{
	MyApp::s_CursorTool = ROTATEVIEW; 
}

void guiParentWindow::OnMoveObj(wxCommandEvent& event)
{
	MyApp::s_CursorTool = MOVEOBJ; 
}

void guiParentWindow::OnRotateObj(wxCommandEvent& event)
{
	MyApp::s_CursorTool = ROTATEOBJ; 
}

void guiParentWindow::OnCreateObj(wxCommandEvent& event)
{
	MyApp::s_CursorTool = CREATEOBJ; 
}

void guiParentWindow::OnCloneObj(wxCommandEvent& event)
{
	MyApp::s_CursorTool = CLONEOBJ; 
}
