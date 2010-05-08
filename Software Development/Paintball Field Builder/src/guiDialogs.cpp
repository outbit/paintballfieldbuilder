///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 16 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "../inc/guiDialogs.h"

///////////////////////////////////////////////////////////////////////////

guiInfo::guiInfo( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxGridSizer* gMainSizer;
	gMainSizer = new wxGridSizer( 1, 1, 0, 0 );
	
	wxStaticBoxSizer* sbPFBSizer;
	sbPFBSizer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Paintball Field Builder Info") ), wxVERTICAL );
	
	sbPFBSizer->SetMinSize( wxSize( 100,100 ) ); 
	m_PFBBitmap = new wxStaticBitmap( this, wxID_ANY, wxBitmap( wxT("../license/hpb_logo.bmp"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, 0 );
	sbPFBSizer->Add( m_PFBBitmap, 0, wxALL, 5 );
	
	m_PFBVersionStaticText = new wxStaticText( this, wxID_ANY, wxT("Paintball Field Builder v2.0.0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_PFBVersionStaticText->Wrap( -1 );
	sbPFBSizer->Add( m_PFBVersionStaticText, 0, wxALL, 5 );
	
	m_PFBUrlStaticText = new wxStaticText( this, wxID_ANY, wxT("www.paintballfieldbuilder.com"), wxDefaultPosition, wxDefaultSize, 0 );
	m_PFBUrlStaticText->Wrap( -1 );
	sbPFBSizer->Add( m_PFBUrlStaticText, 0, wxALL, 5 );
	
	gMainSizer->Add( sbPFBSizer, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbOGRESizer;
	sbOGRESizer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("3D POWERED BY:") ), wxVERTICAL );
	
	sbOGRESizer->SetMinSize( wxSize( 100,100 ) ); 
	m_OGREBitmap = new wxStaticBitmap( this, wxID_ANY, wxBitmap( wxT("../license/ogre_logo.bmp"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, 0 );
	sbOGRESizer->Add( m_OGREBitmap, 0, wxALL, 5 );
	
	m_OGREVersionStaticText = new wxStaticText( this, wxID_ANY, wxT("OGRE v1.7 (www.ogre3d.org)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_OGREVersionStaticText->Wrap( -1 );
	sbOGRESizer->Add( m_OGREVersionStaticText, 0, wxALL, 5 );
	
	gMainSizer->Add( sbOGRESizer, 1, wxEXPAND, 5 );
	
	this->SetSizer( gMainSizer );
	this->Layout();
}

guiInfo::~guiInfo()
{
}

guiRegister::guiRegister( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxGridSizer* gMainSizer;
	gMainSizer = new wxGridSizer( 2, 2, 0, 0 );
	
	m_KeyStaticText = new wxStaticText( this, wxID_ANY, wxT("Key:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_KeyStaticText->Wrap( -1 );
	gMainSizer->Add( m_KeyStaticText, 0, wxALL, 5 );
	
	m_KeyText = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 150,-1 ), 0 );
	m_KeyText->SetMaxLength( 30 ); 
	gMainSizer->Add( m_KeyText, 0, wxALL, 5 );
	
	m_RegisterButton = new wxButton( this, wxID_ANY, wxT("Register"), wxDefaultPosition, wxDefaultSize, 0 );
	gMainSizer->Add( m_RegisterButton, 0, wxALL, 5 );
	
	this->SetSizer( gMainSizer );
	this->Layout();
	
	// Connect Events
	m_KeyText->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( guiRegister::OnRegister ), NULL, this );
	m_RegisterButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( guiRegister::OnRegister ), NULL, this );
}

guiRegister::~guiRegister()
{
	// Disconnect Events
	m_KeyText->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( guiRegister::OnRegister ), NULL, this );
	m_RegisterButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( guiRegister::OnRegister ), NULL, this );
}

guiViewOptions::guiViewOptions( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxGridSizer* gSizer19;
	gSizer19 = new wxGridSizer( 2, 2, 0, 0 );
	
	wxStaticBoxSizer* sbSizer15;
	sbSizer15 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Field Options") ), wxVERTICAL );
	
	m_checkBox1 = new wxCheckBox( this, wxID_ANY, wxT("Terrain"), wxDefaultPosition, wxDefaultSize, 0 );
	
	sbSizer15->Add( m_checkBox1, 0, wxALL, 5 );
	
	m_checkBox2 = new wxCheckBox( this, wxID_ANY, wxT("Yard Lines"), wxDefaultPosition, wxDefaultSize, 0 );
	
	sbSizer15->Add( m_checkBox2, 0, wxALL, 5 );
	
	m_checkBox3 = new wxCheckBox( this, wxID_ANY, wxT("SkyBox"), wxDefaultPosition, wxDefaultSize, 0 );
	
	sbSizer15->Add( m_checkBox3, 0, wxALL, 5 );
	
	m_checkBox4 = new wxCheckBox( this, wxID_ANY, wxT("50 Yard Line"), wxDefaultPosition, wxDefaultSize, 0 );
	
	sbSizer15->Add( m_checkBox4, 0, wxALL, 5 );
	
	m_checkBox5 = new wxCheckBox( this, wxID_ANY, wxT("Center Yard Line"), wxDefaultPosition, wxDefaultSize, 0 );
	
	sbSizer15->Add( m_checkBox5, 0, wxALL, 5 );
	
	gSizer19->Add( sbSizer15, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer16;
	sbSizer16 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Graphic Options") ), wxVERTICAL );
	
	m_checkBox6 = new wxCheckBox( this, wxID_ANY, wxT("Shadows"), wxDefaultPosition, wxDefaultSize, 0 );
	
	sbSizer16->Add( m_checkBox6, 0, wxALL, 5 );
	
	m_checkBox7 = new wxCheckBox( this, wxID_ANY, wxT("Gouraud Shading"), wxDefaultPosition, wxDefaultSize, 0 );
	
	sbSizer16->Add( m_checkBox7, 0, wxALL, 5 );
	
	m_checkBox8 = new wxCheckBox( this, wxID_ANY, wxT("Texture Mapping"), wxDefaultPosition, wxDefaultSize, 0 );
	
	sbSizer16->Add( m_checkBox8, 0, wxALL, 5 );
	
	m_checkBox9 = new wxCheckBox( this, wxID_ANY, wxT("Solid View"), wxDefaultPosition, wxDefaultSize, 0 );
	
	sbSizer16->Add( m_checkBox9, 0, wxALL, 5 );
	
	wxGridSizer* gSizer22;
	gSizer22 = new wxGridSizer( 1, 2, 0, 0 );
	
	m_staticText23 = new wxStaticText( this, wxID_ANY, wxT("Renderer:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText23->Wrap( -1 );
	gSizer22->Add( m_staticText23, 0, wxALL, 5 );
	
	wxString m_choice1Choices[] = { wxT("Direct3D9"), wxT("OpenGL") };
	int m_choice1NChoices = sizeof( m_choice1Choices ) / sizeof( wxString );
	m_choice1 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice1NChoices, m_choice1Choices, 0 );
	m_choice1->SetSelection( 0 );
	gSizer22->Add( m_choice1, 0, wxALL, 5 );
	
	sbSizer16->Add( gSizer22, 1, wxEXPAND, 5 );
	
	wxGridSizer* gSizer20;
	gSizer20 = new wxGridSizer( 1, 5, 0, 0 );
	
	m_staticText22 = new wxStaticText( this, wxID_ANY, wxT("Background Color:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText22->Wrap( -1 );
	m_staticText22->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_ACTIVEBORDER ) );
	
	gSizer20->Add( m_staticText22, 0, wxALL, 5 );
	
	
	gSizer20->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	gSizer20->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	gSizer20->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	gSizer20->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_textCtrl20 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 30,-1 ), 0 );
	m_textCtrl20->SetMaxLength( 3 ); 
	gSizer20->Add( m_textCtrl20, 0, wxALL, 5 );
	
	m_textCtrl21 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 30,-1 ), 0 );
	m_textCtrl21->SetMaxLength( 3 ); 
	gSizer20->Add( m_textCtrl21, 0, wxALL, 5 );
	
	m_textCtrl22 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 30,-1 ), 0 );
	m_textCtrl22->SetMaxLength( 3 ); 
	gSizer20->Add( m_textCtrl22, 0, wxALL, 5 );
	
	sbSizer16->Add( gSizer20, 1, wxEXPAND, 5 );
	
	gSizer19->Add( sbSizer16, 1, wxEXPAND, 5 );
	
	this->SetSizer( gSizer19 );
	this->Layout();
	
	// Connect Events
	m_checkBox1->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( guiViewOptions::OnTerrainCheck ), NULL, this );
	m_checkBox2->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( guiViewOptions::OnYardLinesCheck ), NULL, this );
	m_checkBox3->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( guiViewOptions::OnSkyBoxCheck ), NULL, this );
	m_checkBox4->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( guiViewOptions::On50YardLineCheck ), NULL, this );
	m_checkBox5->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( guiViewOptions::OnCenterYardLineCheck ), NULL, this );
	m_checkBox6->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( guiViewOptions::OnShadowsCheck ), NULL, this );
	m_checkBox7->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( guiViewOptions::OnGouraudShadingCheck ), NULL, this );
	m_checkBox8->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( guiViewOptions::OnTextureMappingCheck ), NULL, this );
	m_checkBox9->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( guiViewOptions::OnSolidViewCheck ), NULL, this );
	m_choice1->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( guiViewOptions::OnRendererChoice ), NULL, this );
	m_textCtrl20->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( guiViewOptions::OnBackgroundRedText ), NULL, this );
	m_textCtrl21->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( guiViewOptions::OnBackgroundGreenText ), NULL, this );
	m_textCtrl22->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( guiViewOptions::OnBackgroundBlueText ), NULL, this );
}

