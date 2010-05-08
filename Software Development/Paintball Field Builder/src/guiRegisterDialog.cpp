#include "../inc/Common.h"				// Include Before wxWidgets, or strange compiler error
#include "../inc/guiRegisterDialog.h"

guiRegisterDialog::guiRegisterDialog(wxWindow *parent) : guiRegister(parent)
{
}

guiRegisterDialog::~guiRegisterDialog()
{
}

void guiRegisterDialog::OnRegister( wxCommandEvent& event )
{
	PFB_ERRORMESSAGE("This is a tesT Register");
}