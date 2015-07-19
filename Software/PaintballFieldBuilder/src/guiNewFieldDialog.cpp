/**
 * ---------------------------------------------------------
 * @author: David Whiteside
 * @date: 09/20/09
 * @description: GUI New Field for wxWindow
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

#include "../inc/Application.h"
#include "../inc/guiNewFieldDialog.h"


guiNewFieldDialog::guiNewFieldDialog(wxWindow *parent) : guiNewField(parent)
{
    // Choose the current UNIT of measurement
    /*if (MyApp::s_App.mUnitM == WORLDUNITSPERYARD) {
    	this->m_choiceUnit->SetColumns(2);
    } else if (MyApp::s_App.mUnitM == WORLDUNITSPERMETER) {
    	this->m_choiceUnit->SetColumns(0);
    } else if (MyApp::s_App.mUnitM == WORLDUNITSPERFOOT) {
    	this->m_choiceUnit->SetColumns(1);
    }*/
}

guiNewFieldDialog::~guiNewFieldDialog()
{
}

void guiNewFieldDialog::OnCreateButton(wxCommandEvent &event)
{
    if (this->m_choiceUnit->GetCurrentSelection() == 2) {
        // Convert To Yards
        MyApp::s_App.mUnitM = WORLDUNITSPERYARD;
    } else if (this->m_choiceUnit->GetCurrentSelection() == 0) {
        // Convert Meters To Yards
        MyApp::s_App.mUnitM = WORLDUNITSPERMETER;
    } else if (this->m_choiceUnit->GetCurrentSelection() == 1) {
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

    this->Close();
}


void guiNewFieldDialog::OnCancelButton(wxCommandEvent &event)
{
    this->Close();
}