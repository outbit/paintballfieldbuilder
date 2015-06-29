#include "../inc/guiRenderWindow.h"
#include "../inc/Application.h"


guiRenderWindow::guiRenderWindow(const wxString& title, wxWindow *parent)
    : wxPanel(parent, wxID_ANY, wxPoint(128+25, 0), wxSize(parent->GetClientSize().x-(128+25),parent->GetClientSize().y))
{
    Connect(wxEVT_SIZE, wxSizeEventHandler(guiRenderWindow::OnSize));
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
    Disconnect(wxEVT_SIZE, wxSizeEventHandler(guiRenderWindow::OnSize));
    Disconnect(wxEVT_IDLE, wxIdleEventHandler(guiRenderWindow::OnIdle));

    Disconnect(wxEVT_LEFT_UP, wxMouseEventHandler(guiRenderWindow::OnLeftUp));
    Disconnect(wxEVT_LEFT_DOWN, wxMouseEventHandler(guiRenderWindow::OnLeftDown));
    Disconnect(wxEVT_LEFT_DCLICK, wxMouseEventHandler(guiRenderWindow::OnLeftDClick));

    Disconnect(wxEVT_RIGHT_UP, wxMouseEventHandler(guiRenderWindow::OnRightUp));
    Disconnect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(guiRenderWindow::OnRightDown));
    Disconnect(wxEVT_RIGHT_DCLICK, wxMouseEventHandler(guiRenderWindow::OnRightDClick));

    Disconnect(wxEVT_MOTION, wxMouseEventHandler(guiRenderWindow::OnMouseMotion));
    Disconnect(wxEVT_MOUSEWHEEL, wxMouseEventHandler(guiRenderWindow::OnMouseWheel));

    Disconnect(wxEVT_ENTER_WINDOW, wxMouseEventHandler(guiRenderWindow::OnEnterWindow));
    Disconnect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(guiRenderWindow::OnLeaveWindow));
}

