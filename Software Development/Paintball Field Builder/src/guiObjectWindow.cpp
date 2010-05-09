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

guiObjectWindow::guiObjectWindow(const wxString& title, wxWindow *parent)
       : wxScrolledWindow(parent, wxID_ANY, wxPoint(0, 0), wxSize(128+25,parent->GetClientSize().y))
{
	// Resize Event
	Connect(wxEVT_SIZE, wxSizeEventHandler(guiObjectWindow::Layout));
}

guiObjectWindow::~guiObjectWindow()
{
	// Resize Event
	Disconnect(wxEVT_SIZE, wxSizeEventHandler(guiObjectWindow::Layout));
}


void guiObjectWindow::OnSize()
{
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
		wxBitmapButton *b = new wxBitmapButton(this, wxID_ANY, *(MyApp::s_App.mFieldKit.GetBunker(x)->bmp));
		sizer->Add(b);
	}
	this->SetSizer(sizer);
	this->FitInside();
	this->SetScrollRate(5,5);
	onetime=1;
}
}

void guiObjectWindow::Layout(wxSizeEvent& WXUNUSED(event))
{
	// Resize
/*
	this->SetClientSize(180, this->GetParent()->GetSize().y);
*/
}


void guiObjectWindow::OnQuit(wxCommandEvent& WXUNUSED(event))
{
  Close(true);
}

