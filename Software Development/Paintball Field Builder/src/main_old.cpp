#include "main.hpp"
#include "Application.hpp"
#include "../Licensing Software/LicensingSoftware.hpp" // FOR CHECKING FOR VALID USER KEY
#include "../Licensing Software/Client/Client.hpp" // REGISTRATION

UINT G_CursorTool = ID_MOVEVIEW;
VIEWMODE G_ViewMode = TOP;

CCTWindow G_PFDWindow(false, 0, 0, 800, 600, "PFDClass", "Paintball Field Builder", MAKEINTRESOURCE(IDR_MENU1), MAKEINTRESOURCE(IDI_ICON1), NULL, NULL, WS_MAXIMIZE|WS_THICKFRAME|WS_SYSMENU|WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN, (HBRUSH)(COLOR_BTNFACE+1));
CCTWindow G_PFDEditWindow(true, 150+20, 32, 650, 600, "PFDEditClass", "Viewport", NULL, NULL, NULL, WS_EX_APPWINDOW, WS_CHILD|WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_BORDER|WS_VISIBLE|WS_CLIPCHILDREN);
CCTWindow G_PFDToolWindow(true, 0, 32, 128+20+20, 600, "PFDToolClass", "Field Kit", NULL, NULL, NULL, WS_EX_TOOLWINDOW|WS_EX_APPWINDOW|WS_EX_TOPMOST, /*WS_POPUP|*/WS_CHILD|WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_BORDER|WS_VISIBLE|WS_CLIPCHILDREN|WS_VSCROLL, (HBRUSH)(COLOR_BTNFACE+1));
CFieldKit G_FieldKit;
BunkerID G_Bunker;
PFDApplication G_App;
HINSTANCE G_hInst;
bool G_Render = false;
HWND G_DLG2 = NULL;
HWND G_DLG3 = NULL;
HWND G_DLG4 = NULL;
HWND G_DLG5 = NULL;
HWND G_DLG7 = NULL;
HWND G_DLG8 = NULL;
HWND G_DLG9 = NULL;
int G_BunkerScroll = 1;
CQLogFile G_Log("PaintballFieldBuilder.log", true, true, true, "Paintball Field Builder", false, true, G_Directory);


bool G_Quit = false;
bool G_Restart = false;


char G_Directory[MAX_FILE] = {0};
char G_FieldKit_Path[MAX_FILE] = {0};

Real G_MouseX, G_MouseY;
bool G_FirstLeftClick = true;
bool G_FirstRightClick = true;
bool G_SOFTWARE_REGISTERED = false;
bool G_File_Saved = false;
bool G_File_Opened = false;
BYTE G_Dragging = false;

VIEWOPTIONS G_ViewOptions;

unsigned int FIELDWIDTH = 16;
unsigned int FIELDLENGTH = 30;
unsigned int GRIDWIDTH = 16;
unsigned int GRIDLENGTH = 30;
Real G_UnitM = WORLDUNITSPERYARD;

ColourValue G_BackgroundColor(1.0f, 1.0f, 1.0f);

#define LOADSCREEN


/*
void PrintBitmap(LPCTSTR filename)
{
 CPrintDialog printDlg(FALSE);
 printDlg.GetDefaults(); 
 // Or get from user:
 // if (printDlg.DoModal() == IDCANCEL)   
 //        return; 
 CDC dc;
 if (!dc.Attach(printDlg.GetPrinterDC())) {
  AfxMessageBox(_T("No printer found!")); return;
 } 
 
 dc.m_bPrinting = TRUE; 
 DOCINFO di;    
 // Initialise print document details
 ::ZeroMemory (&di, sizeof (DOCINFO));
 di.cbSize = sizeof (DOCINFO);
 di.lpszDocName = filename; 
 BOOL bPrintingOK = dc.StartDoc(&di); // Begin a new print job 
 // Get the printing extents
 // and store in the m_rectDraw field of a 
 // CPrintInfo object
 CPrintInfo Info;
 Info.SetMaxPage(1); // just one page 
 int maxw = dc.GetDeviceCaps(HORZRES);
 int maxh = dc.GetDeviceCaps(VERTRES); 
 Info.m_rectDraw.SetRect(0, 0, maxw, maxh); 
 for (UINT page = Info.GetMinPage(); page <= 
      Info.GetMaxPage() && bPrintingOK; page++) {
  dc.StartPage();    // begin new page
  Info.m_nCurPage = page;
  CBitmap bitmap;
  // LoadImage does the trick here, it creates a DIB section
  // You can also use a resource here
  // by using MAKEINTRESOURCE() ... etc. 
  if(!bitmap.Attach(::LoadImage(
   ::GetModuleHandle(NULL), filename, IMAGE_BITMAP, 0, 0, 
   LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE))) {
    AfxMessageBox(_T("Error loading bitmap!")); return;
   } 
   BITMAP bm;
   bitmap.GetBitmap(&bm);
   int w = bm.bmWidth; 
   int h = bm.bmHeight; 
   // create memory device context
   CDC memDC; 
   memDC.CreateCompatibleDC(&dc);
   CBitmap *pBmp = memDC.SelectObject(&bitmap);
   memDC.SetMapMode(dc.GetMapMode());
   dc.SetStretchBltMode(HALFTONE);
   // now stretchblt to maximum width on page
   dc.StretchBlt(0, 0, maxw, maxh, &memDC, 0, 0, w, h, SRCCOPY); 
   // clean up
   memDC.SelectObject(pBmp);
   bPrintingOK = (dc.EndPage() > 0);   // end page
 } 
 if (bPrintingOK)
   dc.EndDoc(); // end a print job
 else dc.AbortDoc();           // abort job. 
}
*/

bool LoadFieldKits_InFolder(char *path)
{
	WIN32_FIND_DATA FileData; 
	HANDLE hSearch;  
	BOOL fFinished = FALSE;
	char tm_path[MAX_FILE] = {0};
	char tmpstr[MAX_FILE] = {0};

   //Make a backup of the directory       
	memset(tm_path, NULL, sizeof(tm_path));
    strcpy(tm_path, path);

	// Start Search
   hSearch = FindFirstFile("*.*", &FileData); 
   if (hSearch == INVALID_HANDLE_VALUE) 
   { 
      LOG("No Files Found In FieldKit Folder?"); 
      fFinished = true;
   } 
 
   while (!fFinished) 
   {
    //Is it a . or .. directory? If it is, skip, or we'll go forever.      
       if (!(strcmp(FileData.cFileName, "." )) || !(strcmp(FileData.cFileName, "..")))             
       {
		   // Do Nothing
       }
	   else if ((FileData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY)
	   {
            //Restore the original directory            
            strcpy(path, tm_path);

            //Append the file found on to the path of the           
            sprintf(path, "%s\\%s", path, FileData.cFileName);

            if (SetCurrentDirectory(path))             
            {                 
                LoadFieldKits_InFolder(path);             
            }
			else
			{
				string tmp = string("Failed To Search Directory: ") + path;
				LOG(tmp.c_str());
				// return false; // STOP SEARCHING WHEN YOU CANNOT OPEN A DIRECTORY
			}
	   }
	   else // File
	   {
					memset(tmpstr, NULL, sizeof(tmpstr));
                    sprintf(tmpstr, "%s\\%s", tm_path, FileData.cFileName);
					string tmpname;
					tmpname += FileData.cFileName;
					if (string::npos != tmpname.find(".pfk"))
					{
					G_FieldKit.Load(tmpstr);
					}
					SetCurrentDirectory(tm_path);
	   }

      if (!FindNextFile(hSearch, &FileData)) 
      {
         if (GetLastError() == ERROR_NO_MORE_FILES) 
         { 
            fFinished = TRUE; 
         } 
         else 
         { 
            LOG("Could Not Find Next File"); 
            return false;
         } 
      }
   }    

// Close the search handle. 
   FindClose(hSearch);

	return true;
}


void TryCreateFunctions(void)
{
				UpdateMousePos(false);
			  if (G_CursorTool == ID_SELECT)
			  {
				G_App.SelectObject(G_MouseX, G_MouseY);
			  }
			  else if (G_CursorTool == ID_CREATEOBJ)
			  {
				G_App.CreateObject(G_MouseX, G_MouseY);
			  }
			  else if (G_CursorTool == ID_CLONEOBJ)
			  {
				G_App.SelectObject(G_MouseX, G_MouseY);
				G_App.CloneSelectedObj();
				G_App.MoveSelectedObj(G_MouseX, G_MouseY);
			  }
			  else if ( (G_CursorTool == ID_ROTATEOBJ) || (G_CursorTool == ID_MOVEOBJ) )
			  {
					G_App.SelectObject(G_MouseX, G_MouseY);
			  }
}

inline void UpdateMousePos(bool pure)
{
	POINT p;
	GetCursorPos(&p);
		if (!pure)
		{
		  G_MouseX = (Real)((Real)((Real)(p.x) - (G_PFDWindow.xpos+G_PFDEditWindow.xpos))/G_PFDEditWindow.width);
		  G_MouseY = (Real)((Real)((Real)(p.y) - (G_PFDWindow.ypos+G_PFDEditWindow.ypos)/*-40*/)/G_PFDEditWindow.height);
		}
		else
		{
		  G_MouseX = (Real)p.x;
		  G_MouseY = (Real)p.y;
		}
}

void DrawFieldKit(HWND hWnd)
{
    HDC hDC = NULL, MemDC = NULL;
    PAINTSTRUCT Ps;
    HBITMAP bmp = NULL;

		InvalidateRect(hWnd, NULL, true); // Force Redraw

	    hDC = BeginPaint(hWnd, &Ps);

		 for (unsigned int x = 0; x < G_FieldKit.GetBunkerCount(); x++)
		 {
			if (G_Bunker == x)
			{
				::PatBlt(hDC, (10-4), G_BunkerScroll+(10-4)+(x*(128+10)), 128+8, 128+8, BLACKNESS);
			}

	     // Load the bitmap from file
		 bmp = (HBITMAP)G_FieldKit.GetBunker(x)->bmp;
			if (bmp)
			{
			// Create a memory device compatible with the above DC variable
			MemDC = CreateCompatibleDC(hDC);
			// Select the new bitmap
			SelectObject(MemDC, bmp);
			// Copy the bits from the memory DC into the current dc
			BitBlt(hDC, 10, G_BunkerScroll+10+(x*(128+10)), 128, 128, MemDC, 0, 0, SRCCOPY);

			// Restore the old bitmap
			DeleteDC(MemDC);
			}
		 }

	    EndPaint(hWnd, &Ps);
}

void DrawNothing(HWND hWnd)
{
    HDC hDC = NULL;
    PAINTSTRUCT Ps;

		InvalidateRect(hWnd, NULL, true); // Force Redraw

	    hDC = BeginPaint(hWnd, &Ps);
	    EndPaint(hWnd, &Ps);
}

void HandleMessagesDLG(HWND handle)
{
	MSG msg;
	BOOL bRet = GetMessage(&msg, NULL, 0, 0);

		if ((bRet == -1) || !bRet)
		{
		// Handle the error and possibly exit
		}
		else if (!IsWindow(handle) || !IsDialogMessage(handle, &msg)) 
		{ 
			TranslateMessage(&msg); 
			DispatchMessage(&msg); 
		} 
}


LRESULT CALLBACK DefaultProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  switch(msg)
  {
    case WM_CLOSE:
		{
		PostMessage(hWnd, WM_QUIT, 0, 0); // Send A WM_QUIT Message
		}break;

	case WM_COMMAND:
		{
/*
			switch (wParam)
			{
			   case ID_OK:
				{
		          PostMessage(hWnd, WM_QUIT, 0, 0); // Send A WM_QUIT Message
				}break;
			}
*/
		}break;

    default:
        // Process the left-over messages
        return DefWindowProc(hWnd, msg, wParam, lParam);

  }
return 0;
}


