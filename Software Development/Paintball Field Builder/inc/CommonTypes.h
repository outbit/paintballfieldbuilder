/**
 * ---------------------------------------------------------
 * @author: David Whiteside
 * @date: 09/20/09
 * @description: Common Application Include, Standard Definitions
 * Copyright 2004-2009 Whiteside Solutions LLC (www.whitesidesolutions.com)
 * ---------------------------------------------------------
 */
#ifndef PFB_COMMON_TYPES_H
#define PFB_COMMON_TYPES_H

// DEBUG
#ifdef _DEBUG
#define _INC_MALLOC
#include <ogrememorymanager.h>
#endif

// OGRE Types
#include <Ogre.h>
#include <OgreConfigFile.h>
using namespace Ogre;

// Standard Type Defines
#ifndef TRUE
#define TRUE  1
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef NULL
#define NULL  0
#endif
#ifndef SAFE_FREE
#define SAFE_FREE(a) if (a) free(a);a = NULL;
#endif
#ifndef SAFE_DELETE
#define SAFE_DELETE(a) if (a) delete a;a = NULL;
#endif
#ifndef SAFE_DELETEA
#define SAFE_DELETEA(a) if (a) delete[] a;a = NULL;
#endif
#define TMPDIR "tmp/"
#define MAX_FILE MAX_PATH+500
#define MAXSTR 256

#endif // PFB_COMMON_TYPES