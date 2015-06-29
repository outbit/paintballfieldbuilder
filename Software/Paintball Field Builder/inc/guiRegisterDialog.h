/**
 * ---------------------------------------------------------
 * @author: David Whiteside
 * @date: 09/20/09
 * @description: QLogFile is a class that manages logging and error message handling
 * Copyright 2004-2009 Whiteside Solutions LLC (www.whitesidesolutions.com)
 * ---------------------------------------------------------
 */

#ifndef guiRegisterDialog_H
#define guiRegisterDialog_H

#include "guiDialogs.h"


/**
*/
class guiRegisterDialog : public guiRegister
{
public:
	guiRegisterDialog(wxWindow *parent);
	~guiRegisterDialog();
	void OnRegister( wxCommandEvent& event );
};


#endif //guiRegisterDialog_H