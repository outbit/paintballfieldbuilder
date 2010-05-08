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
	if (mUndoRedo_Pos < 0) {
		mUndoRedo_Pos = 0; // start at zero because redo always adds 1
	}

	if (mUndoRedo_Pos < mUndoRedo.size()-1)
		if (mUndoRedo_Pos < UNDO_BUFFERSIZE)
		{
			mUndoRedo_Pos++;

			MakeURChange(false);
		}
		else
			return;
}


void CUndoRedo::Undo()
{
	if (mUndoRedo_Pos >= UNDO_BUFFERSIZE) {
		mUndoRedo_Pos = mUndoRedo.size()-1;
	}

	// mUndoRedo Starts At 1, 0 is a none action
	if (mUndoRedo_Pos >= 1)
	{
		MakeURChange(true);

		mUndoRedo_Pos--;
	} else {
		return;
	}
}