void guiRenderWindow::OnSize(wxSizeEvent& WXUNUSED(event))
{
    // Resize Window
    wxWindow *parent = this->GetParent();
    this->SetClientSize(parent->GetClientSize().x-(128+25), parent->GetClientSize().y);
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

void guiRenderWindow::OnLeftUp(wxMouseEvent& event)
{

    // If Dragging then Release (Drag n Drop)
    if (MyApp::s_IsDragging == true) {
        MyApp::s_IsDragging = false;
    }
}

void guiRenderWindow::OnLeftDown(wxMouseEvent& event)
{
    // Button JUST changed to down
    wxPoint p = event.GetPosition();
    Real x_pos = (Real)p.x/(Real)this->GetSize().x;
    Real y_pos = (Real)p.y/(Real)this->GetSize().y;

    switch ( MyApp::s_CursorTool ) {

    case MOVEOBJ:
        MyApp::s_App.SelectObject(x_pos, y_pos);
        break;

    case ROTATEOBJ:
        MyApp::s_App.SelectObject(x_pos, y_pos);
        break;

    case SELECTOBJ:
        MyApp::s_App.SelectObject(x_pos, y_pos);
        break;

    case CREATEOBJ:
        MyApp::s_App.CreateObject(x_pos, y_pos);
        // Undo/Redo Create
        MyApp::s_App.AddURSpotSelectedObj(UR_CREATE);
        break;

    case CLONEOBJ:
        MyApp::s_App.SelectObject(x_pos, y_pos);
        MyApp::s_App.CloneSelectedObj();
        // Undo/Redo Create
        MyApp::s_App.AddURSpotSelectedObj(UR_CREATE);
        break;
    }
}

void guiRenderWindow::OnLeftDClick(wxMouseEvent& event)
{
}

void guiRenderWindow::OnRightUp(wxMouseEvent& event)
{
}

void guiRenderWindow::OnRightDown(wxMouseEvent& event)
{
}

void guiRenderWindow::OnRightDClick(wxMouseEvent& event)
{
}

void guiRenderWindow::OnMouseMotion(wxMouseEvent& event)
{
    static wxPoint last_mouse_pos(event.GetPosition());
    static bool last_leftdown = false;

    // Left mouse button is held down
    if ( event.LeftIsDown() ) {
        last_leftdown = true;
        wxPoint p = event.GetPosition();
        float x_force = PFB_max((float)p.x-(float)last_mouse_pos.x, MAX_MOUSEFORCE);
        float y_force = PFB_max((float)p.y-(float)last_mouse_pos.y, MAX_MOUSEFORCE);
        Real x_pos = (Real)p.x/(Real)this->GetSize().x;
        Real y_pos = (Real)p.y/(Real)this->GetSize().y;

        if ( MyApp::s_IsDragging == true ) {
            // Drag N Drop
            if ( false == MyApp::s_IsDraggingFailed ) {
                // If it did not fail, then move the bunker that was created
                MyApp::s_App.MoveSelectedObj(x_pos, y_pos);
            } else {
                PFB_LOG("render - TRYING creating drag object again...");
                //If the first drag and create bunker failed, try again
                if ( 1 == MyApp::s_App.CreateObject(x_pos, y_pos) ) {
                    MyApp::s_IsDraggingFailed = false;
                    // Undo/Redo Create
                    MyApp::s_App.AddURSpotSelectedObj(UR_CREATE);
                }
            }
        } else {
            switch ( MyApp::s_CursorTool ) {

            case MOVEVIEW: {
                MyApp::s_App.MoveView(x_force, y_force);
            }
            break;

            case ROTATEVIEW: {
                PFB_LOG("render - rotating");
                MyApp::s_App.RotateView(x_force, y_force);
            }
            break;

            case MOVEOBJ:
                MyApp::s_App.MoveSelectedObj(x_pos, y_pos);
                break;

            case ROTATEOBJ:
                MyApp::s_App.RotateSelectedObj(x_force, y_force);
                break;

            case SELECTOBJ:
                // No dragging, just selecting
                break;

            case CREATEOBJ:
                // no dragging, just creating
                break;

            case CLONEOBJ:
                MyApp::s_App.MoveSelectedObj(x_pos, y_pos);
                break;
            }
        }

        // Store last mouse position for FORCE value
        last_mouse_pos = p;

    } else { // Mouse Released and moved
        // Mouse First Released
        if (last_leftdown == true) {
            last_leftdown = false;

            switch ( MyApp::s_CursorTool ) {
            case MOVEVIEW: {
            } break;
            case ROTATEVIEW: {
            } break;

            case MOVEOBJ:
                // Undo/Redo
                MyApp::s_App.AddURSpotSelectedObj(UR_CHANGE);
                break;

            case ROTATEOBJ:
                // Undo/Redo
                MyApp::s_App.AddURSpotSelectedObj(UR_CHANGE);
                break;

            case SELECTOBJ:
                // No dragging, just selecting
                break;

            case CREATEOBJ:
                // no dragging, just creating
                break;

            case CLONEOBJ:
                // Undo/Redo
                MyApp::s_App.AddURSpotSelectedObj(UR_CHANGE);
                break;
            }
        }
        last_mouse_pos.x = 0;
        last_mouse_pos.y = 0;
    }
}

void guiRenderWindow::OnMouseWheel(wxMouseEvent& event)
{
}

void guiRenderWindow::OnEnterWindow(wxMouseEvent& event)
{
    wxPoint p = event.GetPosition();
    Real x_pos = (Real)p.x/(Real)this->GetSize().x;
    Real y_pos = (Real)p.y/(Real)this->GetSize().y;

    // Drag N Drop
    if ( event.LeftIsDown() ) {
        if ( MyApp::s_IsDragging == true ) {
            // 0 == did not click on terrain,
            if (0 == MyApp::s_App.CreateObject(x_pos, y_pos) ) {
                MyApp::s_IsDraggingFailed = true;
            } else { /* did create bunker on terrain*/
                // Undo/Redo Create
                MyApp::s_App.AddURSpotSelectedObj(UR_CREATE);
            }
        }
    }
}

void guiRenderWindow::OnLeaveWindow(wxMouseEvent& event)
{
}