guiViewOptions::~guiViewOptions()
{
	// Disconnect Events
	m_checkBox1->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( guiViewOptions::OnTerrainCheck ), NULL, this );
	m_checkBox2->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( guiViewOptions::OnYardLinesCheck ), NULL, this );
	m_checkBox3->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( guiViewOptions::OnSkyBoxCheck ), NULL, this );
	m_checkBox4->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( guiViewOptions::On50YardLineCheck ), NULL, this );
	m_checkBox5->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( guiViewOptions::OnCenterYardLineCheck ), NULL, this );
	m_checkBox6->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( guiViewOptions::OnShadowsCheck ), NULL, this );
	m_checkBox7->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( guiViewOptions::OnGouraudShadingCheck ), NULL, this );
	m_checkBox8->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( guiViewOptions::OnTextureMappingCheck ), NULL, this );
	m_checkBox9->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( guiViewOptions::OnSolidViewCheck ), NULL, this );
	m_choice1->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( guiViewOptions::OnRendererChoice ), NULL, this );
	m_textCtrl20->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( guiViewOptions::OnBackgroundRedText ), NULL, this );
	m_textCtrl21->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( guiViewOptions::OnBackgroundGreenText ), NULL, this );
	m_textCtrl22->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( guiViewOptions::OnBackgroundBlueText ), NULL, this );
}

