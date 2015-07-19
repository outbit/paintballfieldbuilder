/**
 * ---------------------------------------------------------
 * @author: David Whiteside
 * @date: 09/20/09
 * @description: GUI View Dialog for wxWindow
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
#include "../inc/guiViewOptionsDialog.h"

guiViewOptionsDialog::guiViewOptionsDialog(wxWindow *parent) : guiViewOptions(parent)
{
    this->m_checkTerrain->SetValue(MyApp::s_App.mViewOptions._terrain);
    this->m_checkYardlines->SetValue(MyApp::s_App.mViewOptions._yardlines);
    this->m_checkSkybox->SetValue(MyApp::s_App.mViewOptions._skybox);
    this->m_check50yardline->SetValue(MyApp::s_App.mViewOptions._fiftyyardline);
    this->m_checkCenteryardline->SetValue(MyApp::s_App.mViewOptions._centeryardline);
    this->m_checkShadows->SetValue(MyApp::s_App.mViewOptions._shadows);
    this->m_checkGouraud->SetValue(MyApp::s_App.mViewOptions._gouraud);
    this->m_checkTexture->SetValue(MyApp::s_App.mViewOptions._texture);
    this->m_checkSolid->SetValue(MyApp::s_App.mViewOptions._solid);
}

guiViewOptionsDialog::~guiViewOptionsDialog()
{
}

void guiViewOptionsDialog::OnTerrainCheck(wxCommandEvent &event)
{
    MyApp::s_App.ToggleTerrain(this->m_checkTerrain->GetValue());
}

void guiViewOptionsDialog::OnYardLinesCheck(wxCommandEvent &event)
{
    MyApp::s_App.ToggleYardLines(this->m_checkYardlines->GetValue());
}

void guiViewOptionsDialog::OnSkyBoxCheck(wxCommandEvent &event)
{
    MyApp::s_App.ToggleSkyBox(this->m_checkSkybox->GetValue());
}

void guiViewOptionsDialog::On50YardLineCheck(wxCommandEvent &event)
{
    MyApp::s_App.ToggleFiftyYardLine(this->m_check50yardline->GetValue());
}

void guiViewOptionsDialog::OnCenterYardLineCheck(wxCommandEvent &event)
{
    MyApp::s_App.ToggleCenterYardLine(this->m_checkCenteryardline->GetValue());
}

void guiViewOptionsDialog::OnShadowsCheck(wxCommandEvent &event)
{
    MyApp::s_App.ToggleShadows(this->m_checkShadows->GetValue());
}

void guiViewOptionsDialog::OnGouraudShadingCheck(wxCommandEvent &event)
{
    MyApp::s_App.ToggleGouraud(this->m_checkGouraud->GetValue());
}

void guiViewOptionsDialog::OnTextureMappingCheck(wxCommandEvent &event)
{
    MyApp::s_App.ToggleTexture(this->m_checkTexture->GetValue());
}

void guiViewOptionsDialog::OnSolidViewCheck(wxCommandEvent &event)
{
    MyApp::s_App.ToggleSolid(this->m_checkSolid->GetValue());
}

void guiViewOptionsDialog::OnRendererChoice(wxCommandEvent &event)
{
    //MyApp::s_App.ToggleYardLines(this->m_checkYardlines->GetValue());
}

void guiViewOptionsDialog::OnBackgroundRedText(wxCommandEvent &event)
{
    //MyApp::s_App.ToggleYardLines(this->m_checkYardlines->GetValue());
}

void guiViewOptionsDialog::OnBackgroundGreenText(wxCommandEvent &event)
{
    //MyApp::s_App.ToggleYardLines(this->m_checkYardlines->GetValue());
}

void guiViewOptionsDialog::OnBackgroundBlueText(wxCommandEvent &event)
{
    //MyApp::s_App.ToggleYardLines(this->m_checkYardlines->GetValue());
}