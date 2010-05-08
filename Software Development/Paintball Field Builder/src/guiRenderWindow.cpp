#include "../inc/guiRenderWindow.h"
#include "../inc/main.h"					// Reference Main API


guiRenderWindow::guiRenderWindow(const wxString& title, wxWindow *parent)
       : wxPanel(parent, wxID_ANY, wxPoint(180, 0), wxSize(parent->GetClientSize().x-180,parent->GetClientSize().y))
{
        Connect(wxEVT_SIZE, wxSizeEventHandler(guiRenderWindow::Layout));
		Connect(wxEVT_IDLE, wxIdleEventHandler(guiRenderWindow::OnIdle));
}

guiRenderWindow::~guiRenderWindow()
{
        Disconnect(wxEVT_SIZE, wxSizeEventHandler(guiRenderWindow::Layout));
		Disconnect(wxEVT_IDLE, wxIdleEventHandler(guiRenderWindow::OnIdle));
}

void guiRenderWindow::Layout(wxSizeEvent& WXUNUSED(event))
{
        // This is getting called...but resize fails
	wxWindow *parent = this->GetParent();
        this->SetClientSize(parent->GetSize().x-180, parent->GetSize().y);
}


void guiRenderWindow::OnQuit(wxCommandEvent& WXUNUSED(event))
{
  Close(true);
}


void guiRenderWindow::OnIdle(wxIdleEvent& event)
{
	// Render Loop
//	MyApp::mApp.Render();

   event.RequestMore(true);
}
