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
};


#endif //guiViewOptionsDialog_H