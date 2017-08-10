////////////////////////////////////////
// Spy C Code Implementation
////////////////////////////////////////
#include "vspy.h"
// module variables
// TODO: add global variables here

// TODO: add event handlers here
#define MPI_STRLEN	        24 // max string has 16 characters + \0
#define MPI_MTC_LENGTH      16
#define MPI_EMPNAC_LENGTH   2
#define MPI_BMPNAC_LENGTH   2
#define MPI_ECUID_LENGTH    16
#define MPI_VPPS_LENGTH     14
#define MPI_DUNS_LENGTH     9

#define SAPA_STRLEN	        64 // max string has 22*2 characters + \0
#define SAPA_SEEDKEY_LENGTH 22
#define SAPA_SEED_LENGTH    5

static void hex2str(char *str, unsigned char *hex, int len)
{
    int i;
    unsigned char l4, h4;
    for(i = 0; i < len; i++) {
        h4 = (hex[i] & 0xf0)>>4;
        l4 = hex[i] & 0x0f;
        if (h4 <= 9)
            str[2*i] = h4 + ('0' -0);
        else
            str[2*i] = h4 + ('A'-10);

        if (l4 <= 9)
            str[2*i+1] = l4 + ('0' -0);
        else
            str[2*i+1] = l4 + ('A'-10);
    }
    str[2*i]=0;
}

static unsigned char asc2hex(char asccode)
{
    unsigned char ret;
    if('0' <= asccode && asccode <= '9')
        ret = asccode-'0';
    else if('a' <= asccode && asccode <= 'f')
        ret = asccode-'a'+10;
    else if('A' <= asccode && asccode <= 'F')
        ret = asccode-'A'+10;
    else
        ret = 0;
    return ret;
}

static void ascs2hex(unsigned char *hex, unsigned char *ascs, int srclen)
{
    unsigned char l4, h4;
    int i, lenstr;
    lenstr = srclen;
    if(lenstr == 0){
        return;
    }
    if(lenstr%2)
        return;
    for(i = 0; i < lenstr; i += 2){
        h4 = asc2hex(ascs[i]);
        l4 = asc2hex(ascs[i+1]);
        hex[i/2] = (h4<<4) + l4;
    }
}

static void str2hex(unsigned char *hex, int *len, char *str)
{
    unsigned char l4, h4;
    int i, lenstr;
    lenstr = strlen(str);
    if(lenstr == 0){
        *len = 0;
        return;
    }
    for(i = 0; i < lenstr-(lenstr%2); i += 2){
        h4 = asc2hex(str[i]);
        l4 = asc2hex(str[i+1]);
        hex[i/2] = (h4<<4)+l4;
    }
    if(lenstr%2)
        hex[(lenstr+1)/2-1] = asc2hex(str[lenstr-1]) << 4;
    *len = (lenstr+1)/2;
}

void Spy_EveryMessage(GenericMessage * p_Msg)
{
	// TODO: add something you want to do for every message
}

void Spy_EveryLongMessage(GenericLongMessage * p_Msg)
{
	// TODO: add something you want to do for every long message
}

void Spy_EveryLoop(unsigned int uiCurrentTime)
{
	// TODO: add something you want to do every millisecond
}

void Spy_EveryGUILoop()
{
	// TODO: write code to interact with the vehicle spy gui (this is called on the GUI thread)
}

void Spy_ErrorState(int iNetwork, int iTxErrorCount, int iRxErrorCount, int iErrorBitfield)
{
}

void Spy_ErrorFrame(int iNetwork, int iTxErrorCount, int iRxErrorCount, int iErrorBitfield)
{
}

void Spy_Stopped()
{

	// TODO: add stopped code
}

void Spy_KeyPress(int iKey, int iCTRLPressed, int iALTPressed)
{
	// TODO: add key handler code
}

void Spy_Started()
{
	// TODO: add started code
}

