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

#ifndef WSLOGFILE_H
#define WSLOGFILE_H

#include "../inc/Common.h"

// WINDOWS
#include <windows.h>

// STANDARD LINE
#define WSLOG_LINE  "----------------------------------------------------------"
// ENTENSE LINE
#define WSLOG_LINE2 "**********************************************************"
// BOLD LINE
#define WSLOG_LINE3 "##########################################################"

// Message Box - Platform Independence
#define WSLOG_MSGBOX(a,b) wxMessageBox(a, b);


/** Class that is used for Logging
	@remarks
		This Class allows you to create log files and append log messages to them.
*/
class CWSLogFile
{
private:
	// The Name of the File
	String mLogFileName;
	// Set True to enable logging
	bool mLogging;
	// Set True to enable a date stamp on each log
	bool mLogTime;
	// Set True to enable 
	bool mDisplayErrors;
	// String for The name of the program that created the logfile
	String mLogFileCreator;
	// The Directory to Log To
	char *mRootdir;

public:
	// Constructors
	CWSLogFile(String logfilename = "Default.log", bool logging = true, bool logtime = true, bool displayerrors = true, String creator = "Default", bool init = true, bool clearlog = true, char* rootdir = NULL);

	// Destructors
	virtual ~CWSLogFile(void);

	// Create The Log File (like touch in *nix)
	void Init(bool clearlog = true);
	// Log to the File
	bool Log(String message, bool logtime = true);
	// Log Error to File
	bool LogERROR(String error);
	// Clear The Log File
	bool Clear(void);

	// Get The Name of the Log File
	inline String GetFileName(void) { 
		return this->mLogFileName; 
	}
	// Get If Logging Is Enabled
	inline bool GetLogging(void) {
		return this->mLogging; 
	}
	// Get If Error Display is Set
	inline bool GetDisplayErrors(void) {
		return this->mDisplayErrors;
	}
};


#endif // WSLOGFILE_H
