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
	
	m_checkTerrain = new wxCheckBox( this, wxID_ANY, wxT("Terrain"), wxDefaultPosition, wxDefaultSize, 0 );
	
	sbSizer15->Add( m_checkTerrain, 0, wxALL, 5 );
	
	m_checkYardlines = new wxCheckBox( this, wxID_ANY, wxT("Yard Lines"), wxDefaultPosition, wxDefaultSize, 0 );
	
	sbSizer15->Add( m_checkYardlines, 0, wxALL, 5 );
	
	m_checkSkybox = new wxCheckBox( this, wxID_ANY, wxT("SkyBox"), wxDefaultPosition, wxDefaultSize, 0 );
	
	sbSizer15->Add( m_checkSkybox, 0, wxALL, 5 );
	
	m_check50yardline = new wxCheckBox( this, wxID_ANY, wxT("50 Yard Line"), wxDefaultPosition, wxDefaultSize, 0 );
	
	sbSizer15->Add( m_check50yardline, 0, wxALL, 5 );
	
	m_checkCenteryardline = new wxCheckBox( this, wxID_ANY, wxT("Center Yard Line"), wxDefaultPosition, wxDefaultSize, 0 );
	
	sbSizer15->Add( m_checkCenteryardline, 0, wxALL, 5 );
	
	gSizer19->Add( sbSizer15, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer16;
	sbSizer16 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Graphic Options") ), wxVERTICAL );
	
	m_checkShadows = new wxCheckBox( this, wxID_ANY, wxT("Shadows"), wxDefaultPosition, wxDefaultSize, 0 );
	
	sbSizer16->Add( m_checkShadows, 0, wxALL, 5 );
	
	m_checkGouraud = new wxCheckBox( this, wxID_ANY, wxT("Gouraud Shading"), wxDefaultPosition, wxDefaultSize, 0 );
	
	sbSizer16->Add( m_checkGouraud, 0, wxALL, 5 );
	
	m_checkTexture = new wxCheckBox( this, wxID_ANY, wxT("Texture Mapping"), wxDefaultPosition, wxDefaultSize, 0 );
	
	sbSizer16->Add( m_checkTexture, 0, wxALL, 5 );
	
	m_checkSolid = new wxCheckBox( this, wxID_ANY, wxT("Solid View"), wxDefaultPosition, wxDefaultSize, 0 );
	
	sbSizer16->Add( m_checkSolid, 0, wxALL, 5 );
	
	wxGridSizer* gSizer22;
	gSizer22 = new wxGridSizer( 1, 2, 0, 0 );
	
	m_staticText23 = new wxStaticText( this, wxID_ANY, wxT("Renderer:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText23->Wrap( -1 );
	gSizer22->Add( m_staticText23, 0, wxALL, 5 );
	
	wxString m_choiceRendererChoices[] = { wxT("Direct3D9"), wxT("OpenGL") };
	int m_choiceRendererNChoices = sizeof( m_choiceRendererChoices ) / sizeof( wxString );
	m_choiceRenderer = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceRendererNChoices, m_choiceRendererChoices, 0 );
	m_choiceRenderer->SetSelection( 1 );
	gSizer22->Add( m_choiceRenderer, 0, wxALL, 5 );
	
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
	
	m_textRed = new wxTextCtrl( this, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize( 30,-1 ), 0 );
	m_textRed->SetMaxLength( 3 ); 
	gSizer20->Add( m_textRed, 0, wxALL, 5 );
	
	m_textGreen = new wxTextCtrl( this, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize( 30,-1 ), 0 );
	m_textGreen->SetMaxLength( 3 ); 
	gSizer20->Add( m_textGreen, 0, wxALL, 5 );
	
	m_textBlue = new wxTextCtrl( this, wxID_ANY, wxT("255"), wxDefaultPosition, wxSize( 30,-1 ), 0 );
	m_textBlue->SetMaxLength( 3 ); 
	gSizer20->Add( m_textBlue, 0, wxALL, 5 );
	
	sbSizer16->Add( gSizer20, 1, wxEXPAND, 5 );
	
	gSizer19->Add( sbSizer16, 1, wxEXPAND, 5 );
	
	this->SetSizer( gSizer19 );
	this->Layout();
	
	// Connect Events
	m_checkTerrain->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( guiViewOptions::OnTerrainCheck ), NULL, this );
	m_checkYardlines->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( guiViewOptions::OnYardLinesCheck ), NULL, this );
	m_checkSkybox->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( guiViewOptions::OnSkyBoxCheck ), NULL, this );
	m_check50yardline->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( guiViewOptions::On50YardLineCheck ), NULL, this );
	m_checkCenteryardline->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( guiViewOptions::OnCenterYardLineCheck ), NULL, this );
	m_checkShadows->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( guiViewOptions::OnShadowsCheck ), NULL, this );
	m_checkGouraud->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( guiViewOptions::OnGouraudShadingCheck ), NULL, this );
	m_checkTexture->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( guiViewOptions::OnTextureMappingCheck ), NULL, this );
	m_checkSolid->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( guiViewOptions::OnSolidViewCheck ), NULL, this );
	m_choiceRenderer->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( guiViewOptions::OnRendererChoice ), NULL, this );
	m_textRed->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( guiViewOptions::OnBackgroundRedText ), NULL, this );
	m_textGreen->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( guiViewOptions::OnBackgroundGreenText ), NULL, this );
	m_textBlue->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( guiViewOptions::OnBackgroundBlueText ), NULL, this );
}

