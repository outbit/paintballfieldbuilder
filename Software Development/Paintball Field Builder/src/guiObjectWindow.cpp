/**
 * ---------------------------------------------------------
 * @author: David Whiteside
 * @date: 09/20/09
 * @description: The Window That Displays Objects that can be placed on the screen
 * Copyright 2004-2009 Whiteside Solutions LLC (www.whitesidesolutions.com)
 * ---------------------------------------------------------
 */

#include "../inc/guiObjectWindow.h"
#include "../inc/Common.h"				// Needed For Access to OGRE App
#include "../inc/Application.h"

#define OBJECT_SPACING 15
#define ID_BUTTON_HIGHEST 1000

guiObjectWindow::guiObjectWindow(const wxString& title, wxWindow *parent)
       : wxScrolledWindow(parent, wxID_ANY, wxPoint(0, 0), wxSize(128+25,parent->GetClientSize().y))
{
	// Resize Event
	Connect(wxEVT_SIZE, wxSizeEventHandler(guiObjectWindow::OnSize));
}

guiObjectWindow::~guiObjectWindow()
{
	// Resize Event
	Disconnect(wxEVT_SIZE, wxSizeEventHandler(guiObjectWindow::OnSize));
}


void guiObjectWindow::OnSize(wxSizeEvent& WXUNUSED(event))
{
	// Resize Window
	wxWindow *parent = this->GetParent();
    this->SetSize(128+25, parent->GetClientSize().y);
}

void guiObjectWindow::OnDraw(wxDC& dc)
{
	/*
	wxBitmap *tmp = 0;
	int count =0;
	for (unsigned int x = 0; x < MyApp::s_App.mFieldKit.GetBunkerCount(); x++)
	{
		tmp = MyApp::s_App.mFieldKit.GetBunker(x)->bmp;
		dc.DrawBitmap(*tmp, 0, (128+OBJECT_SPACING)*count, false);
		count++;
	}
	*/
	// WORKS BUT MAKE BETTER MAN
	static onetime = 0;

	if (onetime == 0) {
		wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

		for (unsigned int x = 0; x < MyApp::s_App.mFieldKit.GetBunkerCount(); x++)
		{
			wxBitmapButton *b = new wxBitmapButton(this, ID_BUTTON_HIGHEST+x, *(MyApp::s_App.mFieldKit.GetBunker(x)->bmp));
			if( b ) {
				MyApp::s_App.mFieldKit.GetBunker(x)->button = b; // Store Bunker for use later
				sizer->Add(b);
				Connect(ID_BUTTON_HIGHEST+x, wxEVT_COMMAND_BUTTON_CLICKED, 
					wxCommandEventHandler(guiObjectWindow::OnButtonClick));
			}
		}
		this->SetSizer(sizer);
		this->FitInside();
		this->SetScrollRate(5,5);
		onetime=1;
	}
}


void guiObjectWindow::OnButtonClick(wxCommandEvent& event)
{
	// Button Clicked
	wxBitmapButton *button = (wxBitmapButton*)event.GetEventObject();
	for (unsigned int x = 0; x < MyApp::s_App.mFieldKit.GetBunkerCount(); x++)
	{
		if ( button == MyApp::s_App.mFieldKit.GetBunker(x)->button ) {
			Bunker *bunker = MyApp::s_App.mFieldKit.GetBunker(x);
			if (bunker) {
				MyApp::s_App.mBunker = x;	// Set Selected Bunker
				PFB_LOG(bunker->model_name);
			}
		}
	}
	PFB_LOG("test click");
}


void guiObjectWindow::OnQuit(wxCommandEvent& WXUNUSED(event))
{
  Close(true);
}

