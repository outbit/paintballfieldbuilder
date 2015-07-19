/**
 * ---------------------------------------------------------
 * @author: David Whiteside
 * @date: 09/20/09
 * @description: UNDO/REDO
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