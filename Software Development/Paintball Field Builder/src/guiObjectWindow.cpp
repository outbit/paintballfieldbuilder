/**
 * ---------------------------------------------------------
 * @author: David Whiteside
 * @date: 09/20/09
 * @description: The Window That Displays Objects that can be placed on the screen
 * Copyright 2004-2009 Whiteside Solutions LLC (www.whitesidesolutions.com)
 * ---------------------------------------------------------
 */

#include "../inc/guiObjectWindow.h"


guiObjectWindow::guiObjectWindow(const wxString& title, wxWindow *parent)
       : wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(180,parent->GetClientSize().y))
{
	SetScrollbar(wxVERTICAL, 0, 16, 50);

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
	MessageBox(0, 0, 0, 0);
}

void guiObjectWindow::Layout(wxSizeEvent& WXUNUSED(event))
{
	// Resize
/*
	this->SetClientSize(180, this->GetParent()->GetSize().y);
*/
	MessageBox(0, 0, 0, 0);
}


void guiObjectWindow::OnQuit(wxCommandEvent& WXUNUSED(event))
{
  Close(true);
}