LRESULT CALLBACK DLG2Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
HWND hCheck = NULL;
char tmp[MAXSTR] = {0};
float r = 1, g = 1, b = 1;
HWND hWndList = NULL;

  switch(message)
  {
    case WM_CREATE:
	     return(0);
	break;

    case WM_CLOSE:
		// Get Renderer
		memset(tmp, 0, sizeof(tmp));
		hWndList = GetDlgItem(hWnd, IDC_COMBO2);
		GetDlgItemText(hWnd, IDC_COMBO2, tmp, MAX_STR);

		G_DLG2 = NULL;
		EndDialog(hWnd,false);

		if (!strcmp("OpenGL", tmp))
		{
		G_App.ChangeRenderer(PFB_RENDER_OPENGL);
		}
		else if (!strcmp("Direct3D9c", tmp))
		{
		G_App.ChangeRenderer(PFB_RENDER_DIRECT3D9);
		}
	     return(0);
	break;


    case WM_INITDIALOG:
			// Set up default amount
			hWndList = GetDlgItem(hWnd, IDC_COMBO2);

			SendMessage(hWndList, CB_ADDSTRING, 0, (LPARAM) "OpenGL");
			SendMessage(hWndList, CB_SETITEMDATA, 0, (LPARAM) 0);
			SendMessage(hWndList, CB_ADDSTRING, 0, (LPARAM) "Direct3D9c");
			SendMessage(hWndList, CB_SETITEMDATA, 1, (LPARAM) 1);

			SendDlgItemMessage(hWnd, IDC_COMBO2, CB_SETCURSEL, !G_App.GetRenderer(), !G_App.GetRenderer());

				memset(tmp, 0, sizeof(tmp));
				sprintf(tmp, "%d", (int)(G_BackgroundColor.r*255));
				SetDlgItemText(hWnd, IDC_REDEDIT, tmp);

				memset(tmp, 0, sizeof(tmp));
				sprintf(tmp, "%d", (int)(G_BackgroundColor.g*255));
				SetDlgItemText(hWnd, IDC_GREENEDIT, tmp);

				memset(tmp, 0, sizeof(tmp));
				sprintf(tmp, "%d", (int)(G_BackgroundColor.b*255));
				SetDlgItemText(hWnd, IDC_BLUEEDIT, tmp);
	     return(0);
	break;

    case WM_PAINT:
		InvalidateRect(hWnd, NULL, true); // Force Redraw
	break;

	      case WM_COMMAND: 
            switch(LOWORD(wParam))
			 {
                case IDC_CHECK1:
					G_ViewOptions._terrain = !G_ViewOptions._terrain;
					G_App.ToggleTerrain(G_ViewOptions._terrain);
				  return(0);
				break;

                case IDC_CHECK2:
					G_ViewOptions._yardlines = !G_ViewOptions._yardlines;
					G_App.ToggleYardLines(G_ViewOptions._yardlines);
				  return(0);
				break;

                case IDC_CHECK3:
					G_ViewOptions._skybox = !G_ViewOptions._skybox;
					G_App.ToggleSkyBox(G_ViewOptions._skybox);
				  return(0);
				break;

                case IDC_CHECK4:
					G_ViewOptions._fiftyyardline = !G_ViewOptions._fiftyyardline;
					G_App.ToggleFiftyYardLine(G_ViewOptions._fiftyyardline);
				  return(0);
				break;

                case IDC_CHECK5:
					G_ViewOptions._shadows = !G_ViewOptions._shadows;
					G_App.ToggleShadows(G_ViewOptions._shadows);
				  return(0);
				break;

                case IDC_CHECK6:
					G_ViewOptions._gouraud = !G_ViewOptions._gouraud;
					G_App.ToggleGouraud(G_ViewOptions._gouraud);
				  return(0);
				break;

                case IDC_CHECK7:
					G_ViewOptions._texture = !G_ViewOptions._texture;
					G_App.ToggleTexture(G_ViewOptions._texture);
				  return(0);
				break;

                case IDC_CHECK8:
					G_ViewOptions._solid = !G_ViewOptions._solid;
					G_App.ToggleSolid(G_ViewOptions._solid);
				  return(0);
				break;

                case IDC_CHECK9:
					G_ViewOptions._centeryardline = !G_ViewOptions._centeryardline;
					G_App.ToggleCenterYardLine(G_ViewOptions._centeryardline);
				  return(0);
				break;

                case IDC_SETBACKGROUNDCOLOR:
					memset(tmp, 0, sizeof(tmp));
					GetDlgItemText(hWnd, IDC_REDEDIT, tmp, MAX_STR);
					r = atof(tmp);
					memset(tmp, 0, sizeof(tmp));
					GetDlgItemText(hWnd, IDC_GREENEDIT, tmp, MAX_STR);
					g = atof(tmp);
					memset(tmp, 0, sizeof(tmp));
					GetDlgItemText(hWnd, IDC_BLUEEDIT, tmp, MAX_STR);
					b = atof(tmp);
					if (r > 255)
						r = 255;
					if (g > 255)
						g = 255;
					if (b > 255)
						b = 255;
					G_BackgroundColor = ColourValue(r/255, g/255, b/255, 1.0f);
					G_App.SetBackgroundColor(G_BackgroundColor);
				  return(0);
				break;

                case IDCANCEL:
					G_DLG2 = NULL;
					EndDialog(hWnd, false);
				  return(0);
				break;
			 }
  }
    return(false);
}

LRESULT CALLBACK DLG3Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
HWND hCheck = NULL;
  switch(message)
  {
    case WM_CREATE:
	     return(0);
	break;

    case WM_CLOSE:
		G_DLG3 = NULL;
	  EndDialog(hWnd,false);
	     return(0);
	break;

    case WM_PAINT:
		InvalidateRect(hWnd, NULL, true); // Force Redraw
	break;
  }
    return(false);
}

LRESULT CALLBACK DLG4Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
HWND hCheck = NULL;
  switch(message)
  {
    case WM_CREATE:
	     return(0);
	break;

    case WM_CLOSE:
		G_DLG4 = NULL;
	  EndDialog(hWnd,false);
	     return(0);
	break;

    case WM_PAINT:
		InvalidateRect(hWnd, NULL, true); // Force Redraw
	break;
  }
    return(false);
}

