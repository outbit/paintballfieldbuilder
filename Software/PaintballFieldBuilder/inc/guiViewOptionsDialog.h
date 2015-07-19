/**
 * ---------------------------------------------------------
 * @author: David Whiteside
 * @date: 09/20/09
 * @description: QLogFile is a class that manages logging and error message handling
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

#ifndef guiViewOptionsDialog_H
#define guiViewOptionsDialog_H

#include "guiDialogs.h"


/**
*/
class guiViewOptionsDialog : public guiViewOptions
{
public:
	guiViewOptionsDialog(wxWindow *parent);
	~guiViewOptionsDialog();

	void OnTerrainCheck(wxCommandEvent &event);
	void OnYardLinesCheck(wxCommandEvent &event);
	void OnSkyBoxCheck(wxCommandEvent &event);
	void On50YardLineCheck(wxCommandEvent &event);
	void OnCenterYardLineCheck(wxCommandEvent &event);
	void OnShadowsCheck(wxCommandEvent &event);
	void OnGouraudShadingCheck(wxCommandEvent &event);
	void OnTextureMappingCheck(wxCommandEvent &event);
	void OnSolidViewCheck(wxCommandEvent &event);
	void OnRendererChoice(wxCommandEvent &event);
	void OnBackgroundRedText(wxCommandEvent &event);
	void OnBackgroundGreenText(wxCommandEvent &event);
	void OnBackgroundBlueText(wxCommandEvent &event);
};


#endif //guiViewOptionsDialog_H