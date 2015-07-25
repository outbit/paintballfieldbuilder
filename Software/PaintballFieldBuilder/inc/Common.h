/**
 * ---------------------------------------------------------
 * @author: David Whiteside
 * @date: 09/20/09
 * @description: Common Application Include, Standard Definitions
 * Copyright (c) 2005-2015 David Whiteside
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

// Limit MAX value
inline float PFB_max(float val, float max)
{
	if (val > max) {
		val = max;
	} else if (val < max*-1) {
		val = max*-1;
	}
	return val;
}


#endif // PFB_COMMON
