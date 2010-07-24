/**---------------------------------------------------------
 * @author: David Whiteside
 * @date: 09/20/09
 * @description: Undo REdo
 * Copyright 2004-2009 Whiteside Solutions LLC (www.whitesidesolutions.com)
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
	BunkerInfo old_object;
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