void Spy_BeforeStarted()
{
	// TODO: add before started code
}

void Spy_Main()
{
	// TODO: Add code here to run every time Spy is run
	int i;
	char text[MPI_STRLEN];
	unsigned char sapaText[SAPA_STRLEN];
	unsigned char array_appSig_sapaWrite_SeedKey[SAPA_SEEDKEY_LENGTH] = {0};
	unsigned char array_appSig_sapaWrite_Seed[SAPA_SEED_LENGTH] = {0};
	int len;
	
	memset(text, 0, sizeof(text));
	AS_appSig_mpiWrite_MTC_GetText(text);
	for (i = 0; i < sizeof(text); i++) {
		AS_appSig_mpiWrite_bytesMTC_SetAt(i, text[i]);
	}
	memset(text, 0, sizeof(text));
	AS_appSig_mpiWrite_EMPNAC_GetText(text);
	for (i = 0; i < sizeof(text); i++) {
		AS_appSig_mpiWrite_bytesEMPNAC_SetAt(i, text[i]);
	}
	memset(text, 0, sizeof(text));
	AS_appSig_mpiWrite_BMPNAC_GetText(text);
	for (i = 0; i < sizeof(text); i++) {
		AS_appSig_mpiWrite_bytesBMPNAC_SetAt(i, text[i]);
	}

	memset(sapaText, 0, sizeof(sapaText));
	AS_appSig_sapaWrite_SeedKey_GetText(sapaText);
	str2hex(array_appSig_sapaWrite_SeedKey, &len, sapaText);
	for (i = 0; i < SAPA_SEEDKEY_LENGTH; i++) {
		AS_appSig_sapaWrite_bytesSeedKey_SetAt(i, array_appSig_sapaWrite_SeedKey[i]);
	}  
	
	memset(sapaText, 0, sizeof(sapaText));
	AS_appSig_sapaWrite_Seed_GetText(sapaText);
	str2hex(array_appSig_sapaWrite_Seed, &len, sapaText);
	for (i = 0; i < SAPA_SEED_LENGTH; i++) {
		AS_appSig_sapaWrite_bytesSeed_SetAt(i, array_appSig_sapaWrite_Seed[i]);
	}	
}

char g_str_appSig_mpiWrite_MTC[MPI_STRLEN] = {0};
void SpyAppSig_AS_appSig_mpiWrite_MTC(double dNewValue)
{
    // TODO: Add Event Code
	int i = 0;
	char text[MPI_STRLEN];

	AS_appSig_mpiWrite_MTC_GetText(text);
	if (strcmp(g_str_appSig_mpiWrite_MTC, text)) {
		memset(g_str_appSig_mpiWrite_MTC, 0, sizeof(g_str_appSig_mpiWrite_MTC));
		strncpy_s(g_str_appSig_mpiWrite_MTC, sizeof(g_str_appSig_mpiWrite_MTC),
                  text, strlen(text));
		for (i = 0; i < MPI_MTC_LENGTH; i++) {
			AS_appSig_mpiWrite_bytesMTC_SetAt(i, g_str_appSig_mpiWrite_MTC[i]);
		}
	}
}

char g_str_appSig_mpiWrite_BMPNAC[MPI_STRLEN] = {0};
void SpyAppSig_AS_appSig_mpiWrite_BMPNAC(double dNewValue)
{
    // TODO: Add Event Code
	int i = 0;
	char text[MPI_STRLEN];

	AS_appSig_mpiWrite_BMPNAC_GetText(text);
	if (strcmp(g_str_appSig_mpiWrite_BMPNAC, text)) {
		memset(g_str_appSig_mpiWrite_BMPNAC, 0, sizeof(g_str_appSig_mpiWrite_BMPNAC));
		strncpy_s(g_str_appSig_mpiWrite_BMPNAC, sizeof(g_str_appSig_mpiWrite_BMPNAC),
                  text, strlen(text));
		for (i = 0; i < sizeof(g_str_appSig_mpiWrite_BMPNAC); i++) {
			AS_appSig_mpiWrite_bytesBMPNAC_SetAt(i, g_str_appSig_mpiWrite_BMPNAC[i]);
		}
	}
}

