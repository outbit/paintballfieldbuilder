/**
 * ---------------------------------------------------------
 * @author: David Whiteside
 * @date: 07/04/10
 * @description: GUI Class for resizing the field
 * Copyright 2004-2010 Whiteside Solutions LLC (www.whitesidesolutions.com)
 * ---------------------------------------------------------
 */

#ifndef guiResizeFieldDialog_H
#define guiResizeFieldDialog_H

#include "guiDialogs.h"


/**
*/
class guiResizeFieldDialog : public guiResizeField
{
public:
	guiResizeFieldDialog(wxWindow *parent);
	~guiResizeFieldDialog();
	void OnCreateButton( wxCommandEvent& event );
	void OnCancelButton( wxCommandEvent& event );
};


#endif //guiResizeFieldDialog_H