LRESULT CALLBACK DLG7Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
HWND hCheck = NULL;
char tmp[MAXSTR] = {0};
HWND hWndList = NULL;
  switch(message)
  {
    case WM_CREATE:
	     return(0);
	break;

    case WM_CLOSE:
		G_DLG7 = NULL;
	  EndDialog(hWnd,false);
	     return(0);
	break;

    case WM_INITDIALOG:
			// Set up default amount
			hWndList = GetDlgItem(hWnd, IDC_COMBO1);

			SendMessage(hWndList, CB_ADDSTRING, 0, (LPARAM) "Yards");
			SendMessage(hWndList, CB_SETITEMDATA, 0, (LPARAM) 0);
			SendMessage(hWndList, CB_ADDSTRING, 0, (LPARAM) "Meters");
			SendMessage(hWndList, CB_SETITEMDATA, 1, (LPARAM) 1);

			SendDlgItemMessage(hWnd, IDC_COMBO1, CB_SETCURSEL, 0, 0);

				memset(tmp, 0, sizeof(tmp));
				sprintf(tmp, "%d", (int)FIELDWIDTH);
				SetDlgItemText(hWnd, IDC_EDIT6, tmp);

				memset(tmp, 0, sizeof(tmp));
				sprintf(tmp, "%d", (int)FIELDLENGTH);
				SetDlgItemText(hWnd, IDC_EDIT7, tmp);

				memset(tmp, 0, sizeof(tmp));
				sprintf(tmp, "%d", (int)GRIDWIDTH);
				SetDlgItemText(hWnd, IDC_EDIT8, tmp);

				memset(tmp, 0, sizeof(tmp));
				sprintf(tmp, "%d", (int)GRIDLENGTH);
				SetDlgItemText(hWnd, IDC_EDIT9, tmp);

				// Get Measurment
				memset(tmp, 0, sizeof(tmp));
				if (G_UnitM == WORLDUNITSPERYARD)
				{
					strcpy(tmp, "Yards");
				}
				else if (G_UnitM == WORLDUNITSPERMETER)
				{
					strcpy(tmp, "Meters");
				}
				else if (G_UnitM == WORLDUNITSPERFOOT)
				{
					strcpy(tmp, "Feet");
				}
				else if (G_UnitM == WORLDUNITSPERINCH)
				{
					strcpy(tmp, "Inches");
				}
				else
				{
					strcpy(tmp, "Yards");
				}
				SetDlgItemText(hWnd, IDC_COMBO1, tmp);
	     return(0);
	break;

    case WM_PAINT:
		return (0);
	break;

	case WM_COMMAND:
		{
			switch (wParam)
			{
			case IDOK:
				{
				memset(tmp, 0, sizeof(tmp));
				GetDlgItemText(hWnd, IDC_EDIT6, tmp, MAX_STR);
				FIELDWIDTH = atof(tmp);

				memset(tmp, 0, sizeof(tmp));
				GetDlgItemText(hWnd, IDC_EDIT7, tmp, MAX_STR);
				FIELDLENGTH = atof(tmp);

				memset(tmp, 0, sizeof(tmp));
				GetDlgItemText(hWnd, IDC_EDIT8, tmp, MAX_STR);
				GRIDWIDTH = atof(tmp);

				memset(tmp, 0, sizeof(tmp));
				GetDlgItemText(hWnd, IDC_EDIT9, tmp, MAX_STR);
				GRIDLENGTH = atof(tmp);

				// Get Measurment
				memset(tmp, 0, sizeof(tmp));
				hWndList = GetDlgItem(hWnd, IDC_COMBO1);
				GetDlgItemText(hWnd, IDC_COMBO1, tmp, MAX_STR);

				if (!strcmp(tmp, "Yards"))
				{
					// Convert To Yards
					G_UnitM = WORLDUNITSPERYARD;
				}
				else if (!strcmp(tmp, "Meters"))
				{
					// Convert Meters To Yards
					G_UnitM = WORLDUNITSPERMETER;
				}
				else if (!strcmp(tmp, "Feet"))
				{
					// Convert Meters To Feet
					G_UnitM = WORLDUNITSPERFOOT;
				}
				else if (!strcmp(tmp, "Inch"))
				{
					// Convert Meters To Inches
					G_UnitM = WORLDUNITSPERINCH;
				}
				else
				{
					// Convert To Yards
					G_UnitM = WORLDUNITSPERYARD;
				}

				if (FIELDWIDTH > MAX_FIELDWIDTH)
					FIELDWIDTH = MAX_FIELDWIDTH;
				if (GRIDWIDTH > MAX_GRIDWIDTH)
					GRIDWIDTH = MAX_GRIDWIDTH;
				if (FIELDLENGTH > MAX_FIELDLENGTH)
					FIELDLENGTH = MAX_FIELDLENGTH;
				if (GRIDLENGTH > MAX_GRIDLENGTH)
					GRIDLENGTH = MAX_GRIDLENGTH; 

				if (FIELDWIDTH < MIN_FIELDWIDTH)
					FIELDWIDTH = MIN_FIELDWIDTH;
				if (GRIDWIDTH < MIN_GRIDWIDTH)
					GRIDWIDTH = MIN_GRIDWIDTH;
				if (FIELDLENGTH < MIN_FIELDLENGTH)
					FIELDLENGTH = MIN_FIELDLENGTH;
				if (GRIDLENGTH < MIN_GRIDLENGTH)
					GRIDLENGTH = MIN_GRIDLENGTH; 

					G_App.DeleteAllBunkers();

					G_App.ReCreateScene();

					ToggleAll();

					G_File_Saved = false;
					G_File_Opened = false;

					G_DLG7 = NULL;
					EndDialog(hWnd,false);
					return 0;
				}break;

			case IDCANCEL:
				{
					G_DLG7 = NULL;
					EndDialog(hWnd,false);
					return 0;
				}break;
			}
		break;
		}
  }
    return(false);
}


LRESULT CALLBACK DLG9Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
HWND hCheck = NULL;
char tmp[MAXSTR] = {0};
HWND hWndList = NULL;
  switch(message)
  {
    case WM_CREATE:
	     return(0);
	break;

    case WM_CLOSE:
		G_DLG9 = NULL;
	  EndDialog(hWnd,false);
	     return(0);
	break;

    case WM_INITDIALOG:
			// Set up default amount
			hWndList = GetDlgItem(hWnd, IDC_COMBO1);

			SendMessage(hWndList, CB_ADDSTRING, 0, (LPARAM) "Yards");
			SendMessage(hWndList, CB_SETITEMDATA, 0, (LPARAM) 0);
			SendMessage(hWndList, CB_ADDSTRING, 0, (LPARAM) "Meters");
			SendMessage(hWndList, CB_SETITEMDATA, 1, (LPARAM) 1);

			SendDlgItemMessage(hWnd, IDC_COMBO1, CB_SETCURSEL, 0, 0);

				memset(tmp, 0, sizeof(tmp));
				sprintf(tmp, "%d", (int)FIELDWIDTH);
				SetDlgItemText(hWnd, IDC_EDIT6, tmp);

				memset(tmp, 0, sizeof(tmp));
				sprintf(tmp, "%d", (int)FIELDLENGTH);
				SetDlgItemText(hWnd, IDC_EDIT7, tmp);

				memset(tmp, 0, sizeof(tmp));
				sprintf(tmp, "%d", (int)GRIDWIDTH);
				SetDlgItemText(hWnd, IDC_EDIT8, tmp);

				memset(tmp, 0, sizeof(tmp));
				sprintf(tmp, "%d", (int)GRIDLENGTH);
				SetDlgItemText(hWnd, IDC_EDIT9, tmp);

				// Get Measurment
				memset(tmp, 0, sizeof(tmp));
				if (G_UnitM == WORLDUNITSPERYARD)
				{
					strcpy(tmp, "Yards");
				}
				else if (G_UnitM == WORLDUNITSPERMETER)
				{
					strcpy(tmp, "Meters");
				}
				else if (G_UnitM == WORLDUNITSPERFOOT)
				{
					strcpy(tmp, "Feet");
				}
				else if (G_UnitM == WORLDUNITSPERINCH)
				{
					strcpy(tmp, "Inches");
				}
				else
				{
					strcpy(tmp, "Yards");
				}
				SetDlgItemText(hWnd, IDC_COMBO1, tmp);
	     return(0);
	break;

    case WM_PAINT:
		return (0);
	break;

	case WM_COMMAND:
		{
			switch (wParam)
			{
			case IDOK:
				{
				memset(tmp, 0, sizeof(tmp));
				GetDlgItemText(hWnd, IDC_EDIT6, tmp, MAX_STR);
				FIELDWIDTH = atof(tmp);

				memset(tmp, 0, sizeof(tmp));
				GetDlgItemText(hWnd, IDC_EDIT7, tmp, MAX_STR);
				FIELDLENGTH = atof(tmp);

				memset(tmp, 0, sizeof(tmp));
				GetDlgItemText(hWnd, IDC_EDIT8, tmp, MAX_STR);
				GRIDWIDTH = atof(tmp);

				memset(tmp, 0, sizeof(tmp));
				GetDlgItemText(hWnd, IDC_EDIT9, tmp, MAX_STR);
				GRIDLENGTH = atof(tmp);

				// Get Measurment
				memset(tmp, 0, sizeof(tmp));
				hWndList = GetDlgItem(hWnd, IDC_COMBO1);
				GetDlgItemText(hWnd, IDC_COMBO1, tmp, MAX_STR);

				if (!strcmp(tmp, "Yards"))
				{
					// Convert To Yards
					G_UnitM = WORLDUNITSPERYARD;
				}
				else if (!strcmp(tmp, "Meters"))
				{
					// Convert Meters To Yards
					G_UnitM = WORLDUNITSPERMETER;
				}
				else if (!strcmp(tmp, "Feet"))
				{
					// Convert Meters To Feet
					G_UnitM = WORLDUNITSPERFOOT;
				}
				else if (!strcmp(tmp, "Inch"))
				{
					// Convert Meters To Inches
					G_UnitM = WORLDUNITSPERINCH;
				}
				else
				{
					// Convert To Yards
					G_UnitM = WORLDUNITSPERYARD;
				}

				if (FIELDWIDTH > MAX_FIELDWIDTH)
					FIELDWIDTH = MAX_FIELDWIDTH;
				if (GRIDWIDTH > MAX_GRIDWIDTH)
					GRIDWIDTH = MAX_GRIDWIDTH;
				if (FIELDLENGTH > MAX_FIELDLENGTH)
					FIELDLENGTH = MAX_FIELDLENGTH;
				if (GRIDLENGTH > MAX_GRIDLENGTH)
					GRIDLENGTH = MAX_GRIDLENGTH; 

				if (FIELDWIDTH < MIN_FIELDWIDTH)
					FIELDWIDTH = MIN_FIELDWIDTH;
				if (GRIDWIDTH < MIN_GRIDWIDTH)
					GRIDWIDTH = MIN_GRIDWIDTH;
				if (FIELDLENGTH < MIN_FIELDLENGTH)
					FIELDLENGTH = MIN_FIELDLENGTH;
				if (GRIDLENGTH < MIN_GRIDLENGTH)
					GRIDLENGTH = MIN_GRIDLENGTH; 

					G_App.ReCreateScene();

					ToggleAll();

					G_DLG9 = NULL;
					EndDialog(hWnd,false);
					return 0;
				}break;

			case IDCANCEL:
				{
					G_DLG9 = NULL;
					EndDialog(hWnd,false);
					return 0;
				}break;
			}
		break;
		}
  }
    return(false);
}


