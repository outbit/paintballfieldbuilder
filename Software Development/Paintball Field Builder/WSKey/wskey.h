/**
 * ---------------------------------------------------------
 * @author: David Whiteside
 * @date: 09/20/09
 * @description: Handles Product Activation
 * Copyright 2004-2009 Whiteside Solutions LLC (www.whitesidesolutions.com)
 * ---------------------------------------------------------
 */

#ifndef WSKEY_H
#define WSKEY_H

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctime>


// Project Specific
#include "../inc/Common.h"
#define WSKEY_LOGM(a) PFB_LOG(a)
// Project Specific


namespace WSKey
{

// User Custom Defines
//#define WSK_FULL                                        // for full key administration and generation
#define WSK_LOG(a) WSKEY_LOGM(a)        // Custom Logging Function
#define WSK_UNIQUE1 'p'                         // ID
#define WSK_UNIQUE2 'f'                         // ID
#define WSK_UNIQUE3 'b'                         // ID
#define WSK_TRIALDAYS 15                        // MAXIMUM Trial Day

// Defines
#ifndef WSK_LOG
#define WSK_LOG(a)
#error "Please Define WSK_LOG to allow logging
#endif //WSK_LOG

#define WSK_VERSION             1
#define WSK_MAXSTR              500
#define WSK_KEYLEN              20
#define WSK_RESCUEIDLEN 40
typedef unsigned char WSK_BYTE;

// A Computers Identity Signature for User Key
struct WSKey_userID
{
	WSK_BYTE name[WSK_MAXSTR];      // computer name
	WSK_BYTE rescueID[WSK_RESCUEIDLEN]; // customers can register product remotely, stores encrypted computer name
};

// Date
struct WSKey_date
{
	WSK_BYTE day;
	WSK_BYTE month;
	int year;               // 2009
};

// Key
struct WSKey_key
{
	WSK_BYTE k[WSK_KEYLEN];
	bool trial;
	WSKey_date expires;
	WSKey_userID id;
	int expires_days;
};

// Global Variables
WSK_BYTE g_valid[];
WSK_BYTE g_ascii_to_valid[];
WSK_BYTE g_valid_to_ascii[];

// Key Class
class CWSKey
{
private:
bool m_valid;
int m_expires_daysleft;
WSKey_key m_key;

WSKey_date GetCurrentDate();                                                                            // Return Date in WSK Format

public:
CWSKey(bool trial = false);                                                                                                                       // Constructor
CWSKey(char asciikey[]);                                                                                        // Constructor To Initiate With ascii Key
~CWSKey();                                                                                                                      // Destructor

bool Save(char *filename);                                                                                      // Save Encrypted Key To Disk
bool Load(char *filename);                                                                                      // Load Encrypted Key From Disk
bool ValidateKey();                                                                                                     // if no key start 30 day trial, else check if key is valid
bool ValidateUserKey(WSKey_userID id);                                                          // Tie a key to their hardware
bool GenerateTrialKey(const WSKey_date *expires);                                       // Trial Period Key (frome expire date)
bool GenerateTrialKey(int expires_days);                                                        // Trial Period Key (from days)

// Inline
inline int GetDaysLeft() {
	return this->m_expires_daysleft;
}
inline bool IsTrial() {
	return this->m_key.trial;
}
inline WSK_BYTE *GetKey() {
	return this->m_key.k;
}
inline LogKey()
{
	char asciikey[WSK_KEYLEN+1] = {0};
	memset(asciikey, 0, sizeof(asciikey));
	for (int x = 0; x < WSK_KEYLEN; x++)
		asciikey[x] = g_valid_to_ascii[this->m_key.k[x]];
	WSK_LOG(asciikey);
}
inline void GetKey (char key[])                                                                         // Get The Ascii Version of the key
{
	// Init With A Key From Customer
	for (int x = 0; x < sizeof(m_key.k); x++)
		key[x] = g_valid_to_ascii[m_key.k[x]];
}

#ifdef WSK_FULL
bool GenerateKey();                                                                                                     // Generate Random Key
bool GenerateUserKey(WSKey_userID id);                                                          // Generate a Key based on their hardware
#endif //WSKEY_FULL
};

} // namespace WSKey

#endif // WSKEY_H