guiViewOptions::~guiViewOptions()
{
	// Disconnect Events
	m_checkTerrain->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( guiViewOptions::OnTerrainCheck ), NULL, this );
	m_checkYardlines->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( guiViewOptions::OnYardLinesCheck ), NULL, this );
	m_checkSkybox->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( guiViewOptions::OnSkyBoxCheck ), NULL, this );
	m_check50yardline->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( guiViewOptions::On50YardLineCheck ), NULL, this );
	m_checkCenteryardline->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( guiViewOptions::OnCenterYardLineCheck ), NULL, this );
	m_checkShadows->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( guiViewOptions::OnShadowsCheck ), NULL, this );
	m_checkGouraud->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( guiViewOptions::OnGouraudShadingCheck ), NULL, this );
	m_checkTexture->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( guiViewOptions::OnTextureMappingCheck ), NULL, this );
	m_checkSolid->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( guiViewOptions::OnSolidViewCheck ), NULL, this );
	m_choiceRenderer->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( guiViewOptions::OnRendererChoice ), NULL, this );
	m_textRed->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( guiViewOptions::OnBackgroundRedText ), NULL, this );
	m_textGreen->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( guiViewOptions::OnBackgroundGreenText ), NULL, this );
	m_textBlue->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( guiViewOptions::OnBackgroundBlueText ), NULL, this );
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
	
	m_textFieldwidth = new wxTextCtrl( this, wxID_ANY, wxT("16"), wxDefaultPosition, wxDefaultSize, 0 );
	m_textFieldwidth->SetMaxLength( 30 ); 
	gSizer4->Add( m_textFieldwidth, 0, wxALL, 5 );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, wxT("Height"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	gSizer4->Add( m_staticText5, 0, wxALL, 5 );
	
	m_textFieldheight = new wxTextCtrl( this, wxID_ANY, wxT("30"), wxDefaultPosition, wxDefaultSize, 0 );
	m_textFieldheight->SetMaxLength( 30 ); 
	gSizer4->Add( m_textFieldheight, 0, wxALL, 5 );
	
	sbSizer2->Add( gSizer4, 1, wxEXPAND, 5 );
	
	gSizer3->Add( sbSizer2, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer5;
	sbSizer5 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Grid Dimensions") ), wxVERTICAL );
	
	wxGridSizer* gSizer41;
	gSizer41 = new wxGridSizer( 2, 2, 0, 0 );
	
	m_staticText41 = new wxStaticText( this, wxID_ANY, wxT("Width"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText41->Wrap( -1 );
	gSizer41->Add( m_staticText41, 0, wxALL, 5 );
	
	m_textGridwidth = new wxTextCtrl( this, wxID_ANY, wxT("16"), wxDefaultPosition, wxDefaultSize, 0 );
	m_textGridwidth->SetMaxLength( 30 ); 
	gSizer41->Add( m_textGridwidth, 0, wxALL, 5 );
	
	m_staticText51 = new wxStaticText( this, wxID_ANY, wxT("Height"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText51->Wrap( -1 );
	gSizer41->Add( m_staticText51, 0, wxALL, 5 );
	
	m_textGridheight = new wxTextCtrl( this, wxID_ANY, wxT("30"), wxDefaultPosition, wxDefaultSize, 0 );
	m_textGridheight->SetMaxLength( 30 ); 
	gSizer41->Add( m_textGridheight, 0, wxALL, 5 );
	
	sbSizer5->Add( gSizer41, 1, wxEXPAND, 5 );
	
	gSizer3->Add( sbSizer5, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer6;
	sbSizer6 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Options") ), wxVERTICAL );
	
	wxGridSizer* gSizer42;
	gSizer42 = new wxGridSizer( 2, 2, 0, 0 );
	
	m_staticText42 = new wxStaticText( this, wxID_ANY, wxT("Unit"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText42->Wrap( -1 );
	gSizer42->Add( m_staticText42, 0, wxALL, 5 );
	
	wxString m_choiceUnitChoices[] = { wxT("Meters"), wxT("Feet"), wxT("Yards") };
	int m_choiceUnitNChoices = sizeof( m_choiceUnitChoices ) / sizeof( wxString );
	m_choiceUnit = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceUnitNChoices, m_choiceUnitChoices, 0 );
	m_choiceUnit->SetSelection( 2 );
	gSizer42->Add( m_choiceUnit, 0, wxALL, 5 );
	
	sbSizer6->Add( gSizer42, 1, wxEXPAND, 5 );
	
	gSizer3->Add( sbSizer6, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer12;
	sbSizer12 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxEmptyString ), wxVERTICAL );
	
	m_buttonCreate = new wxButton( this, wxID_ANY, wxT("Create Field"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer12->Add( m_buttonCreate, 0, wxALL, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer12->Add( m_buttonCancel, 0, wxALL, 5 );
	
	gSizer3->Add( sbSizer12, 1, wxEXPAND, 5 );
	
	this->SetSizer( gSizer3 );
	this->Layout();
	
	// Connect Events
	m_buttonCreate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( guiNewField::OnCreateButton ), NULL, this );
	m_buttonCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( guiNewField::OnCancelButton ), NULL, this );
}

guiNewField::~guiNewField()
{
	// Disconnect Events
	m_buttonCreate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( guiNewField::OnCreateButton ), NULL, this );
	m_buttonCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( guiNewField::OnCancelButton ), NULL, this );
}

guiResizeField::guiResizeField( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
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
	
	m_textFieldwidth = new wxTextCtrl( this, wxID_ANY, wxT("16"), wxDefaultPosition, wxDefaultSize, 0 );
	m_textFieldwidth->SetMaxLength( 30 ); 
	gSizer4->Add( m_textFieldwidth, 0, wxALL, 5 );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, wxT("Height"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	gSizer4->Add( m_staticText5, 0, wxALL, 5 );
	
	m_textFieldheight = new wxTextCtrl( this, wxID_ANY, wxT("30"), wxDefaultPosition, wxDefaultSize, 0 );
	m_textFieldheight->SetMaxLength( 30 ); 
	gSizer4->Add( m_textFieldheight, 0, wxALL, 5 );
	
	sbSizer2->Add( gSizer4, 1, wxEXPAND, 5 );
	
	gSizer3->Add( sbSizer2, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer5;
	sbSizer5 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Grid Dimensions") ), wxVERTICAL );
	
	wxGridSizer* gSizer41;
	gSizer41 = new wxGridSizer( 2, 2, 0, 0 );
	
	m_staticText41 = new wxStaticText( this, wxID_ANY, wxT("Width"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText41->Wrap( -1 );
	gSizer41->Add( m_staticText41, 0, wxALL, 5 );
	
	m_textGridwidth = new wxTextCtrl( this, wxID_ANY, wxT("16"), wxDefaultPosition, wxDefaultSize, 0 );
	m_textGridwidth->SetMaxLength( 30 ); 
	gSizer41->Add( m_textGridwidth, 0, wxALL, 5 );
	
	m_staticText51 = new wxStaticText( this, wxID_ANY, wxT("Height"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText51->Wrap( -1 );
	gSizer41->Add( m_staticText51, 0, wxALL, 5 );
	
	m_textGridheight = new wxTextCtrl( this, wxID_ANY, wxT("30"), wxDefaultPosition, wxDefaultSize, 0 );
	m_textGridheight->SetMaxLength( 30 ); 
	gSizer41->Add( m_textGridheight, 0, wxALL, 5 );
	
	sbSizer5->Add( gSizer41, 1, wxEXPAND, 5 );
	
	gSizer3->Add( sbSizer5, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer6;
	sbSizer6 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Options") ), wxVERTICAL );
	
	wxGridSizer* gSizer42;
	gSizer42 = new wxGridSizer( 2, 2, 0, 0 );
	
	m_staticText42 = new wxStaticText( this, wxID_ANY, wxT("Unit"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText42->Wrap( -1 );
	gSizer42->Add( m_staticText42, 0, wxALL, 5 );
	
	wxString m_choiceUnitChoices[] = { wxT("Meters"), wxT("Feet"), wxT("Yards") };
	int m_choiceUnitNChoices = sizeof( m_choiceUnitChoices ) / sizeof( wxString );
	m_choiceUnit = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceUnitNChoices, m_choiceUnitChoices, 0 );
	m_choiceUnit->SetSelection( 2 );
	gSizer42->Add( m_choiceUnit, 0, wxALL, 5 );
	
	sbSizer6->Add( gSizer42, 1, wxEXPAND, 5 );
	
	gSizer3->Add( sbSizer6, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer11;
	sbSizer11 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxEmptyString ), wxVERTICAL );
	
	m_OkButton = new wxButton( this, wxID_ANY, wxT("Resize"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer11->Add( m_OkButton, 0, wxALL, 5 );
	
	gSizer3->Add( sbSizer11, 1, wxEXPAND, 5 );
	
	this->SetSizer( gSizer3 );
	this->Layout();
	
	// Connect Events
	m_OkButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( guiResizeField::OnOkButton ), NULL, this );
}

guiResizeField::~guiResizeField()
{
	// Disconnect Events
	m_OkButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( guiResizeField::OnOkButton ), NULL, this );
}
