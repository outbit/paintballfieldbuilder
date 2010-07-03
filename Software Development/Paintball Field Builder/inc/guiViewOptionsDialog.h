/**
 * ---------------------------------------------------------
 * @author: David Whiteside
 * @date: 09/20/09
 * @description: QLogFile is a class that manages logging and error message handling
 * Copyright 2004-2009 Whiteside Solutions LLC (www.whitesidesolutions.com)
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