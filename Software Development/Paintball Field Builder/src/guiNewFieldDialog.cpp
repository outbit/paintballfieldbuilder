#include "../inc/Application.h"
#include "../inc/guiNewFieldDialog.h"


guiNewFieldDialog::guiNewFieldDialog(wxWindow *parent) : guiNewField(parent)
{
}

guiNewFieldDialog::~guiNewFieldDialog()
{
}

void guiNewFieldDialog::OnCreateButton(wxCommandEvent &event)
{
	if (this->m_choiceUnit->GetCurrentSelection() == 2)
	{
		// Convert To Yards
		MyApp::s_App.mUnitM = WORLDUNITSPERYARD;
	}
	else if (this->m_choiceUnit->GetCurrentSelection() == 0)
	{
		// Convert Meters To Yards
		MyApp::s_App.mUnitM = WORLDUNITSPERMETER;
	}
	else if (this->m_choiceUnit->GetCurrentSelection() == 1)
	{
		// Convert Meters To Feet
		MyApp::s_App.mUnitM = WORLDUNITSPERFOOT;
	}

	// Assign Values
	wxString str = "";
	long val = 0;

	// Set Field Width
	str = this->m_textFieldwidth->GetLineText(0);
	str.ToLong(&val, 10);
	MyApp::s_App.mFIELDWIDTH = val;

	// Set Field Length
	str = this->m_textFieldheight->GetLineText(0);
	str.ToLong(&val, 10);
	MyApp::s_App.mFIELDLENGTH = val;

	// Set Grid Width
	str = this->m_textGridwidth->GetLineText(0);
	str.ToLong(&val, 10);
	MyApp::s_App.mGRIDWIDTH = val;

	// Set Grid Length
	str = this->m_textGridheight->GetLineText(0);
	str.ToLong(&val, 10);
	MyApp::s_App.mGRIDLENGTH = val;

	// Check Field/Grid Max
	if (MyApp::s_App.mFIELDWIDTH > MAX_FIELDWIDTH) {
		MyApp::s_App.mFIELDWIDTH = MAX_FIELDWIDTH;
	}
	if (MyApp::s_App.mGRIDWIDTH > MAX_GRIDWIDTH) {
		MyApp::s_App.mGRIDWIDTH = MAX_GRIDWIDTH;
	}
	if (MyApp::s_App.mFIELDLENGTH > MAX_FIELDLENGTH) {
		MyApp::s_App.mFIELDLENGTH = MAX_FIELDLENGTH;
	}
	if (MyApp::s_App.mGRIDLENGTH > MAX_GRIDLENGTH) {
		MyApp::s_App.mGRIDLENGTH = MAX_GRIDLENGTH; 
	}

	// Check Field/grid Min
	if (MyApp::s_App.mFIELDWIDTH < MIN_FIELDWIDTH) {
		MyApp::s_App.mFIELDWIDTH = MIN_FIELDWIDTH;
	}
	if (MyApp::s_App.mGRIDWIDTH < MIN_GRIDWIDTH) {
		MyApp::s_App.mGRIDWIDTH = MIN_GRIDWIDTH;
	}
	if (MyApp::s_App.mFIELDLENGTH < MIN_FIELDLENGTH) {
		MyApp::s_App.mFIELDLENGTH = MIN_FIELDLENGTH;
	}
	if (MyApp::s_App.mGRIDLENGTH < MIN_GRIDLENGTH) {
		MyApp::s_App.mGRIDLENGTH = MIN_GRIDLENGTH;
	}

	// Re-Create Scene
	MyApp::s_App.DeleteAllBunkers();
	MyApp::s_App.ReCreateScene();
}


void guiNewFieldDialog::OnCancelButton(wxCommandEvent &event) {
	this->Close();
}