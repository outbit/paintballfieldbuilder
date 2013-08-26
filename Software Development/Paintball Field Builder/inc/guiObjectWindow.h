/**
 * ---------------------------------------------------------
 * @author: David Whiteside
 * @date: 09/20/09
 * @description: The Window that handles objects that can be placed in render window
 * Copyright 2004-2009 Whiteside Solutions LLC (www.whitesidesolutions.com)
 * ---------------------------------------------------------
 */
#ifndef guiObjectWindow_H
#define guiObjectWindow_H

#define wxUSE_DEBUG_NEW_ALWAYS 0
#include <wx/wx.h>
#include <wx/menu.h>

class guiObjectWindow : public wxScrolledWindow
{
private:
	wxBoxSizer *m_Sizer;

public:
	static bool s_Redraw;

	guiObjectWindow(const wxString& title, wxWindow *parent);
	~guiObjectWindow();
	void DisconnectAllBunkers();
	void OnSize(wxSizeEvent& WXUNUSED(event));
	void OnButtonClick(wxMouseEvent& event);
	void OnQuit(wxCommandEvent& event);
	void OnDraw(wxDC& dc);
};

#endif // guiObjectWindow_H
