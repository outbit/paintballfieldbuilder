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

	// Create Sizer
	if (!this->m_Sizer) {
		this->m_Sizer = new wxBoxSizer(wxVERTICAL);
		this->SetSizer(m_Sizer);
		this->SetScrollRate(5,5);
	}
}

guiObjectWindow::~guiObjectWindow()
{
	// Resize Event
	Disconnect(wxEVT_SIZE, wxSizeEventHandler(guiObjectWindow::OnSize));

	// Disconnect Bunkers
	this->DisconnectAllBunkers();
}

void guiObjectWindow::DisconnectAllBunkers()
{
		for (unsigned int x = 0; x < MyApp::s_App.mFieldKit.GetBunkerCount(); x++)
		{
			wxBitmapButton *b = MyApp::s_App.mFieldKit.GetBunker(x)->button; // Store Bunker for use later
				b->Disconnect(ID_BUTTON_HIGHEST+x, wxEVT_LEFT_DOWN, 
					wxMouseEventHandler(guiObjectWindow::OnButtonClick));
		}
}


void guiObjectWindow::OnSize(wxSizeEvent& WXUNUSED(event))
{
	// Resize Window
	wxWindow *parent = this->GetParent();
    this->SetSize(128+25, parent->GetClientSize().y);
}

void guiObjectWindow::OnDraw(wxDC& dc)
{
	// WORKS BUT MAKE BETTER MAN
	static onetime = 0;

	if (onetime == 0) {
		for (unsigned int x = 0; x < MyApp::s_App.mFieldKit.GetBunkerCount(); x++)
		{
			wxBitmapButton *b = new wxBitmapButton(this, ID_BUTTON_HIGHEST+x, *(MyApp::s_App.mFieldKit.GetBunker(x)->bmp));
			if( b ) {
				MyApp::s_App.mFieldKit.GetBunker(x)->button = b; // Store Bunker for use later
				m_Sizer->Add(b);
				// REMEMBER TO DISCONNECT LATER
				b->Connect(ID_BUTTON_HIGHEST+x, wxEVT_LEFT_DOWN, 
					wxMouseEventHandler(guiObjectWindow::OnButtonClick));
			}
		}
		this->FitInside();
		onetime=1;
	}
}


void guiObjectWindow::OnButtonClick(wxMouseEvent& event)
{
	// Button Clicked
	wxBitmapButton *button = (wxBitmapButton*)event.GetEventObject();
	Bunker *bunker = NULL;
	for (unsigned int x = 0; x < MyApp::s_App.mFieldKit.GetBunkerCount(); x++)
	{
		if ( button == MyApp::s_App.mFieldKit.GetBunker(x)->button ) {
			bunker = MyApp::s_App.mFieldKit.GetBunker(x);
			if (bunker) {
				MyApp::s_App.mBunker = x;	// Set Selected Bunker
				PFB_LOG(bunker->model_name);
				break;
			}
		}
	}

	// Drag n Drop (Source)
	if (bunker)
	{
		MyApp::s_IsDragging = true;
	}
}


void guiObjectWindow::OnQuit(wxCommandEvent& WXUNUSED(event))
{
  Close(true);
}

