/**
 * ---------------------------------------------------------
 * @author: David Whiteside
 * @date: 09/20/09
 * @description: FieldKit File Management
 * Copyright 2004-2009 Whiteside Solutions LLC (www.whitesidesolutions.com)
 * ---------------------------------------------------------
*/
#ifndef FIELDKIT_H
#define FIELDKIT_H

#include "../inc/Common.h"

#include <vector>
#include <ogrezip.h>

// Used to contain properties of a bunker
struct Bunker
{
	String name;
	String image_name;
	String model_name;
	String material_name;
	wxBitmap *bmp;
};

// Typedefs
typedef unsigned int BunkerID;
typedef char FILEDATA;

// Definitions
#define FIELDKITVER "1"
enum SEARCHMODE {SM_NAME, SM_IMAGE_NAME, SM_MODEL_NAME, SM_MATERIAL_NAME};

class CFieldKit
{
private:
String m_Version;
String m_GeneratedBy;
String m_Credit;
String m_Copyright;
bool m_isLoaded;
std::vector<Bunker> m_Bunkers;
unsigned int m_BunkerCount;
std::vector<String> m_LoadedFieldKits;
unsigned int m_LoadedFieldKitsCount;

inline bool AlreadyLoaded(String name)
{
	for (unsigned int x = 0; x < this->m_LoadedFieldKitsCount; x++)
	{
		if (name.compare(m_LoadedFieldKits[x]) == NULL)
		{
			return true; // Its Already Loaded
		}
	}

	return false;
}

public:
// Constructors
CFieldKit(String file = "");

// Destructors
~CFieldKit(void);

// Functions
bool Load(String file);
bool CleanUp(void);

inline Bunker *GetBunker(const BunkerID id)
{
	if (!m_BunkerCount || !m_isLoaded || (id >= m_BunkerCount))
		return 0;
	else
		return &this->m_Bunkers[id];
}

inline unsigned int GetBunkerCount(void)
{
	return this->m_BunkerCount;
}
};


// Global Functions
DWORD LoadFile(String file, FILEDATA *&data);
size_t LoadFileD(DataStreamPtr &filePtr, FILEDATA *&data);
void WriteFileD(String file, DataStreamPtr &filePtr);


#endif // FIELDKIT