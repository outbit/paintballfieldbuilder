/**
 * ---------------------------------------------------------
 * @author: David Whiteside
 * @date: 09/20/09
 * @description: QLogFile is a class that manages logging and error message handling
 * Copyright 2004-2009 Whiteside Solutions LLC (www.whitesidesolutions.com)
 * ---------------------------------------------------------
 */

#include "../inc/wsLogFile.h"

#include <iostream>
#include <ctime>


CWSLogFile::CWSLogFile(String logfilename, bool logging, bool logtime, bool displayerrors, String creator, bool init, bool clearlog, char *rootdir)
{
    this->mLogFileName += logfilename;
    this->mLogging = logging;
    this->mLogTime = false;
    this->mDisplayErrors = displayerrors;
    this->mLogFileCreator = creator;
    this->mRootdir = rootdir;

    if (init) {
        this->Init(clearlog);
    }
    // OK SHOW LOG TIME NOW
    this->mLogTime = logtime;
}


void CWSLogFile::Init(bool clearlog)
{
    bool logtime = this->mLogTime;

    this->mLogTime = false;

    String tmp;
    tmp += "LOG FILE CREATED BY: ";
    tmp += this->mLogFileCreator;
    // Create A Brand New Log File Header!!
    time_t t = time(0);
    if (clearlog) {
        this->Clear();
    }
    this->Log(WSLOG_LINE3);
    this->Log(WSLOG_LINE);
    this->Log(tmp);
    this->Log(WSLOG_LINE);
    this->Log(asctime(gmtime(&t)));
    this->Log(WSLOG_LINE);
    this->Log(WSLOG_LINE3);
    this->Log(" ");
    this->Log(" ");

// OK SHOW LOG TIME NOW
    this->mLogTime = logtime;
}


CWSLogFile::~CWSLogFile(void)
{
}


/* *Desc: Logs A Message
 *Param $message: A Null Terminated String To Log
 *Param $endline: if true then it will start a new line
 *Return: false if failed
 */
bool CWSLogFile::Log(String message, bool logtime)
{
    if (this->mRootdir != NULL)
        SetCurrentDirectory(this->mRootdir);

    String tmp;
    tmp.clear();
    if (logtime && this->mLogTime) {
        time_t t = time(0);
        tmp += (asctime(gmtime(&t)));
        tmp += " : ";
    }
    tmp += message;

// If Logging Is Enabled
    if (this->mLogging) {
        FILE *filePtr = 0;

        // Check For Null Message
        if (!tmp.size()) {
            Log("Logging Error: Null Value");
            return false;
        }

        filePtr = fopen(this->mLogFileName.c_str(), "ab");

        // Check For Null File Pointer
        if (!filePtr) {
            Log("Logging Error: Failed To Open File");
            return false;
        }

        fwrite(tmp.c_str(), sizeof(char), tmp.size(), filePtr);

        // EndLine
        char endlinestr[] = {13, 10}; // Carrage Return, Line Feed
        fwrite(endlinestr, sizeof(char), sizeof(endlinestr), filePtr);

        fclose(filePtr);
    }

    return true;
}


/* *Desc: Logs A Error Message And Aborts
 *Param $error: The Error Message
 *Param $num: The Error Number (OPTIONAL)
 *Return: false if failed
 */
bool CWSLogFile::LogERROR(String error)
{
    if (error.size() == NULL) {
        Log("Failed To Log Error");
        return false;
    }

// If Logging Is Enabled
    if (this->mLogging) {
        Log(error);
    }

// If Display Errors Is Enabled
    if (this->mDisplayErrors) {
        WSLOG_MSGBOX(error.c_str(), "ERROR");
    }

    return true;
}


/* *Desc: Clears The Log File
 *Return: false if failed
 */
bool CWSLogFile::Clear(void)
{
    FILE *fileptr = 0;

    if (this->mRootdir != NULL)
        SetCurrentDirectory(this->mRootdir);

    fileptr = fopen(this->mLogFileName.c_str(), "wb");

    // Failed To Open
    if (!fileptr)
        return false;

    fclose(fileptr);

    return true;
}
