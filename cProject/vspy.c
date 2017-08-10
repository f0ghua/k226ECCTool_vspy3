// vspy generated implementation file
#include "vspy.h"
#include "stdarg.h"

unsigned int g_uiHandle;
unsigned char g_bUseExtendedIdBit = 0;
long g_lStartDelay = 0;

#define MIN_VSPY_H_VERSION     1

int getStartDelay()
{
    return g_lStartDelay;
}

void setStartDelay(int delay)
{
    if ((delay < 0) || (delay > 99999))
    {
        Printf("setStartDelay was passed an invalid value: %d\n", delay);
        delay = 0;
    }
    g_lStartDelay = delay;
}

int CM_GetVSPY_C_H_Version()
{
    return MIN_VSPY_H_VERSION;
}

void SetUseExtendedIdBit()
{
    g_bUseExtendedIdBit = 1;
}

int GetMessageName(int iMessageId, int iMessageContext, char * pName, int iBufferSize)
{
    int nLen;
    wchar_t *pWideBuffer = malloc(iBufferSize * sizeof(wchar_t));
    if (isExtId(iMessageId))
        iMessageId = mkStdId(iMessageId);
    if (CM_GetMessageName(g_uiHandle, iMessageId, iMessageContext, pWideBuffer, iBufferSize))
    {
        nLen = WideCharToMultiByte(0, 0, pWideBuffer, (int)wcslen(pWideBuffer), NULL, 0, NULL, NULL);
        WideCharToMultiByte(0, 0, pWideBuffer, (int)wcslen(pWideBuffer), pName, nLen, NULL, NULL);
        pName[nLen] = 0;
        free(pWideBuffer);
        return 1;
    }
    free(pWideBuffer);
    return 0;
}

int GetMessageNameW(int iMessageId, int iMessageContext, wchar_t * pName, int iBufferSize)
{
    if (isExtId(iMessageId))
        iMessageId = mkStdId(iMessageId);
    return CM_GetMessageName(g_uiHandle, iMessageId, iMessageContext, pName, iBufferSize);
}

int SpyViewGetCount()
{
    int temp = 0;
    CM_GetSetValue(g_uiHandle, CM_GET_VIEWCOUNT, 0, &temp);
    return temp;
}

int SpyViewGetType(void* pView)
{
    stGetViewTypeArgs args;
    args.InForm = pView;
    CM_GetSetValue(g_uiHandle, CM_GET_VIEWTYPE, 0, &args);
    return args.OutType;
}

void* SpyViewGetHandle(int index){

    void* temp = NULL;
    CM_GetSetValue(g_uiHandle, CM_GET_VIEWHANDLE, index, &temp);
    return temp;
}

void SpyViewShow(void* pView)
{
    CM_GetSetValue(g_uiHandle, CM_SET_SHOWVIEW, 0, pView);
}

void SpyViewHide(void* pView)
{
    CM_GetSetValue(g_uiHandle, CM_SET_HIDEVIEW, 0, pView);
}

int SpyViewIsVisible(void* pView)
{
    stGetViewIsVisibleArgs args;
    args.InForm = pView;
    CM_GetSetValue(g_uiHandle, CM_GET_VIEWISVISIBLE, 0, &args);
    return args.OutVisible;
}

void* SpyViewShowByType(int type)
{
    void* temp = NULL;
    CM_GetSetValue(g_uiHandle, CM_SET_SHOWVIEWBYTYPE, type, &temp);
    return temp;
}

void* SpyViewGetProcAddress(void* pView, const char* szProcName)
{
    stGetViewProcAddressArgs args;
    args.InForm = pView;
    args.InFunctionName = szProcName;
    args.OutFunctionPtr = NULL;
    CM_GetSetValue(g_uiHandle, CM_GET_VIEWPROCADDRESS, 0, &args);
    return args.OutFunctionPtr;
}

double AS_Get(int index)
{
    double dTemp;
    CM_GetSetValue(g_uiHandle, CM_GETSET_GET_APP_SIGNAL, index, &dTemp);
    return dTemp;
}

void AS_Set(int index, double dValue)
{
    double dTemp = dValue;
    CM_GetSetValue(g_uiHandle, CM_GETSET_SET_APP_SIGNAL, index, &dTemp);
}

struct AppSigValue
{
    int nOffset;
    double dValue;
};

double AS_GetAt(int index, int element)
{
    struct AppSigValue sVal;
    if (element == 0)
        return AS_Get(index);
    sVal.nOffset = element;
    CM_GetSetValue(g_uiHandle, CM_GETSET_GET_APP_SIGNAL_AT, index, &sVal);
    return sVal.dValue;
}

void AS_SetAt(int index, int element, double dValue)
{
    struct AppSigValue sVal;
    if (element == 0)
    {
        AS_Set(index, dValue);
        return;
    }
    sVal.dValue = dValue;
    sVal.nOffset = element;
    CM_GetSetValue(g_uiHandle, CM_GETSET_SET_APP_SIGNAL_AT, index, &sVal);
}

int AS_GetText(int nIndex, void * szValue, int nLength)
{
    wchar_t szTemp[1024];
    int nLen = nLength;
    CM_GetSetValue(g_uiHandle, CM_GETSET_GET_APP_SIGNAL_TEXT, nIndex, szTemp);
    if (nLen <= 0)
        nLen = min(WideCharToMultiByte(0, 0, szTemp, (int)wcslen(szTemp), NULL, 0, NULL, NULL), 1023);
    if (wcsncmp(szTemp, L"#0x", 3) == 0)  // Binary
    {
        wchar_t szByte[] = L"00";
        int nByte;
        nLen = ((int)wcslen(szTemp) - 3) / 2;
        for (nByte = 0; nByte < nLen; ++nByte)
        {
            szByte[0] = szTemp[3 + nByte * 2];
            szByte[1] = szTemp[4 + nByte * 2];
            *((BYTE *)szValue + nByte) = (BYTE)wcstol(szByte, NULL, 16);
        }
        return nLen;
    }
    WideCharToMultiByte(0, 0, szTemp, (int)wcslen(szTemp), (char *)szValue, nLen, NULL, NULL);
    *((char *)szValue + nLen) = 0;
    return (int)strlen(szValue);
}

int AS_SetText(int nIndex, void * szValue, int nLength)
{
    BOOL bIsBinary = 0;
    wchar_t szTemp[1024];
    int nLen = nLength;
    if (nLen <= 0)
        nLen = min(MultiByteToWideChar(0, 0, (char *)szValue, (int)strlen(szValue), NULL, 0), 1023);
    else
    {
        int nByte;
        wcscpy_s(szTemp, 4, L"#0x");
        for (nByte = 0; nByte < nLength; ++nByte)
        {
            if ((*((BYTE *)szValue) + nByte) < 32)
                bIsBinary = 1;
            swprintf(szTemp + (nByte * 2) + 3, _countof(szTemp) - (nByte * 2) - 3, L"%02x",
                     (*((BYTE *)szValue) + nByte));
        }
    }
    if (bIsBinary)
    {
        CM_GetSetValue(g_uiHandle, CM_GETSET_SET_APP_SIGNAL_TEXT, nIndex, szTemp);
        return nLength;
    }
    else
    {
        MultiByteToWideChar(0, 0, szValue, (int)strlen(szValue), szTemp, nLen);
        szTemp[nLen] = 0;
        CM_GetSetValue(g_uiHandle, CM_GETSET_SET_APP_SIGNAL_TEXT, nIndex, szTemp);
        return (int)strlen(szValue);
    }
}

int AS_GetTextW(int index, wchar_t * szValue)
{
    CM_GetSetValue(g_uiHandle, CM_GETSET_GET_APP_SIGNAL_TEXT, index, szValue);
    return (int)wcslen(szValue);
}

struct AppSigTextValue
{
    int nOffset;
    wchar_t *szValue;
};

int AS_GetTextAtW(int index, int element, wchar_t * szValue)
{
    struct AppSigTextValue sVal;
    sVal.szValue = szValue;
    sVal.nOffset = element;
    CM_GetSetValue(g_uiHandle, CM_GETSET_GET_APP_SIGNAL_TEXT_AT, index, &sVal);
    return (int)wcslen(szValue);
}

int AS_SetTextAtW(int index, int element, wchar_t * szValue)
{
    struct AppSigTextValue sVal;
    sVal.szValue = szValue;
    sVal.nOffset = element;
    CM_GetSetValue(g_uiHandle, CM_GETSET_SET_APP_SIGNAL_TEXT_AT, index, &sVal);
    return (int)wcslen(szValue);
}

int CanNetworksInUse[] = {
    0,  //HS_CAN
    1,  //MS_CAN
};

int Spy_NetworksInUse()
{
    return _countof(CanNetworksInUse);
}

int Spy_TranslateNetwork(int nNetworkOffset)
{
    if ((nNetworkOffset <= 1) || (nNetworkOffset > Spy_NetworksInUse()))
        return CanNetworksInUse[0] + 1;
    else
        return CanNetworksInUse[nNetworkOffset - 1] + 1;
}
int Spy_UntranslateNetwork(int nNetwork)
{
    int can;
    for (can = 0; can < Spy_NetworksInUse(); ++can)
    {
        if (CanNetworksInUse[can] + 1 == nNetwork)
            return can + 1;
    }
    return 1;
}

int Spy_LINIndex(int iNetwork)
{
    if (iNetwork == NET_LIN2__neoVI_3G_)
        return 2;
    else if (iNetwork == NET_LIN3__neoVI_3G_)
        return 3;
    else if (iNetwork == NET_LIN4__neoVI_3G_)
        return 4;
    else if (iNetwork == NET_LIN2__VNET_A_)
        return 2;
    else if (iNetwork == NET_LIN3__VNET_A_)
        return 3;
    else if (iNetwork == NET_LIN4__VNET_A_)
        return 4;
    else
        return 1;
}

// network index variables - identify networks in vspy
int NET_HS_CAN = 0;
void NET_HS_CAN_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN,0);
}
void NET_HS_CAN_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN,p_NetworkStats);
}
int NET_MS_CAN = 1;
void NET_MS_CAN_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_MS_CAN,0);
}
void NET_MS_CAN_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_MS_CAN,p_NetworkStats);
}
int NET_SW_CAN = 2;
void NET_SW_CAN_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_SW_CAN,0);
}
void NET_SW_CAN_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_SW_CAN,p_NetworkStats);
}
int NET_J1850_VPW = 3;
void NET_J1850_VPW_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_J1850_VPW,0);
}
void NET_J1850_VPW_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_J1850_VPW,p_NetworkStats);
}
int NET_ISO9141_KW2K = 4;
void NET_ISO9141_KW2K_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_ISO9141_KW2K,0);
}
void NET_ISO9141_KW2K_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_ISO9141_KW2K,p_NetworkStats);
}
int NET_LSFT_CAN = 5;
void NET_LSFT_CAN_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LSFT_CAN,0);
}
void NET_LSFT_CAN_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LSFT_CAN,p_NetworkStats);
}
int NET_J1850_PWM = 6;
void NET_J1850_PWM_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_J1850_PWM,0);
}
void NET_J1850_PWM_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_J1850_PWM,p_NetworkStats);
}
int NET_J1708 = 7;
void NET_J1708_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_J1708,0);
}
void NET_J1708_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_J1708,p_NetworkStats);
}
int NET_neoVI = 8;
void NET_neoVI_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_neoVI,0);
}
void NET_neoVI_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_neoVI,p_NetworkStats);
}
int NET_HS_CAN2__neoVI_3G_ = 9;
void NET_HS_CAN2__neoVI_3G__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN2__neoVI_3G_,0);
}
void NET_HS_CAN2__neoVI_3G__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN2__neoVI_3G_,p_NetworkStats);
}
int NET_HS_CAN3__neoVI_3G_ = 10;
void NET_HS_CAN3__neoVI_3G__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN3__neoVI_3G_,0);
}
void NET_HS_CAN3__neoVI_3G__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN3__neoVI_3G_,p_NetworkStats);
}
int NET_LIN2__neoVI_3G_ = 11;
void NET_LIN2__neoVI_3G__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN2__neoVI_3G_,0);
}
void NET_LIN2__neoVI_3G__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN2__neoVI_3G_,p_NetworkStats);
}
int NET_LIN3__neoVI_3G_ = 12;
void NET_LIN3__neoVI_3G__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN3__neoVI_3G_,0);
}
void NET_LIN3__neoVI_3G__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN3__neoVI_3G_,p_NetworkStats);
}
int NET_LIN4__neoVI_3G_ = 13;
void NET_LIN4__neoVI_3G__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN4__neoVI_3G_,0);
}
void NET_LIN4__neoVI_3G__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN4__neoVI_3G_,p_NetworkStats);
}
int NET_CGI__neoVI_3G_ = 14;
void NET_CGI__neoVI_3G__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_CGI__neoVI_3G_,0);
}
void NET_CGI__neoVI_3G__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_CGI__neoVI_3G_,p_NetworkStats);
}
int NET_LIN = 15;
void NET_LIN_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN,0);
}
void NET_LIN_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN,p_NetworkStats);
}
int NET_ISO9141_KW2K_2 = 16;
void NET_ISO9141_KW2K_2_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_ISO9141_KW2K_2,0);
}
void NET_ISO9141_KW2K_2_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_ISO9141_KW2K_2,p_NetworkStats);
}
int NET_ISO9141_KW2K_3 = 17;
void NET_ISO9141_KW2K_3_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_ISO9141_KW2K_3,0);
}
void NET_ISO9141_KW2K_3_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_ISO9141_KW2K_3,p_NetworkStats);
}
int NET_ISO9141_KW2K_4 = 18;
void NET_ISO9141_KW2K_4_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_ISO9141_KW2K_4,0);
}
void NET_ISO9141_KW2K_4_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_ISO9141_KW2K_4,p_NetworkStats);
}
int NET_HS_CAN4 = 19;
void NET_HS_CAN4_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN4,0);
}
void NET_HS_CAN4_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN4,p_NetworkStats);
}
int NET_HS_CAN5 = 20;
void NET_HS_CAN5_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN5,0);
}
void NET_HS_CAN5_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN5,p_NetworkStats);
}
int NET_UART__neoVI_3G_ = 21;
void NET_UART__neoVI_3G__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_UART__neoVI_3G_,0);
}
void NET_UART__neoVI_3G__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_UART__neoVI_3G_,p_NetworkStats);
}
int NET_UART2__neoVI_3G_ = 22;
void NET_UART2__neoVI_3G__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_UART2__neoVI_3G_,0);
}
void NET_UART2__neoVI_3G__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_UART2__neoVI_3G_,p_NetworkStats);
}
int NET_neoMOST = 23;
void NET_neoMOST_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_neoMOST,0);
}
void NET_neoMOST_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_neoMOST,p_NetworkStats);
}
int NET_MOST__VNET_A_ = 24;
void NET_MOST__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_MOST__VNET_A_,0);
}
void NET_MOST__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_MOST__VNET_A_,p_NetworkStats);
}
int NET_FlexRay1A__VNET_A_ = 25;
void NET_FlexRay1A__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_FlexRay1A__VNET_A_,0);
}
void NET_FlexRay1A__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_FlexRay1A__VNET_A_,p_NetworkStats);
}
int NET_FlexRay1B__VNET_A_ = 26;
void NET_FlexRay1B__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_FlexRay1B__VNET_A_,0);
}
void NET_FlexRay1B__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_FlexRay1B__VNET_A_,p_NetworkStats);
}
int NET_FlexRay2A__VNET_A_ = 27;
void NET_FlexRay2A__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_FlexRay2A__VNET_A_,0);
}
void NET_FlexRay2A__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_FlexRay2A__VNET_A_,p_NetworkStats);
}
int NET_FlexRay2B__VNET_A_ = 28;
void NET_FlexRay2B__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_FlexRay2B__VNET_A_,0);
}
void NET_FlexRay2B__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_FlexRay2B__VNET_A_,p_NetworkStats);
}
int NET_HS_CAN__VNET_A_ = 29;
void NET_HS_CAN__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN__VNET_A_,0);
}
void NET_HS_CAN__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN__VNET_A_,p_NetworkStats);
}
int NET_MS_CAN__VNET_A_ = 30;
void NET_MS_CAN__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_MS_CAN__VNET_A_,0);
}
void NET_MS_CAN__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_MS_CAN__VNET_A_,p_NetworkStats);
}
int NET_SW_CAN__VNET_A_ = 31;
void NET_SW_CAN__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_SW_CAN__VNET_A_,0);
}
void NET_SW_CAN__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_SW_CAN__VNET_A_,p_NetworkStats);
}
int NET_J1850_VPW__VNET_A_ = 32;
void NET_J1850_VPW__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_J1850_VPW__VNET_A_,0);
}
void NET_J1850_VPW__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_J1850_VPW__VNET_A_,p_NetworkStats);
}
int NET_LSFT_CAN__VNET_A_ = 33;
void NET_LSFT_CAN__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LSFT_CAN__VNET_A_,0);
}
void NET_LSFT_CAN__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LSFT_CAN__VNET_A_,p_NetworkStats);
}
int NET_J1708__VNET_A_ = 34;
void NET_J1708__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_J1708__VNET_A_,0);
}
void NET_J1708__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_J1708__VNET_A_,p_NetworkStats);
}
int NET_neoVI__VNET_A_ = 35;
void NET_neoVI__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_neoVI__VNET_A_,0);
}
void NET_neoVI__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_neoVI__VNET_A_,p_NetworkStats);
}
int NET_HS_CAN2__VNET_A_ = 36;
void NET_HS_CAN2__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN2__VNET_A_,0);
}
void NET_HS_CAN2__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN2__VNET_A_,p_NetworkStats);
}
int NET_HS_CAN3__VNET_A_ = 37;
void NET_HS_CAN3__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN3__VNET_A_,0);
}
void NET_HS_CAN3__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN3__VNET_A_,p_NetworkStats);
}
int NET_LIN__VNET_A_ = 38;
void NET_LIN__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN__VNET_A_,0);
}
void NET_LIN__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN__VNET_A_,p_NetworkStats);
}
int NET_LIN2__VNET_A_ = 39;
void NET_LIN2__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN2__VNET_A_,0);
}
void NET_LIN2__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN2__VNET_A_,p_NetworkStats);
}
int NET_LIN3__VNET_A_ = 40;
void NET_LIN3__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN3__VNET_A_,0);
}
void NET_LIN3__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN3__VNET_A_,p_NetworkStats);
}
int NET_LIN4__VNET_A_ = 41;
void NET_LIN4__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN4__VNET_A_,0);
}
void NET_LIN4__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN4__VNET_A_,p_NetworkStats);
}
int NET_CGI__VNET_A_ = 42;
void NET_CGI__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_CGI__VNET_A_,0);
}
void NET_CGI__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_CGI__VNET_A_,p_NetworkStats);
}
int NET_ISO9141_KW2K__VNET_A_ = 43;
void NET_ISO9141_KW2K__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_ISO9141_KW2K__VNET_A_,0);
}
void NET_ISO9141_KW2K__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_ISO9141_KW2K__VNET_A_,p_NetworkStats);
}
int NET_ISO9141_KW2K_2__VNET_A_ = 44;
void NET_ISO9141_KW2K_2__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_ISO9141_KW2K_2__VNET_A_,0);
}
void NET_ISO9141_KW2K_2__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_ISO9141_KW2K_2__VNET_A_,p_NetworkStats);
}
int NET_ISO9141_KW2K_3__VNET_A_ = 45;
void NET_ISO9141_KW2K_3__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_ISO9141_KW2K_3__VNET_A_,0);
}
void NET_ISO9141_KW2K_3__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_ISO9141_KW2K_3__VNET_A_,p_NetworkStats);
}
int NET_ISO9141_KW2K_4__VNET_A_ = 46;
void NET_ISO9141_KW2K_4__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_ISO9141_KW2K_4__VNET_A_,0);
}
void NET_ISO9141_KW2K_4__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_ISO9141_KW2K_4__VNET_A_,p_NetworkStats);
}

int GenericMessageTransmit(GenericMessage * p_Msg)
{
    int iID;
    int iBitField;
    iID = p_Msg->iID;
    iBitField = p_Msg->iBitField;
    if (isExtId(iID))
    {
        iID = mkStdId(iID);
        iBitField |= ATTR_CAN_29BIT_ID_FRAME;
    }

    return CM_TransmitMessage(g_uiHandle, p_Msg->iNetwork, iID, p_Msg->iNumDataBytes, iBitField, p_Msg->btData);
}

int GenericLongMessageTransmit(GenericLongMessage * p_Msg)
{
    int iID;
    int iBitField;
    iID = p_Msg->iID;
    iBitField = p_Msg->iBitField;

    return CM_TransmitMessage(g_uiHandle, p_Msg->iNetwork, iID, p_Msg->iNumDataBytes, iBitField, p_Msg->btData);
}

int CANFDMessageTransmit(GenericLongMessage * p_Msg, BOOL bBRS)
{
    int iID;
    int iBitField;
    iID = p_Msg->iID;
    iBitField = p_Msg->iBitField;
    if (isExtId(iID))
    {
        iID = mkStdId(iID);
        iBitField |= ATTR_CAN_29BIT_ID_FRAME;
    }
    iBitField |= ATTR_CANFD_FRAME;
    if (bBRS)
        iBitField |= ATTR_CANFD_BRS;

    return CM_TransmitMessage(g_uiHandle, p_Msg->iNetwork, iID, p_Msg->iNumDataBytes, iBitField, p_Msg->btData);
}

void SpySetTxSignal(unsigned int iMessageIndex, unsigned int iSignalIndex, double dValue)
{
    TxSetSignal txSetSignal;
    txSetSignal.iSignal = iSignalIndex;
    txSetSignal.iType = 0;
    txSetSignal.dValue = dValue;
    CM_GetSetValue(g_uiHandle, CM_GETSET_SET_TXSIGNAL, iMessageIndex, &txSetSignal);
}

void SpySetTxSignalRaw(unsigned int iMessageIndex, unsigned int iSignalIndex, __int64 nValue)
{
    TxSetSignal txSetSignal;
    txSetSignal.iSignal = iSignalIndex;
    txSetSignal.iType = 1;
    txSetSignal.nValue = nValue;
    CM_GetSetValue(g_uiHandle, CM_GETSET_SET_TXSIGNAL, iMessageIndex, &txSetSignal);
}

void SpySetTxEvent(unsigned int iMessageIndex)
{
    TxSetSignal txSetSignal;
    txSetSignal.iType = 2;
    CM_GetSetValue(g_uiHandle, CM_GETSET_SET_TXSIGNAL, iMessageIndex, &txSetSignal);
}

int Spy_TextAPI_W(wchar_t * wcCommand, wchar_t * wcResponse, int iResponseMaxLength)
{
    return CM_TextAPI(g_uiHandle,wcCommand,wcResponse,iResponseMaxLength);
}

int Spy_TextAPI(char * szCommand, char * szResponse, int iResponseMaxLength)
{
    int iCount;
    int iResult;
    wchar_t wcCommand[1024];
    wchar_t wcResponse[1024];
    iCount = MultiByteToWideChar(0, 0, szCommand, (int)strlen(szCommand), NULL, 0);
    MultiByteToWideChar(0, 0, szCommand, (int)strlen(szCommand), wcCommand, iCount);
    wcCommand[iCount] = 0;
    iResult = CM_TextAPI(g_uiHandle, wcCommand, wcResponse, 1024);
    iCount = WideCharToMultiByte(0, 0, wcResponse, (int)wcslen(wcResponse), NULL, 0, NULL, NULL);
    WideCharToMultiByte(0, 0, wcResponse, (int)wcslen(wcResponse), szResponse, iCount, NULL, NULL);
    szResponse[iCount] = 0;
    return iResult;
}

#define MAX_PRINT_BUF_SIZE 1024

int OutputChars(const char *szMsg, int nLen)
{
    wchar_t *pWideBuffer;
    int iCount = MultiByteToWideChar(0, 0, szMsg, nLen, NULL, 0);
    pWideBuffer = malloc((iCount + 1) * sizeof(wchar_t));
    MultiByteToWideChar(0, 0, szMsg, nLen, pWideBuffer, iCount);
    pWideBuffer[iCount] = 0;
    CM_OutputWindow(g_uiHandle, pWideBuffer, 0x0000, 0);
    free(pWideBuffer);
    return iCount;
}

int Printf(const char *szInMsg, ...)
{
    va_list ap;
    int iNumCharacters;
    char szMsg[MAX_PRINT_BUF_SIZE];
    va_start(ap, szInMsg);
    iNumCharacters = vsprintf_s(szMsg, MAX_PRINT_BUF_SIZE, szInMsg, ap);
    iNumCharacters = OutputChars(szMsg, iNumCharacters);
    va_end(ap);
    return iNumCharacters;
}

int PrintfW(const wchar_t *szInMsg, ...)
{
    va_list ap;
    int iNumCharacters;
    wchar_t szMsg[MAX_PRINT_BUF_SIZE];
    va_start(ap, szInMsg);
    iNumCharacters = vswprintf_s(szMsg, MAX_PRINT_BUF_SIZE, szInMsg, ap);
    va_end(ap);
    CM_OutputWindow(g_uiHandle, szMsg, 0x0000, 0);
    return iNumCharacters;
}

int WriteLine(const char *szInMsg, ...)
{
    va_list ap;
    int iNumCharacters;
    char szMsg[MAX_PRINT_BUF_SIZE];
    va_start(ap, szInMsg);
    iNumCharacters = vsprintf_s(szMsg, MAX_PRINT_BUF_SIZE, szInMsg, ap);
    strcat_s(szMsg, MAX_PRINT_BUF_SIZE, "\n");
    ++iNumCharacters;
    iNumCharacters = OutputChars(szMsg, iNumCharacters);
    va_end(ap);
    return iNumCharacters;
}

int WriteLineW(const wchar_t *szInMsg, ...)
{
    va_list ap;
    int iNumCharacters;
    wchar_t szMsg[MAX_PRINT_BUF_SIZE];
    va_start(ap, szInMsg);
    iNumCharacters = vswprintf_s(szMsg, MAX_PRINT_BUF_SIZE, szInMsg, ap);
    va_end(ap);
    wcscat_s(szMsg, MAX_PRINT_BUF_SIZE, L"\n");
    CM_OutputWindow(g_uiHandle, szMsg, 0x0000, 0);
    return iNumCharacters + 1;
}

// Retrieve the system error message for the last error code
void DisplayLastError(LPCWSTR lpszFunction)
{
    LPVOID lpMsgBuf;
    DWORD dw = GetLastError();

    FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, dw,
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR) &lpMsgBuf, 0, NULL );

    // Display the error message
    if (lpszFunction)
        PrintfW(L"%ls failed with error %d: %ls\n", lpszFunction, dw, lpMsgBuf);
    else
        PrintfW(L"Error %d: %ls\n", dw, lpMsgBuf);

    LocalFree(lpMsgBuf);
}

#define ICS_MAX_RS232_PORT 255
HANDLE hSerialPorts[ICS_MAX_RS232_PORT] = { INVALID_HANDLE_VALUE };

RS232OnRxTx_fdef fptr_ICS_RS232OnSend = NULL;
RS232OnRxTx_fdef fptr_ICS_RS232OnReceive = NULL;
RS232OnError_fdef fptr_ICS_RS232OnError = NULL;

DWORD ICS_RS232Open(DWORD port)
{
    wchar_t szPort[20];
    if ((port <= 0) || (port > ICS_MAX_RS232_PORT))
    {
        PrintfW(L"ICS_RS232Open was passed an invalid port number: %d\n", port);
        return 0;
    }
    wsprintf(szPort, TEXT("\\\\.\\COM%d"), port);
    hSerialPorts[port - 1] = CreateFile(szPort, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hSerialPorts[port - 1] != INVALID_HANDLE_VALUE)
        return 1;
    else
    {
        DisplayLastError(TEXT("ICS_RS232Open"));
        return 0;
    }
}

DWORD ICS_RS232Close(DWORD port)
{
    if ((port <= 0) || (port > ICS_MAX_RS232_PORT))
    {
        PrintfW(L"ICS_RS232Close was passed an invalid port number: %d\n", port);
        return 0;
    }
    if (hSerialPorts[port - 1] != INVALID_HANDLE_VALUE)
    {
        CloseHandle(hSerialPorts[port - 1]);
        hSerialPorts[port - 1] = INVALID_HANDLE_VALUE;
        return 1;
    }
    else
    {
        PrintfW(L"ICS_RS232Close port number %d was not opened\n", port);
        return 0;
    }
}

DWORD ICS_RS232ConfigTimeout(DWORD port, DWORD baudrate, DWORD numberOfDataBits, DWORD numberOfStopBits, DWORD parity, DWORD timeout)
{
    if ((port <= 0) || (port > ICS_MAX_RS232_PORT))
    {
        PrintfW(L"ICS_RS232ConfigTimeout was passed an invalid port number: %d\n", port);
        return 0;
    }
    if (hSerialPorts[port - 1] != INVALID_HANDLE_VALUE)
    {
        DCB comState;
        if (GetCommState(hSerialPorts[port - 1], &comState))
		{
            DCB newComState = comState;

            newComState.BaudRate = baudrate;
            newComState.ByteSize = (BYTE)numberOfDataBits;
            newComState.StopBits = (BYTE)numberOfStopBits;
            newComState.Parity = (BYTE)parity;

            if (SetCommState(hSerialPorts[port - 1], &newComState))
            {
                // Add CommTimeout
                COMMTIMEOUTS commTimeout;
                GetCommTimeouts(hSerialPorts[port - 1], &commTimeout);

                commTimeout.ReadIntervalTimeout = 0;
                commTimeout.ReadTotalTimeoutMultiplier = 0;
                commTimeout.ReadTotalTimeoutConstant = timeout;
                commTimeout.WriteTotalTimeoutMultiplier = 0;
                commTimeout.WriteTotalTimeoutConstant = timeout;

                SetCommTimeouts(hSerialPorts[port - 1], &commTimeout);
                return 1;
            }
            else
            {
                DisplayLastError(TEXT("ICS_RS232Config"));
                hSerialPorts[port - 1] = INVALID_HANDLE_VALUE;
                return 0;
            }
        }
        else
        {
            DisplayLastError(TEXT("ICS_RS232Config"));
            hSerialPorts[port - 1] = INVALID_HANDLE_VALUE; 
            return 0;
        }
    }
    else
    {
        PrintfW(L"ICS_RS232Config port number %d was not opened\n", port); 
        return 0;
    }
}

DWORD ICS_RS232Config(DWORD port, DWORD baudrate, DWORD numberOfDataBits, DWORD numberOfStopBits, DWORD parity)
{
    return ICS_RS232ConfigTimeout(port, baudrate, numberOfDataBits, numberOfStopBits, parity, 10);
}

DWORD ICS_RS232SetHandshake(DWORD port, DWORD handshake, DWORD XonLimit, DWORD XoffLimit, DWORD XonChar, DWORD XoffChar)
{
    if ((port <= 0) || (port > ICS_MAX_RS232_PORT))
    {
        PrintfW(L"ICS_RS232SetHandshake was passed an invalid port number: %d\n", port);
        return 0;
    }
    if (hSerialPorts[port - 1] != INVALID_HANDLE_VALUE)
    {
        DCB comState;
        if (GetCommState(hSerialPorts[port - 1], &comState))
        {
            if (handshake == 128) // Software handshake
            {
                comState.fRtsControl = RTS_CONTROL_HANDSHAKE;
                comState.XonLim = (WORD)XonLimit;
                comState.XoffLim = (WORD)XoffLimit;
                comState.XonChar = (char)XonChar;
                comState.XoffChar = (char)XoffChar;
                if (SetCommState(hSerialPorts[port - 1], &comState))
                    return 1;
                else
                {
                    DisplayLastError(TEXT("RS232SetHandshake"));
                    hSerialPorts[port - 1] = INVALID_HANDLE_VALUE;
                    return 0;
                }
            }
            else
            {
                return 1;
            }
        }
        else
        {
            DisplayLastError(TEXT("ICS_RS232SetHandshake"));
            hSerialPorts[port - 1] = INVALID_HANDLE_VALUE;
            return 0;
        }
    }
    else
    {
        PrintfW(L"ICS_RS232SetHandshake port number %d was not opened\n", port);
        return 0;
    }
}

DWORD ICS_RS232SetSignalLine(DWORD port, DWORD line, DWORD state)
{
    return 0;
}

DWORD ICS_RS232Send(DWORD port, BYTE buffer[], DWORD size)
{
    if ((port <= 0) || (port > ICS_MAX_RS232_PORT))
    {
        PrintfW(L"ICS_RS232Send was passed an invalid port number: %d\n", port);
        return 0;
    }
    if (hSerialPorts[port - 1] != INVALID_HANDLE_VALUE)
    {
        DWORD dwBytesWritten = 0;
        if (WriteFile(hSerialPorts[port - 1], buffer, size, &dwBytesWritten, NULL))
        {
            if (fptr_ICS_RS232OnSend)
                fptr_ICS_RS232OnSend(port, buffer, size);
            return 1;
        }
        else
        {
            DisplayLastError(TEXT("ICS_RS232Send"));
            if (fptr_ICS_RS232OnError)
                fptr_ICS_RS232OnError(port, 0x1);
            return 0;
        }
    }
    else
    {
        PrintfW(L"ICS_RS232Send port number %d was not opened\n", port);
        return 0;
    }
}

DWORD ICS_RS232Receive(DWORD port, BYTE buffer[], DWORD size)
{
    if ((port <= 0) || (port > ICS_MAX_RS232_PORT))
    {
        PrintfW(L"ICS_RS232Receive was passed an invalid port number: %d\n", port);
        return 0;
    }
    if (hSerialPorts[port - 1] != INVALID_HANDLE_VALUE)
    {
        DWORD dwBytesRead = 0;
        if (ReadFile(hSerialPorts[port - 1], buffer, size, &dwBytesRead, NULL))
        {
            if (fptr_ICS_RS232OnReceive)
                fptr_ICS_RS232OnReceive(port, buffer, size);
            return 1;
        }
        else
        {
            DisplayLastError(TEXT("ICS_RS232Receive"));
            if (fptr_ICS_RS232OnError)
                fptr_ICS_RS232OnError(port, 0x2);
            return 0;
        }
    }
    else
    {
        PrintfW(L"ICS_RS232Receive port number %d was not opened\n", port);
        return 0;
    }
}

WORD ICS_RS232WriteByte(DWORD port, DWORD data)
{
    return (WORD)ICS_RS232Send(port, (LPBYTE)&data, 1);
}

WORD ICS_RS232WriteBlock(DWORD port, BYTE buffer[], DWORD size)
{
    return (WORD)ICS_RS232Send(port, buffer, size);
}

void ICS_RS232CloseAllPorts()
{
    int nPort;
    for (nPort = 0; nPort < ICS_MAX_RS232_PORT; ++nPort)
    {
        if (hSerialPorts[nPort] != INVALID_HANDLE_VALUE)
        {
            CloseHandle(hSerialPorts[nPort]);
            hSerialPorts[nPort] = INVALID_HANDLE_VALUE;
        }
    }
    UnloadInpout();
}

HINSTANCE hInpOutDll = NULL;
char bIOErrorDisp = 0;
lpOut32 gfpOut32 = NULL;
lpInp32 gfpInp32 = NULL;
lpIsInpOutDriverOpen gfpIsInpOutDriverOpen = NULL;

void LoadInpOut()
{
    if (hInpOutDll == NULL)
    {
        char szPath[MAX_PATH];
        char *pLastSlash;
        GetModuleFileNameA(NULL, szPath, sizeof(szPath));
        pLastSlash = strrchr(szPath, '\\');
        if (pLastSlash)
            *(pLastSlash + 1) = 0;
        strcat_s(szPath, MAX_PATH, "inpout32.DLL");
        hInpOutDll = LoadLibraryA(szPath);
    }
    if (hInpOutDll == NULL)
    {
        if (bIOErrorDisp == 0)
        {
            PrintfW(L"InpOut32.DLL is not installed!");
            bIOErrorDisp = 1;
        }
    }
    else if (gfpIsInpOutDriverOpen == NULL)
    {
		gfpOut32 = (lpOut32)GetProcAddress(hInpOutDll, "Out32");
		gfpInp32 = (lpInp32)GetProcAddress(hInpOutDll, "Inp32");
		gfpIsInpOutDriverOpen = (lpIsInpOutDriverOpen)GetProcAddress(hInpOutDll, "IsInpOutDriverOpen");
    }
}

void UnloadInpout()
{
    if (hInpOutDll)
    {
        gfpOut32 = NULL;
        gfpInp32 = NULL;
        gfpIsInpOutDriverOpen = NULL;
        FreeLibrary(hInpOutDll);
    }
}

void SpyAppSig_CallAllHandlers()
{
    SpyAppSig_AS_appSig_mpiRead_bytesBMPNAC(0.0);
    SpyAppSig_AS_appSig_mpiRead_bytesDUNS(0.0);
    SpyAppSig_AS_appSig_mpiRead_bytesECUID(0.0);
    SpyAppSig_AS_appSig_mpiRead_bytesEMPNAC(0.0);
    SpyAppSig_AS_appSig_mpiRead_bytesMTC(0.0);
    SpyAppSig_AS_appSig_mpiRead_bytesVPPS(0.0);
    SpyAppSig_AS_appSig_mpiWrite_BMPNAC(0.0);
    SpyAppSig_AS_appSig_mpiWrite_EMPNAC(0.0);
    SpyAppSig_AS_appSig_mpiWrite_MTC(0.0);
    SpyAppSig_AS_appSig_sapaWrite_bytesSeedKey(0.0);
    SpyAppSig_AS_appSig_sapaWrite_bytesSeed(0.0);
}

void __stdcall CM_AS_appSig_mpiRead_bytesBMPNAC()
{
    SpyAppSig_AS_appSig_mpiRead_bytesBMPNAC(AS_appSig_mpiRead_bytesBMPNAC_Get());
}

void __stdcall CM_AS_appSig_mpiRead_bytesDUNS()
{
    SpyAppSig_AS_appSig_mpiRead_bytesDUNS(AS_appSig_mpiRead_bytesDUNS_Get());
}

void __stdcall CM_AS_appSig_mpiRead_bytesECUID()
{
    SpyAppSig_AS_appSig_mpiRead_bytesECUID(AS_appSig_mpiRead_bytesECUID_Get());
}

void __stdcall CM_AS_appSig_mpiRead_bytesEMPNAC()
{
    SpyAppSig_AS_appSig_mpiRead_bytesEMPNAC(AS_appSig_mpiRead_bytesEMPNAC_Get());
}

void __stdcall CM_AS_appSig_mpiRead_bytesMTC()
{
    SpyAppSig_AS_appSig_mpiRead_bytesMTC(AS_appSig_mpiRead_bytesMTC_Get());
}

void __stdcall CM_AS_appSig_mpiRead_bytesVPPS()
{
    SpyAppSig_AS_appSig_mpiRead_bytesVPPS(AS_appSig_mpiRead_bytesVPPS_Get());
}

void __stdcall CM_AS_appSig_mpiWrite_BMPNAC()
{
    SpyAppSig_AS_appSig_mpiWrite_BMPNAC(AS_appSig_mpiWrite_BMPNAC_Get());
}

void __stdcall CM_AS_appSig_mpiWrite_EMPNAC()
{
    SpyAppSig_AS_appSig_mpiWrite_EMPNAC(AS_appSig_mpiWrite_EMPNAC_Get());
}

void __stdcall CM_AS_appSig_mpiWrite_MTC()
{
    SpyAppSig_AS_appSig_mpiWrite_MTC(AS_appSig_mpiWrite_MTC_Get());
}

void __stdcall CM_AS_appSig_sapaWrite_bytesSeedKey()
{
    SpyAppSig_AS_appSig_sapaWrite_bytesSeedKey(AS_appSig_sapaWrite_bytesSeedKey_Get());
}

void __stdcall CM_AS_appSig_sapaWrite_bytesSeed()
{
    SpyAppSig_AS_appSig_sapaWrite_bytesSeed(AS_appSig_sapaWrite_bytesSeed_Get());
}

void (* CM_RegisterCallback) (unsigned int uiHandle, unsigned short iValueType, unsigned short iIndex, void * pCallBackPointer) ;
void (* CM_GetSetValue) (unsigned int uiHandle, unsigned short iValueType, unsigned short iIndex, void * pValueToSet) ;
int (* CM_TextAPI) (unsigned int uiHandle, wchar_t * pCommand, wchar_t * pResponse, int iResponseMaxLength) ;
int (* CM_FindIndexForObjectFromName) (unsigned int uiHandle, int iObjectType,wchar_t * pName, int * p_iObjectIndex);
int (* CM_GetMessageName) (unsigned int uiHandle, int iMessageId, int iMessageContext, wchar_t * pName, int iBufferSize);
int (* CM_ShowPanel) (unsigned int uiHandle, wchar_t * pWindowName, wchar_t * pPanelName);
int (* CM_SetControlProperty) (unsigned int uiHandle, wchar_t * pPanelName, wchar_t * pWindowName, int prop, void *pValue);
int (* CM_OutputWindow) (unsigned int uiHandle, wchar_t * p_TextToWrite, int iColor, int iLength) ;
int (* CM_TransmitMessage) (unsigned int  uiHandle, int iNetwork,int iID, int iNumDataBytes,int iBitField,unsigned char * p_btData);
int (* CM_GetSignalValue) (unsigned int uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,unsigned short iSignalIndex,void * pValueToSet);
int (* CM_TxFromSignals) (unsigned int uiHandle, unsigned short iMessageType,
				       unsigned short iMessageIndex, unsigned char * bt_DefaultBytes, int iByteCount,
				       int iNetworkIndex, void * pSignalValues, int iNumSignalCount);
int (* CM_TxFromRawSignals) (unsigned int uiHandle, unsigned short iMessageType,
				       unsigned short iMessageIndex, unsigned char * bt_DefaultBytes, int iByteCount,
				       int iNetworkIndex, void * pSignalValues, int iNumSignalCount);
int (* CM_MessageGenericInit) (unsigned int uiHandle, unsigned short iMessageType,
					   unsigned short iMessageIndex, void * p_MessageStats, int * p_iNetworkID,
					   int * p_iNumDataBytes, int  p_iNumDataMax, int * p_iPeriodMs, int * p_iID,
					   int * p_iBitField, unsigned char * p_btData, double * p_dSignals, int dSignalMaxCount,
					   int * p_iActualSignalMaxCount,__int64 * p_iTimeStampNanoSecondsHW,unsigned int * p_iTimeStampMillisecondsOS);
int (* CM_MessageRawInit) (unsigned int uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
					   uint64 * p_dSignals, int dSignalMaxCount, int * p_iActualSignalMaxCount);
uint64 (* CM_SignalPhysicalToRaw) (unsigned int uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
					   unsigned short iSignalIndex, double dPhysicalValue);
int (* CM_UpdateMessageSignalsFromBytes) (unsigned int uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
                    unsigned char * p_btData, int iNumDataBytes);
int (* CM_UpdateBytesFromSignals) (unsigned int uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
                    double * p_dSignals, int dSignalMaxCount, unsigned char * p_btData, int iNumDataBytes);
int (* CM_UpdateBytesFromRawSignals) (unsigned int uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
                    uint64 * p_iSignals, int dSignalMaxCount, unsigned char * p_btData, int iNumDataBytes);
int (* CM_GetEcuCount) (unsigned int uiHandle);
int (* CM_GetMemoryBlockCount) (unsigned int uiHandle, int ecu);
int (* CM_GetMemoryBlockInfo) (unsigned int uiHandle, int ecu, int block, unsigned int *address, unsigned int *size);
int (* CM_GetMemoryBlockData) (unsigned int uiHandle, int ecu, int block, unsigned char *buffer, unsigned int address, unsigned int size);
int (* CM_SetMemoryBlockData) (unsigned int uiHandle, int ecu, int block, unsigned char *buffer, unsigned int address, unsigned int size);

void __stdcall CM_ExtensionInit(unsigned int uiHandle, struct stCallBackPointers  * p_stCallBackPointers)
{
    g_uiHandle = uiHandle;
    // setup the callback function to communicate to the CoreMini
    CM_RegisterCallback = (void ( *)(unsigned int, unsigned short, unsigned short, void *)) p_stCallBackPointers->pRegisterCallBack;
    CM_GetSetValue = (void ( *)(unsigned int , unsigned short, unsigned short, void *)) p_stCallBackPointers->pGetSetValueCallBack; 
    CM_TextAPI = (int ( *)(unsigned int, wchar_t *, wchar_t *, int)) p_stCallBackPointers->pTextAPICallBack;
    CM_FindIndexForObjectFromName = (int ( *)(unsigned int, int, wchar_t *, int *)) p_stCallBackPointers->pFindIndexForObjectFromNameCallBack;
    CM_GetMessageName = (int ( *)(unsigned int uiHandle, int iMessageId, int iMessageContext, wchar_t * pName, int iBufferSize)) p_stCallBackPointers->pGetMessageName;
    CM_ShowPanel = (int ( *)(unsigned int, wchar_t *, wchar_t *)) p_stCallBackPointers->pShowPanelCallBack;
    CM_SetControlProperty = (int ( *)(unsigned int, wchar_t *, wchar_t *, int, void *)) p_stCallBackPointers->pSetControlProp;
    CM_OutputWindow = (int ( *)(unsigned int, wchar_t *, int, int)) p_stCallBackPointers->pOutputWindowCallBack;
    CM_TransmitMessage = (int (* )(unsigned int, int, int, int, int, unsigned char *)) p_stCallBackPointers->pTransmitMessageCallBack  ;
    CM_GetSignalValue = (int (* )(unsigned int, unsigned short, unsigned short, unsigned short, void *)) p_stCallBackPointers->pGetSignalValue;
    CM_TxFromSignals = (int (* )(unsigned int uiHandle, unsigned short iMessageType,
                    unsigned short iMessageIndex, unsigned char * bt_DefaultBytes, int iByteCount,
                    int iNetworkIndex, void * pSignalValues,
                    int iNumSignalCount)) p_stCallBackPointers->pTransmitMessagesFromSignalValues; 
    CM_TxFromRawSignals = (int (* )(unsigned int uiHandle, unsigned short iMessageType,
                    unsigned short iMessageIndex, unsigned char * bt_DefaultBytes, int iByteCount,
                    int iNetworkIndex, void * pSignalValues,
                    int iNumSignalCount)) p_stCallBackPointers->pTransmitMessagesFromRawSignalValues;
    CM_MessageGenericInit = (int (* )(unsigned int uiHandle, unsigned short iMessageType,
                    unsigned short iMessageIndex, void *p_MessageStats, int *p_iNetworkID,
                    int *p_iNumDataBytes, int  p_iNumDataMax, int *p_iPeriodMs, int *p_iID,
                    int *p_iBitField, unsigned char *p_btData, double *p_dSignals, int dSignalMaxCount,
                    int *p_iActualSignalMaxCount, __int64 *p_iTimeStampNanoSecondsHW, unsigned int *p_iTimeStampMillisecondsOS)) p_stCallBackPointers->pMessageGenericInit; 
    CM_MessageRawInit = (int (* )(unsigned int uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
					   uint64 * p_dSignals, int dSignalMaxCount, int * p_iActualSignalMaxCount)) p_stCallBackPointers->pMessageRawInit;
    CM_SignalPhysicalToRaw = (uint64 (* )(unsigned int uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
					   unsigned short iSignalIndex, double dPhysicalValue)) p_stCallBackPointers->pSignalPhysicalToRaw;
    CM_UpdateMessageSignalsFromBytes = (int (* )(unsigned int uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
                    unsigned char * p_btData, int iNumDataBytes)) p_stCallBackPointers->pUpdateMessageSignalsFromBytes;
    CM_UpdateBytesFromSignals = (int (* )(unsigned int uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
                    double * p_dSignals, int dSignalMaxCount, unsigned char * p_btData, int iNumDataBytes)) p_stCallBackPointers->pUpdateBytesFromSignals;
    CM_UpdateBytesFromRawSignals = (int (* )(unsigned int uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
                    uint64 * p_iSignals, int dSignalMaxCount, unsigned char * p_btData, int iNumDataBytes)) p_stCallBackPointers->pUpdateBytesFromRawSignals;
    CM_GetEcuCount = (int (* )(unsigned int uiHandle)) p_stCallBackPointers->pGetEcuCount;
    CM_GetMemoryBlockCount = (int (* )(unsigned int uiHandle, int ecu)) p_stCallBackPointers->pGetMemoryBlockCount;
    CM_GetMemoryBlockInfo = (int (* )(unsigned int uiHandle, int ecu, int block, unsigned int *address, unsigned int *size)) p_stCallBackPointers->pGetMemoryBlockInfo;
    CM_GetMemoryBlockData = (int (* )(unsigned int uiHandle, int ecu, int block, unsigned char *buffer, unsigned int address, unsigned int size)) p_stCallBackPointers->pGetMemoryBlockData;
    CM_SetMemoryBlockData = (int (* )(unsigned int uiHandle, int ecu, int block, unsigned char *buffer, unsigned int address, unsigned int size)) p_stCallBackPointers->pSetMemoryBlockData;
    // fix up the index variables by searching for the names
    // network indexes
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN",&NET_HS_CAN);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"MS CAN",&NET_MS_CAN);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"SW CAN",&NET_SW_CAN);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"J1850 VPW",&NET_J1850_VPW);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"ISO9141/KW2K",&NET_ISO9141_KW2K);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LSFT CAN",&NET_LSFT_CAN);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"J1850 PWM",&NET_J1850_PWM);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"J1708",&NET_J1708);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"neoVI",&NET_neoVI);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN2 (neoVI 3G)",&NET_HS_CAN2__neoVI_3G_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN3 (neoVI 3G)",&NET_HS_CAN3__neoVI_3G_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN2 (neoVI 3G)",&NET_LIN2__neoVI_3G_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN3 (neoVI 3G)",&NET_LIN3__neoVI_3G_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN4 (neoVI 3G)",&NET_LIN4__neoVI_3G_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"CGI (neoVI 3G)",&NET_CGI__neoVI_3G_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN",&NET_LIN);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"ISO9141/KW2K 2",&NET_ISO9141_KW2K_2);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"ISO9141/KW2K 3",&NET_ISO9141_KW2K_3);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"ISO9141/KW2K 4",&NET_ISO9141_KW2K_4);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN4",&NET_HS_CAN4);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN5",&NET_HS_CAN5);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"UART (neoVI 3G)",&NET_UART__neoVI_3G_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"UART2 (neoVI 3G)",&NET_UART2__neoVI_3G_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"neoMOST",&NET_neoMOST);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"MOST (VNET A)",&NET_MOST__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"FlexRay1A (VNET A)",&NET_FlexRay1A__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"FlexRay1B (VNET A)",&NET_FlexRay1B__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"FlexRay2A (VNET A)",&NET_FlexRay2A__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"FlexRay2B (VNET A)",&NET_FlexRay2B__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN (VNET A)",&NET_HS_CAN__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"MS CAN (VNET A)",&NET_MS_CAN__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"SW CAN (VNET A)",&NET_SW_CAN__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"J1850 VPW (VNET A)",&NET_J1850_VPW__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LSFT CAN (VNET A)",&NET_LSFT_CAN__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"J1708 (VNET A)",&NET_J1708__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"neoVI (VNET A)",&NET_neoVI__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN2 (VNET A)",&NET_HS_CAN2__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN3 (VNET A)",&NET_HS_CAN3__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN (VNET A)",&NET_LIN__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN2 (VNET A)",&NET_LIN2__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN3 (VNET A)",&NET_LIN3__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN4 (VNET A)",&NET_LIN4__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"CGI (VNET A)",&NET_CGI__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"ISO9141/KW2K (VNET A)",&NET_ISO9141_KW2K__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"ISO9141/KW2K 2 (VNET A)",&NET_ISO9141_KW2K_2__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"ISO9141/KW2K 3 (VNET A)",&NET_ISO9141_KW2K_3__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"ISO9141/KW2K 4 (VNET A)",&NET_ISO9141_KW2K_4__VNET_A_);

    // database indexes
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message_neoVI",&DB_Report_Message_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__PWM__neoVI",&DB_Report_Message__PWM__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__VCAN_RF__neoVI",&DB_Report_Message__VCAN_RF__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__neoVI_Fire2__neoVI",&DB_Report_Message__neoVI_Fire2__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__GPS_Latitude__neoVI",&DB_Report_Message__GPS_Latitude__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__GPS_Longitude__neoVI",&DB_Report_Message__GPS_Longitude__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__GPS_Flags__neoVI",&DB_Report_Message__GPS_Flags__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__GPS_Altitude__neoVI",&DB_Report_Message__GPS_Altitude__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__GPS_Speed_Bearing__neoVI",&DB_Report_Message__GPS_Speed_Bearing__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__GPS_Accuracy__neoVI",&DB_Report_Message__GPS_Accuracy__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__GPS_Time__neoVI",&DB_Report_Message__GPS_Time__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__WirelessneoVI_Sectors__neoVI",&DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__WirelessneoVI_Signals__neoVI",&DB_Report_Message__WirelessneoVI_Signals__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI",&DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_neoVI_Logger_Message_Data_Lost_neoVI",&DB_neoVI_Logger_Message_Data_Lost_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI",&DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_neoVI_Logger_woke_up_neoVI",&DB_neoVI_Logger_woke_up_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message_1_Analog_Card__neoVI",&DB_Report_Message_1_Analog_Card__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message_2_Analog_Card__neoVI",&DB_Report_Message_2_Analog_Card__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message_3_Analog_Card__neoVI",&DB_Report_Message_3_Analog_Card__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message_4_Analog_Card__neoVI",&DB_Report_Message_4_Analog_Card__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Time_Resync_neoVI",&DB_Time_Resync_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_VNET_Clock_Edge_neoVI",&DB_VNET_Clock_Edge_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_VNET_A_Stats_neoVI",&DB_VNET_A_Stats_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_VNET_A_Reboot_neoVI",&DB_VNET_A_Reboot_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_neoVI_Went_To_Sleep_neoVI",&DB_neoVI_Went_To_Sleep_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Device_subsystem_restarted__neoVI",&DB_Device_subsystem_restarted__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Ethernet_DAQ_Report_neoVI",&DB_Ethernet_DAQ_Report_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_neoVI_Status_Update_neoVI",&DB_neoVI_Status_Update_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Scc_Status_neoVI",&DB_Scc_Status_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__Analog_Card_PWM_Inputs__neoVI",&DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__Analog_Card_PWM1__neoVI",&DB_Report_Message__Analog_Card_PWM1__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__Analog_Card_PWM2__neoVI",&DB_Report_Message__Analog_Card_PWM2__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__Analog_Card_PWM3__neoVI",&DB_Report_Message__Analog_Card_PWM3__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__Analog_Card_PWM4__neoVI",&DB_Report_Message__Analog_Card_PWM4__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__Analog_Card_PWM5__neoVI",&DB_Report_Message__Analog_Card_PWM5__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__Analog_Card_PWM6__neoVI",&DB_Report_Message__Analog_Card_PWM6__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__Analog_Card_PWM7__neoVI",&DB_Report_Message__Analog_Card_PWM7__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__Analog_Card_PWM8__neoVI",&DB_Report_Message__Analog_Card_PWM8__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_neoVI_Device_Status_neoVI",&DB_neoVI_Device_Status_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_neoVI_Device_Status_2_neoVI",&DB_neoVI_Device_Status_2_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Trace_Logger_Status_neoVI",&DB_Trace_Logger_Status_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Trigger_neoVI",&DB_Trigger_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Exterior_Lighting_HS_CAN",&DB_Exterior_Lighting_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Front_Seat_Heat_Cool_Control_HS_CAN",&DB_Front_Seat_Heat_Cool_Control_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_PPEI_Engine_Environmental_Stat_HS_CAN",&DB_PPEI_Engine_Environmental_Stat_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Instrument_Panel_Sensor_HS_CAN",&DB_Instrument_Panel_Sensor_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN",&DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN",&DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN",&DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN",&DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Front_Seat_Heat_Cool_Switches_HS_CAN",&DB_Front_Seat_Heat_Cool_Switches_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Auxiliary_Heater_Status_HS_CAN",&DB_Auxiliary_Heater_Status_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Rear_Window_Defog_Status_HS_CAN",&DB_Rear_Window_Defog_Status_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_PPEI_Engine_General_Status_1_HS_CAN",&DB_PPEI_Engine_General_Status_1_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Climate_Control_General_Status_HS_CAN",&DB_Climate_Control_General_Status_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Network_Management_BCM_HS_CAN",&DB_Network_Management_BCM_HS_CAN_Index);

    // messages indexes
     CM_FindIndexForObjectFromName(g_uiHandle,2,L"MG_step8_14_Climate_Control_General_Status_HS_CAN",&MG_step8_14_Climate_Control_General_Status_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,2,L"MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN",&MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,2,L"MG_step12_Auxiliary_Heater_Status_HS_CAN",&MG_step12_Auxiliary_Heater_Status_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,2,L"MG_step10_PCRM006_LIN",&MG_step10_PCRM006_LIN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,2,L"MG_stepX_diagResponse_HS_CAN",&MG_stepX_diagResponse_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,2,L"MG_C_diag_response1Data_HS_CAN",&MG_C_diag_response1Data_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,2,L"MG_step13_Rear_Window_Defog_Status_HS_CAN",&MG_step13_Rear_Window_Defog_Status_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,2,L"MG_mpi_diagResponse_HS_CAN",&MG_mpi_diagResponse_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,2,L"MG_mpi_diagResponse_consFrame1_HS_CAN",&MG_mpi_diagResponse_consFrame1_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,2,L"MG_mpi_diagResponse_consFrame2_HS_CAN",&MG_mpi_diagResponse_consFrame2_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,2,L"MG_step9_PCRM005_LIN2__neoVI_3G_",&MG_step9_PCRM005_LIN2__neoVI_3G__Index);
     CM_FindIndexForObjectFromName(g_uiHandle,2,L"MG_step10_1_PCRM006_1_LIN3__neoVI_3G_",&MG_step10_1_PCRM006_1_LIN3__neoVI_3G__Index);

    // tx messages indexes
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step1_Network_Management_BCM_HS_CAN",&TX_step1_Network_Management_BCM_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN",&TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step3_Exterior_Lighting_HS_CAN",&TX_step3_Exterior_Lighting_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN",&TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step5_Instrument_Panel_Sensor_HS_CAN",&TX_step5_Instrument_Panel_Sensor_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN",&TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step7_PPEI_Engine_General_Status_1_HS_CAN",&TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_stepX_diagRequest1_HS_CAN",&TX_stepX_diagRequest1_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step15_diagRequest2_HS_CAN",&TX_step15_diagRequest2_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step16_diagRequest2_HS_CAN",&TX_step16_diagRequest2_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step17_diagRequest2_HS_CAN",&TX_step17_diagRequest2_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step18_diagRequest2_HS_CAN",&TX_step18_diagRequest2_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step19_diagRequest2_HS_CAN",&TX_step19_diagRequest2_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step20_diagRequest2_HS_CAN",&TX_step20_diagRequest2_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step21_diagRequest2_HS_CAN",&TX_step21_diagRequest2_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step22_diagRequest2_HS_CAN",&TX_step22_diagRequest2_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step23_diagRequest2_HS_CAN",&TX_step23_diagRequest2_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step24_diagRequest2_HS_CAN",&TX_step24_diagRequest2_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step25_diagRequest2_HS_CAN",&TX_step25_diagRequest2_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step26_diagRequest2_HS_CAN",&TX_step26_diagRequest2_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step27_diagRequest2_HS_CAN",&TX_step27_diagRequest2_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step28_diagRequest2_HS_CAN",&TX_step28_diagRequest2_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step29_diagRequest2_HS_CAN",&TX_step29_diagRequest2_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step30_diagRequest2_HS_CAN",&TX_step30_diagRequest2_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step31_diagRequest2_HS_CAN",&TX_step31_diagRequest2_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step32_diagRequest2_HS_CAN",&TX_step32_diagRequest2_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step33_diagRequest2_HS_CAN",&TX_step33_diagRequest2_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step34_diagRequest2_HS_CAN",&TX_step34_diagRequest2_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step35_diagRequest2_HS_CAN",&TX_step35_diagRequest2_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step36_diagRequest2_HS_CAN",&TX_step36_diagRequest2_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step37_diagRequest2_HS_CAN",&TX_step37_diagRequest2_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step38_diagRequest2_HS_CAN",&TX_step38_diagRequest2_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step343536_diagRequest2_HS_CAN",&TX_step343536_diagRequest2_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_mpiWrite_diagRequest_step1_1_HS_CAN",&TX_mpiWrite_diagRequest_step1_1_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_mpiWrite_diagRequest_step1_2_HS_CAN",&TX_mpiWrite_diagRequest_step1_2_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_mpiWrite_diagRequest_step1_3_HS_CAN",&TX_mpiWrite_diagRequest_step1_3_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_mpiWrite_diagRequest_step2_1_HS_CAN",&TX_mpiWrite_diagRequest_step2_1_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_mpiWrite_diagRequest_constructive_HS_CAN",&TX_mpiWrite_diagRequest_constructive_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_mpiWrite_diagRequest_step3_1_HS_CAN",&TX_mpiWrite_diagRequest_step3_1_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_mpiWrite_diagRequest_step4_1_HS_CAN",&TX_mpiWrite_diagRequest_step4_1_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_mpiWrite_diagRequest_step5_1_HS_CAN",&TX_mpiWrite_diagRequest_step5_1_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_mpiWrite_diagRequest_step6_1_HS_CAN",&TX_mpiWrite_diagRequest_step6_1_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_mpiWrite_diagRequest_step6_2_HS_CAN",&TX_mpiWrite_diagRequest_step6_2_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_mpiWrite_diagRequest_step6_3_HS_CAN",&TX_mpiWrite_diagRequest_step6_3_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_mpiWrite_diagRequest_step6_4_HS_CAN",&TX_mpiWrite_diagRequest_step6_4_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_mpiWrite_diagRequest_step7_1_HS_CAN",&TX_mpiWrite_diagRequest_step7_1_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_mpiWrite_diagRequest_step8_1_HS_CAN",&TX_mpiWrite_diagRequest_step8_1_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_mpiRead_diagRequest_step1_1_HS_CAN",&TX_mpiRead_diagRequest_step1_1_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_mpiRead_diagRequest_step2_1_HS_CAN",&TX_mpiRead_diagRequest_step2_1_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_mpiRead_diagRequest_flowControl_HS_CAN",&TX_mpiRead_diagRequest_flowControl_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_mpiRead_diagRequest_step3_1_HS_CAN",&TX_mpiRead_diagRequest_step3_1_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_mpiRead_diagRequest_step4_1_HS_CAN",&TX_mpiRead_diagRequest_step4_1_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_mpiRead_diagRequest_step5_1_HS_CAN",&TX_mpiRead_diagRequest_step5_1_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_mpiRead_diagRequest_step6_1_HS_CAN",&TX_mpiRead_diagRequest_step6_1_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_mpiRead_diagRequest_step7_1_HS_CAN",&TX_mpiRead_diagRequest_step7_1_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_mpiRead_diagRequest_step8_1_HS_CAN",&TX_mpiRead_diagRequest_step8_1_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_mpiRead_diagRequest_step9_1_HS_CAN",&TX_mpiRead_diagRequest_step9_1_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_mpiWrite_diagRequest_stepX_1_HS_CAN",&TX_mpiWrite_diagRequest_stepX_1_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_TestPresentMessage_HS_CAN",&TX_TestPresentMessage_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_mpiWrite_diagRequest_stepModel_1_HS_CAN",&TX_mpiWrite_diagRequest_stepModel_1_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step7_1_message_1_122_HS_CAN",&TX_step7_1_message_1_122_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step7_1_message_2_4c1_HS_CAN",&TX_step7_1_message_2_4c1_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step7_1_message_3_190_HS_CAN",&TX_step7_1_message_3_190_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step7_1_message_4_371_HS_CAN",&TX_step7_1_message_4_371_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step7_1_message_5_3c5_HS_CAN",&TX_step7_1_message_5_3c5_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step39_diagRequest2_HS_CAN",&TX_step39_diagRequest2_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step40_diagRequest2_HS_CAN",&TX_step40_diagRequest2_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_step41_diagRequest2_HS_CAN",&TX_step41_diagRequest2_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_sapaWrite_diagRequest_step2_1_HS_CAN",&TX_sapaWrite_diagRequest_step2_1_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_sapaWrite_diagRequest_constructive_1_HS_CAN",&TX_sapaWrite_diagRequest_constructive_1_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_sapaWrite_diagRequest_constructive_2_HS_CAN",&TX_sapaWrite_diagRequest_constructive_2_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_sapaWrite_diagRequest_constructive_3_HS_CAN",&TX_sapaWrite_diagRequest_constructive_3_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_sapaRead_diagRequest_step2_HS_CAN",&TX_sapaRead_diagRequest_step2_HS_CAN_Index);

    // function block indexes
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fsMain_test",&FB_fsMain_test_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fsMain_process",&FB_fsMain_process_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fsMain_daemon",&FB_fsMain_daemon_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fsMain_loopStep32to38",&FB_fsMain_loopStep32to38_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fsMain_saveSettings",&FB_fsMain_saveSettings_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fsMain_subPeriodicMsgOn",&FB_fsMain_subPeriodicMsgOn_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fsMain_subPeriodicMsgOff",&FB_fsMain_subPeriodicMsgOff_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fs_resetCurrValuesAutoTest",&FB_fs_resetCurrValuesAutoTest_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fs_linkDetect",&FB_fs_linkDetect_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fsMain_autoTest",&FB_fsMain_autoTest_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fs_resetTargetValues",&FB_fs_resetTargetValues_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fs_resetCurrValues",&FB_fs_resetCurrValues_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fs_resetPassedFlags",&FB_fs_resetPassedFlags_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fs_periodicSteps32_38",&FB_fs_periodicSteps32_38_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fs_step8_Execute",&FB_fs_step8_Execute_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fs_step9_Execute",&FB_fs_step9_Execute_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fs_step10_Execute",&FB_fs_step10_Execute_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fs_step_10_1_Execute",&FB_fs_step_10_1_Execute_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fs_step15_sendOnce",&FB_fs_step15_sendOnce_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fs_step16_sendOnce",&FB_fs_step16_sendOnce_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fs_step17_sendOnce",&FB_fs_step17_sendOnce_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fs_step18_sendOnce",&FB_fs_step18_sendOnce_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fs_step19_sendOnce",&FB_fs_step19_sendOnce_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fs_step20_sendOnce",&FB_fs_step20_sendOnce_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fs_step21_sendOnce",&FB_fs_step21_sendOnce_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fs_step22_sendOnce",&FB_fs_step22_sendOnce_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fs_step23_sendOnce",&FB_fs_step23_sendOnce_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fs_step24_sendOnce",&FB_fs_step24_sendOnce_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fs_step25_sendOnce",&FB_fs_step25_sendOnce_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fs_step26_sendOnce",&FB_fs_step26_sendOnce_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fs_step27_sendOnce",&FB_fs_step27_sendOnce_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fs_step28_sendOnce",&FB_fs_step28_sendOnce_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fs_step29_sendOnce",&FB_fs_step29_sendOnce_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fs_step30_sendOnce",&FB_fs_step30_sendOnce_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fs_step31_sendOnce",&FB_fs_step31_sendOnce_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fs_step32_sendOnce",&FB_fs_step32_sendOnce_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fs_step33_sendOnce",&FB_fs_step33_sendOnce_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fs_step34_sendOnce",&FB_fs_step34_sendOnce_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fs_step35_sendOnce",&FB_fs_step35_sendOnce_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fs_step36_sendOnce",&FB_fs_step36_sendOnce_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fs_step37_sendOnce",&FB_fs_step37_sendOnce_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fs_step38_sendOnce",&FB_fs_step38_sendOnce_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fs_step39_sendOnce",&FB_fs_step39_sendOnce_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fs_step40_sendOnce",&FB_fs_step40_sendOnce_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fs_step41_sendOnce",&FB_fs_step41_sendOnce_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fs_step343536_sendOnce",&FB_fs_step343536_sendOnce_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_fs_step3738_sendOnce",&FB_fs_step3738_sendOnce_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_mpiWrite_mainMPIWrite",&FB_mpiWrite_mainMPIWrite_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_mpiWrite_resetPassedFlags",&FB_mpiWrite_resetPassedFlags_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_mpiWrite_sub_step1",&FB_mpiWrite_sub_step1_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_mpiWrite_sub_stepX_Str",&FB_mpiWrite_sub_stepX_Str_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_mpiWrite_sub_stepX_Number",&FB_mpiWrite_sub_stepX_Number_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_mpiWrite_sub_step2",&FB_mpiWrite_sub_step2_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_mpiWrite_sub_step3",&FB_mpiWrite_sub_step3_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_mpiWrite_sub_step4",&FB_mpiWrite_sub_step4_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_mpiWrite_sub_step5",&FB_mpiWrite_sub_step5_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_mpiWrite_sub_step6",&FB_mpiWrite_sub_step6_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_mpiWrite_sub_step7",&FB_mpiWrite_sub_step7_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_mpiWrite_sub_step8",&FB_mpiWrite_sub_step8_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_mpiRead_mainMPIRead",&FB_mpiRead_mainMPIRead_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_mpiRead_resetValues",&FB_mpiRead_resetValues_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_mpiRead_resetPassedFlags",&FB_mpiRead_resetPassedFlags_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_mpiRead_sub_step1",&FB_mpiRead_sub_step1_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_mpiRead_sub_step2",&FB_mpiRead_sub_step2_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_mpiRead_sub_step3",&FB_mpiRead_sub_step3_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_mpiRead_sub_step4",&FB_mpiRead_sub_step4_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_mpiRead_sub_step5",&FB_mpiRead_sub_step5_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_mpiRead_sub_step6",&FB_mpiRead_sub_step6_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_mpiRead_sub_step7",&FB_mpiRead_sub_step7_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_mpiRead_sub_step8",&FB_mpiRead_sub_step8_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_mpiRead_sub_step9",&FB_mpiRead_sub_step9_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_mpiWrite_mainModelWrite",&FB_mpiWrite_mainModelWrite_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_mpiWrite_sub_stepModel",&FB_mpiWrite_sub_stepModel_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_sapa_mainWrite",&FB_sapa_mainWrite_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_sapa_mainRead",&FB_sapa_mainRead_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_sapaRead_resetValues",&FB_sapaRead_resetValues_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_sapaWrite_sub_step1",&FB_sapaWrite_sub_step1_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_sapaWrite_sub_step2",&FB_sapaWrite_sub_step2_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_sapaRead_sub_step1",&FB_sapaRead_sub_step1_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_sapaRead_sub_step2",&FB_sapaRead_sub_step2_Index);

    // diagnostic job indexes
     CM_FindIndexForObjectFromName(g_uiHandle,6,L"DG_$22_Read_Data_By_PID",&DG_$22_Read_Data_By_PID_Index);

    // app signals indexes
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_targetValueTypeMin",&AS_appSig_C_targetValueTypeMin_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_targetValueTypeNormal",&AS_appSig_C_targetValueTypeNormal_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_targetValueTypeMax",&AS_appSig_C_targetValueTypeMax_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_targetValueType",&AS_appSig_targetValueType_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_DrvHCSMInd1",&AS_appSig_DrvHCSMInd1_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_testDiagStepsDelay",&AS_appSig_C_testDiagStepsDelay_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_autoDiagStepsDelay",&AS_appSig_C_autoDiagStepsDelay_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_responseTimeout",&AS_appSig_C_responseTimeout_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_steps_currRawValue",&AS_appSig_steps_currRawValue_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_steps_targetRawValue",&AS_appSig_steps_targetRawValue_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_steps_isPassed",&AS_appSig_steps_isPassed_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_bool_targetValue",&AS_appSig_C_bool_targetValue_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_temp_targetRawValueMin",&AS_appSig_C_temp_targetRawValueMin_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_temp_targetRawValueNormal",&AS_appSig_C_temp_targetRawValueNormal_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_temp_targetRawValueMax",&AS_appSig_C_temp_targetRawValueMax_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_step15_targetRawValue",&AS_appSig_C_step15_targetRawValue_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_step16_targetRawValue",&AS_appSig_C_step16_targetRawValue_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_step16_targetPhyValueStr",&AS_appSig_C_step16_targetPhyValueStr_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_step17_targetRawValue",&AS_appSig_C_step17_targetRawValue_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_step17_targetPhyValueStr",&AS_appSig_C_step17_targetPhyValueStr_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_step18_targetRawValue",&AS_appSig_C_step18_targetRawValue_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_step19_targetRawValueMin",&AS_appSig_C_step19_targetRawValueMin_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_step19_targetRawValueNormal",&AS_appSig_C_step19_targetRawValueNormal_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_step19_targetRawValueMax",&AS_appSig_C_step19_targetRawValueMax_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_step26_targetRawValueMin",&AS_appSig_C_step26_targetRawValueMin_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_step26_targetRawValueNormal",&AS_appSig_C_step26_targetRawValueNormal_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_step26_targetRawValueMax",&AS_appSig_C_step26_targetRawValueMax_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_step29_targetRawValueMin",&AS_appSig_C_step29_targetRawValueMin_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_step25_targetRawValueMin",&AS_appSig_C_step25_targetRawValueMin_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_step29_targetRawValueMax",&AS_appSig_C_step29_targetRawValueMax_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_step30_targetRawValueMin",&AS_appSig_C_step30_targetRawValueMin_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_step30_targetRawValueNormal",&AS_appSig_C_step30_targetRawValueNormal_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_step30_targetRawValueMax",&AS_appSig_C_step30_targetRawValueMax_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_step31_targetRawValue",&AS_appSig_C_step31_targetRawValue_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_targetValueType_tmp",&AS_appSig_targetValueType_tmp_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_isAutoTestPassed",&AS_appSig_isAutoTestPassed_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_tmp_byteHex",&AS_appSig_tmp_byteHex_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_steps_currPhyValueStr",&AS_appSig_steps_currPhyValueStr_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_step15_currPhyValue",&AS_appSig_step15_currPhyValue_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_step16_currPhyValue",&AS_appSig_step16_currPhyValue_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_step17_currPhyValue",&AS_appSig_step17_currPhyValue_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_step18_currPhyValue",&AS_appSig_step18_currPhyValue_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_step19_currPhyValue",&AS_appSig_step19_currPhyValue_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_step20_currPhyValue",&AS_appSig_step20_currPhyValue_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_step21_currPhyValue",&AS_appSig_step21_currPhyValue_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_step22_currPhyValue",&AS_appSig_step22_currPhyValue_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_step23_currPhyValue",&AS_appSig_step23_currPhyValue_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_step24_currPhyValue",&AS_appSig_step24_currPhyValue_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_step25_currPhyValue",&AS_appSig_step25_currPhyValue_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_step26_currPhyValue",&AS_appSig_step26_currPhyValue_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_step27_currPhyValue",&AS_appSig_step27_currPhyValue_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_step28_currPhyValue",&AS_appSig_step28_currPhyValue_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_step29_currPhyValue",&AS_appSig_step29_currPhyValue_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_step30_currPhyValue",&AS_appSig_step30_currPhyValue_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_step31_currPhyValue",&AS_appSig_step31_currPhyValue_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_step32_currPhyValue",&AS_appSig_step32_currPhyValue_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_step33_currPhyValue",&AS_appSig_step33_currPhyValue_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_step34_currPhyValue",&AS_appSig_step34_currPhyValue_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_step35_currPhyValue",&AS_appSig_step35_currPhyValue_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_step36_currPhyValue",&AS_appSig_step36_currPhyValue_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_step37_currPhyValue",&AS_appSig_step37_currPhyValue_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_step38_currPhyValue",&AS_appSig_step38_currPhyValue_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_invalidStr",&AS_appSig_C_invalidStr_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_linkCanState",&AS_appSig_linkCanState_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_isAutoTestPassedGUI",&AS_appSig_isAutoTestPassedGUI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_isStep32to38QueryStart",&AS_appSig_isStep32to38QueryStart_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_step25_targetRawValueNormal",&AS_appSig_C_step25_targetRawValueNormal_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_step25_targetRawValueMax",&AS_appSig_C_step25_targetRawValueMax_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_step29_targetRawValueNormal",&AS_appSig_C_step29_targetRawValueNormal_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_step27_targetRawValueNormal",&AS_appSig_C_step27_targetRawValueNormal_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_step27_targetRawValueMin",&AS_appSig_C_step27_targetRawValueMin_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_step27_targetRawValueMax",&AS_appSig_C_step27_targetRawValueMax_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_step28_targetRawValueNormal",&AS_appSig_C_step28_targetRawValueNormal_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_step28_targetRawValueMin",&AS_appSig_C_step28_targetRawValueMin_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_step28_targetRawValueMax",&AS_appSig_C_step28_targetRawValueMax_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiWrite_MTC",&AS_appSig_mpiWrite_MTC_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiWrite_EMPN",&AS_appSig_mpiWrite_EMPN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiWrite_BMPN",&AS_appSig_mpiWrite_BMPN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiWrite_EMPNAC",&AS_appSig_mpiWrite_EMPNAC_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiWrite_BMPNAC",&AS_appSig_mpiWrite_BMPNAC_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiWrite_SN",&AS_appSig_mpiWrite_SN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiWrite_ENGINE",&AS_appSig_mpiWrite_ENGINE_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiReadSteps_valueStr",&AS_appSig_mpiReadSteps_valueStr_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiWrite_lock",&AS_appSig_mpiWrite_lock_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiWriteSteps_isPassed",&AS_appSig_mpiWriteSteps_isPassed_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiReadSteps_isPassed",&AS_appSig_mpiReadSteps_isPassed_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiRead_isCheckPassed",&AS_appSig_mpiRead_isCheckPassed_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiRead_isCheckPassedGUI",&AS_appSig_mpiRead_isCheckPassedGUI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiWrite_bytesENGINE",&AS_appSig_mpiWrite_bytesENGINE_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiWrite_ENGINENumber",&AS_appSig_mpiWrite_ENGINENumber_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiWrite_bytesMTC",&AS_appSig_mpiWrite_bytesMTC_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiWrite_bytesEMPNAC",&AS_appSig_mpiWrite_bytesEMPNAC_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiWrite_bytesBMPNAC",&AS_appSig_mpiWrite_bytesBMPNAC_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiRead_bytesMTC",&AS_appSig_mpiRead_bytesMTC_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiRead_MTC",&AS_appSig_mpiRead_MTC_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_mpiWriteSubStepsDelay",&AS_appSig_C_mpiWriteSubStepsDelay_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_mpiWriteSubStepDelay_MTC",&AS_appSig_C_mpiWriteSubStepDelay_MTC_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_mpiWriteStepsDelay",&AS_appSig_C_mpiWriteStepsDelay_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiRead_bytesECUID",&AS_appSig_mpiRead_bytesECUID_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiRead_ECUID",&AS_appSig_mpiRead_ECUID_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiRead_EMPN",&AS_appSig_mpiRead_EMPN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiRead_BMPN",&AS_appSig_mpiRead_BMPN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiRead_bytesEMPNAC",&AS_appSig_mpiRead_bytesEMPNAC_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiRead_bytesBMPNAC",&AS_appSig_mpiRead_bytesBMPNAC_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiRead_bytesVPPS",&AS_appSig_mpiRead_bytesVPPS_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiRead_bytesDUNS",&AS_appSig_mpiRead_bytesDUNS_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiRead_VPPS",&AS_appSig_mpiRead_VPPS_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiRead_DUNS",&AS_appSig_mpiRead_DUNS_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiRead_EMPNAC",&AS_appSig_mpiRead_EMPNAC_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiRead_BMPNAC",&AS_appSig_mpiRead_BMPNAC_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiRead_ECUID_SN",&AS_appSig_mpiRead_ECUID_SN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiRead_ECUID_BMPN",&AS_appSig_mpiRead_ECUID_BMPN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiRead_EMPNStr",&AS_appSig_mpiRead_EMPNStr_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiRead_BMPNStr",&AS_appSig_mpiRead_BMPNStr_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiRead_ECUID_SNStr",&AS_appSig_mpiRead_ECUID_SNStr_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiRead_ECUID_BMPNStr",&AS_appSig_mpiRead_ECUID_BMPNStr_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiWrite_Model",&AS_appSig_mpiWrite_Model_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_mpiWriteState",&AS_appSig_mpiWriteState_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_mpiReadStepsDelay",&AS_appSig_C_mpiReadStepsDelay_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_mpiReadSubStepsDelay",&AS_appSig_C_mpiReadSubStepsDelay_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_sapaWriteSteps_isPassed",&AS_appSig_sapaWriteSteps_isPassed_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_sapaWrite_SeedKey",&AS_appSig_sapaWrite_SeedKey_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_sapaWrite_bytesSeedKey",&AS_appSig_sapaWrite_bytesSeedKey_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_sapaWrite_Seed",&AS_appSig_sapaWrite_Seed_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_sapaWrite_bytesSeed",&AS_appSig_sapaWrite_bytesSeed_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_sapaRead_Seed",&AS_appSig_sapaRead_Seed_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_sapaRead_bytesSeed",&AS_appSig_sapaRead_bytesSeed_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_sapaReadSteps_isPassed",&AS_appSig_sapaReadSteps_isPassed_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_sapaWrite_lock",&AS_appSig_sapaWrite_lock_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_sapaWriteStepsDelay",&AS_appSig_C_sapaWriteStepsDelay_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_sapaWriteSubStepDelay_SeedKey",&AS_appSig_C_sapaWriteSubStepDelay_SeedKey_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_step39_targetRawValueMin",&AS_appSig_C_step39_targetRawValueMin_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_step39_targetRawValueNormal",&AS_appSig_C_step39_targetRawValueNormal_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_step39_targetRawValueMax",&AS_appSig_C_step39_targetRawValueMax_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_step40_targetRawValueMin",&AS_appSig_C_step40_targetRawValueMin_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_step40_targetRawValueNormal",&AS_appSig_C_step40_targetRawValueNormal_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_C_step40_targetRawValueMax",&AS_appSig_C_step40_targetRawValueMax_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_step39_currPhyValue",&AS_appSig_step39_currPhyValue_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_step40_currPhyValue",&AS_appSig_step40_currPhyValue_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_appSig_step41_currPhyValue",&AS_appSig_step41_currPhyValue_Index);

CM_RegisterCallback( g_uiHandle,CM_CALLBACKTYPE_APP_SIGNAL, AS_appSig_mpiRead_bytesBMPNAC_Index,CM_AS_appSig_mpiRead_bytesBMPNAC);
CM_RegisterCallback( g_uiHandle,CM_CALLBACKTYPE_APP_SIGNAL, AS_appSig_mpiRead_bytesDUNS_Index,CM_AS_appSig_mpiRead_bytesDUNS);
CM_RegisterCallback( g_uiHandle,CM_CALLBACKTYPE_APP_SIGNAL, AS_appSig_mpiRead_bytesECUID_Index,CM_AS_appSig_mpiRead_bytesECUID);
CM_RegisterCallback( g_uiHandle,CM_CALLBACKTYPE_APP_SIGNAL, AS_appSig_mpiRead_bytesEMPNAC_Index,CM_AS_appSig_mpiRead_bytesEMPNAC);
CM_RegisterCallback( g_uiHandle,CM_CALLBACKTYPE_APP_SIGNAL, AS_appSig_mpiRead_bytesMTC_Index,CM_AS_appSig_mpiRead_bytesMTC);
CM_RegisterCallback( g_uiHandle,CM_CALLBACKTYPE_APP_SIGNAL, AS_appSig_mpiRead_bytesVPPS_Index,CM_AS_appSig_mpiRead_bytesVPPS);
CM_RegisterCallback( g_uiHandle,CM_CALLBACKTYPE_APP_SIGNAL, AS_appSig_mpiWrite_BMPNAC_Index,CM_AS_appSig_mpiWrite_BMPNAC);
CM_RegisterCallback( g_uiHandle,CM_CALLBACKTYPE_APP_SIGNAL, AS_appSig_mpiWrite_EMPNAC_Index,CM_AS_appSig_mpiWrite_EMPNAC);
CM_RegisterCallback( g_uiHandle,CM_CALLBACKTYPE_APP_SIGNAL, AS_appSig_mpiWrite_MTC_Index,CM_AS_appSig_mpiWrite_MTC);
CM_RegisterCallback( g_uiHandle,CM_CALLBACKTYPE_APP_SIGNAL, AS_appSig_sapaWrite_bytesSeedKey_Index,CM_AS_appSig_sapaWrite_bytesSeedKey);
CM_RegisterCallback( g_uiHandle,CM_CALLBACKTYPE_APP_SIGNAL, AS_appSig_sapaWrite_bytesSeed_Index,CM_AS_appSig_sapaWrite_bytesSeed);
}
void __stdcall CM_EveryMessage(int iNetwork, int iID, __int64 iTimeStampNanoSecondsHW, unsigned int iTimeStampMillisecondsOS,
									  int iNumDataBytes, int iBitField, unsigned char *p_btData)
{
    GenericMessage stMsg = {0};
    stMsg.iNetwork = iNetwork;
    stMsg.iID = iID;
    stMsg.iNumDataBytes = iNumDataBytes;
    if (stMsg.iNumDataBytes > sizeof(stMsg.btData))
        stMsg.iNumDataBytes = sizeof(stMsg.btData);
    stMsg.iBitField = iBitField;
    stMsg.iTimeStampMillisecondsOS = iTimeStampMillisecondsOS;
    stMsg.iTimeStampNanoSecondsHW = iTimeStampNanoSecondsHW;
    if (g_bUseExtendedIdBit && (stMsg.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        stMsg.iID = mkExtId(stMsg.iID);
    memcpy(stMsg.btData, p_btData, stMsg.iNumDataBytes);
    Spy_EveryMessage(&stMsg);

    if ((stMsg.iBitField & ATTR_CANFD_FRAME) || (stMsg.iNumDataBytes < iNumDataBytes))
    {
        GenericLongMessage stLongMsg = {0};
        stLongMsg.iNetwork = stMsg.iNetwork;
        stLongMsg.iID = stMsg.iID;
        stLongMsg.iNumDataBytes = iNumDataBytes;
        if (stLongMsg.iNumDataBytes > sizeof(stLongMsg.btData))
            stLongMsg.iNumDataBytes = sizeof(stLongMsg.btData);
        stLongMsg.iBitField = stMsg.iBitField;
        stLongMsg.iTimeStampMillisecondsOS = stMsg.iTimeStampMillisecondsOS;
        stLongMsg.iTimeStampNanoSecondsHW = stMsg.iTimeStampNanoSecondsHW;
        memcpy(stLongMsg.btData, p_btData, stLongMsg.iNumDataBytes);
        Spy_EveryLongMessage(&stLongMsg);
    }
}

void Spy_Lock()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_SPY_LOCK,0,0);
}
void Spy_Unlock()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_SPY_UNLOCK,0,0);
}

void SpyShowPanel(char * pWindowName, char * pPanelName)
{
    wchar_t szWideWindowName[1024];
    wchar_t szWidePanelName[1024];
    int iCount;

    iCount = MultiByteToWideChar(0, 0, pWindowName, (int)strlen(pWindowName), NULL, 0);
    MultiByteToWideChar(0, 0, pWindowName, (int)strlen(pWindowName), szWideWindowName, iCount);
    szWideWindowName[iCount] = 0;

    iCount = MultiByteToWideChar(0, 0, pPanelName, (int)strlen(pPanelName), NULL, 0);
    MultiByteToWideChar(0, 0, pPanelName, (int)strlen(pPanelName), szWidePanelName, iCount);
    szWidePanelName[iCount] = 0;

    // call the api
    CM_ShowPanel(g_uiHandle,szWideWindowName,szWidePanelName);
}

void SpyShowPanelW(wchar_t * pWindowName, wchar_t * pPanelName)
{
    CM_ShowPanel(g_uiHandle,pWindowName,pPanelName);
}

void SpySetControlProperty(char * pPanelName, char * pControlTag, int prop, void *pValue)
{
    wchar_t szWidePanelName[1024];
    wchar_t szWideControlTag[1024];
    int iCount;

    iCount = MultiByteToWideChar(0, 0, pPanelName, (int)strlen(pPanelName), NULL, 0);
    MultiByteToWideChar(0, 0, pPanelName, (int)strlen(pPanelName), szWidePanelName, iCount);
    szWidePanelName[iCount] = 0;

    iCount = MultiByteToWideChar(0, 0, pControlTag, (int)strlen(pControlTag), NULL, 0);
    MultiByteToWideChar(0, 0, pControlTag, (int)strlen(pControlTag), szWideControlTag, iCount);
    szWideControlTag[iCount] = 0;
    if (SPY_CTL_PROP_SET_CAPTION == prop)
    {
        wchar_t szWideValue[1024];
        iCount = MultiByteToWideChar(0, 0, pValue, (int)strlen(pValue), NULL, 0);
        MultiByteToWideChar(0, 0, pValue, (int)strlen(pValue), szWideValue, iCount);
        szWideValue[iCount] = 0;
        CM_SetControlProperty(g_uiHandle, szWidePanelName, szWideControlTag, prop, szWideValue);
    }
    else // call the api
        CM_SetControlProperty(g_uiHandle, szWidePanelName, szWideControlTag, prop, pValue);
}

void SpySetControlPropertyW(wchar_t * pPanelName, wchar_t * pControlTag, int prop, void *pValue)
{
    CM_SetControlProperty(g_uiHandle, pPanelName, pControlTag, prop, pValue);
}
int AS_appSig_C_targetValueTypeMin_Index = 0; // sig22
int AS_appSig_C_targetValueTypeNormal_Index = 1; // sig23
int AS_appSig_C_targetValueTypeMax_Index = 2; // sig24
int AS_appSig_targetValueType_Index = 3; // sig21
int AS_appSig_DrvHCSMInd1_Index = 4; // sig4
int AS_appSig_C_testDiagStepsDelay_Index = 5; // sig10
int AS_appSig_C_autoDiagStepsDelay_Index = 6; // sig11
int AS_appSig_C_responseTimeout_Index = 7; // sig12
int AS_appSig_steps_currRawValue_Index = 8; // sig30
int AS_appSig_steps_targetRawValue_Index = 9; // sig31
int AS_appSig_steps_isPassed_Index = 10; // sig32
int AS_appSig_C_bool_targetValue_Index = 11; // sig36
int AS_appSig_C_temp_targetRawValueMin_Index = 12; // sig37
int AS_appSig_C_temp_targetRawValueNormal_Index = 13; // sig38
int AS_appSig_C_temp_targetRawValueMax_Index = 14; // sig39
int AS_appSig_C_step15_targetRawValue_Index = 15; // sig33
int AS_appSig_C_step16_targetRawValue_Index = 16; // sig34
int AS_appSig_C_step16_targetPhyValueStr_Index = 17; // sig53
int AS_appSig_C_step17_targetRawValue_Index = 18; // sig35
int AS_appSig_C_step17_targetPhyValueStr_Index = 19; // sig61
int AS_appSig_C_step18_targetRawValue_Index = 20; // sig9
int AS_appSig_C_step19_targetRawValueMin_Index = 21; // sig19
int AS_appSig_C_step19_targetRawValueNormal_Index = 22; // sig18
int AS_appSig_C_step19_targetRawValueMax_Index = 23; // sig17
int AS_appSig_C_step26_targetRawValueMin_Index = 24; // sig40
int AS_appSig_C_step26_targetRawValueNormal_Index = 25; // sig41
int AS_appSig_C_step26_targetRawValueMax_Index = 26; // sig42
int AS_appSig_C_step29_targetRawValueMin_Index = 27; // sig43
int AS_appSig_C_step25_targetRawValueMin_Index = 28; // sig44
int AS_appSig_C_step29_targetRawValueMax_Index = 29; // sig45
int AS_appSig_C_step30_targetRawValueMin_Index = 30; // sig46
int AS_appSig_C_step30_targetRawValueNormal_Index = 31; // sig47
int AS_appSig_C_step30_targetRawValueMax_Index = 32; // sig48
int AS_appSig_C_step31_targetRawValue_Index = 33; // sig49
int AS_appSig_targetValueType_tmp_Index = 34; // sig50
int AS_appSig_isAutoTestPassed_Index = 35; // sig52
int AS_appSig_tmp_byteHex_Index = 36; // sig54
int AS_appSig_steps_currPhyValueStr_Index = 37; // sig57
int AS_appSig_step15_currPhyValue_Index = 38; // sig60
int AS_appSig_step16_currPhyValue_Index = 39; // sig63
int AS_appSig_step17_currPhyValue_Index = 40; // sig64
int AS_appSig_step18_currPhyValue_Index = 41; // sig65
int AS_appSig_step19_currPhyValue_Index = 42; // sig66
int AS_appSig_step20_currPhyValue_Index = 43; // sig67
int AS_appSig_step21_currPhyValue_Index = 44; // sig68
int AS_appSig_step22_currPhyValue_Index = 45; // sig69
int AS_appSig_step23_currPhyValue_Index = 46; // sig70
int AS_appSig_step24_currPhyValue_Index = 47; // sig71
int AS_appSig_step25_currPhyValue_Index = 48; // sig72
int AS_appSig_step26_currPhyValue_Index = 49; // sig73
int AS_appSig_step27_currPhyValue_Index = 50; // sig74
int AS_appSig_step28_currPhyValue_Index = 51; // sig75
int AS_appSig_step29_currPhyValue_Index = 52; // sig76
int AS_appSig_step30_currPhyValue_Index = 53; // sig77
int AS_appSig_step31_currPhyValue_Index = 54; // sig86
int AS_appSig_step32_currPhyValue_Index = 55; // sig79
int AS_appSig_step33_currPhyValue_Index = 56; // sig80
int AS_appSig_step34_currPhyValue_Index = 57; // sig81
int AS_appSig_step35_currPhyValue_Index = 58; // sig82
int AS_appSig_step36_currPhyValue_Index = 59; // sig83
int AS_appSig_step37_currPhyValue_Index = 60; // sig84
int AS_appSig_step38_currPhyValue_Index = 61; // sig85
int AS_appSig_C_invalidStr_Index = 62; // sig87
int AS_appSig_linkCanState_Index = 63; // sig88
int AS_appSig_isAutoTestPassedGUI_Index = 64; // sig89
int AS_appSig_isStep32to38QueryStart_Index = 65; // sig90
int AS_appSig_C_step25_targetRawValueNormal_Index = 66; // sig92
int AS_appSig_C_step25_targetRawValueMax_Index = 67; // sig93
int AS_appSig_C_step29_targetRawValueNormal_Index = 68; // sig94
int AS_appSig_C_step27_targetRawValueNormal_Index = 69; // sig95
int AS_appSig_C_step27_targetRawValueMin_Index = 70; // sig96
int AS_appSig_C_step27_targetRawValueMax_Index = 71; // sig97
int AS_appSig_C_step28_targetRawValueNormal_Index = 72; // sig98
int AS_appSig_C_step28_targetRawValueMin_Index = 73; // sig99
int AS_appSig_C_step28_targetRawValueMax_Index = 74; // sig100
int AS_appSig_mpiWrite_MTC_Index = 75; // sig101
int AS_appSig_mpiWrite_EMPN_Index = 76; // sig103
int AS_appSig_mpiWrite_BMPN_Index = 77; // sig104
int AS_appSig_mpiWrite_EMPNAC_Index = 78; // sig105
int AS_appSig_mpiWrite_BMPNAC_Index = 79; // sig106
int AS_appSig_mpiWrite_SN_Index = 80; // sig108
int AS_appSig_mpiWrite_ENGINE_Index = 81; // sig114
int AS_appSig_mpiReadSteps_valueStr_Index = 82; // sig107
int AS_appSig_mpiWrite_lock_Index = 83; // sig109
int AS_appSig_mpiWriteSteps_isPassed_Index = 84; // sig110
int AS_appSig_mpiReadSteps_isPassed_Index = 85; // sig111
int AS_appSig_mpiRead_isCheckPassed_Index = 86; // sig112
int AS_appSig_mpiRead_isCheckPassedGUI_Index = 87; // sig113
int AS_appSig_mpiWrite_bytesENGINE_Index = 88; // sig115
int AS_appSig_mpiWrite_ENGINENumber_Index = 89; // sig118
int AS_appSig_mpiWrite_bytesMTC_Index = 90; // sig119
int AS_appSig_mpiWrite_bytesEMPNAC_Index = 91; // sig120
int AS_appSig_mpiWrite_bytesBMPNAC_Index = 92; // sig121
int AS_appSig_mpiRead_bytesMTC_Index = 93; // sig122
int AS_appSig_mpiRead_MTC_Index = 94; // sig123
int AS_appSig_C_mpiWriteSubStepsDelay_Index = 95; // sig124
int AS_appSig_C_mpiWriteSubStepDelay_MTC_Index = 96; // sig148
int AS_appSig_C_mpiWriteStepsDelay_Index = 97; // sig125
int AS_appSig_mpiRead_bytesECUID_Index = 98; // sig126
int AS_appSig_mpiRead_ECUID_Index = 99; // sig127
int AS_appSig_mpiRead_EMPN_Index = 100; // sig128
int AS_appSig_mpiRead_BMPN_Index = 101; // sig129
int AS_appSig_mpiRead_bytesEMPNAC_Index = 102; // sig130
int AS_appSig_mpiRead_bytesBMPNAC_Index = 103; // sig131
int AS_appSig_mpiRead_bytesVPPS_Index = 104; // sig132
int AS_appSig_mpiRead_bytesDUNS_Index = 105; // sig133
int AS_appSig_mpiRead_VPPS_Index = 106; // sig134
int AS_appSig_mpiRead_DUNS_Index = 107; // sig135
int AS_appSig_mpiRead_EMPNAC_Index = 108; // sig136
int AS_appSig_mpiRead_BMPNAC_Index = 109; // sig137
int AS_appSig_mpiRead_ECUID_SN_Index = 110; // sig138
int AS_appSig_mpiRead_ECUID_BMPN_Index = 111; // sig139
int AS_appSig_mpiRead_EMPNStr_Index = 112; // sig140
int AS_appSig_mpiRead_BMPNStr_Index = 113; // sig141
int AS_appSig_mpiRead_ECUID_SNStr_Index = 114; // sig142
int AS_appSig_mpiRead_ECUID_BMPNStr_Index = 115; // sig143
int AS_appSig_mpiWrite_Model_Index = 116; // sig144
int AS_appSig_mpiWriteState_Index = 117; // sig145
int AS_appSig_C_mpiReadStepsDelay_Index = 118; // sig146
int AS_appSig_C_mpiReadSubStepsDelay_Index = 119; // sig147
int AS_appSig_sapaWriteSteps_isPassed_Index = 120; // sig167
int AS_appSig_sapaWrite_SeedKey_Index = 121; // sig150
int AS_appSig_sapaWrite_bytesSeedKey_Index = 122; // sig151
int AS_appSig_sapaWrite_Seed_Index = 123; // sig152
int AS_appSig_sapaWrite_bytesSeed_Index = 124; // sig153
int AS_appSig_sapaRead_Seed_Index = 125; // sig154
int AS_appSig_sapaRead_bytesSeed_Index = 126; // sig155
int AS_appSig_sapaReadSteps_isPassed_Index = 127; // sig156
int AS_appSig_sapaWrite_lock_Index = 128; // sig157
int AS_appSig_C_sapaWriteStepsDelay_Index = 129; // sig169
int AS_appSig_C_sapaWriteSubStepDelay_SeedKey_Index = 130; // sig168
int AS_appSig_C_step39_targetRawValueMin_Index = 131; // sig158
int AS_appSig_C_step39_targetRawValueNormal_Index = 132; // sig159
int AS_appSig_C_step39_targetRawValueMax_Index = 133; // sig160
int AS_appSig_C_step40_targetRawValueMin_Index = 134; // sig161
int AS_appSig_C_step40_targetRawValueNormal_Index = 135; // sig162
int AS_appSig_C_step40_targetRawValueMax_Index = 136; // sig163
int AS_appSig_step39_currPhyValue_Index = 137; // sig164
int AS_appSig_step40_currPhyValue_Index = 138; // sig165
int AS_appSig_step41_currPhyValue_Index = 139; // sig166
int DG_$22_Read_Data_By_PID_Index = 0;
void DG_$22_Read_Data_By_PID_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_DIAGJOB_START,DG_$22_Read_Data_By_PID_Index,NULL);
}
void DG_$22_Read_Data_By_PID_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_DIAGJOB_STOP,DG_$22_Read_Data_By_PID_Index,NULL);
}
void DG_$22_Read_Data_By_PID_Save()
{
CM_GetSetValue(g_uiHandle,CM_GETSET_DIAGJOB_SAVE,DG_$22_Read_Data_By_PID_Index,NULL);
}
int DG_$22_Read_Data_By_PID_IsRunning()
{
    int iTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_DIAG_JOB_ISRUNNING,DG_$22_Read_Data_By_PID_Index,&iTemp);
    return iTemp;
}
int DG_$22_Read_Data_By_PID_NumMessagesCollected()
{
    int iTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_DIAG_JOB_NumMessagesCollected,DG_$22_Read_Data_By_PID_Index,&iTemp);
    return iTemp;
}
int DG_$22_Read_Data_By_PID_IsSuccessful()
{
    int iTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_DIAG_JOB_Successful,DG_$22_Read_Data_By_PID_Index,&iTemp);
    return iTemp;
}
int DG_$22_Read_Data_By_PID_ECUResponseCount()
{
    int iTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_DIAG_JOB_ECUResponseCount,DG_$22_Read_Data_By_PID_Index,&iTemp);
    return iTemp;
}
double DG_$22_Read_Data_By_PID_TotalTimeAbs()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_DIAG_JOB_TotalTimeAbs,DG_$22_Read_Data_By_PID_Index,&dTemp);
    return dTemp;
}
int DG_$22_Read_Data_By_PID_Last7FSubFunctionEx78()
{
    int iTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_DIAG_JOB_Last7FSubFunctionEx78,DG_$22_Read_Data_By_PID_Index,&iTemp);
    return iTemp;
}
int DG_$22_Read_Data_By_PID_7FCountEx78()
{
    int iTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_DIAG_JOB_7FCountEx78,DG_$22_Read_Data_By_PID_Index,&iTemp);
    return iTemp;
}
int DG_$22_Read_Data_By_PID_7FCountResponsePending()
{
    int iTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_DIAG_JOB_7FCountResponsePending,DG_$22_Read_Data_By_PID_Index,&iTemp);
    return iTemp;
}
int FB_fsMain_test_Index = 0;
void FB_fsMain_test_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fsMain_test_Index,NULL);
}
void FB_fsMain_test_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fsMain_test_Index,NULL);
}
void FB_fsMain_test_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fsMain_test_Index,NULL);
}
void FB_fsMain_test_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fsMain_test_Index,NULL);
}
double FB_fsMain_test_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fsMain_test_Index,&dTemp);
    return dTemp;
}
double FB_fsMain_test_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fsMain_test_Index,&dTemp);
    return dTemp;
}
double FB_fsMain_test_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fsMain_test_Index,&dTemp);
    return dTemp;
}
int FB_fsMain_process_Index = 1;
void FB_fsMain_process_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fsMain_process_Index,NULL);
}
void FB_fsMain_process_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fsMain_process_Index,NULL);
}
void FB_fsMain_process_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fsMain_process_Index,NULL);
}
void FB_fsMain_process_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fsMain_process_Index,NULL);
}
double FB_fsMain_process_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fsMain_process_Index,&dTemp);
    return dTemp;
}
double FB_fsMain_process_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fsMain_process_Index,&dTemp);
    return dTemp;
}
double FB_fsMain_process_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fsMain_process_Index,&dTemp);
    return dTemp;
}
int FB_fsMain_daemon_Index = 2;
void FB_fsMain_daemon_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fsMain_daemon_Index,NULL);
}
void FB_fsMain_daemon_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fsMain_daemon_Index,NULL);
}
void FB_fsMain_daemon_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fsMain_daemon_Index,NULL);
}
void FB_fsMain_daemon_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fsMain_daemon_Index,NULL);
}
double FB_fsMain_daemon_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fsMain_daemon_Index,&dTemp);
    return dTemp;
}
double FB_fsMain_daemon_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fsMain_daemon_Index,&dTemp);
    return dTemp;
}
double FB_fsMain_daemon_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fsMain_daemon_Index,&dTemp);
    return dTemp;
}
int FB_fsMain_loopStep32to38_Index = 3;
void FB_fsMain_loopStep32to38_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fsMain_loopStep32to38_Index,NULL);
}
void FB_fsMain_loopStep32to38_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fsMain_loopStep32to38_Index,NULL);
}
void FB_fsMain_loopStep32to38_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fsMain_loopStep32to38_Index,NULL);
}
void FB_fsMain_loopStep32to38_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fsMain_loopStep32to38_Index,NULL);
}
double FB_fsMain_loopStep32to38_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fsMain_loopStep32to38_Index,&dTemp);
    return dTemp;
}
double FB_fsMain_loopStep32to38_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fsMain_loopStep32to38_Index,&dTemp);
    return dTemp;
}
double FB_fsMain_loopStep32to38_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fsMain_loopStep32to38_Index,&dTemp);
    return dTemp;
}
int FB_fsMain_saveSettings_Index = 4;
void FB_fsMain_saveSettings_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fsMain_saveSettings_Index,NULL);
}
void FB_fsMain_saveSettings_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fsMain_saveSettings_Index,NULL);
}
void FB_fsMain_saveSettings_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fsMain_saveSettings_Index,NULL);
}
void FB_fsMain_saveSettings_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fsMain_saveSettings_Index,NULL);
}
double FB_fsMain_saveSettings_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fsMain_saveSettings_Index,&dTemp);
    return dTemp;
}
double FB_fsMain_saveSettings_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fsMain_saveSettings_Index,&dTemp);
    return dTemp;
}
double FB_fsMain_saveSettings_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fsMain_saveSettings_Index,&dTemp);
    return dTemp;
}
int FB_fsMain_subPeriodicMsgOn_Index = 5;
void FB_fsMain_subPeriodicMsgOn_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fsMain_subPeriodicMsgOn_Index,NULL);
}
void FB_fsMain_subPeriodicMsgOn_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fsMain_subPeriodicMsgOn_Index,NULL);
}
void FB_fsMain_subPeriodicMsgOn_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fsMain_subPeriodicMsgOn_Index,NULL);
}
void FB_fsMain_subPeriodicMsgOn_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fsMain_subPeriodicMsgOn_Index,NULL);
}
double FB_fsMain_subPeriodicMsgOn_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fsMain_subPeriodicMsgOn_Index,&dTemp);
    return dTemp;
}
double FB_fsMain_subPeriodicMsgOn_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fsMain_subPeriodicMsgOn_Index,&dTemp);
    return dTemp;
}
double FB_fsMain_subPeriodicMsgOn_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fsMain_subPeriodicMsgOn_Index,&dTemp);
    return dTemp;
}
int FB_fsMain_subPeriodicMsgOff_Index = 6;
void FB_fsMain_subPeriodicMsgOff_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fsMain_subPeriodicMsgOff_Index,NULL);
}
void FB_fsMain_subPeriodicMsgOff_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fsMain_subPeriodicMsgOff_Index,NULL);
}
void FB_fsMain_subPeriodicMsgOff_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fsMain_subPeriodicMsgOff_Index,NULL);
}
void FB_fsMain_subPeriodicMsgOff_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fsMain_subPeriodicMsgOff_Index,NULL);
}
double FB_fsMain_subPeriodicMsgOff_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fsMain_subPeriodicMsgOff_Index,&dTemp);
    return dTemp;
}
double FB_fsMain_subPeriodicMsgOff_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fsMain_subPeriodicMsgOff_Index,&dTemp);
    return dTemp;
}
double FB_fsMain_subPeriodicMsgOff_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fsMain_subPeriodicMsgOff_Index,&dTemp);
    return dTemp;
}
int FB_fs_resetCurrValuesAutoTest_Index = 7;
void FB_fs_resetCurrValuesAutoTest_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fs_resetCurrValuesAutoTest_Index,NULL);
}
void FB_fs_resetCurrValuesAutoTest_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fs_resetCurrValuesAutoTest_Index,NULL);
}
void FB_fs_resetCurrValuesAutoTest_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fs_resetCurrValuesAutoTest_Index,NULL);
}
void FB_fs_resetCurrValuesAutoTest_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fs_resetCurrValuesAutoTest_Index,NULL);
}
double FB_fs_resetCurrValuesAutoTest_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fs_resetCurrValuesAutoTest_Index,&dTemp);
    return dTemp;
}
double FB_fs_resetCurrValuesAutoTest_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fs_resetCurrValuesAutoTest_Index,&dTemp);
    return dTemp;
}
double FB_fs_resetCurrValuesAutoTest_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fs_resetCurrValuesAutoTest_Index,&dTemp);
    return dTemp;
}
int FB_fs_linkDetect_Index = 8;
void FB_fs_linkDetect_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fs_linkDetect_Index,NULL);
}
void FB_fs_linkDetect_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fs_linkDetect_Index,NULL);
}
void FB_fs_linkDetect_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fs_linkDetect_Index,NULL);
}
void FB_fs_linkDetect_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fs_linkDetect_Index,NULL);
}
double FB_fs_linkDetect_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fs_linkDetect_Index,&dTemp);
    return dTemp;
}
double FB_fs_linkDetect_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fs_linkDetect_Index,&dTemp);
    return dTemp;
}
double FB_fs_linkDetect_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fs_linkDetect_Index,&dTemp);
    return dTemp;
}
int FB_fsMain_autoTest_Index = 9;
void FB_fsMain_autoTest_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fsMain_autoTest_Index,NULL);
}
void FB_fsMain_autoTest_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fsMain_autoTest_Index,NULL);
}
void FB_fsMain_autoTest_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fsMain_autoTest_Index,NULL);
}
void FB_fsMain_autoTest_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fsMain_autoTest_Index,NULL);
}
double FB_fsMain_autoTest_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fsMain_autoTest_Index,&dTemp);
    return dTemp;
}
double FB_fsMain_autoTest_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fsMain_autoTest_Index,&dTemp);
    return dTemp;
}
double FB_fsMain_autoTest_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fsMain_autoTest_Index,&dTemp);
    return dTemp;
}
int FB_fs_resetTargetValues_Index = 10;
void FB_fs_resetTargetValues_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fs_resetTargetValues_Index,NULL);
}
void FB_fs_resetTargetValues_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fs_resetTargetValues_Index,NULL);
}
void FB_fs_resetTargetValues_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fs_resetTargetValues_Index,NULL);
}
void FB_fs_resetTargetValues_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fs_resetTargetValues_Index,NULL);
}
double FB_fs_resetTargetValues_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fs_resetTargetValues_Index,&dTemp);
    return dTemp;
}
double FB_fs_resetTargetValues_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fs_resetTargetValues_Index,&dTemp);
    return dTemp;
}
double FB_fs_resetTargetValues_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fs_resetTargetValues_Index,&dTemp);
    return dTemp;
}
int FB_fs_resetCurrValues_Index = 11;
void FB_fs_resetCurrValues_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fs_resetCurrValues_Index,NULL);
}
void FB_fs_resetCurrValues_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fs_resetCurrValues_Index,NULL);
}
void FB_fs_resetCurrValues_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fs_resetCurrValues_Index,NULL);
}
void FB_fs_resetCurrValues_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fs_resetCurrValues_Index,NULL);
}
double FB_fs_resetCurrValues_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fs_resetCurrValues_Index,&dTemp);
    return dTemp;
}
double FB_fs_resetCurrValues_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fs_resetCurrValues_Index,&dTemp);
    return dTemp;
}
double FB_fs_resetCurrValues_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fs_resetCurrValues_Index,&dTemp);
    return dTemp;
}
int FB_fs_resetPassedFlags_Index = 12;
void FB_fs_resetPassedFlags_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fs_resetPassedFlags_Index,NULL);
}
void FB_fs_resetPassedFlags_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fs_resetPassedFlags_Index,NULL);
}
void FB_fs_resetPassedFlags_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fs_resetPassedFlags_Index,NULL);
}
void FB_fs_resetPassedFlags_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fs_resetPassedFlags_Index,NULL);
}
double FB_fs_resetPassedFlags_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fs_resetPassedFlags_Index,&dTemp);
    return dTemp;
}
double FB_fs_resetPassedFlags_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fs_resetPassedFlags_Index,&dTemp);
    return dTemp;
}
double FB_fs_resetPassedFlags_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fs_resetPassedFlags_Index,&dTemp);
    return dTemp;
}
int FB_fs_periodicSteps32_38_Index = 13;
void FB_fs_periodicSteps32_38_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fs_periodicSteps32_38_Index,NULL);
}
void FB_fs_periodicSteps32_38_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fs_periodicSteps32_38_Index,NULL);
}
void FB_fs_periodicSteps32_38_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fs_periodicSteps32_38_Index,NULL);
}
void FB_fs_periodicSteps32_38_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fs_periodicSteps32_38_Index,NULL);
}
double FB_fs_periodicSteps32_38_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fs_periodicSteps32_38_Index,&dTemp);
    return dTemp;
}
double FB_fs_periodicSteps32_38_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fs_periodicSteps32_38_Index,&dTemp);
    return dTemp;
}
double FB_fs_periodicSteps32_38_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fs_periodicSteps32_38_Index,&dTemp);
    return dTemp;
}
int FB_fs_step8_Execute_Index = 14;
void FB_fs_step8_Execute_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fs_step8_Execute_Index,NULL);
}
void FB_fs_step8_Execute_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fs_step8_Execute_Index,NULL);
}
void FB_fs_step8_Execute_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fs_step8_Execute_Index,NULL);
}
void FB_fs_step8_Execute_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fs_step8_Execute_Index,NULL);
}
double FB_fs_step8_Execute_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fs_step8_Execute_Index,&dTemp);
    return dTemp;
}
double FB_fs_step8_Execute_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fs_step8_Execute_Index,&dTemp);
    return dTemp;
}
double FB_fs_step8_Execute_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fs_step8_Execute_Index,&dTemp);
    return dTemp;
}
int FB_fs_step9_Execute_Index = 15;
void FB_fs_step9_Execute_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fs_step9_Execute_Index,NULL);
}
void FB_fs_step9_Execute_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fs_step9_Execute_Index,NULL);
}
void FB_fs_step9_Execute_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fs_step9_Execute_Index,NULL);
}
void FB_fs_step9_Execute_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fs_step9_Execute_Index,NULL);
}
double FB_fs_step9_Execute_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fs_step9_Execute_Index,&dTemp);
    return dTemp;
}
double FB_fs_step9_Execute_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fs_step9_Execute_Index,&dTemp);
    return dTemp;
}
double FB_fs_step9_Execute_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fs_step9_Execute_Index,&dTemp);
    return dTemp;
}
int FB_fs_step10_Execute_Index = 16;
void FB_fs_step10_Execute_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fs_step10_Execute_Index,NULL);
}
void FB_fs_step10_Execute_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fs_step10_Execute_Index,NULL);
}
void FB_fs_step10_Execute_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fs_step10_Execute_Index,NULL);
}
void FB_fs_step10_Execute_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fs_step10_Execute_Index,NULL);
}
double FB_fs_step10_Execute_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fs_step10_Execute_Index,&dTemp);
    return dTemp;
}
double FB_fs_step10_Execute_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fs_step10_Execute_Index,&dTemp);
    return dTemp;
}
double FB_fs_step10_Execute_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fs_step10_Execute_Index,&dTemp);
    return dTemp;
}
int FB_fs_step_10_1_Execute_Index = 17;
void FB_fs_step_10_1_Execute_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fs_step_10_1_Execute_Index,NULL);
}
void FB_fs_step_10_1_Execute_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fs_step_10_1_Execute_Index,NULL);
}
void FB_fs_step_10_1_Execute_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fs_step_10_1_Execute_Index,NULL);
}
void FB_fs_step_10_1_Execute_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fs_step_10_1_Execute_Index,NULL);
}
double FB_fs_step_10_1_Execute_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fs_step_10_1_Execute_Index,&dTemp);
    return dTemp;
}
double FB_fs_step_10_1_Execute_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fs_step_10_1_Execute_Index,&dTemp);
    return dTemp;
}
double FB_fs_step_10_1_Execute_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fs_step_10_1_Execute_Index,&dTemp);
    return dTemp;
}
int FB_fs_step15_sendOnce_Index = 18;
void FB_fs_step15_sendOnce_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fs_step15_sendOnce_Index,NULL);
}
void FB_fs_step15_sendOnce_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fs_step15_sendOnce_Index,NULL);
}
void FB_fs_step15_sendOnce_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fs_step15_sendOnce_Index,NULL);
}
void FB_fs_step15_sendOnce_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fs_step15_sendOnce_Index,NULL);
}
double FB_fs_step15_sendOnce_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fs_step15_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step15_sendOnce_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fs_step15_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step15_sendOnce_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fs_step15_sendOnce_Index,&dTemp);
    return dTemp;
}
int FB_fs_step16_sendOnce_Index = 19;
void FB_fs_step16_sendOnce_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fs_step16_sendOnce_Index,NULL);
}
void FB_fs_step16_sendOnce_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fs_step16_sendOnce_Index,NULL);
}
void FB_fs_step16_sendOnce_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fs_step16_sendOnce_Index,NULL);
}
void FB_fs_step16_sendOnce_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fs_step16_sendOnce_Index,NULL);
}
double FB_fs_step16_sendOnce_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fs_step16_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step16_sendOnce_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fs_step16_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step16_sendOnce_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fs_step16_sendOnce_Index,&dTemp);
    return dTemp;
}
int FB_fs_step17_sendOnce_Index = 20;
void FB_fs_step17_sendOnce_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fs_step17_sendOnce_Index,NULL);
}
void FB_fs_step17_sendOnce_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fs_step17_sendOnce_Index,NULL);
}
void FB_fs_step17_sendOnce_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fs_step17_sendOnce_Index,NULL);
}
void FB_fs_step17_sendOnce_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fs_step17_sendOnce_Index,NULL);
}
double FB_fs_step17_sendOnce_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fs_step17_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step17_sendOnce_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fs_step17_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step17_sendOnce_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fs_step17_sendOnce_Index,&dTemp);
    return dTemp;
}
int FB_fs_step18_sendOnce_Index = 21;
void FB_fs_step18_sendOnce_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fs_step18_sendOnce_Index,NULL);
}
void FB_fs_step18_sendOnce_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fs_step18_sendOnce_Index,NULL);
}
void FB_fs_step18_sendOnce_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fs_step18_sendOnce_Index,NULL);
}
void FB_fs_step18_sendOnce_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fs_step18_sendOnce_Index,NULL);
}
double FB_fs_step18_sendOnce_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fs_step18_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step18_sendOnce_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fs_step18_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step18_sendOnce_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fs_step18_sendOnce_Index,&dTemp);
    return dTemp;
}
int FB_fs_step19_sendOnce_Index = 22;
void FB_fs_step19_sendOnce_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fs_step19_sendOnce_Index,NULL);
}
void FB_fs_step19_sendOnce_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fs_step19_sendOnce_Index,NULL);
}
void FB_fs_step19_sendOnce_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fs_step19_sendOnce_Index,NULL);
}
void FB_fs_step19_sendOnce_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fs_step19_sendOnce_Index,NULL);
}
double FB_fs_step19_sendOnce_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fs_step19_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step19_sendOnce_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fs_step19_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step19_sendOnce_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fs_step19_sendOnce_Index,&dTemp);
    return dTemp;
}
int FB_fs_step20_sendOnce_Index = 23;
void FB_fs_step20_sendOnce_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fs_step20_sendOnce_Index,NULL);
}
void FB_fs_step20_sendOnce_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fs_step20_sendOnce_Index,NULL);
}
void FB_fs_step20_sendOnce_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fs_step20_sendOnce_Index,NULL);
}
void FB_fs_step20_sendOnce_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fs_step20_sendOnce_Index,NULL);
}
double FB_fs_step20_sendOnce_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fs_step20_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step20_sendOnce_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fs_step20_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step20_sendOnce_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fs_step20_sendOnce_Index,&dTemp);
    return dTemp;
}
int FB_fs_step21_sendOnce_Index = 24;
void FB_fs_step21_sendOnce_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fs_step21_sendOnce_Index,NULL);
}
void FB_fs_step21_sendOnce_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fs_step21_sendOnce_Index,NULL);
}
void FB_fs_step21_sendOnce_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fs_step21_sendOnce_Index,NULL);
}
void FB_fs_step21_sendOnce_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fs_step21_sendOnce_Index,NULL);
}
double FB_fs_step21_sendOnce_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fs_step21_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step21_sendOnce_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fs_step21_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step21_sendOnce_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fs_step21_sendOnce_Index,&dTemp);
    return dTemp;
}
int FB_fs_step22_sendOnce_Index = 25;
void FB_fs_step22_sendOnce_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fs_step22_sendOnce_Index,NULL);
}
void FB_fs_step22_sendOnce_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fs_step22_sendOnce_Index,NULL);
}
void FB_fs_step22_sendOnce_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fs_step22_sendOnce_Index,NULL);
}
void FB_fs_step22_sendOnce_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fs_step22_sendOnce_Index,NULL);
}
double FB_fs_step22_sendOnce_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fs_step22_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step22_sendOnce_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fs_step22_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step22_sendOnce_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fs_step22_sendOnce_Index,&dTemp);
    return dTemp;
}
int FB_fs_step23_sendOnce_Index = 26;
void FB_fs_step23_sendOnce_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fs_step23_sendOnce_Index,NULL);
}
void FB_fs_step23_sendOnce_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fs_step23_sendOnce_Index,NULL);
}
void FB_fs_step23_sendOnce_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fs_step23_sendOnce_Index,NULL);
}
void FB_fs_step23_sendOnce_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fs_step23_sendOnce_Index,NULL);
}
double FB_fs_step23_sendOnce_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fs_step23_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step23_sendOnce_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fs_step23_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step23_sendOnce_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fs_step23_sendOnce_Index,&dTemp);
    return dTemp;
}
int FB_fs_step24_sendOnce_Index = 27;
void FB_fs_step24_sendOnce_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fs_step24_sendOnce_Index,NULL);
}
void FB_fs_step24_sendOnce_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fs_step24_sendOnce_Index,NULL);
}
void FB_fs_step24_sendOnce_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fs_step24_sendOnce_Index,NULL);
}
void FB_fs_step24_sendOnce_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fs_step24_sendOnce_Index,NULL);
}
double FB_fs_step24_sendOnce_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fs_step24_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step24_sendOnce_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fs_step24_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step24_sendOnce_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fs_step24_sendOnce_Index,&dTemp);
    return dTemp;
}
int FB_fs_step25_sendOnce_Index = 28;
void FB_fs_step25_sendOnce_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fs_step25_sendOnce_Index,NULL);
}
void FB_fs_step25_sendOnce_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fs_step25_sendOnce_Index,NULL);
}
void FB_fs_step25_sendOnce_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fs_step25_sendOnce_Index,NULL);
}
void FB_fs_step25_sendOnce_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fs_step25_sendOnce_Index,NULL);
}
double FB_fs_step25_sendOnce_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fs_step25_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step25_sendOnce_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fs_step25_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step25_sendOnce_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fs_step25_sendOnce_Index,&dTemp);
    return dTemp;
}
int FB_fs_step26_sendOnce_Index = 29;
void FB_fs_step26_sendOnce_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fs_step26_sendOnce_Index,NULL);
}
void FB_fs_step26_sendOnce_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fs_step26_sendOnce_Index,NULL);
}
void FB_fs_step26_sendOnce_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fs_step26_sendOnce_Index,NULL);
}
void FB_fs_step26_sendOnce_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fs_step26_sendOnce_Index,NULL);
}
double FB_fs_step26_sendOnce_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fs_step26_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step26_sendOnce_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fs_step26_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step26_sendOnce_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fs_step26_sendOnce_Index,&dTemp);
    return dTemp;
}
int FB_fs_step27_sendOnce_Index = 30;
void FB_fs_step27_sendOnce_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fs_step27_sendOnce_Index,NULL);
}
void FB_fs_step27_sendOnce_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fs_step27_sendOnce_Index,NULL);
}
void FB_fs_step27_sendOnce_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fs_step27_sendOnce_Index,NULL);
}
void FB_fs_step27_sendOnce_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fs_step27_sendOnce_Index,NULL);
}
double FB_fs_step27_sendOnce_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fs_step27_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step27_sendOnce_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fs_step27_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step27_sendOnce_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fs_step27_sendOnce_Index,&dTemp);
    return dTemp;
}
int FB_fs_step28_sendOnce_Index = 31;
void FB_fs_step28_sendOnce_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fs_step28_sendOnce_Index,NULL);
}
void FB_fs_step28_sendOnce_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fs_step28_sendOnce_Index,NULL);
}
void FB_fs_step28_sendOnce_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fs_step28_sendOnce_Index,NULL);
}
void FB_fs_step28_sendOnce_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fs_step28_sendOnce_Index,NULL);
}
double FB_fs_step28_sendOnce_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fs_step28_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step28_sendOnce_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fs_step28_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step28_sendOnce_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fs_step28_sendOnce_Index,&dTemp);
    return dTemp;
}
int FB_fs_step29_sendOnce_Index = 32;
void FB_fs_step29_sendOnce_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fs_step29_sendOnce_Index,NULL);
}
void FB_fs_step29_sendOnce_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fs_step29_sendOnce_Index,NULL);
}
void FB_fs_step29_sendOnce_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fs_step29_sendOnce_Index,NULL);
}
void FB_fs_step29_sendOnce_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fs_step29_sendOnce_Index,NULL);
}
double FB_fs_step29_sendOnce_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fs_step29_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step29_sendOnce_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fs_step29_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step29_sendOnce_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fs_step29_sendOnce_Index,&dTemp);
    return dTemp;
}
int FB_fs_step30_sendOnce_Index = 33;
void FB_fs_step30_sendOnce_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fs_step30_sendOnce_Index,NULL);
}
void FB_fs_step30_sendOnce_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fs_step30_sendOnce_Index,NULL);
}
void FB_fs_step30_sendOnce_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fs_step30_sendOnce_Index,NULL);
}
void FB_fs_step30_sendOnce_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fs_step30_sendOnce_Index,NULL);
}
double FB_fs_step30_sendOnce_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fs_step30_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step30_sendOnce_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fs_step30_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step30_sendOnce_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fs_step30_sendOnce_Index,&dTemp);
    return dTemp;
}
int FB_fs_step31_sendOnce_Index = 34;
void FB_fs_step31_sendOnce_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fs_step31_sendOnce_Index,NULL);
}
void FB_fs_step31_sendOnce_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fs_step31_sendOnce_Index,NULL);
}
void FB_fs_step31_sendOnce_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fs_step31_sendOnce_Index,NULL);
}
void FB_fs_step31_sendOnce_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fs_step31_sendOnce_Index,NULL);
}
double FB_fs_step31_sendOnce_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fs_step31_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step31_sendOnce_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fs_step31_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step31_sendOnce_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fs_step31_sendOnce_Index,&dTemp);
    return dTemp;
}
int FB_fs_step32_sendOnce_Index = 35;
void FB_fs_step32_sendOnce_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fs_step32_sendOnce_Index,NULL);
}
void FB_fs_step32_sendOnce_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fs_step32_sendOnce_Index,NULL);
}
void FB_fs_step32_sendOnce_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fs_step32_sendOnce_Index,NULL);
}
void FB_fs_step32_sendOnce_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fs_step32_sendOnce_Index,NULL);
}
double FB_fs_step32_sendOnce_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fs_step32_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step32_sendOnce_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fs_step32_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step32_sendOnce_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fs_step32_sendOnce_Index,&dTemp);
    return dTemp;
}
int FB_fs_step33_sendOnce_Index = 36;
void FB_fs_step33_sendOnce_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fs_step33_sendOnce_Index,NULL);
}
void FB_fs_step33_sendOnce_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fs_step33_sendOnce_Index,NULL);
}
void FB_fs_step33_sendOnce_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fs_step33_sendOnce_Index,NULL);
}
void FB_fs_step33_sendOnce_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fs_step33_sendOnce_Index,NULL);
}
double FB_fs_step33_sendOnce_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fs_step33_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step33_sendOnce_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fs_step33_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step33_sendOnce_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fs_step33_sendOnce_Index,&dTemp);
    return dTemp;
}
int FB_fs_step34_sendOnce_Index = 37;
void FB_fs_step34_sendOnce_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fs_step34_sendOnce_Index,NULL);
}
void FB_fs_step34_sendOnce_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fs_step34_sendOnce_Index,NULL);
}
void FB_fs_step34_sendOnce_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fs_step34_sendOnce_Index,NULL);
}
void FB_fs_step34_sendOnce_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fs_step34_sendOnce_Index,NULL);
}
double FB_fs_step34_sendOnce_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fs_step34_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step34_sendOnce_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fs_step34_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step34_sendOnce_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fs_step34_sendOnce_Index,&dTemp);
    return dTemp;
}
int FB_fs_step35_sendOnce_Index = 38;
void FB_fs_step35_sendOnce_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fs_step35_sendOnce_Index,NULL);
}
void FB_fs_step35_sendOnce_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fs_step35_sendOnce_Index,NULL);
}
void FB_fs_step35_sendOnce_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fs_step35_sendOnce_Index,NULL);
}
void FB_fs_step35_sendOnce_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fs_step35_sendOnce_Index,NULL);
}
double FB_fs_step35_sendOnce_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fs_step35_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step35_sendOnce_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fs_step35_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step35_sendOnce_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fs_step35_sendOnce_Index,&dTemp);
    return dTemp;
}
int FB_fs_step36_sendOnce_Index = 39;
void FB_fs_step36_sendOnce_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fs_step36_sendOnce_Index,NULL);
}
void FB_fs_step36_sendOnce_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fs_step36_sendOnce_Index,NULL);
}
void FB_fs_step36_sendOnce_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fs_step36_sendOnce_Index,NULL);
}
void FB_fs_step36_sendOnce_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fs_step36_sendOnce_Index,NULL);
}
double FB_fs_step36_sendOnce_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fs_step36_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step36_sendOnce_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fs_step36_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step36_sendOnce_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fs_step36_sendOnce_Index,&dTemp);
    return dTemp;
}
int FB_fs_step37_sendOnce_Index = 40;
void FB_fs_step37_sendOnce_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fs_step37_sendOnce_Index,NULL);
}
void FB_fs_step37_sendOnce_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fs_step37_sendOnce_Index,NULL);
}
void FB_fs_step37_sendOnce_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fs_step37_sendOnce_Index,NULL);
}
void FB_fs_step37_sendOnce_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fs_step37_sendOnce_Index,NULL);
}
double FB_fs_step37_sendOnce_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fs_step37_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step37_sendOnce_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fs_step37_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step37_sendOnce_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fs_step37_sendOnce_Index,&dTemp);
    return dTemp;
}
int FB_fs_step38_sendOnce_Index = 41;
void FB_fs_step38_sendOnce_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fs_step38_sendOnce_Index,NULL);
}
void FB_fs_step38_sendOnce_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fs_step38_sendOnce_Index,NULL);
}
void FB_fs_step38_sendOnce_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fs_step38_sendOnce_Index,NULL);
}
void FB_fs_step38_sendOnce_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fs_step38_sendOnce_Index,NULL);
}
double FB_fs_step38_sendOnce_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fs_step38_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step38_sendOnce_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fs_step38_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step38_sendOnce_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fs_step38_sendOnce_Index,&dTemp);
    return dTemp;
}
int FB_fs_step39_sendOnce_Index = 42;
void FB_fs_step39_sendOnce_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fs_step39_sendOnce_Index,NULL);
}
void FB_fs_step39_sendOnce_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fs_step39_sendOnce_Index,NULL);
}
void FB_fs_step39_sendOnce_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fs_step39_sendOnce_Index,NULL);
}
void FB_fs_step39_sendOnce_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fs_step39_sendOnce_Index,NULL);
}
double FB_fs_step39_sendOnce_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fs_step39_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step39_sendOnce_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fs_step39_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step39_sendOnce_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fs_step39_sendOnce_Index,&dTemp);
    return dTemp;
}
int FB_fs_step40_sendOnce_Index = 43;
void FB_fs_step40_sendOnce_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fs_step40_sendOnce_Index,NULL);
}
void FB_fs_step40_sendOnce_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fs_step40_sendOnce_Index,NULL);
}
void FB_fs_step40_sendOnce_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fs_step40_sendOnce_Index,NULL);
}
void FB_fs_step40_sendOnce_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fs_step40_sendOnce_Index,NULL);
}
double FB_fs_step40_sendOnce_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fs_step40_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step40_sendOnce_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fs_step40_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step40_sendOnce_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fs_step40_sendOnce_Index,&dTemp);
    return dTemp;
}
int FB_fs_step41_sendOnce_Index = 44;
void FB_fs_step41_sendOnce_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fs_step41_sendOnce_Index,NULL);
}
void FB_fs_step41_sendOnce_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fs_step41_sendOnce_Index,NULL);
}
void FB_fs_step41_sendOnce_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fs_step41_sendOnce_Index,NULL);
}
void FB_fs_step41_sendOnce_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fs_step41_sendOnce_Index,NULL);
}
double FB_fs_step41_sendOnce_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fs_step41_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step41_sendOnce_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fs_step41_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step41_sendOnce_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fs_step41_sendOnce_Index,&dTemp);
    return dTemp;
}
int FB_fs_step343536_sendOnce_Index = 45;
void FB_fs_step343536_sendOnce_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fs_step343536_sendOnce_Index,NULL);
}
void FB_fs_step343536_sendOnce_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fs_step343536_sendOnce_Index,NULL);
}
void FB_fs_step343536_sendOnce_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fs_step343536_sendOnce_Index,NULL);
}
void FB_fs_step343536_sendOnce_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fs_step343536_sendOnce_Index,NULL);
}
double FB_fs_step343536_sendOnce_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fs_step343536_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step343536_sendOnce_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fs_step343536_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step343536_sendOnce_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fs_step343536_sendOnce_Index,&dTemp);
    return dTemp;
}
int FB_fs_step3738_sendOnce_Index = 46;
void FB_fs_step3738_sendOnce_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_fs_step3738_sendOnce_Index,NULL);
}
void FB_fs_step3738_sendOnce_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_fs_step3738_sendOnce_Index,NULL);
}
void FB_fs_step3738_sendOnce_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_fs_step3738_sendOnce_Index,NULL);
}
void FB_fs_step3738_sendOnce_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_fs_step3738_sendOnce_Index,NULL);
}
double FB_fs_step3738_sendOnce_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_fs_step3738_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step3738_sendOnce_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_fs_step3738_sendOnce_Index,&dTemp);
    return dTemp;
}
double FB_fs_step3738_sendOnce_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_fs_step3738_sendOnce_Index,&dTemp);
    return dTemp;
}
int FB_mpiWrite_mainMPIWrite_Index = 47;
void FB_mpiWrite_mainMPIWrite_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_mpiWrite_mainMPIWrite_Index,NULL);
}
void FB_mpiWrite_mainMPIWrite_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_mpiWrite_mainMPIWrite_Index,NULL);
}
void FB_mpiWrite_mainMPIWrite_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_mpiWrite_mainMPIWrite_Index,NULL);
}
void FB_mpiWrite_mainMPIWrite_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_mpiWrite_mainMPIWrite_Index,NULL);
}
double FB_mpiWrite_mainMPIWrite_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_mpiWrite_mainMPIWrite_Index,&dTemp);
    return dTemp;
}
double FB_mpiWrite_mainMPIWrite_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_mpiWrite_mainMPIWrite_Index,&dTemp);
    return dTemp;
}
double FB_mpiWrite_mainMPIWrite_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_mpiWrite_mainMPIWrite_Index,&dTemp);
    return dTemp;
}
int FB_mpiWrite_resetPassedFlags_Index = 48;
void FB_mpiWrite_resetPassedFlags_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_mpiWrite_resetPassedFlags_Index,NULL);
}
void FB_mpiWrite_resetPassedFlags_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_mpiWrite_resetPassedFlags_Index,NULL);
}
void FB_mpiWrite_resetPassedFlags_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_mpiWrite_resetPassedFlags_Index,NULL);
}
void FB_mpiWrite_resetPassedFlags_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_mpiWrite_resetPassedFlags_Index,NULL);
}
double FB_mpiWrite_resetPassedFlags_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_mpiWrite_resetPassedFlags_Index,&dTemp);
    return dTemp;
}
double FB_mpiWrite_resetPassedFlags_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_mpiWrite_resetPassedFlags_Index,&dTemp);
    return dTemp;
}
double FB_mpiWrite_resetPassedFlags_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_mpiWrite_resetPassedFlags_Index,&dTemp);
    return dTemp;
}
int FB_mpiWrite_sub_step1_Index = 49;
void FB_mpiWrite_sub_step1_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_mpiWrite_sub_step1_Index,NULL);
}
void FB_mpiWrite_sub_step1_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_mpiWrite_sub_step1_Index,NULL);
}
void FB_mpiWrite_sub_step1_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_mpiWrite_sub_step1_Index,NULL);
}
void FB_mpiWrite_sub_step1_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_mpiWrite_sub_step1_Index,NULL);
}
double FB_mpiWrite_sub_step1_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_mpiWrite_sub_step1_Index,&dTemp);
    return dTemp;
}
double FB_mpiWrite_sub_step1_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_mpiWrite_sub_step1_Index,&dTemp);
    return dTemp;
}
double FB_mpiWrite_sub_step1_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_mpiWrite_sub_step1_Index,&dTemp);
    return dTemp;
}
int FB_mpiWrite_sub_stepX_Str_Index = 50;
void FB_mpiWrite_sub_stepX_Str_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_mpiWrite_sub_stepX_Str_Index,NULL);
}
void FB_mpiWrite_sub_stepX_Str_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_mpiWrite_sub_stepX_Str_Index,NULL);
}
void FB_mpiWrite_sub_stepX_Str_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_mpiWrite_sub_stepX_Str_Index,NULL);
}
void FB_mpiWrite_sub_stepX_Str_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_mpiWrite_sub_stepX_Str_Index,NULL);
}
double FB_mpiWrite_sub_stepX_Str_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_mpiWrite_sub_stepX_Str_Index,&dTemp);
    return dTemp;
}
double FB_mpiWrite_sub_stepX_Str_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_mpiWrite_sub_stepX_Str_Index,&dTemp);
    return dTemp;
}
double FB_mpiWrite_sub_stepX_Str_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_mpiWrite_sub_stepX_Str_Index,&dTemp);
    return dTemp;
}
int FB_mpiWrite_sub_stepX_Number_Index = 51;
void FB_mpiWrite_sub_stepX_Number_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_mpiWrite_sub_stepX_Number_Index,NULL);
}
void FB_mpiWrite_sub_stepX_Number_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_mpiWrite_sub_stepX_Number_Index,NULL);
}
void FB_mpiWrite_sub_stepX_Number_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_mpiWrite_sub_stepX_Number_Index,NULL);
}
void FB_mpiWrite_sub_stepX_Number_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_mpiWrite_sub_stepX_Number_Index,NULL);
}
double FB_mpiWrite_sub_stepX_Number_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_mpiWrite_sub_stepX_Number_Index,&dTemp);
    return dTemp;
}
double FB_mpiWrite_sub_stepX_Number_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_mpiWrite_sub_stepX_Number_Index,&dTemp);
    return dTemp;
}
double FB_mpiWrite_sub_stepX_Number_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_mpiWrite_sub_stepX_Number_Index,&dTemp);
    return dTemp;
}
int FB_mpiWrite_sub_step2_Index = 52;
void FB_mpiWrite_sub_step2_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_mpiWrite_sub_step2_Index,NULL);
}
void FB_mpiWrite_sub_step2_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_mpiWrite_sub_step2_Index,NULL);
}
void FB_mpiWrite_sub_step2_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_mpiWrite_sub_step2_Index,NULL);
}
void FB_mpiWrite_sub_step2_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_mpiWrite_sub_step2_Index,NULL);
}
double FB_mpiWrite_sub_step2_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_mpiWrite_sub_step2_Index,&dTemp);
    return dTemp;
}
double FB_mpiWrite_sub_step2_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_mpiWrite_sub_step2_Index,&dTemp);
    return dTemp;
}
double FB_mpiWrite_sub_step2_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_mpiWrite_sub_step2_Index,&dTemp);
    return dTemp;
}
int FB_mpiWrite_sub_step3_Index = 53;
void FB_mpiWrite_sub_step3_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_mpiWrite_sub_step3_Index,NULL);
}
void FB_mpiWrite_sub_step3_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_mpiWrite_sub_step3_Index,NULL);
}
void FB_mpiWrite_sub_step3_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_mpiWrite_sub_step3_Index,NULL);
}
void FB_mpiWrite_sub_step3_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_mpiWrite_sub_step3_Index,NULL);
}
double FB_mpiWrite_sub_step3_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_mpiWrite_sub_step3_Index,&dTemp);
    return dTemp;
}
double FB_mpiWrite_sub_step3_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_mpiWrite_sub_step3_Index,&dTemp);
    return dTemp;
}
double FB_mpiWrite_sub_step3_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_mpiWrite_sub_step3_Index,&dTemp);
    return dTemp;
}
int FB_mpiWrite_sub_step4_Index = 54;
void FB_mpiWrite_sub_step4_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_mpiWrite_sub_step4_Index,NULL);
}
void FB_mpiWrite_sub_step4_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_mpiWrite_sub_step4_Index,NULL);
}
void FB_mpiWrite_sub_step4_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_mpiWrite_sub_step4_Index,NULL);
}
void FB_mpiWrite_sub_step4_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_mpiWrite_sub_step4_Index,NULL);
}
double FB_mpiWrite_sub_step4_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_mpiWrite_sub_step4_Index,&dTemp);
    return dTemp;
}
double FB_mpiWrite_sub_step4_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_mpiWrite_sub_step4_Index,&dTemp);
    return dTemp;
}
double FB_mpiWrite_sub_step4_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_mpiWrite_sub_step4_Index,&dTemp);
    return dTemp;
}
int FB_mpiWrite_sub_step5_Index = 55;
void FB_mpiWrite_sub_step5_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_mpiWrite_sub_step5_Index,NULL);
}
void FB_mpiWrite_sub_step5_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_mpiWrite_sub_step5_Index,NULL);
}
void FB_mpiWrite_sub_step5_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_mpiWrite_sub_step5_Index,NULL);
}
void FB_mpiWrite_sub_step5_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_mpiWrite_sub_step5_Index,NULL);
}
double FB_mpiWrite_sub_step5_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_mpiWrite_sub_step5_Index,&dTemp);
    return dTemp;
}
double FB_mpiWrite_sub_step5_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_mpiWrite_sub_step5_Index,&dTemp);
    return dTemp;
}
double FB_mpiWrite_sub_step5_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_mpiWrite_sub_step5_Index,&dTemp);
    return dTemp;
}
int FB_mpiWrite_sub_step6_Index = 56;
void FB_mpiWrite_sub_step6_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_mpiWrite_sub_step6_Index,NULL);
}
void FB_mpiWrite_sub_step6_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_mpiWrite_sub_step6_Index,NULL);
}
void FB_mpiWrite_sub_step6_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_mpiWrite_sub_step6_Index,NULL);
}
void FB_mpiWrite_sub_step6_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_mpiWrite_sub_step6_Index,NULL);
}
double FB_mpiWrite_sub_step6_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_mpiWrite_sub_step6_Index,&dTemp);
    return dTemp;
}
double FB_mpiWrite_sub_step6_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_mpiWrite_sub_step6_Index,&dTemp);
    return dTemp;
}
double FB_mpiWrite_sub_step6_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_mpiWrite_sub_step6_Index,&dTemp);
    return dTemp;
}
int FB_mpiWrite_sub_step7_Index = 57;
void FB_mpiWrite_sub_step7_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_mpiWrite_sub_step7_Index,NULL);
}
void FB_mpiWrite_sub_step7_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_mpiWrite_sub_step7_Index,NULL);
}
void FB_mpiWrite_sub_step7_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_mpiWrite_sub_step7_Index,NULL);
}
void FB_mpiWrite_sub_step7_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_mpiWrite_sub_step7_Index,NULL);
}
double FB_mpiWrite_sub_step7_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_mpiWrite_sub_step7_Index,&dTemp);
    return dTemp;
}
double FB_mpiWrite_sub_step7_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_mpiWrite_sub_step7_Index,&dTemp);
    return dTemp;
}
double FB_mpiWrite_sub_step7_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_mpiWrite_sub_step7_Index,&dTemp);
    return dTemp;
}
int FB_mpiWrite_sub_step8_Index = 58;
void FB_mpiWrite_sub_step8_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_mpiWrite_sub_step8_Index,NULL);
}
void FB_mpiWrite_sub_step8_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_mpiWrite_sub_step8_Index,NULL);
}
void FB_mpiWrite_sub_step8_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_mpiWrite_sub_step8_Index,NULL);
}
void FB_mpiWrite_sub_step8_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_mpiWrite_sub_step8_Index,NULL);
}
double FB_mpiWrite_sub_step8_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_mpiWrite_sub_step8_Index,&dTemp);
    return dTemp;
}
double FB_mpiWrite_sub_step8_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_mpiWrite_sub_step8_Index,&dTemp);
    return dTemp;
}
double FB_mpiWrite_sub_step8_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_mpiWrite_sub_step8_Index,&dTemp);
    return dTemp;
}
int FB_mpiRead_mainMPIRead_Index = 59;
void FB_mpiRead_mainMPIRead_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_mpiRead_mainMPIRead_Index,NULL);
}
void FB_mpiRead_mainMPIRead_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_mpiRead_mainMPIRead_Index,NULL);
}
void FB_mpiRead_mainMPIRead_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_mpiRead_mainMPIRead_Index,NULL);
}
void FB_mpiRead_mainMPIRead_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_mpiRead_mainMPIRead_Index,NULL);
}
double FB_mpiRead_mainMPIRead_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_mpiRead_mainMPIRead_Index,&dTemp);
    return dTemp;
}
double FB_mpiRead_mainMPIRead_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_mpiRead_mainMPIRead_Index,&dTemp);
    return dTemp;
}
double FB_mpiRead_mainMPIRead_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_mpiRead_mainMPIRead_Index,&dTemp);
    return dTemp;
}
int FB_mpiRead_resetValues_Index = 60;
void FB_mpiRead_resetValues_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_mpiRead_resetValues_Index,NULL);
}
void FB_mpiRead_resetValues_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_mpiRead_resetValues_Index,NULL);
}
void FB_mpiRead_resetValues_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_mpiRead_resetValues_Index,NULL);
}
void FB_mpiRead_resetValues_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_mpiRead_resetValues_Index,NULL);
}
double FB_mpiRead_resetValues_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_mpiRead_resetValues_Index,&dTemp);
    return dTemp;
}
double FB_mpiRead_resetValues_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_mpiRead_resetValues_Index,&dTemp);
    return dTemp;
}
double FB_mpiRead_resetValues_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_mpiRead_resetValues_Index,&dTemp);
    return dTemp;
}
int FB_mpiRead_resetPassedFlags_Index = 61;
void FB_mpiRead_resetPassedFlags_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_mpiRead_resetPassedFlags_Index,NULL);
}
void FB_mpiRead_resetPassedFlags_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_mpiRead_resetPassedFlags_Index,NULL);
}
void FB_mpiRead_resetPassedFlags_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_mpiRead_resetPassedFlags_Index,NULL);
}
void FB_mpiRead_resetPassedFlags_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_mpiRead_resetPassedFlags_Index,NULL);
}
double FB_mpiRead_resetPassedFlags_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_mpiRead_resetPassedFlags_Index,&dTemp);
    return dTemp;
}
double FB_mpiRead_resetPassedFlags_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_mpiRead_resetPassedFlags_Index,&dTemp);
    return dTemp;
}
double FB_mpiRead_resetPassedFlags_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_mpiRead_resetPassedFlags_Index,&dTemp);
    return dTemp;
}
int FB_mpiRead_sub_step1_Index = 62;
void FB_mpiRead_sub_step1_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_mpiRead_sub_step1_Index,NULL);
}
void FB_mpiRead_sub_step1_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_mpiRead_sub_step1_Index,NULL);
}
void FB_mpiRead_sub_step1_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_mpiRead_sub_step1_Index,NULL);
}
void FB_mpiRead_sub_step1_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_mpiRead_sub_step1_Index,NULL);
}
double FB_mpiRead_sub_step1_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_mpiRead_sub_step1_Index,&dTemp);
    return dTemp;
}
double FB_mpiRead_sub_step1_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_mpiRead_sub_step1_Index,&dTemp);
    return dTemp;
}
double FB_mpiRead_sub_step1_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_mpiRead_sub_step1_Index,&dTemp);
    return dTemp;
}
int FB_mpiRead_sub_step2_Index = 63;
void FB_mpiRead_sub_step2_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_mpiRead_sub_step2_Index,NULL);
}
void FB_mpiRead_sub_step2_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_mpiRead_sub_step2_Index,NULL);
}
void FB_mpiRead_sub_step2_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_mpiRead_sub_step2_Index,NULL);
}
void FB_mpiRead_sub_step2_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_mpiRead_sub_step2_Index,NULL);
}
double FB_mpiRead_sub_step2_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_mpiRead_sub_step2_Index,&dTemp);
    return dTemp;
}
double FB_mpiRead_sub_step2_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_mpiRead_sub_step2_Index,&dTemp);
    return dTemp;
}
double FB_mpiRead_sub_step2_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_mpiRead_sub_step2_Index,&dTemp);
    return dTemp;
}
int FB_mpiRead_sub_step3_Index = 64;
void FB_mpiRead_sub_step3_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_mpiRead_sub_step3_Index,NULL);
}
void FB_mpiRead_sub_step3_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_mpiRead_sub_step3_Index,NULL);
}
void FB_mpiRead_sub_step3_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_mpiRead_sub_step3_Index,NULL);
}
void FB_mpiRead_sub_step3_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_mpiRead_sub_step3_Index,NULL);
}
double FB_mpiRead_sub_step3_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_mpiRead_sub_step3_Index,&dTemp);
    return dTemp;
}
double FB_mpiRead_sub_step3_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_mpiRead_sub_step3_Index,&dTemp);
    return dTemp;
}
double FB_mpiRead_sub_step3_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_mpiRead_sub_step3_Index,&dTemp);
    return dTemp;
}
int FB_mpiRead_sub_step4_Index = 65;
void FB_mpiRead_sub_step4_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_mpiRead_sub_step4_Index,NULL);
}
void FB_mpiRead_sub_step4_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_mpiRead_sub_step4_Index,NULL);
}
void FB_mpiRead_sub_step4_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_mpiRead_sub_step4_Index,NULL);
}
void FB_mpiRead_sub_step4_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_mpiRead_sub_step4_Index,NULL);
}
double FB_mpiRead_sub_step4_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_mpiRead_sub_step4_Index,&dTemp);
    return dTemp;
}
double FB_mpiRead_sub_step4_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_mpiRead_sub_step4_Index,&dTemp);
    return dTemp;
}
double FB_mpiRead_sub_step4_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_mpiRead_sub_step4_Index,&dTemp);
    return dTemp;
}
int FB_mpiRead_sub_step5_Index = 66;
void FB_mpiRead_sub_step5_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_mpiRead_sub_step5_Index,NULL);
}
void FB_mpiRead_sub_step5_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_mpiRead_sub_step5_Index,NULL);
}
void FB_mpiRead_sub_step5_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_mpiRead_sub_step5_Index,NULL);
}
void FB_mpiRead_sub_step5_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_mpiRead_sub_step5_Index,NULL);
}
double FB_mpiRead_sub_step5_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_mpiRead_sub_step5_Index,&dTemp);
    return dTemp;
}
double FB_mpiRead_sub_step5_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_mpiRead_sub_step5_Index,&dTemp);
    return dTemp;
}
double FB_mpiRead_sub_step5_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_mpiRead_sub_step5_Index,&dTemp);
    return dTemp;
}
int FB_mpiRead_sub_step6_Index = 67;
void FB_mpiRead_sub_step6_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_mpiRead_sub_step6_Index,NULL);
}
void FB_mpiRead_sub_step6_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_mpiRead_sub_step6_Index,NULL);
}
void FB_mpiRead_sub_step6_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_mpiRead_sub_step6_Index,NULL);
}
void FB_mpiRead_sub_step6_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_mpiRead_sub_step6_Index,NULL);
}
double FB_mpiRead_sub_step6_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_mpiRead_sub_step6_Index,&dTemp);
    return dTemp;
}
double FB_mpiRead_sub_step6_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_mpiRead_sub_step6_Index,&dTemp);
    return dTemp;
}
double FB_mpiRead_sub_step6_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_mpiRead_sub_step6_Index,&dTemp);
    return dTemp;
}
int FB_mpiRead_sub_step7_Index = 68;
void FB_mpiRead_sub_step7_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_mpiRead_sub_step7_Index,NULL);
}
void FB_mpiRead_sub_step7_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_mpiRead_sub_step7_Index,NULL);
}
void FB_mpiRead_sub_step7_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_mpiRead_sub_step7_Index,NULL);
}
void FB_mpiRead_sub_step7_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_mpiRead_sub_step7_Index,NULL);
}
double FB_mpiRead_sub_step7_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_mpiRead_sub_step7_Index,&dTemp);
    return dTemp;
}
double FB_mpiRead_sub_step7_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_mpiRead_sub_step7_Index,&dTemp);
    return dTemp;
}
double FB_mpiRead_sub_step7_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_mpiRead_sub_step7_Index,&dTemp);
    return dTemp;
}
int FB_mpiRead_sub_step8_Index = 69;
void FB_mpiRead_sub_step8_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_mpiRead_sub_step8_Index,NULL);
}
void FB_mpiRead_sub_step8_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_mpiRead_sub_step8_Index,NULL);
}
void FB_mpiRead_sub_step8_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_mpiRead_sub_step8_Index,NULL);
}
void FB_mpiRead_sub_step8_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_mpiRead_sub_step8_Index,NULL);
}
double FB_mpiRead_sub_step8_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_mpiRead_sub_step8_Index,&dTemp);
    return dTemp;
}
double FB_mpiRead_sub_step8_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_mpiRead_sub_step8_Index,&dTemp);
    return dTemp;
}
double FB_mpiRead_sub_step8_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_mpiRead_sub_step8_Index,&dTemp);
    return dTemp;
}
int FB_mpiRead_sub_step9_Index = 70;
void FB_mpiRead_sub_step9_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_mpiRead_sub_step9_Index,NULL);
}
void FB_mpiRead_sub_step9_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_mpiRead_sub_step9_Index,NULL);
}
void FB_mpiRead_sub_step9_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_mpiRead_sub_step9_Index,NULL);
}
void FB_mpiRead_sub_step9_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_mpiRead_sub_step9_Index,NULL);
}
double FB_mpiRead_sub_step9_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_mpiRead_sub_step9_Index,&dTemp);
    return dTemp;
}
double FB_mpiRead_sub_step9_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_mpiRead_sub_step9_Index,&dTemp);
    return dTemp;
}
double FB_mpiRead_sub_step9_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_mpiRead_sub_step9_Index,&dTemp);
    return dTemp;
}
int FB_mpiWrite_mainModelWrite_Index = 71;
void FB_mpiWrite_mainModelWrite_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_mpiWrite_mainModelWrite_Index,NULL);
}
void FB_mpiWrite_mainModelWrite_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_mpiWrite_mainModelWrite_Index,NULL);
}
void FB_mpiWrite_mainModelWrite_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_mpiWrite_mainModelWrite_Index,NULL);
}
void FB_mpiWrite_mainModelWrite_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_mpiWrite_mainModelWrite_Index,NULL);
}
double FB_mpiWrite_mainModelWrite_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_mpiWrite_mainModelWrite_Index,&dTemp);
    return dTemp;
}
double FB_mpiWrite_mainModelWrite_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_mpiWrite_mainModelWrite_Index,&dTemp);
    return dTemp;
}
double FB_mpiWrite_mainModelWrite_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_mpiWrite_mainModelWrite_Index,&dTemp);
    return dTemp;
}
int FB_mpiWrite_sub_stepModel_Index = 72;
void FB_mpiWrite_sub_stepModel_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_mpiWrite_sub_stepModel_Index,NULL);
}
void FB_mpiWrite_sub_stepModel_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_mpiWrite_sub_stepModel_Index,NULL);
}
void FB_mpiWrite_sub_stepModel_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_mpiWrite_sub_stepModel_Index,NULL);
}
void FB_mpiWrite_sub_stepModel_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_mpiWrite_sub_stepModel_Index,NULL);
}
double FB_mpiWrite_sub_stepModel_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_mpiWrite_sub_stepModel_Index,&dTemp);
    return dTemp;
}
double FB_mpiWrite_sub_stepModel_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_mpiWrite_sub_stepModel_Index,&dTemp);
    return dTemp;
}
double FB_mpiWrite_sub_stepModel_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_mpiWrite_sub_stepModel_Index,&dTemp);
    return dTemp;
}
int FB_sapa_mainWrite_Index = 73;
void FB_sapa_mainWrite_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_sapa_mainWrite_Index,NULL);
}
void FB_sapa_mainWrite_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_sapa_mainWrite_Index,NULL);
}
void FB_sapa_mainWrite_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_sapa_mainWrite_Index,NULL);
}
void FB_sapa_mainWrite_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_sapa_mainWrite_Index,NULL);
}
double FB_sapa_mainWrite_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_sapa_mainWrite_Index,&dTemp);
    return dTemp;
}
double FB_sapa_mainWrite_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_sapa_mainWrite_Index,&dTemp);
    return dTemp;
}
double FB_sapa_mainWrite_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_sapa_mainWrite_Index,&dTemp);
    return dTemp;
}
int FB_sapa_mainRead_Index = 74;
void FB_sapa_mainRead_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_sapa_mainRead_Index,NULL);
}
void FB_sapa_mainRead_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_sapa_mainRead_Index,NULL);
}
void FB_sapa_mainRead_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_sapa_mainRead_Index,NULL);
}
void FB_sapa_mainRead_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_sapa_mainRead_Index,NULL);
}
double FB_sapa_mainRead_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_sapa_mainRead_Index,&dTemp);
    return dTemp;
}
double FB_sapa_mainRead_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_sapa_mainRead_Index,&dTemp);
    return dTemp;
}
double FB_sapa_mainRead_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_sapa_mainRead_Index,&dTemp);
    return dTemp;
}
int FB_sapaRead_resetValues_Index = 75;
void FB_sapaRead_resetValues_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_sapaRead_resetValues_Index,NULL);
}
void FB_sapaRead_resetValues_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_sapaRead_resetValues_Index,NULL);
}
void FB_sapaRead_resetValues_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_sapaRead_resetValues_Index,NULL);
}
void FB_sapaRead_resetValues_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_sapaRead_resetValues_Index,NULL);
}
double FB_sapaRead_resetValues_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_sapaRead_resetValues_Index,&dTemp);
    return dTemp;
}
double FB_sapaRead_resetValues_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_sapaRead_resetValues_Index,&dTemp);
    return dTemp;
}
double FB_sapaRead_resetValues_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_sapaRead_resetValues_Index,&dTemp);
    return dTemp;
}
int FB_sapaWrite_sub_step1_Index = 76;
void FB_sapaWrite_sub_step1_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_sapaWrite_sub_step1_Index,NULL);
}
void FB_sapaWrite_sub_step1_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_sapaWrite_sub_step1_Index,NULL);
}
void FB_sapaWrite_sub_step1_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_sapaWrite_sub_step1_Index,NULL);
}
void FB_sapaWrite_sub_step1_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_sapaWrite_sub_step1_Index,NULL);
}
double FB_sapaWrite_sub_step1_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_sapaWrite_sub_step1_Index,&dTemp);
    return dTemp;
}
double FB_sapaWrite_sub_step1_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_sapaWrite_sub_step1_Index,&dTemp);
    return dTemp;
}
double FB_sapaWrite_sub_step1_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_sapaWrite_sub_step1_Index,&dTemp);
    return dTemp;
}
int FB_sapaWrite_sub_step2_Index = 77;
void FB_sapaWrite_sub_step2_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_sapaWrite_sub_step2_Index,NULL);
}
void FB_sapaWrite_sub_step2_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_sapaWrite_sub_step2_Index,NULL);
}
void FB_sapaWrite_sub_step2_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_sapaWrite_sub_step2_Index,NULL);
}
void FB_sapaWrite_sub_step2_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_sapaWrite_sub_step2_Index,NULL);
}
double FB_sapaWrite_sub_step2_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_sapaWrite_sub_step2_Index,&dTemp);
    return dTemp;
}
double FB_sapaWrite_sub_step2_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_sapaWrite_sub_step2_Index,&dTemp);
    return dTemp;
}
double FB_sapaWrite_sub_step2_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_sapaWrite_sub_step2_Index,&dTemp);
    return dTemp;
}
int FB_sapaRead_sub_step1_Index = 78;
void FB_sapaRead_sub_step1_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_sapaRead_sub_step1_Index,NULL);
}
void FB_sapaRead_sub_step1_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_sapaRead_sub_step1_Index,NULL);
}
void FB_sapaRead_sub_step1_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_sapaRead_sub_step1_Index,NULL);
}
void FB_sapaRead_sub_step1_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_sapaRead_sub_step1_Index,NULL);
}
double FB_sapaRead_sub_step1_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_sapaRead_sub_step1_Index,&dTemp);
    return dTemp;
}
double FB_sapaRead_sub_step1_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_sapaRead_sub_step1_Index,&dTemp);
    return dTemp;
}
double FB_sapaRead_sub_step1_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_sapaRead_sub_step1_Index,&dTemp);
    return dTemp;
}
int FB_sapaRead_sub_step2_Index = 79;
void FB_sapaRead_sub_step2_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_sapaRead_sub_step2_Index,NULL);
}
void FB_sapaRead_sub_step2_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_sapaRead_sub_step2_Index,NULL);
}
void FB_sapaRead_sub_step2_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_sapaRead_sub_step2_Index,NULL);
}
void FB_sapaRead_sub_step2_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_sapaRead_sub_step2_Index,NULL);
}
double FB_sapaRead_sub_step2_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_sapaRead_sub_step2_Index,&dTemp);
    return dTemp;
}
double FB_sapaRead_sub_step2_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_sapaRead_sub_step2_Index,&dTemp);
    return dTemp;
}
double FB_sapaRead_sub_step2_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_sapaRead_sub_step2_Index,&dTemp);
    return dTemp;
}

int TX_step1_Network_Management_BCM_HS_CAN_Index = 0;

void TX_step1_Network_Management_BCM_HS_CAN_Init(TX_step1_Network_Management_BCM_HS_CAN * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step1_Network_Management_BCM_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->SrcNodeID = dValues[0];
    pMsg->UDat = dValues[1];
    CM_MessageRawInit(g_uiHandle, 2, TX_step1_Network_Management_BCM_HS_CAN_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->SrcNodeID_raw = (BYTE)nRawValues[0];
    pMsg->UDat_raw = (uint64)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void TX_step1_Network_Management_BCM_HS_CAN_LoadSignalValuesArray(TX_step1_Network_Management_BCM_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->SrcNodeID;
    dArray[1] = pMsg->UDat;
}

void TX_step1_Network_Management_BCM_HS_CAN_LoadRawSignalValuesArray(TX_step1_Network_Management_BCM_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->SrcNodeID_raw;
    nRawValues[1] = pMsg->UDat_raw;
}

int TX_step1_Network_Management_BCM_HS_CAN_Transmit(TX_step1_Network_Management_BCM_HS_CAN * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 2, TX_step1_Network_Management_BCM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        TX_step1_Network_Management_BCM_HS_CAN_Init(pMsg);
    }

    TX_step1_Network_Management_BCM_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 2, TX_step1_Network_Management_BCM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int TX_step1_Network_Management_BCM_HS_CAN_Transmit_raw(TX_step1_Network_Management_BCM_HS_CAN * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 2, TX_step1_Network_Management_BCM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        TX_step1_Network_Management_BCM_HS_CAN_Init(pMsg);
    }

    TX_step1_Network_Management_BCM_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step1_Network_Management_BCM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int TX_step1_Network_Management_BCM_HS_CAN_UpdateBytesFromSignals(TX_step1_Network_Management_BCM_HS_CAN * pMsg)
{
    double dArray[2];

    TX_step1_Network_Management_BCM_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 2, TX_step1_Network_Management_BCM_HS_CAN_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int TX_step1_Network_Management_BCM_HS_CAN_UpdateBytesFromRawSignals(TX_step1_Network_Management_BCM_HS_CAN * pMsg)
{
    uint64 nRawValues[2];

    TX_step1_Network_Management_BCM_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 2, TX_step1_Network_Management_BCM_HS_CAN_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int TX_step1_Network_Management_BCM_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step1_Network_Management_BCM_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Index = 1;

void TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Init(TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN * pMsg)
{
    double dValues[8] = {0.0};
    uint64 nRawValues[8] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 8, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->DrvHCSMIndReq = dValues[0];
    pMsg->DrvHCSMInd1 = dValues[1];
    pMsg->DrvHCSMInd2 = dValues[2];
    pMsg->DrvHCSMInd3 = dValues[3];
    pMsg->PassHCSMIndReq = dValues[4];
    pMsg->PassHCSMInd1 = dValues[5];
    pMsg->PassHCSMInd2 = dValues[6];
    pMsg->PassHCSMInd3 = dValues[7];
    CM_MessageRawInit(g_uiHandle, 2, TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Index, nRawValues, 8, &iActualSignalMaxCount);
    pMsg->DrvHCSMIndReq_raw = (BYTE)nRawValues[0];
    pMsg->DrvHCSMInd1_raw = (BYTE)nRawValues[1];
    pMsg->DrvHCSMInd2_raw = (BYTE)nRawValues[2];
    pMsg->DrvHCSMInd3_raw = (BYTE)nRawValues[3];
    pMsg->PassHCSMIndReq_raw = (BYTE)nRawValues[4];
    pMsg->PassHCSMInd1_raw = (BYTE)nRawValues[5];
    pMsg->PassHCSMInd2_raw = (BYTE)nRawValues[6];
    pMsg->PassHCSMInd3_raw = (BYTE)nRawValues[7];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_LoadSignalValuesArray(TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->DrvHCSMIndReq;
    dArray[1] = pMsg->DrvHCSMInd1;
    dArray[2] = pMsg->DrvHCSMInd2;
    dArray[3] = pMsg->DrvHCSMInd3;
    dArray[4] = pMsg->PassHCSMIndReq;
    dArray[5] = pMsg->PassHCSMInd1;
    dArray[6] = pMsg->PassHCSMInd2;
    dArray[7] = pMsg->PassHCSMInd3;
}

void TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_LoadRawSignalValuesArray(TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->DrvHCSMIndReq_raw;
    nRawValues[1] = pMsg->DrvHCSMInd1_raw;
    nRawValues[2] = pMsg->DrvHCSMInd2_raw;
    nRawValues[3] = pMsg->DrvHCSMInd3_raw;
    nRawValues[4] = pMsg->PassHCSMIndReq_raw;
    nRawValues[5] = pMsg->PassHCSMInd1_raw;
    nRawValues[6] = pMsg->PassHCSMInd2_raw;
    nRawValues[7] = pMsg->PassHCSMInd3_raw;
}

int TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Transmit(TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN * pMsg)
{
    double dArray[8];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 2, TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Init(pMsg);
    }

    TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 2, TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 8);
}

int TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Transmit_raw(TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN * pMsg)
{
    uint64 nRawValues[8];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 2, TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Init(pMsg);
    }

    TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 8);
}

int TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_UpdateBytesFromSignals(TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN * pMsg)
{
    double dArray[8];

    TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 2, TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Index, dArray, 8, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_UpdateBytesFromRawSignals(TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN * pMsg)
{
    uint64 nRawValues[8];

    TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 2, TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Index, nRawValues, 8, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_step3_Exterior_Lighting_HS_CAN_Index = 2;

void TX_step3_Exterior_Lighting_HS_CAN_Init(TX_step3_Exterior_Lighting_HS_CAN * pMsg)
{
    double dValues[32] = {0.0};
    uint64 nRawValues[32] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step3_Exterior_Lighting_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 32, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->AdvFrntLghtSysEnbld = dValues[0];
    pMsg->AutLghtCtrl = dValues[1];
    pMsg->AutoBmSlctAllwd = dValues[2];
    pMsg->AutoLtsActIO = dValues[3];
    pMsg->AutoLtsInactIO = dValues[4];
    pMsg->BrkLtsAtv = dValues[5];
    pMsg->DRLAct = dValues[6];
    pMsg->DispNtSchmAtv = dValues[7];
    pMsg->FlToPsSwAtv = dValues[8];
    pMsg->FrFogLmpsAct = dValues[9];
    pMsg->FrFgLtIO = dValues[10];
    pMsg->HazSwAtv = dValues[11];
    pMsg->HdlmpBmSelectStat = dValues[12];
    pMsg->HighBmAct = dValues[13];
    pMsg->HiBmIO = dValues[14];
    pMsg->HiBmReqd = dValues[15];
    pMsg->IntDimDspLvl = dValues[16];
    pMsg->IntDimLvl = dValues[17];
    pMsg->IntDimNtPnlAtv = dValues[18];
    pMsg->LftTrnLmpAtv = dValues[19];
    pMsg->LowBmAct = dValues[20];
    pMsg->MainLghtSw = dValues[21];
    pMsg->OtsdAmbtLtLvlStat = dValues[22];
    pMsg->OtsdAmbtLtLvlStatV = dValues[23];
    pMsg->PrkLtIO = dValues[24];
    pMsg->PrkLtLeftIO = dValues[25];
    pMsg->PrkLtRightIO = dValues[26];
    pMsg->RrFogLmpsAct = dValues[27];
    pMsg->RrFgLtIO = dValues[28];
    pMsg->RevLmpAtv = dValues[29];
    pMsg->RtTrnLmpAtv = dValues[30];
    pMsg->TrnSwAct = dValues[31];
    CM_MessageRawInit(g_uiHandle, 2, TX_step3_Exterior_Lighting_HS_CAN_Index, nRawValues, 32, &iActualSignalMaxCount);
    pMsg->AdvFrntLghtSysEnbld_raw = (BYTE)nRawValues[0];
    pMsg->AutLghtCtrl_raw = (BYTE)nRawValues[1];
    pMsg->AutoBmSlctAllwd_raw = (BYTE)nRawValues[2];
    pMsg->AutoLtsActIO_raw = (BYTE)nRawValues[3];
    pMsg->AutoLtsInactIO_raw = (BYTE)nRawValues[4];
    pMsg->BrkLtsAtv_raw = (BYTE)nRawValues[5];
    pMsg->DRLAct_raw = (BYTE)nRawValues[6];
    pMsg->DispNtSchmAtv_raw = (BYTE)nRawValues[7];
    pMsg->FlToPsSwAtv_raw = (BYTE)nRawValues[8];
    pMsg->FrFogLmpsAct_raw = (BYTE)nRawValues[9];
    pMsg->FrFgLtIO_raw = (BYTE)nRawValues[10];
    pMsg->HazSwAtv_raw = (BYTE)nRawValues[11];
    pMsg->HdlmpBmSelectStat_raw = (BYTE)nRawValues[12];
    pMsg->HighBmAct_raw = (BYTE)nRawValues[13];
    pMsg->HiBmIO_raw = (BYTE)nRawValues[14];
    pMsg->HiBmReqd_raw = (BYTE)nRawValues[15];
    pMsg->IntDimDspLvl_raw = (BYTE)nRawValues[16];
    pMsg->IntDimLvl_raw = (BYTE)nRawValues[17];
    pMsg->IntDimNtPnlAtv_raw = (BYTE)nRawValues[18];
    pMsg->LftTrnLmpAtv_raw = (BYTE)nRawValues[19];
    pMsg->LowBmAct_raw = (BYTE)nRawValues[20];
    pMsg->MainLghtSw_raw = (BYTE)nRawValues[21];
    pMsg->OtsdAmbtLtLvlStat_raw = (BYTE)nRawValues[22];
    pMsg->OtsdAmbtLtLvlStatV_raw = (BYTE)nRawValues[23];
    pMsg->PrkLtIO_raw = (BYTE)nRawValues[24];
    pMsg->PrkLtLeftIO_raw = (BYTE)nRawValues[25];
    pMsg->PrkLtRightIO_raw = (BYTE)nRawValues[26];
    pMsg->RrFogLmpsAct_raw = (BYTE)nRawValues[27];
    pMsg->RrFgLtIO_raw = (BYTE)nRawValues[28];
    pMsg->RevLmpAtv_raw = (BYTE)nRawValues[29];
    pMsg->RtTrnLmpAtv_raw = (BYTE)nRawValues[30];
    pMsg->TrnSwAct_raw = (BYTE)nRawValues[31];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void TX_step3_Exterior_Lighting_HS_CAN_LoadSignalValuesArray(TX_step3_Exterior_Lighting_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->AdvFrntLghtSysEnbld;
    dArray[1] = pMsg->AutLghtCtrl;
    dArray[2] = pMsg->AutoBmSlctAllwd;
    dArray[3] = pMsg->AutoLtsActIO;
    dArray[4] = pMsg->AutoLtsInactIO;
    dArray[5] = pMsg->BrkLtsAtv;
    dArray[6] = pMsg->DRLAct;
    dArray[7] = pMsg->DispNtSchmAtv;
    dArray[8] = pMsg->FlToPsSwAtv;
    dArray[9] = pMsg->FrFogLmpsAct;
    dArray[10] = pMsg->FrFgLtIO;
    dArray[11] = pMsg->HazSwAtv;
    dArray[12] = pMsg->HdlmpBmSelectStat;
    dArray[13] = pMsg->HighBmAct;
    dArray[14] = pMsg->HiBmIO;
    dArray[15] = pMsg->HiBmReqd;
    dArray[16] = pMsg->IntDimDspLvl;
    dArray[17] = pMsg->IntDimLvl;
    dArray[18] = pMsg->IntDimNtPnlAtv;
    dArray[19] = pMsg->LftTrnLmpAtv;
    dArray[20] = pMsg->LowBmAct;
    dArray[21] = pMsg->MainLghtSw;
    dArray[22] = pMsg->OtsdAmbtLtLvlStat;
    dArray[23] = pMsg->OtsdAmbtLtLvlStatV;
    dArray[24] = pMsg->PrkLtIO;
    dArray[25] = pMsg->PrkLtLeftIO;
    dArray[26] = pMsg->PrkLtRightIO;
    dArray[27] = pMsg->RrFogLmpsAct;
    dArray[28] = pMsg->RrFgLtIO;
    dArray[29] = pMsg->RevLmpAtv;
    dArray[30] = pMsg->RtTrnLmpAtv;
    dArray[31] = pMsg->TrnSwAct;
}

void TX_step3_Exterior_Lighting_HS_CAN_LoadRawSignalValuesArray(TX_step3_Exterior_Lighting_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->AdvFrntLghtSysEnbld_raw;
    nRawValues[1] = pMsg->AutLghtCtrl_raw;
    nRawValues[2] = pMsg->AutoBmSlctAllwd_raw;
    nRawValues[3] = pMsg->AutoLtsActIO_raw;
    nRawValues[4] = pMsg->AutoLtsInactIO_raw;
    nRawValues[5] = pMsg->BrkLtsAtv_raw;
    nRawValues[6] = pMsg->DRLAct_raw;
    nRawValues[7] = pMsg->DispNtSchmAtv_raw;
    nRawValues[8] = pMsg->FlToPsSwAtv_raw;
    nRawValues[9] = pMsg->FrFogLmpsAct_raw;
    nRawValues[10] = pMsg->FrFgLtIO_raw;
    nRawValues[11] = pMsg->HazSwAtv_raw;
    nRawValues[12] = pMsg->HdlmpBmSelectStat_raw;
    nRawValues[13] = pMsg->HighBmAct_raw;
    nRawValues[14] = pMsg->HiBmIO_raw;
    nRawValues[15] = pMsg->HiBmReqd_raw;
    nRawValues[16] = pMsg->IntDimDspLvl_raw;
    nRawValues[17] = pMsg->IntDimLvl_raw;
    nRawValues[18] = pMsg->IntDimNtPnlAtv_raw;
    nRawValues[19] = pMsg->LftTrnLmpAtv_raw;
    nRawValues[20] = pMsg->LowBmAct_raw;
    nRawValues[21] = pMsg->MainLghtSw_raw;
    nRawValues[22] = pMsg->OtsdAmbtLtLvlStat_raw;
    nRawValues[23] = pMsg->OtsdAmbtLtLvlStatV_raw;
    nRawValues[24] = pMsg->PrkLtIO_raw;
    nRawValues[25] = pMsg->PrkLtLeftIO_raw;
    nRawValues[26] = pMsg->PrkLtRightIO_raw;
    nRawValues[27] = pMsg->RrFogLmpsAct_raw;
    nRawValues[28] = pMsg->RrFgLtIO_raw;
    nRawValues[29] = pMsg->RevLmpAtv_raw;
    nRawValues[30] = pMsg->RtTrnLmpAtv_raw;
    nRawValues[31] = pMsg->TrnSwAct_raw;
}

int TX_step3_Exterior_Lighting_HS_CAN_Transmit(TX_step3_Exterior_Lighting_HS_CAN * pMsg)
{
    double dArray[32];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 2, TX_step3_Exterior_Lighting_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        TX_step3_Exterior_Lighting_HS_CAN_Init(pMsg);
    }

    TX_step3_Exterior_Lighting_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 2, TX_step3_Exterior_Lighting_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 32);
}

int TX_step3_Exterior_Lighting_HS_CAN_Transmit_raw(TX_step3_Exterior_Lighting_HS_CAN * pMsg)
{
    uint64 nRawValues[32];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 2, TX_step3_Exterior_Lighting_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        TX_step3_Exterior_Lighting_HS_CAN_Init(pMsg);
    }

    TX_step3_Exterior_Lighting_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step3_Exterior_Lighting_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 32);
}

int TX_step3_Exterior_Lighting_HS_CAN_UpdateBytesFromSignals(TX_step3_Exterior_Lighting_HS_CAN * pMsg)
{
    double dArray[32];

    TX_step3_Exterior_Lighting_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 2, TX_step3_Exterior_Lighting_HS_CAN_Index, dArray, 32, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int TX_step3_Exterior_Lighting_HS_CAN_UpdateBytesFromRawSignals(TX_step3_Exterior_Lighting_HS_CAN * pMsg)
{
    uint64 nRawValues[32];

    TX_step3_Exterior_Lighting_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 2, TX_step3_Exterior_Lighting_HS_CAN_Index, nRawValues, 32, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int TX_step3_Exterior_Lighting_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step3_Exterior_Lighting_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Index = 3;

void TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Init(TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN * pMsg)
{
    double dValues[8] = {0.0};
    uint64 nRawValues[8] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 8, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->OtsAirTmp = dValues[0];
    pMsg->OtsAirTmpCrVal = dValues[1];
    pMsg->OtsAirTmpCrValMsk = dValues[2];
    pMsg->OtsAirTmpCrValV = dValues[3];
    pMsg->EngInltSpcfcHmdty = dValues[4];
    pMsg->EngInltSpcfcHmdtyM = dValues[5];
    pMsg->EngInltSpcfcHmdtyV = dValues[6];
    pMsg->OtsAirTmpV = dValues[7];
    CM_MessageRawInit(g_uiHandle, 2, TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Index, nRawValues, 8, &iActualSignalMaxCount);
    pMsg->OtsAirTmp_raw = (BYTE)nRawValues[0];
    pMsg->OtsAirTmpCrVal_raw = (BYTE)nRawValues[1];
    pMsg->OtsAirTmpCrValMsk_raw = (BYTE)nRawValues[2];
    pMsg->OtsAirTmpCrValV_raw = (BYTE)nRawValues[3];
    pMsg->EngInltSpcfcHmdty_raw = (BYTE)nRawValues[4];
    pMsg->EngInltSpcfcHmdtyM_raw = (BYTE)nRawValues[5];
    pMsg->EngInltSpcfcHmdtyV_raw = (BYTE)nRawValues[6];
    pMsg->OtsAirTmpV_raw = (BYTE)nRawValues[7];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_LoadSignalValuesArray(TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->OtsAirTmp;
    dArray[1] = pMsg->OtsAirTmpCrVal;
    dArray[2] = pMsg->OtsAirTmpCrValMsk;
    dArray[3] = pMsg->OtsAirTmpCrValV;
    dArray[4] = pMsg->EngInltSpcfcHmdty;
    dArray[5] = pMsg->EngInltSpcfcHmdtyM;
    dArray[6] = pMsg->EngInltSpcfcHmdtyV;
    dArray[7] = pMsg->OtsAirTmpV;
}

void TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_LoadRawSignalValuesArray(TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->OtsAirTmp_raw;
    nRawValues[1] = pMsg->OtsAirTmpCrVal_raw;
    nRawValues[2] = pMsg->OtsAirTmpCrValMsk_raw;
    nRawValues[3] = pMsg->OtsAirTmpCrValV_raw;
    nRawValues[4] = pMsg->EngInltSpcfcHmdty_raw;
    nRawValues[5] = pMsg->EngInltSpcfcHmdtyM_raw;
    nRawValues[6] = pMsg->EngInltSpcfcHmdtyV_raw;
    nRawValues[7] = pMsg->OtsAirTmpV_raw;
}

int TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Transmit(TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN * pMsg)
{
    double dArray[8];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 2, TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Init(pMsg);
    }

    TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 2, TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 8);
}

int TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Transmit_raw(TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN * pMsg)
{
    uint64 nRawValues[8];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 2, TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Init(pMsg);
    }

    TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 8);
}

int TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_UpdateBytesFromSignals(TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN * pMsg)
{
    double dArray[8];

    TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 2, TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Index, dArray, 8, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_UpdateBytesFromRawSignals(TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN * pMsg)
{
    uint64 nRawValues[8];

    TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 2, TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Index, nRawValues, 8, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_step5_Instrument_Panel_Sensor_HS_CAN_Index = 4;

void TX_step5_Instrument_Panel_Sensor_HS_CAN_Init(TX_step5_Instrument_Panel_Sensor_HS_CAN * pMsg)
{
    double dValues[5] = {0.0};
    uint64 nRawValues[5] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step5_Instrument_Panel_Sensor_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 5, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->IPSnsrSolrAnglFltd = dValues[0];
    pMsg->IPSnsrRwSolrIntFltd = dValues[1];
    pMsg->IPSnsrRwSolrInt = dValues[2];
    pMsg->IPSnsrSolrAzmthAngl = dValues[3];
    pMsg->IPSnsrSolrElvtnAngl = dValues[4];
    CM_MessageRawInit(g_uiHandle, 2, TX_step5_Instrument_Panel_Sensor_HS_CAN_Index, nRawValues, 5, &iActualSignalMaxCount);
    pMsg->IPSnsrSolrAnglFltd_raw = (BYTE)nRawValues[0];
    pMsg->IPSnsrRwSolrIntFltd_raw = (BYTE)nRawValues[1];
    pMsg->IPSnsrRwSolrInt_raw = (BYTE)nRawValues[2];
    pMsg->IPSnsrSolrAzmthAngl_raw = (BYTE)nRawValues[3];
    pMsg->IPSnsrSolrElvtnAngl_raw = (BYTE)nRawValues[4];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void TX_step5_Instrument_Panel_Sensor_HS_CAN_LoadSignalValuesArray(TX_step5_Instrument_Panel_Sensor_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->IPSnsrSolrAnglFltd;
    dArray[1] = pMsg->IPSnsrRwSolrIntFltd;
    dArray[2] = pMsg->IPSnsrRwSolrInt;
    dArray[3] = pMsg->IPSnsrSolrAzmthAngl;
    dArray[4] = pMsg->IPSnsrSolrElvtnAngl;
}

void TX_step5_Instrument_Panel_Sensor_HS_CAN_LoadRawSignalValuesArray(TX_step5_Instrument_Panel_Sensor_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->IPSnsrSolrAnglFltd_raw;
    nRawValues[1] = pMsg->IPSnsrRwSolrIntFltd_raw;
    nRawValues[2] = pMsg->IPSnsrRwSolrInt_raw;
    nRawValues[3] = pMsg->IPSnsrSolrAzmthAngl_raw;
    nRawValues[4] = pMsg->IPSnsrSolrElvtnAngl_raw;
}

int TX_step5_Instrument_Panel_Sensor_HS_CAN_Transmit(TX_step5_Instrument_Panel_Sensor_HS_CAN * pMsg)
{
    double dArray[5];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 2, TX_step5_Instrument_Panel_Sensor_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        TX_step5_Instrument_Panel_Sensor_HS_CAN_Init(pMsg);
    }

    TX_step5_Instrument_Panel_Sensor_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 2, TX_step5_Instrument_Panel_Sensor_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 5);
}

int TX_step5_Instrument_Panel_Sensor_HS_CAN_Transmit_raw(TX_step5_Instrument_Panel_Sensor_HS_CAN * pMsg)
{
    uint64 nRawValues[5];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 2, TX_step5_Instrument_Panel_Sensor_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        TX_step5_Instrument_Panel_Sensor_HS_CAN_Init(pMsg);
    }

    TX_step5_Instrument_Panel_Sensor_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step5_Instrument_Panel_Sensor_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 5);
}

int TX_step5_Instrument_Panel_Sensor_HS_CAN_UpdateBytesFromSignals(TX_step5_Instrument_Panel_Sensor_HS_CAN * pMsg)
{
    double dArray[5];

    TX_step5_Instrument_Panel_Sensor_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 2, TX_step5_Instrument_Panel_Sensor_HS_CAN_Index, dArray, 5, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int TX_step5_Instrument_Panel_Sensor_HS_CAN_UpdateBytesFromRawSignals(TX_step5_Instrument_Panel_Sensor_HS_CAN * pMsg)
{
    uint64 nRawValues[5];

    TX_step5_Instrument_Panel_Sensor_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 2, TX_step5_Instrument_Panel_Sensor_HS_CAN_Index, nRawValues, 5, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int TX_step5_Instrument_Panel_Sensor_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step5_Instrument_Panel_Sensor_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index = 5;

void TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Init(TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN * pMsg)
{
    double dValues[12] = {0.0};
    uint64 nRawValues[12] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 12, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->DistRollCntAvgDrvn = dValues[0];
    pMsg->DstRolCntAvgDrnRstOc = dValues[1];
    pMsg->DistRollCntAvgDrvnSrc = dValues[2];
    pMsg->DistRollCntAvgDrvnV = dValues[3];
    pMsg->DstRolCntAvgNonDrvn = dValues[4];
    pMsg->DstRolCntAvNDrRstOc = dValues[5];
    pMsg->DstRolCntAvgNonDrvnV = dValues[6];
    pMsg->VehSpdAvgDrvn = dValues[7];
    pMsg->VehSpdAvgDrvnSrc = dValues[8];
    pMsg->VehSpdAvgDrvnV = dValues[9];
    pMsg->VehSpdAvgNDrvn = dValues[10];
    pMsg->VehSpdAvgNDrvnV = dValues[11];
    CM_MessageRawInit(g_uiHandle, 2, TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, nRawValues, 12, &iActualSignalMaxCount);
    pMsg->DistRollCntAvgDrvn_raw = (WORD)nRawValues[0];
    pMsg->DstRolCntAvgDrnRstOc_raw = (BYTE)nRawValues[1];
    pMsg->DistRollCntAvgDrvnSrc_raw = (BYTE)nRawValues[2];
    pMsg->DistRollCntAvgDrvnV_raw = (BYTE)nRawValues[3];
    pMsg->DstRolCntAvgNonDrvn_raw = (WORD)nRawValues[4];
    pMsg->DstRolCntAvNDrRstOc_raw = (BYTE)nRawValues[5];
    pMsg->DstRolCntAvgNonDrvnV_raw = (BYTE)nRawValues[6];
    pMsg->VehSpdAvgDrvn_raw = (WORD)nRawValues[7];
    pMsg->VehSpdAvgDrvnSrc_raw = (BYTE)nRawValues[8];
    pMsg->VehSpdAvgDrvnV_raw = (BYTE)nRawValues[9];
    pMsg->VehSpdAvgNDrvn_raw = (WORD)nRawValues[10];
    pMsg->VehSpdAvgNDrvnV_raw = (BYTE)nRawValues[11];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_LoadSignalValuesArray(TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->DistRollCntAvgDrvn;
    dArray[1] = pMsg->DstRolCntAvgDrnRstOc;
    dArray[2] = pMsg->DistRollCntAvgDrvnSrc;
    dArray[3] = pMsg->DistRollCntAvgDrvnV;
    dArray[4] = pMsg->DstRolCntAvgNonDrvn;
    dArray[5] = pMsg->DstRolCntAvNDrRstOc;
    dArray[6] = pMsg->DstRolCntAvgNonDrvnV;
    dArray[7] = pMsg->VehSpdAvgDrvn;
    dArray[8] = pMsg->VehSpdAvgDrvnSrc;
    dArray[9] = pMsg->VehSpdAvgDrvnV;
    dArray[10] = pMsg->VehSpdAvgNDrvn;
    dArray[11] = pMsg->VehSpdAvgNDrvnV;
}

void TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_LoadRawSignalValuesArray(TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->DistRollCntAvgDrvn_raw;
    nRawValues[1] = pMsg->DstRolCntAvgDrnRstOc_raw;
    nRawValues[2] = pMsg->DistRollCntAvgDrvnSrc_raw;
    nRawValues[3] = pMsg->DistRollCntAvgDrvnV_raw;
    nRawValues[4] = pMsg->DstRolCntAvgNonDrvn_raw;
    nRawValues[5] = pMsg->DstRolCntAvNDrRstOc_raw;
    nRawValues[6] = pMsg->DstRolCntAvgNonDrvnV_raw;
    nRawValues[7] = pMsg->VehSpdAvgDrvn_raw;
    nRawValues[8] = pMsg->VehSpdAvgDrvnSrc_raw;
    nRawValues[9] = pMsg->VehSpdAvgDrvnV_raw;
    nRawValues[10] = pMsg->VehSpdAvgNDrvn_raw;
    nRawValues[11] = pMsg->VehSpdAvgNDrvnV_raw;
}

int TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Transmit(TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN * pMsg)
{
    double dArray[12];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 2, TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Init(pMsg);
    }

    TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 2, TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 12);
}

int TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Transmit_raw(TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN * pMsg)
{
    uint64 nRawValues[12];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 2, TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Init(pMsg);
    }

    TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 12);
}

int TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_UpdateBytesFromSignals(TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN * pMsg)
{
    double dArray[12];

    TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 2, TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, dArray, 12, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_UpdateBytesFromRawSignals(TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN * pMsg)
{
    uint64 nRawValues[12];

    TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 2, TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, nRawValues, 12, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index = 6;

void TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Init(TX_step7_PPEI_Engine_General_Status_1_HS_CAN * pMsg)
{
    double dValues[19] = {0.0};
    uint64 nRawValues[19] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 19, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->AccActPos = dValues[0];
    pMsg->AccActPosV = dValues[1];
    pMsg->CrsCntAtv = dValues[2];
    pMsg->CrsCntEnbld = dValues[3];
    pMsg->Eng12vStrtrMtrCmmdOn = dValues[4];
    pMsg->EngCntrlRunCrnkTrmSt = dValues[5];
    pMsg->EngIdlAtv = dValues[6];
    pMsg->EngAirIntBstPr = dValues[7];
    pMsg->EngAirIntBstPrV = dValues[8];
    pMsg->EngRunAtv = dValues[9];
    pMsg->EngSpd = dValues[10];
    pMsg->EngSpdStat = dValues[11];
    pMsg->PT_BrkPedDscrtInpStat = dValues[12];
    pMsg->PT_BrkPedDscrtInpStatV = dValues[13];
    pMsg->PTCrnkAbrted = dValues[14];
    pMsg->PT_CrnkAct = dValues[15];
    pMsg->PTRunAbrt = dValues[16];
    pMsg->RmVhStrtEngRng = dValues[17];
    pMsg->SpdLmtrSpdWrngEnbld = dValues[18];
    CM_MessageRawInit(g_uiHandle, 2, TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, nRawValues, 19, &iActualSignalMaxCount);
    pMsg->AccActPos_raw = (BYTE)nRawValues[0];
    pMsg->AccActPosV_raw = (BYTE)nRawValues[1];
    pMsg->CrsCntAtv_raw = (BYTE)nRawValues[2];
    pMsg->CrsCntEnbld_raw = (BYTE)nRawValues[3];
    pMsg->Eng12vStrtrMtrCmmdOn_raw = (BYTE)nRawValues[4];
    pMsg->EngCntrlRunCrnkTrmSt_raw = (BYTE)nRawValues[5];
    pMsg->EngIdlAtv_raw = (BYTE)nRawValues[6];
    pMsg->EngAirIntBstPr_raw = (BYTE)nRawValues[7];
    pMsg->EngAirIntBstPrV_raw = (BYTE)nRawValues[8];
    pMsg->EngRunAtv_raw = (BYTE)nRawValues[9];
    pMsg->EngSpd_raw = (WORD)nRawValues[10];
    pMsg->EngSpdStat_raw = (BYTE)nRawValues[11];
    pMsg->PT_BrkPedDscrtInpStat_raw = (BYTE)nRawValues[12];
    pMsg->PT_BrkPedDscrtInpStatV_raw = (BYTE)nRawValues[13];
    pMsg->PTCrnkAbrted_raw = (BYTE)nRawValues[14];
    pMsg->PT_CrnkAct_raw = (BYTE)nRawValues[15];
    pMsg->PTRunAbrt_raw = (BYTE)nRawValues[16];
    pMsg->RmVhStrtEngRng_raw = (BYTE)nRawValues[17];
    pMsg->SpdLmtrSpdWrngEnbld_raw = (BYTE)nRawValues[18];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void TX_step7_PPEI_Engine_General_Status_1_HS_CAN_LoadSignalValuesArray(TX_step7_PPEI_Engine_General_Status_1_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->AccActPos;
    dArray[1] = pMsg->AccActPosV;
    dArray[2] = pMsg->CrsCntAtv;
    dArray[3] = pMsg->CrsCntEnbld;
    dArray[4] = pMsg->Eng12vStrtrMtrCmmdOn;
    dArray[5] = pMsg->EngCntrlRunCrnkTrmSt;
    dArray[6] = pMsg->EngIdlAtv;
    dArray[7] = pMsg->EngAirIntBstPr;
    dArray[8] = pMsg->EngAirIntBstPrV;
    dArray[9] = pMsg->EngRunAtv;
    dArray[10] = pMsg->EngSpd;
    dArray[11] = pMsg->EngSpdStat;
    dArray[12] = pMsg->PT_BrkPedDscrtInpStat;
    dArray[13] = pMsg->PT_BrkPedDscrtInpStatV;
    dArray[14] = pMsg->PTCrnkAbrted;
    dArray[15] = pMsg->PT_CrnkAct;
    dArray[16] = pMsg->PTRunAbrt;
    dArray[17] = pMsg->RmVhStrtEngRng;
    dArray[18] = pMsg->SpdLmtrSpdWrngEnbld;
}

void TX_step7_PPEI_Engine_General_Status_1_HS_CAN_LoadRawSignalValuesArray(TX_step7_PPEI_Engine_General_Status_1_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->AccActPos_raw;
    nRawValues[1] = pMsg->AccActPosV_raw;
    nRawValues[2] = pMsg->CrsCntAtv_raw;
    nRawValues[3] = pMsg->CrsCntEnbld_raw;
    nRawValues[4] = pMsg->Eng12vStrtrMtrCmmdOn_raw;
    nRawValues[5] = pMsg->EngCntrlRunCrnkTrmSt_raw;
    nRawValues[6] = pMsg->EngIdlAtv_raw;
    nRawValues[7] = pMsg->EngAirIntBstPr_raw;
    nRawValues[8] = pMsg->EngAirIntBstPrV_raw;
    nRawValues[9] = pMsg->EngRunAtv_raw;
    nRawValues[10] = pMsg->EngSpd_raw;
    nRawValues[11] = pMsg->EngSpdStat_raw;
    nRawValues[12] = pMsg->PT_BrkPedDscrtInpStat_raw;
    nRawValues[13] = pMsg->PT_BrkPedDscrtInpStatV_raw;
    nRawValues[14] = pMsg->PTCrnkAbrted_raw;
    nRawValues[15] = pMsg->PT_CrnkAct_raw;
    nRawValues[16] = pMsg->PTRunAbrt_raw;
    nRawValues[17] = pMsg->RmVhStrtEngRng_raw;
    nRawValues[18] = pMsg->SpdLmtrSpdWrngEnbld_raw;
}

int TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Transmit(TX_step7_PPEI_Engine_General_Status_1_HS_CAN * pMsg)
{
    double dArray[19];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 2, TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Init(pMsg);
    }

    TX_step7_PPEI_Engine_General_Status_1_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 2, TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 19);
}

int TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Transmit_raw(TX_step7_PPEI_Engine_General_Status_1_HS_CAN * pMsg)
{
    uint64 nRawValues[19];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 2, TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Init(pMsg);
    }

    TX_step7_PPEI_Engine_General_Status_1_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 19);
}

int TX_step7_PPEI_Engine_General_Status_1_HS_CAN_UpdateBytesFromSignals(TX_step7_PPEI_Engine_General_Status_1_HS_CAN * pMsg)
{
    double dArray[19];

    TX_step7_PPEI_Engine_General_Status_1_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 2, TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, dArray, 19, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int TX_step7_PPEI_Engine_General_Status_1_HS_CAN_UpdateBytesFromRawSignals(TX_step7_PPEI_Engine_General_Status_1_HS_CAN * pMsg)
{
    uint64 nRawValues[19];

    TX_step7_PPEI_Engine_General_Status_1_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 2, TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, nRawValues, 19, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int TX_step7_PPEI_Engine_General_Status_1_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_stepX_diagRequest1_HS_CAN_Index = 7;

void TX_stepX_diagRequest1_HS_CAN_Init(TX_stepX_diagRequest1_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_stepX_diagRequest1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_stepX_diagRequest1_HS_CAN_Transmit(TX_stepX_diagRequest1_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_stepX_diagRequest1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_stepX_diagRequest1_HS_CAN_Transmit_raw(TX_stepX_diagRequest1_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_stepX_diagRequest1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_stepX_diagRequest1_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_stepX_diagRequest1_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_step15_diagRequest2_HS_CAN_Index = 8;

void TX_step15_diagRequest2_HS_CAN_Init(TX_step15_diagRequest2_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step15_diagRequest2_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_step15_diagRequest2_HS_CAN_Transmit(TX_step15_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_step15_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step15_diagRequest2_HS_CAN_Transmit_raw(TX_step15_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step15_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step15_diagRequest2_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step15_diagRequest2_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_step16_diagRequest2_HS_CAN_Index = 9;

void TX_step16_diagRequest2_HS_CAN_Init(TX_step16_diagRequest2_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step16_diagRequest2_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_step16_diagRequest2_HS_CAN_Transmit(TX_step16_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_step16_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step16_diagRequest2_HS_CAN_Transmit_raw(TX_step16_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step16_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step16_diagRequest2_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step16_diagRequest2_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_step17_diagRequest2_HS_CAN_Index = 10;

void TX_step17_diagRequest2_HS_CAN_Init(TX_step17_diagRequest2_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step17_diagRequest2_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_step17_diagRequest2_HS_CAN_Transmit(TX_step17_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_step17_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step17_diagRequest2_HS_CAN_Transmit_raw(TX_step17_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step17_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step17_diagRequest2_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step17_diagRequest2_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_step18_diagRequest2_HS_CAN_Index = 11;

void TX_step18_diagRequest2_HS_CAN_Init(TX_step18_diagRequest2_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step18_diagRequest2_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_step18_diagRequest2_HS_CAN_Transmit(TX_step18_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_step18_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step18_diagRequest2_HS_CAN_Transmit_raw(TX_step18_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step18_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step18_diagRequest2_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step18_diagRequest2_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_step19_diagRequest2_HS_CAN_Index = 12;

void TX_step19_diagRequest2_HS_CAN_Init(TX_step19_diagRequest2_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step19_diagRequest2_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_step19_diagRequest2_HS_CAN_Transmit(TX_step19_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_step19_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step19_diagRequest2_HS_CAN_Transmit_raw(TX_step19_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step19_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step19_diagRequest2_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step19_diagRequest2_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_step20_diagRequest2_HS_CAN_Index = 13;

void TX_step20_diagRequest2_HS_CAN_Init(TX_step20_diagRequest2_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step20_diagRequest2_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_step20_diagRequest2_HS_CAN_Transmit(TX_step20_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_step20_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step20_diagRequest2_HS_CAN_Transmit_raw(TX_step20_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step20_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step20_diagRequest2_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step20_diagRequest2_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_step21_diagRequest2_HS_CAN_Index = 14;

void TX_step21_diagRequest2_HS_CAN_Init(TX_step21_diagRequest2_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step21_diagRequest2_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_step21_diagRequest2_HS_CAN_Transmit(TX_step21_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_step21_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step21_diagRequest2_HS_CAN_Transmit_raw(TX_step21_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step21_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step21_diagRequest2_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step21_diagRequest2_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_step22_diagRequest2_HS_CAN_Index = 15;

void TX_step22_diagRequest2_HS_CAN_Init(TX_step22_diagRequest2_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step22_diagRequest2_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_step22_diagRequest2_HS_CAN_Transmit(TX_step22_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_step22_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step22_diagRequest2_HS_CAN_Transmit_raw(TX_step22_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step22_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step22_diagRequest2_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step22_diagRequest2_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_step23_diagRequest2_HS_CAN_Index = 16;

void TX_step23_diagRequest2_HS_CAN_Init(TX_step23_diagRequest2_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step23_diagRequest2_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_step23_diagRequest2_HS_CAN_Transmit(TX_step23_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_step23_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step23_diagRequest2_HS_CAN_Transmit_raw(TX_step23_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step23_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step23_diagRequest2_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step23_diagRequest2_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_step24_diagRequest2_HS_CAN_Index = 17;

void TX_step24_diagRequest2_HS_CAN_Init(TX_step24_diagRequest2_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step24_diagRequest2_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_step24_diagRequest2_HS_CAN_Transmit(TX_step24_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_step24_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step24_diagRequest2_HS_CAN_Transmit_raw(TX_step24_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step24_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step24_diagRequest2_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step24_diagRequest2_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_step25_diagRequest2_HS_CAN_Index = 18;

void TX_step25_diagRequest2_HS_CAN_Init(TX_step25_diagRequest2_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step25_diagRequest2_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_step25_diagRequest2_HS_CAN_Transmit(TX_step25_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_step25_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step25_diagRequest2_HS_CAN_Transmit_raw(TX_step25_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step25_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step25_diagRequest2_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step25_diagRequest2_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_step26_diagRequest2_HS_CAN_Index = 19;

void TX_step26_diagRequest2_HS_CAN_Init(TX_step26_diagRequest2_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step26_diagRequest2_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_step26_diagRequest2_HS_CAN_Transmit(TX_step26_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_step26_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step26_diagRequest2_HS_CAN_Transmit_raw(TX_step26_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step26_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step26_diagRequest2_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step26_diagRequest2_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_step27_diagRequest2_HS_CAN_Index = 20;

void TX_step27_diagRequest2_HS_CAN_Init(TX_step27_diagRequest2_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step27_diagRequest2_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_step27_diagRequest2_HS_CAN_Transmit(TX_step27_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_step27_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step27_diagRequest2_HS_CAN_Transmit_raw(TX_step27_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step27_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step27_diagRequest2_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step27_diagRequest2_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_step28_diagRequest2_HS_CAN_Index = 21;

void TX_step28_diagRequest2_HS_CAN_Init(TX_step28_diagRequest2_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step28_diagRequest2_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_step28_diagRequest2_HS_CAN_Transmit(TX_step28_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_step28_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step28_diagRequest2_HS_CAN_Transmit_raw(TX_step28_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step28_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step28_diagRequest2_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step28_diagRequest2_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_step29_diagRequest2_HS_CAN_Index = 22;

void TX_step29_diagRequest2_HS_CAN_Init(TX_step29_diagRequest2_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step29_diagRequest2_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_step29_diagRequest2_HS_CAN_Transmit(TX_step29_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_step29_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step29_diagRequest2_HS_CAN_Transmit_raw(TX_step29_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step29_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step29_diagRequest2_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step29_diagRequest2_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_step30_diagRequest2_HS_CAN_Index = 23;

void TX_step30_diagRequest2_HS_CAN_Init(TX_step30_diagRequest2_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step30_diagRequest2_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_step30_diagRequest2_HS_CAN_Transmit(TX_step30_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_step30_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step30_diagRequest2_HS_CAN_Transmit_raw(TX_step30_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step30_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step30_diagRequest2_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step30_diagRequest2_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_step31_diagRequest2_HS_CAN_Index = 24;

void TX_step31_diagRequest2_HS_CAN_Init(TX_step31_diagRequest2_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step31_diagRequest2_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_step31_diagRequest2_HS_CAN_Transmit(TX_step31_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_step31_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step31_diagRequest2_HS_CAN_Transmit_raw(TX_step31_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step31_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step31_diagRequest2_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step31_diagRequest2_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_step32_diagRequest2_HS_CAN_Index = 25;

void TX_step32_diagRequest2_HS_CAN_Init(TX_step32_diagRequest2_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step32_diagRequest2_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_step32_diagRequest2_HS_CAN_Transmit(TX_step32_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_step32_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step32_diagRequest2_HS_CAN_Transmit_raw(TX_step32_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step32_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step32_diagRequest2_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step32_diagRequest2_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_step33_diagRequest2_HS_CAN_Index = 26;

void TX_step33_diagRequest2_HS_CAN_Init(TX_step33_diagRequest2_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step33_diagRequest2_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_step33_diagRequest2_HS_CAN_Transmit(TX_step33_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_step33_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step33_diagRequest2_HS_CAN_Transmit_raw(TX_step33_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step33_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step33_diagRequest2_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step33_diagRequest2_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_step34_diagRequest2_HS_CAN_Index = 27;

void TX_step34_diagRequest2_HS_CAN_Init(TX_step34_diagRequest2_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step34_diagRequest2_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_step34_diagRequest2_HS_CAN_Transmit(TX_step34_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_step34_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step34_diagRequest2_HS_CAN_Transmit_raw(TX_step34_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step34_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step34_diagRequest2_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step34_diagRequest2_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_step35_diagRequest2_HS_CAN_Index = 28;

void TX_step35_diagRequest2_HS_CAN_Init(TX_step35_diagRequest2_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step35_diagRequest2_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_step35_diagRequest2_HS_CAN_Transmit(TX_step35_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_step35_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step35_diagRequest2_HS_CAN_Transmit_raw(TX_step35_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step35_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step35_diagRequest2_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step35_diagRequest2_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_step36_diagRequest2_HS_CAN_Index = 29;

void TX_step36_diagRequest2_HS_CAN_Init(TX_step36_diagRequest2_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step36_diagRequest2_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_step36_diagRequest2_HS_CAN_Transmit(TX_step36_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_step36_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step36_diagRequest2_HS_CAN_Transmit_raw(TX_step36_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step36_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step36_diagRequest2_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step36_diagRequest2_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_step37_diagRequest2_HS_CAN_Index = 30;

void TX_step37_diagRequest2_HS_CAN_Init(TX_step37_diagRequest2_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step37_diagRequest2_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_step37_diagRequest2_HS_CAN_Transmit(TX_step37_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_step37_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step37_diagRequest2_HS_CAN_Transmit_raw(TX_step37_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step37_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step37_diagRequest2_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step37_diagRequest2_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_step38_diagRequest2_HS_CAN_Index = 31;

void TX_step38_diagRequest2_HS_CAN_Init(TX_step38_diagRequest2_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step38_diagRequest2_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_step38_diagRequest2_HS_CAN_Transmit(TX_step38_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_step38_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step38_diagRequest2_HS_CAN_Transmit_raw(TX_step38_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step38_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step38_diagRequest2_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step38_diagRequest2_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_step343536_diagRequest2_HS_CAN_Index = 32;

void TX_step343536_diagRequest2_HS_CAN_Init(TX_step343536_diagRequest2_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step343536_diagRequest2_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_step343536_diagRequest2_HS_CAN_Transmit(TX_step343536_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_step343536_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step343536_diagRequest2_HS_CAN_Transmit_raw(TX_step343536_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step343536_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step343536_diagRequest2_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step343536_diagRequest2_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_mpiWrite_diagRequest_step1_1_HS_CAN_Index = 33;

void TX_mpiWrite_diagRequest_step1_1_HS_CAN_Init(TX_mpiWrite_diagRequest_step1_1_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_mpiWrite_diagRequest_step1_1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_mpiWrite_diagRequest_step1_1_HS_CAN_Transmit(TX_mpiWrite_diagRequest_step1_1_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_mpiWrite_diagRequest_step1_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiWrite_diagRequest_step1_1_HS_CAN_Transmit_raw(TX_mpiWrite_diagRequest_step1_1_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_mpiWrite_diagRequest_step1_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiWrite_diagRequest_step1_1_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_mpiWrite_diagRequest_step1_1_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_mpiWrite_diagRequest_step1_2_HS_CAN_Index = 34;

void TX_mpiWrite_diagRequest_step1_2_HS_CAN_Init(TX_mpiWrite_diagRequest_step1_2_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_mpiWrite_diagRequest_step1_2_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_mpiWrite_diagRequest_step1_2_HS_CAN_Transmit(TX_mpiWrite_diagRequest_step1_2_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_mpiWrite_diagRequest_step1_2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiWrite_diagRequest_step1_2_HS_CAN_Transmit_raw(TX_mpiWrite_diagRequest_step1_2_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_mpiWrite_diagRequest_step1_2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiWrite_diagRequest_step1_2_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_mpiWrite_diagRequest_step1_2_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_mpiWrite_diagRequest_step1_3_HS_CAN_Index = 35;

void TX_mpiWrite_diagRequest_step1_3_HS_CAN_Init(TX_mpiWrite_diagRequest_step1_3_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_mpiWrite_diagRequest_step1_3_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_mpiWrite_diagRequest_step1_3_HS_CAN_Transmit(TX_mpiWrite_diagRequest_step1_3_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_mpiWrite_diagRequest_step1_3_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiWrite_diagRequest_step1_3_HS_CAN_Transmit_raw(TX_mpiWrite_diagRequest_step1_3_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_mpiWrite_diagRequest_step1_3_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiWrite_diagRequest_step1_3_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_mpiWrite_diagRequest_step1_3_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_mpiWrite_diagRequest_step2_1_HS_CAN_Index = 36;

void TX_mpiWrite_diagRequest_step2_1_HS_CAN_Init(TX_mpiWrite_diagRequest_step2_1_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_mpiWrite_diagRequest_step2_1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_mpiWrite_diagRequest_step2_1_HS_CAN_Transmit(TX_mpiWrite_diagRequest_step2_1_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_mpiWrite_diagRequest_step2_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiWrite_diagRequest_step2_1_HS_CAN_Transmit_raw(TX_mpiWrite_diagRequest_step2_1_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_mpiWrite_diagRequest_step2_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiWrite_diagRequest_step2_1_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_mpiWrite_diagRequest_step2_1_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_mpiWrite_diagRequest_constructive_HS_CAN_Index = 37;

void TX_mpiWrite_diagRequest_constructive_HS_CAN_Init(TX_mpiWrite_diagRequest_constructive_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_mpiWrite_diagRequest_constructive_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_mpiWrite_diagRequest_constructive_HS_CAN_Transmit(TX_mpiWrite_diagRequest_constructive_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_mpiWrite_diagRequest_constructive_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiWrite_diagRequest_constructive_HS_CAN_Transmit_raw(TX_mpiWrite_diagRequest_constructive_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_mpiWrite_diagRequest_constructive_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiWrite_diagRequest_constructive_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_mpiWrite_diagRequest_constructive_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_mpiWrite_diagRequest_step3_1_HS_CAN_Index = 38;

void TX_mpiWrite_diagRequest_step3_1_HS_CAN_Init(TX_mpiWrite_diagRequest_step3_1_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_mpiWrite_diagRequest_step3_1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_mpiWrite_diagRequest_step3_1_HS_CAN_Transmit(TX_mpiWrite_diagRequest_step3_1_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_mpiWrite_diagRequest_step3_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiWrite_diagRequest_step3_1_HS_CAN_Transmit_raw(TX_mpiWrite_diagRequest_step3_1_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_mpiWrite_diagRequest_step3_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiWrite_diagRequest_step3_1_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_mpiWrite_diagRequest_step3_1_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_mpiWrite_diagRequest_step4_1_HS_CAN_Index = 39;

void TX_mpiWrite_diagRequest_step4_1_HS_CAN_Init(TX_mpiWrite_diagRequest_step4_1_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_mpiWrite_diagRequest_step4_1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_mpiWrite_diagRequest_step4_1_HS_CAN_Transmit(TX_mpiWrite_diagRequest_step4_1_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_mpiWrite_diagRequest_step4_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiWrite_diagRequest_step4_1_HS_CAN_Transmit_raw(TX_mpiWrite_diagRequest_step4_1_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_mpiWrite_diagRequest_step4_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiWrite_diagRequest_step4_1_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_mpiWrite_diagRequest_step4_1_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_mpiWrite_diagRequest_step5_1_HS_CAN_Index = 40;

void TX_mpiWrite_diagRequest_step5_1_HS_CAN_Init(TX_mpiWrite_diagRequest_step5_1_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_mpiWrite_diagRequest_step5_1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_mpiWrite_diagRequest_step5_1_HS_CAN_Transmit(TX_mpiWrite_diagRequest_step5_1_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_mpiWrite_diagRequest_step5_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiWrite_diagRequest_step5_1_HS_CAN_Transmit_raw(TX_mpiWrite_diagRequest_step5_1_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_mpiWrite_diagRequest_step5_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiWrite_diagRequest_step5_1_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_mpiWrite_diagRequest_step5_1_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_mpiWrite_diagRequest_step6_1_HS_CAN_Index = 41;

void TX_mpiWrite_diagRequest_step6_1_HS_CAN_Init(TX_mpiWrite_diagRequest_step6_1_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_mpiWrite_diagRequest_step6_1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_mpiWrite_diagRequest_step6_1_HS_CAN_Transmit(TX_mpiWrite_diagRequest_step6_1_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_mpiWrite_diagRequest_step6_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiWrite_diagRequest_step6_1_HS_CAN_Transmit_raw(TX_mpiWrite_diagRequest_step6_1_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_mpiWrite_diagRequest_step6_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiWrite_diagRequest_step6_1_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_mpiWrite_diagRequest_step6_1_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_mpiWrite_diagRequest_step6_2_HS_CAN_Index = 42;

void TX_mpiWrite_diagRequest_step6_2_HS_CAN_Init(TX_mpiWrite_diagRequest_step6_2_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_mpiWrite_diagRequest_step6_2_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_mpiWrite_diagRequest_step6_2_HS_CAN_Transmit(TX_mpiWrite_diagRequest_step6_2_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_mpiWrite_diagRequest_step6_2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiWrite_diagRequest_step6_2_HS_CAN_Transmit_raw(TX_mpiWrite_diagRequest_step6_2_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_mpiWrite_diagRequest_step6_2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiWrite_diagRequest_step6_2_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_mpiWrite_diagRequest_step6_2_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_mpiWrite_diagRequest_step6_3_HS_CAN_Index = 43;

void TX_mpiWrite_diagRequest_step6_3_HS_CAN_Init(TX_mpiWrite_diagRequest_step6_3_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_mpiWrite_diagRequest_step6_3_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_mpiWrite_diagRequest_step6_3_HS_CAN_Transmit(TX_mpiWrite_diagRequest_step6_3_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_mpiWrite_diagRequest_step6_3_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiWrite_diagRequest_step6_3_HS_CAN_Transmit_raw(TX_mpiWrite_diagRequest_step6_3_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_mpiWrite_diagRequest_step6_3_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiWrite_diagRequest_step6_3_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_mpiWrite_diagRequest_step6_3_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_mpiWrite_diagRequest_step6_4_HS_CAN_Index = 44;

void TX_mpiWrite_diagRequest_step6_4_HS_CAN_Init(TX_mpiWrite_diagRequest_step6_4_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_mpiWrite_diagRequest_step6_4_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_mpiWrite_diagRequest_step6_4_HS_CAN_Transmit(TX_mpiWrite_diagRequest_step6_4_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_mpiWrite_diagRequest_step6_4_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiWrite_diagRequest_step6_4_HS_CAN_Transmit_raw(TX_mpiWrite_diagRequest_step6_4_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_mpiWrite_diagRequest_step6_4_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiWrite_diagRequest_step6_4_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_mpiWrite_diagRequest_step6_4_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_mpiWrite_diagRequest_step7_1_HS_CAN_Index = 45;

void TX_mpiWrite_diagRequest_step7_1_HS_CAN_Init(TX_mpiWrite_diagRequest_step7_1_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_mpiWrite_diagRequest_step7_1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_mpiWrite_diagRequest_step7_1_HS_CAN_Transmit(TX_mpiWrite_diagRequest_step7_1_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_mpiWrite_diagRequest_step7_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiWrite_diagRequest_step7_1_HS_CAN_Transmit_raw(TX_mpiWrite_diagRequest_step7_1_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_mpiWrite_diagRequest_step7_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiWrite_diagRequest_step7_1_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_mpiWrite_diagRequest_step7_1_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_mpiWrite_diagRequest_step8_1_HS_CAN_Index = 46;

void TX_mpiWrite_diagRequest_step8_1_HS_CAN_Init(TX_mpiWrite_diagRequest_step8_1_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_mpiWrite_diagRequest_step8_1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_mpiWrite_diagRequest_step8_1_HS_CAN_Transmit(TX_mpiWrite_diagRequest_step8_1_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_mpiWrite_diagRequest_step8_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiWrite_diagRequest_step8_1_HS_CAN_Transmit_raw(TX_mpiWrite_diagRequest_step8_1_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_mpiWrite_diagRequest_step8_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiWrite_diagRequest_step8_1_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_mpiWrite_diagRequest_step8_1_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_mpiRead_diagRequest_step1_1_HS_CAN_Index = 47;

void TX_mpiRead_diagRequest_step1_1_HS_CAN_Init(TX_mpiRead_diagRequest_step1_1_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_mpiRead_diagRequest_step1_1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_mpiRead_diagRequest_step1_1_HS_CAN_Transmit(TX_mpiRead_diagRequest_step1_1_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_mpiRead_diagRequest_step1_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiRead_diagRequest_step1_1_HS_CAN_Transmit_raw(TX_mpiRead_diagRequest_step1_1_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_mpiRead_diagRequest_step1_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiRead_diagRequest_step1_1_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_mpiRead_diagRequest_step1_1_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_mpiRead_diagRequest_step2_1_HS_CAN_Index = 48;

void TX_mpiRead_diagRequest_step2_1_HS_CAN_Init(TX_mpiRead_diagRequest_step2_1_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_mpiRead_diagRequest_step2_1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_mpiRead_diagRequest_step2_1_HS_CAN_Transmit(TX_mpiRead_diagRequest_step2_1_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_mpiRead_diagRequest_step2_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiRead_diagRequest_step2_1_HS_CAN_Transmit_raw(TX_mpiRead_diagRequest_step2_1_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_mpiRead_diagRequest_step2_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiRead_diagRequest_step2_1_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_mpiRead_diagRequest_step2_1_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_mpiRead_diagRequest_flowControl_HS_CAN_Index = 49;

void TX_mpiRead_diagRequest_flowControl_HS_CAN_Init(TX_mpiRead_diagRequest_flowControl_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_mpiRead_diagRequest_flowControl_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_mpiRead_diagRequest_flowControl_HS_CAN_Transmit(TX_mpiRead_diagRequest_flowControl_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_mpiRead_diagRequest_flowControl_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiRead_diagRequest_flowControl_HS_CAN_Transmit_raw(TX_mpiRead_diagRequest_flowControl_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_mpiRead_diagRequest_flowControl_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiRead_diagRequest_flowControl_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_mpiRead_diagRequest_flowControl_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_mpiRead_diagRequest_step3_1_HS_CAN_Index = 50;

void TX_mpiRead_diagRequest_step3_1_HS_CAN_Init(TX_mpiRead_diagRequest_step3_1_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_mpiRead_diagRequest_step3_1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_mpiRead_diagRequest_step3_1_HS_CAN_Transmit(TX_mpiRead_diagRequest_step3_1_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_mpiRead_diagRequest_step3_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiRead_diagRequest_step3_1_HS_CAN_Transmit_raw(TX_mpiRead_diagRequest_step3_1_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_mpiRead_diagRequest_step3_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiRead_diagRequest_step3_1_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_mpiRead_diagRequest_step3_1_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_mpiRead_diagRequest_step4_1_HS_CAN_Index = 51;

void TX_mpiRead_diagRequest_step4_1_HS_CAN_Init(TX_mpiRead_diagRequest_step4_1_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_mpiRead_diagRequest_step4_1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_mpiRead_diagRequest_step4_1_HS_CAN_Transmit(TX_mpiRead_diagRequest_step4_1_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_mpiRead_diagRequest_step4_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiRead_diagRequest_step4_1_HS_CAN_Transmit_raw(TX_mpiRead_diagRequest_step4_1_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_mpiRead_diagRequest_step4_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiRead_diagRequest_step4_1_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_mpiRead_diagRequest_step4_1_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_mpiRead_diagRequest_step5_1_HS_CAN_Index = 52;

void TX_mpiRead_diagRequest_step5_1_HS_CAN_Init(TX_mpiRead_diagRequest_step5_1_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_mpiRead_diagRequest_step5_1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_mpiRead_diagRequest_step5_1_HS_CAN_Transmit(TX_mpiRead_diagRequest_step5_1_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_mpiRead_diagRequest_step5_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiRead_diagRequest_step5_1_HS_CAN_Transmit_raw(TX_mpiRead_diagRequest_step5_1_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_mpiRead_diagRequest_step5_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiRead_diagRequest_step5_1_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_mpiRead_diagRequest_step5_1_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_mpiRead_diagRequest_step6_1_HS_CAN_Index = 53;

void TX_mpiRead_diagRequest_step6_1_HS_CAN_Init(TX_mpiRead_diagRequest_step6_1_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_mpiRead_diagRequest_step6_1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_mpiRead_diagRequest_step6_1_HS_CAN_Transmit(TX_mpiRead_diagRequest_step6_1_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_mpiRead_diagRequest_step6_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiRead_diagRequest_step6_1_HS_CAN_Transmit_raw(TX_mpiRead_diagRequest_step6_1_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_mpiRead_diagRequest_step6_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiRead_diagRequest_step6_1_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_mpiRead_diagRequest_step6_1_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_mpiRead_diagRequest_step7_1_HS_CAN_Index = 54;

void TX_mpiRead_diagRequest_step7_1_HS_CAN_Init(TX_mpiRead_diagRequest_step7_1_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_mpiRead_diagRequest_step7_1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_mpiRead_diagRequest_step7_1_HS_CAN_Transmit(TX_mpiRead_diagRequest_step7_1_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_mpiRead_diagRequest_step7_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiRead_diagRequest_step7_1_HS_CAN_Transmit_raw(TX_mpiRead_diagRequest_step7_1_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_mpiRead_diagRequest_step7_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiRead_diagRequest_step7_1_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_mpiRead_diagRequest_step7_1_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_mpiRead_diagRequest_step8_1_HS_CAN_Index = 55;

void TX_mpiRead_diagRequest_step8_1_HS_CAN_Init(TX_mpiRead_diagRequest_step8_1_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_mpiRead_diagRequest_step8_1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_mpiRead_diagRequest_step8_1_HS_CAN_Transmit(TX_mpiRead_diagRequest_step8_1_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_mpiRead_diagRequest_step8_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiRead_diagRequest_step8_1_HS_CAN_Transmit_raw(TX_mpiRead_diagRequest_step8_1_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_mpiRead_diagRequest_step8_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiRead_diagRequest_step8_1_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_mpiRead_diagRequest_step8_1_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_mpiRead_diagRequest_step9_1_HS_CAN_Index = 56;

void TX_mpiRead_diagRequest_step9_1_HS_CAN_Init(TX_mpiRead_diagRequest_step9_1_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_mpiRead_diagRequest_step9_1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_mpiRead_diagRequest_step9_1_HS_CAN_Transmit(TX_mpiRead_diagRequest_step9_1_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_mpiRead_diagRequest_step9_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiRead_diagRequest_step9_1_HS_CAN_Transmit_raw(TX_mpiRead_diagRequest_step9_1_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_mpiRead_diagRequest_step9_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiRead_diagRequest_step9_1_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_mpiRead_diagRequest_step9_1_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_mpiWrite_diagRequest_stepX_1_HS_CAN_Index = 57;

void TX_mpiWrite_diagRequest_stepX_1_HS_CAN_Init(TX_mpiWrite_diagRequest_stepX_1_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_mpiWrite_diagRequest_stepX_1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_mpiWrite_diagRequest_stepX_1_HS_CAN_Transmit(TX_mpiWrite_diagRequest_stepX_1_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_mpiWrite_diagRequest_stepX_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiWrite_diagRequest_stepX_1_HS_CAN_Transmit_raw(TX_mpiWrite_diagRequest_stepX_1_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_mpiWrite_diagRequest_stepX_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiWrite_diagRequest_stepX_1_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_mpiWrite_diagRequest_stepX_1_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_TestPresentMessage_HS_CAN_Index = 58;

void TX_TestPresentMessage_HS_CAN_Init(TX_TestPresentMessage_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_TestPresentMessage_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_TestPresentMessage_HS_CAN_Transmit(TX_TestPresentMessage_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_TestPresentMessage_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_TestPresentMessage_HS_CAN_Transmit_raw(TX_TestPresentMessage_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_TestPresentMessage_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_TestPresentMessage_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_TestPresentMessage_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_mpiWrite_diagRequest_stepModel_1_HS_CAN_Index = 59;

void TX_mpiWrite_diagRequest_stepModel_1_HS_CAN_Init(TX_mpiWrite_diagRequest_stepModel_1_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_mpiWrite_diagRequest_stepModel_1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_mpiWrite_diagRequest_stepModel_1_HS_CAN_Transmit(TX_mpiWrite_diagRequest_stepModel_1_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_mpiWrite_diagRequest_stepModel_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiWrite_diagRequest_stepModel_1_HS_CAN_Transmit_raw(TX_mpiWrite_diagRequest_stepModel_1_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_mpiWrite_diagRequest_stepModel_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_mpiWrite_diagRequest_stepModel_1_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_mpiWrite_diagRequest_stepModel_1_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_step7_1_message_1_122_HS_CAN_Index = 60;

void TX_step7_1_message_1_122_HS_CAN_Init(TX_step7_1_message_1_122_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step7_1_message_1_122_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_step7_1_message_1_122_HS_CAN_Transmit(TX_step7_1_message_1_122_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_step7_1_message_1_122_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step7_1_message_1_122_HS_CAN_Transmit_raw(TX_step7_1_message_1_122_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step7_1_message_1_122_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step7_1_message_1_122_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step7_1_message_1_122_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_step7_1_message_2_4c1_HS_CAN_Index = 61;

void TX_step7_1_message_2_4c1_HS_CAN_Init(TX_step7_1_message_2_4c1_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step7_1_message_2_4c1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_step7_1_message_2_4c1_HS_CAN_Transmit(TX_step7_1_message_2_4c1_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_step7_1_message_2_4c1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step7_1_message_2_4c1_HS_CAN_Transmit_raw(TX_step7_1_message_2_4c1_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step7_1_message_2_4c1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step7_1_message_2_4c1_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step7_1_message_2_4c1_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_step7_1_message_3_190_HS_CAN_Index = 62;

void TX_step7_1_message_3_190_HS_CAN_Init(TX_step7_1_message_3_190_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step7_1_message_3_190_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_step7_1_message_3_190_HS_CAN_Transmit(TX_step7_1_message_3_190_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_step7_1_message_3_190_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step7_1_message_3_190_HS_CAN_Transmit_raw(TX_step7_1_message_3_190_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step7_1_message_3_190_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step7_1_message_3_190_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step7_1_message_3_190_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_step7_1_message_4_371_HS_CAN_Index = 63;

void TX_step7_1_message_4_371_HS_CAN_Init(TX_step7_1_message_4_371_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step7_1_message_4_371_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_step7_1_message_4_371_HS_CAN_Transmit(TX_step7_1_message_4_371_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_step7_1_message_4_371_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step7_1_message_4_371_HS_CAN_Transmit_raw(TX_step7_1_message_4_371_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step7_1_message_4_371_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step7_1_message_4_371_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step7_1_message_4_371_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_step7_1_message_5_3c5_HS_CAN_Index = 64;

void TX_step7_1_message_5_3c5_HS_CAN_Init(TX_step7_1_message_5_3c5_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step7_1_message_5_3c5_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_step7_1_message_5_3c5_HS_CAN_Transmit(TX_step7_1_message_5_3c5_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_step7_1_message_5_3c5_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step7_1_message_5_3c5_HS_CAN_Transmit_raw(TX_step7_1_message_5_3c5_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step7_1_message_5_3c5_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step7_1_message_5_3c5_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step7_1_message_5_3c5_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_step39_diagRequest2_HS_CAN_Index = 65;

void TX_step39_diagRequest2_HS_CAN_Init(TX_step39_diagRequest2_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step39_diagRequest2_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_step39_diagRequest2_HS_CAN_Transmit(TX_step39_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_step39_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step39_diagRequest2_HS_CAN_Transmit_raw(TX_step39_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step39_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step39_diagRequest2_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step39_diagRequest2_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_step40_diagRequest2_HS_CAN_Index = 66;

void TX_step40_diagRequest2_HS_CAN_Init(TX_step40_diagRequest2_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step40_diagRequest2_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_step40_diagRequest2_HS_CAN_Transmit(TX_step40_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_step40_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step40_diagRequest2_HS_CAN_Transmit_raw(TX_step40_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step40_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step40_diagRequest2_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step40_diagRequest2_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_step41_diagRequest2_HS_CAN_Index = 67;

void TX_step41_diagRequest2_HS_CAN_Init(TX_step41_diagRequest2_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_step41_diagRequest2_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_step41_diagRequest2_HS_CAN_Transmit(TX_step41_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_step41_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step41_diagRequest2_HS_CAN_Transmit_raw(TX_step41_diagRequest2_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_step41_diagRequest2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_step41_diagRequest2_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_step41_diagRequest2_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_sapaWrite_diagRequest_step2_1_HS_CAN_Index = 68;

void TX_sapaWrite_diagRequest_step2_1_HS_CAN_Init(TX_sapaWrite_diagRequest_step2_1_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_sapaWrite_diagRequest_step2_1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_sapaWrite_diagRequest_step2_1_HS_CAN_Transmit(TX_sapaWrite_diagRequest_step2_1_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_sapaWrite_diagRequest_step2_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_sapaWrite_diagRequest_step2_1_HS_CAN_Transmit_raw(TX_sapaWrite_diagRequest_step2_1_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_sapaWrite_diagRequest_step2_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_sapaWrite_diagRequest_step2_1_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_sapaWrite_diagRequest_step2_1_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_sapaWrite_diagRequest_constructive_1_HS_CAN_Index = 69;

void TX_sapaWrite_diagRequest_constructive_1_HS_CAN_Init(TX_sapaWrite_diagRequest_constructive_1_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_sapaWrite_diagRequest_constructive_1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_sapaWrite_diagRequest_constructive_1_HS_CAN_Transmit(TX_sapaWrite_diagRequest_constructive_1_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_sapaWrite_diagRequest_constructive_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_sapaWrite_diagRequest_constructive_1_HS_CAN_Transmit_raw(TX_sapaWrite_diagRequest_constructive_1_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_sapaWrite_diagRequest_constructive_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_sapaWrite_diagRequest_constructive_1_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_sapaWrite_diagRequest_constructive_1_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_sapaWrite_diagRequest_constructive_2_HS_CAN_Index = 70;

void TX_sapaWrite_diagRequest_constructive_2_HS_CAN_Init(TX_sapaWrite_diagRequest_constructive_2_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_sapaWrite_diagRequest_constructive_2_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_sapaWrite_diagRequest_constructive_2_HS_CAN_Transmit(TX_sapaWrite_diagRequest_constructive_2_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_sapaWrite_diagRequest_constructive_2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_sapaWrite_diagRequest_constructive_2_HS_CAN_Transmit_raw(TX_sapaWrite_diagRequest_constructive_2_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_sapaWrite_diagRequest_constructive_2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_sapaWrite_diagRequest_constructive_2_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_sapaWrite_diagRequest_constructive_2_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_sapaWrite_diagRequest_constructive_3_HS_CAN_Index = 71;

void TX_sapaWrite_diagRequest_constructive_3_HS_CAN_Init(TX_sapaWrite_diagRequest_constructive_3_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_sapaWrite_diagRequest_constructive_3_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_sapaWrite_diagRequest_constructive_3_HS_CAN_Transmit(TX_sapaWrite_diagRequest_constructive_3_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_sapaWrite_diagRequest_constructive_3_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_sapaWrite_diagRequest_constructive_3_HS_CAN_Transmit_raw(TX_sapaWrite_diagRequest_constructive_3_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_sapaWrite_diagRequest_constructive_3_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_sapaWrite_diagRequest_constructive_3_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_sapaWrite_diagRequest_constructive_3_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_sapaRead_diagRequest_step2_HS_CAN_Index = 72;

void TX_sapaRead_diagRequest_step2_HS_CAN_Init(TX_sapaRead_diagRequest_step2_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_sapaRead_diagRequest_step2_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int TX_sapaRead_diagRequest_step2_HS_CAN_Transmit(TX_sapaRead_diagRequest_step2_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 2, TX_sapaRead_diagRequest_step2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_sapaRead_diagRequest_step2_HS_CAN_Transmit_raw(TX_sapaRead_diagRequest_step2_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 2, TX_sapaRead_diagRequest_step2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int TX_sapaRead_diagRequest_step2_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_sapaRead_diagRequest_step2_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int MG_step8_14_Climate_Control_General_Status_HS_CAN_Index = 0;

void MG_step8_14_Climate_Control_General_Status_HS_CAN_Init(MG_step8_14_Climate_Control_General_Status_HS_CAN * pMsg)
{
    double dValues[6] = {0.0};
    uint64 nRawValues[6] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 1, 
    MG_step8_14_Climate_Control_General_Status_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 6, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->ACCmpsrFldOn = dValues[0];
    pMsg->ACCompModReq = dValues[1];
    pMsg->ACCompNormLd = dValues[2];
    pMsg->ACCompNormLdV = dValues[3];
    pMsg->ACCmEngRunReq = dValues[4];
    pMsg->ClmtCtrlTrgtTemp = dValues[5];
    CM_MessageRawInit(g_uiHandle, 1, MG_step8_14_Climate_Control_General_Status_HS_CAN_Index, nRawValues, 6, &iActualSignalMaxCount);
    pMsg->ACCmpsrFldOn_raw = (BYTE)nRawValues[0];
    pMsg->ACCompModReq_raw = (BYTE)nRawValues[1];
    pMsg->ACCompNormLd_raw = (BYTE)nRawValues[2];
    pMsg->ACCompNormLdV_raw = (BYTE)nRawValues[3];
    pMsg->ACCmEngRunReq_raw = (BYTE)nRawValues[4];
    pMsg->ClmtCtrlTrgtTemp_raw = (WORD)nRawValues[5];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void MG_step8_14_Climate_Control_General_Status_HS_CAN_LoadSignalValuesArray(MG_step8_14_Climate_Control_General_Status_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->ACCmpsrFldOn;
    dArray[1] = pMsg->ACCompModReq;
    dArray[2] = pMsg->ACCompNormLd;
    dArray[3] = pMsg->ACCompNormLdV;
    dArray[4] = pMsg->ACCmEngRunReq;
    dArray[5] = pMsg->ClmtCtrlTrgtTemp;
}

void MG_step8_14_Climate_Control_General_Status_HS_CAN_LoadRawSignalValuesArray(MG_step8_14_Climate_Control_General_Status_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->ACCmpsrFldOn_raw;
    nRawValues[1] = pMsg->ACCompModReq_raw;
    nRawValues[2] = pMsg->ACCompNormLd_raw;
    nRawValues[3] = pMsg->ACCompNormLdV_raw;
    nRawValues[4] = pMsg->ACCmEngRunReq_raw;
    nRawValues[5] = pMsg->ClmtCtrlTrgtTemp_raw;
}

int MG_step8_14_Climate_Control_General_Status_HS_CAN_Transmit(MG_step8_14_Climate_Control_General_Status_HS_CAN * pMsg)
{
    double dArray[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 1, MG_step8_14_Climate_Control_General_Status_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        MG_step8_14_Climate_Control_General_Status_HS_CAN_Init(pMsg);
    }

    MG_step8_14_Climate_Control_General_Status_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 1, MG_step8_14_Climate_Control_General_Status_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 6);
}

int MG_step8_14_Climate_Control_General_Status_HS_CAN_Transmit_raw(MG_step8_14_Climate_Control_General_Status_HS_CAN * pMsg)
{
    uint64 nRawValues[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 1, MG_step8_14_Climate_Control_General_Status_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        MG_step8_14_Climate_Control_General_Status_HS_CAN_Init(pMsg);
    }

    MG_step8_14_Climate_Control_General_Status_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 1, MG_step8_14_Climate_Control_General_Status_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 6);
}

int MG_step8_14_Climate_Control_General_Status_HS_CAN_UpdateBytesFromSignals(MG_step8_14_Climate_Control_General_Status_HS_CAN * pMsg)
{
    double dArray[6];

    MG_step8_14_Climate_Control_General_Status_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 1, MG_step8_14_Climate_Control_General_Status_HS_CAN_Index, dArray, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int MG_step8_14_Climate_Control_General_Status_HS_CAN_UpdateBytesFromRawSignals(MG_step8_14_Climate_Control_General_Status_HS_CAN * pMsg)
{
    uint64 nRawValues[6];

    MG_step8_14_Climate_Control_General_Status_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 1, MG_step8_14_Climate_Control_General_Status_HS_CAN_Index, nRawValues, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_Index = 1;

void MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_Init(MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN * pMsg)
{
    double dValues[6] = {0.0};
    uint64 nRawValues[6] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 1, 
    MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 6, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->DrvHCSeatSw1Act = dValues[0];
    pMsg->DrvHCSeatSw2Act = dValues[1];
    pMsg->DrvHCSeatSw3Act = dValues[2];
    pMsg->PassHCSeatSw1Act = dValues[3];
    pMsg->PassHCSeatSw2Act = dValues[4];
    pMsg->PassHCSeatSw3Act = dValues[5];
    CM_MessageRawInit(g_uiHandle, 1, MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_Index, nRawValues, 6, &iActualSignalMaxCount);
    pMsg->DrvHCSeatSw1Act_raw = (BYTE)nRawValues[0];
    pMsg->DrvHCSeatSw2Act_raw = (BYTE)nRawValues[1];
    pMsg->DrvHCSeatSw3Act_raw = (BYTE)nRawValues[2];
    pMsg->PassHCSeatSw1Act_raw = (BYTE)nRawValues[3];
    pMsg->PassHCSeatSw2Act_raw = (BYTE)nRawValues[4];
    pMsg->PassHCSeatSw3Act_raw = (BYTE)nRawValues[5];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_LoadSignalValuesArray(MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->DrvHCSeatSw1Act;
    dArray[1] = pMsg->DrvHCSeatSw2Act;
    dArray[2] = pMsg->DrvHCSeatSw3Act;
    dArray[3] = pMsg->PassHCSeatSw1Act;
    dArray[4] = pMsg->PassHCSeatSw2Act;
    dArray[5] = pMsg->PassHCSeatSw3Act;
}

void MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_LoadRawSignalValuesArray(MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->DrvHCSeatSw1Act_raw;
    nRawValues[1] = pMsg->DrvHCSeatSw2Act_raw;
    nRawValues[2] = pMsg->DrvHCSeatSw3Act_raw;
    nRawValues[3] = pMsg->PassHCSeatSw1Act_raw;
    nRawValues[4] = pMsg->PassHCSeatSw2Act_raw;
    nRawValues[5] = pMsg->PassHCSeatSw3Act_raw;
}

int MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_Transmit(MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN * pMsg)
{
    double dArray[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 1, MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_Init(pMsg);
    }

    MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 1, MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 6);
}

int MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_Transmit_raw(MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN * pMsg)
{
    uint64 nRawValues[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 1, MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_Init(pMsg);
    }

    MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 1, MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 6);
}

int MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_UpdateBytesFromSignals(MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN * pMsg)
{
    double dArray[6];

    MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 1, MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_Index, dArray, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_UpdateBytesFromRawSignals(MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN * pMsg)
{
    uint64 nRawValues[6];

    MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 1, MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_Index, nRawValues, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int MG_step12_Auxiliary_Heater_Status_HS_CAN_Index = 2;

void MG_step12_Auxiliary_Heater_Status_HS_CAN_Init(MG_step12_Auxiliary_Heater_Status_HS_CAN * pMsg)
{
    double dValues[4] = {0.0};
    uint64 nRawValues[4] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 1, 
    MG_step12_Auxiliary_Heater_Status_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 4, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->AuxHtrAtv = dValues[0];
    pMsg->CCClntCrcFlwRtReq = dValues[1];
    pMsg->HtrCoreInltClntTmpCalc = dValues[2];
    pMsg->HtrCoreInltClntTmpCalcV = dValues[3];
    CM_MessageRawInit(g_uiHandle, 1, MG_step12_Auxiliary_Heater_Status_HS_CAN_Index, nRawValues, 4, &iActualSignalMaxCount);
    pMsg->AuxHtrAtv_raw = (BYTE)nRawValues[0];
    pMsg->CCClntCrcFlwRtReq_raw = (BYTE)nRawValues[1];
    pMsg->HtrCoreInltClntTmpCalc_raw = (BYTE)nRawValues[2];
    pMsg->HtrCoreInltClntTmpCalcV_raw = (BYTE)nRawValues[3];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void MG_step12_Auxiliary_Heater_Status_HS_CAN_LoadSignalValuesArray(MG_step12_Auxiliary_Heater_Status_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->AuxHtrAtv;
    dArray[1] = pMsg->CCClntCrcFlwRtReq;
    dArray[2] = pMsg->HtrCoreInltClntTmpCalc;
    dArray[3] = pMsg->HtrCoreInltClntTmpCalcV;
}

void MG_step12_Auxiliary_Heater_Status_HS_CAN_LoadRawSignalValuesArray(MG_step12_Auxiliary_Heater_Status_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->AuxHtrAtv_raw;
    nRawValues[1] = pMsg->CCClntCrcFlwRtReq_raw;
    nRawValues[2] = pMsg->HtrCoreInltClntTmpCalc_raw;
    nRawValues[3] = pMsg->HtrCoreInltClntTmpCalcV_raw;
}

int MG_step12_Auxiliary_Heater_Status_HS_CAN_Transmit(MG_step12_Auxiliary_Heater_Status_HS_CAN * pMsg)
{
    double dArray[4];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 1, MG_step12_Auxiliary_Heater_Status_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        MG_step12_Auxiliary_Heater_Status_HS_CAN_Init(pMsg);
    }

    MG_step12_Auxiliary_Heater_Status_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 1, MG_step12_Auxiliary_Heater_Status_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 4);
}

int MG_step12_Auxiliary_Heater_Status_HS_CAN_Transmit_raw(MG_step12_Auxiliary_Heater_Status_HS_CAN * pMsg)
{
    uint64 nRawValues[4];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 1, MG_step12_Auxiliary_Heater_Status_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        MG_step12_Auxiliary_Heater_Status_HS_CAN_Init(pMsg);
    }

    MG_step12_Auxiliary_Heater_Status_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 1, MG_step12_Auxiliary_Heater_Status_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 4);
}

int MG_step12_Auxiliary_Heater_Status_HS_CAN_UpdateBytesFromSignals(MG_step12_Auxiliary_Heater_Status_HS_CAN * pMsg)
{
    double dArray[4];

    MG_step12_Auxiliary_Heater_Status_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 1, MG_step12_Auxiliary_Heater_Status_HS_CAN_Index, dArray, 4, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int MG_step12_Auxiliary_Heater_Status_HS_CAN_UpdateBytesFromRawSignals(MG_step12_Auxiliary_Heater_Status_HS_CAN * pMsg)
{
    uint64 nRawValues[4];

    MG_step12_Auxiliary_Heater_Status_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 1, MG_step12_Auxiliary_Heater_Status_HS_CAN_Index, nRawValues, 4, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int MG_step10_PCRM006_LIN_Index = 3;

void MG_step10_PCRM006_LIN_Init(MG_step10_PCRM006_LIN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 1, 
    MG_step10_PCRM006_LIN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int MG_step10_PCRM006_LIN_Transmit(MG_step10_PCRM006_LIN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 1, MG_step10_PCRM006_LIN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int MG_step10_PCRM006_LIN_Transmit_raw(MG_step10_PCRM006_LIN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 1, MG_step10_PCRM006_LIN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}


int MG_stepX_diagResponse_HS_CAN_Index = 4;

void MG_stepX_diagResponse_HS_CAN_Init(MG_stepX_diagResponse_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 1, 
    MG_stepX_diagResponse_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int MG_stepX_diagResponse_HS_CAN_Transmit(MG_stepX_diagResponse_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 1, MG_stepX_diagResponse_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int MG_stepX_diagResponse_HS_CAN_Transmit_raw(MG_stepX_diagResponse_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 1, MG_stepX_diagResponse_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}


int MG_C_diag_response1Data_HS_CAN_Index = 5;

void MG_C_diag_response1Data_HS_CAN_Init(MG_C_diag_response1Data_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 1, 
    MG_C_diag_response1Data_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int MG_C_diag_response1Data_HS_CAN_Transmit(MG_C_diag_response1Data_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 1, MG_C_diag_response1Data_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int MG_C_diag_response1Data_HS_CAN_Transmit_raw(MG_C_diag_response1Data_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 1, MG_C_diag_response1Data_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}


int MG_step13_Rear_Window_Defog_Status_HS_CAN_Index = 6;

void MG_step13_Rear_Window_Defog_Status_HS_CAN_Init(MG_step13_Rear_Window_Defog_Status_HS_CAN * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 1, 
    MG_step13_Rear_Window_Defog_Status_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->RrWndDfgOn = dValues[0];
    CM_MessageRawInit(g_uiHandle, 1, MG_step13_Rear_Window_Defog_Status_HS_CAN_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->RrWndDfgOn_raw = (BYTE)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void MG_step13_Rear_Window_Defog_Status_HS_CAN_LoadSignalValuesArray(MG_step13_Rear_Window_Defog_Status_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->RrWndDfgOn;
}

void MG_step13_Rear_Window_Defog_Status_HS_CAN_LoadRawSignalValuesArray(MG_step13_Rear_Window_Defog_Status_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->RrWndDfgOn_raw;
}

int MG_step13_Rear_Window_Defog_Status_HS_CAN_Transmit(MG_step13_Rear_Window_Defog_Status_HS_CAN * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 1, MG_step13_Rear_Window_Defog_Status_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        MG_step13_Rear_Window_Defog_Status_HS_CAN_Init(pMsg);
    }

    MG_step13_Rear_Window_Defog_Status_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 1, MG_step13_Rear_Window_Defog_Status_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int MG_step13_Rear_Window_Defog_Status_HS_CAN_Transmit_raw(MG_step13_Rear_Window_Defog_Status_HS_CAN * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 1, MG_step13_Rear_Window_Defog_Status_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        MG_step13_Rear_Window_Defog_Status_HS_CAN_Init(pMsg);
    }

    MG_step13_Rear_Window_Defog_Status_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 1, MG_step13_Rear_Window_Defog_Status_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int MG_step13_Rear_Window_Defog_Status_HS_CAN_UpdateBytesFromSignals(MG_step13_Rear_Window_Defog_Status_HS_CAN * pMsg)
{
    double dArray[1];

    MG_step13_Rear_Window_Defog_Status_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 1, MG_step13_Rear_Window_Defog_Status_HS_CAN_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int MG_step13_Rear_Window_Defog_Status_HS_CAN_UpdateBytesFromRawSignals(MG_step13_Rear_Window_Defog_Status_HS_CAN * pMsg)
{
    uint64 nRawValues[1];

    MG_step13_Rear_Window_Defog_Status_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 1, MG_step13_Rear_Window_Defog_Status_HS_CAN_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int MG_mpi_diagResponse_HS_CAN_Index = 7;

void MG_mpi_diagResponse_HS_CAN_Init(MG_mpi_diagResponse_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 1, 
    MG_mpi_diagResponse_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int MG_mpi_diagResponse_HS_CAN_Transmit(MG_mpi_diagResponse_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 1, MG_mpi_diagResponse_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int MG_mpi_diagResponse_HS_CAN_Transmit_raw(MG_mpi_diagResponse_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 1, MG_mpi_diagResponse_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}


int MG_mpi_diagResponse_consFrame1_HS_CAN_Index = 8;

void MG_mpi_diagResponse_consFrame1_HS_CAN_Init(MG_mpi_diagResponse_consFrame1_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 1, 
    MG_mpi_diagResponse_consFrame1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int MG_mpi_diagResponse_consFrame1_HS_CAN_Transmit(MG_mpi_diagResponse_consFrame1_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 1, MG_mpi_diagResponse_consFrame1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int MG_mpi_diagResponse_consFrame1_HS_CAN_Transmit_raw(MG_mpi_diagResponse_consFrame1_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 1, MG_mpi_diagResponse_consFrame1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}


int MG_mpi_diagResponse_consFrame2_HS_CAN_Index = 9;

void MG_mpi_diagResponse_consFrame2_HS_CAN_Init(MG_mpi_diagResponse_consFrame2_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 1, 
    MG_mpi_diagResponse_consFrame2_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int MG_mpi_diagResponse_consFrame2_HS_CAN_Transmit(MG_mpi_diagResponse_consFrame2_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 1, MG_mpi_diagResponse_consFrame2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int MG_mpi_diagResponse_consFrame2_HS_CAN_Transmit_raw(MG_mpi_diagResponse_consFrame2_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 1, MG_mpi_diagResponse_consFrame2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}


int MG_step9_PCRM005_LIN2__neoVI_3G__Index = 10;

void MG_step9_PCRM005_LIN2__neoVI_3G__Init(MG_step9_PCRM005_LIN2__neoVI_3G_ * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 1, 
    MG_step9_PCRM005_LIN2__neoVI_3G__Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int MG_step9_PCRM005_LIN2__neoVI_3G__Transmit(MG_step9_PCRM005_LIN2__neoVI_3G_ * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 1, MG_step9_PCRM005_LIN2__neoVI_3G__Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int MG_step9_PCRM005_LIN2__neoVI_3G__Transmit_raw(MG_step9_PCRM005_LIN2__neoVI_3G_ * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 1, MG_step9_PCRM005_LIN2__neoVI_3G__Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}


int MG_step10_1_PCRM006_1_LIN3__neoVI_3G__Index = 11;

void MG_step10_1_PCRM006_1_LIN3__neoVI_3G__Init(MG_step10_1_PCRM006_1_LIN3__neoVI_3G_ * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 1, 
    MG_step10_1_PCRM006_1_LIN3__neoVI_3G__Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int MG_step10_1_PCRM006_1_LIN3__neoVI_3G__Transmit(MG_step10_1_PCRM006_1_LIN3__neoVI_3G_ * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 1, MG_step10_1_PCRM006_1_LIN3__neoVI_3G__Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int MG_step10_1_PCRM006_1_LIN3__neoVI_3G__Transmit_raw(MG_step10_1_PCRM006_1_LIN3__neoVI_3G_ * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 1, MG_step10_1_PCRM006_1_LIN3__neoVI_3G__Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}


int DB_Report_Message_neoVI_Index = 0;

void DB_Report_Message_neoVI_Init(DB_Report_Message_neoVI * pMsg)
{
    double dValues[14] = {0.0};
    uint64 nRawValues[14] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 14, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->MISC3_AIN = dValues[0];
    pMsg->MISC4_AIN = dValues[1];
    pMsg->MISC5_AIN = dValues[2];
    pMsg->MISC6_AIN = dValues[3];
    pMsg->MISC1 = dValues[4];
    pMsg->MISC2 = dValues[5];
    pMsg->MISC3 = dValues[6];
    pMsg->MISC4 = dValues[7];
    pMsg->MISC5 = dValues[8];
    pMsg->MISC6 = dValues[9];
    pMsg->LED1 = dValues[10];
    pMsg->LED2 = dValues[11];
    pMsg->LIN1 = dValues[12];
    pMsg->LIN2 = dValues[13];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message_neoVI_Index, nRawValues, 14, &iActualSignalMaxCount);
    pMsg->MISC3_AIN_raw = (WORD)nRawValues[0];
    pMsg->MISC4_AIN_raw = (WORD)nRawValues[1];
    pMsg->MISC5_AIN_raw = (WORD)nRawValues[2];
    pMsg->MISC6_AIN_raw = (WORD)nRawValues[3];
    pMsg->MISC1_raw = (BYTE)nRawValues[4];
    pMsg->MISC2_raw = (BYTE)nRawValues[5];
    pMsg->MISC3_raw = (BYTE)nRawValues[6];
    pMsg->MISC4_raw = (BYTE)nRawValues[7];
    pMsg->MISC5_raw = (BYTE)nRawValues[8];
    pMsg->MISC6_raw = (BYTE)nRawValues[9];
    pMsg->LED1_raw = (BYTE)nRawValues[10];
    pMsg->LED2_raw = (BYTE)nRawValues[11];
    pMsg->LIN1_raw = (BYTE)nRawValues[12];
    pMsg->LIN2_raw = (BYTE)nRawValues[13];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message_neoVI_LoadSignalValuesArray(DB_Report_Message_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->MISC3_AIN;
    dArray[1] = pMsg->MISC4_AIN;
    dArray[2] = pMsg->MISC5_AIN;
    dArray[3] = pMsg->MISC6_AIN;
    dArray[4] = pMsg->MISC1;
    dArray[5] = pMsg->MISC2;
    dArray[6] = pMsg->MISC3;
    dArray[7] = pMsg->MISC4;
    dArray[8] = pMsg->MISC5;
    dArray[9] = pMsg->MISC6;
    dArray[10] = pMsg->LED1;
    dArray[11] = pMsg->LED2;
    dArray[12] = pMsg->LIN1;
    dArray[13] = pMsg->LIN2;
}

void DB_Report_Message_neoVI_LoadRawSignalValuesArray(DB_Report_Message_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->MISC3_AIN_raw;
    nRawValues[1] = pMsg->MISC4_AIN_raw;
    nRawValues[2] = pMsg->MISC5_AIN_raw;
    nRawValues[3] = pMsg->MISC6_AIN_raw;
    nRawValues[4] = pMsg->MISC1_raw;
    nRawValues[5] = pMsg->MISC2_raw;
    nRawValues[6] = pMsg->MISC3_raw;
    nRawValues[7] = pMsg->MISC4_raw;
    nRawValues[8] = pMsg->MISC5_raw;
    nRawValues[9] = pMsg->MISC6_raw;
    nRawValues[10] = pMsg->LED1_raw;
    nRawValues[11] = pMsg->LED2_raw;
    nRawValues[12] = pMsg->LIN1_raw;
    nRawValues[13] = pMsg->LIN2_raw;
}

int DB_Report_Message_neoVI_Transmit(DB_Report_Message_neoVI * pMsg)
{
    double dArray[14];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message_neoVI_Init(pMsg);
    }

    DB_Report_Message_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 14);
}

int DB_Report_Message_neoVI_Transmit_raw(DB_Report_Message_neoVI * pMsg)
{
    uint64 nRawValues[14];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message_neoVI_Init(pMsg);
    }

    DB_Report_Message_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 14);
}

int DB_Report_Message_neoVI_UpdateBytesFromSignals(DB_Report_Message_neoVI * pMsg)
{
    double dArray[14];

    DB_Report_Message_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message_neoVI_Index, dArray, 14, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Report_Message_neoVI_UpdateBytesFromRawSignals(DB_Report_Message_neoVI * pMsg)
{
    uint64 nRawValues[14];

    DB_Report_Message_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message_neoVI_Index, nRawValues, 14, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Report_Message__PWM__neoVI_Index = 1;

void DB_Report_Message__PWM__neoVI_Init(DB_Report_Message__PWM__neoVI * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__PWM__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->PWM_In_1 = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__PWM__neoVI_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->PWM_In_1_raw = (DWORD)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__PWM__neoVI_LoadSignalValuesArray(DB_Report_Message__PWM__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->PWM_In_1;
}

void DB_Report_Message__PWM__neoVI_LoadRawSignalValuesArray(DB_Report_Message__PWM__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->PWM_In_1_raw;
}

int DB_Report_Message__PWM__neoVI_Transmit(DB_Report_Message__PWM__neoVI * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__PWM__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__PWM__neoVI_Init(pMsg);
    }

    DB_Report_Message__PWM__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__PWM__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_Report_Message__PWM__neoVI_Transmit_raw(DB_Report_Message__PWM__neoVI * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__PWM__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__PWM__neoVI_Init(pMsg);
    }

    DB_Report_Message__PWM__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__PWM__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_Report_Message__PWM__neoVI_UpdateBytesFromSignals(DB_Report_Message__PWM__neoVI * pMsg)
{
    double dArray[1];

    DB_Report_Message__PWM__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__PWM__neoVI_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Report_Message__PWM__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__PWM__neoVI * pMsg)
{
    uint64 nRawValues[1];

    DB_Report_Message__PWM__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__PWM__neoVI_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Report_Message__VCAN_RF__neoVI_Index = 2;

void DB_Report_Message__VCAN_RF__neoVI_Init(DB_Report_Message__VCAN_RF__neoVI * pMsg)
{
    double dValues[10] = {0.0};
    uint64 nRawValues[10] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__VCAN_RF__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 10, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->MISC1_AIN = dValues[0];
    pMsg->MISC_1 = dValues[1];
    pMsg->MISC_2 = dValues[2];
    pMsg->MISC_3 = dValues[3];
    pMsg->MISC_4 = dValues[4];
    pMsg->Vehicle_Battery_Voltage = dValues[5];
    pMsg->Temperature = dValues[6];
    pMsg->Hardware_Revision = dValues[7];
    pMsg->RTC_Battery_Measure_Enabled = dValues[8];
    pMsg->RTC_Battery_Voltage = dValues[9];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, nRawValues, 10, &iActualSignalMaxCount);
    pMsg->MISC1_AIN_raw = (WORD)nRawValues[0];
    pMsg->MISC_1_raw = (BYTE)nRawValues[1];
    pMsg->MISC_2_raw = (BYTE)nRawValues[2];
    pMsg->MISC_3_raw = (BYTE)nRawValues[3];
    pMsg->MISC_4_raw = (BYTE)nRawValues[4];
    pMsg->Vehicle_Battery_Voltage_raw = (WORD)nRawValues[5];
    pMsg->Temperature_raw = (WORD)nRawValues[6];
    pMsg->Hardware_Revision_raw = (WORD)nRawValues[7];
    pMsg->RTC_Battery_Measure_Enabled_raw = (BYTE)nRawValues[8];
    pMsg->RTC_Battery_Voltage_raw = (WORD)nRawValues[9];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__VCAN_RF__neoVI_LoadSignalValuesArray(DB_Report_Message__VCAN_RF__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->MISC1_AIN;
    dArray[1] = pMsg->MISC_1;
    dArray[2] = pMsg->MISC_2;
    dArray[3] = pMsg->MISC_3;
    dArray[4] = pMsg->MISC_4;
    dArray[5] = pMsg->Vehicle_Battery_Voltage;
    dArray[6] = pMsg->Temperature;
    dArray[7] = pMsg->Hardware_Revision;
    dArray[8] = pMsg->RTC_Battery_Measure_Enabled;
    dArray[9] = pMsg->RTC_Battery_Voltage;
}

void DB_Report_Message__VCAN_RF__neoVI_LoadRawSignalValuesArray(DB_Report_Message__VCAN_RF__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->MISC1_AIN_raw;
    nRawValues[1] = pMsg->MISC_1_raw;
    nRawValues[2] = pMsg->MISC_2_raw;
    nRawValues[3] = pMsg->MISC_3_raw;
    nRawValues[4] = pMsg->MISC_4_raw;
    nRawValues[5] = pMsg->Vehicle_Battery_Voltage_raw;
    nRawValues[6] = pMsg->Temperature_raw;
    nRawValues[7] = pMsg->Hardware_Revision_raw;
    nRawValues[8] = pMsg->RTC_Battery_Measure_Enabled_raw;
    nRawValues[9] = pMsg->RTC_Battery_Voltage_raw;
}

int DB_Report_Message__VCAN_RF__neoVI_Transmit(DB_Report_Message__VCAN_RF__neoVI * pMsg)
{
    double dArray[10];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__VCAN_RF__neoVI_Init(pMsg);
    }

    DB_Report_Message__VCAN_RF__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 10);
}

int DB_Report_Message__VCAN_RF__neoVI_Transmit_raw(DB_Report_Message__VCAN_RF__neoVI * pMsg)
{
    uint64 nRawValues[10];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__VCAN_RF__neoVI_Init(pMsg);
    }

    DB_Report_Message__VCAN_RF__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 10);
}

int DB_Report_Message__VCAN_RF__neoVI_UpdateBytesFromSignals(DB_Report_Message__VCAN_RF__neoVI * pMsg)
{
    double dArray[10];

    DB_Report_Message__VCAN_RF__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, dArray, 10, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Report_Message__VCAN_RF__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__VCAN_RF__neoVI * pMsg)
{
    uint64 nRawValues[10];

    DB_Report_Message__VCAN_RF__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, nRawValues, 10, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Report_Message__neoVI_Fire2__neoVI_Index = 3;

void DB_Report_Message__neoVI_Fire2__neoVI_Init(DB_Report_Message__neoVI_Fire2__neoVI * pMsg)
{
    double dValues[7] = {0.0};
    uint64 nRawValues[7] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__neoVI_Fire2__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 7, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->EMISC1_AIN = dValues[0];
    pMsg->EMISC2_AIN = dValues[1];
    pMsg->MISC3 = dValues[2];
    pMsg->MISC4 = dValues[3];
    pMsg->Vehicle_Battery_Voltage = dValues[4];
    pMsg->Temperature = dValues[5];
    pMsg->RTC_Battery_Voltage = dValues[6];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, nRawValues, 7, &iActualSignalMaxCount);
    pMsg->EMISC1_AIN_raw = (WORD)nRawValues[0];
    pMsg->EMISC2_AIN_raw = (WORD)nRawValues[1];
    pMsg->MISC3_raw = (BYTE)nRawValues[2];
    pMsg->MISC4_raw = (BYTE)nRawValues[3];
    pMsg->Vehicle_Battery_Voltage_raw = (WORD)nRawValues[4];
    pMsg->Temperature_raw = (WORD)nRawValues[5];
    pMsg->RTC_Battery_Voltage_raw = (WORD)nRawValues[6];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__neoVI_Fire2__neoVI_LoadSignalValuesArray(DB_Report_Message__neoVI_Fire2__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->EMISC1_AIN;
    dArray[1] = pMsg->EMISC2_AIN;
    dArray[2] = pMsg->MISC3;
    dArray[3] = pMsg->MISC4;
    dArray[4] = pMsg->Vehicle_Battery_Voltage;
    dArray[5] = pMsg->Temperature;
    dArray[6] = pMsg->RTC_Battery_Voltage;
}

void DB_Report_Message__neoVI_Fire2__neoVI_LoadRawSignalValuesArray(DB_Report_Message__neoVI_Fire2__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->EMISC1_AIN_raw;
    nRawValues[1] = pMsg->EMISC2_AIN_raw;
    nRawValues[2] = pMsg->MISC3_raw;
    nRawValues[3] = pMsg->MISC4_raw;
    nRawValues[4] = pMsg->Vehicle_Battery_Voltage_raw;
    nRawValues[5] = pMsg->Temperature_raw;
    nRawValues[6] = pMsg->RTC_Battery_Voltage_raw;
}

int DB_Report_Message__neoVI_Fire2__neoVI_Transmit(DB_Report_Message__neoVI_Fire2__neoVI * pMsg)
{
    double dArray[7];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__neoVI_Fire2__neoVI_Init(pMsg);
    }

    DB_Report_Message__neoVI_Fire2__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 7);
}

int DB_Report_Message__neoVI_Fire2__neoVI_Transmit_raw(DB_Report_Message__neoVI_Fire2__neoVI * pMsg)
{
    uint64 nRawValues[7];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__neoVI_Fire2__neoVI_Init(pMsg);
    }

    DB_Report_Message__neoVI_Fire2__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 7);
}

int DB_Report_Message__neoVI_Fire2__neoVI_UpdateBytesFromSignals(DB_Report_Message__neoVI_Fire2__neoVI * pMsg)
{
    double dArray[7];

    DB_Report_Message__neoVI_Fire2__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, dArray, 7, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Report_Message__neoVI_Fire2__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__neoVI_Fire2__neoVI * pMsg)
{
    uint64 nRawValues[7];

    DB_Report_Message__neoVI_Fire2__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, nRawValues, 7, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Report_Message__GPS_Latitude__neoVI_Index = 4;

void DB_Report_Message__GPS_Latitude__neoVI_Init(DB_Report_Message__GPS_Latitude__neoVI * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__GPS_Latitude__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Latitude = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__GPS_Latitude__neoVI_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->Latitude_raw = (uint64)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__GPS_Latitude__neoVI_LoadSignalValuesArray(DB_Report_Message__GPS_Latitude__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Latitude;
}

void DB_Report_Message__GPS_Latitude__neoVI_LoadRawSignalValuesArray(DB_Report_Message__GPS_Latitude__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Latitude_raw;
}

int DB_Report_Message__GPS_Latitude__neoVI_Transmit(DB_Report_Message__GPS_Latitude__neoVI * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Latitude__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Latitude__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Latitude__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Latitude__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_Report_Message__GPS_Latitude__neoVI_Transmit_raw(DB_Report_Message__GPS_Latitude__neoVI * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Latitude__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Latitude__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Latitude__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Latitude__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_Report_Message__GPS_Latitude__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Latitude__neoVI * pMsg)
{
    double dArray[1];

    DB_Report_Message__GPS_Latitude__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Latitude__neoVI_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Report_Message__GPS_Latitude__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Latitude__neoVI * pMsg)
{
    uint64 nRawValues[1];

    DB_Report_Message__GPS_Latitude__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Latitude__neoVI_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Report_Message__GPS_Longitude__neoVI_Index = 5;

void DB_Report_Message__GPS_Longitude__neoVI_Init(DB_Report_Message__GPS_Longitude__neoVI * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__GPS_Longitude__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Longitude = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__GPS_Longitude__neoVI_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->Longitude_raw = (uint64)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__GPS_Longitude__neoVI_LoadSignalValuesArray(DB_Report_Message__GPS_Longitude__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Longitude;
}

void DB_Report_Message__GPS_Longitude__neoVI_LoadRawSignalValuesArray(DB_Report_Message__GPS_Longitude__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Longitude_raw;
}

int DB_Report_Message__GPS_Longitude__neoVI_Transmit(DB_Report_Message__GPS_Longitude__neoVI * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Longitude__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Longitude__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Longitude__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Longitude__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_Report_Message__GPS_Longitude__neoVI_Transmit_raw(DB_Report_Message__GPS_Longitude__neoVI * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Longitude__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Longitude__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Longitude__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Longitude__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_Report_Message__GPS_Longitude__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Longitude__neoVI * pMsg)
{
    double dArray[1];

    DB_Report_Message__GPS_Longitude__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Longitude__neoVI_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Report_Message__GPS_Longitude__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Longitude__neoVI * pMsg)
{
    uint64 nRawValues[1];

    DB_Report_Message__GPS_Longitude__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Longitude__neoVI_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Report_Message__GPS_Flags__neoVI_Index = 6;

void DB_Report_Message__GPS_Flags__neoVI_Init(DB_Report_Message__GPS_Flags__neoVI * pMsg)
{
    double dValues[8] = {0.0};
    uint64 nRawValues[8] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__GPS_Flags__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 8, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Update_Count = dValues[0];
    pMsg->GPS_Date_Available = dValues[1];
    pMsg->GPS_Time_Available = dValues[2];
    pMsg->GPS_Accuracy_Available = dValues[3];
    pMsg->GPS_Bearing_Available = dValues[4];
    pMsg->GPS_Speed_Available = dValues[5];
    pMsg->GPS_Altitude_Available = dValues[6];
    pMsg->GPS_Lat_Lon_Available = dValues[7];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, nRawValues, 8, &iActualSignalMaxCount);
    pMsg->Update_Count_raw = (BYTE)nRawValues[0];
    pMsg->GPS_Date_Available_raw = (BYTE)nRawValues[1];
    pMsg->GPS_Time_Available_raw = (BYTE)nRawValues[2];
    pMsg->GPS_Accuracy_Available_raw = (BYTE)nRawValues[3];
    pMsg->GPS_Bearing_Available_raw = (BYTE)nRawValues[4];
    pMsg->GPS_Speed_Available_raw = (BYTE)nRawValues[5];
    pMsg->GPS_Altitude_Available_raw = (BYTE)nRawValues[6];
    pMsg->GPS_Lat_Lon_Available_raw = (BYTE)nRawValues[7];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__GPS_Flags__neoVI_LoadSignalValuesArray(DB_Report_Message__GPS_Flags__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Update_Count;
    dArray[1] = pMsg->GPS_Date_Available;
    dArray[2] = pMsg->GPS_Time_Available;
    dArray[3] = pMsg->GPS_Accuracy_Available;
    dArray[4] = pMsg->GPS_Bearing_Available;
    dArray[5] = pMsg->GPS_Speed_Available;
    dArray[6] = pMsg->GPS_Altitude_Available;
    dArray[7] = pMsg->GPS_Lat_Lon_Available;
}

void DB_Report_Message__GPS_Flags__neoVI_LoadRawSignalValuesArray(DB_Report_Message__GPS_Flags__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Update_Count_raw;
    nRawValues[1] = pMsg->GPS_Date_Available_raw;
    nRawValues[2] = pMsg->GPS_Time_Available_raw;
    nRawValues[3] = pMsg->GPS_Accuracy_Available_raw;
    nRawValues[4] = pMsg->GPS_Bearing_Available_raw;
    nRawValues[5] = pMsg->GPS_Speed_Available_raw;
    nRawValues[6] = pMsg->GPS_Altitude_Available_raw;
    nRawValues[7] = pMsg->GPS_Lat_Lon_Available_raw;
}

int DB_Report_Message__GPS_Flags__neoVI_Transmit(DB_Report_Message__GPS_Flags__neoVI * pMsg)
{
    double dArray[8];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Flags__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Flags__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 8);
}

int DB_Report_Message__GPS_Flags__neoVI_Transmit_raw(DB_Report_Message__GPS_Flags__neoVI * pMsg)
{
    uint64 nRawValues[8];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Flags__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Flags__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 8);
}

int DB_Report_Message__GPS_Flags__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Flags__neoVI * pMsg)
{
    double dArray[8];

    DB_Report_Message__GPS_Flags__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, dArray, 8, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Report_Message__GPS_Flags__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Flags__neoVI * pMsg)
{
    uint64 nRawValues[8];

    DB_Report_Message__GPS_Flags__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, nRawValues, 8, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Report_Message__GPS_Altitude__neoVI_Index = 7;

void DB_Report_Message__GPS_Altitude__neoVI_Init(DB_Report_Message__GPS_Altitude__neoVI * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__GPS_Altitude__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Altitude_Ellipse = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__GPS_Altitude__neoVI_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->Altitude_Ellipse_raw = (uint64)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__GPS_Altitude__neoVI_LoadSignalValuesArray(DB_Report_Message__GPS_Altitude__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Altitude_Ellipse;
}

void DB_Report_Message__GPS_Altitude__neoVI_LoadRawSignalValuesArray(DB_Report_Message__GPS_Altitude__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Altitude_Ellipse_raw;
}

int DB_Report_Message__GPS_Altitude__neoVI_Transmit(DB_Report_Message__GPS_Altitude__neoVI * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Altitude__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Altitude__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Altitude__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Altitude__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_Report_Message__GPS_Altitude__neoVI_Transmit_raw(DB_Report_Message__GPS_Altitude__neoVI * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Altitude__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Altitude__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Altitude__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Altitude__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_Report_Message__GPS_Altitude__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Altitude__neoVI * pMsg)
{
    double dArray[1];

    DB_Report_Message__GPS_Altitude__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Altitude__neoVI_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Report_Message__GPS_Altitude__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Altitude__neoVI * pMsg)
{
    uint64 nRawValues[1];

    DB_Report_Message__GPS_Altitude__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Altitude__neoVI_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Report_Message__GPS_Speed_Bearing__neoVI_Index = 8;

void DB_Report_Message__GPS_Speed_Bearing__neoVI_Init(DB_Report_Message__GPS_Speed_Bearing__neoVI * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__GPS_Speed_Bearing__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Speed = dValues[0];
    pMsg->Bearing = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__GPS_Speed_Bearing__neoVI_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->Speed_raw = (DWORD)nRawValues[0];
    pMsg->Bearing_raw = (DWORD)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__GPS_Speed_Bearing__neoVI_LoadSignalValuesArray(DB_Report_Message__GPS_Speed_Bearing__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Speed;
    dArray[1] = pMsg->Bearing;
}

void DB_Report_Message__GPS_Speed_Bearing__neoVI_LoadRawSignalValuesArray(DB_Report_Message__GPS_Speed_Bearing__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Speed_raw;
    nRawValues[1] = pMsg->Bearing_raw;
}

int DB_Report_Message__GPS_Speed_Bearing__neoVI_Transmit(DB_Report_Message__GPS_Speed_Bearing__neoVI * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Speed_Bearing__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Speed_Bearing__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Speed_Bearing__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Speed_Bearing__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_Report_Message__GPS_Speed_Bearing__neoVI_Transmit_raw(DB_Report_Message__GPS_Speed_Bearing__neoVI * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Speed_Bearing__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Speed_Bearing__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Speed_Bearing__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Speed_Bearing__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_Report_Message__GPS_Speed_Bearing__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Speed_Bearing__neoVI * pMsg)
{
    double dArray[2];

    DB_Report_Message__GPS_Speed_Bearing__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Speed_Bearing__neoVI_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Report_Message__GPS_Speed_Bearing__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Speed_Bearing__neoVI * pMsg)
{
    uint64 nRawValues[2];

    DB_Report_Message__GPS_Speed_Bearing__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Speed_Bearing__neoVI_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Report_Message__GPS_Accuracy__neoVI_Index = 9;

void DB_Report_Message__GPS_Accuracy__neoVI_Init(DB_Report_Message__GPS_Accuracy__neoVI * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__GPS_Accuracy__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Accuracy = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__GPS_Accuracy__neoVI_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->Accuracy_raw = (DWORD)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__GPS_Accuracy__neoVI_LoadSignalValuesArray(DB_Report_Message__GPS_Accuracy__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Accuracy;
}

void DB_Report_Message__GPS_Accuracy__neoVI_LoadRawSignalValuesArray(DB_Report_Message__GPS_Accuracy__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Accuracy_raw;
}

int DB_Report_Message__GPS_Accuracy__neoVI_Transmit(DB_Report_Message__GPS_Accuracy__neoVI * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Accuracy__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Accuracy__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Accuracy__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Accuracy__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_Report_Message__GPS_Accuracy__neoVI_Transmit_raw(DB_Report_Message__GPS_Accuracy__neoVI * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Accuracy__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Accuracy__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Accuracy__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Accuracy__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_Report_Message__GPS_Accuracy__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Accuracy__neoVI * pMsg)
{
    double dArray[1];

    DB_Report_Message__GPS_Accuracy__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Accuracy__neoVI_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Report_Message__GPS_Accuracy__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Accuracy__neoVI * pMsg)
{
    uint64 nRawValues[1];

    DB_Report_Message__GPS_Accuracy__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Accuracy__neoVI_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Report_Message__GPS_Time__neoVI_Index = 10;

void DB_Report_Message__GPS_Time__neoVI_Init(DB_Report_Message__GPS_Time__neoVI * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__GPS_Time__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Timestamp = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__GPS_Time__neoVI_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->Timestamp_raw = (uint64)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__GPS_Time__neoVI_LoadSignalValuesArray(DB_Report_Message__GPS_Time__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Timestamp;
}

void DB_Report_Message__GPS_Time__neoVI_LoadRawSignalValuesArray(DB_Report_Message__GPS_Time__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Timestamp_raw;
}

int DB_Report_Message__GPS_Time__neoVI_Transmit(DB_Report_Message__GPS_Time__neoVI * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Time__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Time__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Time__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Time__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_Report_Message__GPS_Time__neoVI_Transmit_raw(DB_Report_Message__GPS_Time__neoVI * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Time__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Time__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Time__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Time__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_Report_Message__GPS_Time__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Time__neoVI * pMsg)
{
    double dArray[1];

    DB_Report_Message__GPS_Time__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Time__neoVI_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Report_Message__GPS_Time__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Time__neoVI * pMsg)
{
    uint64 nRawValues[1];

    DB_Report_Message__GPS_Time__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Time__neoVI_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index = 11;

void DB_Report_Message__WirelessneoVI_Sectors__neoVI_Init(DB_Report_Message__WirelessneoVI_Sectors__neoVI * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->WiviStartSector = dValues[0];
    pMsg->WiviEndSector = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->WiviStartSector_raw = (DWORD)nRawValues[0];
    pMsg->WiviEndSector_raw = (DWORD)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__WirelessneoVI_Sectors__neoVI_LoadSignalValuesArray(DB_Report_Message__WirelessneoVI_Sectors__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->WiviStartSector;
    dArray[1] = pMsg->WiviEndSector;
}

void DB_Report_Message__WirelessneoVI_Sectors__neoVI_LoadRawSignalValuesArray(DB_Report_Message__WirelessneoVI_Sectors__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->WiviStartSector_raw;
    nRawValues[1] = pMsg->WiviEndSector_raw;
}

int DB_Report_Message__WirelessneoVI_Sectors__neoVI_Transmit(DB_Report_Message__WirelessneoVI_Sectors__neoVI * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__WirelessneoVI_Sectors__neoVI_Init(pMsg);
    }

    DB_Report_Message__WirelessneoVI_Sectors__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_Report_Message__WirelessneoVI_Sectors__neoVI_Transmit_raw(DB_Report_Message__WirelessneoVI_Sectors__neoVI * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__WirelessneoVI_Sectors__neoVI_Init(pMsg);
    }

    DB_Report_Message__WirelessneoVI_Sectors__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_Report_Message__WirelessneoVI_Sectors__neoVI_UpdateBytesFromSignals(DB_Report_Message__WirelessneoVI_Sectors__neoVI * pMsg)
{
    double dArray[2];

    DB_Report_Message__WirelessneoVI_Sectors__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Report_Message__WirelessneoVI_Sectors__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__WirelessneoVI_Sectors__neoVI * pMsg)
{
    uint64 nRawValues[2];

    DB_Report_Message__WirelessneoVI_Sectors__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Report_Message__WirelessneoVI_Signals__neoVI_Index = 12;

void DB_Report_Message__WirelessneoVI_Signals__neoVI_Init(DB_Report_Message__WirelessneoVI_Signals__neoVI * pMsg)
{
    double dValues[6] = {0.0};
    uint64 nRawValues[6] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 6, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->WiviJob = dValues[0];
    pMsg->WiviApkResponse = dValues[1];
    pMsg->WiviDataTransferMediumChoice = dValues[2];
    pMsg->WiviApkResponseTo = dValues[3];
    pMsg->WiviReserved0 = dValues[4];
    pMsg->WiviReserved1 = dValues[5];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, nRawValues, 6, &iActualSignalMaxCount);
    pMsg->WiviJob_raw = (BYTE)nRawValues[0];
    pMsg->WiviApkResponse_raw = (BYTE)nRawValues[1];
    pMsg->WiviDataTransferMediumChoice_raw = (BYTE)nRawValues[2];
    pMsg->WiviApkResponseTo_raw = (BYTE)nRawValues[3];
    pMsg->WiviReserved0_raw = (BYTE)nRawValues[4];
    pMsg->WiviReserved1_raw = (BYTE)nRawValues[5];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__WirelessneoVI_Signals__neoVI_LoadSignalValuesArray(DB_Report_Message__WirelessneoVI_Signals__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->WiviJob;
    dArray[1] = pMsg->WiviApkResponse;
    dArray[2] = pMsg->WiviDataTransferMediumChoice;
    dArray[3] = pMsg->WiviApkResponseTo;
    dArray[4] = pMsg->WiviReserved0;
    dArray[5] = pMsg->WiviReserved1;
}

void DB_Report_Message__WirelessneoVI_Signals__neoVI_LoadRawSignalValuesArray(DB_Report_Message__WirelessneoVI_Signals__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->WiviJob_raw;
    nRawValues[1] = pMsg->WiviApkResponse_raw;
    nRawValues[2] = pMsg->WiviDataTransferMediumChoice_raw;
    nRawValues[3] = pMsg->WiviApkResponseTo_raw;
    nRawValues[4] = pMsg->WiviReserved0_raw;
    nRawValues[5] = pMsg->WiviReserved1_raw;
}

int DB_Report_Message__WirelessneoVI_Signals__neoVI_Transmit(DB_Report_Message__WirelessneoVI_Signals__neoVI * pMsg)
{
    double dArray[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__WirelessneoVI_Signals__neoVI_Init(pMsg);
    }

    DB_Report_Message__WirelessneoVI_Signals__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 6);
}

int DB_Report_Message__WirelessneoVI_Signals__neoVI_Transmit_raw(DB_Report_Message__WirelessneoVI_Signals__neoVI * pMsg)
{
    uint64 nRawValues[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__WirelessneoVI_Signals__neoVI_Init(pMsg);
    }

    DB_Report_Message__WirelessneoVI_Signals__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 6);
}

int DB_Report_Message__WirelessneoVI_Signals__neoVI_UpdateBytesFromSignals(DB_Report_Message__WirelessneoVI_Signals__neoVI * pMsg)
{
    double dArray[6];

    DB_Report_Message__WirelessneoVI_Signals__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, dArray, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Report_Message__WirelessneoVI_Signals__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__WirelessneoVI_Signals__neoVI * pMsg)
{
    uint64 nRawValues[6];

    DB_Report_Message__WirelessneoVI_Signals__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, nRawValues, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_Index = 13;

void DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_Init(DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_Transmit(DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 0, DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_Transmit_raw(DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 0, DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}


int DB_neoVI_Logger_Message_Data_Lost_neoVI_Index = 14;

void DB_neoVI_Logger_Message_Data_Lost_neoVI_Init(DB_neoVI_Logger_Message_Data_Lost_neoVI * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_neoVI_Logger_Message_Data_Lost_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int DB_neoVI_Logger_Message_Data_Lost_neoVI_Transmit(DB_neoVI_Logger_Message_Data_Lost_neoVI * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 0, DB_neoVI_Logger_Message_Data_Lost_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int DB_neoVI_Logger_Message_Data_Lost_neoVI_Transmit_raw(DB_neoVI_Logger_Message_Data_Lost_neoVI * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 0, DB_neoVI_Logger_Message_Data_Lost_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}


int DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_Index = 15;

void DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_Init(DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_Transmit(DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 0, DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_Transmit_raw(DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 0, DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}


int DB_neoVI_Logger_woke_up_neoVI_Index = 16;

void DB_neoVI_Logger_woke_up_neoVI_Init(DB_neoVI_Logger_woke_up_neoVI * pMsg)
{
    double dValues[10] = {0.0};
    uint64 nRawValues[10] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_neoVI_Logger_woke_up_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 10, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->SleepFlags = dValues[0];
    pMsg->WakeupFlags = dValues[1];
    pMsg->WakeUpSms = dValues[2];
    pMsg->WakeupSlaveA = dValues[3];
    pMsg->WakeupSlaveB = dValues[4];
    pMsg->WakeupMainVnet = dValues[5];
    pMsg->WakeupUsb = dValues[6];
    pMsg->PowerBoot = dValues[7];
    pMsg->LowVbatSleep = dValues[8];
    pMsg->NoCmSleep = dValues[9];
    CM_MessageRawInit(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, nRawValues, 10, &iActualSignalMaxCount);
    pMsg->SleepFlags_raw = (WORD)nRawValues[0];
    pMsg->WakeupFlags_raw = (WORD)nRawValues[1];
    pMsg->WakeUpSms_raw = (BYTE)nRawValues[2];
    pMsg->WakeupSlaveA_raw = (BYTE)nRawValues[3];
    pMsg->WakeupSlaveB_raw = (BYTE)nRawValues[4];
    pMsg->WakeupMainVnet_raw = (BYTE)nRawValues[5];
    pMsg->WakeupUsb_raw = (BYTE)nRawValues[6];
    pMsg->PowerBoot_raw = (BYTE)nRawValues[7];
    pMsg->LowVbatSleep_raw = (BYTE)nRawValues[8];
    pMsg->NoCmSleep_raw = (BYTE)nRawValues[9];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_neoVI_Logger_woke_up_neoVI_LoadSignalValuesArray(DB_neoVI_Logger_woke_up_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->SleepFlags;
    dArray[1] = pMsg->WakeupFlags;
    dArray[2] = pMsg->WakeUpSms;
    dArray[3] = pMsg->WakeupSlaveA;
    dArray[4] = pMsg->WakeupSlaveB;
    dArray[5] = pMsg->WakeupMainVnet;
    dArray[6] = pMsg->WakeupUsb;
    dArray[7] = pMsg->PowerBoot;
    dArray[8] = pMsg->LowVbatSleep;
    dArray[9] = pMsg->NoCmSleep;
}

void DB_neoVI_Logger_woke_up_neoVI_LoadRawSignalValuesArray(DB_neoVI_Logger_woke_up_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->SleepFlags_raw;
    nRawValues[1] = pMsg->WakeupFlags_raw;
    nRawValues[2] = pMsg->WakeUpSms_raw;
    nRawValues[3] = pMsg->WakeupSlaveA_raw;
    nRawValues[4] = pMsg->WakeupSlaveB_raw;
    nRawValues[5] = pMsg->WakeupMainVnet_raw;
    nRawValues[6] = pMsg->WakeupUsb_raw;
    nRawValues[7] = pMsg->PowerBoot_raw;
    nRawValues[8] = pMsg->LowVbatSleep_raw;
    nRawValues[9] = pMsg->NoCmSleep_raw;
}

int DB_neoVI_Logger_woke_up_neoVI_Transmit(DB_neoVI_Logger_woke_up_neoVI * pMsg)
{
    double dArray[10];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_neoVI_Logger_woke_up_neoVI_Init(pMsg);
    }

    DB_neoVI_Logger_woke_up_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 10);
}

int DB_neoVI_Logger_woke_up_neoVI_Transmit_raw(DB_neoVI_Logger_woke_up_neoVI * pMsg)
{
    uint64 nRawValues[10];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_neoVI_Logger_woke_up_neoVI_Init(pMsg);
    }

    DB_neoVI_Logger_woke_up_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 10);
}

int DB_neoVI_Logger_woke_up_neoVI_UpdateBytesFromSignals(DB_neoVI_Logger_woke_up_neoVI * pMsg)
{
    double dArray[10];

    DB_neoVI_Logger_woke_up_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, dArray, 10, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_neoVI_Logger_woke_up_neoVI_UpdateBytesFromRawSignals(DB_neoVI_Logger_woke_up_neoVI * pMsg)
{
    uint64 nRawValues[10];

    DB_neoVI_Logger_woke_up_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, nRawValues, 10, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Report_Message_1_Analog_Card__neoVI_Index = 17;

void DB_Report_Message_1_Analog_Card__neoVI_Init(DB_Report_Message_1_Analog_Card__neoVI * pMsg)
{
    double dValues[4] = {0.0};
    uint64 nRawValues[4] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message_1_Analog_Card__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 4, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Channel_A = dValues[0];
    pMsg->Channel_B = dValues[1];
    pMsg->Channel_1_Differential_ = dValues[2];
    pMsg->Channel_2_Differential_ = dValues[3];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message_1_Analog_Card__neoVI_Index, nRawValues, 4, &iActualSignalMaxCount);
    pMsg->Channel_A_raw = (WORD)nRawValues[0];
    pMsg->Channel_B_raw = (WORD)nRawValues[1];
    pMsg->Channel_1_Differential__raw = (WORD)nRawValues[2];
    pMsg->Channel_2_Differential__raw = (WORD)nRawValues[3];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message_1_Analog_Card__neoVI_LoadSignalValuesArray(DB_Report_Message_1_Analog_Card__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Channel_A;
    dArray[1] = pMsg->Channel_B;
    dArray[2] = pMsg->Channel_1_Differential_;
    dArray[3] = pMsg->Channel_2_Differential_;
}

void DB_Report_Message_1_Analog_Card__neoVI_LoadRawSignalValuesArray(DB_Report_Message_1_Analog_Card__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Channel_A_raw;
    nRawValues[1] = pMsg->Channel_B_raw;
    nRawValues[2] = pMsg->Channel_1_Differential__raw;
    nRawValues[3] = pMsg->Channel_2_Differential__raw;
}

int DB_Report_Message_1_Analog_Card__neoVI_Transmit(DB_Report_Message_1_Analog_Card__neoVI * pMsg)
{
    double dArray[4];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message_1_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message_1_Analog_Card__neoVI_Init(pMsg);
    }

    DB_Report_Message_1_Analog_Card__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message_1_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 4);
}

int DB_Report_Message_1_Analog_Card__neoVI_Transmit_raw(DB_Report_Message_1_Analog_Card__neoVI * pMsg)
{
    uint64 nRawValues[4];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message_1_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message_1_Analog_Card__neoVI_Init(pMsg);
    }

    DB_Report_Message_1_Analog_Card__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message_1_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 4);
}

int DB_Report_Message_1_Analog_Card__neoVI_UpdateBytesFromSignals(DB_Report_Message_1_Analog_Card__neoVI * pMsg)
{
    double dArray[4];

    DB_Report_Message_1_Analog_Card__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message_1_Analog_Card__neoVI_Index, dArray, 4, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Report_Message_1_Analog_Card__neoVI_UpdateBytesFromRawSignals(DB_Report_Message_1_Analog_Card__neoVI * pMsg)
{
    uint64 nRawValues[4];

    DB_Report_Message_1_Analog_Card__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message_1_Analog_Card__neoVI_Index, nRawValues, 4, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Report_Message_2_Analog_Card__neoVI_Index = 18;

void DB_Report_Message_2_Analog_Card__neoVI_Init(DB_Report_Message_2_Analog_Card__neoVI * pMsg)
{
    double dValues[4] = {0.0};
    uint64 nRawValues[4] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message_2_Analog_Card__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 4, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Channel_3_Differential_ = dValues[0];
    pMsg->Channel_4_Differential_ = dValues[1];
    pMsg->Channel_5_Differential_ = dValues[2];
    pMsg->Channel_6_Differential_ = dValues[3];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message_2_Analog_Card__neoVI_Index, nRawValues, 4, &iActualSignalMaxCount);
    pMsg->Channel_3_Differential__raw = (WORD)nRawValues[0];
    pMsg->Channel_4_Differential__raw = (WORD)nRawValues[1];
    pMsg->Channel_5_Differential__raw = (WORD)nRawValues[2];
    pMsg->Channel_6_Differential__raw = (WORD)nRawValues[3];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message_2_Analog_Card__neoVI_LoadSignalValuesArray(DB_Report_Message_2_Analog_Card__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Channel_3_Differential_;
    dArray[1] = pMsg->Channel_4_Differential_;
    dArray[2] = pMsg->Channel_5_Differential_;
    dArray[3] = pMsg->Channel_6_Differential_;
}

void DB_Report_Message_2_Analog_Card__neoVI_LoadRawSignalValuesArray(DB_Report_Message_2_Analog_Card__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Channel_3_Differential__raw;
    nRawValues[1] = pMsg->Channel_4_Differential__raw;
    nRawValues[2] = pMsg->Channel_5_Differential__raw;
    nRawValues[3] = pMsg->Channel_6_Differential__raw;
}

int DB_Report_Message_2_Analog_Card__neoVI_Transmit(DB_Report_Message_2_Analog_Card__neoVI * pMsg)
{
    double dArray[4];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message_2_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message_2_Analog_Card__neoVI_Init(pMsg);
    }

    DB_Report_Message_2_Analog_Card__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message_2_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 4);
}

int DB_Report_Message_2_Analog_Card__neoVI_Transmit_raw(DB_Report_Message_2_Analog_Card__neoVI * pMsg)
{
    uint64 nRawValues[4];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message_2_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message_2_Analog_Card__neoVI_Init(pMsg);
    }

    DB_Report_Message_2_Analog_Card__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message_2_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 4);
}

int DB_Report_Message_2_Analog_Card__neoVI_UpdateBytesFromSignals(DB_Report_Message_2_Analog_Card__neoVI * pMsg)
{
    double dArray[4];

    DB_Report_Message_2_Analog_Card__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message_2_Analog_Card__neoVI_Index, dArray, 4, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Report_Message_2_Analog_Card__neoVI_UpdateBytesFromRawSignals(DB_Report_Message_2_Analog_Card__neoVI * pMsg)
{
    uint64 nRawValues[4];

    DB_Report_Message_2_Analog_Card__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message_2_Analog_Card__neoVI_Index, nRawValues, 4, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Report_Message_3_Analog_Card__neoVI_Index = 19;

void DB_Report_Message_3_Analog_Card__neoVI_Init(DB_Report_Message_3_Analog_Card__neoVI * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message_3_Analog_Card__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Channel_7_Differential_ = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message_3_Analog_Card__neoVI_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->Channel_7_Differential__raw = (WORD)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message_3_Analog_Card__neoVI_LoadSignalValuesArray(DB_Report_Message_3_Analog_Card__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Channel_7_Differential_;
}

void DB_Report_Message_3_Analog_Card__neoVI_LoadRawSignalValuesArray(DB_Report_Message_3_Analog_Card__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Channel_7_Differential__raw;
}

int DB_Report_Message_3_Analog_Card__neoVI_Transmit(DB_Report_Message_3_Analog_Card__neoVI * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message_3_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message_3_Analog_Card__neoVI_Init(pMsg);
    }

    DB_Report_Message_3_Analog_Card__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message_3_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_Report_Message_3_Analog_Card__neoVI_Transmit_raw(DB_Report_Message_3_Analog_Card__neoVI * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message_3_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message_3_Analog_Card__neoVI_Init(pMsg);
    }

    DB_Report_Message_3_Analog_Card__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message_3_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_Report_Message_3_Analog_Card__neoVI_UpdateBytesFromSignals(DB_Report_Message_3_Analog_Card__neoVI * pMsg)
{
    double dArray[1];

    DB_Report_Message_3_Analog_Card__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message_3_Analog_Card__neoVI_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Report_Message_3_Analog_Card__neoVI_UpdateBytesFromRawSignals(DB_Report_Message_3_Analog_Card__neoVI * pMsg)
{
    uint64 nRawValues[1];

    DB_Report_Message_3_Analog_Card__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message_3_Analog_Card__neoVI_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Report_Message_4_Analog_Card__neoVI_Index = 20;

void DB_Report_Message_4_Analog_Card__neoVI_Init(DB_Report_Message_4_Analog_Card__neoVI * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message_4_Analog_Card__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Timestamp = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message_4_Analog_Card__neoVI_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->Timestamp_raw = (uint64)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message_4_Analog_Card__neoVI_LoadSignalValuesArray(DB_Report_Message_4_Analog_Card__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Timestamp;
}

void DB_Report_Message_4_Analog_Card__neoVI_LoadRawSignalValuesArray(DB_Report_Message_4_Analog_Card__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Timestamp_raw;
}

int DB_Report_Message_4_Analog_Card__neoVI_Transmit(DB_Report_Message_4_Analog_Card__neoVI * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message_4_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message_4_Analog_Card__neoVI_Init(pMsg);
    }

    DB_Report_Message_4_Analog_Card__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message_4_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_Report_Message_4_Analog_Card__neoVI_Transmit_raw(DB_Report_Message_4_Analog_Card__neoVI * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message_4_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message_4_Analog_Card__neoVI_Init(pMsg);
    }

    DB_Report_Message_4_Analog_Card__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message_4_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_Report_Message_4_Analog_Card__neoVI_UpdateBytesFromSignals(DB_Report_Message_4_Analog_Card__neoVI * pMsg)
{
    double dArray[1];

    DB_Report_Message_4_Analog_Card__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message_4_Analog_Card__neoVI_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Report_Message_4_Analog_Card__neoVI_UpdateBytesFromRawSignals(DB_Report_Message_4_Analog_Card__neoVI * pMsg)
{
    uint64 nRawValues[1];

    DB_Report_Message_4_Analog_Card__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message_4_Analog_Card__neoVI_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Time_Resync_neoVI_Index = 21;

void DB_Time_Resync_neoVI_Init(DB_Time_Resync_neoVI * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Time_Resync_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Timestamp = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_Time_Resync_neoVI_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->Timestamp_raw = (uint64)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Time_Resync_neoVI_LoadSignalValuesArray(DB_Time_Resync_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Timestamp;
}

void DB_Time_Resync_neoVI_LoadRawSignalValuesArray(DB_Time_Resync_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Timestamp_raw;
}

int DB_Time_Resync_neoVI_Transmit(DB_Time_Resync_neoVI * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Time_Resync_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Time_Resync_neoVI_Init(pMsg);
    }

    DB_Time_Resync_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Time_Resync_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_Time_Resync_neoVI_Transmit_raw(DB_Time_Resync_neoVI * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Time_Resync_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Time_Resync_neoVI_Init(pMsg);
    }

    DB_Time_Resync_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Time_Resync_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_Time_Resync_neoVI_UpdateBytesFromSignals(DB_Time_Resync_neoVI * pMsg)
{
    double dArray[1];

    DB_Time_Resync_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Time_Resync_neoVI_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Time_Resync_neoVI_UpdateBytesFromRawSignals(DB_Time_Resync_neoVI * pMsg)
{
    uint64 nRawValues[1];

    DB_Time_Resync_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Time_Resync_neoVI_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_VNET_Clock_Edge_neoVI_Index = 22;

void DB_VNET_Clock_Edge_neoVI_Init(DB_VNET_Clock_Edge_neoVI * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_VNET_Clock_Edge_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int DB_VNET_Clock_Edge_neoVI_Transmit(DB_VNET_Clock_Edge_neoVI * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 0, DB_VNET_Clock_Edge_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int DB_VNET_Clock_Edge_neoVI_Transmit_raw(DB_VNET_Clock_Edge_neoVI * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 0, DB_VNET_Clock_Edge_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}


int DB_VNET_A_Stats_neoVI_Index = 23;

void DB_VNET_A_Stats_neoVI_Init(DB_VNET_A_Stats_neoVI * pMsg)
{
    double dValues[5] = {0.0};
    uint64 nRawValues[5] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_VNET_A_Stats_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 5, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->msgTotal = dValues[0];
    pMsg->rxSize = dValues[1];
    pMsg->scCnt = dValues[2];
    pMsg->yields = dValues[3];
    pMsg->bytesRead = dValues[4];
    CM_MessageRawInit(g_uiHandle, 0, DB_VNET_A_Stats_neoVI_Index, nRawValues, 5, &iActualSignalMaxCount);
    pMsg->msgTotal_raw = (WORD)nRawValues[0];
    pMsg->rxSize_raw = (BYTE)nRawValues[1];
    pMsg->scCnt_raw = (BYTE)nRawValues[2];
    pMsg->yields_raw = (WORD)nRawValues[3];
    pMsg->bytesRead_raw = (WORD)nRawValues[4];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_VNET_A_Stats_neoVI_LoadSignalValuesArray(DB_VNET_A_Stats_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->msgTotal;
    dArray[1] = pMsg->rxSize;
    dArray[2] = pMsg->scCnt;
    dArray[3] = pMsg->yields;
    dArray[4] = pMsg->bytesRead;
}

void DB_VNET_A_Stats_neoVI_LoadRawSignalValuesArray(DB_VNET_A_Stats_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->msgTotal_raw;
    nRawValues[1] = pMsg->rxSize_raw;
    nRawValues[2] = pMsg->scCnt_raw;
    nRawValues[3] = pMsg->yields_raw;
    nRawValues[4] = pMsg->bytesRead_raw;
}

int DB_VNET_A_Stats_neoVI_Transmit(DB_VNET_A_Stats_neoVI * pMsg)
{
    double dArray[5];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_VNET_A_Stats_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_VNET_A_Stats_neoVI_Init(pMsg);
    }

    DB_VNET_A_Stats_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_VNET_A_Stats_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 5);
}

int DB_VNET_A_Stats_neoVI_Transmit_raw(DB_VNET_A_Stats_neoVI * pMsg)
{
    uint64 nRawValues[5];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_VNET_A_Stats_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_VNET_A_Stats_neoVI_Init(pMsg);
    }

    DB_VNET_A_Stats_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_VNET_A_Stats_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 5);
}

int DB_VNET_A_Stats_neoVI_UpdateBytesFromSignals(DB_VNET_A_Stats_neoVI * pMsg)
{
    double dArray[5];

    DB_VNET_A_Stats_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_VNET_A_Stats_neoVI_Index, dArray, 5, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_VNET_A_Stats_neoVI_UpdateBytesFromRawSignals(DB_VNET_A_Stats_neoVI * pMsg)
{
    uint64 nRawValues[5];

    DB_VNET_A_Stats_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_VNET_A_Stats_neoVI_Index, nRawValues, 5, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_VNET_A_Reboot_neoVI_Index = 24;

void DB_VNET_A_Reboot_neoVI_Init(DB_VNET_A_Reboot_neoVI * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_VNET_A_Reboot_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int DB_VNET_A_Reboot_neoVI_Transmit(DB_VNET_A_Reboot_neoVI * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 0, DB_VNET_A_Reboot_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int DB_VNET_A_Reboot_neoVI_Transmit_raw(DB_VNET_A_Reboot_neoVI * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 0, DB_VNET_A_Reboot_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}


int DB_neoVI_Went_To_Sleep_neoVI_Index = 25;

void DB_neoVI_Went_To_Sleep_neoVI_Init(DB_neoVI_Went_To_Sleep_neoVI * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_neoVI_Went_To_Sleep_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int DB_neoVI_Went_To_Sleep_neoVI_Transmit(DB_neoVI_Went_To_Sleep_neoVI * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 0, DB_neoVI_Went_To_Sleep_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int DB_neoVI_Went_To_Sleep_neoVI_Transmit_raw(DB_neoVI_Went_To_Sleep_neoVI * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 0, DB_neoVI_Went_To_Sleep_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}


int DB_Device_subsystem_restarted__neoVI_Index = 26;

void DB_Device_subsystem_restarted__neoVI_Init(DB_Device_subsystem_restarted__neoVI * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Device_subsystem_restarted__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int DB_Device_subsystem_restarted__neoVI_Transmit(DB_Device_subsystem_restarted__neoVI * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 0, DB_Device_subsystem_restarted__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int DB_Device_subsystem_restarted__neoVI_Transmit_raw(DB_Device_subsystem_restarted__neoVI * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Device_subsystem_restarted__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}


int DB_Ethernet_DAQ_Report_neoVI_Index = 27;

void DB_Ethernet_DAQ_Report_neoVI_Init(DB_Ethernet_DAQ_Report_neoVI * pMsg)
{
    double dValues[14] = {0.0};
    uint64 nRawValues[14] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Ethernet_DAQ_Report_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 14, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Recording = dValues[0];
    pMsg->FPGA_Alive = dValues[1];
    pMsg->Bad_Chip = dValues[2];
    pMsg->Raw_MAC_Mode = dValues[3];
    pMsg->IPv4_Filter = dValues[4];
    pMsg->RxOverflow = dValues[5];
    pMsg->CmdBusy = dValues[6];
    pMsg->LogTO = dValues[7];
    pMsg->SockActivityTO = dValues[8];
    pMsg->FPGAComTO = dValues[9];
    pMsg->SockConfigTO = dValues[10];
    pMsg->SockDiscon = dValues[11];
    pMsg->WcfSM = dValues[12];
    pMsg->TxMsgsPending = dValues[13];
    CM_MessageRawInit(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, nRawValues, 14, &iActualSignalMaxCount);
    pMsg->Recording_raw = (BYTE)nRawValues[0];
    pMsg->FPGA_Alive_raw = (BYTE)nRawValues[1];
    pMsg->Bad_Chip_raw = (BYTE)nRawValues[2];
    pMsg->Raw_MAC_Mode_raw = (BYTE)nRawValues[3];
    pMsg->IPv4_Filter_raw = (BYTE)nRawValues[4];
    pMsg->RxOverflow_raw = (BYTE)nRawValues[5];
    pMsg->CmdBusy_raw = (BYTE)nRawValues[6];
    pMsg->LogTO_raw = (BYTE)nRawValues[7];
    pMsg->SockActivityTO_raw = (BYTE)nRawValues[8];
    pMsg->FPGAComTO_raw = (BYTE)nRawValues[9];
    pMsg->SockConfigTO_raw = (BYTE)nRawValues[10];
    pMsg->SockDiscon_raw = (BYTE)nRawValues[11];
    pMsg->WcfSM_raw = (BYTE)nRawValues[12];
    pMsg->TxMsgsPending_raw = (BYTE)nRawValues[13];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Ethernet_DAQ_Report_neoVI_LoadSignalValuesArray(DB_Ethernet_DAQ_Report_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Recording;
    dArray[1] = pMsg->FPGA_Alive;
    dArray[2] = pMsg->Bad_Chip;
    dArray[3] = pMsg->Raw_MAC_Mode;
    dArray[4] = pMsg->IPv4_Filter;
    dArray[5] = pMsg->RxOverflow;
    dArray[6] = pMsg->CmdBusy;
    dArray[7] = pMsg->LogTO;
    dArray[8] = pMsg->SockActivityTO;
    dArray[9] = pMsg->FPGAComTO;
    dArray[10] = pMsg->SockConfigTO;
    dArray[11] = pMsg->SockDiscon;
    dArray[12] = pMsg->WcfSM;
    dArray[13] = pMsg->TxMsgsPending;
}

void DB_Ethernet_DAQ_Report_neoVI_LoadRawSignalValuesArray(DB_Ethernet_DAQ_Report_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Recording_raw;
    nRawValues[1] = pMsg->FPGA_Alive_raw;
    nRawValues[2] = pMsg->Bad_Chip_raw;
    nRawValues[3] = pMsg->Raw_MAC_Mode_raw;
    nRawValues[4] = pMsg->IPv4_Filter_raw;
    nRawValues[5] = pMsg->RxOverflow_raw;
    nRawValues[6] = pMsg->CmdBusy_raw;
    nRawValues[7] = pMsg->LogTO_raw;
    nRawValues[8] = pMsg->SockActivityTO_raw;
    nRawValues[9] = pMsg->FPGAComTO_raw;
    nRawValues[10] = pMsg->SockConfigTO_raw;
    nRawValues[11] = pMsg->SockDiscon_raw;
    nRawValues[12] = pMsg->WcfSM_raw;
    nRawValues[13] = pMsg->TxMsgsPending_raw;
}

int DB_Ethernet_DAQ_Report_neoVI_Transmit(DB_Ethernet_DAQ_Report_neoVI * pMsg)
{
    double dArray[14];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Ethernet_DAQ_Report_neoVI_Init(pMsg);
    }

    DB_Ethernet_DAQ_Report_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 14);
}

int DB_Ethernet_DAQ_Report_neoVI_Transmit_raw(DB_Ethernet_DAQ_Report_neoVI * pMsg)
{
    uint64 nRawValues[14];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Ethernet_DAQ_Report_neoVI_Init(pMsg);
    }

    DB_Ethernet_DAQ_Report_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 14);
}

int DB_Ethernet_DAQ_Report_neoVI_UpdateBytesFromSignals(DB_Ethernet_DAQ_Report_neoVI * pMsg)
{
    double dArray[14];

    DB_Ethernet_DAQ_Report_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, dArray, 14, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Ethernet_DAQ_Report_neoVI_UpdateBytesFromRawSignals(DB_Ethernet_DAQ_Report_neoVI * pMsg)
{
    uint64 nRawValues[14];

    DB_Ethernet_DAQ_Report_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, nRawValues, 14, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_neoVI_Status_Update_neoVI_Index = 28;

void DB_neoVI_Status_Update_neoVI_Init(DB_neoVI_Status_Update_neoVI * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_neoVI_Status_Update_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Type = dValues[0];
    pMsg->ChangeCount = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_neoVI_Status_Update_neoVI_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->Type_raw = (BYTE)nRawValues[0];
    pMsg->ChangeCount_raw = (BYTE)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_neoVI_Status_Update_neoVI_LoadSignalValuesArray(DB_neoVI_Status_Update_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Type;
    dArray[1] = pMsg->ChangeCount;
}

void DB_neoVI_Status_Update_neoVI_LoadRawSignalValuesArray(DB_neoVI_Status_Update_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Type_raw;
    nRawValues[1] = pMsg->ChangeCount_raw;
}

int DB_neoVI_Status_Update_neoVI_Transmit(DB_neoVI_Status_Update_neoVI * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_neoVI_Status_Update_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_neoVI_Status_Update_neoVI_Init(pMsg);
    }

    DB_neoVI_Status_Update_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_neoVI_Status_Update_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_neoVI_Status_Update_neoVI_Transmit_raw(DB_neoVI_Status_Update_neoVI * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_neoVI_Status_Update_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_neoVI_Status_Update_neoVI_Init(pMsg);
    }

    DB_neoVI_Status_Update_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_neoVI_Status_Update_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_neoVI_Status_Update_neoVI_UpdateBytesFromSignals(DB_neoVI_Status_Update_neoVI * pMsg)
{
    double dArray[2];

    DB_neoVI_Status_Update_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_neoVI_Status_Update_neoVI_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_neoVI_Status_Update_neoVI_UpdateBytesFromRawSignals(DB_neoVI_Status_Update_neoVI * pMsg)
{
    uint64 nRawValues[2];

    DB_neoVI_Status_Update_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_neoVI_Status_Update_neoVI_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Scc_Status_neoVI_Index = 29;

void DB_Scc_Status_neoVI_Init(DB_Scc_Status_neoVI * pMsg)
{
    double dValues[6] = {0.0};
    uint64 nRawValues[6] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Scc_Status_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 6, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->FvA = dValues[0];
    pMsg->ScA = dValues[1];
    pMsg->Atv = dValues[2];
    pMsg->sip = dValues[3];
    pMsg->pt = dValues[4];
    pMsg->Req = dValues[5];
    CM_MessageRawInit(g_uiHandle, 0, DB_Scc_Status_neoVI_Index, nRawValues, 6, &iActualSignalMaxCount);
    pMsg->FvA_raw = (BYTE)nRawValues[0];
    pMsg->ScA_raw = (BYTE)nRawValues[1];
    pMsg->Atv_raw = (BYTE)nRawValues[2];
    pMsg->sip_raw = (BYTE)nRawValues[3];
    pMsg->pt_raw = (DWORD)nRawValues[4];
    pMsg->Req_raw = (BYTE)nRawValues[5];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Scc_Status_neoVI_LoadSignalValuesArray(DB_Scc_Status_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->FvA;
    dArray[1] = pMsg->ScA;
    dArray[2] = pMsg->Atv;
    dArray[3] = pMsg->sip;
    dArray[4] = pMsg->pt;
    dArray[5] = pMsg->Req;
}

void DB_Scc_Status_neoVI_LoadRawSignalValuesArray(DB_Scc_Status_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->FvA_raw;
    nRawValues[1] = pMsg->ScA_raw;
    nRawValues[2] = pMsg->Atv_raw;
    nRawValues[3] = pMsg->sip_raw;
    nRawValues[4] = pMsg->pt_raw;
    nRawValues[5] = pMsg->Req_raw;
}

int DB_Scc_Status_neoVI_Transmit(DB_Scc_Status_neoVI * pMsg)
{
    double dArray[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Scc_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Scc_Status_neoVI_Init(pMsg);
    }

    DB_Scc_Status_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Scc_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 6);
}

int DB_Scc_Status_neoVI_Transmit_raw(DB_Scc_Status_neoVI * pMsg)
{
    uint64 nRawValues[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Scc_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Scc_Status_neoVI_Init(pMsg);
    }

    DB_Scc_Status_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Scc_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 6);
}

int DB_Scc_Status_neoVI_UpdateBytesFromSignals(DB_Scc_Status_neoVI * pMsg)
{
    double dArray[6];

    DB_Scc_Status_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Scc_Status_neoVI_Index, dArray, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Scc_Status_neoVI_UpdateBytesFromRawSignals(DB_Scc_Status_neoVI * pMsg)
{
    uint64 nRawValues[6];

    DB_Scc_Status_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Scc_Status_neoVI_Index, nRawValues, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index = 30;

void DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Init(DB_Report_Message__Analog_Card_PWM_Inputs__neoVI * pMsg)
{
    double dValues[8] = {0.0};
    uint64 nRawValues[8] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 8, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->PWM1_IN = dValues[0];
    pMsg->PWM2_IN = dValues[1];
    pMsg->PWM3_IN = dValues[2];
    pMsg->PWM4_IN = dValues[3];
    pMsg->PWM5_IN = dValues[4];
    pMsg->PWM6_IN = dValues[5];
    pMsg->PWM7_IN = dValues[6];
    pMsg->PWM8_IN = dValues[7];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, nRawValues, 8, &iActualSignalMaxCount);
    pMsg->PWM1_IN_raw = (BYTE)nRawValues[0];
    pMsg->PWM2_IN_raw = (BYTE)nRawValues[1];
    pMsg->PWM3_IN_raw = (BYTE)nRawValues[2];
    pMsg->PWM4_IN_raw = (BYTE)nRawValues[3];
    pMsg->PWM5_IN_raw = (BYTE)nRawValues[4];
    pMsg->PWM6_IN_raw = (BYTE)nRawValues[5];
    pMsg->PWM7_IN_raw = (BYTE)nRawValues[6];
    pMsg->PWM8_IN_raw = (BYTE)nRawValues[7];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_LoadSignalValuesArray(DB_Report_Message__Analog_Card_PWM_Inputs__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->PWM1_IN;
    dArray[1] = pMsg->PWM2_IN;
    dArray[2] = pMsg->PWM3_IN;
    dArray[3] = pMsg->PWM4_IN;
    dArray[4] = pMsg->PWM5_IN;
    dArray[5] = pMsg->PWM6_IN;
    dArray[6] = pMsg->PWM7_IN;
    dArray[7] = pMsg->PWM8_IN;
}

void DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_LoadRawSignalValuesArray(DB_Report_Message__Analog_Card_PWM_Inputs__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->PWM1_IN_raw;
    nRawValues[1] = pMsg->PWM2_IN_raw;
    nRawValues[2] = pMsg->PWM3_IN_raw;
    nRawValues[3] = pMsg->PWM4_IN_raw;
    nRawValues[4] = pMsg->PWM5_IN_raw;
    nRawValues[5] = pMsg->PWM6_IN_raw;
    nRawValues[6] = pMsg->PWM7_IN_raw;
    nRawValues[7] = pMsg->PWM8_IN_raw;
}

int DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM_Inputs__neoVI * pMsg)
{
    double dArray[8];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 8);
}

int DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM_Inputs__neoVI * pMsg)
{
    uint64 nRawValues[8];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 8);
}

int DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM_Inputs__neoVI * pMsg)
{
    double dArray[8];

    DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, dArray, 8, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM_Inputs__neoVI * pMsg)
{
    uint64 nRawValues[8];

    DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, nRawValues, 8, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Report_Message__Analog_Card_PWM1__neoVI_Index = 31;

void DB_Report_Message__Analog_Card_PWM1__neoVI_Init(DB_Report_Message__Analog_Card_PWM1__neoVI * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__Analog_Card_PWM1__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Pulse_Width_ms_ = dValues[0];
    pMsg->Period_ms_ = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM1__neoVI_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->Pulse_Width_ms__raw = (DWORD)nRawValues[0];
    pMsg->Period_ms__raw = (DWORD)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__Analog_Card_PWM1__neoVI_LoadSignalValuesArray(DB_Report_Message__Analog_Card_PWM1__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Pulse_Width_ms_;
    dArray[1] = pMsg->Period_ms_;
}

void DB_Report_Message__Analog_Card_PWM1__neoVI_LoadRawSignalValuesArray(DB_Report_Message__Analog_Card_PWM1__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Pulse_Width_ms__raw;
    nRawValues[1] = pMsg->Period_ms__raw;
}

int DB_Report_Message__Analog_Card_PWM1__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM1__neoVI * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM1__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM1__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM1__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM1__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_Report_Message__Analog_Card_PWM1__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM1__neoVI * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM1__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM1__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM1__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM1__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_Report_Message__Analog_Card_PWM1__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM1__neoVI * pMsg)
{
    double dArray[2];

    DB_Report_Message__Analog_Card_PWM1__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM1__neoVI_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Report_Message__Analog_Card_PWM1__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM1__neoVI * pMsg)
{
    uint64 nRawValues[2];

    DB_Report_Message__Analog_Card_PWM1__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM1__neoVI_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Report_Message__Analog_Card_PWM2__neoVI_Index = 32;

void DB_Report_Message__Analog_Card_PWM2__neoVI_Init(DB_Report_Message__Analog_Card_PWM2__neoVI * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__Analog_Card_PWM2__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Pulse_Width_ms_ = dValues[0];
    pMsg->Period_ms_ = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM2__neoVI_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->Pulse_Width_ms__raw = (DWORD)nRawValues[0];
    pMsg->Period_ms__raw = (DWORD)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__Analog_Card_PWM2__neoVI_LoadSignalValuesArray(DB_Report_Message__Analog_Card_PWM2__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Pulse_Width_ms_;
    dArray[1] = pMsg->Period_ms_;
}

void DB_Report_Message__Analog_Card_PWM2__neoVI_LoadRawSignalValuesArray(DB_Report_Message__Analog_Card_PWM2__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Pulse_Width_ms__raw;
    nRawValues[1] = pMsg->Period_ms__raw;
}

int DB_Report_Message__Analog_Card_PWM2__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM2__neoVI * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM2__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM2__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM2__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM2__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_Report_Message__Analog_Card_PWM2__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM2__neoVI * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM2__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM2__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM2__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM2__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_Report_Message__Analog_Card_PWM2__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM2__neoVI * pMsg)
{
    double dArray[2];

    DB_Report_Message__Analog_Card_PWM2__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM2__neoVI_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Report_Message__Analog_Card_PWM2__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM2__neoVI * pMsg)
{
    uint64 nRawValues[2];

    DB_Report_Message__Analog_Card_PWM2__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM2__neoVI_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Report_Message__Analog_Card_PWM3__neoVI_Index = 33;

void DB_Report_Message__Analog_Card_PWM3__neoVI_Init(DB_Report_Message__Analog_Card_PWM3__neoVI * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__Analog_Card_PWM3__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Pulse_Width_ms_ = dValues[0];
    pMsg->Period_ms_ = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM3__neoVI_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->Pulse_Width_ms__raw = (DWORD)nRawValues[0];
    pMsg->Period_ms__raw = (DWORD)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__Analog_Card_PWM3__neoVI_LoadSignalValuesArray(DB_Report_Message__Analog_Card_PWM3__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Pulse_Width_ms_;
    dArray[1] = pMsg->Period_ms_;
}

void DB_Report_Message__Analog_Card_PWM3__neoVI_LoadRawSignalValuesArray(DB_Report_Message__Analog_Card_PWM3__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Pulse_Width_ms__raw;
    nRawValues[1] = pMsg->Period_ms__raw;
}

int DB_Report_Message__Analog_Card_PWM3__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM3__neoVI * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM3__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM3__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM3__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM3__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_Report_Message__Analog_Card_PWM3__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM3__neoVI * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM3__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM3__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM3__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM3__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_Report_Message__Analog_Card_PWM3__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM3__neoVI * pMsg)
{
    double dArray[2];

    DB_Report_Message__Analog_Card_PWM3__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM3__neoVI_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Report_Message__Analog_Card_PWM3__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM3__neoVI * pMsg)
{
    uint64 nRawValues[2];

    DB_Report_Message__Analog_Card_PWM3__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM3__neoVI_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Report_Message__Analog_Card_PWM4__neoVI_Index = 34;

void DB_Report_Message__Analog_Card_PWM4__neoVI_Init(DB_Report_Message__Analog_Card_PWM4__neoVI * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__Analog_Card_PWM4__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Pulse_Width_ms_ = dValues[0];
    pMsg->Period_ms_ = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM4__neoVI_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->Pulse_Width_ms__raw = (DWORD)nRawValues[0];
    pMsg->Period_ms__raw = (DWORD)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__Analog_Card_PWM4__neoVI_LoadSignalValuesArray(DB_Report_Message__Analog_Card_PWM4__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Pulse_Width_ms_;
    dArray[1] = pMsg->Period_ms_;
}

void DB_Report_Message__Analog_Card_PWM4__neoVI_LoadRawSignalValuesArray(DB_Report_Message__Analog_Card_PWM4__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Pulse_Width_ms__raw;
    nRawValues[1] = pMsg->Period_ms__raw;
}

int DB_Report_Message__Analog_Card_PWM4__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM4__neoVI * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM4__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM4__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM4__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM4__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_Report_Message__Analog_Card_PWM4__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM4__neoVI * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM4__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM4__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM4__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM4__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_Report_Message__Analog_Card_PWM4__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM4__neoVI * pMsg)
{
    double dArray[2];

    DB_Report_Message__Analog_Card_PWM4__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM4__neoVI_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Report_Message__Analog_Card_PWM4__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM4__neoVI * pMsg)
{
    uint64 nRawValues[2];

    DB_Report_Message__Analog_Card_PWM4__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM4__neoVI_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Report_Message__Analog_Card_PWM5__neoVI_Index = 35;

void DB_Report_Message__Analog_Card_PWM5__neoVI_Init(DB_Report_Message__Analog_Card_PWM5__neoVI * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__Analog_Card_PWM5__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Pulse_Width_ms_ = dValues[0];
    pMsg->Period_ms_ = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM5__neoVI_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->Pulse_Width_ms__raw = (DWORD)nRawValues[0];
    pMsg->Period_ms__raw = (DWORD)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__Analog_Card_PWM5__neoVI_LoadSignalValuesArray(DB_Report_Message__Analog_Card_PWM5__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Pulse_Width_ms_;
    dArray[1] = pMsg->Period_ms_;
}

void DB_Report_Message__Analog_Card_PWM5__neoVI_LoadRawSignalValuesArray(DB_Report_Message__Analog_Card_PWM5__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Pulse_Width_ms__raw;
    nRawValues[1] = pMsg->Period_ms__raw;
}

int DB_Report_Message__Analog_Card_PWM5__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM5__neoVI * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM5__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM5__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM5__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM5__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_Report_Message__Analog_Card_PWM5__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM5__neoVI * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM5__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM5__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM5__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM5__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_Report_Message__Analog_Card_PWM5__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM5__neoVI * pMsg)
{
    double dArray[2];

    DB_Report_Message__Analog_Card_PWM5__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM5__neoVI_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Report_Message__Analog_Card_PWM5__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM5__neoVI * pMsg)
{
    uint64 nRawValues[2];

    DB_Report_Message__Analog_Card_PWM5__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM5__neoVI_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Report_Message__Analog_Card_PWM6__neoVI_Index = 36;

void DB_Report_Message__Analog_Card_PWM6__neoVI_Init(DB_Report_Message__Analog_Card_PWM6__neoVI * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__Analog_Card_PWM6__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Pulse_Width_ms_ = dValues[0];
    pMsg->Period_ms_ = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM6__neoVI_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->Pulse_Width_ms__raw = (DWORD)nRawValues[0];
    pMsg->Period_ms__raw = (DWORD)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__Analog_Card_PWM6__neoVI_LoadSignalValuesArray(DB_Report_Message__Analog_Card_PWM6__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Pulse_Width_ms_;
    dArray[1] = pMsg->Period_ms_;
}

void DB_Report_Message__Analog_Card_PWM6__neoVI_LoadRawSignalValuesArray(DB_Report_Message__Analog_Card_PWM6__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Pulse_Width_ms__raw;
    nRawValues[1] = pMsg->Period_ms__raw;
}

int DB_Report_Message__Analog_Card_PWM6__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM6__neoVI * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM6__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM6__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM6__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM6__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_Report_Message__Analog_Card_PWM6__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM6__neoVI * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM6__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM6__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM6__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM6__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_Report_Message__Analog_Card_PWM6__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM6__neoVI * pMsg)
{
    double dArray[2];

    DB_Report_Message__Analog_Card_PWM6__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM6__neoVI_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Report_Message__Analog_Card_PWM6__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM6__neoVI * pMsg)
{
    uint64 nRawValues[2];

    DB_Report_Message__Analog_Card_PWM6__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM6__neoVI_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Report_Message__Analog_Card_PWM7__neoVI_Index = 37;

void DB_Report_Message__Analog_Card_PWM7__neoVI_Init(DB_Report_Message__Analog_Card_PWM7__neoVI * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__Analog_Card_PWM7__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Pulse_Width_ms_ = dValues[0];
    pMsg->Period_ms_ = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM7__neoVI_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->Pulse_Width_ms__raw = (DWORD)nRawValues[0];
    pMsg->Period_ms__raw = (DWORD)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__Analog_Card_PWM7__neoVI_LoadSignalValuesArray(DB_Report_Message__Analog_Card_PWM7__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Pulse_Width_ms_;
    dArray[1] = pMsg->Period_ms_;
}

void DB_Report_Message__Analog_Card_PWM7__neoVI_LoadRawSignalValuesArray(DB_Report_Message__Analog_Card_PWM7__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Pulse_Width_ms__raw;
    nRawValues[1] = pMsg->Period_ms__raw;
}

int DB_Report_Message__Analog_Card_PWM7__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM7__neoVI * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM7__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM7__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM7__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM7__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_Report_Message__Analog_Card_PWM7__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM7__neoVI * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM7__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM7__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM7__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM7__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_Report_Message__Analog_Card_PWM7__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM7__neoVI * pMsg)
{
    double dArray[2];

    DB_Report_Message__Analog_Card_PWM7__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM7__neoVI_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Report_Message__Analog_Card_PWM7__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM7__neoVI * pMsg)
{
    uint64 nRawValues[2];

    DB_Report_Message__Analog_Card_PWM7__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM7__neoVI_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Report_Message__Analog_Card_PWM8__neoVI_Index = 38;

void DB_Report_Message__Analog_Card_PWM8__neoVI_Init(DB_Report_Message__Analog_Card_PWM8__neoVI * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__Analog_Card_PWM8__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Pulse_Width_ms_ = dValues[0];
    pMsg->Period_ms_ = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM8__neoVI_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->Pulse_Width_ms__raw = (DWORD)nRawValues[0];
    pMsg->Period_ms__raw = (DWORD)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__Analog_Card_PWM8__neoVI_LoadSignalValuesArray(DB_Report_Message__Analog_Card_PWM8__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Pulse_Width_ms_;
    dArray[1] = pMsg->Period_ms_;
}

void DB_Report_Message__Analog_Card_PWM8__neoVI_LoadRawSignalValuesArray(DB_Report_Message__Analog_Card_PWM8__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Pulse_Width_ms__raw;
    nRawValues[1] = pMsg->Period_ms__raw;
}

int DB_Report_Message__Analog_Card_PWM8__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM8__neoVI * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM8__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM8__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM8__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM8__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_Report_Message__Analog_Card_PWM8__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM8__neoVI * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM8__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM8__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM8__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM8__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_Report_Message__Analog_Card_PWM8__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM8__neoVI * pMsg)
{
    double dArray[2];

    DB_Report_Message__Analog_Card_PWM8__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM8__neoVI_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Report_Message__Analog_Card_PWM8__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM8__neoVI * pMsg)
{
    uint64 nRawValues[2];

    DB_Report_Message__Analog_Card_PWM8__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM8__neoVI_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_neoVI_Device_Status_neoVI_Index = 39;

void DB_neoVI_Device_Status_neoVI_Init(DB_neoVI_Device_Status_neoVI * pMsg)
{
    double dValues[4] = {0.0};
    uint64 nRawValues[4] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_neoVI_Device_Status_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 4, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->HID_Temperature__C_ = dValues[0];
    pMsg->HID_Bus_Voltage__V_ = dValues[1];
    pMsg->VNET_Temperature__C_ = dValues[2];
    pMsg->VNET_Bus_Voltage__V_ = dValues[3];
    CM_MessageRawInit(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_Index, nRawValues, 4, &iActualSignalMaxCount);
    pMsg->HID_Temperature__C__raw = (WORD)nRawValues[0];
    pMsg->HID_Bus_Voltage__V__raw = (WORD)nRawValues[1];
    pMsg->VNET_Temperature__C__raw = (WORD)nRawValues[2];
    pMsg->VNET_Bus_Voltage__V__raw = (WORD)nRawValues[3];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_neoVI_Device_Status_neoVI_LoadSignalValuesArray(DB_neoVI_Device_Status_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->HID_Temperature__C_;
    dArray[1] = pMsg->HID_Bus_Voltage__V_;
    dArray[2] = pMsg->VNET_Temperature__C_;
    dArray[3] = pMsg->VNET_Bus_Voltage__V_;
}

void DB_neoVI_Device_Status_neoVI_LoadRawSignalValuesArray(DB_neoVI_Device_Status_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->HID_Temperature__C__raw;
    nRawValues[1] = pMsg->HID_Bus_Voltage__V__raw;
    nRawValues[2] = pMsg->VNET_Temperature__C__raw;
    nRawValues[3] = pMsg->VNET_Bus_Voltage__V__raw;
}

int DB_neoVI_Device_Status_neoVI_Transmit(DB_neoVI_Device_Status_neoVI * pMsg)
{
    double dArray[4];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_neoVI_Device_Status_neoVI_Init(pMsg);
    }

    DB_neoVI_Device_Status_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 4);
}

int DB_neoVI_Device_Status_neoVI_Transmit_raw(DB_neoVI_Device_Status_neoVI * pMsg)
{
    uint64 nRawValues[4];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_neoVI_Device_Status_neoVI_Init(pMsg);
    }

    DB_neoVI_Device_Status_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 4);
}

int DB_neoVI_Device_Status_neoVI_UpdateBytesFromSignals(DB_neoVI_Device_Status_neoVI * pMsg)
{
    double dArray[4];

    DB_neoVI_Device_Status_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_Index, dArray, 4, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_neoVI_Device_Status_neoVI_UpdateBytesFromRawSignals(DB_neoVI_Device_Status_neoVI * pMsg)
{
    uint64 nRawValues[4];

    DB_neoVI_Device_Status_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_Index, nRawValues, 4, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_neoVI_Device_Status_2_neoVI_Index = 40;

void DB_neoVI_Device_Status_2_neoVI_Init(DB_neoVI_Device_Status_2_neoVI * pMsg)
{
    double dValues[3] = {0.0};
    uint64 nRawValues[3] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_neoVI_Device_Status_2_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 3, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Disk_Space_Avail__WiVI__KB = dValues[0];
    pMsg->Power_Supply_Voltage = dValues[1];
    pMsg->Temperature__C_ = dValues[2];
    CM_MessageRawInit(g_uiHandle, 0, DB_neoVI_Device_Status_2_neoVI_Index, nRawValues, 3, &iActualSignalMaxCount);
    pMsg->Disk_Space_Avail__WiVI__KB_raw = (DWORD)nRawValues[0];
    pMsg->Power_Supply_Voltage_raw = (WORD)nRawValues[1];
    pMsg->Temperature__C__raw = (WORD)nRawValues[2];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_neoVI_Device_Status_2_neoVI_LoadSignalValuesArray(DB_neoVI_Device_Status_2_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Disk_Space_Avail__WiVI__KB;
    dArray[1] = pMsg->Power_Supply_Voltage;
    dArray[2] = pMsg->Temperature__C_;
}

void DB_neoVI_Device_Status_2_neoVI_LoadRawSignalValuesArray(DB_neoVI_Device_Status_2_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Disk_Space_Avail__WiVI__KB_raw;
    nRawValues[1] = pMsg->Power_Supply_Voltage_raw;
    nRawValues[2] = pMsg->Temperature__C__raw;
}

int DB_neoVI_Device_Status_2_neoVI_Transmit(DB_neoVI_Device_Status_2_neoVI * pMsg)
{
    double dArray[3];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_neoVI_Device_Status_2_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_neoVI_Device_Status_2_neoVI_Init(pMsg);
    }

    DB_neoVI_Device_Status_2_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_neoVI_Device_Status_2_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 3);
}

int DB_neoVI_Device_Status_2_neoVI_Transmit_raw(DB_neoVI_Device_Status_2_neoVI * pMsg)
{
    uint64 nRawValues[3];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_neoVI_Device_Status_2_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_neoVI_Device_Status_2_neoVI_Init(pMsg);
    }

    DB_neoVI_Device_Status_2_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_neoVI_Device_Status_2_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 3);
}

int DB_neoVI_Device_Status_2_neoVI_UpdateBytesFromSignals(DB_neoVI_Device_Status_2_neoVI * pMsg)
{
    double dArray[3];

    DB_neoVI_Device_Status_2_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_neoVI_Device_Status_2_neoVI_Index, dArray, 3, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_neoVI_Device_Status_2_neoVI_UpdateBytesFromRawSignals(DB_neoVI_Device_Status_2_neoVI * pMsg)
{
    uint64 nRawValues[3];

    DB_neoVI_Device_Status_2_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_neoVI_Device_Status_2_neoVI_Index, nRawValues, 3, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Trace_Logger_Status_neoVI_Index = 41;

void DB_Trace_Logger_Status_neoVI_Init(DB_Trace_Logger_Status_neoVI * pMsg)
{
    double dValues[7] = {0.0};
    uint64 nRawValues[7] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Trace_Logger_Status_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 7, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->State = dValues[0];
    pMsg->Debug_Level = dValues[1];
    pMsg->IP_MSB_ = dValues[2];
    pMsg->IP = dValues[3];
    pMsg->IP_sig4 = dValues[4];
    pMsg->IP_LSB_ = dValues[5];
    pMsg->Port = dValues[6];
    CM_MessageRawInit(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, nRawValues, 7, &iActualSignalMaxCount);
    pMsg->State_raw = (BYTE)nRawValues[0];
    pMsg->Debug_Level_raw = (BYTE)nRawValues[1];
    pMsg->IP_MSB__raw = (BYTE)nRawValues[2];
    pMsg->IP_raw = (BYTE)nRawValues[3];
    pMsg->IP_sig4_raw = (BYTE)nRawValues[4];
    pMsg->IP_LSB__raw = (BYTE)nRawValues[5];
    pMsg->Port_raw = (WORD)nRawValues[6];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Trace_Logger_Status_neoVI_LoadSignalValuesArray(DB_Trace_Logger_Status_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->State;
    dArray[1] = pMsg->Debug_Level;
    dArray[2] = pMsg->IP_MSB_;
    dArray[3] = pMsg->IP;
    dArray[4] = pMsg->IP_sig4;
    dArray[5] = pMsg->IP_LSB_;
    dArray[6] = pMsg->Port;
}

void DB_Trace_Logger_Status_neoVI_LoadRawSignalValuesArray(DB_Trace_Logger_Status_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->State_raw;
    nRawValues[1] = pMsg->Debug_Level_raw;
    nRawValues[2] = pMsg->IP_MSB__raw;
    nRawValues[3] = pMsg->IP_raw;
    nRawValues[4] = pMsg->IP_sig4_raw;
    nRawValues[5] = pMsg->IP_LSB__raw;
    nRawValues[6] = pMsg->Port_raw;
}

int DB_Trace_Logger_Status_neoVI_Transmit(DB_Trace_Logger_Status_neoVI * pMsg)
{
    double dArray[7];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Trace_Logger_Status_neoVI_Init(pMsg);
    }

    DB_Trace_Logger_Status_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 7);
}

int DB_Trace_Logger_Status_neoVI_Transmit_raw(DB_Trace_Logger_Status_neoVI * pMsg)
{
    uint64 nRawValues[7];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Trace_Logger_Status_neoVI_Init(pMsg);
    }

    DB_Trace_Logger_Status_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 7);
}

int DB_Trace_Logger_Status_neoVI_UpdateBytesFromSignals(DB_Trace_Logger_Status_neoVI * pMsg)
{
    double dArray[7];

    DB_Trace_Logger_Status_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, dArray, 7, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Trace_Logger_Status_neoVI_UpdateBytesFromRawSignals(DB_Trace_Logger_Status_neoVI * pMsg)
{
    uint64 nRawValues[7];

    DB_Trace_Logger_Status_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, nRawValues, 7, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Trigger_neoVI_Index = 42;

void DB_Trigger_neoVI_Init(DB_Trigger_neoVI * pMsg)
{
    double dValues[3] = {0.0};
    uint64 nRawValues[3] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Trigger_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 3, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Logger_triggered = dValues[0];
    pMsg->Pre_trigger_size = dValues[1];
    pMsg->Collection_index = dValues[2];
    CM_MessageRawInit(g_uiHandle, 0, DB_Trigger_neoVI_Index, nRawValues, 3, &iActualSignalMaxCount);
    pMsg->Logger_triggered_raw = (BYTE)nRawValues[0];
    pMsg->Pre_trigger_size_raw = (DWORD)nRawValues[1];
    pMsg->Collection_index_raw = (BYTE)nRawValues[2];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Trigger_neoVI_LoadSignalValuesArray(DB_Trigger_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Logger_triggered;
    dArray[1] = pMsg->Pre_trigger_size;
    dArray[2] = pMsg->Collection_index;
}

void DB_Trigger_neoVI_LoadRawSignalValuesArray(DB_Trigger_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Logger_triggered_raw;
    nRawValues[1] = pMsg->Pre_trigger_size_raw;
    nRawValues[2] = pMsg->Collection_index_raw;
}

int DB_Trigger_neoVI_Transmit(DB_Trigger_neoVI * pMsg)
{
    double dArray[3];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Trigger_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Trigger_neoVI_Init(pMsg);
    }

    DB_Trigger_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Trigger_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 3);
}

int DB_Trigger_neoVI_Transmit_raw(DB_Trigger_neoVI * pMsg)
{
    uint64 nRawValues[3];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Trigger_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Trigger_neoVI_Init(pMsg);
    }

    DB_Trigger_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Trigger_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 3);
}

int DB_Trigger_neoVI_UpdateBytesFromSignals(DB_Trigger_neoVI * pMsg)
{
    double dArray[3];

    DB_Trigger_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Trigger_neoVI_Index, dArray, 3, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Trigger_neoVI_UpdateBytesFromRawSignals(DB_Trigger_neoVI * pMsg)
{
    uint64 nRawValues[3];

    DB_Trigger_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Trigger_neoVI_Index, nRawValues, 3, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Exterior_Lighting_HS_CAN_Index = 43;

void DB_Exterior_Lighting_HS_CAN_Init(DB_Exterior_Lighting_HS_CAN * pMsg)
{
    double dValues[32] = {0.0};
    uint64 nRawValues[32] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Exterior_Lighting_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 32, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->AdvFrntLghtSysEnbld = dValues[0];
    pMsg->AutLghtCtrl = dValues[1];
    pMsg->AutoBmSlctAllwd = dValues[2];
    pMsg->AutoLtsActIO = dValues[3];
    pMsg->AutoLtsInactIO = dValues[4];
    pMsg->BrkLtsAtv = dValues[5];
    pMsg->DRLAct = dValues[6];
    pMsg->DispNtSchmAtv = dValues[7];
    pMsg->FlToPsSwAtv = dValues[8];
    pMsg->FrFogLmpsAct = dValues[9];
    pMsg->FrFgLtIO = dValues[10];
    pMsg->HazSwAtv = dValues[11];
    pMsg->HdlmpBmSelectStat = dValues[12];
    pMsg->HighBmAct = dValues[13];
    pMsg->HiBmIO = dValues[14];
    pMsg->HiBmReqd = dValues[15];
    pMsg->IntDimDspLvl = dValues[16];
    pMsg->IntDimLvl = dValues[17];
    pMsg->IntDimNtPnlAtv = dValues[18];
    pMsg->LftTrnLmpAtv = dValues[19];
    pMsg->LowBmAct = dValues[20];
    pMsg->MainLghtSw = dValues[21];
    pMsg->OtsdAmbtLtLvlStat = dValues[22];
    pMsg->OtsdAmbtLtLvlStatV = dValues[23];
    pMsg->PrkLtIO = dValues[24];
    pMsg->PrkLtLeftIO = dValues[25];
    pMsg->PrkLtRightIO = dValues[26];
    pMsg->RrFogLmpsAct = dValues[27];
    pMsg->RrFgLtIO = dValues[28];
    pMsg->RevLmpAtv = dValues[29];
    pMsg->RtTrnLmpAtv = dValues[30];
    pMsg->TrnSwAct = dValues[31];
    CM_MessageRawInit(g_uiHandle, 0, DB_Exterior_Lighting_HS_CAN_Index, nRawValues, 32, &iActualSignalMaxCount);
    pMsg->AdvFrntLghtSysEnbld_raw = (BYTE)nRawValues[0];
    pMsg->AutLghtCtrl_raw = (BYTE)nRawValues[1];
    pMsg->AutoBmSlctAllwd_raw = (BYTE)nRawValues[2];
    pMsg->AutoLtsActIO_raw = (BYTE)nRawValues[3];
    pMsg->AutoLtsInactIO_raw = (BYTE)nRawValues[4];
    pMsg->BrkLtsAtv_raw = (BYTE)nRawValues[5];
    pMsg->DRLAct_raw = (BYTE)nRawValues[6];
    pMsg->DispNtSchmAtv_raw = (BYTE)nRawValues[7];
    pMsg->FlToPsSwAtv_raw = (BYTE)nRawValues[8];
    pMsg->FrFogLmpsAct_raw = (BYTE)nRawValues[9];
    pMsg->FrFgLtIO_raw = (BYTE)nRawValues[10];
    pMsg->HazSwAtv_raw = (BYTE)nRawValues[11];
    pMsg->HdlmpBmSelectStat_raw = (BYTE)nRawValues[12];
    pMsg->HighBmAct_raw = (BYTE)nRawValues[13];
    pMsg->HiBmIO_raw = (BYTE)nRawValues[14];
    pMsg->HiBmReqd_raw = (BYTE)nRawValues[15];
    pMsg->IntDimDspLvl_raw = (BYTE)nRawValues[16];
    pMsg->IntDimLvl_raw = (BYTE)nRawValues[17];
    pMsg->IntDimNtPnlAtv_raw = (BYTE)nRawValues[18];
    pMsg->LftTrnLmpAtv_raw = (BYTE)nRawValues[19];
    pMsg->LowBmAct_raw = (BYTE)nRawValues[20];
    pMsg->MainLghtSw_raw = (BYTE)nRawValues[21];
    pMsg->OtsdAmbtLtLvlStat_raw = (BYTE)nRawValues[22];
    pMsg->OtsdAmbtLtLvlStatV_raw = (BYTE)nRawValues[23];
    pMsg->PrkLtIO_raw = (BYTE)nRawValues[24];
    pMsg->PrkLtLeftIO_raw = (BYTE)nRawValues[25];
    pMsg->PrkLtRightIO_raw = (BYTE)nRawValues[26];
    pMsg->RrFogLmpsAct_raw = (BYTE)nRawValues[27];
    pMsg->RrFgLtIO_raw = (BYTE)nRawValues[28];
    pMsg->RevLmpAtv_raw = (BYTE)nRawValues[29];
    pMsg->RtTrnLmpAtv_raw = (BYTE)nRawValues[30];
    pMsg->TrnSwAct_raw = (BYTE)nRawValues[31];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Exterior_Lighting_HS_CAN_LoadSignalValuesArray(DB_Exterior_Lighting_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->AdvFrntLghtSysEnbld;
    dArray[1] = pMsg->AutLghtCtrl;
    dArray[2] = pMsg->AutoBmSlctAllwd;
    dArray[3] = pMsg->AutoLtsActIO;
    dArray[4] = pMsg->AutoLtsInactIO;
    dArray[5] = pMsg->BrkLtsAtv;
    dArray[6] = pMsg->DRLAct;
    dArray[7] = pMsg->DispNtSchmAtv;
    dArray[8] = pMsg->FlToPsSwAtv;
    dArray[9] = pMsg->FrFogLmpsAct;
    dArray[10] = pMsg->FrFgLtIO;
    dArray[11] = pMsg->HazSwAtv;
    dArray[12] = pMsg->HdlmpBmSelectStat;
    dArray[13] = pMsg->HighBmAct;
    dArray[14] = pMsg->HiBmIO;
    dArray[15] = pMsg->HiBmReqd;
    dArray[16] = pMsg->IntDimDspLvl;
    dArray[17] = pMsg->IntDimLvl;
    dArray[18] = pMsg->IntDimNtPnlAtv;
    dArray[19] = pMsg->LftTrnLmpAtv;
    dArray[20] = pMsg->LowBmAct;
    dArray[21] = pMsg->MainLghtSw;
    dArray[22] = pMsg->OtsdAmbtLtLvlStat;
    dArray[23] = pMsg->OtsdAmbtLtLvlStatV;
    dArray[24] = pMsg->PrkLtIO;
    dArray[25] = pMsg->PrkLtLeftIO;
    dArray[26] = pMsg->PrkLtRightIO;
    dArray[27] = pMsg->RrFogLmpsAct;
    dArray[28] = pMsg->RrFgLtIO;
    dArray[29] = pMsg->RevLmpAtv;
    dArray[30] = pMsg->RtTrnLmpAtv;
    dArray[31] = pMsg->TrnSwAct;
}

void DB_Exterior_Lighting_HS_CAN_LoadRawSignalValuesArray(DB_Exterior_Lighting_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->AdvFrntLghtSysEnbld_raw;
    nRawValues[1] = pMsg->AutLghtCtrl_raw;
    nRawValues[2] = pMsg->AutoBmSlctAllwd_raw;
    nRawValues[3] = pMsg->AutoLtsActIO_raw;
    nRawValues[4] = pMsg->AutoLtsInactIO_raw;
    nRawValues[5] = pMsg->BrkLtsAtv_raw;
    nRawValues[6] = pMsg->DRLAct_raw;
    nRawValues[7] = pMsg->DispNtSchmAtv_raw;
    nRawValues[8] = pMsg->FlToPsSwAtv_raw;
    nRawValues[9] = pMsg->FrFogLmpsAct_raw;
    nRawValues[10] = pMsg->FrFgLtIO_raw;
    nRawValues[11] = pMsg->HazSwAtv_raw;
    nRawValues[12] = pMsg->HdlmpBmSelectStat_raw;
    nRawValues[13] = pMsg->HighBmAct_raw;
    nRawValues[14] = pMsg->HiBmIO_raw;
    nRawValues[15] = pMsg->HiBmReqd_raw;
    nRawValues[16] = pMsg->IntDimDspLvl_raw;
    nRawValues[17] = pMsg->IntDimLvl_raw;
    nRawValues[18] = pMsg->IntDimNtPnlAtv_raw;
    nRawValues[19] = pMsg->LftTrnLmpAtv_raw;
    nRawValues[20] = pMsg->LowBmAct_raw;
    nRawValues[21] = pMsg->MainLghtSw_raw;
    nRawValues[22] = pMsg->OtsdAmbtLtLvlStat_raw;
    nRawValues[23] = pMsg->OtsdAmbtLtLvlStatV_raw;
    nRawValues[24] = pMsg->PrkLtIO_raw;
    nRawValues[25] = pMsg->PrkLtLeftIO_raw;
    nRawValues[26] = pMsg->PrkLtRightIO_raw;
    nRawValues[27] = pMsg->RrFogLmpsAct_raw;
    nRawValues[28] = pMsg->RrFgLtIO_raw;
    nRawValues[29] = pMsg->RevLmpAtv_raw;
    nRawValues[30] = pMsg->RtTrnLmpAtv_raw;
    nRawValues[31] = pMsg->TrnSwAct_raw;
}

int DB_Exterior_Lighting_HS_CAN_Transmit(DB_Exterior_Lighting_HS_CAN * pMsg)
{
    double dArray[32];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Exterior_Lighting_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Exterior_Lighting_HS_CAN_Init(pMsg);
    }

    DB_Exterior_Lighting_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Exterior_Lighting_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 32);
}

int DB_Exterior_Lighting_HS_CAN_Transmit_raw(DB_Exterior_Lighting_HS_CAN * pMsg)
{
    uint64 nRawValues[32];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Exterior_Lighting_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Exterior_Lighting_HS_CAN_Init(pMsg);
    }

    DB_Exterior_Lighting_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Exterior_Lighting_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 32);
}

int DB_Exterior_Lighting_HS_CAN_UpdateBytesFromSignals(DB_Exterior_Lighting_HS_CAN * pMsg)
{
    double dArray[32];

    DB_Exterior_Lighting_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Exterior_Lighting_HS_CAN_Index, dArray, 32, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Exterior_Lighting_HS_CAN_UpdateBytesFromRawSignals(DB_Exterior_Lighting_HS_CAN * pMsg)
{
    uint64 nRawValues[32];

    DB_Exterior_Lighting_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Exterior_Lighting_HS_CAN_Index, nRawValues, 32, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Front_Seat_Heat_Cool_Control_HS_CAN_Index = 44;

void DB_Front_Seat_Heat_Cool_Control_HS_CAN_Init(DB_Front_Seat_Heat_Cool_Control_HS_CAN * pMsg)
{
    double dValues[8] = {0.0};
    uint64 nRawValues[8] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Front_Seat_Heat_Cool_Control_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 8, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->DrvHCSMIndReq = dValues[0];
    pMsg->DrvHCSMInd1 = dValues[1];
    pMsg->DrvHCSMInd2 = dValues[2];
    pMsg->DrvHCSMInd3 = dValues[3];
    pMsg->PassHCSMIndReq = dValues[4];
    pMsg->PassHCSMInd1 = dValues[5];
    pMsg->PassHCSMInd2 = dValues[6];
    pMsg->PassHCSMInd3 = dValues[7];
    CM_MessageRawInit(g_uiHandle, 0, DB_Front_Seat_Heat_Cool_Control_HS_CAN_Index, nRawValues, 8, &iActualSignalMaxCount);
    pMsg->DrvHCSMIndReq_raw = (BYTE)nRawValues[0];
    pMsg->DrvHCSMInd1_raw = (BYTE)nRawValues[1];
    pMsg->DrvHCSMInd2_raw = (BYTE)nRawValues[2];
    pMsg->DrvHCSMInd3_raw = (BYTE)nRawValues[3];
    pMsg->PassHCSMIndReq_raw = (BYTE)nRawValues[4];
    pMsg->PassHCSMInd1_raw = (BYTE)nRawValues[5];
    pMsg->PassHCSMInd2_raw = (BYTE)nRawValues[6];
    pMsg->PassHCSMInd3_raw = (BYTE)nRawValues[7];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Front_Seat_Heat_Cool_Control_HS_CAN_LoadSignalValuesArray(DB_Front_Seat_Heat_Cool_Control_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->DrvHCSMIndReq;
    dArray[1] = pMsg->DrvHCSMInd1;
    dArray[2] = pMsg->DrvHCSMInd2;
    dArray[3] = pMsg->DrvHCSMInd3;
    dArray[4] = pMsg->PassHCSMIndReq;
    dArray[5] = pMsg->PassHCSMInd1;
    dArray[6] = pMsg->PassHCSMInd2;
    dArray[7] = pMsg->PassHCSMInd3;
}

void DB_Front_Seat_Heat_Cool_Control_HS_CAN_LoadRawSignalValuesArray(DB_Front_Seat_Heat_Cool_Control_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->DrvHCSMIndReq_raw;
    nRawValues[1] = pMsg->DrvHCSMInd1_raw;
    nRawValues[2] = pMsg->DrvHCSMInd2_raw;
    nRawValues[3] = pMsg->DrvHCSMInd3_raw;
    nRawValues[4] = pMsg->PassHCSMIndReq_raw;
    nRawValues[5] = pMsg->PassHCSMInd1_raw;
    nRawValues[6] = pMsg->PassHCSMInd2_raw;
    nRawValues[7] = pMsg->PassHCSMInd3_raw;
}

int DB_Front_Seat_Heat_Cool_Control_HS_CAN_Transmit(DB_Front_Seat_Heat_Cool_Control_HS_CAN * pMsg)
{
    double dArray[8];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Front_Seat_Heat_Cool_Control_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Front_Seat_Heat_Cool_Control_HS_CAN_Init(pMsg);
    }

    DB_Front_Seat_Heat_Cool_Control_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Front_Seat_Heat_Cool_Control_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 8);
}

int DB_Front_Seat_Heat_Cool_Control_HS_CAN_Transmit_raw(DB_Front_Seat_Heat_Cool_Control_HS_CAN * pMsg)
{
    uint64 nRawValues[8];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Front_Seat_Heat_Cool_Control_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Front_Seat_Heat_Cool_Control_HS_CAN_Init(pMsg);
    }

    DB_Front_Seat_Heat_Cool_Control_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Front_Seat_Heat_Cool_Control_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 8);
}

int DB_Front_Seat_Heat_Cool_Control_HS_CAN_UpdateBytesFromSignals(DB_Front_Seat_Heat_Cool_Control_HS_CAN * pMsg)
{
    double dArray[8];

    DB_Front_Seat_Heat_Cool_Control_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Front_Seat_Heat_Cool_Control_HS_CAN_Index, dArray, 8, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Front_Seat_Heat_Cool_Control_HS_CAN_UpdateBytesFromRawSignals(DB_Front_Seat_Heat_Cool_Control_HS_CAN * pMsg)
{
    uint64 nRawValues[8];

    DB_Front_Seat_Heat_Cool_Control_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Front_Seat_Heat_Cool_Control_HS_CAN_Index, nRawValues, 8, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_PPEI_Engine_Environmental_Stat_HS_CAN_Index = 45;

void DB_PPEI_Engine_Environmental_Stat_HS_CAN_Init(DB_PPEI_Engine_Environmental_Stat_HS_CAN * pMsg)
{
    double dValues[8] = {0.0};
    uint64 nRawValues[8] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_PPEI_Engine_Environmental_Stat_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 8, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->OtsAirTmp = dValues[0];
    pMsg->OtsAirTmpCrVal = dValues[1];
    pMsg->OtsAirTmpCrValMsk = dValues[2];
    pMsg->OtsAirTmpCrValV = dValues[3];
    pMsg->EngInltSpcfcHmdty = dValues[4];
    pMsg->EngInltSpcfcHmdtyM = dValues[5];
    pMsg->EngInltSpcfcHmdtyV = dValues[6];
    pMsg->OtsAirTmpV = dValues[7];
    CM_MessageRawInit(g_uiHandle, 0, DB_PPEI_Engine_Environmental_Stat_HS_CAN_Index, nRawValues, 8, &iActualSignalMaxCount);
    pMsg->OtsAirTmp_raw = (BYTE)nRawValues[0];
    pMsg->OtsAirTmpCrVal_raw = (BYTE)nRawValues[1];
    pMsg->OtsAirTmpCrValMsk_raw = (BYTE)nRawValues[2];
    pMsg->OtsAirTmpCrValV_raw = (BYTE)nRawValues[3];
    pMsg->EngInltSpcfcHmdty_raw = (BYTE)nRawValues[4];
    pMsg->EngInltSpcfcHmdtyM_raw = (BYTE)nRawValues[5];
    pMsg->EngInltSpcfcHmdtyV_raw = (BYTE)nRawValues[6];
    pMsg->OtsAirTmpV_raw = (BYTE)nRawValues[7];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_PPEI_Engine_Environmental_Stat_HS_CAN_LoadSignalValuesArray(DB_PPEI_Engine_Environmental_Stat_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->OtsAirTmp;
    dArray[1] = pMsg->OtsAirTmpCrVal;
    dArray[2] = pMsg->OtsAirTmpCrValMsk;
    dArray[3] = pMsg->OtsAirTmpCrValV;
    dArray[4] = pMsg->EngInltSpcfcHmdty;
    dArray[5] = pMsg->EngInltSpcfcHmdtyM;
    dArray[6] = pMsg->EngInltSpcfcHmdtyV;
    dArray[7] = pMsg->OtsAirTmpV;
}

void DB_PPEI_Engine_Environmental_Stat_HS_CAN_LoadRawSignalValuesArray(DB_PPEI_Engine_Environmental_Stat_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->OtsAirTmp_raw;
    nRawValues[1] = pMsg->OtsAirTmpCrVal_raw;
    nRawValues[2] = pMsg->OtsAirTmpCrValMsk_raw;
    nRawValues[3] = pMsg->OtsAirTmpCrValV_raw;
    nRawValues[4] = pMsg->EngInltSpcfcHmdty_raw;
    nRawValues[5] = pMsg->EngInltSpcfcHmdtyM_raw;
    nRawValues[6] = pMsg->EngInltSpcfcHmdtyV_raw;
    nRawValues[7] = pMsg->OtsAirTmpV_raw;
}

int DB_PPEI_Engine_Environmental_Stat_HS_CAN_Transmit(DB_PPEI_Engine_Environmental_Stat_HS_CAN * pMsg)
{
    double dArray[8];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_PPEI_Engine_Environmental_Stat_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_PPEI_Engine_Environmental_Stat_HS_CAN_Init(pMsg);
    }

    DB_PPEI_Engine_Environmental_Stat_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_PPEI_Engine_Environmental_Stat_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 8);
}

int DB_PPEI_Engine_Environmental_Stat_HS_CAN_Transmit_raw(DB_PPEI_Engine_Environmental_Stat_HS_CAN * pMsg)
{
    uint64 nRawValues[8];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_PPEI_Engine_Environmental_Stat_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_PPEI_Engine_Environmental_Stat_HS_CAN_Init(pMsg);
    }

    DB_PPEI_Engine_Environmental_Stat_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_PPEI_Engine_Environmental_Stat_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 8);
}

int DB_PPEI_Engine_Environmental_Stat_HS_CAN_UpdateBytesFromSignals(DB_PPEI_Engine_Environmental_Stat_HS_CAN * pMsg)
{
    double dArray[8];

    DB_PPEI_Engine_Environmental_Stat_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_PPEI_Engine_Environmental_Stat_HS_CAN_Index, dArray, 8, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_PPEI_Engine_Environmental_Stat_HS_CAN_UpdateBytesFromRawSignals(DB_PPEI_Engine_Environmental_Stat_HS_CAN * pMsg)
{
    uint64 nRawValues[8];

    DB_PPEI_Engine_Environmental_Stat_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_PPEI_Engine_Environmental_Stat_HS_CAN_Index, nRawValues, 8, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Instrument_Panel_Sensor_HS_CAN_Index = 46;

void DB_Instrument_Panel_Sensor_HS_CAN_Init(DB_Instrument_Panel_Sensor_HS_CAN * pMsg)
{
    double dValues[5] = {0.0};
    uint64 nRawValues[5] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Instrument_Panel_Sensor_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 5, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->IPSnsrSolrAnglFltd = dValues[0];
    pMsg->IPSnsrRwSolrIntFltd = dValues[1];
    pMsg->IPSnsrRwSolrInt = dValues[2];
    pMsg->IPSnsrSolrAzmthAngl = dValues[3];
    pMsg->IPSnsrSolrElvtnAngl = dValues[4];
    CM_MessageRawInit(g_uiHandle, 0, DB_Instrument_Panel_Sensor_HS_CAN_Index, nRawValues, 5, &iActualSignalMaxCount);
    pMsg->IPSnsrSolrAnglFltd_raw = (BYTE)nRawValues[0];
    pMsg->IPSnsrRwSolrIntFltd_raw = (BYTE)nRawValues[1];
    pMsg->IPSnsrRwSolrInt_raw = (BYTE)nRawValues[2];
    pMsg->IPSnsrSolrAzmthAngl_raw = (BYTE)nRawValues[3];
    pMsg->IPSnsrSolrElvtnAngl_raw = (BYTE)nRawValues[4];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Instrument_Panel_Sensor_HS_CAN_LoadSignalValuesArray(DB_Instrument_Panel_Sensor_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->IPSnsrSolrAnglFltd;
    dArray[1] = pMsg->IPSnsrRwSolrIntFltd;
    dArray[2] = pMsg->IPSnsrRwSolrInt;
    dArray[3] = pMsg->IPSnsrSolrAzmthAngl;
    dArray[4] = pMsg->IPSnsrSolrElvtnAngl;
}

void DB_Instrument_Panel_Sensor_HS_CAN_LoadRawSignalValuesArray(DB_Instrument_Panel_Sensor_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->IPSnsrSolrAnglFltd_raw;
    nRawValues[1] = pMsg->IPSnsrRwSolrIntFltd_raw;
    nRawValues[2] = pMsg->IPSnsrRwSolrInt_raw;
    nRawValues[3] = pMsg->IPSnsrSolrAzmthAngl_raw;
    nRawValues[4] = pMsg->IPSnsrSolrElvtnAngl_raw;
}

int DB_Instrument_Panel_Sensor_HS_CAN_Transmit(DB_Instrument_Panel_Sensor_HS_CAN * pMsg)
{
    double dArray[5];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Instrument_Panel_Sensor_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Instrument_Panel_Sensor_HS_CAN_Init(pMsg);
    }

    DB_Instrument_Panel_Sensor_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Instrument_Panel_Sensor_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 5);
}

int DB_Instrument_Panel_Sensor_HS_CAN_Transmit_raw(DB_Instrument_Panel_Sensor_HS_CAN * pMsg)
{
    uint64 nRawValues[5];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Instrument_Panel_Sensor_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Instrument_Panel_Sensor_HS_CAN_Init(pMsg);
    }

    DB_Instrument_Panel_Sensor_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Instrument_Panel_Sensor_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 5);
}

int DB_Instrument_Panel_Sensor_HS_CAN_UpdateBytesFromSignals(DB_Instrument_Panel_Sensor_HS_CAN * pMsg)
{
    double dArray[5];

    DB_Instrument_Panel_Sensor_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Instrument_Panel_Sensor_HS_CAN_Index, dArray, 5, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Instrument_Panel_Sensor_HS_CAN_UpdateBytesFromRawSignals(DB_Instrument_Panel_Sensor_HS_CAN * pMsg)
{
    uint64 nRawValues[5];

    DB_Instrument_Panel_Sensor_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Instrument_Panel_Sensor_HS_CAN_Index, nRawValues, 5, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index = 47;

void DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Init(DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN * pMsg)
{
    double dValues[12] = {0.0};
    uint64 nRawValues[12] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 12, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->DistRollCntAvgDrvn = dValues[0];
    pMsg->DstRolCntAvgDrnRstOc = dValues[1];
    pMsg->DistRollCntAvgDrvnSrc = dValues[2];
    pMsg->DistRollCntAvgDrvnV = dValues[3];
    pMsg->DstRolCntAvgNonDrvn = dValues[4];
    pMsg->DstRolCntAvNDrRstOc = dValues[5];
    pMsg->DstRolCntAvgNonDrvnV = dValues[6];
    pMsg->VehSpdAvgDrvn = dValues[7];
    pMsg->VehSpdAvgDrvnSrc = dValues[8];
    pMsg->VehSpdAvgDrvnV = dValues[9];
    pMsg->VehSpdAvgNDrvn = dValues[10];
    pMsg->VehSpdAvgNDrvnV = dValues[11];
    CM_MessageRawInit(g_uiHandle, 0, DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, nRawValues, 12, &iActualSignalMaxCount);
    pMsg->DistRollCntAvgDrvn_raw = (WORD)nRawValues[0];
    pMsg->DstRolCntAvgDrnRstOc_raw = (BYTE)nRawValues[1];
    pMsg->DistRollCntAvgDrvnSrc_raw = (BYTE)nRawValues[2];
    pMsg->DistRollCntAvgDrvnV_raw = (BYTE)nRawValues[3];
    pMsg->DstRolCntAvgNonDrvn_raw = (WORD)nRawValues[4];
    pMsg->DstRolCntAvNDrRstOc_raw = (BYTE)nRawValues[5];
    pMsg->DstRolCntAvgNonDrvnV_raw = (BYTE)nRawValues[6];
    pMsg->VehSpdAvgDrvn_raw = (WORD)nRawValues[7];
    pMsg->VehSpdAvgDrvnSrc_raw = (BYTE)nRawValues[8];
    pMsg->VehSpdAvgDrvnV_raw = (BYTE)nRawValues[9];
    pMsg->VehSpdAvgNDrvn_raw = (WORD)nRawValues[10];
    pMsg->VehSpdAvgNDrvnV_raw = (BYTE)nRawValues[11];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_LoadSignalValuesArray(DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->DistRollCntAvgDrvn;
    dArray[1] = pMsg->DstRolCntAvgDrnRstOc;
    dArray[2] = pMsg->DistRollCntAvgDrvnSrc;
    dArray[3] = pMsg->DistRollCntAvgDrvnV;
    dArray[4] = pMsg->DstRolCntAvgNonDrvn;
    dArray[5] = pMsg->DstRolCntAvNDrRstOc;
    dArray[6] = pMsg->DstRolCntAvgNonDrvnV;
    dArray[7] = pMsg->VehSpdAvgDrvn;
    dArray[8] = pMsg->VehSpdAvgDrvnSrc;
    dArray[9] = pMsg->VehSpdAvgDrvnV;
    dArray[10] = pMsg->VehSpdAvgNDrvn;
    dArray[11] = pMsg->VehSpdAvgNDrvnV;
}

void DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_LoadRawSignalValuesArray(DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->DistRollCntAvgDrvn_raw;
    nRawValues[1] = pMsg->DstRolCntAvgDrnRstOc_raw;
    nRawValues[2] = pMsg->DistRollCntAvgDrvnSrc_raw;
    nRawValues[3] = pMsg->DistRollCntAvgDrvnV_raw;
    nRawValues[4] = pMsg->DstRolCntAvgNonDrvn_raw;
    nRawValues[5] = pMsg->DstRolCntAvNDrRstOc_raw;
    nRawValues[6] = pMsg->DstRolCntAvgNonDrvnV_raw;
    nRawValues[7] = pMsg->VehSpdAvgDrvn_raw;
    nRawValues[8] = pMsg->VehSpdAvgDrvnSrc_raw;
    nRawValues[9] = pMsg->VehSpdAvgDrvnV_raw;
    nRawValues[10] = pMsg->VehSpdAvgNDrvn_raw;
    nRawValues[11] = pMsg->VehSpdAvgNDrvnV_raw;
}

int DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Transmit(DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN * pMsg)
{
    double dArray[12];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Init(pMsg);
    }

    DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 12);
}

int DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Transmit_raw(DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN * pMsg)
{
    uint64 nRawValues[12];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Init(pMsg);
    }

    DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 12);
}

int DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_UpdateBytesFromSignals(DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN * pMsg)
{
    double dArray[12];

    DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, dArray, 12, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_UpdateBytesFromRawSignals(DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN * pMsg)
{
    uint64 nRawValues[12];

    DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, nRawValues, 12, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN_Index = 48;

void DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN_Init(DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->DgnInf = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->DgnInf_raw = (uint64)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN_LoadSignalValuesArray(DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->DgnInf;
}

void DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN_LoadRawSignalValuesArray(DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->DgnInf_raw;
}

int DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN_Transmit(DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN_Init(pMsg);
    }

    DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN_Transmit_raw(DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN_Init(pMsg);
    }

    DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN_UpdateBytesFromSignals(DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN * pMsg)
{
    double dArray[1];

    DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN_UpdateBytesFromRawSignals(DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN * pMsg)
{
    uint64 nRawValues[1];

    DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN_Index = 49;

void DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN_Init(DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->DgnInf = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->DgnInf_raw = (uint64)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN_LoadSignalValuesArray(DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->DgnInf;
}

void DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN_LoadRawSignalValuesArray(DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->DgnInf_raw;
}

int DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN_Transmit(DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN_Init(pMsg);
    }

    DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN_Transmit_raw(DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN_Init(pMsg);
    }

    DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN_UpdateBytesFromSignals(DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN * pMsg)
{
    double dArray[1];

    DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN_UpdateBytesFromRawSignals(DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN * pMsg)
{
    uint64 nRawValues[1];

    DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN_Index = 50;

void DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN_Init(DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->DgnInf = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->DgnInf_raw = (uint64)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN_LoadSignalValuesArray(DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->DgnInf;
}

void DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN_LoadRawSignalValuesArray(DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->DgnInf_raw;
}

int DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN_Transmit(DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN_Init(pMsg);
    }

    DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN_Transmit_raw(DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN_Init(pMsg);
    }

    DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN_UpdateBytesFromSignals(DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN * pMsg)
{
    double dArray[1];

    DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN_UpdateBytesFromRawSignals(DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN * pMsg)
{
    uint64 nRawValues[1];

    DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Front_Seat_Heat_Cool_Switches_HS_CAN_Index = 51;

void DB_Front_Seat_Heat_Cool_Switches_HS_CAN_Init(DB_Front_Seat_Heat_Cool_Switches_HS_CAN * pMsg)
{
    double dValues[6] = {0.0};
    uint64 nRawValues[6] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Front_Seat_Heat_Cool_Switches_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 6, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->DrvHCSeatSw1Act = dValues[0];
    pMsg->DrvHCSeatSw2Act = dValues[1];
    pMsg->DrvHCSeatSw3Act = dValues[2];
    pMsg->PassHCSeatSw1Act = dValues[3];
    pMsg->PassHCSeatSw2Act = dValues[4];
    pMsg->PassHCSeatSw3Act = dValues[5];
    CM_MessageRawInit(g_uiHandle, 0, DB_Front_Seat_Heat_Cool_Switches_HS_CAN_Index, nRawValues, 6, &iActualSignalMaxCount);
    pMsg->DrvHCSeatSw1Act_raw = (BYTE)nRawValues[0];
    pMsg->DrvHCSeatSw2Act_raw = (BYTE)nRawValues[1];
    pMsg->DrvHCSeatSw3Act_raw = (BYTE)nRawValues[2];
    pMsg->PassHCSeatSw1Act_raw = (BYTE)nRawValues[3];
    pMsg->PassHCSeatSw2Act_raw = (BYTE)nRawValues[4];
    pMsg->PassHCSeatSw3Act_raw = (BYTE)nRawValues[5];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Front_Seat_Heat_Cool_Switches_HS_CAN_LoadSignalValuesArray(DB_Front_Seat_Heat_Cool_Switches_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->DrvHCSeatSw1Act;
    dArray[1] = pMsg->DrvHCSeatSw2Act;
    dArray[2] = pMsg->DrvHCSeatSw3Act;
    dArray[3] = pMsg->PassHCSeatSw1Act;
    dArray[4] = pMsg->PassHCSeatSw2Act;
    dArray[5] = pMsg->PassHCSeatSw3Act;
}

void DB_Front_Seat_Heat_Cool_Switches_HS_CAN_LoadRawSignalValuesArray(DB_Front_Seat_Heat_Cool_Switches_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->DrvHCSeatSw1Act_raw;
    nRawValues[1] = pMsg->DrvHCSeatSw2Act_raw;
    nRawValues[2] = pMsg->DrvHCSeatSw3Act_raw;
    nRawValues[3] = pMsg->PassHCSeatSw1Act_raw;
    nRawValues[4] = pMsg->PassHCSeatSw2Act_raw;
    nRawValues[5] = pMsg->PassHCSeatSw3Act_raw;
}

int DB_Front_Seat_Heat_Cool_Switches_HS_CAN_Transmit(DB_Front_Seat_Heat_Cool_Switches_HS_CAN * pMsg)
{
    double dArray[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Front_Seat_Heat_Cool_Switches_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Front_Seat_Heat_Cool_Switches_HS_CAN_Init(pMsg);
    }

    DB_Front_Seat_Heat_Cool_Switches_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Front_Seat_Heat_Cool_Switches_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 6);
}

int DB_Front_Seat_Heat_Cool_Switches_HS_CAN_Transmit_raw(DB_Front_Seat_Heat_Cool_Switches_HS_CAN * pMsg)
{
    uint64 nRawValues[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Front_Seat_Heat_Cool_Switches_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Front_Seat_Heat_Cool_Switches_HS_CAN_Init(pMsg);
    }

    DB_Front_Seat_Heat_Cool_Switches_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Front_Seat_Heat_Cool_Switches_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 6);
}

int DB_Front_Seat_Heat_Cool_Switches_HS_CAN_UpdateBytesFromSignals(DB_Front_Seat_Heat_Cool_Switches_HS_CAN * pMsg)
{
    double dArray[6];

    DB_Front_Seat_Heat_Cool_Switches_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Front_Seat_Heat_Cool_Switches_HS_CAN_Index, dArray, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Front_Seat_Heat_Cool_Switches_HS_CAN_UpdateBytesFromRawSignals(DB_Front_Seat_Heat_Cool_Switches_HS_CAN * pMsg)
{
    uint64 nRawValues[6];

    DB_Front_Seat_Heat_Cool_Switches_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Front_Seat_Heat_Cool_Switches_HS_CAN_Index, nRawValues, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Auxiliary_Heater_Status_HS_CAN_Index = 52;

void DB_Auxiliary_Heater_Status_HS_CAN_Init(DB_Auxiliary_Heater_Status_HS_CAN * pMsg)
{
    double dValues[4] = {0.0};
    uint64 nRawValues[4] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Auxiliary_Heater_Status_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 4, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->AuxHtrAtv = dValues[0];
    pMsg->CCClntCrcFlwRtReq = dValues[1];
    pMsg->HtrCoreInltClntTmpCalc = dValues[2];
    pMsg->HtrCoreInltClntTmpCalcV = dValues[3];
    CM_MessageRawInit(g_uiHandle, 0, DB_Auxiliary_Heater_Status_HS_CAN_Index, nRawValues, 4, &iActualSignalMaxCount);
    pMsg->AuxHtrAtv_raw = (BYTE)nRawValues[0];
    pMsg->CCClntCrcFlwRtReq_raw = (BYTE)nRawValues[1];
    pMsg->HtrCoreInltClntTmpCalc_raw = (BYTE)nRawValues[2];
    pMsg->HtrCoreInltClntTmpCalcV_raw = (BYTE)nRawValues[3];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Auxiliary_Heater_Status_HS_CAN_LoadSignalValuesArray(DB_Auxiliary_Heater_Status_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->AuxHtrAtv;
    dArray[1] = pMsg->CCClntCrcFlwRtReq;
    dArray[2] = pMsg->HtrCoreInltClntTmpCalc;
    dArray[3] = pMsg->HtrCoreInltClntTmpCalcV;
}

void DB_Auxiliary_Heater_Status_HS_CAN_LoadRawSignalValuesArray(DB_Auxiliary_Heater_Status_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->AuxHtrAtv_raw;
    nRawValues[1] = pMsg->CCClntCrcFlwRtReq_raw;
    nRawValues[2] = pMsg->HtrCoreInltClntTmpCalc_raw;
    nRawValues[3] = pMsg->HtrCoreInltClntTmpCalcV_raw;
}

int DB_Auxiliary_Heater_Status_HS_CAN_Transmit(DB_Auxiliary_Heater_Status_HS_CAN * pMsg)
{
    double dArray[4];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Auxiliary_Heater_Status_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Auxiliary_Heater_Status_HS_CAN_Init(pMsg);
    }

    DB_Auxiliary_Heater_Status_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Auxiliary_Heater_Status_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 4);
}

int DB_Auxiliary_Heater_Status_HS_CAN_Transmit_raw(DB_Auxiliary_Heater_Status_HS_CAN * pMsg)
{
    uint64 nRawValues[4];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Auxiliary_Heater_Status_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Auxiliary_Heater_Status_HS_CAN_Init(pMsg);
    }

    DB_Auxiliary_Heater_Status_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Auxiliary_Heater_Status_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 4);
}

int DB_Auxiliary_Heater_Status_HS_CAN_UpdateBytesFromSignals(DB_Auxiliary_Heater_Status_HS_CAN * pMsg)
{
    double dArray[4];

    DB_Auxiliary_Heater_Status_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Auxiliary_Heater_Status_HS_CAN_Index, dArray, 4, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Auxiliary_Heater_Status_HS_CAN_UpdateBytesFromRawSignals(DB_Auxiliary_Heater_Status_HS_CAN * pMsg)
{
    uint64 nRawValues[4];

    DB_Auxiliary_Heater_Status_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Auxiliary_Heater_Status_HS_CAN_Index, nRawValues, 4, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Rear_Window_Defog_Status_HS_CAN_Index = 53;

void DB_Rear_Window_Defog_Status_HS_CAN_Init(DB_Rear_Window_Defog_Status_HS_CAN * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Rear_Window_Defog_Status_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->RrWndDfgOn = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_Rear_Window_Defog_Status_HS_CAN_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->RrWndDfgOn_raw = (BYTE)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Rear_Window_Defog_Status_HS_CAN_LoadSignalValuesArray(DB_Rear_Window_Defog_Status_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->RrWndDfgOn;
}

void DB_Rear_Window_Defog_Status_HS_CAN_LoadRawSignalValuesArray(DB_Rear_Window_Defog_Status_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->RrWndDfgOn_raw;
}

int DB_Rear_Window_Defog_Status_HS_CAN_Transmit(DB_Rear_Window_Defog_Status_HS_CAN * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Rear_Window_Defog_Status_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Rear_Window_Defog_Status_HS_CAN_Init(pMsg);
    }

    DB_Rear_Window_Defog_Status_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Rear_Window_Defog_Status_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_Rear_Window_Defog_Status_HS_CAN_Transmit_raw(DB_Rear_Window_Defog_Status_HS_CAN * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Rear_Window_Defog_Status_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Rear_Window_Defog_Status_HS_CAN_Init(pMsg);
    }

    DB_Rear_Window_Defog_Status_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Rear_Window_Defog_Status_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_Rear_Window_Defog_Status_HS_CAN_UpdateBytesFromSignals(DB_Rear_Window_Defog_Status_HS_CAN * pMsg)
{
    double dArray[1];

    DB_Rear_Window_Defog_Status_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Rear_Window_Defog_Status_HS_CAN_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Rear_Window_Defog_Status_HS_CAN_UpdateBytesFromRawSignals(DB_Rear_Window_Defog_Status_HS_CAN * pMsg)
{
    uint64 nRawValues[1];

    DB_Rear_Window_Defog_Status_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Rear_Window_Defog_Status_HS_CAN_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_PPEI_Engine_General_Status_1_HS_CAN_Index = 54;

void DB_PPEI_Engine_General_Status_1_HS_CAN_Init(DB_PPEI_Engine_General_Status_1_HS_CAN * pMsg)
{
    double dValues[19] = {0.0};
    uint64 nRawValues[19] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_PPEI_Engine_General_Status_1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 19, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->AccActPos = dValues[0];
    pMsg->AccActPosV = dValues[1];
    pMsg->CrsCntAtv = dValues[2];
    pMsg->CrsCntEnbld = dValues[3];
    pMsg->Eng12vStrtrMtrCmmdOn = dValues[4];
    pMsg->EngCntrlRunCrnkTrmSt = dValues[5];
    pMsg->EngIdlAtv = dValues[6];
    pMsg->EngAirIntBstPr = dValues[7];
    pMsg->EngAirIntBstPrV = dValues[8];
    pMsg->EngRunAtv = dValues[9];
    pMsg->EngSpd = dValues[10];
    pMsg->EngSpdStat = dValues[11];
    pMsg->PT_BrkPedDscrtInpStat = dValues[12];
    pMsg->PT_BrkPedDscrtInpStatV = dValues[13];
    pMsg->PTCrnkAbrted = dValues[14];
    pMsg->PT_CrnkAct = dValues[15];
    pMsg->PTRunAbrt = dValues[16];
    pMsg->RmVhStrtEngRng = dValues[17];
    pMsg->SpdLmtrSpdWrngEnbld = dValues[18];
    CM_MessageRawInit(g_uiHandle, 0, DB_PPEI_Engine_General_Status_1_HS_CAN_Index, nRawValues, 19, &iActualSignalMaxCount);
    pMsg->AccActPos_raw = (BYTE)nRawValues[0];
    pMsg->AccActPosV_raw = (BYTE)nRawValues[1];
    pMsg->CrsCntAtv_raw = (BYTE)nRawValues[2];
    pMsg->CrsCntEnbld_raw = (BYTE)nRawValues[3];
    pMsg->Eng12vStrtrMtrCmmdOn_raw = (BYTE)nRawValues[4];
    pMsg->EngCntrlRunCrnkTrmSt_raw = (BYTE)nRawValues[5];
    pMsg->EngIdlAtv_raw = (BYTE)nRawValues[6];
    pMsg->EngAirIntBstPr_raw = (BYTE)nRawValues[7];
    pMsg->EngAirIntBstPrV_raw = (BYTE)nRawValues[8];
    pMsg->EngRunAtv_raw = (BYTE)nRawValues[9];
    pMsg->EngSpd_raw = (WORD)nRawValues[10];
    pMsg->EngSpdStat_raw = (BYTE)nRawValues[11];
    pMsg->PT_BrkPedDscrtInpStat_raw = (BYTE)nRawValues[12];
    pMsg->PT_BrkPedDscrtInpStatV_raw = (BYTE)nRawValues[13];
    pMsg->PTCrnkAbrted_raw = (BYTE)nRawValues[14];
    pMsg->PT_CrnkAct_raw = (BYTE)nRawValues[15];
    pMsg->PTRunAbrt_raw = (BYTE)nRawValues[16];
    pMsg->RmVhStrtEngRng_raw = (BYTE)nRawValues[17];
    pMsg->SpdLmtrSpdWrngEnbld_raw = (BYTE)nRawValues[18];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_PPEI_Engine_General_Status_1_HS_CAN_LoadSignalValuesArray(DB_PPEI_Engine_General_Status_1_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->AccActPos;
    dArray[1] = pMsg->AccActPosV;
    dArray[2] = pMsg->CrsCntAtv;
    dArray[3] = pMsg->CrsCntEnbld;
    dArray[4] = pMsg->Eng12vStrtrMtrCmmdOn;
    dArray[5] = pMsg->EngCntrlRunCrnkTrmSt;
    dArray[6] = pMsg->EngIdlAtv;
    dArray[7] = pMsg->EngAirIntBstPr;
    dArray[8] = pMsg->EngAirIntBstPrV;
    dArray[9] = pMsg->EngRunAtv;
    dArray[10] = pMsg->EngSpd;
    dArray[11] = pMsg->EngSpdStat;
    dArray[12] = pMsg->PT_BrkPedDscrtInpStat;
    dArray[13] = pMsg->PT_BrkPedDscrtInpStatV;
    dArray[14] = pMsg->PTCrnkAbrted;
    dArray[15] = pMsg->PT_CrnkAct;
    dArray[16] = pMsg->PTRunAbrt;
    dArray[17] = pMsg->RmVhStrtEngRng;
    dArray[18] = pMsg->SpdLmtrSpdWrngEnbld;
}

void DB_PPEI_Engine_General_Status_1_HS_CAN_LoadRawSignalValuesArray(DB_PPEI_Engine_General_Status_1_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->AccActPos_raw;
    nRawValues[1] = pMsg->AccActPosV_raw;
    nRawValues[2] = pMsg->CrsCntAtv_raw;
    nRawValues[3] = pMsg->CrsCntEnbld_raw;
    nRawValues[4] = pMsg->Eng12vStrtrMtrCmmdOn_raw;
    nRawValues[5] = pMsg->EngCntrlRunCrnkTrmSt_raw;
    nRawValues[6] = pMsg->EngIdlAtv_raw;
    nRawValues[7] = pMsg->EngAirIntBstPr_raw;
    nRawValues[8] = pMsg->EngAirIntBstPrV_raw;
    nRawValues[9] = pMsg->EngRunAtv_raw;
    nRawValues[10] = pMsg->EngSpd_raw;
    nRawValues[11] = pMsg->EngSpdStat_raw;
    nRawValues[12] = pMsg->PT_BrkPedDscrtInpStat_raw;
    nRawValues[13] = pMsg->PT_BrkPedDscrtInpStatV_raw;
    nRawValues[14] = pMsg->PTCrnkAbrted_raw;
    nRawValues[15] = pMsg->PT_CrnkAct_raw;
    nRawValues[16] = pMsg->PTRunAbrt_raw;
    nRawValues[17] = pMsg->RmVhStrtEngRng_raw;
    nRawValues[18] = pMsg->SpdLmtrSpdWrngEnbld_raw;
}

int DB_PPEI_Engine_General_Status_1_HS_CAN_Transmit(DB_PPEI_Engine_General_Status_1_HS_CAN * pMsg)
{
    double dArray[19];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_PPEI_Engine_General_Status_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_PPEI_Engine_General_Status_1_HS_CAN_Init(pMsg);
    }

    DB_PPEI_Engine_General_Status_1_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_PPEI_Engine_General_Status_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 19);
}

int DB_PPEI_Engine_General_Status_1_HS_CAN_Transmit_raw(DB_PPEI_Engine_General_Status_1_HS_CAN * pMsg)
{
    uint64 nRawValues[19];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_PPEI_Engine_General_Status_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_PPEI_Engine_General_Status_1_HS_CAN_Init(pMsg);
    }

    DB_PPEI_Engine_General_Status_1_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_PPEI_Engine_General_Status_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 19);
}

int DB_PPEI_Engine_General_Status_1_HS_CAN_UpdateBytesFromSignals(DB_PPEI_Engine_General_Status_1_HS_CAN * pMsg)
{
    double dArray[19];

    DB_PPEI_Engine_General_Status_1_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_PPEI_Engine_General_Status_1_HS_CAN_Index, dArray, 19, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_PPEI_Engine_General_Status_1_HS_CAN_UpdateBytesFromRawSignals(DB_PPEI_Engine_General_Status_1_HS_CAN * pMsg)
{
    uint64 nRawValues[19];

    DB_PPEI_Engine_General_Status_1_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_PPEI_Engine_General_Status_1_HS_CAN_Index, nRawValues, 19, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Climate_Control_General_Status_HS_CAN_Index = 55;

void DB_Climate_Control_General_Status_HS_CAN_Init(DB_Climate_Control_General_Status_HS_CAN * pMsg)
{
    double dValues[6] = {0.0};
    uint64 nRawValues[6] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Climate_Control_General_Status_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 6, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->ACCmpsrFldOn = dValues[0];
    pMsg->ACCompModReq = dValues[1];
    pMsg->ACCompNormLd = dValues[2];
    pMsg->ACCompNormLdV = dValues[3];
    pMsg->ACCmEngRunReq = dValues[4];
    pMsg->ClmtCtrlTrgtTemp = dValues[5];
    CM_MessageRawInit(g_uiHandle, 0, DB_Climate_Control_General_Status_HS_CAN_Index, nRawValues, 6, &iActualSignalMaxCount);
    pMsg->ACCmpsrFldOn_raw = (BYTE)nRawValues[0];
    pMsg->ACCompModReq_raw = (BYTE)nRawValues[1];
    pMsg->ACCompNormLd_raw = (BYTE)nRawValues[2];
    pMsg->ACCompNormLdV_raw = (BYTE)nRawValues[3];
    pMsg->ACCmEngRunReq_raw = (BYTE)nRawValues[4];
    pMsg->ClmtCtrlTrgtTemp_raw = (WORD)nRawValues[5];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Climate_Control_General_Status_HS_CAN_LoadSignalValuesArray(DB_Climate_Control_General_Status_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->ACCmpsrFldOn;
    dArray[1] = pMsg->ACCompModReq;
    dArray[2] = pMsg->ACCompNormLd;
    dArray[3] = pMsg->ACCompNormLdV;
    dArray[4] = pMsg->ACCmEngRunReq;
    dArray[5] = pMsg->ClmtCtrlTrgtTemp;
}

void DB_Climate_Control_General_Status_HS_CAN_LoadRawSignalValuesArray(DB_Climate_Control_General_Status_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->ACCmpsrFldOn_raw;
    nRawValues[1] = pMsg->ACCompModReq_raw;
    nRawValues[2] = pMsg->ACCompNormLd_raw;
    nRawValues[3] = pMsg->ACCompNormLdV_raw;
    nRawValues[4] = pMsg->ACCmEngRunReq_raw;
    nRawValues[5] = pMsg->ClmtCtrlTrgtTemp_raw;
}

int DB_Climate_Control_General_Status_HS_CAN_Transmit(DB_Climate_Control_General_Status_HS_CAN * pMsg)
{
    double dArray[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Climate_Control_General_Status_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Climate_Control_General_Status_HS_CAN_Init(pMsg);
    }

    DB_Climate_Control_General_Status_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Climate_Control_General_Status_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 6);
}

int DB_Climate_Control_General_Status_HS_CAN_Transmit_raw(DB_Climate_Control_General_Status_HS_CAN * pMsg)
{
    uint64 nRawValues[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Climate_Control_General_Status_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Climate_Control_General_Status_HS_CAN_Init(pMsg);
    }

    DB_Climate_Control_General_Status_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Climate_Control_General_Status_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 6);
}

int DB_Climate_Control_General_Status_HS_CAN_UpdateBytesFromSignals(DB_Climate_Control_General_Status_HS_CAN * pMsg)
{
    double dArray[6];

    DB_Climate_Control_General_Status_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Climate_Control_General_Status_HS_CAN_Index, dArray, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Climate_Control_General_Status_HS_CAN_UpdateBytesFromRawSignals(DB_Climate_Control_General_Status_HS_CAN * pMsg)
{
    uint64 nRawValues[6];

    DB_Climate_Control_General_Status_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Climate_Control_General_Status_HS_CAN_Index, nRawValues, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}


int DB_Network_Management_BCM_HS_CAN_Index = 56;

void DB_Network_Management_BCM_HS_CAN_Init(DB_Network_Management_BCM_HS_CAN * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Network_Management_BCM_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->SrcNodeID = dValues[0];
    pMsg->UDat = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_Network_Management_BCM_HS_CAN_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->SrcNodeID_raw = (BYTE)nRawValues[0];
    pMsg->UDat_raw = (uint64)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Network_Management_BCM_HS_CAN_LoadSignalValuesArray(DB_Network_Management_BCM_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->SrcNodeID;
    dArray[1] = pMsg->UDat;
}

void DB_Network_Management_BCM_HS_CAN_LoadRawSignalValuesArray(DB_Network_Management_BCM_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->SrcNodeID_raw;
    nRawValues[1] = pMsg->UDat_raw;
}

int DB_Network_Management_BCM_HS_CAN_Transmit(DB_Network_Management_BCM_HS_CAN * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Network_Management_BCM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Network_Management_BCM_HS_CAN_Init(pMsg);
    }

    DB_Network_Management_BCM_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Network_Management_BCM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_Network_Management_BCM_HS_CAN_Transmit_raw(DB_Network_Management_BCM_HS_CAN * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Network_Management_BCM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Network_Management_BCM_HS_CAN_Init(pMsg);
    }

    DB_Network_Management_BCM_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Network_Management_BCM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_Network_Management_BCM_HS_CAN_UpdateBytesFromSignals(DB_Network_Management_BCM_HS_CAN * pMsg)
{
    double dArray[2];

    DB_Network_Management_BCM_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Network_Management_BCM_HS_CAN_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

int DB_Network_Management_BCM_HS_CAN_UpdateBytesFromRawSignals(DB_Network_Management_BCM_HS_CAN * pMsg)
{
    uint64 nRawValues[2];

    DB_Network_Management_BCM_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Network_Management_BCM_HS_CAN_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
}