char g_str_appSig_mpiWrite_EMPNAC[MPI_STRLEN] = {0};
void SpyAppSig_AS_appSig_mpiWrite_EMPNAC(double dNewValue)
{
    // TODO: Add Event Code
	int i = 0;
	char text[MPI_STRLEN];

	AS_appSig_mpiWrite_EMPNAC_GetText(text);
	if (strcmp(g_str_appSig_mpiWrite_EMPNAC, text)) {
		memset(g_str_appSig_mpiWrite_EMPNAC, 0, sizeof(g_str_appSig_mpiWrite_EMPNAC));
		strncpy_s(g_str_appSig_mpiWrite_EMPNAC, sizeof(g_str_appSig_mpiWrite_EMPNAC),
                  text, strlen(text));
		for (i = 0; i < sizeof(g_str_appSig_mpiWrite_EMPNAC); i++) {
			AS_appSig_mpiWrite_bytesEMPNAC_SetAt(i, g_str_appSig_mpiWrite_EMPNAC[i]);
		}
	}
}

char g_str_appSig_mpiRead_MTC[MPI_STRLEN] = {0};
void SpyAppSig_AS_appSig_mpiRead_bytesMTC(double dNewValue)
{
    // TODO: Add Event Code
    int i = 0;
   
    for (i = 0; i < MPI_MTC_LENGTH; i++) {
        g_str_appSig_mpiRead_MTC[i] = (char)AS_appSig_mpiRead_bytesMTC_GetAt(i);
    }
   
    AS_appSig_mpiRead_MTC_SetText(g_str_appSig_mpiRead_MTC);
}

char g_str_appSig_mpiRead_EMPNAC[MPI_STRLEN] = {0};
void SpyAppSig_AS_appSig_mpiRead_bytesEMPNAC(double dNewValue)
{
    // TODO: Add Event Code
    int i = 0;
   
    for (i = 0; i < MPI_EMPNAC_LENGTH; i++) {
		g_str_appSig_mpiRead_EMPNAC[i] = (char)AS_appSig_mpiRead_bytesEMPNAC_GetAt(i);
    }
   
    AS_appSig_mpiRead_EMPNAC_SetText(g_str_appSig_mpiRead_EMPNAC);
}

char g_str_appSig_mpiRead_BMPNAC[MPI_STRLEN] = {0};
void SpyAppSig_AS_appSig_mpiRead_bytesBMPNAC(double dNewValue)
{
    // TODO: Add Event Code
    int i = 0;
   
    for (i = 0; i < MPI_BMPNAC_LENGTH; i++) {
		g_str_appSig_mpiRead_BMPNAC[i] = (char)AS_appSig_mpiRead_bytesBMPNAC_GetAt(i);
    }
   
    AS_appSig_mpiRead_BMPNAC_SetText(g_str_appSig_mpiRead_BMPNAC);
}

static int bcd2Ascii(char src, char *dest)
{
    char outputs[] = "0123456789ABCDEF";
    *dest++ = outputs[src>>4];
    *dest++ = outputs[src&0x0F];
    *dest = '\0';

    return 0;
}

