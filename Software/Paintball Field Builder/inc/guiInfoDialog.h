/**
 * ---------------------------------------------------------
 * @author: David Whiteside
 * @date: 09/20/09
 * @description: QLogFile is a class that manages logging and error message handling
 * Copyright 2004-2009 Whiteside Solutions LLC (www.whitesidesolutions.com)
 * ---------------------------------------------------------
 */

#ifndef guiInfoDialog_H
#define guiInfoDialog_H

#include "guiDialogs.h"


/**
*/
class guiInfoDialog : public guiInfo 
{
public:
	guiInfoDialog(wxWindow *parent);
	~guiInfoDialog();
};


#endif //guiInfoDialog_H