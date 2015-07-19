/**---------------------------------------------------------
 * @author: David Whiteside
 * @date: 09/20/09
 * @description: The Main Field Kit Management Class
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

#include "../inc/FieldKit.h"
#include "../inc/main.h"


CFieldKit::CFieldKit(String file)
{
    this->CleanUp();
    m_LoadedFieldKitsCount = NULL;

    if (file.size()) {
        this->Load(file);
    }
}

CFieldKit::~CFieldKit(void)
{
    this->CleanUp();
    m_LoadedFieldKits.clear();
    m_LoadedFieldKitsCount = NULL;
}

bool CFieldKit::Load(String file)
{
    FILEDATA *data = NULL;                          //
    size_t dataLen = NULL;                  //

    SEARCHMODE sfmode = SM_NAME;    //
    SEARCHMODE last_sfmode = SM_MODEL_NAME; //
    BYTE sf_colancount = NULL;              //
    unsigned int x = NULL, i = NULL;                        // Keeps Track Of Element For sf
    Bunker tbunker;

    const String str = file;
    const String str2 = "info.txt";
    const String str3 = "zip";
    ZipArchive zip(str, str3);

    this->CleanUp();
//	SetCurrentDirectory(G_Directory);     ------------------------------ TEST TEST TSET STSET BAD ABDA ABAD SADS D FFI FIX FIX

    try {
        if (this->AlreadyLoaded(file) == false) {
            ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
            ResourceGroupManager::getSingleton().addResourceLocation(file, "Zip", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, true);
            ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
        }
        zip.load();
        DataStreamPtr ptr = zip.open(str2);
// Load The File Into Memory
        dataLen = ::LoadFileD(ptr, data);
    } catch (Ogre::Exception ex) {
        PFB_LOG("Failed To Load Field Kit");
        return false;
    }


    if (!dataLen || !data) {
        PFB_LOG("Failed To Load Config File");
        return false;
    }


// Parse Config File
    BYTE semis = 0;
    for(x = 0; x < dataLen; x++) {
        switch (data[x]) {
        case ':': { // Colan
            semis++;
        }
        break;

        default: { // Something Else
            if (semis == 1) {
                this->m_Version += data[x];

                if (strcmp(this->m_Version.c_str(), FIELDKITVER)) {
                    PFB_LOG("Failed Because Of Incorrect Version");
                    SAFE_DELETEA(data);
                    return false;
                }
            } else if (semis == 3) {
                this->m_GeneratedBy += data[x];
            } else if (semis == 5) {
                this->m_Credit += data[x];
            } else if (semis == 7) {
                this->m_Copyright += data[x];
            }
        }
        break;
        }
    }

// Parse Config File
    for(x = 0; x < dataLen; x++) {
        switch (data[x]) {
        case '>': { // Carrage Return
            if (sf_colancount != 3) {
                PFB_LOG("Failed Because Of Incorrect Format");
                SAFE_DELETEA(data);
                return false;
            }

            sf_colancount = NULL; // Reset Count

            last_sfmode = sfmode;
            sfmode = SM_NAME;

            // Save The bitmap(s) to Temp Directory and Load the bitmap(s) from file
            String tmp = String(TMPDIR) + tbunker.image_name;
            WriteFileD(tmp, zip.open(tbunker.image_name));
            //tbunker.bmp = (HBITMAP)LoadImage (0, tmp.c_str(), IMAGE_BITMAP, 0, 0, LR_SHARED|LR_VGACOLOR|LR_DEFAULTCOLOR|LR_LOADFROMFILE);
            tbunker.bmp = new wxBitmap( wxImage(tmp.c_str()) );

            // Save Script And Parse
            if (this->AlreadyLoaded(file) == false) {
                String mat = String(TMPDIR) + String(tbunker.material_name);
                FILEDATA *buf = NULL;
                MemoryDataStream *ds = NULL;
                try {
                    WriteFileD(mat, zip.open(tbunker.material_name));
                    DWORD len = LoadFile(mat.c_str(), buf);
                    ds = new MemoryDataStream(buf, len);
                    DataStreamPtr dsp(ds);
                    MaterialManager::getSingleton().parseScript(dsp, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
                } catch (Ogre::Exception ex) {
                }
                SAFE_DELETEA(buf);
                //SAFE_DELETEA(ds);
                //DeleteFile(mat.c_str());
            }

            // Save In Bunker List
            this->m_Bunkers.push_back(tbunker);
            this->m_BunkerCount++;
            i++;

            //Clean tbunker
            tbunker.name.clear();
            tbunker.image_name.clear();
            tbunker.model_name.clear();
            tbunker.material_name.clear();
            tbunker.bmp = NULL;

            if (last_sfmode != SM_MATERIAL_NAME) {
                PFB_LOG("Last Mode Was Not SM_MATERIAL_NAME, Config File Is Corrupt");
                SAFE_DELETEA(data);
                return false;
            }
        }
        break;

        case '<': { // Begin
            last_sfmode = sfmode;
            sfmode = SM_NAME;

            if (last_sfmode != SM_NAME) {
                PFB_LOG("Last Mode Was Not SM_NAME, Config File Is Corrupt");
                SAFE_DELETEA(data);
                return false;
            }
        }
        break;

        case ',': { // Cama
            if (sf_colancount == NULL) {
                last_sfmode = sfmode;
                sfmode = SM_IMAGE_NAME;

                if (last_sfmode != SM_NAME) {
                    PFB_LOG("Last Mode Was Not SM_NAME, Config File Is Corrupt");
                    SAFE_DELETEA(data);
                    return false;
                }
            }
            if (sf_colancount == 1) {
                last_sfmode = sfmode;
                sfmode = SM_MODEL_NAME;

                if (last_sfmode != SM_IMAGE_NAME) {
                    PFB_LOG("Last Mode Was Not SM_IMAGE_NAME, Config File Is Corrupt");
                    SAFE_DELETEA(data);
                    return false;
                }
            }
            if (sf_colancount == 2) {
                last_sfmode = sfmode;
                sfmode = SM_MATERIAL_NAME;

                if (last_sfmode != SM_MODEL_NAME) {
                    PFB_LOG("Last Mode Was Not SM_MODEL_NAME, Config File Is Corrupt");
                    SAFE_DELETEA(data);
                    return false;
                }
            }
            sf_colancount++;
        }
        break;

        default: { // Something Else
            switch (sfmode) {
            case SM_NAME: {
                tbunker.name += (char)data[x];
            }
            break;

            case SM_IMAGE_NAME: {
                tbunker.image_name += (char)data[x];
            }
            break;

            case SM_MODEL_NAME: {
                tbunker.model_name += (char)data[x];
            }
            break;

            case SM_MATERIAL_NAME: {
                tbunker.material_name += (char)data[x];
            }
            break;
            }
        }
        break;
        }
    }

    SAFE_DELETEA(data);

    this->m_isLoaded = true;

    try {
        m_LoadedFieldKits.push_back(file);
        m_LoadedFieldKitsCount++;

        ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    } catch (Ogre::Exception ex) {
    }

//	SetScrollBar(G_PFBToolWindow.hWnd);
    return true;
}


bool CFieldKit::CleanUp(void)
{
    for (unsigned int x = 0; x < this->GetBunkerCount(); x++) {
        if (this->GetBunker(x)->bmp) {
            delete this->GetBunker(x)->bmp;
            this->GetBunker(x)->bmp = NULL;
        }

        String tmp;
        tmp.clear();
        tmp = String(TMPDIR) + this->GetBunker(x)->image_name;
        DeleteFile(tmp.c_str()); // Clean Just In Case

        tmp.clear();
        tmp = String(TMPDIR) + this->GetBunker(x)->material_name;
        DeleteFile(tmp.c_str()); // No Need For Materials Anymore

        this->GetBunker(x)->image_name.clear();
        this->GetBunker(x)->material_name.clear();
        this->GetBunker(x)->model_name.clear();
        this->GetBunker(x)->name.clear();
    }
    m_BunkerCount = 0;

    m_Version.clear();
    m_GeneratedBy.clear();
    m_Credit.clear();
    m_Copyright.clear();

    m_Version.empty();
    m_GeneratedBy.empty();
    m_Credit.empty();
    m_Copyright.empty();

    this->m_isLoaded = false;

    m_Bunkers.clear();
    return m_Bunkers.empty();
}


DWORD LoadFile(String file, FILEDATA *&data)
{
    FILE			*filePtr = NULL;		// File Pointer
    unsigned int	x = NULL;				// For Looping
    DWORD			fileLen = NULL;			// File Length

    // Open Filename In Read Binary Mode
    filePtr = fopen(file.c_str(), "rb");
    if(!filePtr) {
        PFB_LOG("Failed To Read File: ");
        return NULL;
    }

    // Find File Length
    fseek(filePtr, 0, SEEK_END);
    fileLen = ftell(filePtr);
    fseek(filePtr, 0, SEEK_SET);

    // Allocate Memory For File Data
    data = new FILEDATA[fileLen];
    if (!data) {
        PFB_LOG("Failed To Allocate Memory For File");
        return NULL;
    }
    memset(data, NULL, fileLen);

    // Read File Data
    for(x = 0; x < fileLen; x++) {
        fread(&data[x], sizeof(FILEDATA)*fileLen, 1, filePtr);
    }

    // Close The File
    fclose(filePtr);

    return fileLen;
}

size_t LoadFileD(DataStreamPtr &filePtr, FILEDATA *&data)
{
    unsigned int x = NULL;                          // For Looping
    size_t fileLen = NULL;                          // File Length

    fileLen = filePtr->size();

    if (!fileLen) {
        PFB_LOG("No File Length");
        return NULL;
    }

    // Allocate Memory For File Data
    data = new FILEDATA[fileLen];
    if (!data) {
        PFB_LOG("Failed To Allocate Memory For File");
        return NULL;
    }
    memset(data, NULL, fileLen*sizeof(FILEDATA));

    // Read File Data
    filePtr->read(data, fileLen*sizeof(FILEDATA));

    return fileLen;
}

void WriteFileD(String file, DataStreamPtr &filePtr)
{
    FILEDATA *data = NULL;
    size_t len = 0;
    len = LoadFileD(filePtr, data);


    FILE *filewrite = NULL; // File Pointer
    filewrite = fopen(file.c_str(), "wb");
    fwrite(data, len, sizeof(FILEDATA), filewrite);
    fclose(filewrite);


    SAFE_DELETEA(data);
}