///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 16 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __guiDialogs__
#define __guiDialogs__

#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statbmp.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/dialog.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/choice.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class guiInfo
///////////////////////////////////////////////////////////////////////////////
class guiInfo : public wxDialog 
{
	private:
	
	protected:
		wxStaticBitmap* m_PFBBitmap;
		wxStaticText* m_PFBVersionStaticText;
		wxStaticText* m_PFBUrlStaticText;
		wxStaticBitmap* m_OGREBitmap;
		wxStaticText* m_OGREVersionStaticText;
	
	public:
		guiInfo( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Info"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 258,332 ), long style = wxDEFAULT_DIALOG_STYLE );
		~guiInfo();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class guiRegister
///////////////////////////////////////////////////////////////////////////////
class guiRegister : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_KeyStaticText;
		wxTextCtrl* m_KeyText;
		wxButton* m_RegisterButton;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnRegister( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		guiRegister( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Register"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 330,90 ), long style = wxDEFAULT_DIALOG_STYLE );
		~guiRegister();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class guiViewOptions
///////////////////////////////////////////////////////////////////////////////
class guiViewOptions : public wxDialog 
{
	private:
	
	protected:
		wxCheckBox* m_checkBox1;
		wxCheckBox* m_checkBox2;
		wxCheckBox* m_checkBox3;
		wxCheckBox* m_checkBox4;
		wxCheckBox* m_checkBox5;
		wxCheckBox* m_checkBox6;
		wxCheckBox* m_checkBox7;
		wxCheckBox* m_checkBox8;
		wxCheckBox* m_checkBox9;
		wxStaticText* m_staticText23;
		wxChoice* m_choice1;
		wxStaticText* m_staticText22;
		
		
		
		
		wxTextCtrl* m_textCtrl20;
		wxTextCtrl* m_textCtrl21;
		wxTextCtrl* m_textCtrl22;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnTerrainCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnYardLinesCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSkyBoxCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void On50YardLineCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnCenterYardLineCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnShadowsCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnGouraudShadingCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnTextureMappingCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSolidViewCheck( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnRendererChoice( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnBackgroundRedText( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnBackgroundGreenText( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnBackgroundBlueText( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		guiViewOptions( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("View Options"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 364,237 ), long style = wxDEFAULT_DIALOG_STYLE );
		~guiViewOptions();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class guiNewField
///////////////////////////////////////////////////////////////////////////////
class guiNewField : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText4;
		wxTextCtrl* m_textCtrl2;
		wxStaticText* m_staticText5;
		wxTextCtrl* m_textCtrl3;
		wxStaticText* m_staticText41;
		wxTextCtrl* m_textCtrl21;
		wxStaticText* m_staticText51;
		wxTextCtrl* m_textCtrl31;
		wxStaticText* m_staticText42;
		wxTextCtrl* m_textCtrl22;
		
		wxButton* m_button3;
		wxButton* m_button4;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnOk( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnCancel( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		guiNewField( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("New Field"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 435,220 ), long style = wxDEFAULT_DIALOG_STYLE );
		~guiNewField();
	
};

#endif //__guiDialogs__
