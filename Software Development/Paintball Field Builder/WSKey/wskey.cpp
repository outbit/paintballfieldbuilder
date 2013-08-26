/**
 * ---------------------------------------------------------
 * @author: David Whiteside
 * @date: 09/20/09
 * @description: Handles Key Activation
 * Copyright 2004-2009 Whiteside Solutions LLC (www.whitesidesolutions.com)
 * ---------------------------------------------------------
 */

#include "wskey.h"

// OS DEPENDENT ON GetTickCount and MessageBox
#include <windows.h>

// encryption
#include <dll.h>
#include <osrng.h>
using CryptoPP::AutoSeededRandomPool;
#include <cryptlib.h>
using CryptoPP::Exception;
#include <aes.h>
using CryptoPP::AES;
#include <modes.h>
using CryptoPP::CBC_Mode;
using namespace CryptoPP;


namespace WSKey
{

// Global Variables
WSK_BYTE g_valid[] =
{ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', \
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', \
	'2', '3', '4', '5', '6', '7', '8', '9'};
WSK_BYTE g_ascii_to_valid[] =
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,26,27, \
	28,29,30,31,32,33,34,35,0,0,0, 0, 0, 0, 0, 0,1, 2, 3, 4, 5, 6, 7, 8, 9, \
	10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,0, 0, 0, 0, 0, 0, 0, 1, 2, \
	3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25, 0, 0, \
	0, 0, 0};

WSK_BYTE g_valid_to_ascii[] =
{97, 98, 99,100,101,102,103,104,105,106,107,108,109,110,  \
	111,112,113,114,115,116,117,118,119,120,121,122, 48, 49,  \
	50, 51, 52, 53, 54, 55, 56, 57};

// Class
CWSKey::CWSKey(bool trial)
{
	m_valid = false;                                                // Has Key Been Validated
	this->m_expires_daysleft = 0;                   // Days Left Till Trial Version Expires
	m_key.trial = trial;                                             // Default To Trial
	memset(m_key.k, 0, sizeof(m_key.k));    // clear key memory
}

CWSKey::CWSKey(char asciikey[])
{
	CWSKey();
	m_key.trial = false;                                            // Not A Trial

	// Init With A Key From Customer
	for (int x = 0; x < sizeof(m_key.k); x++)
		m_key.k[x] = g_ascii_to_valid[asciikey[x]]; // Convert Ascii To Valid (A=0, B=1, etc)
}

CWSKey::~CWSKey()
{
}

bool CWSKey::Load(char *filename)
{
	int version = 0;
	char junk1[1234] = {0};
	char junk2[3456] = {0};
	FILE *file = 0;
	// Decrypt
	byte key[AES::DEFAULT_KEYLENGTH];
	byte iv[AES::BLOCKSIZE];

	// Write Key File
	file = fopen(filename, "rb");
	if (file == 0)
	{
		WSK_LOG("Failed To Open The Key File");
		return false;
	}

	// Read Encrypted Key Data
	fread(&version, sizeof(version), 1, file);      // read version
	if (version != WSK_VERSION)                                     // Check Version
	{
		WSK_LOG("Wrong Version Of Key");
		fclose(file);
		return false;
	}
	fread(junk1, sizeof(junk1), 1, file);           // read junk
	fread(&m_key, sizeof(m_key), 1, file);          // read Key Data
	fread(key, sizeof(key), 1, file);                       // AES KEY
	fread(iv, sizeof(iv), 1, file);                         // AES iv
	fread(junk2, sizeof(junk2), 1, file);           // read junk

	// Close file
	fclose(file);

	// Decrypt
	CFB_Mode<AES>::Decryption cfbDecryption(key, AES::DEFAULT_KEYLENGTH, iv);
	cfbDecryption.ProcessData((byte*)junk1, (byte*)junk1, sizeof(junk1));
	cfbDecryption.ProcessData((byte*)&m_key, (byte*)&m_key, sizeof(m_key));
	cfbDecryption.ProcessData((byte*)junk2, (byte*)junk2, sizeof(junk2));

	return true;
}


