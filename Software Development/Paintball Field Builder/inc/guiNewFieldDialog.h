/**
 * ---------------------------------------------------------
 * @author: David Whiteside
 * @date: 09/20/09
 * @description: QLogFile is a class that manages logging and error message handling
 * Copyright 2004-2009 Whiteside Solutions LLC (www.whitesidesolutions.com)
 * ---------------------------------------------------------
 */

#ifndef guiNewFieldDialog_H
#define guiNewFieldDialog_H

#include "guiDialogs.h"


/**
*/
class guiNewFieldDialog : public guiNewField
{
public:
	guiNewFieldDialog(wxWindow *parent);
	~guiNewFieldDialog();
	void OnCreateButton( wxCommandEvent& event );
	void OnCancelButton( wxCommandEvent& event );
};


#endif //guiNewFieldDialog_H