char g_str_appSig_mpiRead_ECUID[MPI_STRLEN] = {0};
void SpyAppSig_AS_appSig_mpiRead_bytesECUID(double dNewValue)
{
	// TODO: Add Event Code
	int i = 0;
	int offset = 8;
	int j = offset;
	char bcd, asciiCodes[3];
   
	// g_str_appSig_mpiRead_ECUID only stores content from byte8, since byte13 is BCD code, which 
	// expand to 2 bytes ASCII code, so total 9 bytes in array
	// 
	for (i = 0; i < 5; i++) {
		g_str_appSig_mpiRead_ECUID[i] = (char)AS_appSig_mpiRead_bytesECUID_GetAt(j);
		j++;
	}

	bcd = (char)AS_appSig_mpiRead_bytesECUID_GetAt(j++);
	bcd2Ascii(bcd, asciiCodes);

	g_str_appSig_mpiRead_ECUID[i++] = asciiCodes[0];
	g_str_appSig_mpiRead_ECUID[i++] = asciiCodes[1];
   
	g_str_appSig_mpiRead_ECUID[i++] = (char)AS_appSig_mpiRead_bytesECUID_GetAt(j++);
	g_str_appSig_mpiRead_ECUID[i++] = (char)AS_appSig_mpiRead_bytesECUID_GetAt(j++);

	AS_appSig_mpiRead_ECUID_SetText(g_str_appSig_mpiRead_ECUID);
}

char g_str_appSig_mpiRead_VPPS[MPI_STRLEN] = {0};
void SpyAppSig_AS_appSig_mpiRead_bytesVPPS(double dNewValue)
{
    // TODO: Add Event Code
    int i = 0;
   
    for (i = 0; i < MPI_VPPS_LENGTH; i++) {
		g_str_appSig_mpiRead_VPPS[i] = (char)AS_appSig_mpiRead_bytesVPPS_GetAt(i);
    }
   
    AS_appSig_mpiRead_VPPS_SetText(g_str_appSig_mpiRead_VPPS);
}

char g_str_appSig_mpiRead_DUNS[MPI_STRLEN] = {0};
void SpyAppSig_AS_appSig_mpiRead_bytesDUNS(double dNewValue)
{
    // TODO: Add Event Code
    int i = 0;
   
    for (i = 0; i < MPI_DUNS_LENGTH; i++) {
		g_str_appSig_mpiRead_DUNS[i] = (char)AS_appSig_mpiRead_bytesDUNS_GetAt(i);
    }
   
    AS_appSig_mpiRead_DUNS_SetText(g_str_appSig_mpiRead_DUNS);
}

unsigned char g_str_appSig_sapaWrite_SeedKey[SAPA_STRLEN] = {0};
unsigned char g_array_appSig_sapaWrite_SeedKey[SAPA_SEEDKEY_LENGTH] = {0};
void SpyAppSig_AS_appSig_sapaWrite_bytesSeedKey(double dNewValue)
{
   // TODO: Add Event Code
    int i = 0;

    for (i = 0; i < SAPA_SEEDKEY_LENGTH; i++) {
		g_array_appSig_sapaWrite_SeedKey[i] = (unsigned char)AS_appSig_sapaWrite_bytesSeedKey_GetAt(i);
    }
	hex2str(g_str_appSig_sapaWrite_SeedKey, g_array_appSig_sapaWrite_SeedKey, SAPA_SEEDKEY_LENGTH);
    AS_appSig_sapaWrite_SeedKey_SetText(g_str_appSig_sapaWrite_SeedKey);
}           

unsigned char g_str_appSig_sapaWrite_Seed[SAPA_STRLEN] = {0};
unsigned char g_array_appSig_sapaWrite_Seed[SAPA_SEED_LENGTH] = {0};
void SpyAppSig_AS_appSig_sapaWrite_bytesSeed(double dNewValue)
{
   // TODO: Add Event Code
    int i = 0;

    for (i = 0; i < SAPA_SEED_LENGTH; i++) {
		g_array_appSig_sapaWrite_Seed[i] = (unsigned char)AS_appSig_sapaWrite_bytesSeed_GetAt(i);
    }
	hex2str(g_str_appSig_sapaWrite_Seed, g_array_appSig_sapaWrite_Seed, SAPA_SEED_LENGTH);
    AS_appSig_sapaWrite_Seed_SetText(g_str_appSig_sapaWrite_Seed);   
}