LRESULT CALLBACK DLG8Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
HWND hCheck = NULL;
  switch(message)
  {
    case WM_CREATE:
	     return(0);
	break;

    case WM_CLOSE:
		WinExec("C:\\Program Files\\Internet Explorer\\IEXPLORE.EXE http://www.paintballfieldbuilder.com/buy.htm",SW_MAXIMIZE);
		G_DLG8 = NULL;
	  EndDialog(hWnd,false);
	     return(0);
	break;

    case WM_PAINT:
		InvalidateRect(hWnd, NULL, true); // Force Redraw
	break;


	case WM_COMMAND:
		{
			switch (wParam)
			{
			case IDOK:
				{
					WinExec("C:\\Program Files\\Internet Explorer\\IEXPLORE.EXE http://www.paintballfieldbuilder.com/buy.htm",SW_MAXIMIZE);
					G_DLG8 = NULL;
					EndDialog(hWnd,false);
					return 0;
				}break;
			}
		break;
		}
  }
    return(false);
}


LRESULT CALLBACK PFDProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
char File_Name[MAX_FILE] = {0};
static char SAVED_NAME[MAX_FILE] = {0};
OPENFILENAME op = {0}; 
static int lastviewmode = ID_VIEW_TOP;

  switch(msg)
  {
    case WM_CLOSE:
		{
		//G_PFDWindow.DestroyCTWindow();
		G_Quit = true;
		PostMessage(hWnd, WM_QUIT, 0, 0); // Send A WM_QUIT Message
		}break;

    case WM_DESTROY:
		{
		//G_PFDWindow.DestroyCTWindow();
		G_Quit = true;
		PostMessage(hWnd, WM_QUIT, 0, 0); // Send A WM_QUIT Message
		}break;

	case WM_CREATE:
		{
			SendMessage(hWnd, WM_PAINT, 0, 0);
		}break;

	case WM_SHOWWINDOW:
		{
			if (wParam == TRUE) // Window Shown
			{
			ShowWindow(hWnd, SW_MAXIMIZE);
			}
			else // Window Not Shown
			{
			ShowWindow(hWnd, SW_MINIMIZE);
			}
		}break;

	case WM_NOTIFY:
		{
		switch (((LPNMHDR)lParam)->code)
		{
			LPTOOLTIPTEXT lpToolTipText;
			static char szBuf[80];

			case TTN_NEEDTEXT: // tooltip meldet sich und will einen Text
				lpToolTipText = (LPTOOLTIPTEXT)lParam;
				LoadString (G_hInst, lpToolTipText->hdr.idFrom,
				szBuf, sizeof (szBuf));
				lpToolTipText->lpszText = szBuf;
			break;
		}
		}break;

  case WM_PAINT: 
		{
		 DrawNothing(hWnd);
		 _RENDER(G_App);
         SetWindowPos(G_PFDToolWindow.hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
	     UpdateWindow(G_PFDToolWindow.hWnd);         // Update Window
		 UpdateWindow(G_PFDWindow.hWndToolbar);         // Update Window
		}break;

	case WM_COMMAND:
		{
			switch (wParam)
			{
			 // File
			   case ID_FILE_OPEN:
				{
                    // Browse For File
				     ZeroMemory(SAVED_NAME, sizeof(SAVED_NAME));
				     ZeroMemory(&op, sizeof(op));
				     op.lStructSize = sizeof(op);
				     op.hwndOwner = hWnd;
				     op.nMaxFile = sizeof(SAVED_NAME);
				     op.lpstrFilter = "field\0*.field\0";
				     op.nFilterIndex = 1;
				     op.lpstrFileTitle = NULL;
				     op.nMaxFileTitle = sizeof(SAVED_NAME);
				     op.lpstrInitialDir = NULL;
				     op.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
				     op.lStructSize = sizeof(op);
				     op.lpstrFile = SAVED_NAME;
				     op.lpstrTitle = "Open Field";
				      if(!GetOpenFileName(&op))
					  {
					  // Set Current Directory Back
                      SetCurrentDirectory(G_Directory);
				       return 0;
					  }
					  // Set Current Directory Back
                      SetCurrentDirectory(G_Directory);


					  // Delete Current Field
						G_App.DeleteAllBunkers();

					// Load New Field
					  G_App.LoadField(SAVED_NAME);

				    // Redraw Scene
					  G_App.ReCreateScene();

					  ToggleAll();

						G_File_Saved = true;

						// Select Move View Tool And Change View
						G_File_Opened = true;
						if (!ISREGISTERED())
						{
							SendMessage(G_PFDWindow.hWndToolbar, TB_CHECKBUTTON, G_CursorTool, FALSE);  // Uncheck Old Tool
							G_CursorTool = ID_MOVEVIEW;                                                 // Set Cursor Tool
							SendMessage(G_PFDWindow.hWndToolbar, TB_CHECKBUTTON, G_CursorTool, TRUE);   // Check New Tool
							UpdateWindow(G_PFDWindow.hWndToolbar);
						}
				  return (0);
				}break;

			   case ID_FILE_NEW:
				{
					if (!G_DLG7)
					{
					G_DLG7 = CreateDialog(G_hInst, MAKEINTRESOURCE(IDD_DIALOG7), G_PFDWindow.hWnd, (DLGPROC)DLG7Proc);
					ShowWindow(G_DLG7, SW_SHOW);
					}
					return (0);
				}break;

			   case ID_FILE_SAVE:
				{
                  if (ISREGISTERED())
				  {
						if (G_File_Saved)
						{
						G_App.SaveField(SAVED_NAME);
						}
						else
						{
					  // Is Registered
                    // Browse For File
				     ZeroMemory(SAVED_NAME, sizeof(SAVED_NAME));
				     ZeroMemory(&op, sizeof(op));
				     op.lStructSize = sizeof(op);
				     op.hwndOwner = hWnd;
				     op.nMaxFile = sizeof(SAVED_NAME);
				     op.lpstrFilter = "field\0*.field\0";
				     op.nFilterIndex = 1;
				     op.lpstrFileTitle = NULL;
				     op.nMaxFileTitle = sizeof(SAVED_NAME);
				     op.lpstrInitialDir = NULL;
				     op.Flags = OFN_PATHMUSTEXIST/*|OFN_OVERWRITEPROMPT*/;
				     op.lStructSize = sizeof(op);
				     op.lpstrFile = SAVED_NAME;
				     op.lpstrTitle = "Save Paintball Field";
				      if(!GetSaveFileName(&op))
					  {
					  // Set Current Directory Back
                      SetCurrentDirectory(G_Directory);
				       return 0;
					  }
					  // Set Current Directory Back
                      SetCurrentDirectory(G_Directory);

					  G_App.SaveField(SAVED_NAME);

                      G_File_Saved = true;
						}
				   }
				  else
				  {
					DEMOMESSAGE();
				  }
				  return 0;
				}break;

			   case ID_FILE_SAVEAS:
				{
                  if (ISREGISTERED())
				  {
					  // Is Registered
                    // Browse For File
				     ZeroMemory(SAVED_NAME, sizeof(SAVED_NAME));
				     ZeroMemory(&op, sizeof(op));
				     op.lStructSize = sizeof(op);
				     op.hwndOwner = hWnd;
				     op.nMaxFile = sizeof(SAVED_NAME);
				     op.lpstrFilter = "field\0*.field\0";
				     op.nFilterIndex = 1;
				     op.lpstrFileTitle = NULL;
				     op.nMaxFileTitle = sizeof(SAVED_NAME);
				     op.lpstrInitialDir = NULL;
				     op.Flags = OFN_PATHMUSTEXIST/*|OFN_OVERWRITEPROMPT*/;
				     op.lStructSize = sizeof(op);
				     op.lpstrFile = SAVED_NAME;
				     op.lpstrTitle = "Save Paintball Field";
				      if(!GetSaveFileName(&op))
					  {
					  // Set Current Directory Back
                      SetCurrentDirectory(G_Directory);
				       return 0;
					  }
					  // Set Current Directory Back
                      SetCurrentDirectory(G_Directory);

					  G_App.SaveField(SAVED_NAME);

                      G_File_Saved = true;
				  }
				  else
				  {
					DEMOMESSAGE();
				  }
				  return (0);
				}break;

			   case ID_FILE_FIELDKIT:
				{
                  if (ISREGISTERED())
				  {
					  // Is Registered
                    // Browse For File
				     ZeroMemory(File_Name, sizeof(File_Name));
				     ZeroMemory(&op, sizeof(op));
				     op.lStructSize = sizeof(op);
				     op.hwndOwner = hWnd;
				     op.nMaxFile = sizeof(File_Name);
				     op.lpstrFilter = "pfk\0*.pfk\0";
				     op.nFilterIndex = 1;
				     op.lpstrFileTitle = NULL;
				     op.nMaxFileTitle = sizeof(File_Name);
				     op.lpstrInitialDir = NULL;
				     op.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
				     op.lStructSize = sizeof(op);
				     op.lpstrFile = File_Name;
				     op.lpstrTitle = "Select The Paintball Field Kit File";
				      if(!GetOpenFileName(&op))
					  {
					  // Set Current Directory Back
                      SetCurrentDirectory(G_Directory);
				       return 0;
					  }
					  // Set Current Directory Back
                      SetCurrentDirectory(G_Directory);

					  G_FieldKit.Load(File_Name);
					  DrawFieldKit(G_PFDToolWindow.hWnd);
				  }
				  else
				  {
					DEMOMESSAGE();
				  }
				  return (0);
				}break;

			   case ID_FILE_EXIT:
				{
				G_Quit = true;
				PostMessage(hWnd, WM_QUIT, 0, 0); // Send A WM_QUIT Message
				}break;

			 // Edit
			   case ID_EDIT_DELETE:
				{
					G_App.DeleteSelectedObj();
				}break;

			   case ID_EDIT_SELECTNONE:
				{
					G_App.SelectNone();
				}break;

			   case ID_EDIT_MIRRORFIELD:
			    {
					if (G_App.MirrorBunkers() == false)
					{
						LOG("Failed To Mirror Field, Too Many Bunkers On Opposite Side Of Field");
					}
			    }break;

			   case ID_EDIT_RESIZEFIELD:
				{
					if (!G_DLG9)
					{
					G_DLG9 = CreateDialog(G_hInst, MAKEINTRESOURCE(IDD_DIALOG9), G_PFDWindow.hWnd, (DLGPROC)DLG9Proc);
					ShowWindow(G_DLG9, SW_SHOW);
					}
					return (0);
				}break;

			 // View
			   case ID_VIEW_TOP:
				{
/*
					MENUITEMINFO info;
					HMENU menu = GetMenu(hWnd);
					info.cbSize = sizeof(MENUITEMINFO);
					GetMenuItemInfo(menu, lastviewmode, false, &info);
					info.fState = MFS_UNCHECKED|ENABLED;
					SetMenuItemInfo(menu, lastviewmode, false, &info);

					info.cbSize = sizeof(MENUITEMINFO);
					GetMenuItemInfo(menu, ID_VIEW_TOP, false, &info);
					info.fState = MFS_CHECKED|MFS_ENABLED;
					SetMenuItemInfo(menu, ID_VIEW_TOP, false, &info);
*/
				  G_App.SaveCurrentView();
		          G_ViewMode = TOP; // Set View Mode To Top
				  G_App.LookView();

				lastviewmode = ID_VIEW_TOP;
				}break;

			   case ID_VIEW_FIRSTPERSON:
				{
				  G_App.SaveCurrentView();
		          G_ViewMode = FIRSTPERSON; // Set View Mode To FirstPerson
				  G_App.LookView();

				lastviewmode = ID_VIEW_FIRSTPERSON;
				}break;

			   case ID_VIEW_PERSPECTIVE:
				{
				  G_App.SaveCurrentView();
		          G_ViewMode = PERSPECTIVE; // Set View Mode To Perspective
				  G_App.LookView();

				lastviewmode = ID_VIEW_PERSPECTIVE;
				}break;

			   case ID_VIEW_RESETVIEW:
				{
				  G_App.ResetView();
				}break;

			   case ID_VIEW_OPTIONS:
				{
					HWND hCheck = NULL;

					if (!G_DLG2)
					{
					G_DLG2 = CreateDialog(G_hInst, MAKEINTRESOURCE(IDD_DIALOG2), G_PFDWindow.hWnd, (DLGPROC)DLG2Proc);
					
					hCheck = GetDlgItem(G_DLG2, IDC_CHECK1);
					PostMessage(hCheck, BM_SETCHECK,G_ViewOptions._terrain,0);

					hCheck = GetDlgItem(G_DLG2, IDC_CHECK2);
					PostMessage(hCheck, BM_SETCHECK,G_ViewOptions._yardlines,0);

					hCheck = GetDlgItem(G_DLG2, IDC_CHECK3);
					PostMessage(hCheck, BM_SETCHECK,G_ViewOptions._skybox,0);

					hCheck = GetDlgItem(G_DLG2, IDC_CHECK4);
					PostMessage(hCheck, BM_SETCHECK,G_ViewOptions._fiftyyardline,0);

					hCheck = GetDlgItem(G_DLG2, IDC_CHECK5);
					PostMessage(hCheck, BM_SETCHECK,G_ViewOptions._shadows,0);

					hCheck = GetDlgItem(G_DLG2, IDC_CHECK6);
					PostMessage(hCheck, BM_SETCHECK,G_ViewOptions._gouraud,0);

					hCheck = GetDlgItem(G_DLG2, IDC_CHECK7);
					PostMessage(hCheck, BM_SETCHECK,G_ViewOptions._texture,0);

					hCheck = GetDlgItem(G_DLG2, IDC_CHECK8);
					PostMessage(hCheck, BM_SETCHECK,G_ViewOptions._solid,0);

					hCheck = GetDlgItem(G_DLG2, IDC_CHECK9);
					PostMessage(hCheck, BM_SETCHECK,G_ViewOptions._centeryardline,0);

					ShowWindow(G_DLG2, SW_SHOW);
					}
				}break;

			 // Render
			   case ID_RENDER_TOFILE:
				{
                  if (ISREGISTERED())
				  {
					  // Is Registered
                    // Browse For File
				     ZeroMemory(File_Name, sizeof(File_Name));
				     ZeroMemory(&op, sizeof(op));
				     op.lStructSize = sizeof(op);
				     op.hwndOwner = hWnd;
				     op.lpstrFile = File_Name;
				     op.lpstrFile[0] = '\0';
				     op.nMaxFile = sizeof(File_Name);
				     op.lpstrFilter = "bmp\0*.bmp";
				     op.nFilterIndex = 1;
				     op.lpstrFileTitle = NULL;
				     op.nMaxFileTitle = sizeof(File_Name);
				     op.lpstrInitialDir = NULL;
				     op.Flags = OFN_PATHMUSTEXIST;
				     op.lStructSize = sizeof(op);
				     op.lpstrFile = File_Name;
				     op.lpstrTitle = "Save Screenshot";
				      if(!GetSaveFileName(&op))
					  {
				       return 0;
					  }
					  // Set Current Directory Back
                      SetCurrentDirectory(G_Directory);

						// If .field is not in file, name add it
							string name = File_Name;
							if (string::npos == name.find(".bmp"))
							name += ".bmp";

							G_App.TakeScreenShot(name.c_str());
				   }
				  else
				  {
					DEMOMESSAGE();
				  }
				}break;

			 // About
			   case ID_ABOUT_HELP:
				{
				string tmp = "hh.exe paintballfieldbuilder.chm";
				WinExec(tmp.c_str(),SW_MAXIMIZE);
				}break;

			   case ID_ABOUT_OGREINFO:
				{
					if (!G_DLG3)
					{
					G_DLG3 = CreateDialog(G_hInst, MAKEINTRESOURCE(IDD_DIALOG3), G_PFDWindow.hWnd, (DLGPROC)DLG3Proc);
					ShowWindow(G_DLG3, SW_SHOW);
					}
				}break;

			   case ID_ABOUT_PFBINFO:
				{
					if (!G_DLG4)
					{
					G_DLG4 = CreateDialog(G_hInst, MAKEINTRESOURCE(IDD_DIALOG4), G_PFDWindow.hWnd, (DLGPROC)DLG4Proc);
					ShowWindow(G_DLG4, SW_SHOW);
					}
				}break;

			   case ID_ABOUT_REGISTER:
				{
					if (ISREGISTERED())
					{
						LOG("Software Is Already Registered");
					}
					else
					{
						if (!G_DLG5)
						{
						StartClient(G_hInst, MAKEINTRESOURCE(IDD_DIALOG5), G_PFDWindow.hWnd, G_DLG5);
						ShowWindow(G_DLG5, SW_SHOW);
						}
					}
				}break;

		       // TOoLBARS
			   case ID_MOVEOBJ:
				{
					if (!ISREGISTERED() && G_File_Opened)
					{
						ERRORM("Cannot Modify A Field That You Opened With The Trial Version");
						return 0;
					}
		          SendMessage(G_PFDWindow.hWndToolbar, TB_CHECKBUTTON, G_CursorTool, FALSE);  // Uncheck Old Tool
		          G_CursorTool = ID_MOVEOBJ;                                                  // Set Cursor Tool
		          SendMessage(G_PFDWindow.hWndToolbar, TB_CHECKBUTTON, G_CursorTool, TRUE);   // Check New Tool
	              UpdateWindow(G_PFDWindow.hWndToolbar);                                      // Update Window
				}break;

			   case ID_ROTATEOBJ:
				{
					if (!ISREGISTERED() && G_File_Opened)
					{
						ERRORM("Cannot Modify A Field That You Opened With The Trial Version");
						return 0;
					}
		          SendMessage(G_PFDWindow.hWndToolbar, TB_CHECKBUTTON, G_CursorTool, FALSE);  // Uncheck Old Tool
		          G_CursorTool = ID_ROTATEOBJ;                                                // Set Cursor Tool
		          SendMessage(G_PFDWindow.hWndToolbar, TB_CHECKBUTTON, G_CursorTool, TRUE);   // Check New Tool
	              UpdateWindow(G_PFDWindow.hWndToolbar);                                      // Update Window
				}break;

			   case ID_SELECT:
				{
					if (!ISREGISTERED() && G_File_Opened)
					{
						ERRORM("Cannot Modify A Field That You Opened With The Trial Version");
						return 0;
					}
		          SendMessage(G_PFDWindow.hWndToolbar, TB_CHECKBUTTON, G_CursorTool, FALSE);  // Uncheck Old Tool
		          G_CursorTool = ID_SELECT;                                                   // Set Cursor Tool
		          SendMessage(G_PFDWindow.hWndToolbar, TB_CHECKBUTTON, G_CursorTool, TRUE);   // Check New Tool
	              UpdateWindow(G_PFDWindow.hWndToolbar);                                      // Update Window
				}break;

			   case ID_CREATEOBJ:
				{
					if (!ISREGISTERED() && G_File_Opened)
					{
						ERRORM("Cannot Modify A Field That You Opened With The Trial Version");
						return 0;
					}
		          SendMessage(G_PFDWindow.hWndToolbar, TB_CHECKBUTTON, G_CursorTool, FALSE);  // Uncheck Old Tool
		          G_CursorTool = ID_CREATEOBJ;                                                // Set Cursor Tool
		          SendMessage(G_PFDWindow.hWndToolbar, TB_CHECKBUTTON, G_CursorTool, TRUE);   // Check New Tool
	              UpdateWindow(G_PFDWindow.hWndToolbar);                                      // Update Window
				}break;

			   case ID_CLONEOBJ:
				{
					if (!ISREGISTERED() && G_File_Opened)
					{
						ERRORM("Cannot Modify A Field That You Opened With The Trial Version");
						return 0;
					}
		          SendMessage(G_PFDWindow.hWndToolbar, TB_CHECKBUTTON, G_CursorTool, FALSE);  // Uncheck Old Tool
		          G_CursorTool = ID_CLONEOBJ;                                                 // Set Cursor Tool
		          SendMessage(G_PFDWindow.hWndToolbar, TB_CHECKBUTTON, G_CursorTool, TRUE);   // Check New Tool
	              UpdateWindow(G_PFDWindow.hWndToolbar);                                      // Update Window
				}break;

			   case ID_MOVEVIEW:
				{
		          SendMessage(G_PFDWindow.hWndToolbar, TB_CHECKBUTTON, G_CursorTool, FALSE);  // Uncheck Old Tool
		          G_CursorTool = ID_MOVEVIEW;                                                 // Set Cursor Tool
		          SendMessage(G_PFDWindow.hWndToolbar, TB_CHECKBUTTON, G_CursorTool, TRUE);   // Check New Tool
	              UpdateWindow(G_PFDWindow.hWndToolbar);                                      // Update Window
				}break;

			   case ID_ROTATEVIEW:
				{
		          SendMessage(G_PFDWindow.hWndToolbar, TB_CHECKBUTTON, G_CursorTool, FALSE);  // Uncheck Old Tool
		          G_CursorTool = ID_ROTATEVIEW;                                               // Set Cursor Tool
		          SendMessage(G_PFDWindow.hWndToolbar, TB_CHECKBUTTON, G_CursorTool, TRUE);   // Check New Tool
	              UpdateWindow(G_PFDWindow.hWndToolbar);                                      // Update Window
				}break;
				// End Of ToolBar
			}
		}break;

	case WM_KEYDOWN:
		{
			switch (wParam)
			{
			   case VK_ESCAPE:
				   {
						G_Quit = true;
				    	PostMessage(hWnd, WM_QUIT, 0, 0);
				    	return 0;
				   }break;

			   case VK_DELETE:
				   {
				    	G_App.DeleteSelectedObj();
				    	return 0;
				   }break;

			   case VK_UP:
				   {
					   return 0;
				   }break;

			   case VK_DOWN:
				   {
					   return 0;
				   }break;

			   case VK_LEFT:
				   {
						G_App.RotateSelectedObj(-5.00f, 0);
					   return 0;
				   }break;

			   case VK_RIGHT:
				   {
						G_App.RotateSelectedObj(5.00f, 0);
					   return 0;
				   }break;
			}
		}break;

	case WM_SIZE:
		{
		  unsigned int width = LOWORD(lParam);   // width of client area
		  unsigned int height = HIWORD(lParam);  // height of client area

	      // Rezize/Draw Tool Window
           //G_PFDToolWindow.width = width/5;
           G_PFDToolWindow.height = height-50;
           G_PFDToolWindow.MoveCTWindow(true);

	      // Rezize/Draw Edit/View Window
           G_PFDEditWindow.width = (width-G_PFDToolWindow.width)-18;
           G_PFDEditWindow.height = height-50;
           G_PFDEditWindow.MoveCTWindow(true);
		}break;

	case WM_MOVE:
		{
		  unsigned int x = LOWORD(lParam);   // x of window pos
		  unsigned int y = HIWORD(lParam);  // y of window pos

	      // Rezize/Draw Tool Window
           G_PFDWindow.xpos = x;
           G_PFDWindow.ypos = y;
		}break;

    default:
		{
        // Process the left-over messages
        return DefWindowProc(hWnd, msg, wParam, lParam);
		}break;
  }
return 0;
}