WSKey_date CWSKey::GetCurrentDate()
{
	time_t hold_time;
	hold_time=std::time(NULL);
	char *chartime = ctime(&hold_time);
//  WSK_LOG(chartime); //Fri Jan 28 09:12:21 2000\n\0
	WSKey_date current;

	// Get Current Month from ascci to number
	if ( (chartime[4] == 'J') && (chartime[5] == 'a') && (chartime[6] == 'n') )
		current.month = 1;
	else if ( (chartime[4] == 'F') && (chartime[5] == 'e') && (chartime[6] == 'b') )
		current.month = 2;
	else if ( (chartime[4] == 'M') && (chartime[5] == 'a') && (chartime[6] == 'r') )
		current.month = 3;
	else if ( (chartime[4] == 'A') && (chartime[5] == 'p') && (chartime[6] == 'r') )
		current.month = 4;
	else if ( (chartime[4] == 'M') && (chartime[5] == 'a') && (chartime[6] == 'y') )
		current.month = 5;
	else if ( (chartime[4] == 'J') && (chartime[5] == 'u') && (chartime[6] == 'n') )
		current.month = 6;
	else if ( (chartime[4] == 'J') && (chartime[5] == 'u') && (chartime[6] == 'l') )
		current.month = 7;
	else if ( (chartime[4] == 'A') && (chartime[5] == 'u') && (chartime[6] == 'g') )
		current.month = 8;
	else if ( (chartime[4] == 'S') && (chartime[5] == 'e') && (chartime[6] == 'p') )
		current.month = 9;
	else if ( (chartime[4] == 'O') && (chartime[5] == 'c') && (chartime[6] == 't') )
		current.month = 10;
	else if ( (chartime[4] == 'N') && (chartime[5] == 'o') && (chartime[6] == 'v') )
		current.month = 11;
	else if ( (chartime[4] == 'D') && (chartime[5] == 'e') && (chartime[6] == 'c') )
		current.month = 12;
	else
	{
		WSK_LOG("Invalid Month Format - ERROR");
	}

	// Get Current Day from ascii to number
	WSK_LOG("Grabbing Date Information");
	char tmpchar[50] = {0}; //Fri Jan 28 09:12:21 2000\n\0
	memset(tmpchar, 0, sizeof(tmpchar));
	tmpchar[0] = chartime[8];
	tmpchar[1] = chartime[9];
	WSK_LOG(tmpchar);
	current.day = atoi(tmpchar);

	// Get Current Day from ascii to number
	memset(tmpchar, 0, sizeof(tmpchar));
	tmpchar[0] = chartime[20];
	tmpchar[1] = chartime[21];
	tmpchar[2] = chartime[22];
	tmpchar[3] = chartime[23];
	WSK_LOG(tmpchar);
	current.year = atoi(tmpchar);

	return current;
}


bool CWSKey::Save(char *filename)
{
	int version = WSK_VERSION;
	char junk1[1234] = {0};
	char junk2[3456] = {0};
	char encrypt[sizeof(junk1)+sizeof(WSKey_key)+sizeof(junk2)] = {0};
	FILE *file = 0;

	// Set Seed Value
	srand(GetTickCount());  // set Seed Value for Pseudo Random Number Generator

	// Generate Junk Data
	for (int x = 0; x < sizeof(junk1); x++)
	{
		junk1[x] = (char) (-127 + (rand( ) % 127));
		junk2[x] = (char) (-127 + (rand( ) % 127));
	}
	for (int x = sizeof(junk1); x < sizeof(junk2); x++)
	{
		junk2[x] = (char) (0 + (rand( ) % 255));
	}

	// Encrypt ALL DATA BEFORE WRITE
	AutoSeededRandomPool rnd;
	// Generate a random key
	byte key[AES::DEFAULT_KEYLENGTH];
	rnd.GenerateBlock(key, AES::DEFAULT_KEYLENGTH);
	// Generate a random IV
	byte iv[AES::BLOCKSIZE];
	rnd.GenerateBlock(iv, AES::BLOCKSIZE);
	// Copy To Tmp Place, Then Encrypt
	WSKey_key encrypt_key = this->m_key;
	CFB_Mode<AES>::Encryption cfbEncryption(key, AES::DEFAULT_KEYLENGTH, iv);
	cfbEncryption.ProcessData((byte*)junk1, (byte*)junk1, sizeof(junk1));
	cfbEncryption.ProcessData((byte*)&encrypt_key, (byte*)&encrypt_key, sizeof(m_key));
	cfbEncryption.ProcessData((byte*)junk2, (byte*)junk2, sizeof(junk2));

	// Write Key File
	file = fopen(filename, "wb");
	if (file == 0)
	{
		WSK_LOG("Failed To Open The Key File");
		return false;
	}

	// Write Encrypted Key Data
	fwrite(&version, sizeof(version), 1, file);             // File Version
	fwrite(junk1, sizeof(junk1), 1, file);                  // write junk
	fwrite(&encrypt_key, sizeof(m_key), 1, file);   // Write Key
//	fwrite(&m_key, sizeof(m_key), 1, file);			// Unencrypted Key
	fwrite(key, sizeof(key), 1, file);                              // AES KEY
	fwrite(iv, sizeof(iv), 1, file);                                // AES iv
	fwrite(junk2, sizeof(junk2), 1, file);                  // write junk

	// Close file
	fclose(file);

	return true;
}

