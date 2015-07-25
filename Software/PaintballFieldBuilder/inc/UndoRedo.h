/**---------------------------------------------------------
 * @author: David Whiteside
 * @date: 09/20/09
 * @description: Undo REdo
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
 
#ifndef UNDOREDO_H
#define UNDOREDO_H

// Includes
#include "FieldKit.h"
#include <stack>

// Definitions
enum UNDOREDO_ACT {UR_CREATE, UR_DELETE, UR_CHANGE, UR_NONE};
#define UNDO_BUFFERSIZE 10

// Bunker Information stored in each UndoRedo Node
struct BunkerInfo
{
	String meshname;
	Ogre::Vector3 pos;
	Ogre::Quaternion or;
};

// Structs
struct UNDOREDO
{
	Ogre::String node;
	Ogre::String entityname;
	BunkerInfo object;
	UNDOREDO_ACT action;
};


class CUndoRedo
{
protected:
std::stack<UNDOREDO> mUndoStack;
std::stack<UNDOREDO> mRedoStack;

public:
CUndoRedo::CUndoRedo()
{
}

void Redo();
void Undo();

protected:
virtual void AddURSpot(UNDOREDO_ACT action, SceneNode *node) = NULL;
virtual void MakeURChange(bool undo) = NULL;
};


#endif // UNDOREDO_H