LRESULT CALLBACK PFDEditProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  switch(msg)
  {
    case WM_CLOSE:
		{
		PostMessage(hWnd, WM_QUIT, 0, 0); // Send A WM_QUIT Message
		}break;

	case WM_CREATE:
		{
			SendMessage(hWnd, WM_PAINT, 0, 0);
		}break;
/*
	case WM_PAINT:
		{
		//_RENDER(G_App);
		DrawNothing(hWnd);
		}break;
*/
	case WM_LBUTTONDOWN:
		{
		if (GetAsyncKeyState(VK_LBUTTON))
		{
		   if (G_FirstLeftClick)
		   {
			TryCreateFunctions();
           G_FirstLeftClick = false;
		   }
		}
		}break;
/*
	case WM_LBUTTONUP:
		{
		if (!GetAsyncKeyState(VK_LBUTTON))
           G_FirstLeftClick = true;
		}break;
*/
	case WM_RBUTTONDOWN:
		{
		if (GetAsyncKeyState(VK_RBUTTON))
		{
			if (G_FirstRightClick)
			{
				G_App.SelectNone();
				G_FirstRightClick = false;
			}
		}
		}break;

	case WM_MOUSEMOVE:
		{
          WORD xPos = LOWORD(lParam);  // horizontal position of cursor 
          WORD yPos = HIWORD(lParam);  // vertical position of cursor
		  static WORD last_xPos = NULL, last_yPos = NULL;

          if (GetAsyncKeyState(VK_LBUTTON))
		  {
		  Real xForce = (Real) (((Real)xPos-(Real)last_xPos)/*1.5f*/);
		  Real yForce = (Real) (((Real)yPos-(Real)last_yPos)/*1.5f*/);
		  G_MouseX = ((Real)xPos/G_PFDEditWindow.width);
		  G_MouseY = ((Real)yPos/G_PFDEditWindow.height);
		  if ((last_xPos == xPos) && (last_yPos == yPos))
			  break;
		  last_xPos = xPos;
		  last_yPos = yPos;

			UpdateMousePos(true);
			if (G_MouseX <= G_PFDEditWindow.xpos)
				break;

			UpdateMousePos(false); // Get Mouse Position Relitive To The Window

		  if (xForce > MAX_FORCE)
		  xForce = MAX_FORCE;
		  if (yForce > MAX_FORCE)
		  yForce = MAX_FORCE;

		  if (xForce < MAX_FORCE*-1)
		  xForce = MAX_FORCE*-1;
		  if (yForce < MAX_FORCE*-1)
		  yForce = MAX_FORCE*-1;

		  static DWORD lastmove = 0;
		  if (GetTickCount() > lastmove+50)
		  {
			  xForce = NULL;
			  yForce = NULL;
		  }
		  lastmove = GetTickCount();

		if (G_Dragging)
		{
			if (G_Dragging == 1)
			{
				G_App.CreateObject(G_MouseX, G_MouseY);
				G_Dragging = 2;
			}
			else if (G_Dragging == 2)
			{
			  G_App.MoveSelectedObj(G_MouseX, G_MouseY);
			}
		}
		else
		{
			if (G_FirstLeftClick)
			{
				TryCreateFunctions();
				G_FirstLeftClick = false;
			}

			  if (G_CursorTool == ID_ROTATEOBJ)
			  G_App.RotateSelectedObj(xForce, yForce);
			  else if ( (G_CursorTool == ID_MOVEOBJ) || (G_CursorTool == ID_CLONEOBJ) || (G_CursorTool == ID_CREATEOBJ))
			  G_App.MoveSelectedObj(G_MouseX, G_MouseY);
			  else if (G_CursorTool == ID_ROTATEVIEW)
			  {
				if (xForce > MAX_FORCE/4)
				xForce = MAX_FORCE/4;
				if (yForce > MAX_FORCE/4)
				yForce = MAX_FORCE/4;

				if (xForce < MAX_FORCE/-4)
				xForce = MAX_FORCE/-4;
				if (yForce < MAX_FORCE/-4)
				 yForce = MAX_FORCE/-4;

			  G_App.RotateView(xForce, yForce);
			  }
			  else if (G_CursorTool == ID_MOVEVIEW)
			  {
				if (xForce > MAX_FORCE/4)
				xForce = MAX_FORCE/4;
				if (yForce > MAX_FORCE/4)
				yForce = MAX_FORCE/4;

				if (xForce < MAX_FORCE/-4)
				xForce = MAX_FORCE/-4;
				if (yForce < MAX_FORCE/-4)
				 yForce = MAX_FORCE/-4;
			  G_App.MoveView(xForce, yForce);
			  }
		}
		  }
		  else if (GetAsyncKeyState(VK_RBUTTON))
		  {
		  Real xForce = (Real) (((Real)xPos-(Real)last_xPos)/*1.5f*/);
		  Real yForce = (Real) (((Real)yPos-(Real)last_yPos)/*1.5f*/);
		  G_MouseX = ((Real)xPos/G_PFDEditWindow.width);
		  G_MouseY = ((Real)yPos/G_PFDEditWindow.height);
		  if ((last_xPos == xPos) && (last_yPos == yPos))
			  break;
		  last_xPos = xPos;
		  last_yPos = yPos;

			UpdateMousePos(true);
			if (G_MouseX <= G_PFDEditWindow.xpos)
				break;

			UpdateMousePos(false); // Get Mouse Position Relitive To The Window

		  if (xForce > MAX_FORCE)
		  xForce = MAX_FORCE;
		  if (yForce > MAX_FORCE)
		  yForce = MAX_FORCE;

		  if (xForce < MAX_FORCE*-1)
		  xForce = MAX_FORCE*-1;
		  if (yForce < MAX_FORCE*-1)
		  yForce = MAX_FORCE*-1;

				if (xForce > MAX_FORCE/4)
				xForce = MAX_FORCE/4;
				if (yForce > MAX_FORCE/4)
				yForce = MAX_FORCE/4;

				if (xForce < MAX_FORCE/-4)
				xForce = MAX_FORCE/-4;
				if (yForce < MAX_FORCE/-4)
				 yForce = MAX_FORCE/-4;
			  G_App.MoveView(xForce, yForce);

				G_Dragging = 0;
		  }
		}break;

    default:
		{
        // Process the left-over messages
        return DefWindowProc(hWnd, msg, wParam, lParam);
		}break;
  }