guiNewField::guiNewField( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxGridSizer* gSizer3;
	gSizer3 = new wxGridSizer( 2, 2, 0, 0 );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Field Dimensions") ), wxVERTICAL );
	
	wxGridSizer* gSizer4;
	gSizer4 = new wxGridSizer( 2, 2, 0, 0 );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("Width"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	gSizer4->Add( m_staticText4, 0, wxALL, 5 );
	
	m_textCtrl2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrl2->SetMaxLength( 30 ); 
	gSizer4->Add( m_textCtrl2, 0, wxALL, 5 );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, wxT("Height"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	gSizer4->Add( m_staticText5, 0, wxALL, 5 );
	
	m_textCtrl3 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrl3->SetMaxLength( 30 ); 
	gSizer4->Add( m_textCtrl3, 0, wxALL, 5 );
	
	sbSizer2->Add( gSizer4, 1, wxEXPAND, 5 );
	
	gSizer3->Add( sbSizer2, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer5;
	sbSizer5 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Grid Dimensions") ), wxVERTICAL );
	
	wxGridSizer* gSizer41;
	gSizer41 = new wxGridSizer( 2, 2, 0, 0 );
	
	m_staticText41 = new wxStaticText( this, wxID_ANY, wxT("Width"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText41->Wrap( -1 );
	gSizer41->Add( m_staticText41, 0, wxALL, 5 );
	
	m_textCtrl21 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrl21->SetMaxLength( 30 ); 
	gSizer41->Add( m_textCtrl21, 0, wxALL, 5 );
	
	m_staticText51 = new wxStaticText( this, wxID_ANY, wxT("Height"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText51->Wrap( -1 );
	gSizer41->Add( m_staticText51, 0, wxALL, 5 );
	
	m_textCtrl31 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrl31->SetMaxLength( 30 ); 
	gSizer41->Add( m_textCtrl31, 0, wxALL, 5 );
	
	sbSizer5->Add( gSizer41, 1, wxEXPAND, 5 );
	
	gSizer3->Add( sbSizer5, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer6;
	sbSizer6 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Options") ), wxVERTICAL );
	
	wxGridSizer* gSizer42;
	gSizer42 = new wxGridSizer( 2, 2, 0, 0 );
	
	m_staticText42 = new wxStaticText( this, wxID_ANY, wxT("Width"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText42->Wrap( -1 );
	gSizer42->Add( m_staticText42, 0, wxALL, 5 );
	
	m_textCtrl22 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrl22->SetMaxLength( 30 ); 
	gSizer42->Add( m_textCtrl22, 0, wxALL, 5 );
	
	sbSizer6->Add( gSizer42, 1, wxEXPAND, 5 );
	
	gSizer3->Add( sbSizer6, 1, wxEXPAND, 5 );
	
	
	gSizer3->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_button3 = new wxButton( this, wxID_ANY, wxT("Ok"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer3->Add( m_button3, 0, wxALL, 5 );
	
	m_button4 = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer3->Add( m_button4, 0, wxALL, 5 );
	
	this->SetSizer( gSizer3 );
	this->Layout();
	
	// Connect Events
	m_button3->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( guiNewField::OnOk ), NULL, this );
	m_button4->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( guiNewField::OnCancel ), NULL, this );
}

guiNewField::~guiNewField()
{
	// Disconnect Events
	m_button3->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( guiNewField::OnOk ), NULL, this );
	m_button4->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( guiNewField::OnCancel ), NULL, this );
}
