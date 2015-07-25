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