return 0;
}

void SetScrollBar(HWND hWnd)
{
	int x = G_PFDToolWindow.height-(10+(G_FieldKit.GetBunkerCount()*(128+10))); //
	int max = (10+(G_FieldKit.GetBunkerCount()*(128+10))); // 

				if (G_BunkerScroll <= x)
					G_BunkerScroll = x;
				if (G_BunkerScroll >= 1)
					G_BunkerScroll = 1;

				SCROLLINFO si; 
				si.cbSize = sizeof(si); 
				si.fMask  = SIF_ALL|SIF_DISABLENOSCROLL; 
				si.nMin   = 1; 
				si.nMax   = max; 
				si.nPage  = G_PFDToolWindow.height; 
				si.nPos = G_BunkerScroll*-1;
				si.nTrackPos = G_BunkerScroll*-1;
				SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
}

void GetScrollBar(HWND hWnd)
{
	int x = G_PFDToolWindow.height-(10+(G_FieldKit.GetBunkerCount()*(128+10))); //
	int max = (10+(G_FieldKit.GetBunkerCount()*(128+10))); // 

				SCROLLINFO si; 
				si.cbSize = sizeof(si); 
				si.fMask  = SIF_TRACKPOS; 
				GetScrollInfo(hWnd, SB_VERT, &si); 
				si.fMask  = SIF_POS; 
				si.nPos = si.nTrackPos;
				SetScrollInfo(hWnd, SB_VERT, &si, TRUE);

				G_BunkerScroll = si.nTrackPos*-1;

				if (G_BunkerScroll <= x)
					G_BunkerScroll = x;
				if (G_BunkerScroll >= 1)
					G_BunkerScroll = 1;
}

