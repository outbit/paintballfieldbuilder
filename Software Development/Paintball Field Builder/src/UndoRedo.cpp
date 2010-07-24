/**
 * ---------------------------------------------------------
 * @author: David Whiteside
 * @date: 09/20/09
 * @description: UNDO/REDO
 * Copyright 2004-2009 Whiteside Solutions LLC (www.whitesidesolutions.com)
 * ---------------------------------------------------------
 */

#include "../inc/Common.h"
#include "../inc/UndoRedo.h"


void CUndoRedo::Redo()
{
	if ( false == this->mRedoStack.empty() ) {
			MakeURChange(false);

			this->mUndoStack.push(this->mRedoStack.top());
			this->mRedoStack.pop();
	} else {
		PFB_LOG("redo stack is empty");
		return;
	}
	PFB_LOG("redo - finished");
}


void CUndoRedo::Undo()
{
	// mUndoRedo Starts At 1, 0 is a none action
	if (false == this->mUndoStack.empty()) {
		MakeURChange(true);
		
		// Add the action to the REDO stack, remove from undo
		this->mRedoStack.push(this->mUndoStack.top());
		this->mUndoStack.pop();
	} else {
		PFB_LOG("undo stack is empty");
		return;
	}
	PFB_LOG("undo - finished");
}