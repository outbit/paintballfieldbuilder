/**
 * ---------------------------------------------------------
 * @author: David Whiteside
 * @date: 09/20/09
 * @description: Common Application Include, Standard Definitions
 * Copyright 2004-2009 Whiteside Solutions LLC (www.whitesidesolutions.com)
 * ---------------------------------------------------------
 */
#ifndef PFB_COMMON_H
#define PFB_COMMON_H


// Logging/OGRE App/Etc
#include "../inc/CommonTypes.h"
#include "../inc/wsLogFile.h"
#include "../inc/main.h"

// Standard Logging/Key
#define PFB_LOG(a) MyApp::s_Log.Log(a);
#define PFB_ERROR(a) MyApp::s_Log.LogERROR(a);
#define PFB_ERRORMESSAGE(a) wxMessageBox(wxT(a));
#define PFB_ISREGISTERED() (true == MyApp::s_IsRegistered)
// Timing
inline void PFB_Wait(const unsigned int &ms)
{
	unsigned int start;
	start = GetTickCount();
	while( (GetTickCount() - start) < ms) ;
}


#endif // PFB_COMMON