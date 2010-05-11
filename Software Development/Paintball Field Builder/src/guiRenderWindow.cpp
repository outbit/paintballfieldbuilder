#include "../inc/guiRenderWindow.h"
#include "../inc/Application.h"


guiRenderWindow::guiRenderWindow(const wxString& title, wxWindow *parent)
       : wxPanel(parent, wxID_ANY, wxPoint(128+25, 0), wxSize(parent->GetClientSize().x-(128+25),parent->GetClientSize().y))
{
        Connect(wxEVT_SIZE, wxSizeEventHandler(guiRenderWindow::Layout));
		Connect(wxEVT_IDLE, wxIdleEventHandler(guiRenderWindow::OnIdle));

		Connect(wxEVT_LEFT_UP, wxMouseEventHandler(guiRenderWindow::OnLeftUp));
		Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(guiRenderWindow::OnLeftDown));
		Connect(wxEVT_LEFT_DCLICK, wxMouseEventHandler(guiRenderWindow::OnLeftDClick));

		Connect(wxEVT_RIGHT_UP, wxMouseEventHandler(guiRenderWindow::OnRightUp));
		Connect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(guiRenderWindow::OnRightDown));
		Connect(wxEVT_RIGHT_DCLICK, wxMouseEventHandler(guiRenderWindow::OnRightDClick));

		Connect(wxEVT_MOTION, wxMouseEventHandler(guiRenderWindow::OnMouseMotion));
		Connect(wxEVT_MOUSEWHEEL, wxMouseEventHandler(guiRenderWindow::OnMouseWheel));

		Connect(wxEVT_ENTER_WINDOW, wxMouseEventHandler(guiRenderWindow::OnEnterWindow));
		Connect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(guiRenderWindow::OnLeaveWindow));
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
        this->SetClientSize(parent->GetSize().x-(128+25), parent->GetSize().y);
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

void guiRenderWindow::OnLeftUp(wxMouseEvent& event) {
}

void guiRenderWindow::OnLeftDown(wxMouseEvent& event) {
	// Button JUST changed to down
	if ( event.RightDown() ) {
		switch ( MyApp::s_CursorTool ) {
			case CREATEOBJ:
				MyApp::s_App.CreateObject(event.GetX(), event.GetY());
			break;
		}
	}
}

void guiRenderWindow::OnLeftDClick(wxMouseEvent& event) {
}

void guiRenderWindow::OnRightUp(wxMouseEvent& event) {
}

void guiRenderWindow::OnRightDown(wxMouseEvent& event) {
}

void guiRenderWindow::OnRightDClick(wxMouseEvent& event) {
}

void guiRenderWindow::OnMouseMotion(wxMouseEvent& event) {
static wxPoint last_mouse_pos(event.GetPosition());

	// Right mouse button is held down
	if ( event.LeftIsDown() ) {
		switch ( MyApp::s_CursorTool ) {
			case MOVEVIEW: {
				wxPoint p = event.GetPosition();
				MyApp::s_App.MoveView(p.x-last_mouse_pos.x, p.y-last_mouse_pos.y);
				last_mouse_pos = p;
			}break;

			case ROTATEVIEW: {
				wxPoint p = event.GetPosition();
				MyApp::s_App.RotateView(p.x-last_mouse_pos.x, p.y-last_mouse_pos.y);
				last_mouse_pos = p;
			}break;

			case MOVEOBJ:
			break;

			case ROTATEOBJ:
			break;

			case SELECTOBJ:
			break;

			case CREATEOBJ:
			break;

			case CLONEOBJ:
			break;
		}
	}
}

void guiRenderWindow::OnMouseWheel(wxMouseEvent& event) {
}

void guiRenderWindow::OnEnterWindow(wxMouseEvent& event) {
}

void guiRenderWindow::OnLeaveWindow(wxMouseEvent& event) {
}