LRESULT CALLBACK PFDToolProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  switch(msg)
  {
    case WM_CLOSE:
	{
		PostMessage(hWnd, WM_QUIT, 0, 0); // Send A WM_QUIT Message
	}break;

	case WM_CREATE:
		{
		SendMessage(hWnd, WM_PAINT, 0, 0);
		}break;

	case WM_SIZE:
		{
		   G_BunkerScroll = 1;
			SetScrollBar(hWnd);
		}break;

    case WM_VSCROLL: 
		{ 
        switch (LOWORD(wParam)) 
        { 
            // User clicked the scroll bar shaft above the scroll box. 
            case SB_PAGEUP: 
				G_BunkerScroll += 20;

				SetScrollBar(hWnd);
				DrawFieldKit(hWnd);
                break; 
 
            // User clicked the scroll bar shaft below the scroll box. 
            case SB_PAGEDOWN: 
				G_BunkerScroll -= 20;

				SetScrollBar(hWnd);
				DrawFieldKit(hWnd);
                break; 
 
            // User clicked the top arrow. 
            case SB_LINEUP: 
				G_BunkerScroll += 10;

				SetScrollBar(hWnd);
				DrawFieldKit(hWnd);
                break; 
 
            // User clicked the bottom arrow. 
            case SB_LINEDOWN: 
				G_BunkerScroll -= 10;

				SetScrollBar(hWnd);
				DrawFieldKit(hWnd);
                break; 
 
            // User dragged the scroll box. 
            case SB_THUMBPOSITION: 
				GetScrollBar(hWnd);
				DrawFieldKit(hWnd);
                break; 
 
            default:
				break;
        } 
		} break; 


	case WM_PAINT:
		{
		 DrawFieldKit(G_PFDToolWindow.hWnd);
		}break;

	case WM_LBUTTONDOWN:
		{
					if (!ISREGISTERED() && G_File_Opened)
					{
						ERRORM("Cannot Modify A Field That You Opened With The Trial Version");
						return 0;
					}

		if (GetAsyncKeyState(VK_LBUTTON))
		{
		   if (G_FirstLeftClick)
		   {
				    	UpdateMousePos(true);
						G_MouseX -= G_PFDWindow.xpos+G_PFDToolWindow.xpos;
						G_MouseY -= G_PFDWindow.ypos+G_PFDToolWindow.ypos;

						if ((G_MouseY > 10))
						if ((G_MouseX > 10) && (G_MouseX < 128+20))
						{
							for (int x = 0; x < (int)G_FieldKit.GetBunkerCount(); x++)
							{
									if ((G_MouseY > G_BunkerScroll+10+(x*(128+10))) && (G_MouseY < (G_BunkerScroll+10+(x*(128+10)))+128))
									{
										G_Bunker = (BunkerID)x;
										DrawFieldKit(hWnd);
										break;
									}
							}
						}
			G_Dragging = 1;
			G_FirstLeftClick = false;
		   }
		}
		else
		{
			G_Dragging = 0;
		}

		}break;

    default:
		{
        // Process the left-over messages
        return DefWindowProc(hWnd, msg, wParam, lParam);
		}break;
  }
