/**
 * ---------------------------------------------------------
 * @author: David Whiteside
 * @date: 07/05/10
 * @description: The Main Parent Window of Every Other Window
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
 
#ifndef guiParentWindow_H
#define guiParentWindow_H


#define wxUSE_DEBUG_NEW_ALWAYS 0
#include <wx/wx.h>
#include <wx/menu.h>


class guiParentWindow : public wxFrame
{
private:
	// Event Declerations
   enum {	ID_FILE_OPEN=wxID_HIGHEST+1,
			ID_FILE_NEW,
			ID_FILE_SAVE,
			ID_FILE_SAVEAS,
			ID_FILE_LOADFIELDKIT,
			ID_EDIT_UNDO,
			ID_EDIT_REDO,
			ID_EDIT_DELETE,
			ID_EDIT_SELECTNONE,
			ID_EDIT_MIRRORFIELD,
			ID_EDIT_RESIZEFIELD,
			ID_VIEW_TOP,
			ID_VIEW_FIRSTPERSON,
			ID_VIEW_PERSPECTIVE,
			ID_VIEW_RESET,
			ID_VIEW_OPTIONS,
			ID_RENDER_SAVESCREENSHOT,
			ID_ABOUT_HELP,
			ID_ABOUT_INFO,
			ID_ABOUT_REGISTER,
			ID_ROTATEVIEW,
			ID_MOVEVIEW,
			ID_ROTATEOBJ,
			ID_MOVEOBJ,
			ID_SELECTOBJ,
			ID_CREATEOBJ,
			ID_CLONEOBJ					}; // eND OF eNUM

protected:
	wxMenuBar *mMenubar;
	wxMenu *mFile;
	wxMenu *mEdit;
	wxMenu *mView;
	wxMenu *mRender;
	wxMenu *mAbout;
	wxToolBar *mToolbar;

	// If a toolbar is selected, deselect it
	void EnableLastToolbar();

public:
	guiParentWindow(const wxString& title);
	~guiParentWindow();

	void OnSize(wxSizeEvent& event);

	void OnFileNew(wxCommandEvent& event);
	void OnFileOpen(wxCommandEvent& event);
	void OnFileSave(wxCommandEvent& event);
	void OnFileSaveAs(wxCommandEvent& event);
	void OnLoadFieldKit(wxCommandEvent& event);
	void OnQuit(wxCommandEvent& event);

	void OnUndo(wxCommandEvent& event);
	void OnRedo(wxCommandEvent& event);
	void OnDelete(wxCommandEvent& event);
	void OnSelectNone(wxCommandEvent& event);
	void OnMirrorField(wxCommandEvent& event);
	void OnResizeField(wxCommandEvent& event);

	void OnViewTop(wxCommandEvent& event);
	void OnViewFirstPerson(wxCommandEvent& event);
	void OnViewPerspective(wxCommandEvent& event);
	void OnViewReset(wxCommandEvent& event);
	void OnViewOptions(wxCommandEvent& event);

	void OnSaveScreenshot(wxCommandEvent& event);

	void OnHelp(wxCommandEvent& event);
	void OnInfo(wxCommandEvent& event);
	void OnRegister(wxCommandEvent& event);

	void OnMoveView(wxCommandEvent& event);
	void OnRotateView(wxCommandEvent& event);
	void OnMoveObj(wxCommandEvent& event);
	void OnRotateObj(wxCommandEvent& event);
	void OnSelectObj(wxCommandEvent& event);
	void OnCreateObj(wxCommandEvent& event);
	void OnCloneObj(wxCommandEvent& event);

	void OnKeyDown(wxKeyEvent& event);
	void OnKeyUp(wxKeyEvent& event);
};

#endif // guiParentWindow_H