bool CWSKey::ValidateKey()
{
	// Check If Trial Period Is Still VAlid
	if (this->m_key.trial == true)
	{
		// Get Current Date
		WSKey_date current = this->GetCurrentDate();

		// Check If Expired, return true of still a in trial period
		int days = 1;
		int months = 1;
		months = ((m_key.expires.year-current.year)*12 /*years to months*/) + (m_key.expires.month-current.month) /*months to months*/;
		days = (months*30 /*months to days*/) + (m_key.expires.day-current.day /*days to days*/);

		// Save Days Left
		this->m_expires_daysleft = days;

		// Check Trial
		if (days < 0)                           // Check If Key is Expired
		{
			WSK_LOG("This Key Is Expired");
			return false;
		} else if (days > WSK_TRIALDAYS) // Don't Roll Back Your Clocks
		{
			WSK_LOG("Im glad you like the software, but do not roll back the clock");
			wxMessageBox(wxT("do Not Roll back the clock"));
			return false;
		} else
		{
			WSK_LOG("This Key Is Not Expired");
			return true;
		}
	} // is trial?

	if (this->m_key.trial == false) // Not Trial, Check For Valid Key
	{
		int sum[2] = {0, 0};
		int remainder = 0;

		// Validate Key
		if ( (this->m_key.k[0] == g_ascii_to_valid[WSK_UNIQUE1])
		     &&   (this->m_key.k[1] == g_ascii_to_valid[WSK_UNIQUE2])
		     &&   (this->m_key.k[2] == g_ascii_to_valid[WSK_UNIQUE3]) )
		{
			WSK_LOG("First 3 key digits");
		}
		else
		{
			WSK_LOG("First 3 key digits are invalid");
			return false;
		}

		// Get Sums
		for (int x = 0; x < sizeof(m_key.k); x+=2)
			sum[0] += this->m_key.k[x];
		for (int x = 1; x < sizeof(m_key.k); x+=2)
			sum[1] += this->m_key.k[x]*3;

		// Calculate remainder
		remainder = (sum[0] + sum[1])%15;
		if (remainder == 0)
		{
			WSK_LOG("Key Is Valid");
			return true;
		}
	} // Not Trial

// Error
	WSK_LOG("Not A Valid Trial Key and Not A Vaid Key");
	return false;
}


bool CWSKey::ValidateUserKey(WSKey_userID id)
{
	return true;
}


bool CWSKey::GenerateTrialKey(const WSKey_date *expires)
{
	// Add Trial Information (if any), Do Not Generate Valid Key
	if (expires != 0)
	{
		this->m_key.expires.day = expires->day;
		this->m_key.expires.month = expires->month;
		this->m_key.expires.year = expires->year;
		this->m_key.trial = true;
		WSK_LOG("Expire Key Created");
		return true;
	}
	WSK_LOG("This Generator Failed To Work");
	return false;
}


bool CWSKey::GenerateTrialKey(int expires_days)
{
	// get Current Date
	WSKey_date expires = this->GetCurrentDate();

	// Calculate Expiration Date (Its confusing, and assumes all months have 30 days)
	if (expires.day+expires_days > 30)
	{
		// Expires at end of year
		if (expires.month == 12)
		{
			expires.month = 1;
			expires.year += 1;
			expires.day = (expires.day+expires_days)-30;
			WSK_LOG("Month Is December");
		}
		else
		{
			expires.month += 1;
			expires.day = (expires.day+expires_days)-30;
			WSK_LOG("Month is Another Month");
		}
	}
	else
	{
		expires.day = expires.day+expires_days;
		WSK_LOG("Expires In Same Month");
	}

	// Print Expire Debug Information
	char tmp[WSK_MAXSTR] = {0};
	sprintf(tmp, "Expires: %d/%d/%d", expires.month, expires.day, expires.year);
	WSK_LOG(tmp);

// Ok, Now That You have an expire date USE IT
	return this->GenerateTrialKey(&expires);
}


#ifdef WSK_FULL
bool CWSKey::GenerateKey()
{
	int sum[2] = {0, 0};
	int remainder = 0;
	bool original_trial = m_key.trial; // Save Trial Setting

	// Assume key is not a trial key
	m_key.trial = false;

	// set Seed Value for Pseudo Random Number Generator
	srand(GetTickCount());

	// Fill Key With Random Numbers
	this->m_key.k[0] = g_ascii_to_valid[WSK_UNIQUE1];
	this->m_key.k[1] = g_ascii_to_valid[WSK_UNIQUE2];
	this->m_key.k[2] = g_ascii_to_valid[WSK_UNIQUE3];
	for (int x = 3; x < sizeof(m_key.k); x++)
		this->m_key.k[x] = (WSK_BYTE) (0 + (rand( ) % sizeof(g_valid)));

	// Get Sums
	for (int x = 0; x < sizeof(m_key.k); x+=2)
		sum[0] += this->m_key.k[x];
	for (int x = 1; x < sizeof(m_key.k); x+=2)
		sum[1] += this->m_key.k[x]*3;

	// Calculate remainder
	remainder = (sum[0] + sum[1])%15;
	if (remainder == 0)
	{
		WSK_LOG("This Should RARELY HAPPEN");
		m_key.trial = original_trial;
		return true;
	}

	// Correct Number
	if (this->m_key.k[6]-remainder < 1)
	{
		WSK_LOG("Key is impossible to make valid, trying again");
		this->GenerateKey(); // Try Again
	}
	else
	{
		this->m_key.k[6] -= remainder;
	}

	// Make Sure Key Is Valid
	if (this->ValidateKey())
	{
		WSK_LOG("Generator Generated Valid Key");
		m_key.trial = original_trial;
		return true;
	}

	WSK_LOG("This Generator Failed To Work");

	m_key.trial = original_trial;
	return false;
}

bool CWSKey::GenerateUserKey(WSKey_userID id)
{
	return true;
}
#endif //WSK_FULL


} // namespace WSKEY