return 0;
}

bool PFB_LoadTheUserKey(void)
{
bool ret = false;
	SetCurrentDirectory(G_Directory);
  // Check For Valid USERKEY
	LSDATA userkey;
	if (userkey.LoadUserKey())
	{
		// Valid User Key
		if (userkey.ValidateUserKey())
		G_SOFTWARE_REGISTERED = true;

	ret = true;
	}
	else
	{
	ret = false;
	}
	return ret;
}


string BackDir(const string dir, const int back)
{
 string tmp;
 int count = 0;
 tmp += dir;
for (size_t x = tmp.length(); x > 1; x--)
{
	if ((tmp[x] != '/') && (tmp[x] != 92)) // Cant Have \ or /
	{
		// Do Nothing
		tmp[x] = 0;
	}
	else
	{
		tmp[x] = 0;
		count++;
		//if (count >= back)
		//{
			x = 0;
			break;
		//}
	}
}
return tmp;
}


bool IsHomeDir(void)
{
	FILE *f = NULL;
	f = fopen("Paintball Field Builder.exe", "rb");
	if (f)
	{
		fclose(f);
		return true;
	}
	return false;
}

bool FindHomeDir(void)
{
  // Try Default
	memset(G_Directory, NULL, sizeof(G_Directory));
   GetCurrentDirectory(sizeof(G_Directory), G_Directory);
   SetCurrentDirectory(G_Directory);
   if (IsHomeDir() == true)
	   return true;

   // Try Another
	memset(G_Directory, NULL, sizeof(G_Directory));
	strcpy(G_Directory, "C:/Program Files/Hyperformance Paintball LLC/Paintball Field Builder/bin");
   SetCurrentDirectory(G_Directory);
   if (IsHomeDir() == true)
	   return true;

   // Maybe Later Search For It

return false;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
 G_hInst = hInstance;

  // Get Directory
   if (FindHomeDir() == false)
   {
	   LOG("Failed To Find Paintball Field Builder Directory");
	   return 1;
   }
	string tmp;
	tmp += BackDir(G_Directory, 1) + string("fieldkits");
	strcpy(G_FieldKit_Path, tmp.c_str());

G_Log.Init(true);
 SLOG("Paintball Field Builder Started");
 SLOG("Found Home Dir");

  // Check For Valid USERKEY
	PFB_LoadTheUserKey();

if (ISREGISTERED())
 SLOG("Software Is Registered");
else
 SLOG("Software Is Running In Trial Mode");

#ifdef LOADSCREEN
   // Show LoadScreen
	HWND dialoghandle = 0;
if (ISREGISTERED())
{
    dialoghandle = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)NULL);
    Wait(3000);
}
else
{
    dialoghandle = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG6), NULL, (DLGPROC)NULL);
    Wait(8000);
}
#endif

#ifdef LOADSCREEN
  // End Load Screen
    EndDialog(dialoghandle, true);
#endif

G_ViewOptions._terrain = false;
G_ViewOptions._yardlines = true;
G_ViewOptions._skybox = false;
G_ViewOptions._fiftyyardline = true;
G_ViewOptions._shadows = false;
G_ViewOptions._gouraud = true;
G_ViewOptions._texture = true;
G_ViewOptions._solid = true;
G_ViewOptions._centeryardline = true;
 SLOG("View Settings Were Set");

 // Create Main Window
  G_PFDWindow.CreateCTWindow(hInstance, PFDProc);
 SLOG("The Main Window Was Created");

 // Create Edit/View Window
  G_PFDEditWindow.hParent = G_PFDWindow.hWnd;
  G_PFDEditWindow.CreateCTWindow(hInstance, PFDEditProc);
 SLOG("The Edit Window Was Created");

 // Create Tool Window
  G_PFDToolWindow.hParent = G_PFDWindow.hWnd;
  G_PFDToolWindow.CreateCTWindow(hInstance, PFDToolProc);
 SLOG("The Field Kit Window Was Created");

   // Initialize OGRE
    try {
        G_App.go();
		SLOG("OGRE WAS INITIALIZED");
    } catch( Ogre::Exception& e ) {
      ERRORMESSAGE(e.getFullDescription().c_str());
		SLOG("OGRE FAILED TO INITILISE");
		return 1;
    }

  // Load Field Kit(s) in the fieldkits folder
		SetCurrentDirectory(G_FieldKit_Path);
		LoadFieldKits_InFolder(G_FieldKit_Path);
		SetCurrentDirectory(G_Directory);
		SLOG("Loaded All Of The Field Kits");
G_FieldKit.Load("../fieldkits/default.pfk");
SLOG("Loaded The Default Field Kit");

	// Start Rendering
	G_Render = true;

	ToggleAll();

	G_App.LookView();
	_RENDER(G_App);
	SetActiveWindow(G_PFDToolWindow.hWnd);
	DrawFieldKit(G_PFDToolWindow.hWnd);
SLOG("Setup View and Draw Field Kit");

	// Check For Command Line
	if (lpCmdLine && (strlen(lpCmdLine) >= 3)  && ISREGISTERED())
	{
		string a;
		a.clear();
		
		SLOG("Recieved Command From Command Line");

		for (size_t x = 0; x < strlen(lpCmdLine); x++)
		{
			if (lpCmdLine[x] != '"')
			a += lpCmdLine[x];
		}
		if (string::npos != a.find(".field"))
		{
					// Set Current Directory Back
						SetCurrentDirectory(G_Directory);
					// Delete Current Field
						G_App.DeleteAllBunkers();
					// Load New Field
						G_App.LoadField(a);
				    // Redraw Scene
						G_App.ReCreateScene();
						ToggleAll();
						_RENDER(G_App);
		SLOG("Loaded A Field Through Command Line");
		}
		else if (string::npos != a.find(".pfk"))
		{
				// Set Current Directory Back
					SetCurrentDirectory(G_Directory);
					G_FieldKit.Load(a.c_str());
					DrawFieldKit(G_PFDToolWindow.hWnd);
		SLOG("Loaded A Fieldkit through commandline");
		}
	}

		SetActiveWindow(G_PFDWindow.hWnd);

		SetCursor(LoadCursor(NULL, IDC_ARROW));

		SLOG("PFB Completed Initialization");

   // Main Loop
	while (G_Quit != true)
	{
		if (!GetAsyncKeyState(VK_LBUTTON) && !G_FirstLeftClick)
		{
		G_Dragging = 0;
         G_FirstLeftClick = true;
			  if (G_CursorTool == ID_CREATEOBJ)
			  {
				  G_App.SelectNone();
			  }
		}
		if (!GetAsyncKeyState(VK_RBUTTON) && !G_FirstRightClick)
		{
         G_FirstRightClick = true;
		}
		if (GetAsyncKeyState(VK_UP))
		{
			G_App.MoveView(0, 0, 1);
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			G_App.MoveView(0, 0, -1);
		}


		// Do Not Let Them Take Screenshots
		if (ISREGISTERED() == false)
		{
			if (GetAsyncKeyState(VK_SNAPSHOT))
			{
				Wait(1000);
                if(OpenClipboard(G_PFDWindow.hWnd))
				{
				EmptyClipboard();
				}

				while(GetAsyncKeyState(VK_SNAPSHOT)) NULL;
				Wait(1000);
                if(OpenClipboard(G_PFDWindow.hWnd))
				{
				EmptyClipboard();
				}
			}
		}

      // Handle Windows Messages
	   G_PFDWindow.HandleMessages();
	   G_PFDEditWindow.HandleMessages();
	   G_PFDToolWindow.HandleMessages();
      // Handle Dialog Message
	   if (G_DLG2)
	   {
       HandleMessagesDLG(G_DLG2);
	   }
	   if (G_DLG3)
	   {
       HandleMessagesDLG(G_DLG3);
	   }
	   if (G_DLG4)
	   {
       HandleMessagesDLG(G_DLG4);
	   }
	   if (G_DLG5)
	   {
       HandleMessagesDLG(G_DLG5);
	   }
	   if (G_DLG7)
	   {
       HandleMessagesDLG(G_DLG7);
	   }
	   if (G_DLG8)
	   {
       HandleMessagesDLG(G_DLG8);
	   }
	   if (G_DLG9)
	   {
       HandleMessagesDLG(G_DLG9);
	   }

	   if (G_PFDWindow.GetMessage() == WM_QUIT)
		   G_Quit = true;
	}
SLOG("PFB Shutting Down");
	// Stop Rendering
	G_Render = false;

	// Save Recovery File
		G_App.SaveField(string(TMPDIR) + string("recovery.field"));
SLOG("Field Was Saved");

// De-Initialize OGRE
	G_App.stop();
SLOG("OGRE WAS SHUT DOWN");

// Clean Up Windows
 G_PFDEditWindow.DestroyCTWindow();
 G_PFDWindow.DestroyCTWindow();
 G_PFDToolWindow.DestroyCTWindow();
SLOG("Windows Were Shut Down");

 if (G_Restart == true)
 {
SLOG("Restart Was Enabled");
	SetCurrentDirectory(G_Directory);
	WinExec("Paintball Field Builder.exe",SW_MAXIMIZE);
 }

SLOG("PFB ShutDown");

 return 0;
}
