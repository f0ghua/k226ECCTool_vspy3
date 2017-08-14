// vspy generated header file
#ifndef VSPY_GENERATED_HEADER
#define VSPY_GENERATED_HEADER
#include "windows.h"
#include "string.h"
#include <stdio.h>
extern unsigned int g_uiHandle;
typedef unsigned __int64 uint64;

#define printf Printf
int Printf(const char *szInMsg, ...);
int PrintfW(const wchar_t *szInMsg, ...);
int WriteLine(const char *szInMsg, ...);
int WriteLineW(const wchar_t *szInMsg, ...);
void DisplayLastError(LPCWSTR lpszFunction);

typedef void (* RS232OnError_fdef)(DWORD port, DWORD errorFlags);
typedef void (* RS232OnRxTx_fdef)(DWORD port, BYTE buffer[], DWORD dwSize);

DWORD ICS_RS232Open(DWORD port);
DWORD ICS_RS232Close(DWORD port);
DWORD ICS_RS232ConfigTimeout(DWORD port, DWORD baudrate, DWORD numberOfDataBits, DWORD numberOfStopBits, DWORD parity, DWORD timeout);
DWORD ICS_RS232Config(DWORD port, DWORD baudrate, DWORD numberOfDataBits, DWORD numberOfStopBits, DWORD parity);
DWORD ICS_RS232SetHandshake(DWORD port, DWORD handshake, DWORD XonLimit, DWORD XoffLimit, DWORD XonChar, DWORD XoffChar);
DWORD ICS_RS232SetSignalLine(DWORD port, DWORD line, DWORD state);
WORD ICS_RS232WriteByte(DWORD port, DWORD data);
WORD ICS_RS232WriteBlock(DWORD port, BYTE buffer[], DWORD size);
DWORD ICS_RS232Send(DWORD port, BYTE buffer[], DWORD size);
DWORD ICS_RS232Receive(DWORD port, BYTE buffer[], DWORD size);
void ICS_RS232CloseAllPorts();

typedef void	(__stdcall *lpOut32)(short, short);
typedef short	(__stdcall *lpInp32)(short);
typedef BOOL	(__stdcall *lpIsInpOutDriverOpen)(void);
void LoadInpOut();
void UnloadInpout();

#define J1939Priority(id)                   ((unsigned long)((id >> 26) & 0x7))
#define J1939PGN(id)                        ((unsigned long)((id >> 8) & 0x3FFFF))
// PGN is composed of EDP, DP, PF and PS which follow.
#define J1939ExtDataPage(id)                ((unsigned char)((id >> 25) & 0x1))
#define J1939DataPage(id)                   ((unsigned char)((id >> 24) & 0x1))
#define J1939PduFormat(id)                  ((unsigned char)((id >> 16) & 0xFF))
#define J1939PduSpecific(id)                ((unsigned char)((id >> 8) & 0xFF))
#define J1939SourceAddress(id)              ((unsigned char)(id & 0xFF))
#define J1939DestinationAddress(id)         ((unsigned char)(J1939PduFormat(id) < 240) ? ((id >> 8) & 0xFF) : 0)

#define SetJ1939Priority(id, prio)          (id = (prio << 26) | (id & 0x7FFFFFF))
#define SetJ1939PGN(id, pgn)                (id = (pgn << 8) | (id & 0xFF))
// PGN is composed of EDP, DP, PF and PS which follow.
#define SetJ1939ExtDataPage(id, edp)        (id = (edp << 25) | (id & 0x1DFFFFFF))
#define SetJ1939DataPage(id, dp)            (id = (dp << 24) | (id & 0x1EFFFFFF))
#define SetJ1939PduFormat(id, pf)           (id = (pf << 16) | (id & 0x1F00FFFF))
#define SetJ1939PduSpecific(id, ps)         (id = (ps << 8) | (id & 0x1FFF00FF))
#define SetJ1939SourceAddress(id, sa)       (id = sa | (id & 0x1FFFFF00))
#define SetJ1939DestinationAddress(id, da)  SetJ1939PduSpecific(id, da)

int Spy_TextAPI_W(wchar_t * wcCommand, wchar_t * wcResponse, int iResponseMaxLength);
int Spy_TextAPI(char * szCommand, char * szResponse, int iResponseMaxLength);

#define CM_CALLBACKTYPE_APP_SIGNAL                     0
#define CM_CALLBACKTYPE_MESSAGE                        1
#define CM_CALLBACKTYPE_TIMER                          2
#define CM_CALLBACKTYPE_MESSAGE_MG                     3
#define CM_CALLBACKTYPE_MESSAGE_TX                     4
#define CM_CALLBACKTYPE_BEFORE_MESSAGE_TX   5

#define CM_GETSET_SET_APP_SIGNAL                       0
#define CM_GETSET_GET_APP_SIGNAL                       1
#define CM_GETSET_SET_TMR_VALUE                        2
#define CM_GETSET_GET_TMR_VALUE                        3
#define CM_GETSET_SET_TMR_ENABLE                       4
#define CM_GETSET_GET_TMR_ENABLE                       5
#define CM_GETSET_FBLOCK_START                         6
#define CM_GETSET_FBLOCK_STOP                          7
#define CM_GETSET_FBLOCK_TRIGGER                       8
#define CM_GETSET_FBLOCK_SAVE                          9
#define CM_GETSET_FBLOCK_GET_ISRUNNING                10
#define CM_GETSET_FBLOCK_GET_ISTRIGGERED              11
#define CM_GETSET_FBLOCK_GET_NUMCOLLECTED             12
#define CM_GETSET_MSG_STATS_CLR                       13
#define CM_GETSET_DB_STATS_CLR                        14
#define CM_GETSET_TX_STATS_CLR                        15
#define CM_GETSET_NET_STATS_CLR                       16
#define CM_GETSET_NODE_STATS_CLR                      17
#define CM_GETSET_MSG_STATS_GET                       18
#define CM_GETSET_DB_STATS_GET                        19
#define CM_GETSET_TX_STATS_GET                        20
#define CM_GETSET_NET_STATS_GET                       21
#define CM_GETSET_NODE_STATS_GET                      22
#define CM_GETSET_SET_APP_SIGNAL_TEXT                 23
#define CM_GETSET_GET_APP_SIGNAL_TEXT                 24
#define CM_GETSET_DB_DLC_GET                          25
#define CM_GETSET_DB_NETWORK_GET                      26
#define CM_GETSET_DB_PERIOD_GET                       27
#define CM_GETSET_MSG_DLC_GET                         28
#define CM_GETSET_MSG_NETWORK_GET                     29
#define CM_GETSET_MSG_PERIOD_GET                      30
#define CM_GETSET_TX_DLC_GET                          31
#define CM_GETSET_TX_NETWORK_GET                      32
#define CM_GETSET_TX_PERIOD_GET                       33
#define CM_GETSET_SPY_LOCK                            34
#define CM_GETSET_SPY_UNLOCK                          35
#define CM_GETSET_DIAG_JOB_ISRUNNING                  36
#define CM_GETSET_DIAG_JOB_NumMessagesCollected       37
#define CM_GETSET_DIAG_JOB_Successful                 38
#define CM_GETSET_DIAG_JOB_ECUResponseCount           39
#define CM_GETSET_DIAG_JOB_TotalTimeAbs               40
#define CM_GETSET_DIAG_JOB_Last7FSubFunctionEx78      41
#define CM_GETSET_DIAG_JOB_7FCountEx78                42
#define CM_GETSET_DIAG_JOB_7FCountResponsePending     43
#define CM_GETSET_DIAGJOB_START                       44
#define CM_GETSET_DIAGJOB_STOP                        45
#define CM_GETSET_DIAGJOB_SAVE                        46
#define CM_GETSET_FBLOCK_ADD                          47
#define CM_GETSET_FBLOCK_FIND                         48
#define CM_GETSET_FBLOCK_POSTTRIGGER                  49
#define CM_GETSET_SET_TMR_PERIOD                      50
#define CM_GETSET_GET_TMR_TIME_TO_ELAPSE              51
#define CM_GETSET_GET_TIMENS                          52
#define CM_GETSET_SET_CAN_MODE                        53
#define CM_GETSET_SET_BTR                             54
#define CM_GETSET_STOP_MEASUREMENT                    55
#define CM_GETSET_CLEAR_TRACES                        56
#define CM_GETSET_FBLOCK_PAUSE                        57
#define CM_GETSET_FBLOCK_CONTINUE                     58
#define CM_GETSET_SYS_EXIT                            59
#define CM_GETSET_SYS_MINIMIZE                        60
#define CM_GETSET_GET_DB_NAME                         61
#define CM_GETSET_SET_LIN_WAKEUP_PARMS                62
#define CM_GETSET_SEND_LIN_WAKEUP                     63
#define CM_GETSET_SEND_LIN_SLEEP                      64
#define CM_GETSET_IL_ACTION                           65
#define CM_GETSET_SET_TXSIGNAL                        66
#define CM_GETSET_SET_APP_SIGNAL_AT                   67
#define CM_GETSET_GET_APP_SIGNAL_AT                   68
#define CM_GETSET_SET_APP_SIGNAL_TEXT_AT              69
#define CM_GETSET_GET_APP_SIGNAL_TEXT_AT              70
#define CM_GETSET_GET_NODE_NAME                       71
#define CM_GETSET_GET_NODE_TYPE                       72
#define CM_GETSET_GET_STATION_ADDR                    73
#define CM_GETSET_SET_APP_ACTIVE                      74
#define CM_GETSET_GET_SYS_CONF                        75
#define CM_GETSET_GET_REQ_STATE                       76
#define CM_GETSET_GET_SYS_BUS_REQ                     77
#define CM_GETSET_GET_SYS_FAIL_STATES                 78
#define CM_GETSET_GET_SYS_CURR_FAIL_STATES            79
#define CM_GETSET_GET_SYS_DLL_STATES                  80
#define CM_GETSET_GET_TARGET_CONF                     81
#define CM_GETSET_SET_TARGET_CONF                     82
#define CM_GETSET_GET_IS_WAKEUP_NODE                  83
#define CM_GETSET_GET_IND_ACTIVE_OTHER_BUS            84
#define CM_GETSET_REQ_NET_SHUTDOWN                    85
#define CM_GETSET_REQ_NET_ON_OTHER_BUS                86
#define CM_GETSET_REQ_NET_OFF_OTHER_BUS               87
#define CM_GETSET_TABLE_FBLOCK_ACTIVATE_SLOT		    88
#define CM_GETSET_TABLE_FBLOCK_DEACTIVATE_SLOT		89

#define CM_OSEK_GET_TXID                             501
#define CM_OSEK_SET_TXID                             502
#define CM_OSEK_GET_RXID                             503
#define CM_OSEK_SET_RXID                             504
#define CM_OSEK_GET_USEFC                            505
#define CM_OSEK_SET_USEFC                            506
#define CM_OSEK_SET_0PADDING                         507
#define CM_OSEK_GET_USEEXTID                         508
#define CM_OSEK_SET_USEEXTID                         509
#define CM_OSEK_GET_BS                               510
#define CM_OSEK_SET_BS                               511
#define CM_OSEK_GET_STMIN                            512
#define CM_OSEK_SET_STMIN                            513
#define CM_OSEK_GET_EVAL1FC                          514
#define CM_OSEK_SET_EVAL1FC                          515
#define CM_OSEK_GET_TIMEOUTAR                        516
#define CM_OSEK_SET_TIMEOUTAR                        517
#define CM_OSEK_GET_TIMEOUTAS                        518
#define CM_OSEK_SET_TIMEOUTAS                        519
#define CM_OSEK_GET_TIMEOUTBR                        520
#define CM_OSEK_SET_TIMEOUTBR                        521
#define CM_OSEK_GET_TIMEOUTBS                        522
#define CM_OSEK_SET_TIMEOUTBS                        523
#define CM_OSEK_GET_TIMEOUTCR                        524
#define CM_OSEK_SET_TIMEOUTCR                        525
#define CM_OSEK_GET_1FCBS                            526
#define CM_OSEK_SET_1FCBS                            527
#define CM_OSEK_SET_FIXEDST                          528
#define CM_OSEK_GET_0PATTERN                         529
#define CM_OSEK_SET_0PATTERN                         530
#define CM_OSEK_GET_STARTSN                          531
#define CM_OSEK_SET_STARTSN                          532
#define CM_OSEK_GET_IDFROMADR                        533
#define CM_OSEK_SET_IDFROMADR                        534
#define CM_OSEK_GET_ADRFROMID                        535
#define CM_OSEK_SET_ADRFROMID                        536
#define CM_OSEK_GET_TPBASEADR                        537
#define CM_OSEK_SET_TPBASEADR                        538
#define CM_OSEK_GET_MAXMSGLEN                        539
#define CM_OSEK_SET_MAXMSGLEN                        540
#define CM_OSEK_SET_FCDELAY                          541
#define CM_OSEK_SET_WFTMAX                           542
#define CM_OSEK_GET_DATAREQ                          543
#define CM_OSEK_GET_RXDATA                           544
#define CM_OSEK_GET_SRCADR                           545
#define CM_OSEK_GET_NMSTATUS                         546
#define CM_OSEK_SET_NMSTATUS                         547
#define CM_OSEK_GET_NMCONFIG                         548
#define CM_AUTOSAR_SET_STATUS                        549
#define CM_OSEK_SET_ADDRMODE                         550
#define CM_OSEK_GET_ADDRMODE                         551
#define CM_OSEK_SET_DLCMODE                          552
#define CM_OSEK_SET_CAN                              553
#define CM_OSEK_GET_TGTADR                           554
#define CM_OSEK_SET_TGTADR                           555
#define CM_OSEK_GET_TXMODE                           556
#define CM_OSEK_SET_TXMODE                           557
#define CM_OSEK_SET_MINSTMIN                         558
#define CM_OSEK_GET_ECUNUM                           559
#define CM_OSEK_SET_ECUNUM                           560
#define CM_OSEK_GET_LOFCTADR                         561
#define CM_OSEK_SET_LOFCTADR                         562
#define CM_OSEK_GET_HIFCTADR                         563
#define CM_OSEK_SET_HIFCTADR                         564
#define CM_OSEK_GET_MSGCOUNT                         565
#define CM_OSEK_SET_MSGCOUNT                         566
#define CM_OSEK_GET_TXPRIO                           567
#define CM_OSEK_SET_TXPRIO                           568
#define CM_OSEK_GET_FFPRIO                           569
#define CM_OSEK_SET_FFPRIO                           570
#define CM_OSEK_GET_FCPRIO                           571
#define CM_OSEK_SET_FCPRIO                           572
#define CM_OSEK_GET_USEALLAE                         573
#define CM_OSEK_SET_USEALLAE                         574
#define CM_OSEK_GET_TXTOTHRESHOLD                    575
#define CM_OSEK_SET_TXTOTHRESHOLD                    576
#define CM_OSEK_GET_RECENTAE                         577
#define CM_OSEK_SET_MAXCFBURST                       578
#define CM_OSEK_GET_ADREXT                           579
#define CM_OSEK_SET_ADREXT                           580
#define CM_OSEK_CONNECTREQ                           581
#define CM_OSEK_GET_CAN                              582
#define CM_OSEK_GET_0PADDING                         583
#define CM_OSEK_GET_FIXED_DLC                        584
#define CM_GET_VIEWCOUNT						   	   600
#define CM_GET_VIEWHANDLE					   	   	   601
#define CM_GET_VIEWTYPE							   602
#define CM_GET_VIEWPROCADDRESS					   603
#define CM_SET_SHOWVIEW							   604
#define CM_SET_HIDEVIEW							   605
#define CM_GET_VIEWISVISIBLE					   	   606
#define CM_SET_SHOWVIEWBYTYPE			               607

// Send this struct to CM_GET_VIEWPROCADDRESS
typedef struct _stGetViewProcAddressArgs
{
	void* InForm;
	const char* InFunctionName;
	void* OutFunctionPtr;
} stGetViewProcAddressArgs;

// Send this struct to CM_GET_VIEWTYPE
typedef struct _stGetViewTypeArgs
{
	void* InForm;
	int OutType;
} stGetViewTypeArgs;

// Send this struct to CM_GET_VIEWISVISIBLE
typedef struct _stGetViewIsVisibleArgs
{
	void* InForm;
	int OutVisible;
} stGetViewIsVisibleArgs;

// Typedefs for function pointers returned by CM_GET_VIEWPROCADDRESS
typedef int (_stdcall *VideoFrameReview_GetMaxCamCount)(void* pForm);
typedef int (_stdcall *VideoFrameReview_CamIsVisible)(void* pForm, int camIndex);
typedef void (_stdcall *VideoFrameReview_AddRect)(void* pForm, int cam, float percentLeft, float percentTop, float percentRight, float percentBottom, int color, int thickness);
typedef void (_stdcall *VideoFrameReview_ClearRects)(void* pForm, int camIndex);
typedef int (_stdcall *VideoFrameReview_AddText)(void* pForm, int cam, const char* text, float percentLeft, float percentTop, int color, int size);
typedef void (_stdcall *VideoFrameReview_UpdateText)(void* pForm, int cam, int index, const char* text, float percentLeft, float percentTop, int color, int size);
typedef void (_stdcall *VideoFrameReview_ClearTexts)(void* pForm, int cam);
typedef int (_stdcall *VideoFrameReview_AddBitmap)(void* pForm, int cam, float percentLeft, float percentTop, float percentRight, float percentBottom, int visible, const wchar_t* imagePath);
typedef void (_stdcall *VideoFrameReview_UpdateBitmap)(void* pForm, int cam, int index, float percentLeft, float percentTop, float percentRight, float percentBottom, int visible);
typedef void (_stdcall *VideoFrameReview_ClearBitmaps)(void* pForm, int cam);

#define ATTR_LIN_TX_SENDSLAVE                       0x10
#define ATTR_LIN_TX_CLASSIC_CHECKSUM                0x20
#define ATTR_LIN_TX_SEND_BREAK_ONLY                 0x40
#define ATTR_LIN_TX_SEND_HDR_ONLY                   0x80
#define ATTR_ACTIVE_INIT                            0x10
#define ATTR_CAN_29BIT_ID_FRAME                     0x20
#define ATTR_CAN_REMOTE_FRAME                       0x40
#define ATTR_CAN_TX_HIGH_VOLTAGE                    0x80
#define ATTR_ALL_RX_TRANSMIT                           1
#define ATTR_ALL_RX_ERROR                              2
#define ATTR_LIN_RX_MASTER_TX                      0x100
#define ATTR_LIN_RX_SLAVE_TX                       0x200
#define ATTR_CANFD_FRAME                          0x1000
#define ATTR_CANFD_ESI                            0x2000
#define ATTR_CANFD_BRS                            0x4000

// Spy_ErrorState iErrorBitfield flags
#define CAN_ERROR_STATUS_ACTIVE                   0x0000
#define CAN_ERROR_STATUS_TXRX_WARNING             0x0001  // EWARN: Transmitter or Receiver in Error State Warning bit
#define CAN_ERROR_STATUS_RX_WARNING               0x0002  // RXWAR: Receiver in Error State Warning bit
#define CAN_ERROR_STATUS_TX_WARNING               0x0004  // TXWAR: Transmitter in Error State Warning bit
#define CAN_ERROR_STATUS_RX_PASSIVE               0x0008  // RXBP: Receiver in Error State Bus Passive bit
#define CAN_ERROR_STATUS_TX_PASSIVE               0x0010  // TXBP: Transmitter in Error State Bus Passive bit
#define CAN_ERROR_STATUS_TX_BUS_OFF               0x0020  // TXBO: Transmitter in Error State Bus Off bit

#define SPY_CTL_PROP_ENABLE                       1
#define SPY_CTL_PROP_SET_BACKGROUND               2
#define SPY_CTL_PROP_SET_FOREGROUND               3
#define SPY_CTL_PROP_SET_CAPTION                  4
#define SPY_CTL_PROP_SET_LEFT                     5
#define SPY_CTL_PROP_SET_TOP                      6
#define SPY_CTL_PROP_SET_WIDTH                    7
#define SPY_CTL_PROP_SET_HEIGHT                   8
#define SPY_CTL_PROP_SET_TRANSPARENT              9
#define SPY_CTL_PROP_SET_FONT_NAME               10
#define SPY_CTL_PROP_SET_FONT_SIZE               11

struct stCallBackPointers
{
    void * pRegisterCallBack;
    void * pGetSetValueCallBack;
    void * pTransmitMessageCallBack;
    void * pOutputWindowCallBack;
    void * pTextAPICallBack;
    void * pGetSignalValue;
    void * pDecodeSignalValue;
    void * pTransmitMessagesFromSignalValues;
    void * pFindIndexForObjectFromNameCallBack;
    void * pShowPanelCallBack;
    void * pMessageGenericInit;
    void * pGetEcuCount;
    void * pGetMemoryBlockCount;
    void * pGetMemoryBlockInfo;
    void * pGetMemoryBlockData;
    void * pSetMemoryBlockData;
    void * pMessageRawInit;
    void * pSignalPhysicalToRaw;
    void * pTransmitMessagesFromRawSignalValues;
    void * pGetMessageName;
    void * pSetControlProp;
    void * pUpdateMessageSignalsFromBytes;
    void * pUpdateBytesFromSignals;
    void * pUpdateBytesFromRawSignals;
};
extern void (* CM_RegisterCallback) (unsigned int uiHandle, unsigned short iValueType, unsigned short iIndex, void * pCallBackPointer) ;
extern void (* CM_GetSetValue) (unsigned int uiHandle, unsigned short iValueType, unsigned short iIndex, void * pValueToSet) ;
extern int  (* CM_TextAPI) (unsigned int uiHandle, wchar_t * pCommand, wchar_t * pResponse, int iResponseMaxLength) ;
extern int  (* CM_OutputWindow) (unsigned int uiHandle, wchar_t * p_TextToWrite, int iColor, int iLength) ;
extern int  (* CM_TransmitMessage) (unsigned int  uiHandle, int iNetwork,int iID, int iNumDataBytes,int iBitField,unsigned char * p_btData);
extern int  (* CM_GetSignalValue) (unsigned int uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,unsigned short iSignalIndex,void * pValueToSet);
extern int  (* CM_TxFromSignals) (unsigned int uiHandle, unsigned short iMessageType,
                       unsigned short iMessageIndex, unsigned char * bt_DefaultBytes, int iByteCount,
                       int iNetworkIndex, void * pSignalValues,
                       int iNumSignalCount);
extern int  (* CM_TxFromRawSignals) (unsigned int uiHandle, unsigned short iMessageType,
                       unsigned short iMessageIndex, unsigned char * bt_DefaultBytes, int iByteCount,
                       int iNetworkIndex, void * pSignalValues,
                       int iNumSignalCount);
extern int  (* CM_UpdateMessageSignalsFromBytes) (unsigned int uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
                       unsigned char * p_btData, int iNumDataBytes);
extern int  (* CM_UpdateBytesFromSignals) (unsigned int uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
                       double * p_dSignals, int dSignalMaxCount, unsigned char * p_btData, int iNumDataBytes);
extern int  (* CM_UpdateBytesFromRawSignals) (unsigned int uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
                       uint64 * p_iSignals, int dSignalMaxCount, unsigned char * p_btData, int iNumDataBytes);
extern int  (* CM_FindIndexForObjectFromName) (unsigned int uiHandle, int iObjectType,wchar_t * pName, int * p_iObjectIndex);
extern int  (* CM_GetMessageName) (unsigned int uiHandle, int iMessageId, int iMessageContext, wchar_t * pName, int iBufferSize);
extern int  (* CM_ShowPanel) (unsigned int uiHandle, wchar_t * pWindowName, wchar_t * pPanelName);
extern int  (* CM_SetControlProperty) (unsigned int uiHandle, wchar_t * pPanelName, wchar_t * pWindowName, int prop, void *pValue);
extern int  (* CM_MessageGenericInit) (unsigned int uiHandle, unsigned short iMessageType,
                       unsigned short iMessageIndex, void * p_MessageStats, int * p_iNetworkID,
                       int * p_iNumDataBytes, int  p_iNumDataMax, int * p_iPeriodMs, int * p_iID,
                       int * p_iBitField, unsigned char * p_btData, double * p_dSignals, int dSignalMaxCount,
                       int * p_iActualSignalMaxCount,__int64 * p_iTimeStampNanoSecondsHW,unsigned int * p_iTimeStampMillisecondsOS);
extern int  (* CM_MessageRawInit) (unsigned int uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
                       uint64 * p_dSignals, int dSignalMaxCount, int * p_iActualSignalMaxCount);
extern uint64 (* CM_SignalPhysicalToRaw) (unsigned int uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
                       unsigned short iSignalIndex, double dPhysicalValue);
extern int  (* CM_GetEcuCount) (unsigned int uiHandle);
extern int  (* CM_GetMemoryBlockCount) (unsigned int uiHandle, int ecu);
extern int  (* CM_GetMemoryBlockInfo) (unsigned int uiHandle, int ecu, int block, unsigned int *address, unsigned int *size);
extern int  (* CM_GetMemoryBlockData) (unsigned int uiHandle, int ecu, int block, unsigned char *buffer, unsigned int address, unsigned int size);
extern int  (* CM_SetMemoryBlockData) (unsigned int uiHandle, int ecu, int block, unsigned char *buffer, unsigned int address, unsigned int size);

#define CAN_ID_EXTENDED_BIT   0x80000000
#define isStdId(id) ((id & CAN_ID_EXTENDED_BIT) == 0)
#define isExtId(id) ((id & CAN_ID_EXTENDED_BIT) == CAN_ID_EXTENDED_BIT)
#define mkExtId(id) (id | CAN_ID_EXTENDED_BIT)
#define mkStdId(id) (id & (~CAN_ID_EXTENDED_BIT))
#define valOfId(id) ((long)id)
void SetUseExtendedIdBit();

#define GMLAN_SOURCE_MASK 0xff
#define GMLAN_PID_MASK    0xffff
#define GMLAND_PID_SHIFT  8
#define GMLAN_PRIO_MASK   0x07
#define GMLAND_PRIO_SHIFT 26
#define gmlanSetSourceId(id, source) (id |= (source & GMLAN_SOURCE_MASK))
#define gmlanSetPid(id, pid) (id |= ((pid & GMLAN_PID_MASK) << GMLAND_PID_SHIFT))
#define gmlanSetPrio(id, prio) (id |= ((prio & GMLAN_PRIO_MASK) << GMLAND_PRIO_SHIFT))
#define gmlanGetSourceId(id) (id & GMLAN_SOURCE_MASK)
#define gmlanGetPid(id) ((id >> GMLAND_PID_SHIFT) & GMLAN_PID_MASK)
#define gmlanGetPrio(id) ((id >> GMLAND_PRIO_SHIFT) & GMLAN_PRIO_MASK)
#define gmlanId(id, source) (id | (source & GMLAN_SOURCE_MASK))

int getStartDelay();
void setStartDelay(int delay);

void SpyShowPanel(char * pWindowName, char * pPanelName);
void SpyShowPanelW(wchar_t * pWindowName, wchar_t * pPanelName);
void SpySetControlProperty(char * pPanelName, char * pControlTag, int prop, void *pValue);
void SpySetControlPropertyW(wchar_t * pPanelName, wchar_t * pControlTag, int prop, void *pValue);
void Spy_Lock();
void Spy_Unlock();
int GetMessageName(int iMessageId, int iMessageContext, char * pName, int iBufferSize);
int GetMessageNameW(int iMessageId, int iMessageContext, wchar_t * pName, int iBufferSize);
double AS_Get(int index);
void AS_Set(int index, double dValue);
double AS_GetAt(int index, int element);
void AS_SetAt(int index, int element, double dValue);
int AS_GetText(int nIndex, void * szValue, int nLength);
int AS_SetText(int nIndex, void * szValue, int nLength);
int AS_GetTextW(int index, wchar_t * szValue);
void SpySetTxSignal(unsigned int iMessageIndex, unsigned int iSignalIndex, double dValue);
void SpySetTxSignalRaw(unsigned int iMessageIndex, unsigned int iSignalIndex, __int64 nValue);
void SpySetTxEvent(unsigned int iMessageIndex);
int AS_GetTextAtW(int index, int element, wchar_t * szValue);
int AS_SetTextAtW(int index, int element, wchar_t * szValue);
int SpyViewGetCount();
void* SpyViewGetHandle(int index);
int SpyViewGetType(void* pView);
void SpyViewShow(void* pView);
void SpyViewHide(void* pView);
int SpyViewIsVisible(void* pView);
void* SpyViewShowByType(int type);
void* SpyViewGetProcAddress(void* pView, const char* szProcName);

typedef struct {
    unsigned int iSignal;    /// signal to set
    unsigned int iType;      /// 0 physical, 1 raw
    union {
        double dValue;           /// value 
        __int64 nValue;
    };
} TxSetSignal;

// Network Statistics
typedef struct {
    unsigned int iCount;  /// count of messages on network
    unsigned int iRate; /// messages per second
    double dPercentUse; /// current bus utilization 
    unsigned int iMaxRate;    /// maximum messages per second
    double dMaxPercentUse;   /// maximum bus utilization
    unsigned int iErrorCount;   /// number of errors on a network
    unsigned int iTxCount;       /// number of messages transmitted on a network
    unsigned int iErrorRate; /// errors per second
    unsigned int iTxRate;        /// transmissions per second
    unsigned int iTxBufferFill;  /// current network buffer fill level
    unsigned int iCANTxErrCount;  /// transmit CAN errors
    unsigned int iCANRxErrCount;  /// receive CAN errors
} NetworkStats; 
int Spy_TranslateNetwork(int nNetworkOffset);
int Spy_UntranslateNetwork(int nNetwork);
int Spy_NetworksInUse();
int Spy_LINIndex(int iNetwork);

// network index variables - identify networks in vspy
extern int NET_HS_CAN;
void NET_HS_CAN_ClearStats();
void NET_HS_CAN_GetStats(NetworkStats * p_NetworkStats);
extern int NET_MS_CAN;
void NET_MS_CAN_ClearStats();
void NET_MS_CAN_GetStats(NetworkStats * p_NetworkStats);
extern int NET_SW_CAN;
void NET_SW_CAN_ClearStats();
void NET_SW_CAN_GetStats(NetworkStats * p_NetworkStats);
extern int NET_J1850_VPW;
void NET_J1850_VPW_ClearStats();
void NET_J1850_VPW_GetStats(NetworkStats * p_NetworkStats);
extern int NET_ISO9141_KW2K;
void NET_ISO9141_KW2K_ClearStats();
void NET_ISO9141_KW2K_GetStats(NetworkStats * p_NetworkStats);
extern int NET_LSFT_CAN;
void NET_LSFT_CAN_ClearStats();
void NET_LSFT_CAN_GetStats(NetworkStats * p_NetworkStats);
extern int NET_J1850_PWM;
void NET_J1850_PWM_ClearStats();
void NET_J1850_PWM_GetStats(NetworkStats * p_NetworkStats);
extern int NET_J1708;
void NET_J1708_ClearStats();
void NET_J1708_GetStats(NetworkStats * p_NetworkStats);
extern int NET_neoVI;
void NET_neoVI_ClearStats();
void NET_neoVI_GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN2__neoVI_3G_;
void NET_HS_CAN2__neoVI_3G__ClearStats();
void NET_HS_CAN2__neoVI_3G__GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN3__neoVI_3G_;
void NET_HS_CAN3__neoVI_3G__ClearStats();
void NET_HS_CAN3__neoVI_3G__GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN2__neoVI_3G_;
void NET_LIN2__neoVI_3G__ClearStats();
void NET_LIN2__neoVI_3G__GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN3__neoVI_3G_;
void NET_LIN3__neoVI_3G__ClearStats();
void NET_LIN3__neoVI_3G__GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN4__neoVI_3G_;
void NET_LIN4__neoVI_3G__ClearStats();
void NET_LIN4__neoVI_3G__GetStats(NetworkStats * p_NetworkStats);
extern int NET_CGI__neoVI_3G_;
void NET_CGI__neoVI_3G__ClearStats();
void NET_CGI__neoVI_3G__GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN;
void NET_LIN_ClearStats();
void NET_LIN_GetStats(NetworkStats * p_NetworkStats);
extern int NET_ISO9141_KW2K_2;
void NET_ISO9141_KW2K_2_ClearStats();
void NET_ISO9141_KW2K_2_GetStats(NetworkStats * p_NetworkStats);
extern int NET_ISO9141_KW2K_3;
void NET_ISO9141_KW2K_3_ClearStats();
void NET_ISO9141_KW2K_3_GetStats(NetworkStats * p_NetworkStats);
extern int NET_ISO9141_KW2K_4;
void NET_ISO9141_KW2K_4_ClearStats();
void NET_ISO9141_KW2K_4_GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN4;
void NET_HS_CAN4_ClearStats();
void NET_HS_CAN4_GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN5;
void NET_HS_CAN5_ClearStats();
void NET_HS_CAN5_GetStats(NetworkStats * p_NetworkStats);
extern int NET_UART__neoVI_3G_;
void NET_UART__neoVI_3G__ClearStats();
void NET_UART__neoVI_3G__GetStats(NetworkStats * p_NetworkStats);
extern int NET_UART2__neoVI_3G_;
void NET_UART2__neoVI_3G__ClearStats();
void NET_UART2__neoVI_3G__GetStats(NetworkStats * p_NetworkStats);
extern int NET_neoMOST;
void NET_neoMOST_ClearStats();
void NET_neoMOST_GetStats(NetworkStats * p_NetworkStats);
extern int NET_MOST__VNET_A_;
void NET_MOST__VNET_A__ClearStats();
void NET_MOST__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_FlexRay1A__VNET_A_;
void NET_FlexRay1A__VNET_A__ClearStats();
void NET_FlexRay1A__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_FlexRay1B__VNET_A_;
void NET_FlexRay1B__VNET_A__ClearStats();
void NET_FlexRay1B__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_FlexRay2A__VNET_A_;
void NET_FlexRay2A__VNET_A__ClearStats();
void NET_FlexRay2A__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_FlexRay2B__VNET_A_;
void NET_FlexRay2B__VNET_A__ClearStats();
void NET_FlexRay2B__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN__VNET_A_;
void NET_HS_CAN__VNET_A__ClearStats();
void NET_HS_CAN__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_MS_CAN__VNET_A_;
void NET_MS_CAN__VNET_A__ClearStats();
void NET_MS_CAN__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_SW_CAN__VNET_A_;
void NET_SW_CAN__VNET_A__ClearStats();
void NET_SW_CAN__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_J1850_VPW__VNET_A_;
void NET_J1850_VPW__VNET_A__ClearStats();
void NET_J1850_VPW__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_LSFT_CAN__VNET_A_;
void NET_LSFT_CAN__VNET_A__ClearStats();
void NET_LSFT_CAN__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_J1708__VNET_A_;
void NET_J1708__VNET_A__ClearStats();
void NET_J1708__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_neoVI__VNET_A_;
void NET_neoVI__VNET_A__ClearStats();
void NET_neoVI__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN2__VNET_A_;
void NET_HS_CAN2__VNET_A__ClearStats();
void NET_HS_CAN2__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN3__VNET_A_;
void NET_HS_CAN3__VNET_A__ClearStats();
void NET_HS_CAN3__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN__VNET_A_;
void NET_LIN__VNET_A__ClearStats();
void NET_LIN__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN2__VNET_A_;
void NET_LIN2__VNET_A__ClearStats();
void NET_LIN2__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN3__VNET_A_;
void NET_LIN3__VNET_A__ClearStats();
void NET_LIN3__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN4__VNET_A_;
void NET_LIN4__VNET_A__ClearStats();
void NET_LIN4__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_CGI__VNET_A_;
void NET_CGI__VNET_A__ClearStats();
void NET_CGI__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_ISO9141_KW2K__VNET_A_;
void NET_ISO9141_KW2K__VNET_A__ClearStats();
void NET_ISO9141_KW2K__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_ISO9141_KW2K_2__VNET_A_;
void NET_ISO9141_KW2K_2__VNET_A__ClearStats();
void NET_ISO9141_KW2K_2__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_ISO9141_KW2K_3__VNET_A_;
void NET_ISO9141_KW2K_3__VNET_A__ClearStats();
void NET_ISO9141_KW2K_3__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_ISO9141_KW2K_4__VNET_A_;
void NET_ISO9141_KW2K_4__VNET_A__ClearStats();
void NET_ISO9141_KW2K_4__VNET_A__GetStats(NetworkStats * p_NetworkStats);

void SpyAppSig_CallAllHandlers();
void SpyAppSig_AS_appSig_mpiRead_bytesBMPNAC(double dValue);
void SpyAppSig_AS_appSig_mpiRead_bytesDUNS(double dValue);
void SpyAppSig_AS_appSig_mpiRead_bytesECUID(double dValue);
void SpyAppSig_AS_appSig_mpiRead_bytesEMPNAC(double dValue);
void SpyAppSig_AS_appSig_mpiRead_bytesMTC(double dValue);
void SpyAppSig_AS_appSig_mpiRead_bytesVPPS(double dValue);
void SpyAppSig_AS_appSig_mpiWrite_BMPNAC(double dValue);
void SpyAppSig_AS_appSig_mpiWrite_EMPNAC(double dValue);
void SpyAppSig_AS_appSig_mpiWrite_MTC(double dValue);
void SpyAppSig_AS_appSig_sapaWrite_bytesSeedKey(double dValue);
void SpyAppSig_AS_appSig_sapaWrite_bytesSeed(double dValue);
void SpyAppSig_AS_appSig_sapaRead_bytesSeed(double dValue);

// Application Signals
extern int AS_appSig_C_targetValueTypeMin_Index; // sig22
#define AS_appSig_C_targetValueTypeMin_Get() AS_Get(AS_appSig_C_targetValueTypeMin_Index)
#define AS_appSig_C_targetValueTypeMin_Set(dValue) AS_Set(AS_appSig_C_targetValueTypeMin_Index, dValue)

extern int AS_appSig_C_targetValueTypeNormal_Index; // sig23
#define AS_appSig_C_targetValueTypeNormal_Get() AS_Get(AS_appSig_C_targetValueTypeNormal_Index)
#define AS_appSig_C_targetValueTypeNormal_Set(dValue) AS_Set(AS_appSig_C_targetValueTypeNormal_Index, dValue)

extern int AS_appSig_C_targetValueTypeMax_Index; // sig24
#define AS_appSig_C_targetValueTypeMax_Get() AS_Get(AS_appSig_C_targetValueTypeMax_Index)
#define AS_appSig_C_targetValueTypeMax_Set(dValue) AS_Set(AS_appSig_C_targetValueTypeMax_Index, dValue)

extern int AS_appSig_targetValueType_Index; // sig21
#define AS_appSig_targetValueType_Get() AS_Get(AS_appSig_targetValueType_Index)
#define AS_appSig_targetValueType_Set(dValue) AS_Set(AS_appSig_targetValueType_Index, dValue)

extern int AS_appSig_DrvHCSMInd1_Index; // sig4
#define AS_appSig_DrvHCSMInd1_Get() AS_Get(AS_appSig_DrvHCSMInd1_Index)
#define AS_appSig_DrvHCSMInd1_Set(dValue) AS_Set(AS_appSig_DrvHCSMInd1_Index, dValue)

extern int AS_appSig_C_testDiagStepsDelay_Index; // sig10
#define AS_appSig_C_testDiagStepsDelay_Get() AS_Get(AS_appSig_C_testDiagStepsDelay_Index)
#define AS_appSig_C_testDiagStepsDelay_Set(dValue) AS_Set(AS_appSig_C_testDiagStepsDelay_Index, dValue)

extern int AS_appSig_C_autoDiagStepsDelay_Index; // sig11
#define AS_appSig_C_autoDiagStepsDelay_Get() AS_Get(AS_appSig_C_autoDiagStepsDelay_Index)
#define AS_appSig_C_autoDiagStepsDelay_Set(dValue) AS_Set(AS_appSig_C_autoDiagStepsDelay_Index, dValue)

extern int AS_appSig_C_responseTimeout_Index; // sig12
#define AS_appSig_C_responseTimeout_Get() AS_Get(AS_appSig_C_responseTimeout_Index)
#define AS_appSig_C_responseTimeout_Set(dValue) AS_Set(AS_appSig_C_responseTimeout_Index, dValue)

extern int AS_appSig_steps_currRawValue_Index; // sig30
#define AS_appSig_steps_currRawValue_Get() AS_Get(AS_appSig_steps_currRawValue_Index)
#define AS_appSig_steps_currRawValue_Set(dValue) AS_Set(AS_appSig_steps_currRawValue_Index, dValue)
#define AS_appSig_steps_currRawValue_GetAt(offset) AS_GetAt(AS_appSig_steps_currRawValue_Index, offset)
#define AS_appSig_steps_currRawValue_SetAt(offset, dValue) AS_SetAt(AS_appSig_steps_currRawValue_Index, offset, dValue)
#define AS_appSig_steps_currRawValue_GetSize() AS_GetAt(AS_appSig_steps_currRawValue_Index, -1)
#define AS_appSig_steps_currRawValue_SetSize(dValue) AS_SetAt(AS_appSig_steps_currRawValue_Index, -1, dValue)
#define AS_appSig_steps_currRawValue_GetText(szValue) AS_GetText(AS_appSig_steps_currRawValue_Index, szValue, -1)
#define AS_appSig_steps_currRawValue_SetText(szValue) AS_SetText(AS_appSig_steps_currRawValue_Index, szValue, -1)
#define AS_appSig_steps_currRawValue_GetTextLen(szValue, len) AS_GetText(AS_appSig_steps_currRawValue_Index, szValue, len)
#define AS_appSig_steps_currRawValue_SetTextLen(szValue, len) AS_SetText(AS_appSig_steps_currRawValue_Index, szValue, len)

extern int AS_appSig_steps_targetRawValue_Index; // sig31
#define AS_appSig_steps_targetRawValue_Get() AS_Get(AS_appSig_steps_targetRawValue_Index)
#define AS_appSig_steps_targetRawValue_Set(dValue) AS_Set(AS_appSig_steps_targetRawValue_Index, dValue)
#define AS_appSig_steps_targetRawValue_GetAt(offset) AS_GetAt(AS_appSig_steps_targetRawValue_Index, offset)
#define AS_appSig_steps_targetRawValue_SetAt(offset, dValue) AS_SetAt(AS_appSig_steps_targetRawValue_Index, offset, dValue)
#define AS_appSig_steps_targetRawValue_GetSize() AS_GetAt(AS_appSig_steps_targetRawValue_Index, -1)
#define AS_appSig_steps_targetRawValue_SetSize(dValue) AS_SetAt(AS_appSig_steps_targetRawValue_Index, -1, dValue)
#define AS_appSig_steps_targetRawValue_GetText(szValue) AS_GetText(AS_appSig_steps_targetRawValue_Index, szValue, -1)
#define AS_appSig_steps_targetRawValue_SetText(szValue) AS_SetText(AS_appSig_steps_targetRawValue_Index, szValue, -1)
#define AS_appSig_steps_targetRawValue_GetTextLen(szValue, len) AS_GetText(AS_appSig_steps_targetRawValue_Index, szValue, len)
#define AS_appSig_steps_targetRawValue_SetTextLen(szValue, len) AS_SetText(AS_appSig_steps_targetRawValue_Index, szValue, len)

extern int AS_appSig_steps_isPassed_Index; // sig32
#define AS_appSig_steps_isPassed_Get() AS_Get(AS_appSig_steps_isPassed_Index)
#define AS_appSig_steps_isPassed_Set(dValue) AS_Set(AS_appSig_steps_isPassed_Index, dValue)
#define AS_appSig_steps_isPassed_GetAt(offset) AS_GetAt(AS_appSig_steps_isPassed_Index, offset)
#define AS_appSig_steps_isPassed_SetAt(offset, dValue) AS_SetAt(AS_appSig_steps_isPassed_Index, offset, dValue)
#define AS_appSig_steps_isPassed_GetSize() AS_GetAt(AS_appSig_steps_isPassed_Index, -1)
#define AS_appSig_steps_isPassed_SetSize(dValue) AS_SetAt(AS_appSig_steps_isPassed_Index, -1, dValue)
#define AS_appSig_steps_isPassed_GetText(szValue) AS_GetText(AS_appSig_steps_isPassed_Index, szValue, -1)
#define AS_appSig_steps_isPassed_SetText(szValue) AS_SetText(AS_appSig_steps_isPassed_Index, szValue, -1)
#define AS_appSig_steps_isPassed_GetTextLen(szValue, len) AS_GetText(AS_appSig_steps_isPassed_Index, szValue, len)
#define AS_appSig_steps_isPassed_SetTextLen(szValue, len) AS_SetText(AS_appSig_steps_isPassed_Index, szValue, len)

extern int AS_appSig_C_bool_targetValue_Index; // sig36
#define AS_appSig_C_bool_targetValue_Get() AS_Get(AS_appSig_C_bool_targetValue_Index)
#define AS_appSig_C_bool_targetValue_Set(dValue) AS_Set(AS_appSig_C_bool_targetValue_Index, dValue)

extern int AS_appSig_C_temp_targetRawValueMin_Index; // sig37
#define AS_appSig_C_temp_targetRawValueMin_Get() AS_Get(AS_appSig_C_temp_targetRawValueMin_Index)
#define AS_appSig_C_temp_targetRawValueMin_Set(dValue) AS_Set(AS_appSig_C_temp_targetRawValueMin_Index, dValue)

extern int AS_appSig_C_temp_targetRawValueNormal_Index; // sig38
#define AS_appSig_C_temp_targetRawValueNormal_Get() AS_Get(AS_appSig_C_temp_targetRawValueNormal_Index)
#define AS_appSig_C_temp_targetRawValueNormal_Set(dValue) AS_Set(AS_appSig_C_temp_targetRawValueNormal_Index, dValue)

extern int AS_appSig_C_temp_targetRawValueMax_Index; // sig39
#define AS_appSig_C_temp_targetRawValueMax_Get() AS_Get(AS_appSig_C_temp_targetRawValueMax_Index)
#define AS_appSig_C_temp_targetRawValueMax_Set(dValue) AS_Set(AS_appSig_C_temp_targetRawValueMax_Index, dValue)

extern int AS_appSig_C_step15_targetRawValue_Index; // sig33
#define AS_appSig_C_step15_targetRawValue_Get() AS_Get(AS_appSig_C_step15_targetRawValue_Index)
#define AS_appSig_C_step15_targetRawValue_Set(dValue) AS_Set(AS_appSig_C_step15_targetRawValue_Index, dValue)

extern int AS_appSig_C_step16_targetRawValue_Index; // sig34
#define AS_appSig_C_step16_targetRawValue_Get() AS_Get(AS_appSig_C_step16_targetRawValue_Index)
#define AS_appSig_C_step16_targetRawValue_Set(dValue) AS_Set(AS_appSig_C_step16_targetRawValue_Index, dValue)

extern int AS_appSig_C_step16_targetPhyValueStr_Index; // sig53
#define AS_appSig_C_step16_targetPhyValueStr_Get() AS_Get(AS_appSig_C_step16_targetPhyValueStr_Index)
#define AS_appSig_C_step16_targetPhyValueStr_Set(dValue) AS_Set(AS_appSig_C_step16_targetPhyValueStr_Index, dValue)
#define AS_appSig_C_step16_targetPhyValueStr_GetTextW(szValue) AS_GetTextW(AS_appSig_C_step16_targetPhyValueStr_Index, szValue)
#define AS_appSig_C_step16_targetPhyValueStr_SetTextW(szValue) CM_GetSetValue(g_uiHandle, CM_GETSET_SET_APP_SIGNAL_TEXT, AS_appSig_C_step16_targetPhyValueStr_Index, szValue)
#define AS_appSig_C_step16_targetPhyValueStr_GetText(szValue) AS_GetText(AS_appSig_C_step16_targetPhyValueStr_Index, szValue, -1)
#define AS_appSig_C_step16_targetPhyValueStr_SetText(szValue) AS_SetText(AS_appSig_C_step16_targetPhyValueStr_Index, szValue, -1)
#define AS_appSig_C_step16_targetPhyValueStr_GetTextLen(szValue, len) AS_GetText(AS_appSig_C_step16_targetPhyValueStr_Index, szValue, len)
#define AS_appSig_C_step16_targetPhyValueStr_SetTextLen(szValue, len) AS_SetText(AS_appSig_C_step16_targetPhyValueStr_Index, szValue, len)

extern int AS_appSig_C_step17_targetRawValue_Index; // sig35
#define AS_appSig_C_step17_targetRawValue_Get() AS_Get(AS_appSig_C_step17_targetRawValue_Index)
#define AS_appSig_C_step17_targetRawValue_Set(dValue) AS_Set(AS_appSig_C_step17_targetRawValue_Index, dValue)

extern int AS_appSig_C_step17_targetPhyValueStr_Index; // sig61
#define AS_appSig_C_step17_targetPhyValueStr_Get() AS_Get(AS_appSig_C_step17_targetPhyValueStr_Index)
#define AS_appSig_C_step17_targetPhyValueStr_Set(dValue) AS_Set(AS_appSig_C_step17_targetPhyValueStr_Index, dValue)
#define AS_appSig_C_step17_targetPhyValueStr_GetTextW(szValue) AS_GetTextW(AS_appSig_C_step17_targetPhyValueStr_Index, szValue)
#define AS_appSig_C_step17_targetPhyValueStr_SetTextW(szValue) CM_GetSetValue(g_uiHandle, CM_GETSET_SET_APP_SIGNAL_TEXT, AS_appSig_C_step17_targetPhyValueStr_Index, szValue)
#define AS_appSig_C_step17_targetPhyValueStr_GetText(szValue) AS_GetText(AS_appSig_C_step17_targetPhyValueStr_Index, szValue, -1)
#define AS_appSig_C_step17_targetPhyValueStr_SetText(szValue) AS_SetText(AS_appSig_C_step17_targetPhyValueStr_Index, szValue, -1)
#define AS_appSig_C_step17_targetPhyValueStr_GetTextLen(szValue, len) AS_GetText(AS_appSig_C_step17_targetPhyValueStr_Index, szValue, len)
#define AS_appSig_C_step17_targetPhyValueStr_SetTextLen(szValue, len) AS_SetText(AS_appSig_C_step17_targetPhyValueStr_Index, szValue, len)

extern int AS_appSig_C_step18_targetRawValue_Index; // sig9
#define AS_appSig_C_step18_targetRawValue_Get() AS_Get(AS_appSig_C_step18_targetRawValue_Index)
#define AS_appSig_C_step18_targetRawValue_Set(dValue) AS_Set(AS_appSig_C_step18_targetRawValue_Index, dValue)

extern int AS_appSig_C_step19_targetRawValueMin_Index; // sig19
#define AS_appSig_C_step19_targetRawValueMin_Get() AS_Get(AS_appSig_C_step19_targetRawValueMin_Index)
#define AS_appSig_C_step19_targetRawValueMin_Set(dValue) AS_Set(AS_appSig_C_step19_targetRawValueMin_Index, dValue)

extern int AS_appSig_C_step19_targetRawValueNormal_Index; // sig18
#define AS_appSig_C_step19_targetRawValueNormal_Get() AS_Get(AS_appSig_C_step19_targetRawValueNormal_Index)
#define AS_appSig_C_step19_targetRawValueNormal_Set(dValue) AS_Set(AS_appSig_C_step19_targetRawValueNormal_Index, dValue)

extern int AS_appSig_C_step19_targetRawValueMax_Index; // sig17
#define AS_appSig_C_step19_targetRawValueMax_Get() AS_Get(AS_appSig_C_step19_targetRawValueMax_Index)
#define AS_appSig_C_step19_targetRawValueMax_Set(dValue) AS_Set(AS_appSig_C_step19_targetRawValueMax_Index, dValue)

extern int AS_appSig_C_step26_targetRawValueMin_Index; // sig40
#define AS_appSig_C_step26_targetRawValueMin_Get() AS_Get(AS_appSig_C_step26_targetRawValueMin_Index)
#define AS_appSig_C_step26_targetRawValueMin_Set(dValue) AS_Set(AS_appSig_C_step26_targetRawValueMin_Index, dValue)

extern int AS_appSig_C_step26_targetRawValueNormal_Index; // sig41
#define AS_appSig_C_step26_targetRawValueNormal_Get() AS_Get(AS_appSig_C_step26_targetRawValueNormal_Index)
#define AS_appSig_C_step26_targetRawValueNormal_Set(dValue) AS_Set(AS_appSig_C_step26_targetRawValueNormal_Index, dValue)

extern int AS_appSig_C_step26_targetRawValueMax_Index; // sig42
#define AS_appSig_C_step26_targetRawValueMax_Get() AS_Get(AS_appSig_C_step26_targetRawValueMax_Index)
#define AS_appSig_C_step26_targetRawValueMax_Set(dValue) AS_Set(AS_appSig_C_step26_targetRawValueMax_Index, dValue)

extern int AS_appSig_C_step29_targetRawValueMin_Index; // sig43
#define AS_appSig_C_step29_targetRawValueMin_Get() AS_Get(AS_appSig_C_step29_targetRawValueMin_Index)
#define AS_appSig_C_step29_targetRawValueMin_Set(dValue) AS_Set(AS_appSig_C_step29_targetRawValueMin_Index, dValue)

extern int AS_appSig_C_step25_targetRawValueMin_Index; // sig44
#define AS_appSig_C_step25_targetRawValueMin_Get() AS_Get(AS_appSig_C_step25_targetRawValueMin_Index)
#define AS_appSig_C_step25_targetRawValueMin_Set(dValue) AS_Set(AS_appSig_C_step25_targetRawValueMin_Index, dValue)

extern int AS_appSig_C_step29_targetRawValueMax_Index; // sig45
#define AS_appSig_C_step29_targetRawValueMax_Get() AS_Get(AS_appSig_C_step29_targetRawValueMax_Index)
#define AS_appSig_C_step29_targetRawValueMax_Set(dValue) AS_Set(AS_appSig_C_step29_targetRawValueMax_Index, dValue)

extern int AS_appSig_C_step30_targetRawValueMin_Index; // sig46
#define AS_appSig_C_step30_targetRawValueMin_Get() AS_Get(AS_appSig_C_step30_targetRawValueMin_Index)
#define AS_appSig_C_step30_targetRawValueMin_Set(dValue) AS_Set(AS_appSig_C_step30_targetRawValueMin_Index, dValue)

extern int AS_appSig_C_step30_targetRawValueNormal_Index; // sig47
#define AS_appSig_C_step30_targetRawValueNormal_Get() AS_Get(AS_appSig_C_step30_targetRawValueNormal_Index)
#define AS_appSig_C_step30_targetRawValueNormal_Set(dValue) AS_Set(AS_appSig_C_step30_targetRawValueNormal_Index, dValue)

extern int AS_appSig_C_step30_targetRawValueMax_Index; // sig48
#define AS_appSig_C_step30_targetRawValueMax_Get() AS_Get(AS_appSig_C_step30_targetRawValueMax_Index)
#define AS_appSig_C_step30_targetRawValueMax_Set(dValue) AS_Set(AS_appSig_C_step30_targetRawValueMax_Index, dValue)

extern int AS_appSig_C_step31_targetRawValue_Index; // sig49
#define AS_appSig_C_step31_targetRawValue_Get() AS_Get(AS_appSig_C_step31_targetRawValue_Index)
#define AS_appSig_C_step31_targetRawValue_Set(dValue) AS_Set(AS_appSig_C_step31_targetRawValue_Index, dValue)

extern int AS_appSig_targetValueType_tmp_Index; // sig50
#define AS_appSig_targetValueType_tmp_Get() AS_Get(AS_appSig_targetValueType_tmp_Index)
#define AS_appSig_targetValueType_tmp_Set(dValue) AS_Set(AS_appSig_targetValueType_tmp_Index, dValue)

extern int AS_appSig_isAutoTestPassed_Index; // sig52
#define AS_appSig_isAutoTestPassed_Get() AS_Get(AS_appSig_isAutoTestPassed_Index)
#define AS_appSig_isAutoTestPassed_Set(dValue) AS_Set(AS_appSig_isAutoTestPassed_Index, dValue)

extern int AS_appSig_tmp_byteHex_Index; // sig54
#define AS_appSig_tmp_byteHex_Get() AS_Get(AS_appSig_tmp_byteHex_Index)
#define AS_appSig_tmp_byteHex_Set(dValue) AS_Set(AS_appSig_tmp_byteHex_Index, dValue)
#define AS_appSig_tmp_byteHex_GetAt(offset) AS_GetAt(AS_appSig_tmp_byteHex_Index, offset)
#define AS_appSig_tmp_byteHex_SetAt(offset, dValue) AS_SetAt(AS_appSig_tmp_byteHex_Index, offset, dValue)
#define AS_appSig_tmp_byteHex_GetSize() AS_GetAt(AS_appSig_tmp_byteHex_Index, -1)
#define AS_appSig_tmp_byteHex_SetSize(dValue) AS_SetAt(AS_appSig_tmp_byteHex_Index, -1, dValue)
#define AS_appSig_tmp_byteHex_GetText(szValue) AS_GetText(AS_appSig_tmp_byteHex_Index, szValue, -1)
#define AS_appSig_tmp_byteHex_SetText(szValue) AS_SetText(AS_appSig_tmp_byteHex_Index, szValue, -1)
#define AS_appSig_tmp_byteHex_GetTextLen(szValue, len) AS_GetText(AS_appSig_tmp_byteHex_Index, szValue, len)
#define AS_appSig_tmp_byteHex_SetTextLen(szValue, len) AS_SetText(AS_appSig_tmp_byteHex_Index, szValue, len)

extern int AS_appSig_steps_currPhyValueStr_Index; // sig57
#define AS_appSig_steps_currPhyValueStr_Get() AS_Get(AS_appSig_steps_currPhyValueStr_Index)
#define AS_appSig_steps_currPhyValueStr_Set(dValue) AS_Set(AS_appSig_steps_currPhyValueStr_Index, dValue)
#define AS_appSig_steps_currPhyValueStr_GetTextAtW(offset, str) AS_GetTextAtW(AS_appSig_steps_currPhyValueStr_Index, offset, str)
#define AS_appSig_steps_currPhyValueStr_SetTextAtW(offset, str) AS_SetTextAtW(AS_appSig_steps_currPhyValueStr_Index, offset, str)
#define AS_appSig_steps_currPhyValueStr_GetSize() AS_GetAt(AS_appSig_steps_currPhyValueStr_Index, -1)
#define AS_appSig_steps_currPhyValueStr_SetSize(dValue) AS_SetAt(AS_appSig_steps_currPhyValueStr_Index, -1, dValue)
#define AS_appSig_steps_currPhyValueStr_GetTextW(szValue) AS_GetTextW(AS_appSig_steps_currPhyValueStr_Index, szValue)
#define AS_appSig_steps_currPhyValueStr_SetTextW(szValue) CM_GetSetValue(g_uiHandle, CM_GETSET_SET_APP_SIGNAL_TEXT, AS_appSig_steps_currPhyValueStr_Index, szValue)
#define AS_appSig_steps_currPhyValueStr_GetText(szValue) AS_GetText(AS_appSig_steps_currPhyValueStr_Index, szValue, -1)
#define AS_appSig_steps_currPhyValueStr_SetText(szValue) AS_SetText(AS_appSig_steps_currPhyValueStr_Index, szValue, -1)
#define AS_appSig_steps_currPhyValueStr_GetTextLen(szValue, len) AS_GetText(AS_appSig_steps_currPhyValueStr_Index, szValue, len)
#define AS_appSig_steps_currPhyValueStr_SetTextLen(szValue, len) AS_SetText(AS_appSig_steps_currPhyValueStr_Index, szValue, len)

extern int AS_appSig_step15_currPhyValue_Index; // sig60
#define AS_appSig_step15_currPhyValue_Get() AS_Get(AS_appSig_step15_currPhyValue_Index)
#define AS_appSig_step15_currPhyValue_Set(dValue) AS_Set(AS_appSig_step15_currPhyValue_Index, dValue)

extern int AS_appSig_step16_currPhyValue_Index; // sig63
#define AS_appSig_step16_currPhyValue_Get() AS_Get(AS_appSig_step16_currPhyValue_Index)
#define AS_appSig_step16_currPhyValue_Set(dValue) AS_Set(AS_appSig_step16_currPhyValue_Index, dValue)

extern int AS_appSig_step17_currPhyValue_Index; // sig64
#define AS_appSig_step17_currPhyValue_Get() AS_Get(AS_appSig_step17_currPhyValue_Index)
#define AS_appSig_step17_currPhyValue_Set(dValue) AS_Set(AS_appSig_step17_currPhyValue_Index, dValue)

extern int AS_appSig_step18_currPhyValue_Index; // sig65
#define AS_appSig_step18_currPhyValue_Get() AS_Get(AS_appSig_step18_currPhyValue_Index)
#define AS_appSig_step18_currPhyValue_Set(dValue) AS_Set(AS_appSig_step18_currPhyValue_Index, dValue)

extern int AS_appSig_step19_currPhyValue_Index; // sig66
#define AS_appSig_step19_currPhyValue_Get() AS_Get(AS_appSig_step19_currPhyValue_Index)
#define AS_appSig_step19_currPhyValue_Set(dValue) AS_Set(AS_appSig_step19_currPhyValue_Index, dValue)

extern int AS_appSig_step20_currPhyValue_Index; // sig67
#define AS_appSig_step20_currPhyValue_Get() AS_Get(AS_appSig_step20_currPhyValue_Index)
#define AS_appSig_step20_currPhyValue_Set(dValue) AS_Set(AS_appSig_step20_currPhyValue_Index, dValue)

extern int AS_appSig_step21_currPhyValue_Index; // sig68
#define AS_appSig_step21_currPhyValue_Get() AS_Get(AS_appSig_step21_currPhyValue_Index)
#define AS_appSig_step21_currPhyValue_Set(dValue) AS_Set(AS_appSig_step21_currPhyValue_Index, dValue)

extern int AS_appSig_step22_currPhyValue_Index; // sig69
#define AS_appSig_step22_currPhyValue_Get() AS_Get(AS_appSig_step22_currPhyValue_Index)
#define AS_appSig_step22_currPhyValue_Set(dValue) AS_Set(AS_appSig_step22_currPhyValue_Index, dValue)

extern int AS_appSig_step23_currPhyValue_Index; // sig70
#define AS_appSig_step23_currPhyValue_Get() AS_Get(AS_appSig_step23_currPhyValue_Index)
#define AS_appSig_step23_currPhyValue_Set(dValue) AS_Set(AS_appSig_step23_currPhyValue_Index, dValue)

extern int AS_appSig_step24_currPhyValue_Index; // sig71
#define AS_appSig_step24_currPhyValue_Get() AS_Get(AS_appSig_step24_currPhyValue_Index)
#define AS_appSig_step24_currPhyValue_Set(dValue) AS_Set(AS_appSig_step24_currPhyValue_Index, dValue)

extern int AS_appSig_step25_currPhyValue_Index; // sig72
#define AS_appSig_step25_currPhyValue_Get() AS_Get(AS_appSig_step25_currPhyValue_Index)
#define AS_appSig_step25_currPhyValue_Set(dValue) AS_Set(AS_appSig_step25_currPhyValue_Index, dValue)

extern int AS_appSig_step26_currPhyValue_Index; // sig73
#define AS_appSig_step26_currPhyValue_Get() AS_Get(AS_appSig_step26_currPhyValue_Index)
#define AS_appSig_step26_currPhyValue_Set(dValue) AS_Set(AS_appSig_step26_currPhyValue_Index, dValue)

extern int AS_appSig_step27_currPhyValue_Index; // sig74
#define AS_appSig_step27_currPhyValue_Get() AS_Get(AS_appSig_step27_currPhyValue_Index)
#define AS_appSig_step27_currPhyValue_Set(dValue) AS_Set(AS_appSig_step27_currPhyValue_Index, dValue)

extern int AS_appSig_step28_currPhyValue_Index; // sig75
#define AS_appSig_step28_currPhyValue_Get() AS_Get(AS_appSig_step28_currPhyValue_Index)
#define AS_appSig_step28_currPhyValue_Set(dValue) AS_Set(AS_appSig_step28_currPhyValue_Index, dValue)

extern int AS_appSig_step29_currPhyValue_Index; // sig76
#define AS_appSig_step29_currPhyValue_Get() AS_Get(AS_appSig_step29_currPhyValue_Index)
#define AS_appSig_step29_currPhyValue_Set(dValue) AS_Set(AS_appSig_step29_currPhyValue_Index, dValue)

extern int AS_appSig_step30_currPhyValue_Index; // sig77
#define AS_appSig_step30_currPhyValue_Get() AS_Get(AS_appSig_step30_currPhyValue_Index)
#define AS_appSig_step30_currPhyValue_Set(dValue) AS_Set(AS_appSig_step30_currPhyValue_Index, dValue)

extern int AS_appSig_step31_currPhyValue_Index; // sig86
#define AS_appSig_step31_currPhyValue_Get() AS_Get(AS_appSig_step31_currPhyValue_Index)
#define AS_appSig_step31_currPhyValue_Set(dValue) AS_Set(AS_appSig_step31_currPhyValue_Index, dValue)

extern int AS_appSig_step32_currPhyValue_Index; // sig79
#define AS_appSig_step32_currPhyValue_Get() AS_Get(AS_appSig_step32_currPhyValue_Index)
#define AS_appSig_step32_currPhyValue_Set(dValue) AS_Set(AS_appSig_step32_currPhyValue_Index, dValue)

extern int AS_appSig_step33_currPhyValue_Index; // sig80
#define AS_appSig_step33_currPhyValue_Get() AS_Get(AS_appSig_step33_currPhyValue_Index)
#define AS_appSig_step33_currPhyValue_Set(dValue) AS_Set(AS_appSig_step33_currPhyValue_Index, dValue)

extern int AS_appSig_step34_currPhyValue_Index; // sig81
#define AS_appSig_step34_currPhyValue_Get() AS_Get(AS_appSig_step34_currPhyValue_Index)
#define AS_appSig_step34_currPhyValue_Set(dValue) AS_Set(AS_appSig_step34_currPhyValue_Index, dValue)

extern int AS_appSig_step35_currPhyValue_Index; // sig82
#define AS_appSig_step35_currPhyValue_Get() AS_Get(AS_appSig_step35_currPhyValue_Index)
#define AS_appSig_step35_currPhyValue_Set(dValue) AS_Set(AS_appSig_step35_currPhyValue_Index, dValue)

extern int AS_appSig_step36_currPhyValue_Index; // sig83
#define AS_appSig_step36_currPhyValue_Get() AS_Get(AS_appSig_step36_currPhyValue_Index)
#define AS_appSig_step36_currPhyValue_Set(dValue) AS_Set(AS_appSig_step36_currPhyValue_Index, dValue)

extern int AS_appSig_step37_currPhyValue_Index; // sig84
#define AS_appSig_step37_currPhyValue_Get() AS_Get(AS_appSig_step37_currPhyValue_Index)
#define AS_appSig_step37_currPhyValue_Set(dValue) AS_Set(AS_appSig_step37_currPhyValue_Index, dValue)

extern int AS_appSig_step38_currPhyValue_Index; // sig85
#define AS_appSig_step38_currPhyValue_Get() AS_Get(AS_appSig_step38_currPhyValue_Index)
#define AS_appSig_step38_currPhyValue_Set(dValue) AS_Set(AS_appSig_step38_currPhyValue_Index, dValue)

extern int AS_appSig_C_invalidStr_Index; // sig87
#define AS_appSig_C_invalidStr_Get() AS_Get(AS_appSig_C_invalidStr_Index)
#define AS_appSig_C_invalidStr_Set(dValue) AS_Set(AS_appSig_C_invalidStr_Index, dValue)
#define AS_appSig_C_invalidStr_GetTextW(szValue) AS_GetTextW(AS_appSig_C_invalidStr_Index, szValue)
#define AS_appSig_C_invalidStr_SetTextW(szValue) CM_GetSetValue(g_uiHandle, CM_GETSET_SET_APP_SIGNAL_TEXT, AS_appSig_C_invalidStr_Index, szValue)
#define AS_appSig_C_invalidStr_GetText(szValue) AS_GetText(AS_appSig_C_invalidStr_Index, szValue, -1)
#define AS_appSig_C_invalidStr_SetText(szValue) AS_SetText(AS_appSig_C_invalidStr_Index, szValue, -1)
#define AS_appSig_C_invalidStr_GetTextLen(szValue, len) AS_GetText(AS_appSig_C_invalidStr_Index, szValue, len)
#define AS_appSig_C_invalidStr_SetTextLen(szValue, len) AS_SetText(AS_appSig_C_invalidStr_Index, szValue, len)

extern int AS_appSig_linkCanState_Index; // sig88
#define AS_appSig_linkCanState_Get() AS_Get(AS_appSig_linkCanState_Index)
#define AS_appSig_linkCanState_Set(dValue) AS_Set(AS_appSig_linkCanState_Index, dValue)

extern int AS_appSig_isAutoTestPassedGUI_Index; // sig89
#define AS_appSig_isAutoTestPassedGUI_Get() AS_Get(AS_appSig_isAutoTestPassedGUI_Index)
#define AS_appSig_isAutoTestPassedGUI_Set(dValue) AS_Set(AS_appSig_isAutoTestPassedGUI_Index, dValue)

extern int AS_appSig_isStep32to38QueryStart_Index; // sig90
#define AS_appSig_isStep32to38QueryStart_Get() AS_Get(AS_appSig_isStep32to38QueryStart_Index)
#define AS_appSig_isStep32to38QueryStart_Set(dValue) AS_Set(AS_appSig_isStep32to38QueryStart_Index, dValue)

extern int AS_appSig_C_step25_targetRawValueNormal_Index; // sig92
#define AS_appSig_C_step25_targetRawValueNormal_Get() AS_Get(AS_appSig_C_step25_targetRawValueNormal_Index)
#define AS_appSig_C_step25_targetRawValueNormal_Set(dValue) AS_Set(AS_appSig_C_step25_targetRawValueNormal_Index, dValue)

extern int AS_appSig_C_step25_targetRawValueMax_Index; // sig93
#define AS_appSig_C_step25_targetRawValueMax_Get() AS_Get(AS_appSig_C_step25_targetRawValueMax_Index)
#define AS_appSig_C_step25_targetRawValueMax_Set(dValue) AS_Set(AS_appSig_C_step25_targetRawValueMax_Index, dValue)

extern int AS_appSig_C_step29_targetRawValueNormal_Index; // sig94
#define AS_appSig_C_step29_targetRawValueNormal_Get() AS_Get(AS_appSig_C_step29_targetRawValueNormal_Index)
#define AS_appSig_C_step29_targetRawValueNormal_Set(dValue) AS_Set(AS_appSig_C_step29_targetRawValueNormal_Index, dValue)

extern int AS_appSig_C_step27_targetRawValueNormal_Index; // sig95
#define AS_appSig_C_step27_targetRawValueNormal_Get() AS_Get(AS_appSig_C_step27_targetRawValueNormal_Index)
#define AS_appSig_C_step27_targetRawValueNormal_Set(dValue) AS_Set(AS_appSig_C_step27_targetRawValueNormal_Index, dValue)

extern int AS_appSig_C_step27_targetRawValueMin_Index; // sig96
#define AS_appSig_C_step27_targetRawValueMin_Get() AS_Get(AS_appSig_C_step27_targetRawValueMin_Index)
#define AS_appSig_C_step27_targetRawValueMin_Set(dValue) AS_Set(AS_appSig_C_step27_targetRawValueMin_Index, dValue)

extern int AS_appSig_C_step27_targetRawValueMax_Index; // sig97
#define AS_appSig_C_step27_targetRawValueMax_Get() AS_Get(AS_appSig_C_step27_targetRawValueMax_Index)
#define AS_appSig_C_step27_targetRawValueMax_Set(dValue) AS_Set(AS_appSig_C_step27_targetRawValueMax_Index, dValue)

extern int AS_appSig_C_step28_targetRawValueNormal_Index; // sig98
#define AS_appSig_C_step28_targetRawValueNormal_Get() AS_Get(AS_appSig_C_step28_targetRawValueNormal_Index)
#define AS_appSig_C_step28_targetRawValueNormal_Set(dValue) AS_Set(AS_appSig_C_step28_targetRawValueNormal_Index, dValue)

extern int AS_appSig_C_step28_targetRawValueMin_Index; // sig99
#define AS_appSig_C_step28_targetRawValueMin_Get() AS_Get(AS_appSig_C_step28_targetRawValueMin_Index)
#define AS_appSig_C_step28_targetRawValueMin_Set(dValue) AS_Set(AS_appSig_C_step28_targetRawValueMin_Index, dValue)

extern int AS_appSig_C_step28_targetRawValueMax_Index; // sig100
#define AS_appSig_C_step28_targetRawValueMax_Get() AS_Get(AS_appSig_C_step28_targetRawValueMax_Index)
#define AS_appSig_C_step28_targetRawValueMax_Set(dValue) AS_Set(AS_appSig_C_step28_targetRawValueMax_Index, dValue)

extern int AS_appSig_mpiWrite_MTC_Index; // sig101
#define AS_appSig_mpiWrite_MTC_Get() AS_Get(AS_appSig_mpiWrite_MTC_Index)
#define AS_appSig_mpiWrite_MTC_Set(dValue) AS_Set(AS_appSig_mpiWrite_MTC_Index, dValue)
#define AS_appSig_mpiWrite_MTC_GetTextW(szValue) AS_GetTextW(AS_appSig_mpiWrite_MTC_Index, szValue)
#define AS_appSig_mpiWrite_MTC_SetTextW(szValue) CM_GetSetValue(g_uiHandle, CM_GETSET_SET_APP_SIGNAL_TEXT, AS_appSig_mpiWrite_MTC_Index, szValue)
#define AS_appSig_mpiWrite_MTC_GetText(szValue) AS_GetText(AS_appSig_mpiWrite_MTC_Index, szValue, -1)
#define AS_appSig_mpiWrite_MTC_SetText(szValue) AS_SetText(AS_appSig_mpiWrite_MTC_Index, szValue, -1)
#define AS_appSig_mpiWrite_MTC_GetTextLen(szValue, len) AS_GetText(AS_appSig_mpiWrite_MTC_Index, szValue, len)
#define AS_appSig_mpiWrite_MTC_SetTextLen(szValue, len) AS_SetText(AS_appSig_mpiWrite_MTC_Index, szValue, len)

extern int AS_appSig_mpiWrite_EMPN_Index; // sig103
#define AS_appSig_mpiWrite_EMPN_Get() AS_Get(AS_appSig_mpiWrite_EMPN_Index)
#define AS_appSig_mpiWrite_EMPN_Set(dValue) AS_Set(AS_appSig_mpiWrite_EMPN_Index, dValue)

extern int AS_appSig_mpiWrite_BMPN_Index; // sig104
#define AS_appSig_mpiWrite_BMPN_Get() AS_Get(AS_appSig_mpiWrite_BMPN_Index)
#define AS_appSig_mpiWrite_BMPN_Set(dValue) AS_Set(AS_appSig_mpiWrite_BMPN_Index, dValue)

extern int AS_appSig_mpiWrite_EMPNAC_Index; // sig105
#define AS_appSig_mpiWrite_EMPNAC_Get() AS_Get(AS_appSig_mpiWrite_EMPNAC_Index)
#define AS_appSig_mpiWrite_EMPNAC_Set(dValue) AS_Set(AS_appSig_mpiWrite_EMPNAC_Index, dValue)
#define AS_appSig_mpiWrite_EMPNAC_GetTextW(szValue) AS_GetTextW(AS_appSig_mpiWrite_EMPNAC_Index, szValue)
#define AS_appSig_mpiWrite_EMPNAC_SetTextW(szValue) CM_GetSetValue(g_uiHandle, CM_GETSET_SET_APP_SIGNAL_TEXT, AS_appSig_mpiWrite_EMPNAC_Index, szValue)
#define AS_appSig_mpiWrite_EMPNAC_GetText(szValue) AS_GetText(AS_appSig_mpiWrite_EMPNAC_Index, szValue, -1)
#define AS_appSig_mpiWrite_EMPNAC_SetText(szValue) AS_SetText(AS_appSig_mpiWrite_EMPNAC_Index, szValue, -1)
#define AS_appSig_mpiWrite_EMPNAC_GetTextLen(szValue, len) AS_GetText(AS_appSig_mpiWrite_EMPNAC_Index, szValue, len)
#define AS_appSig_mpiWrite_EMPNAC_SetTextLen(szValue, len) AS_SetText(AS_appSig_mpiWrite_EMPNAC_Index, szValue, len)

extern int AS_appSig_mpiWrite_BMPNAC_Index; // sig106
#define AS_appSig_mpiWrite_BMPNAC_Get() AS_Get(AS_appSig_mpiWrite_BMPNAC_Index)
#define AS_appSig_mpiWrite_BMPNAC_Set(dValue) AS_Set(AS_appSig_mpiWrite_BMPNAC_Index, dValue)
#define AS_appSig_mpiWrite_BMPNAC_GetTextW(szValue) AS_GetTextW(AS_appSig_mpiWrite_BMPNAC_Index, szValue)
#define AS_appSig_mpiWrite_BMPNAC_SetTextW(szValue) CM_GetSetValue(g_uiHandle, CM_GETSET_SET_APP_SIGNAL_TEXT, AS_appSig_mpiWrite_BMPNAC_Index, szValue)
#define AS_appSig_mpiWrite_BMPNAC_GetText(szValue) AS_GetText(AS_appSig_mpiWrite_BMPNAC_Index, szValue, -1)
#define AS_appSig_mpiWrite_BMPNAC_SetText(szValue) AS_SetText(AS_appSig_mpiWrite_BMPNAC_Index, szValue, -1)
#define AS_appSig_mpiWrite_BMPNAC_GetTextLen(szValue, len) AS_GetText(AS_appSig_mpiWrite_BMPNAC_Index, szValue, len)
#define AS_appSig_mpiWrite_BMPNAC_SetTextLen(szValue, len) AS_SetText(AS_appSig_mpiWrite_BMPNAC_Index, szValue, len)

extern int AS_appSig_mpiWrite_SN_Index; // sig108
#define AS_appSig_mpiWrite_SN_Get() AS_Get(AS_appSig_mpiWrite_SN_Index)
#define AS_appSig_mpiWrite_SN_Set(dValue) AS_Set(AS_appSig_mpiWrite_SN_Index, dValue)

extern int AS_appSig_mpiWrite_ENGINE_Index; // sig114
#define AS_appSig_mpiWrite_ENGINE_Get() AS_Get(AS_appSig_mpiWrite_ENGINE_Index)
#define AS_appSig_mpiWrite_ENGINE_Set(dValue) AS_Set(AS_appSig_mpiWrite_ENGINE_Index, dValue)
#define AS_appSig_mpiWrite_ENGINE_GetTextW(szValue) AS_GetTextW(AS_appSig_mpiWrite_ENGINE_Index, szValue)
#define AS_appSig_mpiWrite_ENGINE_SetTextW(szValue) CM_GetSetValue(g_uiHandle, CM_GETSET_SET_APP_SIGNAL_TEXT, AS_appSig_mpiWrite_ENGINE_Index, szValue)
#define AS_appSig_mpiWrite_ENGINE_GetText(szValue) AS_GetText(AS_appSig_mpiWrite_ENGINE_Index, szValue, -1)
#define AS_appSig_mpiWrite_ENGINE_SetText(szValue) AS_SetText(AS_appSig_mpiWrite_ENGINE_Index, szValue, -1)
#define AS_appSig_mpiWrite_ENGINE_GetTextLen(szValue, len) AS_GetText(AS_appSig_mpiWrite_ENGINE_Index, szValue, len)
#define AS_appSig_mpiWrite_ENGINE_SetTextLen(szValue, len) AS_SetText(AS_appSig_mpiWrite_ENGINE_Index, szValue, len)

extern int AS_appSig_mpiReadSteps_valueStr_Index; // sig107
#define AS_appSig_mpiReadSteps_valueStr_Get() AS_Get(AS_appSig_mpiReadSteps_valueStr_Index)
#define AS_appSig_mpiReadSteps_valueStr_Set(dValue) AS_Set(AS_appSig_mpiReadSteps_valueStr_Index, dValue)
#define AS_appSig_mpiReadSteps_valueStr_GetTextAtW(offset, str) AS_GetTextAtW(AS_appSig_mpiReadSteps_valueStr_Index, offset, str)
#define AS_appSig_mpiReadSteps_valueStr_SetTextAtW(offset, str) AS_SetTextAtW(AS_appSig_mpiReadSteps_valueStr_Index, offset, str)
#define AS_appSig_mpiReadSteps_valueStr_GetSize() AS_GetAt(AS_appSig_mpiReadSteps_valueStr_Index, -1)
#define AS_appSig_mpiReadSteps_valueStr_SetSize(dValue) AS_SetAt(AS_appSig_mpiReadSteps_valueStr_Index, -1, dValue)
#define AS_appSig_mpiReadSteps_valueStr_GetTextW(szValue) AS_GetTextW(AS_appSig_mpiReadSteps_valueStr_Index, szValue)
#define AS_appSig_mpiReadSteps_valueStr_SetTextW(szValue) CM_GetSetValue(g_uiHandle, CM_GETSET_SET_APP_SIGNAL_TEXT, AS_appSig_mpiReadSteps_valueStr_Index, szValue)
#define AS_appSig_mpiReadSteps_valueStr_GetText(szValue) AS_GetText(AS_appSig_mpiReadSteps_valueStr_Index, szValue, -1)
#define AS_appSig_mpiReadSteps_valueStr_SetText(szValue) AS_SetText(AS_appSig_mpiReadSteps_valueStr_Index, szValue, -1)
#define AS_appSig_mpiReadSteps_valueStr_GetTextLen(szValue, len) AS_GetText(AS_appSig_mpiReadSteps_valueStr_Index, szValue, len)
#define AS_appSig_mpiReadSteps_valueStr_SetTextLen(szValue, len) AS_SetText(AS_appSig_mpiReadSteps_valueStr_Index, szValue, len)

extern int AS_appSig_mpiWrite_lock_Index; // sig109
#define AS_appSig_mpiWrite_lock_Get() AS_Get(AS_appSig_mpiWrite_lock_Index)
#define AS_appSig_mpiWrite_lock_Set(dValue) AS_Set(AS_appSig_mpiWrite_lock_Index, dValue)

extern int AS_appSig_mpiWriteSteps_isPassed_Index; // sig110
#define AS_appSig_mpiWriteSteps_isPassed_Get() AS_Get(AS_appSig_mpiWriteSteps_isPassed_Index)
#define AS_appSig_mpiWriteSteps_isPassed_Set(dValue) AS_Set(AS_appSig_mpiWriteSteps_isPassed_Index, dValue)
#define AS_appSig_mpiWriteSteps_isPassed_GetAt(offset) AS_GetAt(AS_appSig_mpiWriteSteps_isPassed_Index, offset)
#define AS_appSig_mpiWriteSteps_isPassed_SetAt(offset, dValue) AS_SetAt(AS_appSig_mpiWriteSteps_isPassed_Index, offset, dValue)
#define AS_appSig_mpiWriteSteps_isPassed_GetSize() AS_GetAt(AS_appSig_mpiWriteSteps_isPassed_Index, -1)
#define AS_appSig_mpiWriteSteps_isPassed_SetSize(dValue) AS_SetAt(AS_appSig_mpiWriteSteps_isPassed_Index, -1, dValue)
#define AS_appSig_mpiWriteSteps_isPassed_GetText(szValue) AS_GetText(AS_appSig_mpiWriteSteps_isPassed_Index, szValue, -1)
#define AS_appSig_mpiWriteSteps_isPassed_SetText(szValue) AS_SetText(AS_appSig_mpiWriteSteps_isPassed_Index, szValue, -1)
#define AS_appSig_mpiWriteSteps_isPassed_GetTextLen(szValue, len) AS_GetText(AS_appSig_mpiWriteSteps_isPassed_Index, szValue, len)
#define AS_appSig_mpiWriteSteps_isPassed_SetTextLen(szValue, len) AS_SetText(AS_appSig_mpiWriteSteps_isPassed_Index, szValue, len)

extern int AS_appSig_mpiReadSteps_isPassed_Index; // sig111
#define AS_appSig_mpiReadSteps_isPassed_Get() AS_Get(AS_appSig_mpiReadSteps_isPassed_Index)
#define AS_appSig_mpiReadSteps_isPassed_Set(dValue) AS_Set(AS_appSig_mpiReadSteps_isPassed_Index, dValue)
#define AS_appSig_mpiReadSteps_isPassed_GetAt(offset) AS_GetAt(AS_appSig_mpiReadSteps_isPassed_Index, offset)
#define AS_appSig_mpiReadSteps_isPassed_SetAt(offset, dValue) AS_SetAt(AS_appSig_mpiReadSteps_isPassed_Index, offset, dValue)
#define AS_appSig_mpiReadSteps_isPassed_GetSize() AS_GetAt(AS_appSig_mpiReadSteps_isPassed_Index, -1)
#define AS_appSig_mpiReadSteps_isPassed_SetSize(dValue) AS_SetAt(AS_appSig_mpiReadSteps_isPassed_Index, -1, dValue)
#define AS_appSig_mpiReadSteps_isPassed_GetText(szValue) AS_GetText(AS_appSig_mpiReadSteps_isPassed_Index, szValue, -1)
#define AS_appSig_mpiReadSteps_isPassed_SetText(szValue) AS_SetText(AS_appSig_mpiReadSteps_isPassed_Index, szValue, -1)
#define AS_appSig_mpiReadSteps_isPassed_GetTextLen(szValue, len) AS_GetText(AS_appSig_mpiReadSteps_isPassed_Index, szValue, len)
#define AS_appSig_mpiReadSteps_isPassed_SetTextLen(szValue, len) AS_SetText(AS_appSig_mpiReadSteps_isPassed_Index, szValue, len)

extern int AS_appSig_mpiRead_isCheckPassed_Index; // sig112
#define AS_appSig_mpiRead_isCheckPassed_Get() AS_Get(AS_appSig_mpiRead_isCheckPassed_Index)
#define AS_appSig_mpiRead_isCheckPassed_Set(dValue) AS_Set(AS_appSig_mpiRead_isCheckPassed_Index, dValue)

extern int AS_appSig_mpiRead_isCheckPassedGUI_Index; // sig113
#define AS_appSig_mpiRead_isCheckPassedGUI_Get() AS_Get(AS_appSig_mpiRead_isCheckPassedGUI_Index)
#define AS_appSig_mpiRead_isCheckPassedGUI_Set(dValue) AS_Set(AS_appSig_mpiRead_isCheckPassedGUI_Index, dValue)

extern int AS_appSig_mpiWrite_bytesENGINE_Index; // sig115
#define AS_appSig_mpiWrite_bytesENGINE_Get() AS_Get(AS_appSig_mpiWrite_bytesENGINE_Index)
#define AS_appSig_mpiWrite_bytesENGINE_Set(dValue) AS_Set(AS_appSig_mpiWrite_bytesENGINE_Index, dValue)
#define AS_appSig_mpiWrite_bytesENGINE_GetAt(offset) AS_GetAt(AS_appSig_mpiWrite_bytesENGINE_Index, offset)
#define AS_appSig_mpiWrite_bytesENGINE_SetAt(offset, dValue) AS_SetAt(AS_appSig_mpiWrite_bytesENGINE_Index, offset, dValue)
#define AS_appSig_mpiWrite_bytesENGINE_GetSize() AS_GetAt(AS_appSig_mpiWrite_bytesENGINE_Index, -1)
#define AS_appSig_mpiWrite_bytesENGINE_SetSize(dValue) AS_SetAt(AS_appSig_mpiWrite_bytesENGINE_Index, -1, dValue)
#define AS_appSig_mpiWrite_bytesENGINE_GetText(szValue) AS_GetText(AS_appSig_mpiWrite_bytesENGINE_Index, szValue, -1)
#define AS_appSig_mpiWrite_bytesENGINE_SetText(szValue) AS_SetText(AS_appSig_mpiWrite_bytesENGINE_Index, szValue, -1)
#define AS_appSig_mpiWrite_bytesENGINE_GetTextLen(szValue, len) AS_GetText(AS_appSig_mpiWrite_bytesENGINE_Index, szValue, len)
#define AS_appSig_mpiWrite_bytesENGINE_SetTextLen(szValue, len) AS_SetText(AS_appSig_mpiWrite_bytesENGINE_Index, szValue, len)

extern int AS_appSig_mpiWrite_ENGINENumber_Index; // sig118
#define AS_appSig_mpiWrite_ENGINENumber_Get() AS_Get(AS_appSig_mpiWrite_ENGINENumber_Index)
#define AS_appSig_mpiWrite_ENGINENumber_Set(dValue) AS_Set(AS_appSig_mpiWrite_ENGINENumber_Index, dValue)

extern int AS_appSig_mpiWrite_bytesMTC_Index; // sig119
#define AS_appSig_mpiWrite_bytesMTC_Get() AS_Get(AS_appSig_mpiWrite_bytesMTC_Index)
#define AS_appSig_mpiWrite_bytesMTC_Set(dValue) AS_Set(AS_appSig_mpiWrite_bytesMTC_Index, dValue)
#define AS_appSig_mpiWrite_bytesMTC_GetAt(offset) AS_GetAt(AS_appSig_mpiWrite_bytesMTC_Index, offset)
#define AS_appSig_mpiWrite_bytesMTC_SetAt(offset, dValue) AS_SetAt(AS_appSig_mpiWrite_bytesMTC_Index, offset, dValue)
#define AS_appSig_mpiWrite_bytesMTC_GetSize() AS_GetAt(AS_appSig_mpiWrite_bytesMTC_Index, -1)
#define AS_appSig_mpiWrite_bytesMTC_SetSize(dValue) AS_SetAt(AS_appSig_mpiWrite_bytesMTC_Index, -1, dValue)
#define AS_appSig_mpiWrite_bytesMTC_GetText(szValue) AS_GetText(AS_appSig_mpiWrite_bytesMTC_Index, szValue, -1)
#define AS_appSig_mpiWrite_bytesMTC_SetText(szValue) AS_SetText(AS_appSig_mpiWrite_bytesMTC_Index, szValue, -1)
#define AS_appSig_mpiWrite_bytesMTC_GetTextLen(szValue, len) AS_GetText(AS_appSig_mpiWrite_bytesMTC_Index, szValue, len)
#define AS_appSig_mpiWrite_bytesMTC_SetTextLen(szValue, len) AS_SetText(AS_appSig_mpiWrite_bytesMTC_Index, szValue, len)

extern int AS_appSig_mpiWrite_bytesEMPNAC_Index; // sig120
#define AS_appSig_mpiWrite_bytesEMPNAC_Get() AS_Get(AS_appSig_mpiWrite_bytesEMPNAC_Index)
#define AS_appSig_mpiWrite_bytesEMPNAC_Set(dValue) AS_Set(AS_appSig_mpiWrite_bytesEMPNAC_Index, dValue)
#define AS_appSig_mpiWrite_bytesEMPNAC_GetAt(offset) AS_GetAt(AS_appSig_mpiWrite_bytesEMPNAC_Index, offset)
#define AS_appSig_mpiWrite_bytesEMPNAC_SetAt(offset, dValue) AS_SetAt(AS_appSig_mpiWrite_bytesEMPNAC_Index, offset, dValue)
#define AS_appSig_mpiWrite_bytesEMPNAC_GetSize() AS_GetAt(AS_appSig_mpiWrite_bytesEMPNAC_Index, -1)
#define AS_appSig_mpiWrite_bytesEMPNAC_SetSize(dValue) AS_SetAt(AS_appSig_mpiWrite_bytesEMPNAC_Index, -1, dValue)
#define AS_appSig_mpiWrite_bytesEMPNAC_GetText(szValue) AS_GetText(AS_appSig_mpiWrite_bytesEMPNAC_Index, szValue, -1)
#define AS_appSig_mpiWrite_bytesEMPNAC_SetText(szValue) AS_SetText(AS_appSig_mpiWrite_bytesEMPNAC_Index, szValue, -1)
#define AS_appSig_mpiWrite_bytesEMPNAC_GetTextLen(szValue, len) AS_GetText(AS_appSig_mpiWrite_bytesEMPNAC_Index, szValue, len)
#define AS_appSig_mpiWrite_bytesEMPNAC_SetTextLen(szValue, len) AS_SetText(AS_appSig_mpiWrite_bytesEMPNAC_Index, szValue, len)

extern int AS_appSig_mpiWrite_bytesBMPNAC_Index; // sig121
#define AS_appSig_mpiWrite_bytesBMPNAC_Get() AS_Get(AS_appSig_mpiWrite_bytesBMPNAC_Index)
#define AS_appSig_mpiWrite_bytesBMPNAC_Set(dValue) AS_Set(AS_appSig_mpiWrite_bytesBMPNAC_Index, dValue)
#define AS_appSig_mpiWrite_bytesBMPNAC_GetAt(offset) AS_GetAt(AS_appSig_mpiWrite_bytesBMPNAC_Index, offset)
#define AS_appSig_mpiWrite_bytesBMPNAC_SetAt(offset, dValue) AS_SetAt(AS_appSig_mpiWrite_bytesBMPNAC_Index, offset, dValue)
#define AS_appSig_mpiWrite_bytesBMPNAC_GetSize() AS_GetAt(AS_appSig_mpiWrite_bytesBMPNAC_Index, -1)
#define AS_appSig_mpiWrite_bytesBMPNAC_SetSize(dValue) AS_SetAt(AS_appSig_mpiWrite_bytesBMPNAC_Index, -1, dValue)
#define AS_appSig_mpiWrite_bytesBMPNAC_GetText(szValue) AS_GetText(AS_appSig_mpiWrite_bytesBMPNAC_Index, szValue, -1)
#define AS_appSig_mpiWrite_bytesBMPNAC_SetText(szValue) AS_SetText(AS_appSig_mpiWrite_bytesBMPNAC_Index, szValue, -1)
#define AS_appSig_mpiWrite_bytesBMPNAC_GetTextLen(szValue, len) AS_GetText(AS_appSig_mpiWrite_bytesBMPNAC_Index, szValue, len)
#define AS_appSig_mpiWrite_bytesBMPNAC_SetTextLen(szValue, len) AS_SetText(AS_appSig_mpiWrite_bytesBMPNAC_Index, szValue, len)

extern int AS_appSig_mpiRead_bytesMTC_Index; // sig122
#define AS_appSig_mpiRead_bytesMTC_Get() AS_Get(AS_appSig_mpiRead_bytesMTC_Index)
#define AS_appSig_mpiRead_bytesMTC_Set(dValue) AS_Set(AS_appSig_mpiRead_bytesMTC_Index, dValue)
#define AS_appSig_mpiRead_bytesMTC_GetAt(offset) AS_GetAt(AS_appSig_mpiRead_bytesMTC_Index, offset)
#define AS_appSig_mpiRead_bytesMTC_SetAt(offset, dValue) AS_SetAt(AS_appSig_mpiRead_bytesMTC_Index, offset, dValue)
#define AS_appSig_mpiRead_bytesMTC_GetSize() AS_GetAt(AS_appSig_mpiRead_bytesMTC_Index, -1)
#define AS_appSig_mpiRead_bytesMTC_SetSize(dValue) AS_SetAt(AS_appSig_mpiRead_bytesMTC_Index, -1, dValue)
#define AS_appSig_mpiRead_bytesMTC_GetText(szValue) AS_GetText(AS_appSig_mpiRead_bytesMTC_Index, szValue, -1)
#define AS_appSig_mpiRead_bytesMTC_SetText(szValue) AS_SetText(AS_appSig_mpiRead_bytesMTC_Index, szValue, -1)
#define AS_appSig_mpiRead_bytesMTC_GetTextLen(szValue, len) AS_GetText(AS_appSig_mpiRead_bytesMTC_Index, szValue, len)
#define AS_appSig_mpiRead_bytesMTC_SetTextLen(szValue, len) AS_SetText(AS_appSig_mpiRead_bytesMTC_Index, szValue, len)

extern int AS_appSig_mpiRead_MTC_Index; // sig123
#define AS_appSig_mpiRead_MTC_Get() AS_Get(AS_appSig_mpiRead_MTC_Index)
#define AS_appSig_mpiRead_MTC_Set(dValue) AS_Set(AS_appSig_mpiRead_MTC_Index, dValue)
#define AS_appSig_mpiRead_MTC_GetTextW(szValue) AS_GetTextW(AS_appSig_mpiRead_MTC_Index, szValue)
#define AS_appSig_mpiRead_MTC_SetTextW(szValue) CM_GetSetValue(g_uiHandle, CM_GETSET_SET_APP_SIGNAL_TEXT, AS_appSig_mpiRead_MTC_Index, szValue)
#define AS_appSig_mpiRead_MTC_GetText(szValue) AS_GetText(AS_appSig_mpiRead_MTC_Index, szValue, -1)
#define AS_appSig_mpiRead_MTC_SetText(szValue) AS_SetText(AS_appSig_mpiRead_MTC_Index, szValue, -1)
#define AS_appSig_mpiRead_MTC_GetTextLen(szValue, len) AS_GetText(AS_appSig_mpiRead_MTC_Index, szValue, len)
#define AS_appSig_mpiRead_MTC_SetTextLen(szValue, len) AS_SetText(AS_appSig_mpiRead_MTC_Index, szValue, len)

extern int AS_appSig_C_mpiWriteSubStepsDelay_Index; // sig124
#define AS_appSig_C_mpiWriteSubStepsDelay_Get() AS_Get(AS_appSig_C_mpiWriteSubStepsDelay_Index)
#define AS_appSig_C_mpiWriteSubStepsDelay_Set(dValue) AS_Set(AS_appSig_C_mpiWriteSubStepsDelay_Index, dValue)

extern int AS_appSig_C_mpiWriteSubStepDelay_MTC_Index; // sig148
#define AS_appSig_C_mpiWriteSubStepDelay_MTC_Get() AS_Get(AS_appSig_C_mpiWriteSubStepDelay_MTC_Index)
#define AS_appSig_C_mpiWriteSubStepDelay_MTC_Set(dValue) AS_Set(AS_appSig_C_mpiWriteSubStepDelay_MTC_Index, dValue)

extern int AS_appSig_C_mpiWriteStepsDelay_Index; // sig125
#define AS_appSig_C_mpiWriteStepsDelay_Get() AS_Get(AS_appSig_C_mpiWriteStepsDelay_Index)
#define AS_appSig_C_mpiWriteStepsDelay_Set(dValue) AS_Set(AS_appSig_C_mpiWriteStepsDelay_Index, dValue)

extern int AS_appSig_mpiRead_bytesECUID_Index; // sig126
#define AS_appSig_mpiRead_bytesECUID_Get() AS_Get(AS_appSig_mpiRead_bytesECUID_Index)
#define AS_appSig_mpiRead_bytesECUID_Set(dValue) AS_Set(AS_appSig_mpiRead_bytesECUID_Index, dValue)
#define AS_appSig_mpiRead_bytesECUID_GetAt(offset) AS_GetAt(AS_appSig_mpiRead_bytesECUID_Index, offset)
#define AS_appSig_mpiRead_bytesECUID_SetAt(offset, dValue) AS_SetAt(AS_appSig_mpiRead_bytesECUID_Index, offset, dValue)
#define AS_appSig_mpiRead_bytesECUID_GetSize() AS_GetAt(AS_appSig_mpiRead_bytesECUID_Index, -1)
#define AS_appSig_mpiRead_bytesECUID_SetSize(dValue) AS_SetAt(AS_appSig_mpiRead_bytesECUID_Index, -1, dValue)
#define AS_appSig_mpiRead_bytesECUID_GetText(szValue) AS_GetText(AS_appSig_mpiRead_bytesECUID_Index, szValue, -1)
#define AS_appSig_mpiRead_bytesECUID_SetText(szValue) AS_SetText(AS_appSig_mpiRead_bytesECUID_Index, szValue, -1)
#define AS_appSig_mpiRead_bytesECUID_GetTextLen(szValue, len) AS_GetText(AS_appSig_mpiRead_bytesECUID_Index, szValue, len)
#define AS_appSig_mpiRead_bytesECUID_SetTextLen(szValue, len) AS_SetText(AS_appSig_mpiRead_bytesECUID_Index, szValue, len)

extern int AS_appSig_mpiRead_ECUID_Index; // sig127
#define AS_appSig_mpiRead_ECUID_Get() AS_Get(AS_appSig_mpiRead_ECUID_Index)
#define AS_appSig_mpiRead_ECUID_Set(dValue) AS_Set(AS_appSig_mpiRead_ECUID_Index, dValue)
#define AS_appSig_mpiRead_ECUID_GetTextW(szValue) AS_GetTextW(AS_appSig_mpiRead_ECUID_Index, szValue)
#define AS_appSig_mpiRead_ECUID_SetTextW(szValue) CM_GetSetValue(g_uiHandle, CM_GETSET_SET_APP_SIGNAL_TEXT, AS_appSig_mpiRead_ECUID_Index, szValue)
#define AS_appSig_mpiRead_ECUID_GetText(szValue) AS_GetText(AS_appSig_mpiRead_ECUID_Index, szValue, -1)
#define AS_appSig_mpiRead_ECUID_SetText(szValue) AS_SetText(AS_appSig_mpiRead_ECUID_Index, szValue, -1)
#define AS_appSig_mpiRead_ECUID_GetTextLen(szValue, len) AS_GetText(AS_appSig_mpiRead_ECUID_Index, szValue, len)
#define AS_appSig_mpiRead_ECUID_SetTextLen(szValue, len) AS_SetText(AS_appSig_mpiRead_ECUID_Index, szValue, len)

extern int AS_appSig_mpiRead_EMPN_Index; // sig128
#define AS_appSig_mpiRead_EMPN_Get() AS_Get(AS_appSig_mpiRead_EMPN_Index)
#define AS_appSig_mpiRead_EMPN_Set(dValue) AS_Set(AS_appSig_mpiRead_EMPN_Index, dValue)

extern int AS_appSig_mpiRead_BMPN_Index; // sig129
#define AS_appSig_mpiRead_BMPN_Get() AS_Get(AS_appSig_mpiRead_BMPN_Index)
#define AS_appSig_mpiRead_BMPN_Set(dValue) AS_Set(AS_appSig_mpiRead_BMPN_Index, dValue)

extern int AS_appSig_mpiRead_bytesEMPNAC_Index; // sig130
#define AS_appSig_mpiRead_bytesEMPNAC_Get() AS_Get(AS_appSig_mpiRead_bytesEMPNAC_Index)
#define AS_appSig_mpiRead_bytesEMPNAC_Set(dValue) AS_Set(AS_appSig_mpiRead_bytesEMPNAC_Index, dValue)
#define AS_appSig_mpiRead_bytesEMPNAC_GetAt(offset) AS_GetAt(AS_appSig_mpiRead_bytesEMPNAC_Index, offset)
#define AS_appSig_mpiRead_bytesEMPNAC_SetAt(offset, dValue) AS_SetAt(AS_appSig_mpiRead_bytesEMPNAC_Index, offset, dValue)
#define AS_appSig_mpiRead_bytesEMPNAC_GetSize() AS_GetAt(AS_appSig_mpiRead_bytesEMPNAC_Index, -1)
#define AS_appSig_mpiRead_bytesEMPNAC_SetSize(dValue) AS_SetAt(AS_appSig_mpiRead_bytesEMPNAC_Index, -1, dValue)
#define AS_appSig_mpiRead_bytesEMPNAC_GetText(szValue) AS_GetText(AS_appSig_mpiRead_bytesEMPNAC_Index, szValue, -1)
#define AS_appSig_mpiRead_bytesEMPNAC_SetText(szValue) AS_SetText(AS_appSig_mpiRead_bytesEMPNAC_Index, szValue, -1)
#define AS_appSig_mpiRead_bytesEMPNAC_GetTextLen(szValue, len) AS_GetText(AS_appSig_mpiRead_bytesEMPNAC_Index, szValue, len)
#define AS_appSig_mpiRead_bytesEMPNAC_SetTextLen(szValue, len) AS_SetText(AS_appSig_mpiRead_bytesEMPNAC_Index, szValue, len)

extern int AS_appSig_mpiRead_bytesBMPNAC_Index; // sig131
#define AS_appSig_mpiRead_bytesBMPNAC_Get() AS_Get(AS_appSig_mpiRead_bytesBMPNAC_Index)
#define AS_appSig_mpiRead_bytesBMPNAC_Set(dValue) AS_Set(AS_appSig_mpiRead_bytesBMPNAC_Index, dValue)
#define AS_appSig_mpiRead_bytesBMPNAC_GetAt(offset) AS_GetAt(AS_appSig_mpiRead_bytesBMPNAC_Index, offset)
#define AS_appSig_mpiRead_bytesBMPNAC_SetAt(offset, dValue) AS_SetAt(AS_appSig_mpiRead_bytesBMPNAC_Index, offset, dValue)
#define AS_appSig_mpiRead_bytesBMPNAC_GetSize() AS_GetAt(AS_appSig_mpiRead_bytesBMPNAC_Index, -1)
#define AS_appSig_mpiRead_bytesBMPNAC_SetSize(dValue) AS_SetAt(AS_appSig_mpiRead_bytesBMPNAC_Index, -1, dValue)
#define AS_appSig_mpiRead_bytesBMPNAC_GetText(szValue) AS_GetText(AS_appSig_mpiRead_bytesBMPNAC_Index, szValue, -1)
#define AS_appSig_mpiRead_bytesBMPNAC_SetText(szValue) AS_SetText(AS_appSig_mpiRead_bytesBMPNAC_Index, szValue, -1)
#define AS_appSig_mpiRead_bytesBMPNAC_GetTextLen(szValue, len) AS_GetText(AS_appSig_mpiRead_bytesBMPNAC_Index, szValue, len)
#define AS_appSig_mpiRead_bytesBMPNAC_SetTextLen(szValue, len) AS_SetText(AS_appSig_mpiRead_bytesBMPNAC_Index, szValue, len)

extern int AS_appSig_mpiRead_bytesVPPS_Index; // sig132
#define AS_appSig_mpiRead_bytesVPPS_Get() AS_Get(AS_appSig_mpiRead_bytesVPPS_Index)
#define AS_appSig_mpiRead_bytesVPPS_Set(dValue) AS_Set(AS_appSig_mpiRead_bytesVPPS_Index, dValue)
#define AS_appSig_mpiRead_bytesVPPS_GetAt(offset) AS_GetAt(AS_appSig_mpiRead_bytesVPPS_Index, offset)
#define AS_appSig_mpiRead_bytesVPPS_SetAt(offset, dValue) AS_SetAt(AS_appSig_mpiRead_bytesVPPS_Index, offset, dValue)
#define AS_appSig_mpiRead_bytesVPPS_GetSize() AS_GetAt(AS_appSig_mpiRead_bytesVPPS_Index, -1)
#define AS_appSig_mpiRead_bytesVPPS_SetSize(dValue) AS_SetAt(AS_appSig_mpiRead_bytesVPPS_Index, -1, dValue)
#define AS_appSig_mpiRead_bytesVPPS_GetText(szValue) AS_GetText(AS_appSig_mpiRead_bytesVPPS_Index, szValue, -1)
#define AS_appSig_mpiRead_bytesVPPS_SetText(szValue) AS_SetText(AS_appSig_mpiRead_bytesVPPS_Index, szValue, -1)
#define AS_appSig_mpiRead_bytesVPPS_GetTextLen(szValue, len) AS_GetText(AS_appSig_mpiRead_bytesVPPS_Index, szValue, len)
#define AS_appSig_mpiRead_bytesVPPS_SetTextLen(szValue, len) AS_SetText(AS_appSig_mpiRead_bytesVPPS_Index, szValue, len)

extern int AS_appSig_mpiRead_bytesDUNS_Index; // sig133
#define AS_appSig_mpiRead_bytesDUNS_Get() AS_Get(AS_appSig_mpiRead_bytesDUNS_Index)
#define AS_appSig_mpiRead_bytesDUNS_Set(dValue) AS_Set(AS_appSig_mpiRead_bytesDUNS_Index, dValue)
#define AS_appSig_mpiRead_bytesDUNS_GetAt(offset) AS_GetAt(AS_appSig_mpiRead_bytesDUNS_Index, offset)
#define AS_appSig_mpiRead_bytesDUNS_SetAt(offset, dValue) AS_SetAt(AS_appSig_mpiRead_bytesDUNS_Index, offset, dValue)
#define AS_appSig_mpiRead_bytesDUNS_GetSize() AS_GetAt(AS_appSig_mpiRead_bytesDUNS_Index, -1)
#define AS_appSig_mpiRead_bytesDUNS_SetSize(dValue) AS_SetAt(AS_appSig_mpiRead_bytesDUNS_Index, -1, dValue)
#define AS_appSig_mpiRead_bytesDUNS_GetText(szValue) AS_GetText(AS_appSig_mpiRead_bytesDUNS_Index, szValue, -1)
#define AS_appSig_mpiRead_bytesDUNS_SetText(szValue) AS_SetText(AS_appSig_mpiRead_bytesDUNS_Index, szValue, -1)
#define AS_appSig_mpiRead_bytesDUNS_GetTextLen(szValue, len) AS_GetText(AS_appSig_mpiRead_bytesDUNS_Index, szValue, len)
#define AS_appSig_mpiRead_bytesDUNS_SetTextLen(szValue, len) AS_SetText(AS_appSig_mpiRead_bytesDUNS_Index, szValue, len)

extern int AS_appSig_mpiRead_VPPS_Index; // sig134
#define AS_appSig_mpiRead_VPPS_Get() AS_Get(AS_appSig_mpiRead_VPPS_Index)
#define AS_appSig_mpiRead_VPPS_Set(dValue) AS_Set(AS_appSig_mpiRead_VPPS_Index, dValue)
#define AS_appSig_mpiRead_VPPS_GetTextW(szValue) AS_GetTextW(AS_appSig_mpiRead_VPPS_Index, szValue)
#define AS_appSig_mpiRead_VPPS_SetTextW(szValue) CM_GetSetValue(g_uiHandle, CM_GETSET_SET_APP_SIGNAL_TEXT, AS_appSig_mpiRead_VPPS_Index, szValue)
#define AS_appSig_mpiRead_VPPS_GetText(szValue) AS_GetText(AS_appSig_mpiRead_VPPS_Index, szValue, -1)
#define AS_appSig_mpiRead_VPPS_SetText(szValue) AS_SetText(AS_appSig_mpiRead_VPPS_Index, szValue, -1)
#define AS_appSig_mpiRead_VPPS_GetTextLen(szValue, len) AS_GetText(AS_appSig_mpiRead_VPPS_Index, szValue, len)
#define AS_appSig_mpiRead_VPPS_SetTextLen(szValue, len) AS_SetText(AS_appSig_mpiRead_VPPS_Index, szValue, len)

extern int AS_appSig_mpiRead_DUNS_Index; // sig135
#define AS_appSig_mpiRead_DUNS_Get() AS_Get(AS_appSig_mpiRead_DUNS_Index)
#define AS_appSig_mpiRead_DUNS_Set(dValue) AS_Set(AS_appSig_mpiRead_DUNS_Index, dValue)
#define AS_appSig_mpiRead_DUNS_GetTextW(szValue) AS_GetTextW(AS_appSig_mpiRead_DUNS_Index, szValue)
#define AS_appSig_mpiRead_DUNS_SetTextW(szValue) CM_GetSetValue(g_uiHandle, CM_GETSET_SET_APP_SIGNAL_TEXT, AS_appSig_mpiRead_DUNS_Index, szValue)
#define AS_appSig_mpiRead_DUNS_GetText(szValue) AS_GetText(AS_appSig_mpiRead_DUNS_Index, szValue, -1)
#define AS_appSig_mpiRead_DUNS_SetText(szValue) AS_SetText(AS_appSig_mpiRead_DUNS_Index, szValue, -1)
#define AS_appSig_mpiRead_DUNS_GetTextLen(szValue, len) AS_GetText(AS_appSig_mpiRead_DUNS_Index, szValue, len)
#define AS_appSig_mpiRead_DUNS_SetTextLen(szValue, len) AS_SetText(AS_appSig_mpiRead_DUNS_Index, szValue, len)

extern int AS_appSig_mpiRead_EMPNAC_Index; // sig136
#define AS_appSig_mpiRead_EMPNAC_Get() AS_Get(AS_appSig_mpiRead_EMPNAC_Index)
#define AS_appSig_mpiRead_EMPNAC_Set(dValue) AS_Set(AS_appSig_mpiRead_EMPNAC_Index, dValue)
#define AS_appSig_mpiRead_EMPNAC_GetTextW(szValue) AS_GetTextW(AS_appSig_mpiRead_EMPNAC_Index, szValue)
#define AS_appSig_mpiRead_EMPNAC_SetTextW(szValue) CM_GetSetValue(g_uiHandle, CM_GETSET_SET_APP_SIGNAL_TEXT, AS_appSig_mpiRead_EMPNAC_Index, szValue)
#define AS_appSig_mpiRead_EMPNAC_GetText(szValue) AS_GetText(AS_appSig_mpiRead_EMPNAC_Index, szValue, -1)
#define AS_appSig_mpiRead_EMPNAC_SetText(szValue) AS_SetText(AS_appSig_mpiRead_EMPNAC_Index, szValue, -1)
#define AS_appSig_mpiRead_EMPNAC_GetTextLen(szValue, len) AS_GetText(AS_appSig_mpiRead_EMPNAC_Index, szValue, len)
#define AS_appSig_mpiRead_EMPNAC_SetTextLen(szValue, len) AS_SetText(AS_appSig_mpiRead_EMPNAC_Index, szValue, len)

extern int AS_appSig_mpiRead_BMPNAC_Index; // sig137
#define AS_appSig_mpiRead_BMPNAC_Get() AS_Get(AS_appSig_mpiRead_BMPNAC_Index)
#define AS_appSig_mpiRead_BMPNAC_Set(dValue) AS_Set(AS_appSig_mpiRead_BMPNAC_Index, dValue)
#define AS_appSig_mpiRead_BMPNAC_GetTextW(szValue) AS_GetTextW(AS_appSig_mpiRead_BMPNAC_Index, szValue)
#define AS_appSig_mpiRead_BMPNAC_SetTextW(szValue) CM_GetSetValue(g_uiHandle, CM_GETSET_SET_APP_SIGNAL_TEXT, AS_appSig_mpiRead_BMPNAC_Index, szValue)
#define AS_appSig_mpiRead_BMPNAC_GetText(szValue) AS_GetText(AS_appSig_mpiRead_BMPNAC_Index, szValue, -1)
#define AS_appSig_mpiRead_BMPNAC_SetText(szValue) AS_SetText(AS_appSig_mpiRead_BMPNAC_Index, szValue, -1)
#define AS_appSig_mpiRead_BMPNAC_GetTextLen(szValue, len) AS_GetText(AS_appSig_mpiRead_BMPNAC_Index, szValue, len)
#define AS_appSig_mpiRead_BMPNAC_SetTextLen(szValue, len) AS_SetText(AS_appSig_mpiRead_BMPNAC_Index, szValue, len)

extern int AS_appSig_mpiRead_ECUID_SN_Index; // sig138
#define AS_appSig_mpiRead_ECUID_SN_Get() AS_Get(AS_appSig_mpiRead_ECUID_SN_Index)
#define AS_appSig_mpiRead_ECUID_SN_Set(dValue) AS_Set(AS_appSig_mpiRead_ECUID_SN_Index, dValue)

extern int AS_appSig_mpiRead_ECUID_BMPN_Index; // sig139
#define AS_appSig_mpiRead_ECUID_BMPN_Get() AS_Get(AS_appSig_mpiRead_ECUID_BMPN_Index)
#define AS_appSig_mpiRead_ECUID_BMPN_Set(dValue) AS_Set(AS_appSig_mpiRead_ECUID_BMPN_Index, dValue)

extern int AS_appSig_mpiRead_EMPNStr_Index; // sig140
#define AS_appSig_mpiRead_EMPNStr_Get() AS_Get(AS_appSig_mpiRead_EMPNStr_Index)
#define AS_appSig_mpiRead_EMPNStr_Set(dValue) AS_Set(AS_appSig_mpiRead_EMPNStr_Index, dValue)
#define AS_appSig_mpiRead_EMPNStr_GetTextW(szValue) AS_GetTextW(AS_appSig_mpiRead_EMPNStr_Index, szValue)
#define AS_appSig_mpiRead_EMPNStr_SetTextW(szValue) CM_GetSetValue(g_uiHandle, CM_GETSET_SET_APP_SIGNAL_TEXT, AS_appSig_mpiRead_EMPNStr_Index, szValue)
#define AS_appSig_mpiRead_EMPNStr_GetText(szValue) AS_GetText(AS_appSig_mpiRead_EMPNStr_Index, szValue, -1)
#define AS_appSig_mpiRead_EMPNStr_SetText(szValue) AS_SetText(AS_appSig_mpiRead_EMPNStr_Index, szValue, -1)
#define AS_appSig_mpiRead_EMPNStr_GetTextLen(szValue, len) AS_GetText(AS_appSig_mpiRead_EMPNStr_Index, szValue, len)
#define AS_appSig_mpiRead_EMPNStr_SetTextLen(szValue, len) AS_SetText(AS_appSig_mpiRead_EMPNStr_Index, szValue, len)

extern int AS_appSig_mpiRead_BMPNStr_Index; // sig141
#define AS_appSig_mpiRead_BMPNStr_Get() AS_Get(AS_appSig_mpiRead_BMPNStr_Index)
#define AS_appSig_mpiRead_BMPNStr_Set(dValue) AS_Set(AS_appSig_mpiRead_BMPNStr_Index, dValue)
#define AS_appSig_mpiRead_BMPNStr_GetTextW(szValue) AS_GetTextW(AS_appSig_mpiRead_BMPNStr_Index, szValue)
#define AS_appSig_mpiRead_BMPNStr_SetTextW(szValue) CM_GetSetValue(g_uiHandle, CM_GETSET_SET_APP_SIGNAL_TEXT, AS_appSig_mpiRead_BMPNStr_Index, szValue)
#define AS_appSig_mpiRead_BMPNStr_GetText(szValue) AS_GetText(AS_appSig_mpiRead_BMPNStr_Index, szValue, -1)
#define AS_appSig_mpiRead_BMPNStr_SetText(szValue) AS_SetText(AS_appSig_mpiRead_BMPNStr_Index, szValue, -1)
#define AS_appSig_mpiRead_BMPNStr_GetTextLen(szValue, len) AS_GetText(AS_appSig_mpiRead_BMPNStr_Index, szValue, len)
#define AS_appSig_mpiRead_BMPNStr_SetTextLen(szValue, len) AS_SetText(AS_appSig_mpiRead_BMPNStr_Index, szValue, len)

extern int AS_appSig_mpiRead_ECUID_SNStr_Index; // sig142
#define AS_appSig_mpiRead_ECUID_SNStr_Get() AS_Get(AS_appSig_mpiRead_ECUID_SNStr_Index)
#define AS_appSig_mpiRead_ECUID_SNStr_Set(dValue) AS_Set(AS_appSig_mpiRead_ECUID_SNStr_Index, dValue)
#define AS_appSig_mpiRead_ECUID_SNStr_GetTextW(szValue) AS_GetTextW(AS_appSig_mpiRead_ECUID_SNStr_Index, szValue)
#define AS_appSig_mpiRead_ECUID_SNStr_SetTextW(szValue) CM_GetSetValue(g_uiHandle, CM_GETSET_SET_APP_SIGNAL_TEXT, AS_appSig_mpiRead_ECUID_SNStr_Index, szValue)
#define AS_appSig_mpiRead_ECUID_SNStr_GetText(szValue) AS_GetText(AS_appSig_mpiRead_ECUID_SNStr_Index, szValue, -1)
#define AS_appSig_mpiRead_ECUID_SNStr_SetText(szValue) AS_SetText(AS_appSig_mpiRead_ECUID_SNStr_Index, szValue, -1)
#define AS_appSig_mpiRead_ECUID_SNStr_GetTextLen(szValue, len) AS_GetText(AS_appSig_mpiRead_ECUID_SNStr_Index, szValue, len)
#define AS_appSig_mpiRead_ECUID_SNStr_SetTextLen(szValue, len) AS_SetText(AS_appSig_mpiRead_ECUID_SNStr_Index, szValue, len)

extern int AS_appSig_mpiRead_ECUID_BMPNStr_Index; // sig143
#define AS_appSig_mpiRead_ECUID_BMPNStr_Get() AS_Get(AS_appSig_mpiRead_ECUID_BMPNStr_Index)
#define AS_appSig_mpiRead_ECUID_BMPNStr_Set(dValue) AS_Set(AS_appSig_mpiRead_ECUID_BMPNStr_Index, dValue)
#define AS_appSig_mpiRead_ECUID_BMPNStr_GetTextW(szValue) AS_GetTextW(AS_appSig_mpiRead_ECUID_BMPNStr_Index, szValue)
#define AS_appSig_mpiRead_ECUID_BMPNStr_SetTextW(szValue) CM_GetSetValue(g_uiHandle, CM_GETSET_SET_APP_SIGNAL_TEXT, AS_appSig_mpiRead_ECUID_BMPNStr_Index, szValue)
#define AS_appSig_mpiRead_ECUID_BMPNStr_GetText(szValue) AS_GetText(AS_appSig_mpiRead_ECUID_BMPNStr_Index, szValue, -1)
#define AS_appSig_mpiRead_ECUID_BMPNStr_SetText(szValue) AS_SetText(AS_appSig_mpiRead_ECUID_BMPNStr_Index, szValue, -1)
#define AS_appSig_mpiRead_ECUID_BMPNStr_GetTextLen(szValue, len) AS_GetText(AS_appSig_mpiRead_ECUID_BMPNStr_Index, szValue, len)
#define AS_appSig_mpiRead_ECUID_BMPNStr_SetTextLen(szValue, len) AS_SetText(AS_appSig_mpiRead_ECUID_BMPNStr_Index, szValue, len)

extern int AS_appSig_mpiWrite_Model_Index; // sig144
#define AS_appSig_mpiWrite_Model_Get() AS_Get(AS_appSig_mpiWrite_Model_Index)
#define AS_appSig_mpiWrite_Model_Set(dValue) AS_Set(AS_appSig_mpiWrite_Model_Index, dValue)

extern int AS_appSig_mpiWriteState_Index; // sig145
#define AS_appSig_mpiWriteState_Get() AS_Get(AS_appSig_mpiWriteState_Index)
#define AS_appSig_mpiWriteState_Set(dValue) AS_Set(AS_appSig_mpiWriteState_Index, dValue)
#define AS_appSig_mpiWriteState_GetTextW(szValue) AS_GetTextW(AS_appSig_mpiWriteState_Index, szValue)
#define AS_appSig_mpiWriteState_SetTextW(szValue) CM_GetSetValue(g_uiHandle, CM_GETSET_SET_APP_SIGNAL_TEXT, AS_appSig_mpiWriteState_Index, szValue)
#define AS_appSig_mpiWriteState_GetText(szValue) AS_GetText(AS_appSig_mpiWriteState_Index, szValue, -1)
#define AS_appSig_mpiWriteState_SetText(szValue) AS_SetText(AS_appSig_mpiWriteState_Index, szValue, -1)
#define AS_appSig_mpiWriteState_GetTextLen(szValue, len) AS_GetText(AS_appSig_mpiWriteState_Index, szValue, len)
#define AS_appSig_mpiWriteState_SetTextLen(szValue, len) AS_SetText(AS_appSig_mpiWriteState_Index, szValue, len)

extern int AS_appSig_C_mpiReadStepsDelay_Index; // sig146
#define AS_appSig_C_mpiReadStepsDelay_Get() AS_Get(AS_appSig_C_mpiReadStepsDelay_Index)
#define AS_appSig_C_mpiReadStepsDelay_Set(dValue) AS_Set(AS_appSig_C_mpiReadStepsDelay_Index, dValue)

extern int AS_appSig_C_mpiReadSubStepsDelay_Index; // sig147
#define AS_appSig_C_mpiReadSubStepsDelay_Get() AS_Get(AS_appSig_C_mpiReadSubStepsDelay_Index)
#define AS_appSig_C_mpiReadSubStepsDelay_Set(dValue) AS_Set(AS_appSig_C_mpiReadSubStepsDelay_Index, dValue)

extern int AS_appSig_sapaWriteSteps_isPassed_Index; // sig167
#define AS_appSig_sapaWriteSteps_isPassed_Get() AS_Get(AS_appSig_sapaWriteSteps_isPassed_Index)
#define AS_appSig_sapaWriteSteps_isPassed_Set(dValue) AS_Set(AS_appSig_sapaWriteSteps_isPassed_Index, dValue)
#define AS_appSig_sapaWriteSteps_isPassed_GetAt(offset) AS_GetAt(AS_appSig_sapaWriteSteps_isPassed_Index, offset)
#define AS_appSig_sapaWriteSteps_isPassed_SetAt(offset, dValue) AS_SetAt(AS_appSig_sapaWriteSteps_isPassed_Index, offset, dValue)
#define AS_appSig_sapaWriteSteps_isPassed_GetSize() AS_GetAt(AS_appSig_sapaWriteSteps_isPassed_Index, -1)
#define AS_appSig_sapaWriteSteps_isPassed_SetSize(dValue) AS_SetAt(AS_appSig_sapaWriteSteps_isPassed_Index, -1, dValue)
#define AS_appSig_sapaWriteSteps_isPassed_GetText(szValue) AS_GetText(AS_appSig_sapaWriteSteps_isPassed_Index, szValue, -1)
#define AS_appSig_sapaWriteSteps_isPassed_SetText(szValue) AS_SetText(AS_appSig_sapaWriteSteps_isPassed_Index, szValue, -1)
#define AS_appSig_sapaWriteSteps_isPassed_GetTextLen(szValue, len) AS_GetText(AS_appSig_sapaWriteSteps_isPassed_Index, szValue, len)
#define AS_appSig_sapaWriteSteps_isPassed_SetTextLen(szValue, len) AS_SetText(AS_appSig_sapaWriteSteps_isPassed_Index, szValue, len)

extern int AS_appSig_sapaWrite_SeedKey_Index; // sig150
#define AS_appSig_sapaWrite_SeedKey_Get() AS_Get(AS_appSig_sapaWrite_SeedKey_Index)
#define AS_appSig_sapaWrite_SeedKey_Set(dValue) AS_Set(AS_appSig_sapaWrite_SeedKey_Index, dValue)
#define AS_appSig_sapaWrite_SeedKey_GetTextW(szValue) AS_GetTextW(AS_appSig_sapaWrite_SeedKey_Index, szValue)
#define AS_appSig_sapaWrite_SeedKey_SetTextW(szValue) CM_GetSetValue(g_uiHandle, CM_GETSET_SET_APP_SIGNAL_TEXT, AS_appSig_sapaWrite_SeedKey_Index, szValue)
#define AS_appSig_sapaWrite_SeedKey_GetText(szValue) AS_GetText(AS_appSig_sapaWrite_SeedKey_Index, szValue, -1)
#define AS_appSig_sapaWrite_SeedKey_SetText(szValue) AS_SetText(AS_appSig_sapaWrite_SeedKey_Index, szValue, -1)
#define AS_appSig_sapaWrite_SeedKey_GetTextLen(szValue, len) AS_GetText(AS_appSig_sapaWrite_SeedKey_Index, szValue, len)
#define AS_appSig_sapaWrite_SeedKey_SetTextLen(szValue, len) AS_SetText(AS_appSig_sapaWrite_SeedKey_Index, szValue, len)

extern int AS_appSig_sapaWrite_bytesSeedKey_Index; // sig151
#define AS_appSig_sapaWrite_bytesSeedKey_Get() AS_Get(AS_appSig_sapaWrite_bytesSeedKey_Index)
#define AS_appSig_sapaWrite_bytesSeedKey_Set(dValue) AS_Set(AS_appSig_sapaWrite_bytesSeedKey_Index, dValue)
#define AS_appSig_sapaWrite_bytesSeedKey_GetAt(offset) AS_GetAt(AS_appSig_sapaWrite_bytesSeedKey_Index, offset)
#define AS_appSig_sapaWrite_bytesSeedKey_SetAt(offset, dValue) AS_SetAt(AS_appSig_sapaWrite_bytesSeedKey_Index, offset, dValue)
#define AS_appSig_sapaWrite_bytesSeedKey_GetSize() AS_GetAt(AS_appSig_sapaWrite_bytesSeedKey_Index, -1)
#define AS_appSig_sapaWrite_bytesSeedKey_SetSize(dValue) AS_SetAt(AS_appSig_sapaWrite_bytesSeedKey_Index, -1, dValue)
#define AS_appSig_sapaWrite_bytesSeedKey_GetText(szValue) AS_GetText(AS_appSig_sapaWrite_bytesSeedKey_Index, szValue, -1)
#define AS_appSig_sapaWrite_bytesSeedKey_SetText(szValue) AS_SetText(AS_appSig_sapaWrite_bytesSeedKey_Index, szValue, -1)
#define AS_appSig_sapaWrite_bytesSeedKey_GetTextLen(szValue, len) AS_GetText(AS_appSig_sapaWrite_bytesSeedKey_Index, szValue, len)
#define AS_appSig_sapaWrite_bytesSeedKey_SetTextLen(szValue, len) AS_SetText(AS_appSig_sapaWrite_bytesSeedKey_Index, szValue, len)

extern int AS_appSig_sapaWrite_Seed_Index; // sig152
#define AS_appSig_sapaWrite_Seed_Get() AS_Get(AS_appSig_sapaWrite_Seed_Index)
#define AS_appSig_sapaWrite_Seed_Set(dValue) AS_Set(AS_appSig_sapaWrite_Seed_Index, dValue)
#define AS_appSig_sapaWrite_Seed_GetTextW(szValue) AS_GetTextW(AS_appSig_sapaWrite_Seed_Index, szValue)
#define AS_appSig_sapaWrite_Seed_SetTextW(szValue) CM_GetSetValue(g_uiHandle, CM_GETSET_SET_APP_SIGNAL_TEXT, AS_appSig_sapaWrite_Seed_Index, szValue)
#define AS_appSig_sapaWrite_Seed_GetText(szValue) AS_GetText(AS_appSig_sapaWrite_Seed_Index, szValue, -1)
#define AS_appSig_sapaWrite_Seed_SetText(szValue) AS_SetText(AS_appSig_sapaWrite_Seed_Index, szValue, -1)
#define AS_appSig_sapaWrite_Seed_GetTextLen(szValue, len) AS_GetText(AS_appSig_sapaWrite_Seed_Index, szValue, len)
#define AS_appSig_sapaWrite_Seed_SetTextLen(szValue, len) AS_SetText(AS_appSig_sapaWrite_Seed_Index, szValue, len)

extern int AS_appSig_sapaWrite_bytesSeed_Index; // sig153
#define AS_appSig_sapaWrite_bytesSeed_Get() AS_Get(AS_appSig_sapaWrite_bytesSeed_Index)
#define AS_appSig_sapaWrite_bytesSeed_Set(dValue) AS_Set(AS_appSig_sapaWrite_bytesSeed_Index, dValue)
#define AS_appSig_sapaWrite_bytesSeed_GetAt(offset) AS_GetAt(AS_appSig_sapaWrite_bytesSeed_Index, offset)
#define AS_appSig_sapaWrite_bytesSeed_SetAt(offset, dValue) AS_SetAt(AS_appSig_sapaWrite_bytesSeed_Index, offset, dValue)
#define AS_appSig_sapaWrite_bytesSeed_GetSize() AS_GetAt(AS_appSig_sapaWrite_bytesSeed_Index, -1)
#define AS_appSig_sapaWrite_bytesSeed_SetSize(dValue) AS_SetAt(AS_appSig_sapaWrite_bytesSeed_Index, -1, dValue)
#define AS_appSig_sapaWrite_bytesSeed_GetText(szValue) AS_GetText(AS_appSig_sapaWrite_bytesSeed_Index, szValue, -1)
#define AS_appSig_sapaWrite_bytesSeed_SetText(szValue) AS_SetText(AS_appSig_sapaWrite_bytesSeed_Index, szValue, -1)
#define AS_appSig_sapaWrite_bytesSeed_GetTextLen(szValue, len) AS_GetText(AS_appSig_sapaWrite_bytesSeed_Index, szValue, len)
#define AS_appSig_sapaWrite_bytesSeed_SetTextLen(szValue, len) AS_SetText(AS_appSig_sapaWrite_bytesSeed_Index, szValue, len)

extern int AS_appSig_sapaRead_Seed_Index; // sig154
#define AS_appSig_sapaRead_Seed_Get() AS_Get(AS_appSig_sapaRead_Seed_Index)
#define AS_appSig_sapaRead_Seed_Set(dValue) AS_Set(AS_appSig_sapaRead_Seed_Index, dValue)
#define AS_appSig_sapaRead_Seed_GetTextW(szValue) AS_GetTextW(AS_appSig_sapaRead_Seed_Index, szValue)
#define AS_appSig_sapaRead_Seed_SetTextW(szValue) CM_GetSetValue(g_uiHandle, CM_GETSET_SET_APP_SIGNAL_TEXT, AS_appSig_sapaRead_Seed_Index, szValue)
#define AS_appSig_sapaRead_Seed_GetText(szValue) AS_GetText(AS_appSig_sapaRead_Seed_Index, szValue, -1)
#define AS_appSig_sapaRead_Seed_SetText(szValue) AS_SetText(AS_appSig_sapaRead_Seed_Index, szValue, -1)
#define AS_appSig_sapaRead_Seed_GetTextLen(szValue, len) AS_GetText(AS_appSig_sapaRead_Seed_Index, szValue, len)
#define AS_appSig_sapaRead_Seed_SetTextLen(szValue, len) AS_SetText(AS_appSig_sapaRead_Seed_Index, szValue, len)

extern int AS_appSig_sapaRead_bytesSeed_Index; // sig155
#define AS_appSig_sapaRead_bytesSeed_Get() AS_Get(AS_appSig_sapaRead_bytesSeed_Index)
#define AS_appSig_sapaRead_bytesSeed_Set(dValue) AS_Set(AS_appSig_sapaRead_bytesSeed_Index, dValue)
#define AS_appSig_sapaRead_bytesSeed_GetAt(offset) AS_GetAt(AS_appSig_sapaRead_bytesSeed_Index, offset)
#define AS_appSig_sapaRead_bytesSeed_SetAt(offset, dValue) AS_SetAt(AS_appSig_sapaRead_bytesSeed_Index, offset, dValue)
#define AS_appSig_sapaRead_bytesSeed_GetSize() AS_GetAt(AS_appSig_sapaRead_bytesSeed_Index, -1)
#define AS_appSig_sapaRead_bytesSeed_SetSize(dValue) AS_SetAt(AS_appSig_sapaRead_bytesSeed_Index, -1, dValue)
#define AS_appSig_sapaRead_bytesSeed_GetText(szValue) AS_GetText(AS_appSig_sapaRead_bytesSeed_Index, szValue, -1)
#define AS_appSig_sapaRead_bytesSeed_SetText(szValue) AS_SetText(AS_appSig_sapaRead_bytesSeed_Index, szValue, -1)
#define AS_appSig_sapaRead_bytesSeed_GetTextLen(szValue, len) AS_GetText(AS_appSig_sapaRead_bytesSeed_Index, szValue, len)
#define AS_appSig_sapaRead_bytesSeed_SetTextLen(szValue, len) AS_SetText(AS_appSig_sapaRead_bytesSeed_Index, szValue, len)

extern int AS_appSig_sapaReadSteps_isPassed_Index; // sig156
#define AS_appSig_sapaReadSteps_isPassed_Get() AS_Get(AS_appSig_sapaReadSteps_isPassed_Index)
#define AS_appSig_sapaReadSteps_isPassed_Set(dValue) AS_Set(AS_appSig_sapaReadSteps_isPassed_Index, dValue)
#define AS_appSig_sapaReadSteps_isPassed_GetAt(offset) AS_GetAt(AS_appSig_sapaReadSteps_isPassed_Index, offset)
#define AS_appSig_sapaReadSteps_isPassed_SetAt(offset, dValue) AS_SetAt(AS_appSig_sapaReadSteps_isPassed_Index, offset, dValue)
#define AS_appSig_sapaReadSteps_isPassed_GetSize() AS_GetAt(AS_appSig_sapaReadSteps_isPassed_Index, -1)
#define AS_appSig_sapaReadSteps_isPassed_SetSize(dValue) AS_SetAt(AS_appSig_sapaReadSteps_isPassed_Index, -1, dValue)
#define AS_appSig_sapaReadSteps_isPassed_GetText(szValue) AS_GetText(AS_appSig_sapaReadSteps_isPassed_Index, szValue, -1)
#define AS_appSig_sapaReadSteps_isPassed_SetText(szValue) AS_SetText(AS_appSig_sapaReadSteps_isPassed_Index, szValue, -1)
#define AS_appSig_sapaReadSteps_isPassed_GetTextLen(szValue, len) AS_GetText(AS_appSig_sapaReadSteps_isPassed_Index, szValue, len)
#define AS_appSig_sapaReadSteps_isPassed_SetTextLen(szValue, len) AS_SetText(AS_appSig_sapaReadSteps_isPassed_Index, szValue, len)

extern int AS_appSig_sapaWrite_lock_Index; // sig157
#define AS_appSig_sapaWrite_lock_Get() AS_Get(AS_appSig_sapaWrite_lock_Index)
#define AS_appSig_sapaWrite_lock_Set(dValue) AS_Set(AS_appSig_sapaWrite_lock_Index, dValue)

extern int AS_appSig_C_sapaWriteStepsDelay_Index; // sig169
#define AS_appSig_C_sapaWriteStepsDelay_Get() AS_Get(AS_appSig_C_sapaWriteStepsDelay_Index)
#define AS_appSig_C_sapaWriteStepsDelay_Set(dValue) AS_Set(AS_appSig_C_sapaWriteStepsDelay_Index, dValue)

extern int AS_appSig_C_sapaWriteSubStepDelay_SeedKey_Index; // sig168
#define AS_appSig_C_sapaWriteSubStepDelay_SeedKey_Get() AS_Get(AS_appSig_C_sapaWriteSubStepDelay_SeedKey_Index)
#define AS_appSig_C_sapaWriteSubStepDelay_SeedKey_Set(dValue) AS_Set(AS_appSig_C_sapaWriteSubStepDelay_SeedKey_Index, dValue)

extern int AS_appSig_C_step39_targetRawValueMin_Index; // sig158
#define AS_appSig_C_step39_targetRawValueMin_Get() AS_Get(AS_appSig_C_step39_targetRawValueMin_Index)
#define AS_appSig_C_step39_targetRawValueMin_Set(dValue) AS_Set(AS_appSig_C_step39_targetRawValueMin_Index, dValue)

extern int AS_appSig_C_step39_targetRawValueNormal_Index; // sig159
#define AS_appSig_C_step39_targetRawValueNormal_Get() AS_Get(AS_appSig_C_step39_targetRawValueNormal_Index)
#define AS_appSig_C_step39_targetRawValueNormal_Set(dValue) AS_Set(AS_appSig_C_step39_targetRawValueNormal_Index, dValue)

extern int AS_appSig_C_step39_targetRawValueMax_Index; // sig160
#define AS_appSig_C_step39_targetRawValueMax_Get() AS_Get(AS_appSig_C_step39_targetRawValueMax_Index)
#define AS_appSig_C_step39_targetRawValueMax_Set(dValue) AS_Set(AS_appSig_C_step39_targetRawValueMax_Index, dValue)

extern int AS_appSig_C_step40_targetRawValueMin_Index; // sig161
#define AS_appSig_C_step40_targetRawValueMin_Get() AS_Get(AS_appSig_C_step40_targetRawValueMin_Index)
#define AS_appSig_C_step40_targetRawValueMin_Set(dValue) AS_Set(AS_appSig_C_step40_targetRawValueMin_Index, dValue)

extern int AS_appSig_C_step40_targetRawValueNormal_Index; // sig162
#define AS_appSig_C_step40_targetRawValueNormal_Get() AS_Get(AS_appSig_C_step40_targetRawValueNormal_Index)
#define AS_appSig_C_step40_targetRawValueNormal_Set(dValue) AS_Set(AS_appSig_C_step40_targetRawValueNormal_Index, dValue)

extern int AS_appSig_C_step40_targetRawValueMax_Index; // sig163
#define AS_appSig_C_step40_targetRawValueMax_Get() AS_Get(AS_appSig_C_step40_targetRawValueMax_Index)
#define AS_appSig_C_step40_targetRawValueMax_Set(dValue) AS_Set(AS_appSig_C_step40_targetRawValueMax_Index, dValue)

extern int AS_appSig_step39_currPhyValue_Index; // sig164
#define AS_appSig_step39_currPhyValue_Get() AS_Get(AS_appSig_step39_currPhyValue_Index)
#define AS_appSig_step39_currPhyValue_Set(dValue) AS_Set(AS_appSig_step39_currPhyValue_Index, dValue)

extern int AS_appSig_step40_currPhyValue_Index; // sig165
#define AS_appSig_step40_currPhyValue_Get() AS_Get(AS_appSig_step40_currPhyValue_Index)
#define AS_appSig_step40_currPhyValue_Set(dValue) AS_Set(AS_appSig_step40_currPhyValue_Index, dValue)

extern int AS_appSig_step41_currPhyValue_Index; // sig166
#define AS_appSig_step41_currPhyValue_Get() AS_Get(AS_appSig_step41_currPhyValue_Index)
#define AS_appSig_step41_currPhyValue_Set(dValue) AS_Set(AS_appSig_step41_currPhyValue_Index, dValue)

extern int DG_$22_Read_Data_By_PID_Index;
void DG_$22_Read_Data_By_PID_Start();
void DG_$22_Read_Data_By_PID_Stop();
void DG_$22_Read_Data_By_PID_Save();
int DG_$22_Read_Data_By_PID_IsRunning();
int DG_$22_Read_Data_By_PID_NumMessagesCollected();
int DG_$22_Read_Data_By_PID_IsSuccessful();
int DG_$22_Read_Data_By_PID_ECUResponseCount();
double DG_$22_Read_Data_By_PID_TotalTimeAbs();
int DG_$22_Read_Data_By_PID_Last7FSubFunctionEx78();
int DG_$22_Read_Data_By_PID_7FCountEx78();
int DG_$22_Read_Data_By_PID_7FCountResponsePending();
extern int FB_fsMain_test_Index;
void FB_fsMain_test_Start();
void FB_fsMain_test_Stop();
void FB_fsMain_test_Trigger();
void FB_fsMain_test_Save();
double FB_fsMain_test_IsRunning();
double FB_fsMain_test_IsTriggered();
double FB_fsMain_test_NumCollected();
extern int FB_fsMain_process_Index;
void FB_fsMain_process_Start();
void FB_fsMain_process_Stop();
void FB_fsMain_process_Trigger();
void FB_fsMain_process_Save();
double FB_fsMain_process_IsRunning();
double FB_fsMain_process_IsTriggered();
double FB_fsMain_process_NumCollected();
extern int FB_fsMain_daemon_Index;
void FB_fsMain_daemon_Start();
void FB_fsMain_daemon_Stop();
void FB_fsMain_daemon_Trigger();
void FB_fsMain_daemon_Save();
double FB_fsMain_daemon_IsRunning();
double FB_fsMain_daemon_IsTriggered();
double FB_fsMain_daemon_NumCollected();
extern int FB_fsMain_loopStep32to38_Index;
void FB_fsMain_loopStep32to38_Start();
void FB_fsMain_loopStep32to38_Stop();
void FB_fsMain_loopStep32to38_Trigger();
void FB_fsMain_loopStep32to38_Save();
double FB_fsMain_loopStep32to38_IsRunning();
double FB_fsMain_loopStep32to38_IsTriggered();
double FB_fsMain_loopStep32to38_NumCollected();
extern int FB_fsMain_saveSettings_Index;
void FB_fsMain_saveSettings_Start();
void FB_fsMain_saveSettings_Stop();
void FB_fsMain_saveSettings_Trigger();
void FB_fsMain_saveSettings_Save();
double FB_fsMain_saveSettings_IsRunning();
double FB_fsMain_saveSettings_IsTriggered();
double FB_fsMain_saveSettings_NumCollected();
extern int FB_fsMain_subPeriodicMsgOn_Index;
void FB_fsMain_subPeriodicMsgOn_Start();
void FB_fsMain_subPeriodicMsgOn_Stop();
void FB_fsMain_subPeriodicMsgOn_Trigger();
void FB_fsMain_subPeriodicMsgOn_Save();
double FB_fsMain_subPeriodicMsgOn_IsRunning();
double FB_fsMain_subPeriodicMsgOn_IsTriggered();
double FB_fsMain_subPeriodicMsgOn_NumCollected();
extern int FB_fsMain_subPeriodicMsgOff_Index;
void FB_fsMain_subPeriodicMsgOff_Start();
void FB_fsMain_subPeriodicMsgOff_Stop();
void FB_fsMain_subPeriodicMsgOff_Trigger();
void FB_fsMain_subPeriodicMsgOff_Save();
double FB_fsMain_subPeriodicMsgOff_IsRunning();
double FB_fsMain_subPeriodicMsgOff_IsTriggered();
double FB_fsMain_subPeriodicMsgOff_NumCollected();
extern int FB_fs_resetCurrValuesAutoTest_Index;
void FB_fs_resetCurrValuesAutoTest_Start();
void FB_fs_resetCurrValuesAutoTest_Stop();
void FB_fs_resetCurrValuesAutoTest_Trigger();
void FB_fs_resetCurrValuesAutoTest_Save();
double FB_fs_resetCurrValuesAutoTest_IsRunning();
double FB_fs_resetCurrValuesAutoTest_IsTriggered();
double FB_fs_resetCurrValuesAutoTest_NumCollected();
extern int FB_fs_linkDetect_Index;
void FB_fs_linkDetect_Start();
void FB_fs_linkDetect_Stop();
void FB_fs_linkDetect_Trigger();
void FB_fs_linkDetect_Save();
double FB_fs_linkDetect_IsRunning();
double FB_fs_linkDetect_IsTriggered();
double FB_fs_linkDetect_NumCollected();
extern int FB_fsMain_autoTest_Index;
void FB_fsMain_autoTest_Start();
void FB_fsMain_autoTest_Stop();
void FB_fsMain_autoTest_Trigger();
void FB_fsMain_autoTest_Save();
double FB_fsMain_autoTest_IsRunning();
double FB_fsMain_autoTest_IsTriggered();
double FB_fsMain_autoTest_NumCollected();
extern int FB_fs_resetTargetValues_Index;
void FB_fs_resetTargetValues_Start();
void FB_fs_resetTargetValues_Stop();
void FB_fs_resetTargetValues_Trigger();
void FB_fs_resetTargetValues_Save();
double FB_fs_resetTargetValues_IsRunning();
double FB_fs_resetTargetValues_IsTriggered();
double FB_fs_resetTargetValues_NumCollected();
extern int FB_fs_resetCurrValues_Index;
void FB_fs_resetCurrValues_Start();
void FB_fs_resetCurrValues_Stop();
void FB_fs_resetCurrValues_Trigger();
void FB_fs_resetCurrValues_Save();
double FB_fs_resetCurrValues_IsRunning();
double FB_fs_resetCurrValues_IsTriggered();
double FB_fs_resetCurrValues_NumCollected();
extern int FB_fs_resetPassedFlags_Index;
void FB_fs_resetPassedFlags_Start();
void FB_fs_resetPassedFlags_Stop();
void FB_fs_resetPassedFlags_Trigger();
void FB_fs_resetPassedFlags_Save();
double FB_fs_resetPassedFlags_IsRunning();
double FB_fs_resetPassedFlags_IsTriggered();
double FB_fs_resetPassedFlags_NumCollected();
extern int FB_fs_periodicSteps32_38_Index;
void FB_fs_periodicSteps32_38_Start();
void FB_fs_periodicSteps32_38_Stop();
void FB_fs_periodicSteps32_38_Trigger();
void FB_fs_periodicSteps32_38_Save();
double FB_fs_periodicSteps32_38_IsRunning();
double FB_fs_periodicSteps32_38_IsTriggered();
double FB_fs_periodicSteps32_38_NumCollected();
extern int FB_fs_step8_Execute_Index;
void FB_fs_step8_Execute_Start();
void FB_fs_step8_Execute_Stop();
void FB_fs_step8_Execute_Trigger();
void FB_fs_step8_Execute_Save();
double FB_fs_step8_Execute_IsRunning();
double FB_fs_step8_Execute_IsTriggered();
double FB_fs_step8_Execute_NumCollected();
extern int FB_fs_step9_Execute_Index;
void FB_fs_step9_Execute_Start();
void FB_fs_step9_Execute_Stop();
void FB_fs_step9_Execute_Trigger();
void FB_fs_step9_Execute_Save();
double FB_fs_step9_Execute_IsRunning();
double FB_fs_step9_Execute_IsTriggered();
double FB_fs_step9_Execute_NumCollected();
extern int FB_fs_step10_Execute_Index;
void FB_fs_step10_Execute_Start();
void FB_fs_step10_Execute_Stop();
void FB_fs_step10_Execute_Trigger();
void FB_fs_step10_Execute_Save();
double FB_fs_step10_Execute_IsRunning();
double FB_fs_step10_Execute_IsTriggered();
double FB_fs_step10_Execute_NumCollected();
extern int FB_fs_step_10_1_Execute_Index;
void FB_fs_step_10_1_Execute_Start();
void FB_fs_step_10_1_Execute_Stop();
void FB_fs_step_10_1_Execute_Trigger();
void FB_fs_step_10_1_Execute_Save();
double FB_fs_step_10_1_Execute_IsRunning();
double FB_fs_step_10_1_Execute_IsTriggered();
double FB_fs_step_10_1_Execute_NumCollected();
extern int FB_fs_step15_sendOnce_Index;
void FB_fs_step15_sendOnce_Start();
void FB_fs_step15_sendOnce_Stop();
void FB_fs_step15_sendOnce_Trigger();
void FB_fs_step15_sendOnce_Save();
double FB_fs_step15_sendOnce_IsRunning();
double FB_fs_step15_sendOnce_IsTriggered();
double FB_fs_step15_sendOnce_NumCollected();
extern int FB_fs_step16_sendOnce_Index;
void FB_fs_step16_sendOnce_Start();
void FB_fs_step16_sendOnce_Stop();
void FB_fs_step16_sendOnce_Trigger();
void FB_fs_step16_sendOnce_Save();
double FB_fs_step16_sendOnce_IsRunning();
double FB_fs_step16_sendOnce_IsTriggered();
double FB_fs_step16_sendOnce_NumCollected();
extern int FB_fs_step17_sendOnce_Index;
void FB_fs_step17_sendOnce_Start();
void FB_fs_step17_sendOnce_Stop();
void FB_fs_step17_sendOnce_Trigger();
void FB_fs_step17_sendOnce_Save();
double FB_fs_step17_sendOnce_IsRunning();
double FB_fs_step17_sendOnce_IsTriggered();
double FB_fs_step17_sendOnce_NumCollected();
extern int FB_fs_step18_sendOnce_Index;
void FB_fs_step18_sendOnce_Start();
void FB_fs_step18_sendOnce_Stop();
void FB_fs_step18_sendOnce_Trigger();
void FB_fs_step18_sendOnce_Save();
double FB_fs_step18_sendOnce_IsRunning();
double FB_fs_step18_sendOnce_IsTriggered();
double FB_fs_step18_sendOnce_NumCollected();
extern int FB_fs_step19_sendOnce_Index;
void FB_fs_step19_sendOnce_Start();
void FB_fs_step19_sendOnce_Stop();
void FB_fs_step19_sendOnce_Trigger();
void FB_fs_step19_sendOnce_Save();
double FB_fs_step19_sendOnce_IsRunning();
double FB_fs_step19_sendOnce_IsTriggered();
double FB_fs_step19_sendOnce_NumCollected();
extern int FB_fs_step20_sendOnce_Index;
void FB_fs_step20_sendOnce_Start();
void FB_fs_step20_sendOnce_Stop();
void FB_fs_step20_sendOnce_Trigger();
void FB_fs_step20_sendOnce_Save();
double FB_fs_step20_sendOnce_IsRunning();
double FB_fs_step20_sendOnce_IsTriggered();
double FB_fs_step20_sendOnce_NumCollected();
extern int FB_fs_step21_sendOnce_Index;
void FB_fs_step21_sendOnce_Start();
void FB_fs_step21_sendOnce_Stop();
void FB_fs_step21_sendOnce_Trigger();
void FB_fs_step21_sendOnce_Save();
double FB_fs_step21_sendOnce_IsRunning();
double FB_fs_step21_sendOnce_IsTriggered();
double FB_fs_step21_sendOnce_NumCollected();
extern int FB_fs_step22_sendOnce_Index;
void FB_fs_step22_sendOnce_Start();
void FB_fs_step22_sendOnce_Stop();
void FB_fs_step22_sendOnce_Trigger();
void FB_fs_step22_sendOnce_Save();
double FB_fs_step22_sendOnce_IsRunning();
double FB_fs_step22_sendOnce_IsTriggered();
double FB_fs_step22_sendOnce_NumCollected();
extern int FB_fs_step23_sendOnce_Index;
void FB_fs_step23_sendOnce_Start();
void FB_fs_step23_sendOnce_Stop();
void FB_fs_step23_sendOnce_Trigger();
void FB_fs_step23_sendOnce_Save();
double FB_fs_step23_sendOnce_IsRunning();
double FB_fs_step23_sendOnce_IsTriggered();
double FB_fs_step23_sendOnce_NumCollected();
extern int FB_fs_step24_sendOnce_Index;
void FB_fs_step24_sendOnce_Start();
void FB_fs_step24_sendOnce_Stop();
void FB_fs_step24_sendOnce_Trigger();
void FB_fs_step24_sendOnce_Save();
double FB_fs_step24_sendOnce_IsRunning();
double FB_fs_step24_sendOnce_IsTriggered();
double FB_fs_step24_sendOnce_NumCollected();
extern int FB_fs_step25_sendOnce_Index;
void FB_fs_step25_sendOnce_Start();
void FB_fs_step25_sendOnce_Stop();
void FB_fs_step25_sendOnce_Trigger();
void FB_fs_step25_sendOnce_Save();
double FB_fs_step25_sendOnce_IsRunning();
double FB_fs_step25_sendOnce_IsTriggered();
double FB_fs_step25_sendOnce_NumCollected();
extern int FB_fs_step26_sendOnce_Index;
void FB_fs_step26_sendOnce_Start();
void FB_fs_step26_sendOnce_Stop();
void FB_fs_step26_sendOnce_Trigger();
void FB_fs_step26_sendOnce_Save();
double FB_fs_step26_sendOnce_IsRunning();
double FB_fs_step26_sendOnce_IsTriggered();
double FB_fs_step26_sendOnce_NumCollected();
extern int FB_fs_step27_sendOnce_Index;
void FB_fs_step27_sendOnce_Start();
void FB_fs_step27_sendOnce_Stop();
void FB_fs_step27_sendOnce_Trigger();
void FB_fs_step27_sendOnce_Save();
double FB_fs_step27_sendOnce_IsRunning();
double FB_fs_step27_sendOnce_IsTriggered();
double FB_fs_step27_sendOnce_NumCollected();
extern int FB_fs_step28_sendOnce_Index;
void FB_fs_step28_sendOnce_Start();
void FB_fs_step28_sendOnce_Stop();
void FB_fs_step28_sendOnce_Trigger();
void FB_fs_step28_sendOnce_Save();
double FB_fs_step28_sendOnce_IsRunning();
double FB_fs_step28_sendOnce_IsTriggered();
double FB_fs_step28_sendOnce_NumCollected();
extern int FB_fs_step29_sendOnce_Index;
void FB_fs_step29_sendOnce_Start();
void FB_fs_step29_sendOnce_Stop();
void FB_fs_step29_sendOnce_Trigger();
void FB_fs_step29_sendOnce_Save();
double FB_fs_step29_sendOnce_IsRunning();
double FB_fs_step29_sendOnce_IsTriggered();
double FB_fs_step29_sendOnce_NumCollected();
extern int FB_fs_step30_sendOnce_Index;
void FB_fs_step30_sendOnce_Start();
void FB_fs_step30_sendOnce_Stop();
void FB_fs_step30_sendOnce_Trigger();
void FB_fs_step30_sendOnce_Save();
double FB_fs_step30_sendOnce_IsRunning();
double FB_fs_step30_sendOnce_IsTriggered();
double FB_fs_step30_sendOnce_NumCollected();
extern int FB_fs_step31_sendOnce_Index;
void FB_fs_step31_sendOnce_Start();
void FB_fs_step31_sendOnce_Stop();
void FB_fs_step31_sendOnce_Trigger();
void FB_fs_step31_sendOnce_Save();
double FB_fs_step31_sendOnce_IsRunning();
double FB_fs_step31_sendOnce_IsTriggered();
double FB_fs_step31_sendOnce_NumCollected();
extern int FB_fs_step32_sendOnce_Index;
void FB_fs_step32_sendOnce_Start();
void FB_fs_step32_sendOnce_Stop();
void FB_fs_step32_sendOnce_Trigger();
void FB_fs_step32_sendOnce_Save();
double FB_fs_step32_sendOnce_IsRunning();
double FB_fs_step32_sendOnce_IsTriggered();
double FB_fs_step32_sendOnce_NumCollected();
extern int FB_fs_step33_sendOnce_Index;
void FB_fs_step33_sendOnce_Start();
void FB_fs_step33_sendOnce_Stop();
void FB_fs_step33_sendOnce_Trigger();
void FB_fs_step33_sendOnce_Save();
double FB_fs_step33_sendOnce_IsRunning();
double FB_fs_step33_sendOnce_IsTriggered();
double FB_fs_step33_sendOnce_NumCollected();
extern int FB_fs_step34_sendOnce_Index;
void FB_fs_step34_sendOnce_Start();
void FB_fs_step34_sendOnce_Stop();
void FB_fs_step34_sendOnce_Trigger();
void FB_fs_step34_sendOnce_Save();
double FB_fs_step34_sendOnce_IsRunning();
double FB_fs_step34_sendOnce_IsTriggered();
double FB_fs_step34_sendOnce_NumCollected();
extern int FB_fs_step35_sendOnce_Index;
void FB_fs_step35_sendOnce_Start();
void FB_fs_step35_sendOnce_Stop();
void FB_fs_step35_sendOnce_Trigger();
void FB_fs_step35_sendOnce_Save();
double FB_fs_step35_sendOnce_IsRunning();
double FB_fs_step35_sendOnce_IsTriggered();
double FB_fs_step35_sendOnce_NumCollected();
extern int FB_fs_step36_sendOnce_Index;
void FB_fs_step36_sendOnce_Start();
void FB_fs_step36_sendOnce_Stop();
void FB_fs_step36_sendOnce_Trigger();
void FB_fs_step36_sendOnce_Save();
double FB_fs_step36_sendOnce_IsRunning();
double FB_fs_step36_sendOnce_IsTriggered();
double FB_fs_step36_sendOnce_NumCollected();
extern int FB_fs_step37_sendOnce_Index;
void FB_fs_step37_sendOnce_Start();
void FB_fs_step37_sendOnce_Stop();
void FB_fs_step37_sendOnce_Trigger();
void FB_fs_step37_sendOnce_Save();
double FB_fs_step37_sendOnce_IsRunning();
double FB_fs_step37_sendOnce_IsTriggered();
double FB_fs_step37_sendOnce_NumCollected();
extern int FB_fs_step38_sendOnce_Index;
void FB_fs_step38_sendOnce_Start();
void FB_fs_step38_sendOnce_Stop();
void FB_fs_step38_sendOnce_Trigger();
void FB_fs_step38_sendOnce_Save();
double FB_fs_step38_sendOnce_IsRunning();
double FB_fs_step38_sendOnce_IsTriggered();
double FB_fs_step38_sendOnce_NumCollected();
extern int FB_fs_step39_sendOnce_Index;
void FB_fs_step39_sendOnce_Start();
void FB_fs_step39_sendOnce_Stop();
void FB_fs_step39_sendOnce_Trigger();
void FB_fs_step39_sendOnce_Save();
double FB_fs_step39_sendOnce_IsRunning();
double FB_fs_step39_sendOnce_IsTriggered();
double FB_fs_step39_sendOnce_NumCollected();
extern int FB_fs_step40_sendOnce_Index;
void FB_fs_step40_sendOnce_Start();
void FB_fs_step40_sendOnce_Stop();
void FB_fs_step40_sendOnce_Trigger();
void FB_fs_step40_sendOnce_Save();
double FB_fs_step40_sendOnce_IsRunning();
double FB_fs_step40_sendOnce_IsTriggered();
double FB_fs_step40_sendOnce_NumCollected();
extern int FB_fs_step41_sendOnce_Index;
void FB_fs_step41_sendOnce_Start();
void FB_fs_step41_sendOnce_Stop();
void FB_fs_step41_sendOnce_Trigger();
void FB_fs_step41_sendOnce_Save();
double FB_fs_step41_sendOnce_IsRunning();
double FB_fs_step41_sendOnce_IsTriggered();
double FB_fs_step41_sendOnce_NumCollected();
extern int FB_fs_step343536_sendOnce_Index;
void FB_fs_step343536_sendOnce_Start();
void FB_fs_step343536_sendOnce_Stop();
void FB_fs_step343536_sendOnce_Trigger();
void FB_fs_step343536_sendOnce_Save();
double FB_fs_step343536_sendOnce_IsRunning();
double FB_fs_step343536_sendOnce_IsTriggered();
double FB_fs_step343536_sendOnce_NumCollected();
extern int FB_fs_step3738_sendOnce_Index;
void FB_fs_step3738_sendOnce_Start();
void FB_fs_step3738_sendOnce_Stop();
void FB_fs_step3738_sendOnce_Trigger();
void FB_fs_step3738_sendOnce_Save();
double FB_fs_step3738_sendOnce_IsRunning();
double FB_fs_step3738_sendOnce_IsTriggered();
double FB_fs_step3738_sendOnce_NumCollected();
extern int FB_mpiWrite_mainMPIWrite_Index;
void FB_mpiWrite_mainMPIWrite_Start();
void FB_mpiWrite_mainMPIWrite_Stop();
void FB_mpiWrite_mainMPIWrite_Trigger();
void FB_mpiWrite_mainMPIWrite_Save();
double FB_mpiWrite_mainMPIWrite_IsRunning();
double FB_mpiWrite_mainMPIWrite_IsTriggered();
double FB_mpiWrite_mainMPIWrite_NumCollected();
extern int FB_mpiWrite_resetPassedFlags_Index;
void FB_mpiWrite_resetPassedFlags_Start();
void FB_mpiWrite_resetPassedFlags_Stop();
void FB_mpiWrite_resetPassedFlags_Trigger();
void FB_mpiWrite_resetPassedFlags_Save();
double FB_mpiWrite_resetPassedFlags_IsRunning();
double FB_mpiWrite_resetPassedFlags_IsTriggered();
double FB_mpiWrite_resetPassedFlags_NumCollected();
extern int FB_mpiWrite_sub_step1_Index;
void FB_mpiWrite_sub_step1_Start();
void FB_mpiWrite_sub_step1_Stop();
void FB_mpiWrite_sub_step1_Trigger();
void FB_mpiWrite_sub_step1_Save();
double FB_mpiWrite_sub_step1_IsRunning();
double FB_mpiWrite_sub_step1_IsTriggered();
double FB_mpiWrite_sub_step1_NumCollected();
extern int FB_mpiWrite_sub_stepX_Str_Index;
void FB_mpiWrite_sub_stepX_Str_Start();
void FB_mpiWrite_sub_stepX_Str_Stop();
void FB_mpiWrite_sub_stepX_Str_Trigger();
void FB_mpiWrite_sub_stepX_Str_Save();
double FB_mpiWrite_sub_stepX_Str_IsRunning();
double FB_mpiWrite_sub_stepX_Str_IsTriggered();
double FB_mpiWrite_sub_stepX_Str_NumCollected();
extern int FB_mpiWrite_sub_stepX_Number_Index;
void FB_mpiWrite_sub_stepX_Number_Start();
void FB_mpiWrite_sub_stepX_Number_Stop();
void FB_mpiWrite_sub_stepX_Number_Trigger();
void FB_mpiWrite_sub_stepX_Number_Save();
double FB_mpiWrite_sub_stepX_Number_IsRunning();
double FB_mpiWrite_sub_stepX_Number_IsTriggered();
double FB_mpiWrite_sub_stepX_Number_NumCollected();
extern int FB_mpiWrite_sub_step2_Index;
void FB_mpiWrite_sub_step2_Start();
void FB_mpiWrite_sub_step2_Stop();
void FB_mpiWrite_sub_step2_Trigger();
void FB_mpiWrite_sub_step2_Save();
double FB_mpiWrite_sub_step2_IsRunning();
double FB_mpiWrite_sub_step2_IsTriggered();
double FB_mpiWrite_sub_step2_NumCollected();
extern int FB_mpiWrite_sub_step3_Index;
void FB_mpiWrite_sub_step3_Start();
void FB_mpiWrite_sub_step3_Stop();
void FB_mpiWrite_sub_step3_Trigger();
void FB_mpiWrite_sub_step3_Save();
double FB_mpiWrite_sub_step3_IsRunning();
double FB_mpiWrite_sub_step3_IsTriggered();
double FB_mpiWrite_sub_step3_NumCollected();
extern int FB_mpiWrite_sub_step4_Index;
void FB_mpiWrite_sub_step4_Start();
void FB_mpiWrite_sub_step4_Stop();
void FB_mpiWrite_sub_step4_Trigger();
void FB_mpiWrite_sub_step4_Save();
double FB_mpiWrite_sub_step4_IsRunning();
double FB_mpiWrite_sub_step4_IsTriggered();
double FB_mpiWrite_sub_step4_NumCollected();
extern int FB_mpiWrite_sub_step5_Index;
void FB_mpiWrite_sub_step5_Start();
void FB_mpiWrite_sub_step5_Stop();
void FB_mpiWrite_sub_step5_Trigger();
void FB_mpiWrite_sub_step5_Save();
double FB_mpiWrite_sub_step5_IsRunning();
double FB_mpiWrite_sub_step5_IsTriggered();
double FB_mpiWrite_sub_step5_NumCollected();
extern int FB_mpiWrite_sub_step6_Index;
void FB_mpiWrite_sub_step6_Start();
void FB_mpiWrite_sub_step6_Stop();
void FB_mpiWrite_sub_step6_Trigger();
void FB_mpiWrite_sub_step6_Save();
double FB_mpiWrite_sub_step6_IsRunning();
double FB_mpiWrite_sub_step6_IsTriggered();
double FB_mpiWrite_sub_step6_NumCollected();
extern int FB_mpiWrite_sub_step7_Index;
void FB_mpiWrite_sub_step7_Start();
void FB_mpiWrite_sub_step7_Stop();
void FB_mpiWrite_sub_step7_Trigger();
void FB_mpiWrite_sub_step7_Save();
double FB_mpiWrite_sub_step7_IsRunning();
double FB_mpiWrite_sub_step7_IsTriggered();
double FB_mpiWrite_sub_step7_NumCollected();
extern int FB_mpiWrite_sub_step8_Index;
void FB_mpiWrite_sub_step8_Start();
void FB_mpiWrite_sub_step8_Stop();
void FB_mpiWrite_sub_step8_Trigger();
void FB_mpiWrite_sub_step8_Save();
double FB_mpiWrite_sub_step8_IsRunning();
double FB_mpiWrite_sub_step8_IsTriggered();
double FB_mpiWrite_sub_step8_NumCollected();
extern int FB_mpiRead_mainMPIRead_Index;
void FB_mpiRead_mainMPIRead_Start();
void FB_mpiRead_mainMPIRead_Stop();
void FB_mpiRead_mainMPIRead_Trigger();
void FB_mpiRead_mainMPIRead_Save();
double FB_mpiRead_mainMPIRead_IsRunning();
double FB_mpiRead_mainMPIRead_IsTriggered();
double FB_mpiRead_mainMPIRead_NumCollected();
extern int FB_mpiRead_resetValues_Index;
void FB_mpiRead_resetValues_Start();
void FB_mpiRead_resetValues_Stop();
void FB_mpiRead_resetValues_Trigger();
void FB_mpiRead_resetValues_Save();
double FB_mpiRead_resetValues_IsRunning();
double FB_mpiRead_resetValues_IsTriggered();
double FB_mpiRead_resetValues_NumCollected();
extern int FB_mpiRead_resetPassedFlags_Index;
void FB_mpiRead_resetPassedFlags_Start();
void FB_mpiRead_resetPassedFlags_Stop();
void FB_mpiRead_resetPassedFlags_Trigger();
void FB_mpiRead_resetPassedFlags_Save();
double FB_mpiRead_resetPassedFlags_IsRunning();
double FB_mpiRead_resetPassedFlags_IsTriggered();
double FB_mpiRead_resetPassedFlags_NumCollected();
extern int FB_mpiRead_sub_step1_Index;
void FB_mpiRead_sub_step1_Start();
void FB_mpiRead_sub_step1_Stop();
void FB_mpiRead_sub_step1_Trigger();
void FB_mpiRead_sub_step1_Save();
double FB_mpiRead_sub_step1_IsRunning();
double FB_mpiRead_sub_step1_IsTriggered();
double FB_mpiRead_sub_step1_NumCollected();
extern int FB_mpiRead_sub_step2_Index;
void FB_mpiRead_sub_step2_Start();
void FB_mpiRead_sub_step2_Stop();
void FB_mpiRead_sub_step2_Trigger();
void FB_mpiRead_sub_step2_Save();
double FB_mpiRead_sub_step2_IsRunning();
double FB_mpiRead_sub_step2_IsTriggered();
double FB_mpiRead_sub_step2_NumCollected();
extern int FB_mpiRead_sub_step3_Index;
void FB_mpiRead_sub_step3_Start();
void FB_mpiRead_sub_step3_Stop();
void FB_mpiRead_sub_step3_Trigger();
void FB_mpiRead_sub_step3_Save();
double FB_mpiRead_sub_step3_IsRunning();
double FB_mpiRead_sub_step3_IsTriggered();
double FB_mpiRead_sub_step3_NumCollected();
extern int FB_mpiRead_sub_step4_Index;
void FB_mpiRead_sub_step4_Start();
void FB_mpiRead_sub_step4_Stop();
void FB_mpiRead_sub_step4_Trigger();
void FB_mpiRead_sub_step4_Save();
double FB_mpiRead_sub_step4_IsRunning();
double FB_mpiRead_sub_step4_IsTriggered();
double FB_mpiRead_sub_step4_NumCollected();
extern int FB_mpiRead_sub_step5_Index;
void FB_mpiRead_sub_step5_Start();
void FB_mpiRead_sub_step5_Stop();
void FB_mpiRead_sub_step5_Trigger();
void FB_mpiRead_sub_step5_Save();
double FB_mpiRead_sub_step5_IsRunning();
double FB_mpiRead_sub_step5_IsTriggered();
double FB_mpiRead_sub_step5_NumCollected();
extern int FB_mpiRead_sub_step6_Index;
void FB_mpiRead_sub_step6_Start();
void FB_mpiRead_sub_step6_Stop();
void FB_mpiRead_sub_step6_Trigger();
void FB_mpiRead_sub_step6_Save();
double FB_mpiRead_sub_step6_IsRunning();
double FB_mpiRead_sub_step6_IsTriggered();
double FB_mpiRead_sub_step6_NumCollected();
extern int FB_mpiRead_sub_step7_Index;
void FB_mpiRead_sub_step7_Start();
void FB_mpiRead_sub_step7_Stop();
void FB_mpiRead_sub_step7_Trigger();
void FB_mpiRead_sub_step7_Save();
double FB_mpiRead_sub_step7_IsRunning();
double FB_mpiRead_sub_step7_IsTriggered();
double FB_mpiRead_sub_step7_NumCollected();
extern int FB_mpiRead_sub_step8_Index;
void FB_mpiRead_sub_step8_Start();
void FB_mpiRead_sub_step8_Stop();
void FB_mpiRead_sub_step8_Trigger();
void FB_mpiRead_sub_step8_Save();
double FB_mpiRead_sub_step8_IsRunning();
double FB_mpiRead_sub_step8_IsTriggered();
double FB_mpiRead_sub_step8_NumCollected();
extern int FB_mpiRead_sub_step9_Index;
void FB_mpiRead_sub_step9_Start();
void FB_mpiRead_sub_step9_Stop();
void FB_mpiRead_sub_step9_Trigger();
void FB_mpiRead_sub_step9_Save();
double FB_mpiRead_sub_step9_IsRunning();
double FB_mpiRead_sub_step9_IsTriggered();
double FB_mpiRead_sub_step9_NumCollected();
extern int FB_mpiWrite_mainModelWrite_Index;
void FB_mpiWrite_mainModelWrite_Start();
void FB_mpiWrite_mainModelWrite_Stop();
void FB_mpiWrite_mainModelWrite_Trigger();
void FB_mpiWrite_mainModelWrite_Save();
double FB_mpiWrite_mainModelWrite_IsRunning();
double FB_mpiWrite_mainModelWrite_IsTriggered();
double FB_mpiWrite_mainModelWrite_NumCollected();
extern int FB_mpiWrite_sub_stepModel_Index;
void FB_mpiWrite_sub_stepModel_Start();
void FB_mpiWrite_sub_stepModel_Stop();
void FB_mpiWrite_sub_stepModel_Trigger();
void FB_mpiWrite_sub_stepModel_Save();
double FB_mpiWrite_sub_stepModel_IsRunning();
double FB_mpiWrite_sub_stepModel_IsTriggered();
double FB_mpiWrite_sub_stepModel_NumCollected();
extern int FB_sapa_mainWrite_Index;
void FB_sapa_mainWrite_Start();
void FB_sapa_mainWrite_Stop();
void FB_sapa_mainWrite_Trigger();
void FB_sapa_mainWrite_Save();
double FB_sapa_mainWrite_IsRunning();
double FB_sapa_mainWrite_IsTriggered();
double FB_sapa_mainWrite_NumCollected();
extern int FB_sapa_mainRead_Index;
void FB_sapa_mainRead_Start();
void FB_sapa_mainRead_Stop();
void FB_sapa_mainRead_Trigger();
void FB_sapa_mainRead_Save();
double FB_sapa_mainRead_IsRunning();
double FB_sapa_mainRead_IsTriggered();
double FB_sapa_mainRead_NumCollected();
extern int FB_sapaRead_resetValues_Index;
void FB_sapaRead_resetValues_Start();
void FB_sapaRead_resetValues_Stop();
void FB_sapaRead_resetValues_Trigger();
void FB_sapaRead_resetValues_Save();
double FB_sapaRead_resetValues_IsRunning();
double FB_sapaRead_resetValues_IsTriggered();
double FB_sapaRead_resetValues_NumCollected();
extern int FB_sapaWrite_sub_step1_Index;
void FB_sapaWrite_sub_step1_Start();
void FB_sapaWrite_sub_step1_Stop();
void FB_sapaWrite_sub_step1_Trigger();
void FB_sapaWrite_sub_step1_Save();
double FB_sapaWrite_sub_step1_IsRunning();
double FB_sapaWrite_sub_step1_IsTriggered();
double FB_sapaWrite_sub_step1_NumCollected();
extern int FB_sapaWrite_sub_step2_Index;
void FB_sapaWrite_sub_step2_Start();
void FB_sapaWrite_sub_step2_Stop();
void FB_sapaWrite_sub_step2_Trigger();
void FB_sapaWrite_sub_step2_Save();
double FB_sapaWrite_sub_step2_IsRunning();
double FB_sapaWrite_sub_step2_IsTriggered();
double FB_sapaWrite_sub_step2_NumCollected();
extern int FB_sapaRead_sub_step1_Index;
void FB_sapaRead_sub_step1_Start();
void FB_sapaRead_sub_step1_Stop();
void FB_sapaRead_sub_step1_Trigger();
void FB_sapaRead_sub_step1_Save();
double FB_sapaRead_sub_step1_IsRunning();
double FB_sapaRead_sub_step1_IsTriggered();
double FB_sapaRead_sub_step1_NumCollected();
extern int FB_sapaRead_sub_step2_Index;
void FB_sapaRead_sub_step2_Start();
void FB_sapaRead_sub_step2_Stop();
void FB_sapaRead_sub_step2_Trigger();
void FB_sapaRead_sub_step2_Save();
double FB_sapaRead_sub_step2_IsRunning();
double FB_sapaRead_sub_step2_IsTriggered();
double FB_sapaRead_sub_step2_NumCollected();

// Messages

typedef struct {
    unsigned char btPresent;  /// indicates message rxed at least once
    unsigned char  btPresentToggle; /// toggle every message rx
    unsigned char         btMultiFrameComplete; /// indicates frame is complete 
    double dUpdateRateRel;    /// periodic update rate
    double dUpdateRateAbs ;   /// absolute update rate
    int iPerSecond;   /// number of messages per second
    int iCount;       /// number of messages rxed
    int iChangeCount; /// count of everytime the message changes
    double dStartTime;        /// time between two first messages
    double dMsgMinTime;       /// min time between two messages
    double dMaxTime;          /// max time between two messages
    double dMeanTime;         /// average time between two messages
} MessageStats; 

typedef struct {
    int iNetwork; /// Network in Vehicle Spy
    int iID; /// Message ID
    __int64 iTimeStampNanoSecondsHW; /// TimeStamp By Hardware (3G Hardware Only)
    unsigned int iTimeStampMillisecondsOS; /// TimeStamp By OS (timeGetTime API)
    int iNumDataBytes; /// Number Of Data Bytes (CAN DLC)
    int iBitField;
    unsigned char btData[16]; /// Message data bytes
    unsigned char btInitialData[16]; /// Data bytes after initialization
} GenericMessage;

typedef struct {
    int iNetwork; /// Network in Vehicle Spy
    int iID; /// Message ID
    __int64 iTimeStampNanoSecondsHW; /// TimeStamp By Hardware (3G Hardware Only)
    unsigned int iTimeStampMillisecondsOS; /// TimeStamp By OS (timeGetTime API)
    int iNumDataBytes; /// Number Of Data Bytes (CAN DLC)
    int iBitField;
    unsigned char btData[4096]; /// Message data bytes
    unsigned char btInitialData[4096]; /// Data bytes after initialization
} GenericLongMessage;

void Spy_EveryMessage(GenericMessage * p_Msg);
void Spy_EveryLongMessage(GenericLongMessage * p_Msg);
int GenericMessageTransmit(GenericMessage * p_Msg);
int GenericLongMessageTransmit(GenericLongMessage * p_Msg);
int CANFDMessageTransmit(GenericLongMessage * p_Msg, BOOL bBRS);
extern int TX_step1_Network_Management_BCM_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double SrcNodeID; /// Min: 0 Max: 255 Units: 
    BYTE SrcNodeID_raw;
    double UDat; /// Min: 0 Max: 281474976710655 Units: 
    uint64 UDat_raw;
} TX_step1_Network_Management_BCM_HS_CAN;


void TX_step1_Network_Management_BCM_HS_CAN_Init(TX_step1_Network_Management_BCM_HS_CAN * pMsg);
int TX_step1_Network_Management_BCM_HS_CAN_Transmit(TX_step1_Network_Management_BCM_HS_CAN * pMsg);
int TX_step1_Network_Management_BCM_HS_CAN_Transmit_raw(TX_step1_Network_Management_BCM_HS_CAN * pMsg);
int TX_step1_Network_Management_BCM_HS_CAN_UpdateBytesFromSignals(TX_step1_Network_Management_BCM_HS_CAN * pMsg);
int TX_step1_Network_Management_BCM_HS_CAN_UpdateBytesFromRawSignals(TX_step1_Network_Management_BCM_HS_CAN * pMsg);
#define TX_step1_Network_Management_BCM_HS_CAN_SrcNodeID_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step1_Network_Management_BCM_HS_CAN_Index, 0, dPhysicalValue);
#define TX_step1_Network_Management_BCM_HS_CAN_SetSignal_SrcNodeID_Physical(dval) SpySetTxSignal(TX_step1_Network_Management_BCM_HS_CAN_Index, 0, dval)
#define TX_step1_Network_Management_BCM_HS_CAN_SetSignal_SrcNodeID_Raw(nval) SpySetTxSignalRaw(TX_step1_Network_Management_BCM_HS_CAN_Index, 0, nval)
#define TX_step1_Network_Management_BCM_HS_CAN_UDat_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step1_Network_Management_BCM_HS_CAN_Index, 1, dPhysicalValue);
#define TX_step1_Network_Management_BCM_HS_CAN_SetSignal_UDat_Physical(dval) SpySetTxSignal(TX_step1_Network_Management_BCM_HS_CAN_Index, 1, dval)
#define TX_step1_Network_Management_BCM_HS_CAN_SetSignal_UDat_Raw(nval) SpySetTxSignalRaw(TX_step1_Network_Management_BCM_HS_CAN_Index, 1, nval)
int TX_step1_Network_Management_BCM_HS_CAN_TransmitFast();
#define TX_step1_Network_Management_BCM_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step1_Network_Management_BCM_HS_CAN_Index, 0)
extern int TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double DrvHCSMIndReq; /// Min: 0 Max: 3 Units: 
    BYTE DrvHCSMIndReq_raw;
    double DrvHCSMInd1; /// Min: 0 Max: 1 Units: 
    BYTE DrvHCSMInd1_raw;
    double DrvHCSMInd2; /// Min: 0 Max: 1 Units: 
    BYTE DrvHCSMInd2_raw;
    double DrvHCSMInd3; /// Min: 0 Max: 1 Units: 
    BYTE DrvHCSMInd3_raw;
    double PassHCSMIndReq; /// Min: 0 Max: 3 Units: 
    BYTE PassHCSMIndReq_raw;
    double PassHCSMInd1; /// Min: 0 Max: 1 Units: 
    BYTE PassHCSMInd1_raw;
    double PassHCSMInd2; /// Min: 0 Max: 1 Units: 
    BYTE PassHCSMInd2_raw;
    double PassHCSMInd3; /// Min: 0 Max: 1 Units: 
    BYTE PassHCSMInd3_raw;
} TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN;

#pragma warning(disable : 4005)
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_$_DrvHCSMIndReq_$$_Off 0
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_$_DrvHCSMIndReq_$$_Continuous_Indication 1
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_$_DrvHCSMIndReq_$$_Flash_Rate__1_Indication 2
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_$_DrvHCSMIndReq_$$_Flash_Rate__2_Indication 3
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_$_DrvHCSMInd1_$$_False 0
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_$_DrvHCSMInd1_$$_True 1
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_$_DrvHCSMInd2_$$_False 0
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_$_DrvHCSMInd2_$$_True 1
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_$_DrvHCSMInd3_$$_False 0
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_$_DrvHCSMInd3_$$_True 1
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_$_PassHCSMIndReq_$$_Off 0
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_$_PassHCSMIndReq_$$_Continuous_Indication 1
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_$_PassHCSMIndReq_$$_Flash_Rate__1_Indication 2
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_$_PassHCSMIndReq_$$_Flash_Rate__2_Indication 3
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_$_PassHCSMInd1_$$_False 0
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_$_PassHCSMInd1_$$_True 1
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_$_PassHCSMInd2_$$_False 0
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_$_PassHCSMInd2_$$_True 1
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_$_PassHCSMInd3_$$_False 0
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_$_PassHCSMInd3_$$_True 1
#pragma warning(default : 4005)

void TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Init(TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN * pMsg);
int TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Transmit(TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN * pMsg);
int TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Transmit_raw(TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN * pMsg);
int TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_UpdateBytesFromSignals(TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN * pMsg);
int TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_UpdateBytesFromRawSignals(TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN * pMsg);
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_DrvHCSMIndReq_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Index, 0, dPhysicalValue);
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_SetSignal_DrvHCSMIndReq_Physical(dval) SpySetTxSignal(TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Index, 0, dval)
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_SetSignal_DrvHCSMIndReq_Raw(nval) SpySetTxSignalRaw(TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Index, 0, nval)
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_DrvHCSMInd1_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Index, 1, dPhysicalValue);
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_SetSignal_DrvHCSMInd1_Physical(dval) SpySetTxSignal(TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Index, 1, dval)
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_SetSignal_DrvHCSMInd1_Raw(nval) SpySetTxSignalRaw(TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Index, 1, nval)
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_DrvHCSMInd2_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Index, 2, dPhysicalValue);
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_SetSignal_DrvHCSMInd2_Physical(dval) SpySetTxSignal(TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Index, 2, dval)
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_SetSignal_DrvHCSMInd2_Raw(nval) SpySetTxSignalRaw(TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Index, 2, nval)
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_DrvHCSMInd3_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Index, 3, dPhysicalValue);
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_SetSignal_DrvHCSMInd3_Physical(dval) SpySetTxSignal(TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Index, 3, dval)
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_SetSignal_DrvHCSMInd3_Raw(nval) SpySetTxSignalRaw(TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Index, 3, nval)
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_PassHCSMIndReq_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Index, 4, dPhysicalValue);
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_SetSignal_PassHCSMIndReq_Physical(dval) SpySetTxSignal(TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Index, 4, dval)
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_SetSignal_PassHCSMIndReq_Raw(nval) SpySetTxSignalRaw(TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Index, 4, nval)
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_PassHCSMInd1_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Index, 5, dPhysicalValue);
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_SetSignal_PassHCSMInd1_Physical(dval) SpySetTxSignal(TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Index, 5, dval)
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_SetSignal_PassHCSMInd1_Raw(nval) SpySetTxSignalRaw(TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Index, 5, nval)
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_PassHCSMInd2_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Index, 6, dPhysicalValue);
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_SetSignal_PassHCSMInd2_Physical(dval) SpySetTxSignal(TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Index, 6, dval)
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_SetSignal_PassHCSMInd2_Raw(nval) SpySetTxSignalRaw(TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Index, 6, nval)
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_PassHCSMInd3_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Index, 7, dPhysicalValue);
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_SetSignal_PassHCSMInd3_Physical(dval) SpySetTxSignal(TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Index, 7, dval)
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_SetSignal_PassHCSMInd3_Raw(nval) SpySetTxSignalRaw(TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Index, 7, nval)
int TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_TransmitFast();
#define TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step2_Front_Seat_Heat_Cool_Control_HS_CAN_Index, 0)
extern int TX_step3_Exterior_Lighting_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double AdvFrntLghtSysEnbld; /// Min: 0 Max: 1 Units: 
    BYTE AdvFrntLghtSysEnbld_raw;
    double AutLghtCtrl; /// Min: 0 Max: 1 Units: 
    BYTE AutLghtCtrl_raw;
    double AutoBmSlctAllwd; /// Min: 0 Max: 1 Units: 
    BYTE AutoBmSlctAllwd_raw;
    double AutoLtsActIO; /// Min: 0 Max: 1 Units: 
    BYTE AutoLtsActIO_raw;
    double AutoLtsInactIO; /// Min: 0 Max: 1 Units: 
    BYTE AutoLtsInactIO_raw;
    double BrkLtsAtv; /// Min: 0 Max: 1 Units: 
    BYTE BrkLtsAtv_raw;
    double DRLAct; /// Min: 0 Max: 1 Units: 
    BYTE DRLAct_raw;
    double DispNtSchmAtv; /// Min: 0 Max: 1 Units: 
    BYTE DispNtSchmAtv_raw;
    double FlToPsSwAtv; /// Min: 0 Max: 1 Units: 
    BYTE FlToPsSwAtv_raw;
    double FrFogLmpsAct; /// Min: 0 Max: 1 Units: 
    BYTE FrFogLmpsAct_raw;
    double FrFgLtIO; /// Min: 0 Max: 1 Units: 
    BYTE FrFgLtIO_raw;
    double HazSwAtv; /// Min: 0 Max: 1 Units: 
    BYTE HazSwAtv_raw;
    double HdlmpBmSelectStat; /// Min: 0 Max: 3 Units: 
    BYTE HdlmpBmSelectStat_raw;
    double HighBmAct; /// Min: 0 Max: 1 Units: 
    BYTE HighBmAct_raw;
    double HiBmIO; /// Min: 0 Max: 1 Units: 
    BYTE HiBmIO_raw;
    double HiBmReqd; /// Min: 0 Max: 1 Units: 
    BYTE HiBmReqd_raw;
    double IntDimDspLvl; /// Min: 0 Max: 127 Units: 
    BYTE IntDimDspLvl_raw;
    double IntDimLvl; /// Min: 0 Max: 127 Units: 
    BYTE IntDimLvl_raw;
    double IntDimNtPnlAtv; /// Min: 0 Max: 1 Units: 
    BYTE IntDimNtPnlAtv_raw;
    double LftTrnLmpAtv; /// Min: 0 Max: 3 Units: 
    BYTE LftTrnLmpAtv_raw;
    double LowBmAct; /// Min: 0 Max: 1 Units: 
    BYTE LowBmAct_raw;
    double MainLghtSw; /// Min: 0 Max: 3 Units: 
    BYTE MainLghtSw_raw;
    double OtsdAmbtLtLvlStat; /// Min: 0 Max: 3 Units: 
    BYTE OtsdAmbtLtLvlStat_raw;
    double OtsdAmbtLtLvlStatV; /// Min: 0 Max: 1 Units: 
    BYTE OtsdAmbtLtLvlStatV_raw;
    double PrkLtIO; /// Min: 0 Max: 1 Units: 
    BYTE PrkLtIO_raw;
    double PrkLtLeftIO; /// Min: 0 Max: 1 Units: 
    BYTE PrkLtLeftIO_raw;
    double PrkLtRightIO; /// Min: 0 Max: 1 Units: 
    BYTE PrkLtRightIO_raw;
    double RrFogLmpsAct; /// Min: 0 Max: 1 Units: 
    BYTE RrFogLmpsAct_raw;
    double RrFgLtIO; /// Min: 0 Max: 1 Units: 
    BYTE RrFgLtIO_raw;
    double RevLmpAtv; /// Min: 0 Max: 1 Units: 
    BYTE RevLmpAtv_raw;
    double RtTrnLmpAtv; /// Min: 0 Max: 3 Units: 
    BYTE RtTrnLmpAtv_raw;
    double TrnSwAct; /// Min: 0 Max: 3 Units: 
    BYTE TrnSwAct_raw;
} TX_step3_Exterior_Lighting_HS_CAN;

#pragma warning(disable : 4005)
#define TX_step3_Exterior_Lighting_HS_CAN_$_AdvFrntLghtSysEnbld_$$_False 0
#define TX_step3_Exterior_Lighting_HS_CAN_$_AdvFrntLghtSysEnbld_$$_True 1
#define TX_step3_Exterior_Lighting_HS_CAN_$_AutLghtCtrl_$$_False 0
#define TX_step3_Exterior_Lighting_HS_CAN_$_AutLghtCtrl_$$_True 1
#define TX_step3_Exterior_Lighting_HS_CAN_$_AutoBmSlctAllwd_$$_False 0
#define TX_step3_Exterior_Lighting_HS_CAN_$_AutoBmSlctAllwd_$$_True 1
#define TX_step3_Exterior_Lighting_HS_CAN_$_AutoLtsActIO_$$_False 0
#define TX_step3_Exterior_Lighting_HS_CAN_$_AutoLtsActIO_$$_True 1
#define TX_step3_Exterior_Lighting_HS_CAN_$_AutoLtsInactIO_$$_False 0
#define TX_step3_Exterior_Lighting_HS_CAN_$_AutoLtsInactIO_$$_True 1
#define TX_step3_Exterior_Lighting_HS_CAN_$_BrkLtsAtv_$$_False 0
#define TX_step3_Exterior_Lighting_HS_CAN_$_BrkLtsAtv_$$_True 1
#define TX_step3_Exterior_Lighting_HS_CAN_$_DRLAct_$$_False 0
#define TX_step3_Exterior_Lighting_HS_CAN_$_DRLAct_$$_True 1
#define TX_step3_Exterior_Lighting_HS_CAN_$_DispNtSchmAtv_$$_False 0
#define TX_step3_Exterior_Lighting_HS_CAN_$_DispNtSchmAtv_$$_True 1
#define TX_step3_Exterior_Lighting_HS_CAN_$_FlToPsSwAtv_$$_False 0
#define TX_step3_Exterior_Lighting_HS_CAN_$_FlToPsSwAtv_$$_True 1
#define TX_step3_Exterior_Lighting_HS_CAN_$_FrFogLmpsAct_$$_False 0
#define TX_step3_Exterior_Lighting_HS_CAN_$_FrFogLmpsAct_$$_True 1
#define TX_step3_Exterior_Lighting_HS_CAN_$_FrFgLtIO_$$_False 0
#define TX_step3_Exterior_Lighting_HS_CAN_$_FrFgLtIO_$$_True 1
#define TX_step3_Exterior_Lighting_HS_CAN_$_HazSwAtv_$$_False 0
#define TX_step3_Exterior_Lighting_HS_CAN_$_HazSwAtv_$$_True 1
#define TX_step3_Exterior_Lighting_HS_CAN_$_HdlmpBmSelectStat_$$_Unknown 0
#define TX_step3_Exterior_Lighting_HS_CAN_$_HdlmpBmSelectStat_$$_Low_Beams 1
#define TX_step3_Exterior_Lighting_HS_CAN_$_HdlmpBmSelectStat_$$_High_Beams 2
#define TX_step3_Exterior_Lighting_HS_CAN_$_HighBmAct_$$_False 0
#define TX_step3_Exterior_Lighting_HS_CAN_$_HighBmAct_$$_True 1
#define TX_step3_Exterior_Lighting_HS_CAN_$_HiBmIO_$$_False 0
#define TX_step3_Exterior_Lighting_HS_CAN_$_HiBmIO_$$_True 1
#define TX_step3_Exterior_Lighting_HS_CAN_$_HiBmReqd_$$_False 0
#define TX_step3_Exterior_Lighting_HS_CAN_$_HiBmReqd_$$_True 1
#define TX_step3_Exterior_Lighting_HS_CAN_$_IntDimNtPnlAtv_$$_False 0
#define TX_step3_Exterior_Lighting_HS_CAN_$_IntDimNtPnlAtv_$$_True 1
#define TX_step3_Exterior_Lighting_HS_CAN_$_LftTrnLmpAtv_$$_Off 0
#define TX_step3_Exterior_Lighting_HS_CAN_$_LftTrnLmpAtv_$$_On_without_telltale 1
#define TX_step3_Exterior_Lighting_HS_CAN_$_LftTrnLmpAtv_$$_On_with_telltale 2
#define TX_step3_Exterior_Lighting_HS_CAN_$_LowBmAct_$$_False 0
#define TX_step3_Exterior_Lighting_HS_CAN_$_LowBmAct_$$_True 1
#define TX_step3_Exterior_Lighting_HS_CAN_$_MainLghtSw_$$_AUTO 0
#define TX_step3_Exterior_Lighting_HS_CAN_$_MainLghtSw_$$_OFF 1
#define TX_step3_Exterior_Lighting_HS_CAN_$_MainLghtSw_$$_PARKLAMP 2
#define TX_step3_Exterior_Lighting_HS_CAN_$_MainLghtSw_$$_HEADLAMP 3
#define TX_step3_Exterior_Lighting_HS_CAN_$_OtsdAmbtLtLvlStat_$$_Unknown 0
#define TX_step3_Exterior_Lighting_HS_CAN_$_OtsdAmbtLtLvlStat_$$_Night 1
#define TX_step3_Exterior_Lighting_HS_CAN_$_OtsdAmbtLtLvlStat_$$_Day 2
#define TX_step3_Exterior_Lighting_HS_CAN_$_OtsdAmbtLtLvlStatV_$$_Valid 0
#define TX_step3_Exterior_Lighting_HS_CAN_$_OtsdAmbtLtLvlStatV_$$_Invalid 1
#define TX_step3_Exterior_Lighting_HS_CAN_$_PrkLtIO_$$_False 0
#define TX_step3_Exterior_Lighting_HS_CAN_$_PrkLtIO_$$_True 1
#define TX_step3_Exterior_Lighting_HS_CAN_$_PrkLtLeftIO_$$_False 0
#define TX_step3_Exterior_Lighting_HS_CAN_$_PrkLtLeftIO_$$_True 1
#define TX_step3_Exterior_Lighting_HS_CAN_$_PrkLtRightIO_$$_False 0
#define TX_step3_Exterior_Lighting_HS_CAN_$_PrkLtRightIO_$$_True 1
#define TX_step3_Exterior_Lighting_HS_CAN_$_RrFogLmpsAct_$$_False 0
#define TX_step3_Exterior_Lighting_HS_CAN_$_RrFogLmpsAct_$$_True 1
#define TX_step3_Exterior_Lighting_HS_CAN_$_RrFgLtIO_$$_False 0
#define TX_step3_Exterior_Lighting_HS_CAN_$_RrFgLtIO_$$_True 1
#define TX_step3_Exterior_Lighting_HS_CAN_$_RevLmpAtv_$$_False 0
#define TX_step3_Exterior_Lighting_HS_CAN_$_RevLmpAtv_$$_True 1
#define TX_step3_Exterior_Lighting_HS_CAN_$_RtTrnLmpAtv_$$_Off 0
#define TX_step3_Exterior_Lighting_HS_CAN_$_RtTrnLmpAtv_$$_On_without_telltale 1
#define TX_step3_Exterior_Lighting_HS_CAN_$_RtTrnLmpAtv_$$_On_with_telltale 2
#define TX_step3_Exterior_Lighting_HS_CAN_$_TrnSwAct_$$_No_Activation 0
#define TX_step3_Exterior_Lighting_HS_CAN_$_TrnSwAct_$$_Left 1
#define TX_step3_Exterior_Lighting_HS_CAN_$_TrnSwAct_$$_Right 2
#pragma warning(default : 4005)

void TX_step3_Exterior_Lighting_HS_CAN_Init(TX_step3_Exterior_Lighting_HS_CAN * pMsg);
int TX_step3_Exterior_Lighting_HS_CAN_Transmit(TX_step3_Exterior_Lighting_HS_CAN * pMsg);
int TX_step3_Exterior_Lighting_HS_CAN_Transmit_raw(TX_step3_Exterior_Lighting_HS_CAN * pMsg);
int TX_step3_Exterior_Lighting_HS_CAN_UpdateBytesFromSignals(TX_step3_Exterior_Lighting_HS_CAN * pMsg);
int TX_step3_Exterior_Lighting_HS_CAN_UpdateBytesFromRawSignals(TX_step3_Exterior_Lighting_HS_CAN * pMsg);
#define TX_step3_Exterior_Lighting_HS_CAN_AdvFrntLghtSysEnbld_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step3_Exterior_Lighting_HS_CAN_Index, 0, dPhysicalValue);
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_AdvFrntLghtSysEnbld_Physical(dval) SpySetTxSignal(TX_step3_Exterior_Lighting_HS_CAN_Index, 0, dval)
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_AdvFrntLghtSysEnbld_Raw(nval) SpySetTxSignalRaw(TX_step3_Exterior_Lighting_HS_CAN_Index, 0, nval)
#define TX_step3_Exterior_Lighting_HS_CAN_AutLghtCtrl_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step3_Exterior_Lighting_HS_CAN_Index, 1, dPhysicalValue);
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_AutLghtCtrl_Physical(dval) SpySetTxSignal(TX_step3_Exterior_Lighting_HS_CAN_Index, 1, dval)
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_AutLghtCtrl_Raw(nval) SpySetTxSignalRaw(TX_step3_Exterior_Lighting_HS_CAN_Index, 1, nval)
#define TX_step3_Exterior_Lighting_HS_CAN_AutoBmSlctAllwd_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step3_Exterior_Lighting_HS_CAN_Index, 2, dPhysicalValue);
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_AutoBmSlctAllwd_Physical(dval) SpySetTxSignal(TX_step3_Exterior_Lighting_HS_CAN_Index, 2, dval)
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_AutoBmSlctAllwd_Raw(nval) SpySetTxSignalRaw(TX_step3_Exterior_Lighting_HS_CAN_Index, 2, nval)
#define TX_step3_Exterior_Lighting_HS_CAN_AutoLtsActIO_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step3_Exterior_Lighting_HS_CAN_Index, 3, dPhysicalValue);
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_AutoLtsActIO_Physical(dval) SpySetTxSignal(TX_step3_Exterior_Lighting_HS_CAN_Index, 3, dval)
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_AutoLtsActIO_Raw(nval) SpySetTxSignalRaw(TX_step3_Exterior_Lighting_HS_CAN_Index, 3, nval)
#define TX_step3_Exterior_Lighting_HS_CAN_AutoLtsInactIO_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step3_Exterior_Lighting_HS_CAN_Index, 4, dPhysicalValue);
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_AutoLtsInactIO_Physical(dval) SpySetTxSignal(TX_step3_Exterior_Lighting_HS_CAN_Index, 4, dval)
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_AutoLtsInactIO_Raw(nval) SpySetTxSignalRaw(TX_step3_Exterior_Lighting_HS_CAN_Index, 4, nval)
#define TX_step3_Exterior_Lighting_HS_CAN_BrkLtsAtv_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step3_Exterior_Lighting_HS_CAN_Index, 5, dPhysicalValue);
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_BrkLtsAtv_Physical(dval) SpySetTxSignal(TX_step3_Exterior_Lighting_HS_CAN_Index, 5, dval)
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_BrkLtsAtv_Raw(nval) SpySetTxSignalRaw(TX_step3_Exterior_Lighting_HS_CAN_Index, 5, nval)
#define TX_step3_Exterior_Lighting_HS_CAN_DRLAct_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step3_Exterior_Lighting_HS_CAN_Index, 6, dPhysicalValue);
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_DRLAct_Physical(dval) SpySetTxSignal(TX_step3_Exterior_Lighting_HS_CAN_Index, 6, dval)
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_DRLAct_Raw(nval) SpySetTxSignalRaw(TX_step3_Exterior_Lighting_HS_CAN_Index, 6, nval)
#define TX_step3_Exterior_Lighting_HS_CAN_DispNtSchmAtv_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step3_Exterior_Lighting_HS_CAN_Index, 7, dPhysicalValue);
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_DispNtSchmAtv_Physical(dval) SpySetTxSignal(TX_step3_Exterior_Lighting_HS_CAN_Index, 7, dval)
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_DispNtSchmAtv_Raw(nval) SpySetTxSignalRaw(TX_step3_Exterior_Lighting_HS_CAN_Index, 7, nval)
#define TX_step3_Exterior_Lighting_HS_CAN_FlToPsSwAtv_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step3_Exterior_Lighting_HS_CAN_Index, 8, dPhysicalValue);
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_FlToPsSwAtv_Physical(dval) SpySetTxSignal(TX_step3_Exterior_Lighting_HS_CAN_Index, 8, dval)
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_FlToPsSwAtv_Raw(nval) SpySetTxSignalRaw(TX_step3_Exterior_Lighting_HS_CAN_Index, 8, nval)
#define TX_step3_Exterior_Lighting_HS_CAN_FrFogLmpsAct_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step3_Exterior_Lighting_HS_CAN_Index, 9, dPhysicalValue);
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_FrFogLmpsAct_Physical(dval) SpySetTxSignal(TX_step3_Exterior_Lighting_HS_CAN_Index, 9, dval)
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_FrFogLmpsAct_Raw(nval) SpySetTxSignalRaw(TX_step3_Exterior_Lighting_HS_CAN_Index, 9, nval)
#define TX_step3_Exterior_Lighting_HS_CAN_FrFgLtIO_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step3_Exterior_Lighting_HS_CAN_Index, 10, dPhysicalValue);
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_FrFgLtIO_Physical(dval) SpySetTxSignal(TX_step3_Exterior_Lighting_HS_CAN_Index, 10, dval)
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_FrFgLtIO_Raw(nval) SpySetTxSignalRaw(TX_step3_Exterior_Lighting_HS_CAN_Index, 10, nval)
#define TX_step3_Exterior_Lighting_HS_CAN_HazSwAtv_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step3_Exterior_Lighting_HS_CAN_Index, 11, dPhysicalValue);
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_HazSwAtv_Physical(dval) SpySetTxSignal(TX_step3_Exterior_Lighting_HS_CAN_Index, 11, dval)
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_HazSwAtv_Raw(nval) SpySetTxSignalRaw(TX_step3_Exterior_Lighting_HS_CAN_Index, 11, nval)
#define TX_step3_Exterior_Lighting_HS_CAN_HdlmpBmSelectStat_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step3_Exterior_Lighting_HS_CAN_Index, 12, dPhysicalValue);
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_HdlmpBmSelectStat_Physical(dval) SpySetTxSignal(TX_step3_Exterior_Lighting_HS_CAN_Index, 12, dval)
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_HdlmpBmSelectStat_Raw(nval) SpySetTxSignalRaw(TX_step3_Exterior_Lighting_HS_CAN_Index, 12, nval)
#define TX_step3_Exterior_Lighting_HS_CAN_HighBmAct_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step3_Exterior_Lighting_HS_CAN_Index, 13, dPhysicalValue);
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_HighBmAct_Physical(dval) SpySetTxSignal(TX_step3_Exterior_Lighting_HS_CAN_Index, 13, dval)
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_HighBmAct_Raw(nval) SpySetTxSignalRaw(TX_step3_Exterior_Lighting_HS_CAN_Index, 13, nval)
#define TX_step3_Exterior_Lighting_HS_CAN_HiBmIO_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step3_Exterior_Lighting_HS_CAN_Index, 14, dPhysicalValue);
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_HiBmIO_Physical(dval) SpySetTxSignal(TX_step3_Exterior_Lighting_HS_CAN_Index, 14, dval)
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_HiBmIO_Raw(nval) SpySetTxSignalRaw(TX_step3_Exterior_Lighting_HS_CAN_Index, 14, nval)
#define TX_step3_Exterior_Lighting_HS_CAN_HiBmReqd_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step3_Exterior_Lighting_HS_CAN_Index, 15, dPhysicalValue);
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_HiBmReqd_Physical(dval) SpySetTxSignal(TX_step3_Exterior_Lighting_HS_CAN_Index, 15, dval)
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_HiBmReqd_Raw(nval) SpySetTxSignalRaw(TX_step3_Exterior_Lighting_HS_CAN_Index, 15, nval)
#define TX_step3_Exterior_Lighting_HS_CAN_IntDimDspLvl_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step3_Exterior_Lighting_HS_CAN_Index, 16, dPhysicalValue);
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_IntDimDspLvl_Physical(dval) SpySetTxSignal(TX_step3_Exterior_Lighting_HS_CAN_Index, 16, dval)
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_IntDimDspLvl_Raw(nval) SpySetTxSignalRaw(TX_step3_Exterior_Lighting_HS_CAN_Index, 16, nval)
#define TX_step3_Exterior_Lighting_HS_CAN_IntDimLvl_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step3_Exterior_Lighting_HS_CAN_Index, 17, dPhysicalValue);
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_IntDimLvl_Physical(dval) SpySetTxSignal(TX_step3_Exterior_Lighting_HS_CAN_Index, 17, dval)
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_IntDimLvl_Raw(nval) SpySetTxSignalRaw(TX_step3_Exterior_Lighting_HS_CAN_Index, 17, nval)
#define TX_step3_Exterior_Lighting_HS_CAN_IntDimNtPnlAtv_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step3_Exterior_Lighting_HS_CAN_Index, 18, dPhysicalValue);
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_IntDimNtPnlAtv_Physical(dval) SpySetTxSignal(TX_step3_Exterior_Lighting_HS_CAN_Index, 18, dval)
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_IntDimNtPnlAtv_Raw(nval) SpySetTxSignalRaw(TX_step3_Exterior_Lighting_HS_CAN_Index, 18, nval)
#define TX_step3_Exterior_Lighting_HS_CAN_LftTrnLmpAtv_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step3_Exterior_Lighting_HS_CAN_Index, 19, dPhysicalValue);
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_LftTrnLmpAtv_Physical(dval) SpySetTxSignal(TX_step3_Exterior_Lighting_HS_CAN_Index, 19, dval)
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_LftTrnLmpAtv_Raw(nval) SpySetTxSignalRaw(TX_step3_Exterior_Lighting_HS_CAN_Index, 19, nval)
#define TX_step3_Exterior_Lighting_HS_CAN_LowBmAct_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step3_Exterior_Lighting_HS_CAN_Index, 20, dPhysicalValue);
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_LowBmAct_Physical(dval) SpySetTxSignal(TX_step3_Exterior_Lighting_HS_CAN_Index, 20, dval)
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_LowBmAct_Raw(nval) SpySetTxSignalRaw(TX_step3_Exterior_Lighting_HS_CAN_Index, 20, nval)
#define TX_step3_Exterior_Lighting_HS_CAN_MainLghtSw_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step3_Exterior_Lighting_HS_CAN_Index, 21, dPhysicalValue);
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_MainLghtSw_Physical(dval) SpySetTxSignal(TX_step3_Exterior_Lighting_HS_CAN_Index, 21, dval)
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_MainLghtSw_Raw(nval) SpySetTxSignalRaw(TX_step3_Exterior_Lighting_HS_CAN_Index, 21, nval)
#define TX_step3_Exterior_Lighting_HS_CAN_OtsdAmbtLtLvlStat_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step3_Exterior_Lighting_HS_CAN_Index, 22, dPhysicalValue);
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_OtsdAmbtLtLvlStat_Physical(dval) SpySetTxSignal(TX_step3_Exterior_Lighting_HS_CAN_Index, 22, dval)
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_OtsdAmbtLtLvlStat_Raw(nval) SpySetTxSignalRaw(TX_step3_Exterior_Lighting_HS_CAN_Index, 22, nval)
#define TX_step3_Exterior_Lighting_HS_CAN_OtsdAmbtLtLvlStatV_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step3_Exterior_Lighting_HS_CAN_Index, 23, dPhysicalValue);
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_OtsdAmbtLtLvlStatV_Physical(dval) SpySetTxSignal(TX_step3_Exterior_Lighting_HS_CAN_Index, 23, dval)
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_OtsdAmbtLtLvlStatV_Raw(nval) SpySetTxSignalRaw(TX_step3_Exterior_Lighting_HS_CAN_Index, 23, nval)
#define TX_step3_Exterior_Lighting_HS_CAN_PrkLtIO_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step3_Exterior_Lighting_HS_CAN_Index, 24, dPhysicalValue);
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_PrkLtIO_Physical(dval) SpySetTxSignal(TX_step3_Exterior_Lighting_HS_CAN_Index, 24, dval)
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_PrkLtIO_Raw(nval) SpySetTxSignalRaw(TX_step3_Exterior_Lighting_HS_CAN_Index, 24, nval)
#define TX_step3_Exterior_Lighting_HS_CAN_PrkLtLeftIO_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step3_Exterior_Lighting_HS_CAN_Index, 25, dPhysicalValue);
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_PrkLtLeftIO_Physical(dval) SpySetTxSignal(TX_step3_Exterior_Lighting_HS_CAN_Index, 25, dval)
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_PrkLtLeftIO_Raw(nval) SpySetTxSignalRaw(TX_step3_Exterior_Lighting_HS_CAN_Index, 25, nval)
#define TX_step3_Exterior_Lighting_HS_CAN_PrkLtRightIO_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step3_Exterior_Lighting_HS_CAN_Index, 26, dPhysicalValue);
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_PrkLtRightIO_Physical(dval) SpySetTxSignal(TX_step3_Exterior_Lighting_HS_CAN_Index, 26, dval)
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_PrkLtRightIO_Raw(nval) SpySetTxSignalRaw(TX_step3_Exterior_Lighting_HS_CAN_Index, 26, nval)
#define TX_step3_Exterior_Lighting_HS_CAN_RrFogLmpsAct_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step3_Exterior_Lighting_HS_CAN_Index, 27, dPhysicalValue);
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_RrFogLmpsAct_Physical(dval) SpySetTxSignal(TX_step3_Exterior_Lighting_HS_CAN_Index, 27, dval)
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_RrFogLmpsAct_Raw(nval) SpySetTxSignalRaw(TX_step3_Exterior_Lighting_HS_CAN_Index, 27, nval)
#define TX_step3_Exterior_Lighting_HS_CAN_RrFgLtIO_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step3_Exterior_Lighting_HS_CAN_Index, 28, dPhysicalValue);
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_RrFgLtIO_Physical(dval) SpySetTxSignal(TX_step3_Exterior_Lighting_HS_CAN_Index, 28, dval)
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_RrFgLtIO_Raw(nval) SpySetTxSignalRaw(TX_step3_Exterior_Lighting_HS_CAN_Index, 28, nval)
#define TX_step3_Exterior_Lighting_HS_CAN_RevLmpAtv_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step3_Exterior_Lighting_HS_CAN_Index, 29, dPhysicalValue);
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_RevLmpAtv_Physical(dval) SpySetTxSignal(TX_step3_Exterior_Lighting_HS_CAN_Index, 29, dval)
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_RevLmpAtv_Raw(nval) SpySetTxSignalRaw(TX_step3_Exterior_Lighting_HS_CAN_Index, 29, nval)
#define TX_step3_Exterior_Lighting_HS_CAN_RtTrnLmpAtv_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step3_Exterior_Lighting_HS_CAN_Index, 30, dPhysicalValue);
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_RtTrnLmpAtv_Physical(dval) SpySetTxSignal(TX_step3_Exterior_Lighting_HS_CAN_Index, 30, dval)
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_RtTrnLmpAtv_Raw(nval) SpySetTxSignalRaw(TX_step3_Exterior_Lighting_HS_CAN_Index, 30, nval)
#define TX_step3_Exterior_Lighting_HS_CAN_TrnSwAct_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step3_Exterior_Lighting_HS_CAN_Index, 31, dPhysicalValue);
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_TrnSwAct_Physical(dval) SpySetTxSignal(TX_step3_Exterior_Lighting_HS_CAN_Index, 31, dval)
#define TX_step3_Exterior_Lighting_HS_CAN_SetSignal_TrnSwAct_Raw(nval) SpySetTxSignalRaw(TX_step3_Exterior_Lighting_HS_CAN_Index, 31, nval)
int TX_step3_Exterior_Lighting_HS_CAN_TransmitFast();
#define TX_step3_Exterior_Lighting_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step3_Exterior_Lighting_HS_CAN_Index, 0)
extern int TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double OtsAirTmp; /// Min: -40 Max: 87.5 Units: degC
    BYTE OtsAirTmp_raw;
    double OtsAirTmpCrVal; /// Min: -40 Max: 87.5 Units: degC
    BYTE OtsAirTmpCrVal_raw;
    double OtsAirTmpCrValMsk; /// Min: 0 Max: 1 Units: 
    BYTE OtsAirTmpCrValMsk_raw;
    double OtsAirTmpCrValV; /// Min: 0 Max: 1 Units: 
    BYTE OtsAirTmpCrValV_raw;
    double EngInltSpcfcHmdty; /// Min: 0 Max: 4.999989 Units: %water
    BYTE EngInltSpcfcHmdty_raw;
    double EngInltSpcfcHmdtyM; /// Min: 0 Max: 1 Units: 
    BYTE EngInltSpcfcHmdtyM_raw;
    double EngInltSpcfcHmdtyV; /// Min: 0 Max: 1 Units: 
    BYTE EngInltSpcfcHmdtyV_raw;
    double OtsAirTmpV; /// Min: 0 Max: 1 Units: 
    BYTE OtsAirTmpV_raw;
} TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN;

#pragma warning(disable : 4005)
#define TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_$_OtsAirTmpCrValMsk_$$_Don_t_Use_Data 0
#define TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_$_OtsAirTmpCrValMsk_$$_Use_Data 1
#define TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_$_OtsAirTmpCrValV_$$_Valid 0
#define TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_$_OtsAirTmpCrValV_$$_Invalid 1
#define TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_$_EngInltSpcfcHmdtyM_$$_Don_t_Use_Data 0
#define TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_$_EngInltSpcfcHmdtyM_$$_Use_Data 1
#define TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_$_EngInltSpcfcHmdtyV_$$_Valid 0
#define TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_$_EngInltSpcfcHmdtyV_$$_Invalid 1
#define TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_$_OtsAirTmpV_$$_Valid 0
#define TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_$_OtsAirTmpV_$$_Invalid 1
#pragma warning(default : 4005)

void TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Init(TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN * pMsg);
int TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Transmit(TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN * pMsg);
int TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Transmit_raw(TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN * pMsg);
int TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_UpdateBytesFromSignals(TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN * pMsg);
int TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_UpdateBytesFromRawSignals(TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN * pMsg);
#define TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_OtsAirTmp_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Index, 0, dPhysicalValue);
#define TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_SetSignal_OtsAirTmp_Physical(dval) SpySetTxSignal(TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Index, 0, dval)
#define TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_SetSignal_OtsAirTmp_Raw(nval) SpySetTxSignalRaw(TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Index, 0, nval)
#define TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_OtsAirTmpCrVal_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Index, 1, dPhysicalValue);
#define TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_SetSignal_OtsAirTmpCrVal_Physical(dval) SpySetTxSignal(TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Index, 1, dval)
#define TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_SetSignal_OtsAirTmpCrVal_Raw(nval) SpySetTxSignalRaw(TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Index, 1, nval)
#define TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_OtsAirTmpCrValMsk_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Index, 2, dPhysicalValue);
#define TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_SetSignal_OtsAirTmpCrValMsk_Physical(dval) SpySetTxSignal(TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Index, 2, dval)
#define TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_SetSignal_OtsAirTmpCrValMsk_Raw(nval) SpySetTxSignalRaw(TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Index, 2, nval)
#define TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_OtsAirTmpCrValV_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Index, 3, dPhysicalValue);
#define TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_SetSignal_OtsAirTmpCrValV_Physical(dval) SpySetTxSignal(TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Index, 3, dval)
#define TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_SetSignal_OtsAirTmpCrValV_Raw(nval) SpySetTxSignalRaw(TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Index, 3, nval)
#define TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_EngInltSpcfcHmdty_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Index, 4, dPhysicalValue);
#define TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_SetSignal_EngInltSpcfcHmdty_Physical(dval) SpySetTxSignal(TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Index, 4, dval)
#define TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_SetSignal_EngInltSpcfcHmdty_Raw(nval) SpySetTxSignalRaw(TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Index, 4, nval)
#define TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_EngInltSpcfcHmdtyM_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Index, 5, dPhysicalValue);
#define TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_SetSignal_EngInltSpcfcHmdtyM_Physical(dval) SpySetTxSignal(TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Index, 5, dval)
#define TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_SetSignal_EngInltSpcfcHmdtyM_Raw(nval) SpySetTxSignalRaw(TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Index, 5, nval)
#define TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_EngInltSpcfcHmdtyV_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Index, 6, dPhysicalValue);
#define TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_SetSignal_EngInltSpcfcHmdtyV_Physical(dval) SpySetTxSignal(TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Index, 6, dval)
#define TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_SetSignal_EngInltSpcfcHmdtyV_Raw(nval) SpySetTxSignalRaw(TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Index, 6, nval)
#define TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_OtsAirTmpV_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Index, 7, dPhysicalValue);
#define TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_SetSignal_OtsAirTmpV_Physical(dval) SpySetTxSignal(TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Index, 7, dval)
#define TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_SetSignal_OtsAirTmpV_Raw(nval) SpySetTxSignalRaw(TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Index, 7, nval)
int TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_TransmitFast();
#define TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step4_PPEI_Engine_Environmental_Stat_HS_CAN_Index, 0)
extern int TX_step5_Instrument_Panel_Sensor_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double IPSnsrSolrAnglFltd; /// Min: 0 Max: 1 Units: 
    BYTE IPSnsrSolrAnglFltd_raw;
    double IPSnsrRwSolrIntFltd; /// Min: 0 Max: 1 Units: 
    BYTE IPSnsrRwSolrIntFltd_raw;
    double IPSnsrRwSolrInt; /// Min: 0 Max: 765 Units: W/m2
    BYTE IPSnsrRwSolrInt_raw;
    double IPSnsrSolrAzmthAngl; /// Min: -180 Max: 330 Units: deg
    BYTE IPSnsrSolrAzmthAngl_raw;
    double IPSnsrSolrElvtnAngl; /// Min: 0 Max: 255 Units: deg
    BYTE IPSnsrSolrElvtnAngl_raw;
} TX_step5_Instrument_Panel_Sensor_HS_CAN;

#pragma warning(disable : 4005)
#define TX_step5_Instrument_Panel_Sensor_HS_CAN_$_IPSnsrSolrAnglFltd_$$_False 0
#define TX_step5_Instrument_Panel_Sensor_HS_CAN_$_IPSnsrSolrAnglFltd_$$_True 1
#define TX_step5_Instrument_Panel_Sensor_HS_CAN_$_IPSnsrRwSolrIntFltd_$$_False 0
#define TX_step5_Instrument_Panel_Sensor_HS_CAN_$_IPSnsrRwSolrIntFltd_$$_True 1
#pragma warning(default : 4005)

void TX_step5_Instrument_Panel_Sensor_HS_CAN_Init(TX_step5_Instrument_Panel_Sensor_HS_CAN * pMsg);
int TX_step5_Instrument_Panel_Sensor_HS_CAN_Transmit(TX_step5_Instrument_Panel_Sensor_HS_CAN * pMsg);
int TX_step5_Instrument_Panel_Sensor_HS_CAN_Transmit_raw(TX_step5_Instrument_Panel_Sensor_HS_CAN * pMsg);
int TX_step5_Instrument_Panel_Sensor_HS_CAN_UpdateBytesFromSignals(TX_step5_Instrument_Panel_Sensor_HS_CAN * pMsg);
int TX_step5_Instrument_Panel_Sensor_HS_CAN_UpdateBytesFromRawSignals(TX_step5_Instrument_Panel_Sensor_HS_CAN * pMsg);
#define TX_step5_Instrument_Panel_Sensor_HS_CAN_IPSnsrSolrAnglFltd_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step5_Instrument_Panel_Sensor_HS_CAN_Index, 0, dPhysicalValue);
#define TX_step5_Instrument_Panel_Sensor_HS_CAN_SetSignal_IPSnsrSolrAnglFltd_Physical(dval) SpySetTxSignal(TX_step5_Instrument_Panel_Sensor_HS_CAN_Index, 0, dval)
#define TX_step5_Instrument_Panel_Sensor_HS_CAN_SetSignal_IPSnsrSolrAnglFltd_Raw(nval) SpySetTxSignalRaw(TX_step5_Instrument_Panel_Sensor_HS_CAN_Index, 0, nval)
#define TX_step5_Instrument_Panel_Sensor_HS_CAN_IPSnsrRwSolrIntFltd_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step5_Instrument_Panel_Sensor_HS_CAN_Index, 1, dPhysicalValue);
#define TX_step5_Instrument_Panel_Sensor_HS_CAN_SetSignal_IPSnsrRwSolrIntFltd_Physical(dval) SpySetTxSignal(TX_step5_Instrument_Panel_Sensor_HS_CAN_Index, 1, dval)
#define TX_step5_Instrument_Panel_Sensor_HS_CAN_SetSignal_IPSnsrRwSolrIntFltd_Raw(nval) SpySetTxSignalRaw(TX_step5_Instrument_Panel_Sensor_HS_CAN_Index, 1, nval)
#define TX_step5_Instrument_Panel_Sensor_HS_CAN_IPSnsrRwSolrInt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step5_Instrument_Panel_Sensor_HS_CAN_Index, 2, dPhysicalValue);
#define TX_step5_Instrument_Panel_Sensor_HS_CAN_SetSignal_IPSnsrRwSolrInt_Physical(dval) SpySetTxSignal(TX_step5_Instrument_Panel_Sensor_HS_CAN_Index, 2, dval)
#define TX_step5_Instrument_Panel_Sensor_HS_CAN_SetSignal_IPSnsrRwSolrInt_Raw(nval) SpySetTxSignalRaw(TX_step5_Instrument_Panel_Sensor_HS_CAN_Index, 2, nval)
#define TX_step5_Instrument_Panel_Sensor_HS_CAN_IPSnsrSolrAzmthAngl_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step5_Instrument_Panel_Sensor_HS_CAN_Index, 3, dPhysicalValue);
#define TX_step5_Instrument_Panel_Sensor_HS_CAN_SetSignal_IPSnsrSolrAzmthAngl_Physical(dval) SpySetTxSignal(TX_step5_Instrument_Panel_Sensor_HS_CAN_Index, 3, dval)
#define TX_step5_Instrument_Panel_Sensor_HS_CAN_SetSignal_IPSnsrSolrAzmthAngl_Raw(nval) SpySetTxSignalRaw(TX_step5_Instrument_Panel_Sensor_HS_CAN_Index, 3, nval)
#define TX_step5_Instrument_Panel_Sensor_HS_CAN_IPSnsrSolrElvtnAngl_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step5_Instrument_Panel_Sensor_HS_CAN_Index, 4, dPhysicalValue);
#define TX_step5_Instrument_Panel_Sensor_HS_CAN_SetSignal_IPSnsrSolrElvtnAngl_Physical(dval) SpySetTxSignal(TX_step5_Instrument_Panel_Sensor_HS_CAN_Index, 4, dval)
#define TX_step5_Instrument_Panel_Sensor_HS_CAN_SetSignal_IPSnsrSolrElvtnAngl_Raw(nval) SpySetTxSignalRaw(TX_step5_Instrument_Panel_Sensor_HS_CAN_Index, 4, nval)
int TX_step5_Instrument_Panel_Sensor_HS_CAN_TransmitFast();
#define TX_step5_Instrument_Panel_Sensor_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step5_Instrument_Panel_Sensor_HS_CAN_Index, 0)
extern int TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double DistRollCntAvgDrvn; /// Min: 0 Max: 1023.875 Units: m
    WORD DistRollCntAvgDrvn_raw;
    double DstRolCntAvgDrnRstOc; /// Min: 0 Max: 1 Units: 
    BYTE DstRolCntAvgDrnRstOc_raw;
    double DistRollCntAvgDrvnSrc; /// Min: 0 Max: 1 Units: 
    BYTE DistRollCntAvgDrvnSrc_raw;
    double DistRollCntAvgDrvnV; /// Min: 0 Max: 1 Units: 
    BYTE DistRollCntAvgDrvnV_raw;
    double DstRolCntAvgNonDrvn; /// Min: 0 Max: 1023.875 Units: m
    WORD DstRolCntAvgNonDrvn_raw;
    double DstRolCntAvNDrRstOc; /// Min: 0 Max: 1 Units: 
    BYTE DstRolCntAvNDrRstOc_raw;
    double DstRolCntAvgNonDrvnV; /// Min: 0 Max: 1 Units: 
    BYTE DstRolCntAvgNonDrvnV_raw;
    double VehSpdAvgDrvn; /// Min: 0 Max: 511.984375 Units: km/h
    WORD VehSpdAvgDrvn_raw;
    double VehSpdAvgDrvnSrc; /// Min: 0 Max: 1 Units: 
    BYTE VehSpdAvgDrvnSrc_raw;
    double VehSpdAvgDrvnV; /// Min: 0 Max: 1 Units: 
    BYTE VehSpdAvgDrvnV_raw;
    double VehSpdAvgNDrvn; /// Min: 0 Max: 511.984375 Units: km/h
    WORD VehSpdAvgNDrvn_raw;
    double VehSpdAvgNDrvnV; /// Min: 0 Max: 1 Units: 
    BYTE VehSpdAvgNDrvnV_raw;
} TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN;

#pragma warning(disable : 4005)
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_$_DstRolCntAvgDrnRstOc_$$_False 0
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_$_DstRolCntAvgDrnRstOc_$$_True 1
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_$_DistRollCntAvgDrvnSrc_$$_Transmission_Output_Speed 0
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_$_DistRollCntAvgDrvnSrc_$$_Wheel_Speed 1
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_$_DistRollCntAvgDrvnV_$$_Valid 0
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_$_DistRollCntAvgDrvnV_$$_Invalid 1
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_$_DstRolCntAvNDrRstOc_$$_False 0
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_$_DstRolCntAvNDrRstOc_$$_True 1
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_$_DstRolCntAvgNonDrvnV_$$_Valid 0
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_$_DstRolCntAvgNonDrvnV_$$_Invalid 1
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_$_VehSpdAvgDrvnSrc_$$_Transmission_Output_Speed 0
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_$_VehSpdAvgDrvnSrc_$$_Wheel_Speed 1
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_$_VehSpdAvgDrvnV_$$_Valid 0
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_$_VehSpdAvgDrvnV_$$_Invalid 1
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_$_VehSpdAvgNDrvnV_$$_Valid 0
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_$_VehSpdAvgNDrvnV_$$_Invalid 1
#pragma warning(default : 4005)

void TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Init(TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN * pMsg);
int TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Transmit(TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN * pMsg);
int TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Transmit_raw(TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN * pMsg);
int TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_UpdateBytesFromSignals(TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN * pMsg);
int TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_UpdateBytesFromRawSignals(TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN * pMsg);
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_DistRollCntAvgDrvn_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 0, dPhysicalValue);
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_SetSignal_DistRollCntAvgDrvn_Physical(dval) SpySetTxSignal(TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 0, dval)
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_SetSignal_DistRollCntAvgDrvn_Raw(nval) SpySetTxSignalRaw(TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 0, nval)
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_DstRolCntAvgDrnRstOc_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 1, dPhysicalValue);
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_SetSignal_DstRolCntAvgDrnRstOc_Physical(dval) SpySetTxSignal(TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 1, dval)
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_SetSignal_DstRolCntAvgDrnRstOc_Raw(nval) SpySetTxSignalRaw(TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 1, nval)
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_DistRollCntAvgDrvnSrc_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 2, dPhysicalValue);
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_SetSignal_DistRollCntAvgDrvnSrc_Physical(dval) SpySetTxSignal(TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 2, dval)
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_SetSignal_DistRollCntAvgDrvnSrc_Raw(nval) SpySetTxSignalRaw(TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 2, nval)
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_DistRollCntAvgDrvnV_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 3, dPhysicalValue);
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_SetSignal_DistRollCntAvgDrvnV_Physical(dval) SpySetTxSignal(TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 3, dval)
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_SetSignal_DistRollCntAvgDrvnV_Raw(nval) SpySetTxSignalRaw(TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 3, nval)
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_DstRolCntAvgNonDrvn_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 4, dPhysicalValue);
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_SetSignal_DstRolCntAvgNonDrvn_Physical(dval) SpySetTxSignal(TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 4, dval)
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_SetSignal_DstRolCntAvgNonDrvn_Raw(nval) SpySetTxSignalRaw(TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 4, nval)
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_DstRolCntAvNDrRstOc_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 5, dPhysicalValue);
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_SetSignal_DstRolCntAvNDrRstOc_Physical(dval) SpySetTxSignal(TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 5, dval)
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_SetSignal_DstRolCntAvNDrRstOc_Raw(nval) SpySetTxSignalRaw(TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 5, nval)
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_DstRolCntAvgNonDrvnV_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 6, dPhysicalValue);
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_SetSignal_DstRolCntAvgNonDrvnV_Physical(dval) SpySetTxSignal(TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 6, dval)
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_SetSignal_DstRolCntAvgNonDrvnV_Raw(nval) SpySetTxSignalRaw(TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 6, nval)
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_VehSpdAvgDrvn_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 7, dPhysicalValue);
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_SetSignal_VehSpdAvgDrvn_Physical(dval) SpySetTxSignal(TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 7, dval)
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_SetSignal_VehSpdAvgDrvn_Raw(nval) SpySetTxSignalRaw(TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 7, nval)
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_VehSpdAvgDrvnSrc_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 8, dPhysicalValue);
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_SetSignal_VehSpdAvgDrvnSrc_Physical(dval) SpySetTxSignal(TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 8, dval)
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_SetSignal_VehSpdAvgDrvnSrc_Raw(nval) SpySetTxSignalRaw(TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 8, nval)
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_VehSpdAvgDrvnV_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 9, dPhysicalValue);
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_SetSignal_VehSpdAvgDrvnV_Physical(dval) SpySetTxSignal(TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 9, dval)
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_SetSignal_VehSpdAvgDrvnV_Raw(nval) SpySetTxSignalRaw(TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 9, nval)
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_VehSpdAvgNDrvn_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 10, dPhysicalValue);
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_SetSignal_VehSpdAvgNDrvn_Physical(dval) SpySetTxSignal(TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 10, dval)
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_SetSignal_VehSpdAvgNDrvn_Raw(nval) SpySetTxSignalRaw(TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 10, nval)
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_VehSpdAvgNDrvnV_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 11, dPhysicalValue);
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_SetSignal_VehSpdAvgNDrvnV_Physical(dval) SpySetTxSignal(TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 11, dval)
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_SetSignal_VehSpdAvgNDrvnV_Raw(nval) SpySetTxSignalRaw(TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 11, nval)
int TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_TransmitFast();
#define TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step6_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 0)
extern int TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double AccActPos; /// Min: 0 Max: 100.000035 Units: %
    BYTE AccActPos_raw;
    double AccActPosV; /// Min: 0 Max: 1 Units: 
    BYTE AccActPosV_raw;
    double CrsCntAtv; /// Min: 0 Max: 1 Units: 
    BYTE CrsCntAtv_raw;
    double CrsCntEnbld; /// Min: 0 Max: 1 Units: 
    BYTE CrsCntEnbld_raw;
    double Eng12vStrtrMtrCmmdOn; /// Min: 0 Max: 1 Units: 
    BYTE Eng12vStrtrMtrCmmdOn_raw;
    double EngCntrlRunCrnkTrmSt; /// Min: 0 Max: 1 Units: 
    BYTE EngCntrlRunCrnkTrmSt_raw;
    double EngIdlAtv; /// Min: 0 Max: 1 Units: 
    BYTE EngIdlAtv_raw;
    double EngAirIntBstPr; /// Min: -128 Max: 127 Units: kPaG
    BYTE EngAirIntBstPr_raw;
    double EngAirIntBstPrV; /// Min: 0 Max: 1 Units: 
    BYTE EngAirIntBstPrV_raw;
    double EngRunAtv; /// Min: 0 Max: 1 Units: 
    BYTE EngRunAtv_raw;
    double EngSpd; /// Min: 0 Max: 16383.75 Units: rpm
    WORD EngSpd_raw;
    double EngSpdStat; /// Min: 0 Max: 3 Units: 
    BYTE EngSpdStat_raw;
    double PT_BrkPedDscrtInpStat; /// Min: 0 Max: 1 Units: 
    BYTE PT_BrkPedDscrtInpStat_raw;
    double PT_BrkPedDscrtInpStatV; /// Min: 0 Max: 1 Units: 
    BYTE PT_BrkPedDscrtInpStatV_raw;
    double PTCrnkAbrted; /// Min: 0 Max: 1 Units: 
    BYTE PTCrnkAbrted_raw;
    double PT_CrnkAct; /// Min: 0 Max: 1 Units: 
    BYTE PT_CrnkAct_raw;
    double PTRunAbrt; /// Min: 0 Max: 1 Units: 
    BYTE PTRunAbrt_raw;
    double RmVhStrtEngRng; /// Min: 0 Max: 1 Units: 
    BYTE RmVhStrtEngRng_raw;
    double SpdLmtrSpdWrngEnbld; /// Min: 0 Max: 1 Units: 
    BYTE SpdLmtrSpdWrngEnbld_raw;
} TX_step7_PPEI_Engine_General_Status_1_HS_CAN;

#pragma warning(disable : 4005)
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_$_AccActPosV_$$_Valid 0
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_$_AccActPosV_$$_Invalid 1
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_$_CrsCntAtv_$$_False 0
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_$_CrsCntAtv_$$_True 1
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_$_CrsCntEnbld_$$_False 0
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_$_CrsCntEnbld_$$_True 1
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_$_Eng12vStrtrMtrCmmdOn_$$_False 0
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_$_Eng12vStrtrMtrCmmdOn_$$_True 1
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_$_EngCntrlRunCrnkTrmSt_$$_Inactive 0
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_$_EngCntrlRunCrnkTrmSt_$$_Active 1
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_$_EngIdlAtv_$$_False 0
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_$_EngIdlAtv_$$_True 1
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_$_EngAirIntBstPrV_$$_Valid 0
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_$_EngAirIntBstPrV_$$_Invalid 1
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_$_EngRunAtv_$$_False 0
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_$_EngRunAtv_$$_True 1
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_$_EngSpdStat_$$_Normal_Operation 0
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_$_EngSpdStat_$$_Degraded_Operation 1
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_$_EngSpdStat_$$_Invalid 3
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_$_PT_BrkPedDscrtInpStat_$$_Brake_Not_Applied 0
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_$_PT_BrkPedDscrtInpStat_$$_Brake_Applied 1
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_$_PT_BrkPedDscrtInpStatV_$$_Valid 0
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_$_PT_BrkPedDscrtInpStatV_$$_Invalid 1
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_$_PTCrnkAbrted_$$_False 0
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_$_PTCrnkAbrted_$$_True 1
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_$_PT_CrnkAct_$$_False 0
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_$_PT_CrnkAct_$$_True 1
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_$_PTRunAbrt_$$_False 0
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_$_PTRunAbrt_$$_True 1
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_$_RmVhStrtEngRng_$$_False 0
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_$_RmVhStrtEngRng_$$_True 1
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_$_SpdLmtrSpdWrngEnbld_$$_False 0
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_$_SpdLmtrSpdWrngEnbld_$$_True 1
#pragma warning(default : 4005)

void TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Init(TX_step7_PPEI_Engine_General_Status_1_HS_CAN * pMsg);
int TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Transmit(TX_step7_PPEI_Engine_General_Status_1_HS_CAN * pMsg);
int TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Transmit_raw(TX_step7_PPEI_Engine_General_Status_1_HS_CAN * pMsg);
int TX_step7_PPEI_Engine_General_Status_1_HS_CAN_UpdateBytesFromSignals(TX_step7_PPEI_Engine_General_Status_1_HS_CAN * pMsg);
int TX_step7_PPEI_Engine_General_Status_1_HS_CAN_UpdateBytesFromRawSignals(TX_step7_PPEI_Engine_General_Status_1_HS_CAN * pMsg);
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_AccActPos_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 0, dPhysicalValue);
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_SetSignal_AccActPos_Physical(dval) SpySetTxSignal(TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 0, dval)
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_SetSignal_AccActPos_Raw(nval) SpySetTxSignalRaw(TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 0, nval)
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_AccActPosV_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 1, dPhysicalValue);
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_SetSignal_AccActPosV_Physical(dval) SpySetTxSignal(TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 1, dval)
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_SetSignal_AccActPosV_Raw(nval) SpySetTxSignalRaw(TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 1, nval)
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_CrsCntAtv_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 2, dPhysicalValue);
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_SetSignal_CrsCntAtv_Physical(dval) SpySetTxSignal(TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 2, dval)
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_SetSignal_CrsCntAtv_Raw(nval) SpySetTxSignalRaw(TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 2, nval)
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_CrsCntEnbld_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 3, dPhysicalValue);
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_SetSignal_CrsCntEnbld_Physical(dval) SpySetTxSignal(TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 3, dval)
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_SetSignal_CrsCntEnbld_Raw(nval) SpySetTxSignalRaw(TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 3, nval)
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Eng12vStrtrMtrCmmdOn_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 4, dPhysicalValue);
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_SetSignal_Eng12vStrtrMtrCmmdOn_Physical(dval) SpySetTxSignal(TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 4, dval)
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_SetSignal_Eng12vStrtrMtrCmmdOn_Raw(nval) SpySetTxSignalRaw(TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 4, nval)
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_EngCntrlRunCrnkTrmSt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 5, dPhysicalValue);
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_SetSignal_EngCntrlRunCrnkTrmSt_Physical(dval) SpySetTxSignal(TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 5, dval)
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_SetSignal_EngCntrlRunCrnkTrmSt_Raw(nval) SpySetTxSignalRaw(TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 5, nval)
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_EngIdlAtv_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 6, dPhysicalValue);
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_SetSignal_EngIdlAtv_Physical(dval) SpySetTxSignal(TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 6, dval)
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_SetSignal_EngIdlAtv_Raw(nval) SpySetTxSignalRaw(TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 6, nval)
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_EngAirIntBstPr_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 7, dPhysicalValue);
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_SetSignal_EngAirIntBstPr_Physical(dval) SpySetTxSignal(TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 7, dval)
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_SetSignal_EngAirIntBstPr_Raw(nval) SpySetTxSignalRaw(TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 7, nval)
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_EngAirIntBstPrV_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 8, dPhysicalValue);
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_SetSignal_EngAirIntBstPrV_Physical(dval) SpySetTxSignal(TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 8, dval)
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_SetSignal_EngAirIntBstPrV_Raw(nval) SpySetTxSignalRaw(TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 8, nval)
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_EngRunAtv_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 9, dPhysicalValue);
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_SetSignal_EngRunAtv_Physical(dval) SpySetTxSignal(TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 9, dval)
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_SetSignal_EngRunAtv_Raw(nval) SpySetTxSignalRaw(TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 9, nval)
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_EngSpd_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 10, dPhysicalValue);
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_SetSignal_EngSpd_Physical(dval) SpySetTxSignal(TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 10, dval)
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_SetSignal_EngSpd_Raw(nval) SpySetTxSignalRaw(TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 10, nval)
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_EngSpdStat_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 11, dPhysicalValue);
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_SetSignal_EngSpdStat_Physical(dval) SpySetTxSignal(TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 11, dval)
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_SetSignal_EngSpdStat_Raw(nval) SpySetTxSignalRaw(TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 11, nval)
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_PT_BrkPedDscrtInpStat_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 12, dPhysicalValue);
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_SetSignal_PT_BrkPedDscrtInpStat_Physical(dval) SpySetTxSignal(TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 12, dval)
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_SetSignal_PT_BrkPedDscrtInpStat_Raw(nval) SpySetTxSignalRaw(TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 12, nval)
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_PT_BrkPedDscrtInpStatV_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 13, dPhysicalValue);
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_SetSignal_PT_BrkPedDscrtInpStatV_Physical(dval) SpySetTxSignal(TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 13, dval)
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_SetSignal_PT_BrkPedDscrtInpStatV_Raw(nval) SpySetTxSignalRaw(TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 13, nval)
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_PTCrnkAbrted_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 14, dPhysicalValue);
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_SetSignal_PTCrnkAbrted_Physical(dval) SpySetTxSignal(TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 14, dval)
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_SetSignal_PTCrnkAbrted_Raw(nval) SpySetTxSignalRaw(TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 14, nval)
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_PT_CrnkAct_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 15, dPhysicalValue);
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_SetSignal_PT_CrnkAct_Physical(dval) SpySetTxSignal(TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 15, dval)
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_SetSignal_PT_CrnkAct_Raw(nval) SpySetTxSignalRaw(TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 15, nval)
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_PTRunAbrt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 16, dPhysicalValue);
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_SetSignal_PTRunAbrt_Physical(dval) SpySetTxSignal(TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 16, dval)
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_SetSignal_PTRunAbrt_Raw(nval) SpySetTxSignalRaw(TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 16, nval)
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_RmVhStrtEngRng_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 17, dPhysicalValue);
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_SetSignal_RmVhStrtEngRng_Physical(dval) SpySetTxSignal(TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 17, dval)
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_SetSignal_RmVhStrtEngRng_Raw(nval) SpySetTxSignalRaw(TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 17, nval)
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_SpdLmtrSpdWrngEnbld_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 18, dPhysicalValue);
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_SetSignal_SpdLmtrSpdWrngEnbld_Physical(dval) SpySetTxSignal(TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 18, dval)
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_SetSignal_SpdLmtrSpdWrngEnbld_Raw(nval) SpySetTxSignalRaw(TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 18, nval)
int TX_step7_PPEI_Engine_General_Status_1_HS_CAN_TransmitFast();
#define TX_step7_PPEI_Engine_General_Status_1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step7_PPEI_Engine_General_Status_1_HS_CAN_Index, 0)
extern int TX_stepX_diagRequest1_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_stepX_diagRequest1_HS_CAN;


void TX_stepX_diagRequest1_HS_CAN_Init(TX_stepX_diagRequest1_HS_CAN * pMsg);
int TX_stepX_diagRequest1_HS_CAN_Transmit(TX_stepX_diagRequest1_HS_CAN * pMsg);
int TX_stepX_diagRequest1_HS_CAN_Transmit_raw(TX_stepX_diagRequest1_HS_CAN * pMsg);
int TX_stepX_diagRequest1_HS_CAN_TransmitFast();
#define TX_stepX_diagRequest1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_stepX_diagRequest1_HS_CAN_Index, 0)
extern int TX_step15_diagRequest2_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_step15_diagRequest2_HS_CAN;


void TX_step15_diagRequest2_HS_CAN_Init(TX_step15_diagRequest2_HS_CAN * pMsg);
int TX_step15_diagRequest2_HS_CAN_Transmit(TX_step15_diagRequest2_HS_CAN * pMsg);
int TX_step15_diagRequest2_HS_CAN_Transmit_raw(TX_step15_diagRequest2_HS_CAN * pMsg);
int TX_step15_diagRequest2_HS_CAN_TransmitFast();
#define TX_step15_diagRequest2_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step15_diagRequest2_HS_CAN_Index, 0)
extern int TX_step16_diagRequest2_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_step16_diagRequest2_HS_CAN;


void TX_step16_diagRequest2_HS_CAN_Init(TX_step16_diagRequest2_HS_CAN * pMsg);
int TX_step16_diagRequest2_HS_CAN_Transmit(TX_step16_diagRequest2_HS_CAN * pMsg);
int TX_step16_diagRequest2_HS_CAN_Transmit_raw(TX_step16_diagRequest2_HS_CAN * pMsg);
int TX_step16_diagRequest2_HS_CAN_TransmitFast();
#define TX_step16_diagRequest2_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step16_diagRequest2_HS_CAN_Index, 0)
extern int TX_step17_diagRequest2_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_step17_diagRequest2_HS_CAN;


void TX_step17_diagRequest2_HS_CAN_Init(TX_step17_diagRequest2_HS_CAN * pMsg);
int TX_step17_diagRequest2_HS_CAN_Transmit(TX_step17_diagRequest2_HS_CAN * pMsg);
int TX_step17_diagRequest2_HS_CAN_Transmit_raw(TX_step17_diagRequest2_HS_CAN * pMsg);
int TX_step17_diagRequest2_HS_CAN_TransmitFast();
#define TX_step17_diagRequest2_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step17_diagRequest2_HS_CAN_Index, 0)
extern int TX_step18_diagRequest2_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_step18_diagRequest2_HS_CAN;


void TX_step18_diagRequest2_HS_CAN_Init(TX_step18_diagRequest2_HS_CAN * pMsg);
int TX_step18_diagRequest2_HS_CAN_Transmit(TX_step18_diagRequest2_HS_CAN * pMsg);
int TX_step18_diagRequest2_HS_CAN_Transmit_raw(TX_step18_diagRequest2_HS_CAN * pMsg);
int TX_step18_diagRequest2_HS_CAN_TransmitFast();
#define TX_step18_diagRequest2_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step18_diagRequest2_HS_CAN_Index, 0)
extern int TX_step19_diagRequest2_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_step19_diagRequest2_HS_CAN;


void TX_step19_diagRequest2_HS_CAN_Init(TX_step19_diagRequest2_HS_CAN * pMsg);
int TX_step19_diagRequest2_HS_CAN_Transmit(TX_step19_diagRequest2_HS_CAN * pMsg);
int TX_step19_diagRequest2_HS_CAN_Transmit_raw(TX_step19_diagRequest2_HS_CAN * pMsg);
int TX_step19_diagRequest2_HS_CAN_TransmitFast();
#define TX_step19_diagRequest2_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step19_diagRequest2_HS_CAN_Index, 0)
extern int TX_step20_diagRequest2_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_step20_diagRequest2_HS_CAN;


void TX_step20_diagRequest2_HS_CAN_Init(TX_step20_diagRequest2_HS_CAN * pMsg);
int TX_step20_diagRequest2_HS_CAN_Transmit(TX_step20_diagRequest2_HS_CAN * pMsg);
int TX_step20_diagRequest2_HS_CAN_Transmit_raw(TX_step20_diagRequest2_HS_CAN * pMsg);
int TX_step20_diagRequest2_HS_CAN_TransmitFast();
#define TX_step20_diagRequest2_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step20_diagRequest2_HS_CAN_Index, 0)
extern int TX_step21_diagRequest2_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_step21_diagRequest2_HS_CAN;


void TX_step21_diagRequest2_HS_CAN_Init(TX_step21_diagRequest2_HS_CAN * pMsg);
int TX_step21_diagRequest2_HS_CAN_Transmit(TX_step21_diagRequest2_HS_CAN * pMsg);
int TX_step21_diagRequest2_HS_CAN_Transmit_raw(TX_step21_diagRequest2_HS_CAN * pMsg);
int TX_step21_diagRequest2_HS_CAN_TransmitFast();
#define TX_step21_diagRequest2_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step21_diagRequest2_HS_CAN_Index, 0)
extern int TX_step22_diagRequest2_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_step22_diagRequest2_HS_CAN;


void TX_step22_diagRequest2_HS_CAN_Init(TX_step22_diagRequest2_HS_CAN * pMsg);
int TX_step22_diagRequest2_HS_CAN_Transmit(TX_step22_diagRequest2_HS_CAN * pMsg);
int TX_step22_diagRequest2_HS_CAN_Transmit_raw(TX_step22_diagRequest2_HS_CAN * pMsg);
int TX_step22_diagRequest2_HS_CAN_TransmitFast();
#define TX_step22_diagRequest2_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step22_diagRequest2_HS_CAN_Index, 0)
extern int TX_step23_diagRequest2_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_step23_diagRequest2_HS_CAN;


void TX_step23_diagRequest2_HS_CAN_Init(TX_step23_diagRequest2_HS_CAN * pMsg);
int TX_step23_diagRequest2_HS_CAN_Transmit(TX_step23_diagRequest2_HS_CAN * pMsg);
int TX_step23_diagRequest2_HS_CAN_Transmit_raw(TX_step23_diagRequest2_HS_CAN * pMsg);
int TX_step23_diagRequest2_HS_CAN_TransmitFast();
#define TX_step23_diagRequest2_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step23_diagRequest2_HS_CAN_Index, 0)
extern int TX_step24_diagRequest2_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_step24_diagRequest2_HS_CAN;


void TX_step24_diagRequest2_HS_CAN_Init(TX_step24_diagRequest2_HS_CAN * pMsg);
int TX_step24_diagRequest2_HS_CAN_Transmit(TX_step24_diagRequest2_HS_CAN * pMsg);
int TX_step24_diagRequest2_HS_CAN_Transmit_raw(TX_step24_diagRequest2_HS_CAN * pMsg);
int TX_step24_diagRequest2_HS_CAN_TransmitFast();
#define TX_step24_diagRequest2_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step24_diagRequest2_HS_CAN_Index, 0)
extern int TX_step25_diagRequest2_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_step25_diagRequest2_HS_CAN;


void TX_step25_diagRequest2_HS_CAN_Init(TX_step25_diagRequest2_HS_CAN * pMsg);
int TX_step25_diagRequest2_HS_CAN_Transmit(TX_step25_diagRequest2_HS_CAN * pMsg);
int TX_step25_diagRequest2_HS_CAN_Transmit_raw(TX_step25_diagRequest2_HS_CAN * pMsg);
int TX_step25_diagRequest2_HS_CAN_TransmitFast();
#define TX_step25_diagRequest2_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step25_diagRequest2_HS_CAN_Index, 0)
extern int TX_step26_diagRequest2_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_step26_diagRequest2_HS_CAN;


void TX_step26_diagRequest2_HS_CAN_Init(TX_step26_diagRequest2_HS_CAN * pMsg);
int TX_step26_diagRequest2_HS_CAN_Transmit(TX_step26_diagRequest2_HS_CAN * pMsg);
int TX_step26_diagRequest2_HS_CAN_Transmit_raw(TX_step26_diagRequest2_HS_CAN * pMsg);
int TX_step26_diagRequest2_HS_CAN_TransmitFast();
#define TX_step26_diagRequest2_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step26_diagRequest2_HS_CAN_Index, 0)
extern int TX_step27_diagRequest2_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_step27_diagRequest2_HS_CAN;


void TX_step27_diagRequest2_HS_CAN_Init(TX_step27_diagRequest2_HS_CAN * pMsg);
int TX_step27_diagRequest2_HS_CAN_Transmit(TX_step27_diagRequest2_HS_CAN * pMsg);
int TX_step27_diagRequest2_HS_CAN_Transmit_raw(TX_step27_diagRequest2_HS_CAN * pMsg);
int TX_step27_diagRequest2_HS_CAN_TransmitFast();
#define TX_step27_diagRequest2_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step27_diagRequest2_HS_CAN_Index, 0)
extern int TX_step28_diagRequest2_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_step28_diagRequest2_HS_CAN;


void TX_step28_diagRequest2_HS_CAN_Init(TX_step28_diagRequest2_HS_CAN * pMsg);
int TX_step28_diagRequest2_HS_CAN_Transmit(TX_step28_diagRequest2_HS_CAN * pMsg);
int TX_step28_diagRequest2_HS_CAN_Transmit_raw(TX_step28_diagRequest2_HS_CAN * pMsg);
int TX_step28_diagRequest2_HS_CAN_TransmitFast();
#define TX_step28_diagRequest2_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step28_diagRequest2_HS_CAN_Index, 0)
extern int TX_step29_diagRequest2_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_step29_diagRequest2_HS_CAN;


void TX_step29_diagRequest2_HS_CAN_Init(TX_step29_diagRequest2_HS_CAN * pMsg);
int TX_step29_diagRequest2_HS_CAN_Transmit(TX_step29_diagRequest2_HS_CAN * pMsg);
int TX_step29_diagRequest2_HS_CAN_Transmit_raw(TX_step29_diagRequest2_HS_CAN * pMsg);
int TX_step29_diagRequest2_HS_CAN_TransmitFast();
#define TX_step29_diagRequest2_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step29_diagRequest2_HS_CAN_Index, 0)
extern int TX_step30_diagRequest2_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_step30_diagRequest2_HS_CAN;


void TX_step30_diagRequest2_HS_CAN_Init(TX_step30_diagRequest2_HS_CAN * pMsg);
int TX_step30_diagRequest2_HS_CAN_Transmit(TX_step30_diagRequest2_HS_CAN * pMsg);
int TX_step30_diagRequest2_HS_CAN_Transmit_raw(TX_step30_diagRequest2_HS_CAN * pMsg);
int TX_step30_diagRequest2_HS_CAN_TransmitFast();
#define TX_step30_diagRequest2_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step30_diagRequest2_HS_CAN_Index, 0)
extern int TX_step31_diagRequest2_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_step31_diagRequest2_HS_CAN;


void TX_step31_diagRequest2_HS_CAN_Init(TX_step31_diagRequest2_HS_CAN * pMsg);
int TX_step31_diagRequest2_HS_CAN_Transmit(TX_step31_diagRequest2_HS_CAN * pMsg);
int TX_step31_diagRequest2_HS_CAN_Transmit_raw(TX_step31_diagRequest2_HS_CAN * pMsg);
int TX_step31_diagRequest2_HS_CAN_TransmitFast();
#define TX_step31_diagRequest2_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step31_diagRequest2_HS_CAN_Index, 0)
extern int TX_step32_diagRequest2_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_step32_diagRequest2_HS_CAN;


void TX_step32_diagRequest2_HS_CAN_Init(TX_step32_diagRequest2_HS_CAN * pMsg);
int TX_step32_diagRequest2_HS_CAN_Transmit(TX_step32_diagRequest2_HS_CAN * pMsg);
int TX_step32_diagRequest2_HS_CAN_Transmit_raw(TX_step32_diagRequest2_HS_CAN * pMsg);
int TX_step32_diagRequest2_HS_CAN_TransmitFast();
#define TX_step32_diagRequest2_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step32_diagRequest2_HS_CAN_Index, 0)
extern int TX_step33_diagRequest2_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_step33_diagRequest2_HS_CAN;


void TX_step33_diagRequest2_HS_CAN_Init(TX_step33_diagRequest2_HS_CAN * pMsg);
int TX_step33_diagRequest2_HS_CAN_Transmit(TX_step33_diagRequest2_HS_CAN * pMsg);
int TX_step33_diagRequest2_HS_CAN_Transmit_raw(TX_step33_diagRequest2_HS_CAN * pMsg);
int TX_step33_diagRequest2_HS_CAN_TransmitFast();
#define TX_step33_diagRequest2_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step33_diagRequest2_HS_CAN_Index, 0)
extern int TX_step34_diagRequest2_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_step34_diagRequest2_HS_CAN;


void TX_step34_diagRequest2_HS_CAN_Init(TX_step34_diagRequest2_HS_CAN * pMsg);
int TX_step34_diagRequest2_HS_CAN_Transmit(TX_step34_diagRequest2_HS_CAN * pMsg);
int TX_step34_diagRequest2_HS_CAN_Transmit_raw(TX_step34_diagRequest2_HS_CAN * pMsg);
int TX_step34_diagRequest2_HS_CAN_TransmitFast();
#define TX_step34_diagRequest2_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step34_diagRequest2_HS_CAN_Index, 0)
extern int TX_step35_diagRequest2_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_step35_diagRequest2_HS_CAN;


void TX_step35_diagRequest2_HS_CAN_Init(TX_step35_diagRequest2_HS_CAN * pMsg);
int TX_step35_diagRequest2_HS_CAN_Transmit(TX_step35_diagRequest2_HS_CAN * pMsg);
int TX_step35_diagRequest2_HS_CAN_Transmit_raw(TX_step35_diagRequest2_HS_CAN * pMsg);
int TX_step35_diagRequest2_HS_CAN_TransmitFast();
#define TX_step35_diagRequest2_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step35_diagRequest2_HS_CAN_Index, 0)
extern int TX_step36_diagRequest2_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_step36_diagRequest2_HS_CAN;


void TX_step36_diagRequest2_HS_CAN_Init(TX_step36_diagRequest2_HS_CAN * pMsg);
int TX_step36_diagRequest2_HS_CAN_Transmit(TX_step36_diagRequest2_HS_CAN * pMsg);
int TX_step36_diagRequest2_HS_CAN_Transmit_raw(TX_step36_diagRequest2_HS_CAN * pMsg);
int TX_step36_diagRequest2_HS_CAN_TransmitFast();
#define TX_step36_diagRequest2_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step36_diagRequest2_HS_CAN_Index, 0)
extern int TX_step37_diagRequest2_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_step37_diagRequest2_HS_CAN;


void TX_step37_diagRequest2_HS_CAN_Init(TX_step37_diagRequest2_HS_CAN * pMsg);
int TX_step37_diagRequest2_HS_CAN_Transmit(TX_step37_diagRequest2_HS_CAN * pMsg);
int TX_step37_diagRequest2_HS_CAN_Transmit_raw(TX_step37_diagRequest2_HS_CAN * pMsg);
int TX_step37_diagRequest2_HS_CAN_TransmitFast();
#define TX_step37_diagRequest2_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step37_diagRequest2_HS_CAN_Index, 0)
extern int TX_step38_diagRequest2_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_step38_diagRequest2_HS_CAN;


void TX_step38_diagRequest2_HS_CAN_Init(TX_step38_diagRequest2_HS_CAN * pMsg);
int TX_step38_diagRequest2_HS_CAN_Transmit(TX_step38_diagRequest2_HS_CAN * pMsg);
int TX_step38_diagRequest2_HS_CAN_Transmit_raw(TX_step38_diagRequest2_HS_CAN * pMsg);
int TX_step38_diagRequest2_HS_CAN_TransmitFast();
#define TX_step38_diagRequest2_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step38_diagRequest2_HS_CAN_Index, 0)
extern int TX_step343536_diagRequest2_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_step343536_diagRequest2_HS_CAN;


void TX_step343536_diagRequest2_HS_CAN_Init(TX_step343536_diagRequest2_HS_CAN * pMsg);
int TX_step343536_diagRequest2_HS_CAN_Transmit(TX_step343536_diagRequest2_HS_CAN * pMsg);
int TX_step343536_diagRequest2_HS_CAN_Transmit_raw(TX_step343536_diagRequest2_HS_CAN * pMsg);
int TX_step343536_diagRequest2_HS_CAN_TransmitFast();
#define TX_step343536_diagRequest2_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step343536_diagRequest2_HS_CAN_Index, 0)
extern int TX_mpiWrite_diagRequest_step1_1_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_mpiWrite_diagRequest_step1_1_HS_CAN;


void TX_mpiWrite_diagRequest_step1_1_HS_CAN_Init(TX_mpiWrite_diagRequest_step1_1_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_step1_1_HS_CAN_Transmit(TX_mpiWrite_diagRequest_step1_1_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_step1_1_HS_CAN_Transmit_raw(TX_mpiWrite_diagRequest_step1_1_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_step1_1_HS_CAN_TransmitFast();
#define TX_mpiWrite_diagRequest_step1_1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_mpiWrite_diagRequest_step1_1_HS_CAN_Index, 0)
extern int TX_mpiWrite_diagRequest_step1_2_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_mpiWrite_diagRequest_step1_2_HS_CAN;


void TX_mpiWrite_diagRequest_step1_2_HS_CAN_Init(TX_mpiWrite_diagRequest_step1_2_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_step1_2_HS_CAN_Transmit(TX_mpiWrite_diagRequest_step1_2_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_step1_2_HS_CAN_Transmit_raw(TX_mpiWrite_diagRequest_step1_2_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_step1_2_HS_CAN_TransmitFast();
#define TX_mpiWrite_diagRequest_step1_2_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_mpiWrite_diagRequest_step1_2_HS_CAN_Index, 0)
extern int TX_mpiWrite_diagRequest_step1_3_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_mpiWrite_diagRequest_step1_3_HS_CAN;


void TX_mpiWrite_diagRequest_step1_3_HS_CAN_Init(TX_mpiWrite_diagRequest_step1_3_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_step1_3_HS_CAN_Transmit(TX_mpiWrite_diagRequest_step1_3_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_step1_3_HS_CAN_Transmit_raw(TX_mpiWrite_diagRequest_step1_3_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_step1_3_HS_CAN_TransmitFast();
#define TX_mpiWrite_diagRequest_step1_3_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_mpiWrite_diagRequest_step1_3_HS_CAN_Index, 0)
extern int TX_mpiWrite_diagRequest_step2_1_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_mpiWrite_diagRequest_step2_1_HS_CAN;


void TX_mpiWrite_diagRequest_step2_1_HS_CAN_Init(TX_mpiWrite_diagRequest_step2_1_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_step2_1_HS_CAN_Transmit(TX_mpiWrite_diagRequest_step2_1_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_step2_1_HS_CAN_Transmit_raw(TX_mpiWrite_diagRequest_step2_1_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_step2_1_HS_CAN_TransmitFast();
#define TX_mpiWrite_diagRequest_step2_1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_mpiWrite_diagRequest_step2_1_HS_CAN_Index, 0)
extern int TX_mpiWrite_diagRequest_constructive_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_mpiWrite_diagRequest_constructive_HS_CAN;


void TX_mpiWrite_diagRequest_constructive_HS_CAN_Init(TX_mpiWrite_diagRequest_constructive_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_constructive_HS_CAN_Transmit(TX_mpiWrite_diagRequest_constructive_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_constructive_HS_CAN_Transmit_raw(TX_mpiWrite_diagRequest_constructive_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_constructive_HS_CAN_TransmitFast();
#define TX_mpiWrite_diagRequest_constructive_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_mpiWrite_diagRequest_constructive_HS_CAN_Index, 0)
extern int TX_mpiWrite_diagRequest_step3_1_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_mpiWrite_diagRequest_step3_1_HS_CAN;


void TX_mpiWrite_diagRequest_step3_1_HS_CAN_Init(TX_mpiWrite_diagRequest_step3_1_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_step3_1_HS_CAN_Transmit(TX_mpiWrite_diagRequest_step3_1_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_step3_1_HS_CAN_Transmit_raw(TX_mpiWrite_diagRequest_step3_1_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_step3_1_HS_CAN_TransmitFast();
#define TX_mpiWrite_diagRequest_step3_1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_mpiWrite_diagRequest_step3_1_HS_CAN_Index, 0)
extern int TX_mpiWrite_diagRequest_step4_1_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_mpiWrite_diagRequest_step4_1_HS_CAN;


void TX_mpiWrite_diagRequest_step4_1_HS_CAN_Init(TX_mpiWrite_diagRequest_step4_1_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_step4_1_HS_CAN_Transmit(TX_mpiWrite_diagRequest_step4_1_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_step4_1_HS_CAN_Transmit_raw(TX_mpiWrite_diagRequest_step4_1_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_step4_1_HS_CAN_TransmitFast();
#define TX_mpiWrite_diagRequest_step4_1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_mpiWrite_diagRequest_step4_1_HS_CAN_Index, 0)
extern int TX_mpiWrite_diagRequest_step5_1_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_mpiWrite_diagRequest_step5_1_HS_CAN;


void TX_mpiWrite_diagRequest_step5_1_HS_CAN_Init(TX_mpiWrite_diagRequest_step5_1_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_step5_1_HS_CAN_Transmit(TX_mpiWrite_diagRequest_step5_1_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_step5_1_HS_CAN_Transmit_raw(TX_mpiWrite_diagRequest_step5_1_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_step5_1_HS_CAN_TransmitFast();
#define TX_mpiWrite_diagRequest_step5_1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_mpiWrite_diagRequest_step5_1_HS_CAN_Index, 0)
extern int TX_mpiWrite_diagRequest_step6_1_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_mpiWrite_diagRequest_step6_1_HS_CAN;


void TX_mpiWrite_diagRequest_step6_1_HS_CAN_Init(TX_mpiWrite_diagRequest_step6_1_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_step6_1_HS_CAN_Transmit(TX_mpiWrite_diagRequest_step6_1_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_step6_1_HS_CAN_Transmit_raw(TX_mpiWrite_diagRequest_step6_1_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_step6_1_HS_CAN_TransmitFast();
#define TX_mpiWrite_diagRequest_step6_1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_mpiWrite_diagRequest_step6_1_HS_CAN_Index, 0)
extern int TX_mpiWrite_diagRequest_step6_2_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_mpiWrite_diagRequest_step6_2_HS_CAN;


void TX_mpiWrite_diagRequest_step6_2_HS_CAN_Init(TX_mpiWrite_diagRequest_step6_2_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_step6_2_HS_CAN_Transmit(TX_mpiWrite_diagRequest_step6_2_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_step6_2_HS_CAN_Transmit_raw(TX_mpiWrite_diagRequest_step6_2_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_step6_2_HS_CAN_TransmitFast();
#define TX_mpiWrite_diagRequest_step6_2_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_mpiWrite_diagRequest_step6_2_HS_CAN_Index, 0)
extern int TX_mpiWrite_diagRequest_step6_3_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_mpiWrite_diagRequest_step6_3_HS_CAN;


void TX_mpiWrite_diagRequest_step6_3_HS_CAN_Init(TX_mpiWrite_diagRequest_step6_3_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_step6_3_HS_CAN_Transmit(TX_mpiWrite_diagRequest_step6_3_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_step6_3_HS_CAN_Transmit_raw(TX_mpiWrite_diagRequest_step6_3_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_step6_3_HS_CAN_TransmitFast();
#define TX_mpiWrite_diagRequest_step6_3_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_mpiWrite_diagRequest_step6_3_HS_CAN_Index, 0)
extern int TX_mpiWrite_diagRequest_step6_4_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_mpiWrite_diagRequest_step6_4_HS_CAN;


void TX_mpiWrite_diagRequest_step6_4_HS_CAN_Init(TX_mpiWrite_diagRequest_step6_4_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_step6_4_HS_CAN_Transmit(TX_mpiWrite_diagRequest_step6_4_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_step6_4_HS_CAN_Transmit_raw(TX_mpiWrite_diagRequest_step6_4_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_step6_4_HS_CAN_TransmitFast();
#define TX_mpiWrite_diagRequest_step6_4_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_mpiWrite_diagRequest_step6_4_HS_CAN_Index, 0)
extern int TX_mpiWrite_diagRequest_step7_1_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_mpiWrite_diagRequest_step7_1_HS_CAN;


void TX_mpiWrite_diagRequest_step7_1_HS_CAN_Init(TX_mpiWrite_diagRequest_step7_1_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_step7_1_HS_CAN_Transmit(TX_mpiWrite_diagRequest_step7_1_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_step7_1_HS_CAN_Transmit_raw(TX_mpiWrite_diagRequest_step7_1_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_step7_1_HS_CAN_TransmitFast();
#define TX_mpiWrite_diagRequest_step7_1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_mpiWrite_diagRequest_step7_1_HS_CAN_Index, 0)
extern int TX_mpiWrite_diagRequest_step8_1_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_mpiWrite_diagRequest_step8_1_HS_CAN;


void TX_mpiWrite_diagRequest_step8_1_HS_CAN_Init(TX_mpiWrite_diagRequest_step8_1_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_step8_1_HS_CAN_Transmit(TX_mpiWrite_diagRequest_step8_1_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_step8_1_HS_CAN_Transmit_raw(TX_mpiWrite_diagRequest_step8_1_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_step8_1_HS_CAN_TransmitFast();
#define TX_mpiWrite_diagRequest_step8_1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_mpiWrite_diagRequest_step8_1_HS_CAN_Index, 0)
extern int TX_mpiRead_diagRequest_step1_1_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_mpiRead_diagRequest_step1_1_HS_CAN;


void TX_mpiRead_diagRequest_step1_1_HS_CAN_Init(TX_mpiRead_diagRequest_step1_1_HS_CAN * pMsg);
int TX_mpiRead_diagRequest_step1_1_HS_CAN_Transmit(TX_mpiRead_diagRequest_step1_1_HS_CAN * pMsg);
int TX_mpiRead_diagRequest_step1_1_HS_CAN_Transmit_raw(TX_mpiRead_diagRequest_step1_1_HS_CAN * pMsg);
int TX_mpiRead_diagRequest_step1_1_HS_CAN_TransmitFast();
#define TX_mpiRead_diagRequest_step1_1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_mpiRead_diagRequest_step1_1_HS_CAN_Index, 0)
extern int TX_mpiRead_diagRequest_step2_1_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_mpiRead_diagRequest_step2_1_HS_CAN;


void TX_mpiRead_diagRequest_step2_1_HS_CAN_Init(TX_mpiRead_diagRequest_step2_1_HS_CAN * pMsg);
int TX_mpiRead_diagRequest_step2_1_HS_CAN_Transmit(TX_mpiRead_diagRequest_step2_1_HS_CAN * pMsg);
int TX_mpiRead_diagRequest_step2_1_HS_CAN_Transmit_raw(TX_mpiRead_diagRequest_step2_1_HS_CAN * pMsg);
int TX_mpiRead_diagRequest_step2_1_HS_CAN_TransmitFast();
#define TX_mpiRead_diagRequest_step2_1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_mpiRead_diagRequest_step2_1_HS_CAN_Index, 0)
extern int TX_mpiRead_diagRequest_flowControl_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_mpiRead_diagRequest_flowControl_HS_CAN;


void TX_mpiRead_diagRequest_flowControl_HS_CAN_Init(TX_mpiRead_diagRequest_flowControl_HS_CAN * pMsg);
int TX_mpiRead_diagRequest_flowControl_HS_CAN_Transmit(TX_mpiRead_diagRequest_flowControl_HS_CAN * pMsg);
int TX_mpiRead_diagRequest_flowControl_HS_CAN_Transmit_raw(TX_mpiRead_diagRequest_flowControl_HS_CAN * pMsg);
int TX_mpiRead_diagRequest_flowControl_HS_CAN_TransmitFast();
#define TX_mpiRead_diagRequest_flowControl_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_mpiRead_diagRequest_flowControl_HS_CAN_Index, 0)
extern int TX_mpiRead_diagRequest_step3_1_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_mpiRead_diagRequest_step3_1_HS_CAN;


void TX_mpiRead_diagRequest_step3_1_HS_CAN_Init(TX_mpiRead_diagRequest_step3_1_HS_CAN * pMsg);
int TX_mpiRead_diagRequest_step3_1_HS_CAN_Transmit(TX_mpiRead_diagRequest_step3_1_HS_CAN * pMsg);
int TX_mpiRead_diagRequest_step3_1_HS_CAN_Transmit_raw(TX_mpiRead_diagRequest_step3_1_HS_CAN * pMsg);
int TX_mpiRead_diagRequest_step3_1_HS_CAN_TransmitFast();
#define TX_mpiRead_diagRequest_step3_1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_mpiRead_diagRequest_step3_1_HS_CAN_Index, 0)
extern int TX_mpiRead_diagRequest_step4_1_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_mpiRead_diagRequest_step4_1_HS_CAN;


void TX_mpiRead_diagRequest_step4_1_HS_CAN_Init(TX_mpiRead_diagRequest_step4_1_HS_CAN * pMsg);
int TX_mpiRead_diagRequest_step4_1_HS_CAN_Transmit(TX_mpiRead_diagRequest_step4_1_HS_CAN * pMsg);
int TX_mpiRead_diagRequest_step4_1_HS_CAN_Transmit_raw(TX_mpiRead_diagRequest_step4_1_HS_CAN * pMsg);
int TX_mpiRead_diagRequest_step4_1_HS_CAN_TransmitFast();
#define TX_mpiRead_diagRequest_step4_1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_mpiRead_diagRequest_step4_1_HS_CAN_Index, 0)
extern int TX_mpiRead_diagRequest_step5_1_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_mpiRead_diagRequest_step5_1_HS_CAN;


void TX_mpiRead_diagRequest_step5_1_HS_CAN_Init(TX_mpiRead_diagRequest_step5_1_HS_CAN * pMsg);
int TX_mpiRead_diagRequest_step5_1_HS_CAN_Transmit(TX_mpiRead_diagRequest_step5_1_HS_CAN * pMsg);
int TX_mpiRead_diagRequest_step5_1_HS_CAN_Transmit_raw(TX_mpiRead_diagRequest_step5_1_HS_CAN * pMsg);
int TX_mpiRead_diagRequest_step5_1_HS_CAN_TransmitFast();
#define TX_mpiRead_diagRequest_step5_1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_mpiRead_diagRequest_step5_1_HS_CAN_Index, 0)
extern int TX_mpiRead_diagRequest_step6_1_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_mpiRead_diagRequest_step6_1_HS_CAN;


void TX_mpiRead_diagRequest_step6_1_HS_CAN_Init(TX_mpiRead_diagRequest_step6_1_HS_CAN * pMsg);
int TX_mpiRead_diagRequest_step6_1_HS_CAN_Transmit(TX_mpiRead_diagRequest_step6_1_HS_CAN * pMsg);
int TX_mpiRead_diagRequest_step6_1_HS_CAN_Transmit_raw(TX_mpiRead_diagRequest_step6_1_HS_CAN * pMsg);
int TX_mpiRead_diagRequest_step6_1_HS_CAN_TransmitFast();
#define TX_mpiRead_diagRequest_step6_1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_mpiRead_diagRequest_step6_1_HS_CAN_Index, 0)
extern int TX_mpiRead_diagRequest_step7_1_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_mpiRead_diagRequest_step7_1_HS_CAN;


void TX_mpiRead_diagRequest_step7_1_HS_CAN_Init(TX_mpiRead_diagRequest_step7_1_HS_CAN * pMsg);
int TX_mpiRead_diagRequest_step7_1_HS_CAN_Transmit(TX_mpiRead_diagRequest_step7_1_HS_CAN * pMsg);
int TX_mpiRead_diagRequest_step7_1_HS_CAN_Transmit_raw(TX_mpiRead_diagRequest_step7_1_HS_CAN * pMsg);
int TX_mpiRead_diagRequest_step7_1_HS_CAN_TransmitFast();
#define TX_mpiRead_diagRequest_step7_1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_mpiRead_diagRequest_step7_1_HS_CAN_Index, 0)
extern int TX_mpiRead_diagRequest_step8_1_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_mpiRead_diagRequest_step8_1_HS_CAN;


void TX_mpiRead_diagRequest_step8_1_HS_CAN_Init(TX_mpiRead_diagRequest_step8_1_HS_CAN * pMsg);
int TX_mpiRead_diagRequest_step8_1_HS_CAN_Transmit(TX_mpiRead_diagRequest_step8_1_HS_CAN * pMsg);
int TX_mpiRead_diagRequest_step8_1_HS_CAN_Transmit_raw(TX_mpiRead_diagRequest_step8_1_HS_CAN * pMsg);
int TX_mpiRead_diagRequest_step8_1_HS_CAN_TransmitFast();
#define TX_mpiRead_diagRequest_step8_1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_mpiRead_diagRequest_step8_1_HS_CAN_Index, 0)
extern int TX_mpiRead_diagRequest_step9_1_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_mpiRead_diagRequest_step9_1_HS_CAN;


void TX_mpiRead_diagRequest_step9_1_HS_CAN_Init(TX_mpiRead_diagRequest_step9_1_HS_CAN * pMsg);
int TX_mpiRead_diagRequest_step9_1_HS_CAN_Transmit(TX_mpiRead_diagRequest_step9_1_HS_CAN * pMsg);
int TX_mpiRead_diagRequest_step9_1_HS_CAN_Transmit_raw(TX_mpiRead_diagRequest_step9_1_HS_CAN * pMsg);
int TX_mpiRead_diagRequest_step9_1_HS_CAN_TransmitFast();
#define TX_mpiRead_diagRequest_step9_1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_mpiRead_diagRequest_step9_1_HS_CAN_Index, 0)
extern int TX_mpiWrite_diagRequest_stepX_1_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_mpiWrite_diagRequest_stepX_1_HS_CAN;


void TX_mpiWrite_diagRequest_stepX_1_HS_CAN_Init(TX_mpiWrite_diagRequest_stepX_1_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_stepX_1_HS_CAN_Transmit(TX_mpiWrite_diagRequest_stepX_1_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_stepX_1_HS_CAN_Transmit_raw(TX_mpiWrite_diagRequest_stepX_1_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_stepX_1_HS_CAN_TransmitFast();
#define TX_mpiWrite_diagRequest_stepX_1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_mpiWrite_diagRequest_stepX_1_HS_CAN_Index, 0)
extern int TX_TestPresentMessage_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_TestPresentMessage_HS_CAN;


void TX_TestPresentMessage_HS_CAN_Init(TX_TestPresentMessage_HS_CAN * pMsg);
int TX_TestPresentMessage_HS_CAN_Transmit(TX_TestPresentMessage_HS_CAN * pMsg);
int TX_TestPresentMessage_HS_CAN_Transmit_raw(TX_TestPresentMessage_HS_CAN * pMsg);
int TX_TestPresentMessage_HS_CAN_TransmitFast();
#define TX_TestPresentMessage_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_TestPresentMessage_HS_CAN_Index, 0)
extern int TX_mpiWrite_diagRequest_stepModel_1_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_mpiWrite_diagRequest_stepModel_1_HS_CAN;


void TX_mpiWrite_diagRequest_stepModel_1_HS_CAN_Init(TX_mpiWrite_diagRequest_stepModel_1_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_stepModel_1_HS_CAN_Transmit(TX_mpiWrite_diagRequest_stepModel_1_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_stepModel_1_HS_CAN_Transmit_raw(TX_mpiWrite_diagRequest_stepModel_1_HS_CAN * pMsg);
int TX_mpiWrite_diagRequest_stepModel_1_HS_CAN_TransmitFast();
#define TX_mpiWrite_diagRequest_stepModel_1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_mpiWrite_diagRequest_stepModel_1_HS_CAN_Index, 0)
extern int TX_step7_1_message_1_122_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_step7_1_message_1_122_HS_CAN;


void TX_step7_1_message_1_122_HS_CAN_Init(TX_step7_1_message_1_122_HS_CAN * pMsg);
int TX_step7_1_message_1_122_HS_CAN_Transmit(TX_step7_1_message_1_122_HS_CAN * pMsg);
int TX_step7_1_message_1_122_HS_CAN_Transmit_raw(TX_step7_1_message_1_122_HS_CAN * pMsg);
int TX_step7_1_message_1_122_HS_CAN_TransmitFast();
#define TX_step7_1_message_1_122_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step7_1_message_1_122_HS_CAN_Index, 0)
extern int TX_step7_1_message_2_4c1_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_step7_1_message_2_4c1_HS_CAN;


void TX_step7_1_message_2_4c1_HS_CAN_Init(TX_step7_1_message_2_4c1_HS_CAN * pMsg);
int TX_step7_1_message_2_4c1_HS_CAN_Transmit(TX_step7_1_message_2_4c1_HS_CAN * pMsg);
int TX_step7_1_message_2_4c1_HS_CAN_Transmit_raw(TX_step7_1_message_2_4c1_HS_CAN * pMsg);
int TX_step7_1_message_2_4c1_HS_CAN_TransmitFast();
#define TX_step7_1_message_2_4c1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step7_1_message_2_4c1_HS_CAN_Index, 0)
extern int TX_step7_1_message_3_190_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_step7_1_message_3_190_HS_CAN;


void TX_step7_1_message_3_190_HS_CAN_Init(TX_step7_1_message_3_190_HS_CAN * pMsg);
int TX_step7_1_message_3_190_HS_CAN_Transmit(TX_step7_1_message_3_190_HS_CAN * pMsg);
int TX_step7_1_message_3_190_HS_CAN_Transmit_raw(TX_step7_1_message_3_190_HS_CAN * pMsg);
int TX_step7_1_message_3_190_HS_CAN_TransmitFast();
#define TX_step7_1_message_3_190_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step7_1_message_3_190_HS_CAN_Index, 0)
extern int TX_step7_1_message_4_371_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_step7_1_message_4_371_HS_CAN;


void TX_step7_1_message_4_371_HS_CAN_Init(TX_step7_1_message_4_371_HS_CAN * pMsg);
int TX_step7_1_message_4_371_HS_CAN_Transmit(TX_step7_1_message_4_371_HS_CAN * pMsg);
int TX_step7_1_message_4_371_HS_CAN_Transmit_raw(TX_step7_1_message_4_371_HS_CAN * pMsg);
int TX_step7_1_message_4_371_HS_CAN_TransmitFast();
#define TX_step7_1_message_4_371_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step7_1_message_4_371_HS_CAN_Index, 0)
extern int TX_step7_1_message_5_3c5_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_step7_1_message_5_3c5_HS_CAN;


void TX_step7_1_message_5_3c5_HS_CAN_Init(TX_step7_1_message_5_3c5_HS_CAN * pMsg);
int TX_step7_1_message_5_3c5_HS_CAN_Transmit(TX_step7_1_message_5_3c5_HS_CAN * pMsg);
int TX_step7_1_message_5_3c5_HS_CAN_Transmit_raw(TX_step7_1_message_5_3c5_HS_CAN * pMsg);
int TX_step7_1_message_5_3c5_HS_CAN_TransmitFast();
#define TX_step7_1_message_5_3c5_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step7_1_message_5_3c5_HS_CAN_Index, 0)
extern int TX_step39_diagRequest2_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_step39_diagRequest2_HS_CAN;


void TX_step39_diagRequest2_HS_CAN_Init(TX_step39_diagRequest2_HS_CAN * pMsg);
int TX_step39_diagRequest2_HS_CAN_Transmit(TX_step39_diagRequest2_HS_CAN * pMsg);
int TX_step39_diagRequest2_HS_CAN_Transmit_raw(TX_step39_diagRequest2_HS_CAN * pMsg);
int TX_step39_diagRequest2_HS_CAN_TransmitFast();
#define TX_step39_diagRequest2_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step39_diagRequest2_HS_CAN_Index, 0)
extern int TX_step40_diagRequest2_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_step40_diagRequest2_HS_CAN;


void TX_step40_diagRequest2_HS_CAN_Init(TX_step40_diagRequest2_HS_CAN * pMsg);
int TX_step40_diagRequest2_HS_CAN_Transmit(TX_step40_diagRequest2_HS_CAN * pMsg);
int TX_step40_diagRequest2_HS_CAN_Transmit_raw(TX_step40_diagRequest2_HS_CAN * pMsg);
int TX_step40_diagRequest2_HS_CAN_TransmitFast();
#define TX_step40_diagRequest2_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step40_diagRequest2_HS_CAN_Index, 0)
extern int TX_step41_diagRequest2_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_step41_diagRequest2_HS_CAN;


void TX_step41_diagRequest2_HS_CAN_Init(TX_step41_diagRequest2_HS_CAN * pMsg);
int TX_step41_diagRequest2_HS_CAN_Transmit(TX_step41_diagRequest2_HS_CAN * pMsg);
int TX_step41_diagRequest2_HS_CAN_Transmit_raw(TX_step41_diagRequest2_HS_CAN * pMsg);
int TX_step41_diagRequest2_HS_CAN_TransmitFast();
#define TX_step41_diagRequest2_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_step41_diagRequest2_HS_CAN_Index, 0)
extern int TX_sapaWrite_diagRequest_step1_1_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_sapaWrite_diagRequest_step1_1_HS_CAN;


void TX_sapaWrite_diagRequest_step1_1_HS_CAN_Init(TX_sapaWrite_diagRequest_step1_1_HS_CAN * pMsg);
int TX_sapaWrite_diagRequest_step1_1_HS_CAN_Transmit(TX_sapaWrite_diagRequest_step1_1_HS_CAN * pMsg);
int TX_sapaWrite_diagRequest_step1_1_HS_CAN_Transmit_raw(TX_sapaWrite_diagRequest_step1_1_HS_CAN * pMsg);
int TX_sapaWrite_diagRequest_step1_1_HS_CAN_TransmitFast();
#define TX_sapaWrite_diagRequest_step1_1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_sapaWrite_diagRequest_step1_1_HS_CAN_Index, 0)
extern int TX_sapaWrite_diagRequest_step2_1_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_sapaWrite_diagRequest_step2_1_HS_CAN;


void TX_sapaWrite_diagRequest_step2_1_HS_CAN_Init(TX_sapaWrite_diagRequest_step2_1_HS_CAN * pMsg);
int TX_sapaWrite_diagRequest_step2_1_HS_CAN_Transmit(TX_sapaWrite_diagRequest_step2_1_HS_CAN * pMsg);
int TX_sapaWrite_diagRequest_step2_1_HS_CAN_Transmit_raw(TX_sapaWrite_diagRequest_step2_1_HS_CAN * pMsg);
int TX_sapaWrite_diagRequest_step2_1_HS_CAN_TransmitFast();
#define TX_sapaWrite_diagRequest_step2_1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_sapaWrite_diagRequest_step2_1_HS_CAN_Index, 0)
extern int TX_sapaWrite_diagRequest_constructive_1_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_sapaWrite_diagRequest_constructive_1_HS_CAN;


void TX_sapaWrite_diagRequest_constructive_1_HS_CAN_Init(TX_sapaWrite_diagRequest_constructive_1_HS_CAN * pMsg);
int TX_sapaWrite_diagRequest_constructive_1_HS_CAN_Transmit(TX_sapaWrite_diagRequest_constructive_1_HS_CAN * pMsg);
int TX_sapaWrite_diagRequest_constructive_1_HS_CAN_Transmit_raw(TX_sapaWrite_diagRequest_constructive_1_HS_CAN * pMsg);
int TX_sapaWrite_diagRequest_constructive_1_HS_CAN_TransmitFast();
#define TX_sapaWrite_diagRequest_constructive_1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_sapaWrite_diagRequest_constructive_1_HS_CAN_Index, 0)
extern int TX_sapaWrite_diagRequest_constructive_2_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_sapaWrite_diagRequest_constructive_2_HS_CAN;


void TX_sapaWrite_diagRequest_constructive_2_HS_CAN_Init(TX_sapaWrite_diagRequest_constructive_2_HS_CAN * pMsg);
int TX_sapaWrite_diagRequest_constructive_2_HS_CAN_Transmit(TX_sapaWrite_diagRequest_constructive_2_HS_CAN * pMsg);
int TX_sapaWrite_diagRequest_constructive_2_HS_CAN_Transmit_raw(TX_sapaWrite_diagRequest_constructive_2_HS_CAN * pMsg);
int TX_sapaWrite_diagRequest_constructive_2_HS_CAN_TransmitFast();
#define TX_sapaWrite_diagRequest_constructive_2_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_sapaWrite_diagRequest_constructive_2_HS_CAN_Index, 0)
extern int TX_sapaWrite_diagRequest_constructive_3_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_sapaWrite_diagRequest_constructive_3_HS_CAN;


void TX_sapaWrite_diagRequest_constructive_3_HS_CAN_Init(TX_sapaWrite_diagRequest_constructive_3_HS_CAN * pMsg);
int TX_sapaWrite_diagRequest_constructive_3_HS_CAN_Transmit(TX_sapaWrite_diagRequest_constructive_3_HS_CAN * pMsg);
int TX_sapaWrite_diagRequest_constructive_3_HS_CAN_Transmit_raw(TX_sapaWrite_diagRequest_constructive_3_HS_CAN * pMsg);
int TX_sapaWrite_diagRequest_constructive_3_HS_CAN_TransmitFast();
#define TX_sapaWrite_diagRequest_constructive_3_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_sapaWrite_diagRequest_constructive_3_HS_CAN_Index, 0)
extern int TX_sapaRead_diagRequest_step1_1_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_sapaRead_diagRequest_step1_1_HS_CAN;


void TX_sapaRead_diagRequest_step1_1_HS_CAN_Init(TX_sapaRead_diagRequest_step1_1_HS_CAN * pMsg);
int TX_sapaRead_diagRequest_step1_1_HS_CAN_Transmit(TX_sapaRead_diagRequest_step1_1_HS_CAN * pMsg);
int TX_sapaRead_diagRequest_step1_1_HS_CAN_Transmit_raw(TX_sapaRead_diagRequest_step1_1_HS_CAN * pMsg);
int TX_sapaRead_diagRequest_step1_1_HS_CAN_TransmitFast();
#define TX_sapaRead_diagRequest_step1_1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_sapaRead_diagRequest_step1_1_HS_CAN_Index, 0)
extern int TX_sapaRead_diagRequest_step2_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} TX_sapaRead_diagRequest_step2_HS_CAN;


void TX_sapaRead_diagRequest_step2_HS_CAN_Init(TX_sapaRead_diagRequest_step2_HS_CAN * pMsg);
int TX_sapaRead_diagRequest_step2_HS_CAN_Transmit(TX_sapaRead_diagRequest_step2_HS_CAN * pMsg);
int TX_sapaRead_diagRequest_step2_HS_CAN_Transmit_raw(TX_sapaRead_diagRequest_step2_HS_CAN * pMsg);
int TX_sapaRead_diagRequest_step2_HS_CAN_TransmitFast();
#define TX_sapaRead_diagRequest_step2_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_sapaRead_diagRequest_step2_HS_CAN_Index, 0)
extern int MG_step8_14_Climate_Control_General_Status_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double ACCmpsrFldOn; /// Min: 0 Max: 1 Units: 
    BYTE ACCmpsrFldOn_raw;
    double ACCompModReq; /// Min: 0 Max: 3 Units: 
    BYTE ACCompModReq_raw;
    double ACCompNormLd; /// Min: 0 Max: 25.5 Units: l/min
    BYTE ACCompNormLd_raw;
    double ACCompNormLdV; /// Min: 0 Max: 1 Units: 
    BYTE ACCompNormLdV_raw;
    double ACCmEngRunReq; /// Min: 0 Max: 1 Units: 
    BYTE ACCmEngRunReq_raw;
    double ClmtCtrlTrgtTemp; /// Min: -10 Max: 92.3 Units: degC
    WORD ClmtCtrlTrgtTemp_raw;
} MG_step8_14_Climate_Control_General_Status_HS_CAN;

#pragma warning(disable : 4005)
#define MG_step8_14_Climate_Control_General_Status_HS_CAN_$_ACCmpsrFldOn_$$_False 0
#define MG_step8_14_Climate_Control_General_Status_HS_CAN_$_ACCmpsrFldOn_$$_True 1
#define MG_step8_14_Climate_Control_General_Status_HS_CAN_$_ACCompModReq_$$_Disengage_Immediately 0
#define MG_step8_14_Climate_Control_General_Status_HS_CAN_$_ACCompModReq_$$_Disengage 1
#define MG_step8_14_Climate_Control_General_Status_HS_CAN_$_ACCompModReq_$$_Engage 2
#define MG_step8_14_Climate_Control_General_Status_HS_CAN_$_ACCompModReq_$$_No_Action 3
#define MG_step8_14_Climate_Control_General_Status_HS_CAN_$_ACCompNormLdV_$$_Valid 0
#define MG_step8_14_Climate_Control_General_Status_HS_CAN_$_ACCompNormLdV_$$_Invalid 1
#define MG_step8_14_Climate_Control_General_Status_HS_CAN_$_ACCmEngRunReq_$$_No_Action 0
#define MG_step8_14_Climate_Control_General_Status_HS_CAN_$_ACCmEngRunReq_$$_Engine_Run_Requested 1
#pragma warning(default : 4005)

void MG_step8_14_Climate_Control_General_Status_HS_CAN_Init(MG_step8_14_Climate_Control_General_Status_HS_CAN * pMsg);
int MG_step8_14_Climate_Control_General_Status_HS_CAN_Transmit(MG_step8_14_Climate_Control_General_Status_HS_CAN * pMsg);
int MG_step8_14_Climate_Control_General_Status_HS_CAN_Transmit_raw(MG_step8_14_Climate_Control_General_Status_HS_CAN * pMsg);
int MG_step8_14_Climate_Control_General_Status_HS_CAN_UpdateBytesFromSignals(MG_step8_14_Climate_Control_General_Status_HS_CAN * pMsg);
int MG_step8_14_Climate_Control_General_Status_HS_CAN_UpdateBytesFromRawSignals(MG_step8_14_Climate_Control_General_Status_HS_CAN * pMsg);
#define MG_step8_14_Climate_Control_General_Status_HS_CAN_ACCmpsrFldOn_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 1, MG_step8_14_Climate_Control_General_Status_HS_CAN_Index, 0, dPhysicalValue);
#define MG_step8_14_Climate_Control_General_Status_HS_CAN_ACCompModReq_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 1, MG_step8_14_Climate_Control_General_Status_HS_CAN_Index, 1, dPhysicalValue);
#define MG_step8_14_Climate_Control_General_Status_HS_CAN_ACCompNormLd_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 1, MG_step8_14_Climate_Control_General_Status_HS_CAN_Index, 2, dPhysicalValue);
#define MG_step8_14_Climate_Control_General_Status_HS_CAN_ACCompNormLdV_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 1, MG_step8_14_Climate_Control_General_Status_HS_CAN_Index, 3, dPhysicalValue);
#define MG_step8_14_Climate_Control_General_Status_HS_CAN_ACCmEngRunReq_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 1, MG_step8_14_Climate_Control_General_Status_HS_CAN_Index, 4, dPhysicalValue);
#define MG_step8_14_Climate_Control_General_Status_HS_CAN_ClmtCtrlTrgtTemp_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 1, MG_step8_14_Climate_Control_General_Status_HS_CAN_Index, 5, dPhysicalValue);
#define MG_step8_14_Climate_Control_General_Status_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, MG_step8_14_Climate_Control_General_Status_HS_CAN_Index, 0)
extern int MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double DrvHCSeatSw1Act; /// Min: 0 Max: 1 Units: 
    BYTE DrvHCSeatSw1Act_raw;
    double DrvHCSeatSw2Act; /// Min: 0 Max: 1 Units: 
    BYTE DrvHCSeatSw2Act_raw;
    double DrvHCSeatSw3Act; /// Min: 0 Max: 1 Units: 
    BYTE DrvHCSeatSw3Act_raw;
    double PassHCSeatSw1Act; /// Min: 0 Max: 1 Units: 
    BYTE PassHCSeatSw1Act_raw;
    double PassHCSeatSw2Act; /// Min: 0 Max: 1 Units: 
    BYTE PassHCSeatSw2Act_raw;
    double PassHCSeatSw3Act; /// Min: 0 Max: 1 Units: 
    BYTE PassHCSeatSw3Act_raw;
} MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN;

#pragma warning(disable : 4005)
#define MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_$_DrvHCSeatSw1Act_$$_False 0
#define MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_$_DrvHCSeatSw1Act_$$_True 1
#define MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_$_DrvHCSeatSw2Act_$$_False 0
#define MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_$_DrvHCSeatSw2Act_$$_True 1
#define MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_$_DrvHCSeatSw3Act_$$_False 0
#define MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_$_DrvHCSeatSw3Act_$$_True 1
#define MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_$_PassHCSeatSw1Act_$$_False 0
#define MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_$_PassHCSeatSw1Act_$$_True 1
#define MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_$_PassHCSeatSw2Act_$$_False 0
#define MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_$_PassHCSeatSw2Act_$$_True 1
#define MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_$_PassHCSeatSw3Act_$$_False 0
#define MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_$_PassHCSeatSw3Act_$$_True 1
#pragma warning(default : 4005)

void MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_Init(MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN * pMsg);
int MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_Transmit(MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN * pMsg);
int MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_Transmit_raw(MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN * pMsg);
int MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_UpdateBytesFromSignals(MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN * pMsg);
int MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_UpdateBytesFromRawSignals(MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN * pMsg);
#define MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_DrvHCSeatSw1Act_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 1, MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_Index, 0, dPhysicalValue);
#define MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_DrvHCSeatSw2Act_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 1, MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_Index, 1, dPhysicalValue);
#define MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_DrvHCSeatSw3Act_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 1, MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_Index, 2, dPhysicalValue);
#define MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_PassHCSeatSw1Act_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 1, MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_Index, 3, dPhysicalValue);
#define MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_PassHCSeatSw2Act_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 1, MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_Index, 4, dPhysicalValue);
#define MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_PassHCSeatSw3Act_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 1, MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_Index, 5, dPhysicalValue);
#define MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, MG_step11_Front_Seat_Heat_Cool_Switches_HS_CAN_Index, 0)
extern int MG_step12_Auxiliary_Heater_Status_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double AuxHtrAtv; /// Min: 0 Max: 1 Units: 
    BYTE AuxHtrAtv_raw;
    double CCClntCrcFlwRtReq; /// Min: 0 Max: 100.000035 Units: %
    BYTE CCClntCrcFlwRtReq_raw;
    double HtrCoreInltClntTmpCalc; /// Min: -40 Max: 215 Units: degC
    BYTE HtrCoreInltClntTmpCalc_raw;
    double HtrCoreInltClntTmpCalcV; /// Min: 0 Max: 1 Units: 
    BYTE HtrCoreInltClntTmpCalcV_raw;
} MG_step12_Auxiliary_Heater_Status_HS_CAN;

#pragma warning(disable : 4005)
#define MG_step12_Auxiliary_Heater_Status_HS_CAN_$_AuxHtrAtv_$$_False 0
#define MG_step12_Auxiliary_Heater_Status_HS_CAN_$_AuxHtrAtv_$$_True 1
#define MG_step12_Auxiliary_Heater_Status_HS_CAN_$_HtrCoreInltClntTmpCalcV_$$_Valid 0
#define MG_step12_Auxiliary_Heater_Status_HS_CAN_$_HtrCoreInltClntTmpCalcV_$$_Invalid 1
#pragma warning(default : 4005)

void MG_step12_Auxiliary_Heater_Status_HS_CAN_Init(MG_step12_Auxiliary_Heater_Status_HS_CAN * pMsg);
int MG_step12_Auxiliary_Heater_Status_HS_CAN_Transmit(MG_step12_Auxiliary_Heater_Status_HS_CAN * pMsg);
int MG_step12_Auxiliary_Heater_Status_HS_CAN_Transmit_raw(MG_step12_Auxiliary_Heater_Status_HS_CAN * pMsg);
int MG_step12_Auxiliary_Heater_Status_HS_CAN_UpdateBytesFromSignals(MG_step12_Auxiliary_Heater_Status_HS_CAN * pMsg);
int MG_step12_Auxiliary_Heater_Status_HS_CAN_UpdateBytesFromRawSignals(MG_step12_Auxiliary_Heater_Status_HS_CAN * pMsg);
#define MG_step12_Auxiliary_Heater_Status_HS_CAN_AuxHtrAtv_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 1, MG_step12_Auxiliary_Heater_Status_HS_CAN_Index, 0, dPhysicalValue);
#define MG_step12_Auxiliary_Heater_Status_HS_CAN_CCClntCrcFlwRtReq_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 1, MG_step12_Auxiliary_Heater_Status_HS_CAN_Index, 1, dPhysicalValue);
#define MG_step12_Auxiliary_Heater_Status_HS_CAN_HtrCoreInltClntTmpCalc_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 1, MG_step12_Auxiliary_Heater_Status_HS_CAN_Index, 2, dPhysicalValue);
#define MG_step12_Auxiliary_Heater_Status_HS_CAN_HtrCoreInltClntTmpCalcV_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 1, MG_step12_Auxiliary_Heater_Status_HS_CAN_Index, 3, dPhysicalValue);
#define MG_step12_Auxiliary_Heater_Status_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, MG_step12_Auxiliary_Heater_Status_HS_CAN_Index, 0)
extern int MG_step10_PCRM006_LIN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} MG_step10_PCRM006_LIN;


void MG_step10_PCRM006_LIN_Init(MG_step10_PCRM006_LIN * pMsg);
int MG_step10_PCRM006_LIN_Transmit(MG_step10_PCRM006_LIN * pMsg);
int MG_step10_PCRM006_LIN_Transmit_raw(MG_step10_PCRM006_LIN * pMsg);
#define MG_step10_PCRM006_LIN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, MG_step10_PCRM006_LIN_Index, 0)
extern int MG_stepX_diagResponse_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} MG_stepX_diagResponse_HS_CAN;


void MG_stepX_diagResponse_HS_CAN_Init(MG_stepX_diagResponse_HS_CAN * pMsg);
int MG_stepX_diagResponse_HS_CAN_Transmit(MG_stepX_diagResponse_HS_CAN * pMsg);
int MG_stepX_diagResponse_HS_CAN_Transmit_raw(MG_stepX_diagResponse_HS_CAN * pMsg);
#define MG_stepX_diagResponse_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, MG_stepX_diagResponse_HS_CAN_Index, 0)
extern int MG_C_diag_response1Data_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} MG_C_diag_response1Data_HS_CAN;


void MG_C_diag_response1Data_HS_CAN_Init(MG_C_diag_response1Data_HS_CAN * pMsg);
int MG_C_diag_response1Data_HS_CAN_Transmit(MG_C_diag_response1Data_HS_CAN * pMsg);
int MG_C_diag_response1Data_HS_CAN_Transmit_raw(MG_C_diag_response1Data_HS_CAN * pMsg);
#define MG_C_diag_response1Data_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, MG_C_diag_response1Data_HS_CAN_Index, 0)
extern int MG_step13_Rear_Window_Defog_Status_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double RrWndDfgOn; /// Min: 0 Max: 1 Units: 
    BYTE RrWndDfgOn_raw;
} MG_step13_Rear_Window_Defog_Status_HS_CAN;

#pragma warning(disable : 4005)
#define MG_step13_Rear_Window_Defog_Status_HS_CAN_$_RrWndDfgOn_$$_False 0
#define MG_step13_Rear_Window_Defog_Status_HS_CAN_$_RrWndDfgOn_$$_True 1
#pragma warning(default : 4005)

void MG_step13_Rear_Window_Defog_Status_HS_CAN_Init(MG_step13_Rear_Window_Defog_Status_HS_CAN * pMsg);
int MG_step13_Rear_Window_Defog_Status_HS_CAN_Transmit(MG_step13_Rear_Window_Defog_Status_HS_CAN * pMsg);
int MG_step13_Rear_Window_Defog_Status_HS_CAN_Transmit_raw(MG_step13_Rear_Window_Defog_Status_HS_CAN * pMsg);
int MG_step13_Rear_Window_Defog_Status_HS_CAN_UpdateBytesFromSignals(MG_step13_Rear_Window_Defog_Status_HS_CAN * pMsg);
int MG_step13_Rear_Window_Defog_Status_HS_CAN_UpdateBytesFromRawSignals(MG_step13_Rear_Window_Defog_Status_HS_CAN * pMsg);
#define MG_step13_Rear_Window_Defog_Status_HS_CAN_RrWndDfgOn_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 1, MG_step13_Rear_Window_Defog_Status_HS_CAN_Index, 0, dPhysicalValue);
#define MG_step13_Rear_Window_Defog_Status_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, MG_step13_Rear_Window_Defog_Status_HS_CAN_Index, 0)
extern int MG_mpi_diagResponse_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} MG_mpi_diagResponse_HS_CAN;


void MG_mpi_diagResponse_HS_CAN_Init(MG_mpi_diagResponse_HS_CAN * pMsg);
int MG_mpi_diagResponse_HS_CAN_Transmit(MG_mpi_diagResponse_HS_CAN * pMsg);
int MG_mpi_diagResponse_HS_CAN_Transmit_raw(MG_mpi_diagResponse_HS_CAN * pMsg);
#define MG_mpi_diagResponse_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, MG_mpi_diagResponse_HS_CAN_Index, 0)
extern int MG_mpi_diagResponse_consFrame1_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} MG_mpi_diagResponse_consFrame1_HS_CAN;


void MG_mpi_diagResponse_consFrame1_HS_CAN_Init(MG_mpi_diagResponse_consFrame1_HS_CAN * pMsg);
int MG_mpi_diagResponse_consFrame1_HS_CAN_Transmit(MG_mpi_diagResponse_consFrame1_HS_CAN * pMsg);
int MG_mpi_diagResponse_consFrame1_HS_CAN_Transmit_raw(MG_mpi_diagResponse_consFrame1_HS_CAN * pMsg);
#define MG_mpi_diagResponse_consFrame1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, MG_mpi_diagResponse_consFrame1_HS_CAN_Index, 0)
extern int MG_mpi_diagResponse_consFrame2_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} MG_mpi_diagResponse_consFrame2_HS_CAN;


void MG_mpi_diagResponse_consFrame2_HS_CAN_Init(MG_mpi_diagResponse_consFrame2_HS_CAN * pMsg);
int MG_mpi_diagResponse_consFrame2_HS_CAN_Transmit(MG_mpi_diagResponse_consFrame2_HS_CAN * pMsg);
int MG_mpi_diagResponse_consFrame2_HS_CAN_Transmit_raw(MG_mpi_diagResponse_consFrame2_HS_CAN * pMsg);
#define MG_mpi_diagResponse_consFrame2_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, MG_mpi_diagResponse_consFrame2_HS_CAN_Index, 0)
extern int MG_step9_PCRM005_LIN2__neoVI_3G__Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} MG_step9_PCRM005_LIN2__neoVI_3G_;


void MG_step9_PCRM005_LIN2__neoVI_3G__Init(MG_step9_PCRM005_LIN2__neoVI_3G_ * pMsg);
int MG_step9_PCRM005_LIN2__neoVI_3G__Transmit(MG_step9_PCRM005_LIN2__neoVI_3G_ * pMsg);
int MG_step9_PCRM005_LIN2__neoVI_3G__Transmit_raw(MG_step9_PCRM005_LIN2__neoVI_3G_ * pMsg);
#define MG_step9_PCRM005_LIN2__neoVI_3G__ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, MG_step9_PCRM005_LIN2__neoVI_3G__Index, 0)
extern int MG_step10_1_PCRM006_1_LIN3__neoVI_3G__Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} MG_step10_1_PCRM006_1_LIN3__neoVI_3G_;


void MG_step10_1_PCRM006_1_LIN3__neoVI_3G__Init(MG_step10_1_PCRM006_1_LIN3__neoVI_3G_ * pMsg);
int MG_step10_1_PCRM006_1_LIN3__neoVI_3G__Transmit(MG_step10_1_PCRM006_1_LIN3__neoVI_3G_ * pMsg);
int MG_step10_1_PCRM006_1_LIN3__neoVI_3G__Transmit_raw(MG_step10_1_PCRM006_1_LIN3__neoVI_3G_ * pMsg);
#define MG_step10_1_PCRM006_1_LIN3__neoVI_3G__ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, MG_step10_1_PCRM006_1_LIN3__neoVI_3G__Index, 0)
extern int DB_Report_Message_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double MISC3_AIN; /// Min: 0 Max: 1023 Units: 
    WORD MISC3_AIN_raw;
    double MISC4_AIN; /// Min: 0 Max: 1023 Units: 
    WORD MISC4_AIN_raw;
    double MISC5_AIN; /// Min: 0 Max: 1023 Units: 
    WORD MISC5_AIN_raw;
    double MISC6_AIN; /// Min: 0 Max: 1023 Units: 
    WORD MISC6_AIN_raw;
    double MISC1; /// Min: 0 Max: 1 Units: 
    BYTE MISC1_raw;
    double MISC2; /// Min: 0 Max: 1 Units: 
    BYTE MISC2_raw;
    double MISC3; /// Min: 0 Max: 1 Units: 
    BYTE MISC3_raw;
    double MISC4; /// Min: 0 Max: 1 Units: 
    BYTE MISC4_raw;
    double MISC5; /// Min: 0 Max: 1 Units: 
    BYTE MISC5_raw;
    double MISC6; /// Min: 0 Max: 1 Units: 
    BYTE MISC6_raw;
    double LED1; /// Min: 0 Max: 1 Units: 
    BYTE LED1_raw;
    double LED2; /// Min: 0 Max: 1 Units: 
    BYTE LED2_raw;
    double LIN1; /// Min: 0 Max: 1 Units: 
    BYTE LIN1_raw;
    double LIN2; /// Min: 0 Max: 1 Units: 
    BYTE LIN2_raw;
} DB_Report_Message_neoVI;


void DB_Report_Message_neoVI_Init(DB_Report_Message_neoVI * pMsg);
int DB_Report_Message_neoVI_Transmit(DB_Report_Message_neoVI * pMsg);
int DB_Report_Message_neoVI_Transmit_raw(DB_Report_Message_neoVI * pMsg);
int DB_Report_Message_neoVI_UpdateBytesFromSignals(DB_Report_Message_neoVI * pMsg);
int DB_Report_Message_neoVI_UpdateBytesFromRawSignals(DB_Report_Message_neoVI * pMsg);
#define DB_Report_Message_neoVI_MISC3_AIN_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message_neoVI_MISC4_AIN_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message_neoVI_MISC5_AIN_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 2, dPhysicalValue);
#define DB_Report_Message_neoVI_MISC6_AIN_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 3, dPhysicalValue);
#define DB_Report_Message_neoVI_MISC1_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 4, dPhysicalValue);
#define DB_Report_Message_neoVI_MISC2_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 5, dPhysicalValue);
#define DB_Report_Message_neoVI_MISC3_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 6, dPhysicalValue);
#define DB_Report_Message_neoVI_MISC4_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 7, dPhysicalValue);
#define DB_Report_Message_neoVI_MISC5_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 8, dPhysicalValue);
#define DB_Report_Message_neoVI_MISC6_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 9, dPhysicalValue);
#define DB_Report_Message_neoVI_LED1_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 10, dPhysicalValue);
#define DB_Report_Message_neoVI_LED2_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 11, dPhysicalValue);
#define DB_Report_Message_neoVI_LIN1_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 12, dPhysicalValue);
#define DB_Report_Message_neoVI_LIN2_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 13, dPhysicalValue);
#define DB_Report_Message_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message_neoVI_Index, 0)
extern int DB_Report_Message__PWM__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double PWM_In_1; /// Min: 0 Max: 4294967295 Units: 
    DWORD PWM_In_1_raw;
} DB_Report_Message__PWM__neoVI;


void DB_Report_Message__PWM__neoVI_Init(DB_Report_Message__PWM__neoVI * pMsg);
int DB_Report_Message__PWM__neoVI_Transmit(DB_Report_Message__PWM__neoVI * pMsg);
int DB_Report_Message__PWM__neoVI_Transmit_raw(DB_Report_Message__PWM__neoVI * pMsg);
int DB_Report_Message__PWM__neoVI_UpdateBytesFromSignals(DB_Report_Message__PWM__neoVI * pMsg);
int DB_Report_Message__PWM__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__PWM__neoVI * pMsg);
#define DB_Report_Message__PWM__neoVI_PWM_In_1_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__PWM__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__PWM__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__PWM__neoVI_Index, 0)
extern int DB_Report_Message__VCAN_RF__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double MISC1_AIN; /// Min: 0 Max: 41.55477149999999 Units: V
    WORD MISC1_AIN_raw;
    double MISC_1; /// Min: 0 Max: 1 Units: 
    BYTE MISC_1_raw;
    double MISC_2; /// Min: 0 Max: 1 Units: 
    BYTE MISC_2_raw;
    double MISC_3; /// Min: 0 Max: 1 Units: 
    BYTE MISC_3_raw;
    double MISC_4; /// Min: 0 Max: 1 Units: 
    BYTE MISC_4_raw;
    double Vehicle_Battery_Voltage; /// Min: 0 Max: 43.18778320312499 Units: V
    WORD Vehicle_Battery_Voltage_raw;
    double Temperature; /// Min: -215 Max: 114.677734375 Units: C
    WORD Temperature_raw;
    double Hardware_Revision; /// Min: 3 Max: 10.9921875 Units: 
    WORD Hardware_Revision_raw;
    double RTC_Battery_Measure_Enabled; /// Min: 0 Max: 1 Units: 
    BYTE RTC_Battery_Measure_Enabled_raw;
    double RTC_Battery_Voltage; /// Min: 0 Max: 3.29677734375 Units: V
    WORD RTC_Battery_Voltage_raw;
} DB_Report_Message__VCAN_RF__neoVI;


void DB_Report_Message__VCAN_RF__neoVI_Init(DB_Report_Message__VCAN_RF__neoVI * pMsg);
int DB_Report_Message__VCAN_RF__neoVI_Transmit(DB_Report_Message__VCAN_RF__neoVI * pMsg);
int DB_Report_Message__VCAN_RF__neoVI_Transmit_raw(DB_Report_Message__VCAN_RF__neoVI * pMsg);
int DB_Report_Message__VCAN_RF__neoVI_UpdateBytesFromSignals(DB_Report_Message__VCAN_RF__neoVI * pMsg);
int DB_Report_Message__VCAN_RF__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__VCAN_RF__neoVI * pMsg);
#define DB_Report_Message__VCAN_RF__neoVI_MISC1_AIN_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__VCAN_RF__neoVI_MISC_1_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__VCAN_RF__neoVI_MISC_2_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, 2, dPhysicalValue);
#define DB_Report_Message__VCAN_RF__neoVI_MISC_3_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, 3, dPhysicalValue);
#define DB_Report_Message__VCAN_RF__neoVI_MISC_4_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, 4, dPhysicalValue);
#define DB_Report_Message__VCAN_RF__neoVI_Vehicle_Battery_Voltage_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, 5, dPhysicalValue);
#define DB_Report_Message__VCAN_RF__neoVI_Temperature_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, 6, dPhysicalValue);
#define DB_Report_Message__VCAN_RF__neoVI_Hardware_Revision_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, 7, dPhysicalValue);
#define DB_Report_Message__VCAN_RF__neoVI_RTC_Battery_Measure_Enabled_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, 8, dPhysicalValue);
#define DB_Report_Message__VCAN_RF__neoVI_RTC_Battery_Voltage_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, 9, dPhysicalValue);
#define DB_Report_Message__VCAN_RF__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__VCAN_RF__neoVI_Index, 0)
extern int DB_Report_Message__neoVI_Fire2__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double EMISC1_AIN; /// Min: 0 Max: 41.58517545 Units: V
    WORD EMISC1_AIN_raw;
    double EMISC2_AIN; /// Min: 0 Max: 41.58517545 Units: V
    WORD EMISC2_AIN_raw;
    double MISC3; /// Min: 0 Max: 1 Units: 
    BYTE MISC3_raw;
    double MISC4; /// Min: 0 Max: 1 Units: 
    BYTE MISC4_raw;
    double Vehicle_Battery_Voltage; /// Min: 0 Max: 43.21940805 Units: V
    WORD Vehicle_Battery_Voltage_raw;
    double Temperature; /// Min: 0 Max: 0 Units: C
    WORD Temperature_raw;
    double RTC_Battery_Voltage; /// Min: 0 Max: 13.19675175 Units: V
    WORD RTC_Battery_Voltage_raw;
} DB_Report_Message__neoVI_Fire2__neoVI;


void DB_Report_Message__neoVI_Fire2__neoVI_Init(DB_Report_Message__neoVI_Fire2__neoVI * pMsg);
int DB_Report_Message__neoVI_Fire2__neoVI_Transmit(DB_Report_Message__neoVI_Fire2__neoVI * pMsg);
int DB_Report_Message__neoVI_Fire2__neoVI_Transmit_raw(DB_Report_Message__neoVI_Fire2__neoVI * pMsg);
int DB_Report_Message__neoVI_Fire2__neoVI_UpdateBytesFromSignals(DB_Report_Message__neoVI_Fire2__neoVI * pMsg);
int DB_Report_Message__neoVI_Fire2__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__neoVI_Fire2__neoVI * pMsg);
#define DB_Report_Message__neoVI_Fire2__neoVI_EMISC1_AIN_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__neoVI_Fire2__neoVI_EMISC2_AIN_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__neoVI_Fire2__neoVI_MISC3_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, 2, dPhysicalValue);
#define DB_Report_Message__neoVI_Fire2__neoVI_MISC4_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, 3, dPhysicalValue);
#define DB_Report_Message__neoVI_Fire2__neoVI_Vehicle_Battery_Voltage_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, 4, dPhysicalValue);
#define DB_Report_Message__neoVI_Fire2__neoVI_Temperature_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, 5, dPhysicalValue);
#define DB_Report_Message__neoVI_Fire2__neoVI_RTC_Battery_Voltage_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, 6, dPhysicalValue);
#define DB_Report_Message__neoVI_Fire2__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__neoVI_Fire2__neoVI_Index, 0)
extern int DB_Report_Message__GPS_Latitude__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Latitude; /// Min: 0 Max: 0 Units: degrees
    uint64 Latitude_raw;
} DB_Report_Message__GPS_Latitude__neoVI;


void DB_Report_Message__GPS_Latitude__neoVI_Init(DB_Report_Message__GPS_Latitude__neoVI * pMsg);
int DB_Report_Message__GPS_Latitude__neoVI_Transmit(DB_Report_Message__GPS_Latitude__neoVI * pMsg);
int DB_Report_Message__GPS_Latitude__neoVI_Transmit_raw(DB_Report_Message__GPS_Latitude__neoVI * pMsg);
int DB_Report_Message__GPS_Latitude__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Latitude__neoVI * pMsg);
int DB_Report_Message__GPS_Latitude__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Latitude__neoVI * pMsg);
#define DB_Report_Message__GPS_Latitude__neoVI_Latitude_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Latitude__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__GPS_Latitude__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__GPS_Latitude__neoVI_Index, 0)
extern int DB_Report_Message__GPS_Longitude__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Longitude; /// Min: 0 Max: 0 Units: degrees
    uint64 Longitude_raw;
} DB_Report_Message__GPS_Longitude__neoVI;


void DB_Report_Message__GPS_Longitude__neoVI_Init(DB_Report_Message__GPS_Longitude__neoVI * pMsg);
int DB_Report_Message__GPS_Longitude__neoVI_Transmit(DB_Report_Message__GPS_Longitude__neoVI * pMsg);
int DB_Report_Message__GPS_Longitude__neoVI_Transmit_raw(DB_Report_Message__GPS_Longitude__neoVI * pMsg);
int DB_Report_Message__GPS_Longitude__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Longitude__neoVI * pMsg);
int DB_Report_Message__GPS_Longitude__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Longitude__neoVI * pMsg);
#define DB_Report_Message__GPS_Longitude__neoVI_Longitude_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Longitude__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__GPS_Longitude__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__GPS_Longitude__neoVI_Index, 0)
extern int DB_Report_Message__GPS_Flags__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Update_Count; /// Min: 0 Max: 255 Units: 
    BYTE Update_Count_raw;
    double GPS_Date_Available; /// Min: 0 Max: 1 Units: 
    BYTE GPS_Date_Available_raw;
    double GPS_Time_Available; /// Min: 0 Max: 1 Units: 
    BYTE GPS_Time_Available_raw;
    double GPS_Accuracy_Available; /// Min: 0 Max: 1 Units: 
    BYTE GPS_Accuracy_Available_raw;
    double GPS_Bearing_Available; /// Min: 0 Max: 1 Units: 
    BYTE GPS_Bearing_Available_raw;
    double GPS_Speed_Available; /// Min: 0 Max: 1 Units: 
    BYTE GPS_Speed_Available_raw;
    double GPS_Altitude_Available; /// Min: 0 Max: 1 Units: 
    BYTE GPS_Altitude_Available_raw;
    double GPS_Lat_Lon_Available; /// Min: 0 Max: 1 Units: 
    BYTE GPS_Lat_Lon_Available_raw;
} DB_Report_Message__GPS_Flags__neoVI;


void DB_Report_Message__GPS_Flags__neoVI_Init(DB_Report_Message__GPS_Flags__neoVI * pMsg);
int DB_Report_Message__GPS_Flags__neoVI_Transmit(DB_Report_Message__GPS_Flags__neoVI * pMsg);
int DB_Report_Message__GPS_Flags__neoVI_Transmit_raw(DB_Report_Message__GPS_Flags__neoVI * pMsg);
int DB_Report_Message__GPS_Flags__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Flags__neoVI * pMsg);
int DB_Report_Message__GPS_Flags__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Flags__neoVI * pMsg);
#define DB_Report_Message__GPS_Flags__neoVI_Update_Count_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__GPS_Flags__neoVI_GPS_Date_Available_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__GPS_Flags__neoVI_GPS_Time_Available_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, 2, dPhysicalValue);
#define DB_Report_Message__GPS_Flags__neoVI_GPS_Accuracy_Available_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, 3, dPhysicalValue);
#define DB_Report_Message__GPS_Flags__neoVI_GPS_Bearing_Available_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, 4, dPhysicalValue);
#define DB_Report_Message__GPS_Flags__neoVI_GPS_Speed_Available_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, 5, dPhysicalValue);
#define DB_Report_Message__GPS_Flags__neoVI_GPS_Altitude_Available_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, 6, dPhysicalValue);
#define DB_Report_Message__GPS_Flags__neoVI_GPS_Lat_Lon_Available_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, 7, dPhysicalValue);
#define DB_Report_Message__GPS_Flags__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__GPS_Flags__neoVI_Index, 0)
extern int DB_Report_Message__GPS_Altitude__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Altitude_Ellipse; /// Min: 0 Max: 0 Units: meters
    uint64 Altitude_Ellipse_raw;
} DB_Report_Message__GPS_Altitude__neoVI;


void DB_Report_Message__GPS_Altitude__neoVI_Init(DB_Report_Message__GPS_Altitude__neoVI * pMsg);
int DB_Report_Message__GPS_Altitude__neoVI_Transmit(DB_Report_Message__GPS_Altitude__neoVI * pMsg);
int DB_Report_Message__GPS_Altitude__neoVI_Transmit_raw(DB_Report_Message__GPS_Altitude__neoVI * pMsg);
int DB_Report_Message__GPS_Altitude__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Altitude__neoVI * pMsg);
int DB_Report_Message__GPS_Altitude__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Altitude__neoVI * pMsg);
#define DB_Report_Message__GPS_Altitude__neoVI_Altitude_Ellipse_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Altitude__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__GPS_Altitude__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__GPS_Altitude__neoVI_Index, 0)
extern int DB_Report_Message__GPS_Speed_Bearing__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Speed; /// Min: 0 Max: 0 Units: m/s
    DWORD Speed_raw;
    double Bearing; /// Min: 0 Max: 0 Units: degrees
    DWORD Bearing_raw;
} DB_Report_Message__GPS_Speed_Bearing__neoVI;


void DB_Report_Message__GPS_Speed_Bearing__neoVI_Init(DB_Report_Message__GPS_Speed_Bearing__neoVI * pMsg);
int DB_Report_Message__GPS_Speed_Bearing__neoVI_Transmit(DB_Report_Message__GPS_Speed_Bearing__neoVI * pMsg);
int DB_Report_Message__GPS_Speed_Bearing__neoVI_Transmit_raw(DB_Report_Message__GPS_Speed_Bearing__neoVI * pMsg);
int DB_Report_Message__GPS_Speed_Bearing__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Speed_Bearing__neoVI * pMsg);
int DB_Report_Message__GPS_Speed_Bearing__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Speed_Bearing__neoVI * pMsg);
#define DB_Report_Message__GPS_Speed_Bearing__neoVI_Speed_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Speed_Bearing__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__GPS_Speed_Bearing__neoVI_Bearing_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Speed_Bearing__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__GPS_Speed_Bearing__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__GPS_Speed_Bearing__neoVI_Index, 0)
extern int DB_Report_Message__GPS_Accuracy__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Accuracy; /// Min: 0 Max: 0 Units: meters
    DWORD Accuracy_raw;
} DB_Report_Message__GPS_Accuracy__neoVI;


void DB_Report_Message__GPS_Accuracy__neoVI_Init(DB_Report_Message__GPS_Accuracy__neoVI * pMsg);
int DB_Report_Message__GPS_Accuracy__neoVI_Transmit(DB_Report_Message__GPS_Accuracy__neoVI * pMsg);
int DB_Report_Message__GPS_Accuracy__neoVI_Transmit_raw(DB_Report_Message__GPS_Accuracy__neoVI * pMsg);
int DB_Report_Message__GPS_Accuracy__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Accuracy__neoVI * pMsg);
int DB_Report_Message__GPS_Accuracy__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Accuracy__neoVI * pMsg);
#define DB_Report_Message__GPS_Accuracy__neoVI_Accuracy_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Accuracy__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__GPS_Accuracy__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__GPS_Accuracy__neoVI_Index, 0)
extern int DB_Report_Message__GPS_Time__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Timestamp; /// Min: 0 Max: 18446744073709551615 Units: ms since 1/1/1970
    uint64 Timestamp_raw;
} DB_Report_Message__GPS_Time__neoVI;


void DB_Report_Message__GPS_Time__neoVI_Init(DB_Report_Message__GPS_Time__neoVI * pMsg);
int DB_Report_Message__GPS_Time__neoVI_Transmit(DB_Report_Message__GPS_Time__neoVI * pMsg);
int DB_Report_Message__GPS_Time__neoVI_Transmit_raw(DB_Report_Message__GPS_Time__neoVI * pMsg);
int DB_Report_Message__GPS_Time__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Time__neoVI * pMsg);
int DB_Report_Message__GPS_Time__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Time__neoVI * pMsg);
#define DB_Report_Message__GPS_Time__neoVI_Timestamp_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Time__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__GPS_Time__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__GPS_Time__neoVI_Index, 0)
extern int DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double WiviStartSector; /// Min: -2147483648 Max: 2147483647 Units: 
    DWORD WiviStartSector_raw;
    double WiviEndSector; /// Min: -2147483648 Max: 2147483647 Units: 
    DWORD WiviEndSector_raw;
} DB_Report_Message__WirelessneoVI_Sectors__neoVI;


void DB_Report_Message__WirelessneoVI_Sectors__neoVI_Init(DB_Report_Message__WirelessneoVI_Sectors__neoVI * pMsg);
int DB_Report_Message__WirelessneoVI_Sectors__neoVI_Transmit(DB_Report_Message__WirelessneoVI_Sectors__neoVI * pMsg);
int DB_Report_Message__WirelessneoVI_Sectors__neoVI_Transmit_raw(DB_Report_Message__WirelessneoVI_Sectors__neoVI * pMsg);
int DB_Report_Message__WirelessneoVI_Sectors__neoVI_UpdateBytesFromSignals(DB_Report_Message__WirelessneoVI_Sectors__neoVI * pMsg);
int DB_Report_Message__WirelessneoVI_Sectors__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__WirelessneoVI_Sectors__neoVI * pMsg);
#define DB_Report_Message__WirelessneoVI_Sectors__neoVI_WiviStartSector_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__WirelessneoVI_Sectors__neoVI_WiviEndSector_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__WirelessneoVI_Sectors__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index, 0)
extern int DB_Report_Message__WirelessneoVI_Signals__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double WiviJob; /// Min: -128 Max: 127 Units: 
    BYTE WiviJob_raw;
    double WiviApkResponse; /// Min: -128 Max: 127 Units: 
    BYTE WiviApkResponse_raw;
    double WiviDataTransferMediumChoice; /// Min: -128 Max: 127 Units: 
    BYTE WiviDataTransferMediumChoice_raw;
    double WiviApkResponseTo; /// Min: -128 Max: 127 Units: 
    BYTE WiviApkResponseTo_raw;
    double WiviReserved0; /// Min: -128 Max: 127 Units: 
    BYTE WiviReserved0_raw;
    double WiviReserved1; /// Min: -128 Max: 127 Units: 
    BYTE WiviReserved1_raw;
} DB_Report_Message__WirelessneoVI_Signals__neoVI;


void DB_Report_Message__WirelessneoVI_Signals__neoVI_Init(DB_Report_Message__WirelessneoVI_Signals__neoVI * pMsg);
int DB_Report_Message__WirelessneoVI_Signals__neoVI_Transmit(DB_Report_Message__WirelessneoVI_Signals__neoVI * pMsg);
int DB_Report_Message__WirelessneoVI_Signals__neoVI_Transmit_raw(DB_Report_Message__WirelessneoVI_Signals__neoVI * pMsg);
int DB_Report_Message__WirelessneoVI_Signals__neoVI_UpdateBytesFromSignals(DB_Report_Message__WirelessneoVI_Signals__neoVI * pMsg);
int DB_Report_Message__WirelessneoVI_Signals__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__WirelessneoVI_Signals__neoVI * pMsg);
#define DB_Report_Message__WirelessneoVI_Signals__neoVI_WiviJob_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__WirelessneoVI_Signals__neoVI_WiviApkResponse_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__WirelessneoVI_Signals__neoVI_WiviDataTransferMediumChoice_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, 2, dPhysicalValue);
#define DB_Report_Message__WirelessneoVI_Signals__neoVI_WiviApkResponseTo_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, 3, dPhysicalValue);
#define DB_Report_Message__WirelessneoVI_Signals__neoVI_WiviReserved0_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, 4, dPhysicalValue);
#define DB_Report_Message__WirelessneoVI_Signals__neoVI_WiviReserved1_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, 5, dPhysicalValue);
#define DB_Report_Message__WirelessneoVI_Signals__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, 0)
extern int DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI;


void DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_Init(DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI * pMsg);
int DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_Transmit(DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI * pMsg);
int DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_Transmit_raw(DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI * pMsg);
#define DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_Index, 0)
extern int DB_neoVI_Logger_Message_Data_Lost_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} DB_neoVI_Logger_Message_Data_Lost_neoVI;


void DB_neoVI_Logger_Message_Data_Lost_neoVI_Init(DB_neoVI_Logger_Message_Data_Lost_neoVI * pMsg);
int DB_neoVI_Logger_Message_Data_Lost_neoVI_Transmit(DB_neoVI_Logger_Message_Data_Lost_neoVI * pMsg);
int DB_neoVI_Logger_Message_Data_Lost_neoVI_Transmit_raw(DB_neoVI_Logger_Message_Data_Lost_neoVI * pMsg);
#define DB_neoVI_Logger_Message_Data_Lost_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_neoVI_Logger_Message_Data_Lost_neoVI_Index, 0)
extern int DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI;


void DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_Init(DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI * pMsg);
int DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_Transmit(DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI * pMsg);
int DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_Transmit_raw(DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI * pMsg);
#define DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_Index, 0)
extern int DB_neoVI_Logger_woke_up_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double SleepFlags; /// Min: 0 Max: 65535 Units: 
    WORD SleepFlags_raw;
    double WakeupFlags; /// Min: 0 Max: 65535 Units: 
    WORD WakeupFlags_raw;
    double WakeUpSms; /// Min: 0 Max: 1 Units: 
    BYTE WakeUpSms_raw;
    double WakeupSlaveA; /// Min: 0 Max: 1 Units: 
    BYTE WakeupSlaveA_raw;
    double WakeupSlaveB; /// Min: 0 Max: 1 Units: 
    BYTE WakeupSlaveB_raw;
    double WakeupMainVnet; /// Min: 0 Max: 1 Units: 
    BYTE WakeupMainVnet_raw;
    double WakeupUsb; /// Min: 0 Max: 1 Units: 
    BYTE WakeupUsb_raw;
    double PowerBoot; /// Min: 0 Max: 1 Units: 
    BYTE PowerBoot_raw;
    double LowVbatSleep; /// Min: 0 Max: 1 Units: 
    BYTE LowVbatSleep_raw;
    double NoCmSleep; /// Min: 0 Max: 1 Units: 
    BYTE NoCmSleep_raw;
} DB_neoVI_Logger_woke_up_neoVI;


void DB_neoVI_Logger_woke_up_neoVI_Init(DB_neoVI_Logger_woke_up_neoVI * pMsg);
int DB_neoVI_Logger_woke_up_neoVI_Transmit(DB_neoVI_Logger_woke_up_neoVI * pMsg);
int DB_neoVI_Logger_woke_up_neoVI_Transmit_raw(DB_neoVI_Logger_woke_up_neoVI * pMsg);
int DB_neoVI_Logger_woke_up_neoVI_UpdateBytesFromSignals(DB_neoVI_Logger_woke_up_neoVI * pMsg);
int DB_neoVI_Logger_woke_up_neoVI_UpdateBytesFromRawSignals(DB_neoVI_Logger_woke_up_neoVI * pMsg);
#define DB_neoVI_Logger_woke_up_neoVI_SleepFlags_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, 0, dPhysicalValue);
#define DB_neoVI_Logger_woke_up_neoVI_WakeupFlags_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, 1, dPhysicalValue);
#define DB_neoVI_Logger_woke_up_neoVI_WakeUpSms_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, 2, dPhysicalValue);
#define DB_neoVI_Logger_woke_up_neoVI_WakeupSlaveA_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, 3, dPhysicalValue);
#define DB_neoVI_Logger_woke_up_neoVI_WakeupSlaveB_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, 4, dPhysicalValue);
#define DB_neoVI_Logger_woke_up_neoVI_WakeupMainVnet_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, 5, dPhysicalValue);
#define DB_neoVI_Logger_woke_up_neoVI_WakeupUsb_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, 6, dPhysicalValue);
#define DB_neoVI_Logger_woke_up_neoVI_PowerBoot_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, 7, dPhysicalValue);
#define DB_neoVI_Logger_woke_up_neoVI_LowVbatSleep_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, 8, dPhysicalValue);
#define DB_neoVI_Logger_woke_up_neoVI_NoCmSleep_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, 9, dPhysicalValue);
#define DB_neoVI_Logger_woke_up_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_neoVI_Logger_woke_up_neoVI_Index, 0)
extern int DB_Report_Message_1_Analog_Card__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Channel_A; /// Min: -9980.46875 Max: 10000 Units: mV
    WORD Channel_A_raw;
    double Channel_B; /// Min: -9980.46875 Max: 10000 Units: mV
    WORD Channel_B_raw;
    double Channel_1_Differential_; /// Min: -42978.83555 Max: 42980.14719999999 Units: mV
    WORD Channel_1_Differential__raw;
    double Channel_2_Differential_; /// Min: -42978.83555 Max: 42980.14719999999 Units: mV
    WORD Channel_2_Differential__raw;
} DB_Report_Message_1_Analog_Card__neoVI;


void DB_Report_Message_1_Analog_Card__neoVI_Init(DB_Report_Message_1_Analog_Card__neoVI * pMsg);
int DB_Report_Message_1_Analog_Card__neoVI_Transmit(DB_Report_Message_1_Analog_Card__neoVI * pMsg);
int DB_Report_Message_1_Analog_Card__neoVI_Transmit_raw(DB_Report_Message_1_Analog_Card__neoVI * pMsg);
int DB_Report_Message_1_Analog_Card__neoVI_UpdateBytesFromSignals(DB_Report_Message_1_Analog_Card__neoVI * pMsg);
int DB_Report_Message_1_Analog_Card__neoVI_UpdateBytesFromRawSignals(DB_Report_Message_1_Analog_Card__neoVI * pMsg);
#define DB_Report_Message_1_Analog_Card__neoVI_Channel_A_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_1_Analog_Card__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message_1_Analog_Card__neoVI_Channel_B_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_1_Analog_Card__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message_1_Analog_Card__neoVI_Channel_1_Differential__PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_1_Analog_Card__neoVI_Index, 2, dPhysicalValue);
#define DB_Report_Message_1_Analog_Card__neoVI_Channel_2_Differential__PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_1_Analog_Card__neoVI_Index, 3, dPhysicalValue);
#define DB_Report_Message_1_Analog_Card__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message_1_Analog_Card__neoVI_Index, 0)
extern int DB_Report_Message_2_Analog_Card__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Channel_3_Differential_; /// Min: -42978.83555 Max: 42980.14719999999 Units: mV
    WORD Channel_3_Differential__raw;
    double Channel_4_Differential_; /// Min: -42978.83555 Max: 42980.14719999999 Units: mV
    WORD Channel_4_Differential__raw;
    double Channel_5_Differential_; /// Min: -42978.83555 Max: 42980.14719999999 Units: mV
    WORD Channel_5_Differential__raw;
    double Channel_6_Differential_; /// Min: -42978.83555 Max: 42980.14719999999 Units: mV
    WORD Channel_6_Differential__raw;
} DB_Report_Message_2_Analog_Card__neoVI;


void DB_Report_Message_2_Analog_Card__neoVI_Init(DB_Report_Message_2_Analog_Card__neoVI * pMsg);
int DB_Report_Message_2_Analog_Card__neoVI_Transmit(DB_Report_Message_2_Analog_Card__neoVI * pMsg);
int DB_Report_Message_2_Analog_Card__neoVI_Transmit_raw(DB_Report_Message_2_Analog_Card__neoVI * pMsg);
int DB_Report_Message_2_Analog_Card__neoVI_UpdateBytesFromSignals(DB_Report_Message_2_Analog_Card__neoVI * pMsg);
int DB_Report_Message_2_Analog_Card__neoVI_UpdateBytesFromRawSignals(DB_Report_Message_2_Analog_Card__neoVI * pMsg);
#define DB_Report_Message_2_Analog_Card__neoVI_Channel_3_Differential__PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_2_Analog_Card__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message_2_Analog_Card__neoVI_Channel_4_Differential__PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_2_Analog_Card__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message_2_Analog_Card__neoVI_Channel_5_Differential__PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_2_Analog_Card__neoVI_Index, 2, dPhysicalValue);
#define DB_Report_Message_2_Analog_Card__neoVI_Channel_6_Differential__PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_2_Analog_Card__neoVI_Index, 3, dPhysicalValue);
#define DB_Report_Message_2_Analog_Card__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message_2_Analog_Card__neoVI_Index, 0)
extern int DB_Report_Message_3_Analog_Card__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Channel_7_Differential_; /// Min: -42978.83555 Max: 42980.14719999999 Units: mV
    WORD Channel_7_Differential__raw;
} DB_Report_Message_3_Analog_Card__neoVI;


void DB_Report_Message_3_Analog_Card__neoVI_Init(DB_Report_Message_3_Analog_Card__neoVI * pMsg);
int DB_Report_Message_3_Analog_Card__neoVI_Transmit(DB_Report_Message_3_Analog_Card__neoVI * pMsg);
int DB_Report_Message_3_Analog_Card__neoVI_Transmit_raw(DB_Report_Message_3_Analog_Card__neoVI * pMsg);
int DB_Report_Message_3_Analog_Card__neoVI_UpdateBytesFromSignals(DB_Report_Message_3_Analog_Card__neoVI * pMsg);
int DB_Report_Message_3_Analog_Card__neoVI_UpdateBytesFromRawSignals(DB_Report_Message_3_Analog_Card__neoVI * pMsg);
#define DB_Report_Message_3_Analog_Card__neoVI_Channel_7_Differential__PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_3_Analog_Card__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message_3_Analog_Card__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message_3_Analog_Card__neoVI_Index, 0)
extern int DB_Report_Message_4_Analog_Card__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Timestamp; /// Min: 0 Max: 18446744073709551615 Units: 
    uint64 Timestamp_raw;
} DB_Report_Message_4_Analog_Card__neoVI;


void DB_Report_Message_4_Analog_Card__neoVI_Init(DB_Report_Message_4_Analog_Card__neoVI * pMsg);
int DB_Report_Message_4_Analog_Card__neoVI_Transmit(DB_Report_Message_4_Analog_Card__neoVI * pMsg);
int DB_Report_Message_4_Analog_Card__neoVI_Transmit_raw(DB_Report_Message_4_Analog_Card__neoVI * pMsg);
int DB_Report_Message_4_Analog_Card__neoVI_UpdateBytesFromSignals(DB_Report_Message_4_Analog_Card__neoVI * pMsg);
int DB_Report_Message_4_Analog_Card__neoVI_UpdateBytesFromRawSignals(DB_Report_Message_4_Analog_Card__neoVI * pMsg);
#define DB_Report_Message_4_Analog_Card__neoVI_Timestamp_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_4_Analog_Card__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message_4_Analog_Card__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message_4_Analog_Card__neoVI_Index, 0)
extern int DB_Time_Resync_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Timestamp; /// Min: -0 Max: 0 Units: ms
    uint64 Timestamp_raw;
} DB_Time_Resync_neoVI;


void DB_Time_Resync_neoVI_Init(DB_Time_Resync_neoVI * pMsg);
int DB_Time_Resync_neoVI_Transmit(DB_Time_Resync_neoVI * pMsg);
int DB_Time_Resync_neoVI_Transmit_raw(DB_Time_Resync_neoVI * pMsg);
int DB_Time_Resync_neoVI_UpdateBytesFromSignals(DB_Time_Resync_neoVI * pMsg);
int DB_Time_Resync_neoVI_UpdateBytesFromRawSignals(DB_Time_Resync_neoVI * pMsg);
#define DB_Time_Resync_neoVI_Timestamp_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Time_Resync_neoVI_Index, 0, dPhysicalValue);
#define DB_Time_Resync_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Time_Resync_neoVI_Index, 0)
extern int DB_VNET_Clock_Edge_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} DB_VNET_Clock_Edge_neoVI;


void DB_VNET_Clock_Edge_neoVI_Init(DB_VNET_Clock_Edge_neoVI * pMsg);
int DB_VNET_Clock_Edge_neoVI_Transmit(DB_VNET_Clock_Edge_neoVI * pMsg);
int DB_VNET_Clock_Edge_neoVI_Transmit_raw(DB_VNET_Clock_Edge_neoVI * pMsg);
#define DB_VNET_Clock_Edge_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_VNET_Clock_Edge_neoVI_Index, 0)
extern int DB_VNET_A_Stats_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double msgTotal; /// Min: 0 Max: 65535 Units: 
    WORD msgTotal_raw;
    double rxSize; /// Min: 0 Max: 255 Units: 
    BYTE rxSize_raw;
    double scCnt; /// Min: 0 Max: 255 Units: 
    BYTE scCnt_raw;
    double yields; /// Min: 0 Max: 65535 Units: 
    WORD yields_raw;
    double bytesRead; /// Min: 0 Max: 65535 Units: 
    WORD bytesRead_raw;
} DB_VNET_A_Stats_neoVI;


void DB_VNET_A_Stats_neoVI_Init(DB_VNET_A_Stats_neoVI * pMsg);
int DB_VNET_A_Stats_neoVI_Transmit(DB_VNET_A_Stats_neoVI * pMsg);
int DB_VNET_A_Stats_neoVI_Transmit_raw(DB_VNET_A_Stats_neoVI * pMsg);
int DB_VNET_A_Stats_neoVI_UpdateBytesFromSignals(DB_VNET_A_Stats_neoVI * pMsg);
int DB_VNET_A_Stats_neoVI_UpdateBytesFromRawSignals(DB_VNET_A_Stats_neoVI * pMsg);
#define DB_VNET_A_Stats_neoVI_msgTotal_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VNET_A_Stats_neoVI_Index, 0, dPhysicalValue);
#define DB_VNET_A_Stats_neoVI_rxSize_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VNET_A_Stats_neoVI_Index, 1, dPhysicalValue);
#define DB_VNET_A_Stats_neoVI_scCnt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VNET_A_Stats_neoVI_Index, 2, dPhysicalValue);
#define DB_VNET_A_Stats_neoVI_yields_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VNET_A_Stats_neoVI_Index, 3, dPhysicalValue);
#define DB_VNET_A_Stats_neoVI_bytesRead_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VNET_A_Stats_neoVI_Index, 4, dPhysicalValue);
#define DB_VNET_A_Stats_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_VNET_A_Stats_neoVI_Index, 0)
extern int DB_VNET_A_Reboot_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} DB_VNET_A_Reboot_neoVI;


void DB_VNET_A_Reboot_neoVI_Init(DB_VNET_A_Reboot_neoVI * pMsg);
int DB_VNET_A_Reboot_neoVI_Transmit(DB_VNET_A_Reboot_neoVI * pMsg);
int DB_VNET_A_Reboot_neoVI_Transmit_raw(DB_VNET_A_Reboot_neoVI * pMsg);
#define DB_VNET_A_Reboot_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_VNET_A_Reboot_neoVI_Index, 0)
extern int DB_neoVI_Went_To_Sleep_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} DB_neoVI_Went_To_Sleep_neoVI;


void DB_neoVI_Went_To_Sleep_neoVI_Init(DB_neoVI_Went_To_Sleep_neoVI * pMsg);
int DB_neoVI_Went_To_Sleep_neoVI_Transmit(DB_neoVI_Went_To_Sleep_neoVI * pMsg);
int DB_neoVI_Went_To_Sleep_neoVI_Transmit_raw(DB_neoVI_Went_To_Sleep_neoVI * pMsg);
#define DB_neoVI_Went_To_Sleep_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_neoVI_Went_To_Sleep_neoVI_Index, 0)
extern int DB_Device_subsystem_restarted__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} DB_Device_subsystem_restarted__neoVI;


void DB_Device_subsystem_restarted__neoVI_Init(DB_Device_subsystem_restarted__neoVI * pMsg);
int DB_Device_subsystem_restarted__neoVI_Transmit(DB_Device_subsystem_restarted__neoVI * pMsg);
int DB_Device_subsystem_restarted__neoVI_Transmit_raw(DB_Device_subsystem_restarted__neoVI * pMsg);
#define DB_Device_subsystem_restarted__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Device_subsystem_restarted__neoVI_Index, 0)
extern int DB_Ethernet_DAQ_Report_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Recording; /// Min: 0 Max: 1 Units: 
    BYTE Recording_raw;
    double FPGA_Alive; /// Min: 0 Max: 1 Units: 
    BYTE FPGA_Alive_raw;
    double Bad_Chip; /// Min: 0 Max: 1 Units: 
    BYTE Bad_Chip_raw;
    double Raw_MAC_Mode; /// Min: 0 Max: 1 Units: 
    BYTE Raw_MAC_Mode_raw;
    double IPv4_Filter; /// Min: 0 Max: 1 Units: 
    BYTE IPv4_Filter_raw;
    double RxOverflow; /// Min: 0 Max: 1 Units: 
    BYTE RxOverflow_raw;
    double CmdBusy; /// Min: 0 Max: 1 Units: 
    BYTE CmdBusy_raw;
    double LogTO; /// Min: 0 Max: 1 Units: 
    BYTE LogTO_raw;
    double SockActivityTO; /// Min: 0 Max: 1 Units: 
    BYTE SockActivityTO_raw;
    double FPGAComTO; /// Min: 0 Max: 255 Units: 
    BYTE FPGAComTO_raw;
    double SockConfigTO; /// Min: 0 Max: 255 Units: 
    BYTE SockConfigTO_raw;
    double SockDiscon; /// Min: 0 Max: 255 Units: 
    BYTE SockDiscon_raw;
    double WcfSM; /// Min: 0 Max: 255 Units: 
    BYTE WcfSM_raw;
    double TxMsgsPending; /// Min: 0 Max: 255 Units: 
    BYTE TxMsgsPending_raw;
} DB_Ethernet_DAQ_Report_neoVI;


void DB_Ethernet_DAQ_Report_neoVI_Init(DB_Ethernet_DAQ_Report_neoVI * pMsg);
int DB_Ethernet_DAQ_Report_neoVI_Transmit(DB_Ethernet_DAQ_Report_neoVI * pMsg);
int DB_Ethernet_DAQ_Report_neoVI_Transmit_raw(DB_Ethernet_DAQ_Report_neoVI * pMsg);
int DB_Ethernet_DAQ_Report_neoVI_UpdateBytesFromSignals(DB_Ethernet_DAQ_Report_neoVI * pMsg);
int DB_Ethernet_DAQ_Report_neoVI_UpdateBytesFromRawSignals(DB_Ethernet_DAQ_Report_neoVI * pMsg);
#define DB_Ethernet_DAQ_Report_neoVI_Recording_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 0, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_FPGA_Alive_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 1, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_Bad_Chip_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 2, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_Raw_MAC_Mode_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 3, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_IPv4_Filter_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 4, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_RxOverflow_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 5, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_CmdBusy_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 6, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_LogTO_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 7, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_SockActivityTO_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 8, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_FPGAComTO_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 9, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_SockConfigTO_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 10, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_SockDiscon_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 11, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_WcfSM_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 12, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_TxMsgsPending_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 13, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Ethernet_DAQ_Report_neoVI_Index, 0)
extern int DB_neoVI_Status_Update_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Type; /// Min: 0 Max: 255 Units: 
    BYTE Type_raw;
    double ChangeCount; /// Min: 0 Max: 255 Units: 
    BYTE ChangeCount_raw;
} DB_neoVI_Status_Update_neoVI;


void DB_neoVI_Status_Update_neoVI_Init(DB_neoVI_Status_Update_neoVI * pMsg);
int DB_neoVI_Status_Update_neoVI_Transmit(DB_neoVI_Status_Update_neoVI * pMsg);
int DB_neoVI_Status_Update_neoVI_Transmit_raw(DB_neoVI_Status_Update_neoVI * pMsg);
int DB_neoVI_Status_Update_neoVI_UpdateBytesFromSignals(DB_neoVI_Status_Update_neoVI * pMsg);
int DB_neoVI_Status_Update_neoVI_UpdateBytesFromRawSignals(DB_neoVI_Status_Update_neoVI * pMsg);
#define DB_neoVI_Status_Update_neoVI_Type_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Status_Update_neoVI_Index, 0, dPhysicalValue);
#define DB_neoVI_Status_Update_neoVI_ChangeCount_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Status_Update_neoVI_Index, 1, dPhysicalValue);
#define DB_neoVI_Status_Update_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_neoVI_Status_Update_neoVI_Index, 0)
extern int DB_Scc_Status_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double FvA; /// Min: 0 Max: 1 Units: 
    BYTE FvA_raw;
    double ScA; /// Min: 0 Max: 1 Units: 
    BYTE ScA_raw;
    double Atv; /// Min: 0 Max: 1 Units: 
    BYTE Atv_raw;
    double sip; /// Min: 0 Max: 1 Units: 
    BYTE sip_raw;
    double pt; /// Min: 0 Max: 4294967295 Units: 
    DWORD pt_raw;
    double Req; /// Min: 0 Max: 255 Units: 
    BYTE Req_raw;
} DB_Scc_Status_neoVI;


void DB_Scc_Status_neoVI_Init(DB_Scc_Status_neoVI * pMsg);
int DB_Scc_Status_neoVI_Transmit(DB_Scc_Status_neoVI * pMsg);
int DB_Scc_Status_neoVI_Transmit_raw(DB_Scc_Status_neoVI * pMsg);
int DB_Scc_Status_neoVI_UpdateBytesFromSignals(DB_Scc_Status_neoVI * pMsg);
int DB_Scc_Status_neoVI_UpdateBytesFromRawSignals(DB_Scc_Status_neoVI * pMsg);
#define DB_Scc_Status_neoVI_FvA_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Scc_Status_neoVI_Index, 0, dPhysicalValue);
#define DB_Scc_Status_neoVI_ScA_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Scc_Status_neoVI_Index, 1, dPhysicalValue);
#define DB_Scc_Status_neoVI_Atv_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Scc_Status_neoVI_Index, 2, dPhysicalValue);
#define DB_Scc_Status_neoVI_sip_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Scc_Status_neoVI_Index, 3, dPhysicalValue);
#define DB_Scc_Status_neoVI_pt_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Scc_Status_neoVI_Index, 4, dPhysicalValue);
#define DB_Scc_Status_neoVI_Req_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Scc_Status_neoVI_Index, 5, dPhysicalValue);
#define DB_Scc_Status_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Scc_Status_neoVI_Index, 0)
extern int DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double PWM1_IN; /// Min: 0 Max: 1 Units: 
    BYTE PWM1_IN_raw;
    double PWM2_IN; /// Min: 0 Max: 1 Units: 
    BYTE PWM2_IN_raw;
    double PWM3_IN; /// Min: 0 Max: 1 Units: 
    BYTE PWM3_IN_raw;
    double PWM4_IN; /// Min: 0 Max: 1 Units: 
    BYTE PWM4_IN_raw;
    double PWM5_IN; /// Min: 0 Max: 1 Units: 
    BYTE PWM5_IN_raw;
    double PWM6_IN; /// Min: 0 Max: 1 Units: 
    BYTE PWM6_IN_raw;
    double PWM7_IN; /// Min: 0 Max: 1 Units: 
    BYTE PWM7_IN_raw;
    double PWM8_IN; /// Min: 0 Max: 1 Units: 
    BYTE PWM8_IN_raw;
} DB_Report_Message__Analog_Card_PWM_Inputs__neoVI;


void DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Init(DB_Report_Message__Analog_Card_PWM_Inputs__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM_Inputs__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM_Inputs__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM_Inputs__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM_Inputs__neoVI * pMsg);
#define DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_PWM1_IN_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_PWM2_IN_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_PWM3_IN_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, 2, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_PWM4_IN_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, 3, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_PWM5_IN_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, 4, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_PWM6_IN_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, 5, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_PWM7_IN_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, 6, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_PWM8_IN_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, 7, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, 0)
extern int DB_Report_Message__Analog_Card_PWM1__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Pulse_Width_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Pulse_Width_ms__raw;
    double Period_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Period_ms__raw;
} DB_Report_Message__Analog_Card_PWM1__neoVI;


void DB_Report_Message__Analog_Card_PWM1__neoVI_Init(DB_Report_Message__Analog_Card_PWM1__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM1__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM1__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM1__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM1__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM1__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM1__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM1__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM1__neoVI * pMsg);
#define DB_Report_Message__Analog_Card_PWM1__neoVI_Pulse_Width_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM1__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM1__neoVI_Period_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM1__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM1__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__Analog_Card_PWM1__neoVI_Index, 0)
extern int DB_Report_Message__Analog_Card_PWM2__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Pulse_Width_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Pulse_Width_ms__raw;
    double Period_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Period_ms__raw;
} DB_Report_Message__Analog_Card_PWM2__neoVI;


void DB_Report_Message__Analog_Card_PWM2__neoVI_Init(DB_Report_Message__Analog_Card_PWM2__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM2__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM2__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM2__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM2__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM2__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM2__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM2__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM2__neoVI * pMsg);
#define DB_Report_Message__Analog_Card_PWM2__neoVI_Pulse_Width_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM2__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM2__neoVI_Period_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM2__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM2__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__Analog_Card_PWM2__neoVI_Index, 0)
extern int DB_Report_Message__Analog_Card_PWM3__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Pulse_Width_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Pulse_Width_ms__raw;
    double Period_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Period_ms__raw;
} DB_Report_Message__Analog_Card_PWM3__neoVI;


void DB_Report_Message__Analog_Card_PWM3__neoVI_Init(DB_Report_Message__Analog_Card_PWM3__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM3__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM3__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM3__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM3__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM3__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM3__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM3__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM3__neoVI * pMsg);
#define DB_Report_Message__Analog_Card_PWM3__neoVI_Pulse_Width_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM3__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM3__neoVI_Period_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM3__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM3__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__Analog_Card_PWM3__neoVI_Index, 0)
extern int DB_Report_Message__Analog_Card_PWM4__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Pulse_Width_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Pulse_Width_ms__raw;
    double Period_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Period_ms__raw;
} DB_Report_Message__Analog_Card_PWM4__neoVI;


void DB_Report_Message__Analog_Card_PWM4__neoVI_Init(DB_Report_Message__Analog_Card_PWM4__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM4__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM4__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM4__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM4__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM4__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM4__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM4__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM4__neoVI * pMsg);
#define DB_Report_Message__Analog_Card_PWM4__neoVI_Pulse_Width_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM4__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM4__neoVI_Period_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM4__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM4__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__Analog_Card_PWM4__neoVI_Index, 0)
extern int DB_Report_Message__Analog_Card_PWM5__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Pulse_Width_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Pulse_Width_ms__raw;
    double Period_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Period_ms__raw;
} DB_Report_Message__Analog_Card_PWM5__neoVI;


void DB_Report_Message__Analog_Card_PWM5__neoVI_Init(DB_Report_Message__Analog_Card_PWM5__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM5__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM5__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM5__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM5__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM5__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM5__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM5__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM5__neoVI * pMsg);
#define DB_Report_Message__Analog_Card_PWM5__neoVI_Pulse_Width_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM5__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM5__neoVI_Period_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM5__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM5__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__Analog_Card_PWM5__neoVI_Index, 0)
extern int DB_Report_Message__Analog_Card_PWM6__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Pulse_Width_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Pulse_Width_ms__raw;
    double Period_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Period_ms__raw;
} DB_Report_Message__Analog_Card_PWM6__neoVI;


void DB_Report_Message__Analog_Card_PWM6__neoVI_Init(DB_Report_Message__Analog_Card_PWM6__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM6__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM6__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM6__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM6__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM6__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM6__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM6__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM6__neoVI * pMsg);
#define DB_Report_Message__Analog_Card_PWM6__neoVI_Pulse_Width_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM6__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM6__neoVI_Period_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM6__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM6__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__Analog_Card_PWM6__neoVI_Index, 0)
extern int DB_Report_Message__Analog_Card_PWM7__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Pulse_Width_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Pulse_Width_ms__raw;
    double Period_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Period_ms__raw;
} DB_Report_Message__Analog_Card_PWM7__neoVI;


void DB_Report_Message__Analog_Card_PWM7__neoVI_Init(DB_Report_Message__Analog_Card_PWM7__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM7__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM7__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM7__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM7__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM7__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM7__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM7__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM7__neoVI * pMsg);
#define DB_Report_Message__Analog_Card_PWM7__neoVI_Pulse_Width_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM7__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM7__neoVI_Period_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM7__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM7__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__Analog_Card_PWM7__neoVI_Index, 0)
extern int DB_Report_Message__Analog_Card_PWM8__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Pulse_Width_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Pulse_Width_ms__raw;
    double Period_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Period_ms__raw;
} DB_Report_Message__Analog_Card_PWM8__neoVI;


void DB_Report_Message__Analog_Card_PWM8__neoVI_Init(DB_Report_Message__Analog_Card_PWM8__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM8__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM8__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM8__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM8__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM8__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM8__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM8__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM8__neoVI * pMsg);
#define DB_Report_Message__Analog_Card_PWM8__neoVI_Pulse_Width_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM8__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM8__neoVI_Period_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM8__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM8__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__Analog_Card_PWM8__neoVI_Index, 0)
extern int DB_neoVI_Device_Status_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double HID_Temperature__C_; /// Min: 0 Max: 255.99609375 Units: deg C
    WORD HID_Temperature__C__raw;
    double HID_Bus_Voltage__V_; /// Min: 0 Max: 255.99609375 Units: V
    WORD HID_Bus_Voltage__V__raw;
    double VNET_Temperature__C_; /// Min: 0 Max: 255.99609375 Units: deg C
    WORD VNET_Temperature__C__raw;
    double VNET_Bus_Voltage__V_; /// Min: 0 Max: 255.99609375 Units: V
    WORD VNET_Bus_Voltage__V__raw;
} DB_neoVI_Device_Status_neoVI;


void DB_neoVI_Device_Status_neoVI_Init(DB_neoVI_Device_Status_neoVI * pMsg);
int DB_neoVI_Device_Status_neoVI_Transmit(DB_neoVI_Device_Status_neoVI * pMsg);
int DB_neoVI_Device_Status_neoVI_Transmit_raw(DB_neoVI_Device_Status_neoVI * pMsg);
int DB_neoVI_Device_Status_neoVI_UpdateBytesFromSignals(DB_neoVI_Device_Status_neoVI * pMsg);
int DB_neoVI_Device_Status_neoVI_UpdateBytesFromRawSignals(DB_neoVI_Device_Status_neoVI * pMsg);
#define DB_neoVI_Device_Status_neoVI_HID_Temperature__C__PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_Index, 0, dPhysicalValue);
#define DB_neoVI_Device_Status_neoVI_HID_Bus_Voltage__V__PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_Index, 1, dPhysicalValue);
#define DB_neoVI_Device_Status_neoVI_VNET_Temperature__C__PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_Index, 2, dPhysicalValue);
#define DB_neoVI_Device_Status_neoVI_VNET_Bus_Voltage__V__PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_Index, 3, dPhysicalValue);
#define DB_neoVI_Device_Status_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_neoVI_Device_Status_neoVI_Index, 0)
extern int DB_neoVI_Device_Status_2_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Disk_Space_Avail__WiVI__KB; /// Min: 0 Max: 4294967295 Units: KB
    DWORD Disk_Space_Avail__WiVI__KB_raw;
    double Power_Supply_Voltage; /// Min: 0 Max: 255.99609375 Units: V
    WORD Power_Supply_Voltage_raw;
    double Temperature__C_; /// Min: 0 Max: 255.99609375 Units: deg C
    WORD Temperature__C__raw;
} DB_neoVI_Device_Status_2_neoVI;


void DB_neoVI_Device_Status_2_neoVI_Init(DB_neoVI_Device_Status_2_neoVI * pMsg);
int DB_neoVI_Device_Status_2_neoVI_Transmit(DB_neoVI_Device_Status_2_neoVI * pMsg);
int DB_neoVI_Device_Status_2_neoVI_Transmit_raw(DB_neoVI_Device_Status_2_neoVI * pMsg);
int DB_neoVI_Device_Status_2_neoVI_UpdateBytesFromSignals(DB_neoVI_Device_Status_2_neoVI * pMsg);
int DB_neoVI_Device_Status_2_neoVI_UpdateBytesFromRawSignals(DB_neoVI_Device_Status_2_neoVI * pMsg);
#define DB_neoVI_Device_Status_2_neoVI_Disk_Space_Avail__WiVI__KB_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Device_Status_2_neoVI_Index, 0, dPhysicalValue);
#define DB_neoVI_Device_Status_2_neoVI_Power_Supply_Voltage_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Device_Status_2_neoVI_Index, 1, dPhysicalValue);
#define DB_neoVI_Device_Status_2_neoVI_Temperature__C__PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Device_Status_2_neoVI_Index, 2, dPhysicalValue);
#define DB_neoVI_Device_Status_2_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_neoVI_Device_Status_2_neoVI_Index, 0)
extern int DB_Trace_Logger_Status_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double State; /// Min: 0 Max: 8 Units: 
    BYTE State_raw;
    double Debug_Level; /// Min: 0 Max: 3 Units: 
    BYTE Debug_Level_raw;
    double IP_MSB_; /// Min: 0 Max: 255 Units: 
    BYTE IP_MSB__raw;
    double IP; /// Min: 0 Max: 255 Units: 
    BYTE IP_raw;
    double IP_sig4; /// Min: 0 Max: 255 Units: 
    BYTE IP_sig4_raw;
    double IP_LSB_; /// Min: 0 Max: 255 Units: 
    BYTE IP_LSB__raw;
    double Port; /// Min: 0 Max: 65535 Units: 
    WORD Port_raw;
} DB_Trace_Logger_Status_neoVI;

#pragma warning(disable : 4005)
#define DB_Trace_Logger_Status_neoVI_$_State_$$_Direct_Connect 1
#define DB_Trace_Logger_Status_neoVI_$_State_$$_Connecting 2
#define DB_Trace_Logger_Status_neoVI_$_State_$$_Reconnecting 3
#define DB_Trace_Logger_Status_neoVI_$_State_$$_Connected 4
#define DB_Trace_Logger_Status_neoVI_$_State_$$_Set_Debug_Level 5
#define DB_Trace_Logger_Status_neoVI_$_State_$$_Closing 6
#define DB_Trace_Logger_Status_neoVI_$_State_$$_Closed 7
#define DB_Trace_Logger_Status_neoVI_$_State_$$_Timestamp 8
#pragma warning(default : 4005)

void DB_Trace_Logger_Status_neoVI_Init(DB_Trace_Logger_Status_neoVI * pMsg);
int DB_Trace_Logger_Status_neoVI_Transmit(DB_Trace_Logger_Status_neoVI * pMsg);
int DB_Trace_Logger_Status_neoVI_Transmit_raw(DB_Trace_Logger_Status_neoVI * pMsg);
int DB_Trace_Logger_Status_neoVI_UpdateBytesFromSignals(DB_Trace_Logger_Status_neoVI * pMsg);
int DB_Trace_Logger_Status_neoVI_UpdateBytesFromRawSignals(DB_Trace_Logger_Status_neoVI * pMsg);
#define DB_Trace_Logger_Status_neoVI_State_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, 0, dPhysicalValue);
#define DB_Trace_Logger_Status_neoVI_Debug_Level_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, 1, dPhysicalValue);
#define DB_Trace_Logger_Status_neoVI_IP_MSB__PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, 2, dPhysicalValue);
#define DB_Trace_Logger_Status_neoVI_IP_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, 3, dPhysicalValue);
#define DB_Trace_Logger_Status_neoVI_IP_sig4_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, 4, dPhysicalValue);
#define DB_Trace_Logger_Status_neoVI_IP_LSB__PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, 5, dPhysicalValue);
#define DB_Trace_Logger_Status_neoVI_Port_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, 6, dPhysicalValue);
#define DB_Trace_Logger_Status_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Trace_Logger_Status_neoVI_Index, 0)
extern int DB_Trigger_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Logger_triggered; /// Min: 0 Max: 2 Units: 
    BYTE Logger_triggered_raw;
    double Pre_trigger_size; /// Min: 0 Max: 4294967295 Units: 
    DWORD Pre_trigger_size_raw;
    double Collection_index; /// Min: 0 Max: 255 Units: 
    BYTE Collection_index_raw;
} DB_Trigger_neoVI;

#pragma warning(disable : 4005)
#define DB_Trigger_neoVI_$_Logger_triggered_$$_NO_TRG 0
#define DB_Trigger_neoVI_$_Logger_triggered_$$_TRG_msg_ 1
#define DB_Trigger_neoVI_$_Logger_triggered_$$_TRG_ms_ 2
#pragma warning(default : 4005)

void DB_Trigger_neoVI_Init(DB_Trigger_neoVI * pMsg);
int DB_Trigger_neoVI_Transmit(DB_Trigger_neoVI * pMsg);
int DB_Trigger_neoVI_Transmit_raw(DB_Trigger_neoVI * pMsg);
int DB_Trigger_neoVI_UpdateBytesFromSignals(DB_Trigger_neoVI * pMsg);
int DB_Trigger_neoVI_UpdateBytesFromRawSignals(DB_Trigger_neoVI * pMsg);
#define DB_Trigger_neoVI_Logger_triggered_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Trigger_neoVI_Index, 0, dPhysicalValue);
#define DB_Trigger_neoVI_Pre_trigger_size_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Trigger_neoVI_Index, 1, dPhysicalValue);
#define DB_Trigger_neoVI_Collection_index_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Trigger_neoVI_Index, 2, dPhysicalValue);
#define DB_Trigger_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Trigger_neoVI_Index, 0)
extern int DB_Exterior_Lighting_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double AdvFrntLghtSysEnbld; /// Min: 0 Max: 1 Units: 
    BYTE AdvFrntLghtSysEnbld_raw;
    double AutLghtCtrl; /// Min: 0 Max: 1 Units: 
    BYTE AutLghtCtrl_raw;
    double AutoBmSlctAllwd; /// Min: 0 Max: 1 Units: 
    BYTE AutoBmSlctAllwd_raw;
    double AutoLtsActIO; /// Min: 0 Max: 1 Units: 
    BYTE AutoLtsActIO_raw;
    double AutoLtsInactIO; /// Min: 0 Max: 1 Units: 
    BYTE AutoLtsInactIO_raw;
    double BrkLtsAtv; /// Min: 0 Max: 1 Units: 
    BYTE BrkLtsAtv_raw;
    double DRLAct; /// Min: 0 Max: 1 Units: 
    BYTE DRLAct_raw;
    double DispNtSchmAtv; /// Min: 0 Max: 1 Units: 
    BYTE DispNtSchmAtv_raw;
    double FlToPsSwAtv; /// Min: 0 Max: 1 Units: 
    BYTE FlToPsSwAtv_raw;
    double FrFogLmpsAct; /// Min: 0 Max: 1 Units: 
    BYTE FrFogLmpsAct_raw;
    double FrFgLtIO; /// Min: 0 Max: 1 Units: 
    BYTE FrFgLtIO_raw;
    double HazSwAtv; /// Min: 0 Max: 1 Units: 
    BYTE HazSwAtv_raw;
    double HdlmpBmSelectStat; /// Min: 0 Max: 3 Units: 
    BYTE HdlmpBmSelectStat_raw;
    double HighBmAct; /// Min: 0 Max: 1 Units: 
    BYTE HighBmAct_raw;
    double HiBmIO; /// Min: 0 Max: 1 Units: 
    BYTE HiBmIO_raw;
    double HiBmReqd; /// Min: 0 Max: 1 Units: 
    BYTE HiBmReqd_raw;
    double IntDimDspLvl; /// Min: 0 Max: 127 Units: 
    BYTE IntDimDspLvl_raw;
    double IntDimLvl; /// Min: 0 Max: 127 Units: 
    BYTE IntDimLvl_raw;
    double IntDimNtPnlAtv; /// Min: 0 Max: 1 Units: 
    BYTE IntDimNtPnlAtv_raw;
    double LftTrnLmpAtv; /// Min: 0 Max: 3 Units: 
    BYTE LftTrnLmpAtv_raw;
    double LowBmAct; /// Min: 0 Max: 1 Units: 
    BYTE LowBmAct_raw;
    double MainLghtSw; /// Min: 0 Max: 3 Units: 
    BYTE MainLghtSw_raw;
    double OtsdAmbtLtLvlStat; /// Min: 0 Max: 3 Units: 
    BYTE OtsdAmbtLtLvlStat_raw;
    double OtsdAmbtLtLvlStatV; /// Min: 0 Max: 1 Units: 
    BYTE OtsdAmbtLtLvlStatV_raw;
    double PrkLtIO; /// Min: 0 Max: 1 Units: 
    BYTE PrkLtIO_raw;
    double PrkLtLeftIO; /// Min: 0 Max: 1 Units: 
    BYTE PrkLtLeftIO_raw;
    double PrkLtRightIO; /// Min: 0 Max: 1 Units: 
    BYTE PrkLtRightIO_raw;
    double RrFogLmpsAct; /// Min: 0 Max: 1 Units: 
    BYTE RrFogLmpsAct_raw;
    double RrFgLtIO; /// Min: 0 Max: 1 Units: 
    BYTE RrFgLtIO_raw;
    double RevLmpAtv; /// Min: 0 Max: 1 Units: 
    BYTE RevLmpAtv_raw;
    double RtTrnLmpAtv; /// Min: 0 Max: 3 Units: 
    BYTE RtTrnLmpAtv_raw;
    double TrnSwAct; /// Min: 0 Max: 3 Units: 
    BYTE TrnSwAct_raw;
} DB_Exterior_Lighting_HS_CAN;

#pragma warning(disable : 4005)
#define DB_Exterior_Lighting_HS_CAN_$_AdvFrntLghtSysEnbld_$$_False 0
#define DB_Exterior_Lighting_HS_CAN_$_AdvFrntLghtSysEnbld_$$_True 1
#define DB_Exterior_Lighting_HS_CAN_$_AutLghtCtrl_$$_False 0
#define DB_Exterior_Lighting_HS_CAN_$_AutLghtCtrl_$$_True 1
#define DB_Exterior_Lighting_HS_CAN_$_AutoBmSlctAllwd_$$_False 0
#define DB_Exterior_Lighting_HS_CAN_$_AutoBmSlctAllwd_$$_True 1
#define DB_Exterior_Lighting_HS_CAN_$_AutoLtsActIO_$$_False 0
#define DB_Exterior_Lighting_HS_CAN_$_AutoLtsActIO_$$_True 1
#define DB_Exterior_Lighting_HS_CAN_$_AutoLtsInactIO_$$_False 0
#define DB_Exterior_Lighting_HS_CAN_$_AutoLtsInactIO_$$_True 1
#define DB_Exterior_Lighting_HS_CAN_$_BrkLtsAtv_$$_False 0
#define DB_Exterior_Lighting_HS_CAN_$_BrkLtsAtv_$$_True 1
#define DB_Exterior_Lighting_HS_CAN_$_DRLAct_$$_False 0
#define DB_Exterior_Lighting_HS_CAN_$_DRLAct_$$_True 1
#define DB_Exterior_Lighting_HS_CAN_$_DispNtSchmAtv_$$_False 0
#define DB_Exterior_Lighting_HS_CAN_$_DispNtSchmAtv_$$_True 1
#define DB_Exterior_Lighting_HS_CAN_$_FlToPsSwAtv_$$_False 0
#define DB_Exterior_Lighting_HS_CAN_$_FlToPsSwAtv_$$_True 1
#define DB_Exterior_Lighting_HS_CAN_$_FrFogLmpsAct_$$_False 0
#define DB_Exterior_Lighting_HS_CAN_$_FrFogLmpsAct_$$_True 1
#define DB_Exterior_Lighting_HS_CAN_$_FrFgLtIO_$$_False 0
#define DB_Exterior_Lighting_HS_CAN_$_FrFgLtIO_$$_True 1
#define DB_Exterior_Lighting_HS_CAN_$_HazSwAtv_$$_False 0
#define DB_Exterior_Lighting_HS_CAN_$_HazSwAtv_$$_True 1
#define DB_Exterior_Lighting_HS_CAN_$_HdlmpBmSelectStat_$$_Unknown 0
#define DB_Exterior_Lighting_HS_CAN_$_HdlmpBmSelectStat_$$_Low_Beams 1
#define DB_Exterior_Lighting_HS_CAN_$_HdlmpBmSelectStat_$$_High_Beams 2
#define DB_Exterior_Lighting_HS_CAN_$_HighBmAct_$$_False 0
#define DB_Exterior_Lighting_HS_CAN_$_HighBmAct_$$_True 1
#define DB_Exterior_Lighting_HS_CAN_$_HiBmIO_$$_False 0
#define DB_Exterior_Lighting_HS_CAN_$_HiBmIO_$$_True 1
#define DB_Exterior_Lighting_HS_CAN_$_HiBmReqd_$$_False 0
#define DB_Exterior_Lighting_HS_CAN_$_HiBmReqd_$$_True 1
#define DB_Exterior_Lighting_HS_CAN_$_IntDimNtPnlAtv_$$_False 0
#define DB_Exterior_Lighting_HS_CAN_$_IntDimNtPnlAtv_$$_True 1
#define DB_Exterior_Lighting_HS_CAN_$_LftTrnLmpAtv_$$_Off 0
#define DB_Exterior_Lighting_HS_CAN_$_LftTrnLmpAtv_$$_On_without_telltale 1
#define DB_Exterior_Lighting_HS_CAN_$_LftTrnLmpAtv_$$_On_with_telltale 2
#define DB_Exterior_Lighting_HS_CAN_$_LowBmAct_$$_False 0
#define DB_Exterior_Lighting_HS_CAN_$_LowBmAct_$$_True 1
#define DB_Exterior_Lighting_HS_CAN_$_MainLghtSw_$$_AUTO 0
#define DB_Exterior_Lighting_HS_CAN_$_MainLghtSw_$$_OFF 1
#define DB_Exterior_Lighting_HS_CAN_$_MainLghtSw_$$_PARKLAMP 2
#define DB_Exterior_Lighting_HS_CAN_$_MainLghtSw_$$_HEADLAMP 3
#define DB_Exterior_Lighting_HS_CAN_$_OtsdAmbtLtLvlStat_$$_Unknown 0
#define DB_Exterior_Lighting_HS_CAN_$_OtsdAmbtLtLvlStat_$$_Night 1
#define DB_Exterior_Lighting_HS_CAN_$_OtsdAmbtLtLvlStat_$$_Day 2
#define DB_Exterior_Lighting_HS_CAN_$_OtsdAmbtLtLvlStatV_$$_Valid 0
#define DB_Exterior_Lighting_HS_CAN_$_OtsdAmbtLtLvlStatV_$$_Invalid 1
#define DB_Exterior_Lighting_HS_CAN_$_PrkLtIO_$$_False 0
#define DB_Exterior_Lighting_HS_CAN_$_PrkLtIO_$$_True 1
#define DB_Exterior_Lighting_HS_CAN_$_PrkLtLeftIO_$$_False 0
#define DB_Exterior_Lighting_HS_CAN_$_PrkLtLeftIO_$$_True 1
#define DB_Exterior_Lighting_HS_CAN_$_PrkLtRightIO_$$_False 0
#define DB_Exterior_Lighting_HS_CAN_$_PrkLtRightIO_$$_True 1
#define DB_Exterior_Lighting_HS_CAN_$_RrFogLmpsAct_$$_False 0
#define DB_Exterior_Lighting_HS_CAN_$_RrFogLmpsAct_$$_True 1
#define DB_Exterior_Lighting_HS_CAN_$_RrFgLtIO_$$_False 0
#define DB_Exterior_Lighting_HS_CAN_$_RrFgLtIO_$$_True 1
#define DB_Exterior_Lighting_HS_CAN_$_RevLmpAtv_$$_False 0
#define DB_Exterior_Lighting_HS_CAN_$_RevLmpAtv_$$_True 1
#define DB_Exterior_Lighting_HS_CAN_$_RtTrnLmpAtv_$$_Off 0
#define DB_Exterior_Lighting_HS_CAN_$_RtTrnLmpAtv_$$_On_without_telltale 1
#define DB_Exterior_Lighting_HS_CAN_$_RtTrnLmpAtv_$$_On_with_telltale 2
#define DB_Exterior_Lighting_HS_CAN_$_TrnSwAct_$$_No_Activation 0
#define DB_Exterior_Lighting_HS_CAN_$_TrnSwAct_$$_Left 1
#define DB_Exterior_Lighting_HS_CAN_$_TrnSwAct_$$_Right 2
#pragma warning(default : 4005)

void DB_Exterior_Lighting_HS_CAN_Init(DB_Exterior_Lighting_HS_CAN * pMsg);
int DB_Exterior_Lighting_HS_CAN_Transmit(DB_Exterior_Lighting_HS_CAN * pMsg);
int DB_Exterior_Lighting_HS_CAN_Transmit_raw(DB_Exterior_Lighting_HS_CAN * pMsg);
int DB_Exterior_Lighting_HS_CAN_UpdateBytesFromSignals(DB_Exterior_Lighting_HS_CAN * pMsg);
int DB_Exterior_Lighting_HS_CAN_UpdateBytesFromRawSignals(DB_Exterior_Lighting_HS_CAN * pMsg);
#define DB_Exterior_Lighting_HS_CAN_AdvFrntLghtSysEnbld_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Exterior_Lighting_HS_CAN_Index, 0, dPhysicalValue);
#define DB_Exterior_Lighting_HS_CAN_AutLghtCtrl_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Exterior_Lighting_HS_CAN_Index, 1, dPhysicalValue);
#define DB_Exterior_Lighting_HS_CAN_AutoBmSlctAllwd_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Exterior_Lighting_HS_CAN_Index, 2, dPhysicalValue);
#define DB_Exterior_Lighting_HS_CAN_AutoLtsActIO_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Exterior_Lighting_HS_CAN_Index, 3, dPhysicalValue);
#define DB_Exterior_Lighting_HS_CAN_AutoLtsInactIO_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Exterior_Lighting_HS_CAN_Index, 4, dPhysicalValue);
#define DB_Exterior_Lighting_HS_CAN_BrkLtsAtv_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Exterior_Lighting_HS_CAN_Index, 5, dPhysicalValue);
#define DB_Exterior_Lighting_HS_CAN_DRLAct_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Exterior_Lighting_HS_CAN_Index, 6, dPhysicalValue);
#define DB_Exterior_Lighting_HS_CAN_DispNtSchmAtv_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Exterior_Lighting_HS_CAN_Index, 7, dPhysicalValue);
#define DB_Exterior_Lighting_HS_CAN_FlToPsSwAtv_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Exterior_Lighting_HS_CAN_Index, 8, dPhysicalValue);
#define DB_Exterior_Lighting_HS_CAN_FrFogLmpsAct_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Exterior_Lighting_HS_CAN_Index, 9, dPhysicalValue);
#define DB_Exterior_Lighting_HS_CAN_FrFgLtIO_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Exterior_Lighting_HS_CAN_Index, 10, dPhysicalValue);
#define DB_Exterior_Lighting_HS_CAN_HazSwAtv_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Exterior_Lighting_HS_CAN_Index, 11, dPhysicalValue);
#define DB_Exterior_Lighting_HS_CAN_HdlmpBmSelectStat_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Exterior_Lighting_HS_CAN_Index, 12, dPhysicalValue);
#define DB_Exterior_Lighting_HS_CAN_HighBmAct_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Exterior_Lighting_HS_CAN_Index, 13, dPhysicalValue);
#define DB_Exterior_Lighting_HS_CAN_HiBmIO_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Exterior_Lighting_HS_CAN_Index, 14, dPhysicalValue);
#define DB_Exterior_Lighting_HS_CAN_HiBmReqd_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Exterior_Lighting_HS_CAN_Index, 15, dPhysicalValue);
#define DB_Exterior_Lighting_HS_CAN_IntDimDspLvl_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Exterior_Lighting_HS_CAN_Index, 16, dPhysicalValue);
#define DB_Exterior_Lighting_HS_CAN_IntDimLvl_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Exterior_Lighting_HS_CAN_Index, 17, dPhysicalValue);
#define DB_Exterior_Lighting_HS_CAN_IntDimNtPnlAtv_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Exterior_Lighting_HS_CAN_Index, 18, dPhysicalValue);
#define DB_Exterior_Lighting_HS_CAN_LftTrnLmpAtv_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Exterior_Lighting_HS_CAN_Index, 19, dPhysicalValue);
#define DB_Exterior_Lighting_HS_CAN_LowBmAct_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Exterior_Lighting_HS_CAN_Index, 20, dPhysicalValue);
#define DB_Exterior_Lighting_HS_CAN_MainLghtSw_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Exterior_Lighting_HS_CAN_Index, 21, dPhysicalValue);
#define DB_Exterior_Lighting_HS_CAN_OtsdAmbtLtLvlStat_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Exterior_Lighting_HS_CAN_Index, 22, dPhysicalValue);
#define DB_Exterior_Lighting_HS_CAN_OtsdAmbtLtLvlStatV_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Exterior_Lighting_HS_CAN_Index, 23, dPhysicalValue);
#define DB_Exterior_Lighting_HS_CAN_PrkLtIO_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Exterior_Lighting_HS_CAN_Index, 24, dPhysicalValue);
#define DB_Exterior_Lighting_HS_CAN_PrkLtLeftIO_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Exterior_Lighting_HS_CAN_Index, 25, dPhysicalValue);
#define DB_Exterior_Lighting_HS_CAN_PrkLtRightIO_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Exterior_Lighting_HS_CAN_Index, 26, dPhysicalValue);
#define DB_Exterior_Lighting_HS_CAN_RrFogLmpsAct_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Exterior_Lighting_HS_CAN_Index, 27, dPhysicalValue);
#define DB_Exterior_Lighting_HS_CAN_RrFgLtIO_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Exterior_Lighting_HS_CAN_Index, 28, dPhysicalValue);
#define DB_Exterior_Lighting_HS_CAN_RevLmpAtv_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Exterior_Lighting_HS_CAN_Index, 29, dPhysicalValue);
#define DB_Exterior_Lighting_HS_CAN_RtTrnLmpAtv_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Exterior_Lighting_HS_CAN_Index, 30, dPhysicalValue);
#define DB_Exterior_Lighting_HS_CAN_TrnSwAct_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Exterior_Lighting_HS_CAN_Index, 31, dPhysicalValue);
#define DB_Exterior_Lighting_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Exterior_Lighting_HS_CAN_Index, 0)
extern int DB_Front_Seat_Heat_Cool_Control_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double DrvHCSMIndReq; /// Min: 0 Max: 3 Units: 
    BYTE DrvHCSMIndReq_raw;
    double DrvHCSMInd1; /// Min: 0 Max: 1 Units: 
    BYTE DrvHCSMInd1_raw;
    double DrvHCSMInd2; /// Min: 0 Max: 1 Units: 
    BYTE DrvHCSMInd2_raw;
    double DrvHCSMInd3; /// Min: 0 Max: 1 Units: 
    BYTE DrvHCSMInd3_raw;
    double PassHCSMIndReq; /// Min: 0 Max: 3 Units: 
    BYTE PassHCSMIndReq_raw;
    double PassHCSMInd1; /// Min: 0 Max: 1 Units: 
    BYTE PassHCSMInd1_raw;
    double PassHCSMInd2; /// Min: 0 Max: 1 Units: 
    BYTE PassHCSMInd2_raw;
    double PassHCSMInd3; /// Min: 0 Max: 1 Units: 
    BYTE PassHCSMInd3_raw;
} DB_Front_Seat_Heat_Cool_Control_HS_CAN;

#pragma warning(disable : 4005)
#define DB_Front_Seat_Heat_Cool_Control_HS_CAN_$_DrvHCSMIndReq_$$_Off 0
#define DB_Front_Seat_Heat_Cool_Control_HS_CAN_$_DrvHCSMIndReq_$$_Continuous_Indication 1
#define DB_Front_Seat_Heat_Cool_Control_HS_CAN_$_DrvHCSMIndReq_$$_Flash_Rate__1_Indication 2
#define DB_Front_Seat_Heat_Cool_Control_HS_CAN_$_DrvHCSMIndReq_$$_Flash_Rate__2_Indication 3
#define DB_Front_Seat_Heat_Cool_Control_HS_CAN_$_DrvHCSMInd1_$$_False 0
#define DB_Front_Seat_Heat_Cool_Control_HS_CAN_$_DrvHCSMInd1_$$_True 1
#define DB_Front_Seat_Heat_Cool_Control_HS_CAN_$_DrvHCSMInd2_$$_False 0
#define DB_Front_Seat_Heat_Cool_Control_HS_CAN_$_DrvHCSMInd2_$$_True 1
#define DB_Front_Seat_Heat_Cool_Control_HS_CAN_$_DrvHCSMInd3_$$_False 0
#define DB_Front_Seat_Heat_Cool_Control_HS_CAN_$_DrvHCSMInd3_$$_True 1
#define DB_Front_Seat_Heat_Cool_Control_HS_CAN_$_PassHCSMIndReq_$$_Off 0
#define DB_Front_Seat_Heat_Cool_Control_HS_CAN_$_PassHCSMIndReq_$$_Continuous_Indication 1
#define DB_Front_Seat_Heat_Cool_Control_HS_CAN_$_PassHCSMIndReq_$$_Flash_Rate__1_Indication 2
#define DB_Front_Seat_Heat_Cool_Control_HS_CAN_$_PassHCSMIndReq_$$_Flash_Rate__2_Indication 3
#define DB_Front_Seat_Heat_Cool_Control_HS_CAN_$_PassHCSMInd1_$$_False 0
#define DB_Front_Seat_Heat_Cool_Control_HS_CAN_$_PassHCSMInd1_$$_True 1
#define DB_Front_Seat_Heat_Cool_Control_HS_CAN_$_PassHCSMInd2_$$_False 0
#define DB_Front_Seat_Heat_Cool_Control_HS_CAN_$_PassHCSMInd2_$$_True 1
#define DB_Front_Seat_Heat_Cool_Control_HS_CAN_$_PassHCSMInd3_$$_False 0
#define DB_Front_Seat_Heat_Cool_Control_HS_CAN_$_PassHCSMInd3_$$_True 1
#pragma warning(default : 4005)

void DB_Front_Seat_Heat_Cool_Control_HS_CAN_Init(DB_Front_Seat_Heat_Cool_Control_HS_CAN * pMsg);
int DB_Front_Seat_Heat_Cool_Control_HS_CAN_Transmit(DB_Front_Seat_Heat_Cool_Control_HS_CAN * pMsg);
int DB_Front_Seat_Heat_Cool_Control_HS_CAN_Transmit_raw(DB_Front_Seat_Heat_Cool_Control_HS_CAN * pMsg);
int DB_Front_Seat_Heat_Cool_Control_HS_CAN_UpdateBytesFromSignals(DB_Front_Seat_Heat_Cool_Control_HS_CAN * pMsg);
int DB_Front_Seat_Heat_Cool_Control_HS_CAN_UpdateBytesFromRawSignals(DB_Front_Seat_Heat_Cool_Control_HS_CAN * pMsg);
#define DB_Front_Seat_Heat_Cool_Control_HS_CAN_DrvHCSMIndReq_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Front_Seat_Heat_Cool_Control_HS_CAN_Index, 0, dPhysicalValue);
#define DB_Front_Seat_Heat_Cool_Control_HS_CAN_DrvHCSMInd1_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Front_Seat_Heat_Cool_Control_HS_CAN_Index, 1, dPhysicalValue);
#define DB_Front_Seat_Heat_Cool_Control_HS_CAN_DrvHCSMInd2_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Front_Seat_Heat_Cool_Control_HS_CAN_Index, 2, dPhysicalValue);
#define DB_Front_Seat_Heat_Cool_Control_HS_CAN_DrvHCSMInd3_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Front_Seat_Heat_Cool_Control_HS_CAN_Index, 3, dPhysicalValue);
#define DB_Front_Seat_Heat_Cool_Control_HS_CAN_PassHCSMIndReq_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Front_Seat_Heat_Cool_Control_HS_CAN_Index, 4, dPhysicalValue);
#define DB_Front_Seat_Heat_Cool_Control_HS_CAN_PassHCSMInd1_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Front_Seat_Heat_Cool_Control_HS_CAN_Index, 5, dPhysicalValue);
#define DB_Front_Seat_Heat_Cool_Control_HS_CAN_PassHCSMInd2_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Front_Seat_Heat_Cool_Control_HS_CAN_Index, 6, dPhysicalValue);
#define DB_Front_Seat_Heat_Cool_Control_HS_CAN_PassHCSMInd3_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Front_Seat_Heat_Cool_Control_HS_CAN_Index, 7, dPhysicalValue);
#define DB_Front_Seat_Heat_Cool_Control_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Front_Seat_Heat_Cool_Control_HS_CAN_Index, 0)
extern int DB_PPEI_Engine_Environmental_Stat_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double OtsAirTmp; /// Min: -40 Max: 87.5 Units: degC
    BYTE OtsAirTmp_raw;
    double OtsAirTmpCrVal; /// Min: -40 Max: 87.5 Units: degC
    BYTE OtsAirTmpCrVal_raw;
    double OtsAirTmpCrValMsk; /// Min: 0 Max: 1 Units: 
    BYTE OtsAirTmpCrValMsk_raw;
    double OtsAirTmpCrValV; /// Min: 0 Max: 1 Units: 
    BYTE OtsAirTmpCrValV_raw;
    double EngInltSpcfcHmdty; /// Min: 0 Max: 4.999989 Units: %water
    BYTE EngInltSpcfcHmdty_raw;
    double EngInltSpcfcHmdtyM; /// Min: 0 Max: 1 Units: 
    BYTE EngInltSpcfcHmdtyM_raw;
    double EngInltSpcfcHmdtyV; /// Min: 0 Max: 1 Units: 
    BYTE EngInltSpcfcHmdtyV_raw;
    double OtsAirTmpV; /// Min: 0 Max: 1 Units: 
    BYTE OtsAirTmpV_raw;
} DB_PPEI_Engine_Environmental_Stat_HS_CAN;

#pragma warning(disable : 4005)
#define DB_PPEI_Engine_Environmental_Stat_HS_CAN_$_OtsAirTmpCrValMsk_$$_Don_t_Use_Data 0
#define DB_PPEI_Engine_Environmental_Stat_HS_CAN_$_OtsAirTmpCrValMsk_$$_Use_Data 1
#define DB_PPEI_Engine_Environmental_Stat_HS_CAN_$_OtsAirTmpCrValV_$$_Valid 0
#define DB_PPEI_Engine_Environmental_Stat_HS_CAN_$_OtsAirTmpCrValV_$$_Invalid 1
#define DB_PPEI_Engine_Environmental_Stat_HS_CAN_$_EngInltSpcfcHmdtyM_$$_Don_t_Use_Data 0
#define DB_PPEI_Engine_Environmental_Stat_HS_CAN_$_EngInltSpcfcHmdtyM_$$_Use_Data 1
#define DB_PPEI_Engine_Environmental_Stat_HS_CAN_$_EngInltSpcfcHmdtyV_$$_Valid 0
#define DB_PPEI_Engine_Environmental_Stat_HS_CAN_$_EngInltSpcfcHmdtyV_$$_Invalid 1
#define DB_PPEI_Engine_Environmental_Stat_HS_CAN_$_OtsAirTmpV_$$_Valid 0
#define DB_PPEI_Engine_Environmental_Stat_HS_CAN_$_OtsAirTmpV_$$_Invalid 1
#pragma warning(default : 4005)

void DB_PPEI_Engine_Environmental_Stat_HS_CAN_Init(DB_PPEI_Engine_Environmental_Stat_HS_CAN * pMsg);
int DB_PPEI_Engine_Environmental_Stat_HS_CAN_Transmit(DB_PPEI_Engine_Environmental_Stat_HS_CAN * pMsg);
int DB_PPEI_Engine_Environmental_Stat_HS_CAN_Transmit_raw(DB_PPEI_Engine_Environmental_Stat_HS_CAN * pMsg);
int DB_PPEI_Engine_Environmental_Stat_HS_CAN_UpdateBytesFromSignals(DB_PPEI_Engine_Environmental_Stat_HS_CAN * pMsg);
int DB_PPEI_Engine_Environmental_Stat_HS_CAN_UpdateBytesFromRawSignals(DB_PPEI_Engine_Environmental_Stat_HS_CAN * pMsg);
#define DB_PPEI_Engine_Environmental_Stat_HS_CAN_OtsAirTmp_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PPEI_Engine_Environmental_Stat_HS_CAN_Index, 0, dPhysicalValue);
#define DB_PPEI_Engine_Environmental_Stat_HS_CAN_OtsAirTmpCrVal_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PPEI_Engine_Environmental_Stat_HS_CAN_Index, 1, dPhysicalValue);
#define DB_PPEI_Engine_Environmental_Stat_HS_CAN_OtsAirTmpCrValMsk_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PPEI_Engine_Environmental_Stat_HS_CAN_Index, 2, dPhysicalValue);
#define DB_PPEI_Engine_Environmental_Stat_HS_CAN_OtsAirTmpCrValV_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PPEI_Engine_Environmental_Stat_HS_CAN_Index, 3, dPhysicalValue);
#define DB_PPEI_Engine_Environmental_Stat_HS_CAN_EngInltSpcfcHmdty_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PPEI_Engine_Environmental_Stat_HS_CAN_Index, 4, dPhysicalValue);
#define DB_PPEI_Engine_Environmental_Stat_HS_CAN_EngInltSpcfcHmdtyM_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PPEI_Engine_Environmental_Stat_HS_CAN_Index, 5, dPhysicalValue);
#define DB_PPEI_Engine_Environmental_Stat_HS_CAN_EngInltSpcfcHmdtyV_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PPEI_Engine_Environmental_Stat_HS_CAN_Index, 6, dPhysicalValue);
#define DB_PPEI_Engine_Environmental_Stat_HS_CAN_OtsAirTmpV_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PPEI_Engine_Environmental_Stat_HS_CAN_Index, 7, dPhysicalValue);
#define DB_PPEI_Engine_Environmental_Stat_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_PPEI_Engine_Environmental_Stat_HS_CAN_Index, 0)
extern int DB_Instrument_Panel_Sensor_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double IPSnsrSolrAnglFltd; /// Min: 0 Max: 1 Units: 
    BYTE IPSnsrSolrAnglFltd_raw;
    double IPSnsrRwSolrIntFltd; /// Min: 0 Max: 1 Units: 
    BYTE IPSnsrRwSolrIntFltd_raw;
    double IPSnsrRwSolrInt; /// Min: 0 Max: 765 Units: W/m2
    BYTE IPSnsrRwSolrInt_raw;
    double IPSnsrSolrAzmthAngl; /// Min: -180 Max: 330 Units: deg
    BYTE IPSnsrSolrAzmthAngl_raw;
    double IPSnsrSolrElvtnAngl; /// Min: 0 Max: 255 Units: deg
    BYTE IPSnsrSolrElvtnAngl_raw;
} DB_Instrument_Panel_Sensor_HS_CAN;

#pragma warning(disable : 4005)
#define DB_Instrument_Panel_Sensor_HS_CAN_$_IPSnsrSolrAnglFltd_$$_False 0
#define DB_Instrument_Panel_Sensor_HS_CAN_$_IPSnsrSolrAnglFltd_$$_True 1
#define DB_Instrument_Panel_Sensor_HS_CAN_$_IPSnsrRwSolrIntFltd_$$_False 0
#define DB_Instrument_Panel_Sensor_HS_CAN_$_IPSnsrRwSolrIntFltd_$$_True 1
#pragma warning(default : 4005)

void DB_Instrument_Panel_Sensor_HS_CAN_Init(DB_Instrument_Panel_Sensor_HS_CAN * pMsg);
int DB_Instrument_Panel_Sensor_HS_CAN_Transmit(DB_Instrument_Panel_Sensor_HS_CAN * pMsg);
int DB_Instrument_Panel_Sensor_HS_CAN_Transmit_raw(DB_Instrument_Panel_Sensor_HS_CAN * pMsg);
int DB_Instrument_Panel_Sensor_HS_CAN_UpdateBytesFromSignals(DB_Instrument_Panel_Sensor_HS_CAN * pMsg);
int DB_Instrument_Panel_Sensor_HS_CAN_UpdateBytesFromRawSignals(DB_Instrument_Panel_Sensor_HS_CAN * pMsg);
#define DB_Instrument_Panel_Sensor_HS_CAN_IPSnsrSolrAnglFltd_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Instrument_Panel_Sensor_HS_CAN_Index, 0, dPhysicalValue);
#define DB_Instrument_Panel_Sensor_HS_CAN_IPSnsrRwSolrIntFltd_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Instrument_Panel_Sensor_HS_CAN_Index, 1, dPhysicalValue);
#define DB_Instrument_Panel_Sensor_HS_CAN_IPSnsrRwSolrInt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Instrument_Panel_Sensor_HS_CAN_Index, 2, dPhysicalValue);
#define DB_Instrument_Panel_Sensor_HS_CAN_IPSnsrSolrAzmthAngl_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Instrument_Panel_Sensor_HS_CAN_Index, 3, dPhysicalValue);
#define DB_Instrument_Panel_Sensor_HS_CAN_IPSnsrSolrElvtnAngl_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Instrument_Panel_Sensor_HS_CAN_Index, 4, dPhysicalValue);
#define DB_Instrument_Panel_Sensor_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Instrument_Panel_Sensor_HS_CAN_Index, 0)
extern int DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double DistRollCntAvgDrvn; /// Min: 0 Max: 1023.875 Units: m
    WORD DistRollCntAvgDrvn_raw;
    double DstRolCntAvgDrnRstOc; /// Min: 0 Max: 1 Units: 
    BYTE DstRolCntAvgDrnRstOc_raw;
    double DistRollCntAvgDrvnSrc; /// Min: 0 Max: 1 Units: 
    BYTE DistRollCntAvgDrvnSrc_raw;
    double DistRollCntAvgDrvnV; /// Min: 0 Max: 1 Units: 
    BYTE DistRollCntAvgDrvnV_raw;
    double DstRolCntAvgNonDrvn; /// Min: 0 Max: 1023.875 Units: m
    WORD DstRolCntAvgNonDrvn_raw;
    double DstRolCntAvNDrRstOc; /// Min: 0 Max: 1 Units: 
    BYTE DstRolCntAvNDrRstOc_raw;
    double DstRolCntAvgNonDrvnV; /// Min: 0 Max: 1 Units: 
    BYTE DstRolCntAvgNonDrvnV_raw;
    double VehSpdAvgDrvn; /// Min: 0 Max: 511.984375 Units: km/h
    WORD VehSpdAvgDrvn_raw;
    double VehSpdAvgDrvnSrc; /// Min: 0 Max: 1 Units: 
    BYTE VehSpdAvgDrvnSrc_raw;
    double VehSpdAvgDrvnV; /// Min: 0 Max: 1 Units: 
    BYTE VehSpdAvgDrvnV_raw;
    double VehSpdAvgNDrvn; /// Min: 0 Max: 511.984375 Units: km/h
    WORD VehSpdAvgNDrvn_raw;
    double VehSpdAvgNDrvnV; /// Min: 0 Max: 1 Units: 
    BYTE VehSpdAvgNDrvnV_raw;
} DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN;

#pragma warning(disable : 4005)
#define DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_$_DstRolCntAvgDrnRstOc_$$_False 0
#define DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_$_DstRolCntAvgDrnRstOc_$$_True 1
#define DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_$_DistRollCntAvgDrvnSrc_$$_Transmission_Output_Speed 0
#define DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_$_DistRollCntAvgDrvnSrc_$$_Wheel_Speed 1
#define DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_$_DistRollCntAvgDrvnV_$$_Valid 0
#define DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_$_DistRollCntAvgDrvnV_$$_Invalid 1
#define DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_$_DstRolCntAvNDrRstOc_$$_False 0
#define DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_$_DstRolCntAvNDrRstOc_$$_True 1
#define DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_$_DstRolCntAvgNonDrvnV_$$_Valid 0
#define DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_$_DstRolCntAvgNonDrvnV_$$_Invalid 1
#define DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_$_VehSpdAvgDrvnSrc_$$_Transmission_Output_Speed 0
#define DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_$_VehSpdAvgDrvnSrc_$$_Wheel_Speed 1
#define DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_$_VehSpdAvgDrvnV_$$_Valid 0
#define DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_$_VehSpdAvgDrvnV_$$_Invalid 1
#define DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_$_VehSpdAvgNDrvnV_$$_Valid 0
#define DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_$_VehSpdAvgNDrvnV_$$_Invalid 1
#pragma warning(default : 4005)

void DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Init(DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN * pMsg);
int DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Transmit(DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN * pMsg);
int DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Transmit_raw(DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN * pMsg);
int DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_UpdateBytesFromSignals(DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN * pMsg);
int DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_UpdateBytesFromRawSignals(DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN * pMsg);
#define DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_DistRollCntAvgDrvn_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 0, dPhysicalValue);
#define DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_DstRolCntAvgDrnRstOc_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 1, dPhysicalValue);
#define DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_DistRollCntAvgDrvnSrc_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 2, dPhysicalValue);
#define DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_DistRollCntAvgDrvnV_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 3, dPhysicalValue);
#define DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_DstRolCntAvgNonDrvn_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 4, dPhysicalValue);
#define DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_DstRolCntAvNDrRstOc_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 5, dPhysicalValue);
#define DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_DstRolCntAvgNonDrvnV_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 6, dPhysicalValue);
#define DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_VehSpdAvgDrvn_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 7, dPhysicalValue);
#define DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_VehSpdAvgDrvnSrc_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 8, dPhysicalValue);
#define DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_VehSpdAvgDrvnV_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 9, dPhysicalValue);
#define DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_VehSpdAvgNDrvn_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 10, dPhysicalValue);
#define DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_VehSpdAvgNDrvnV_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 11, dPhysicalValue);
#define DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_PPEI_Vehicle_Speed_and_Distanc_HS_CAN_Index, 0)
extern int DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double DgnInf; /// Min: 0 Max: 1.84467440737096e+19 Units: 
    uint64 DgnInf_raw;
} DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN;


void DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN_Init(DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN * pMsg);
int DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN_Transmit(DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN * pMsg);
int DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN_Transmit_raw(DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN * pMsg);
int DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN_UpdateBytesFromSignals(DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN * pMsg);
int DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN_UpdateBytesFromRawSignals(DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN * pMsg);
#define DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN_DgnInf_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN_Index, 0, dPhysicalValue);
#define DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Phy_USDT_Req_to_ECC_F_TestTool_HS_CAN_Index, 0)
extern int DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double DgnInf; /// Min: 0 Max: 1.84467440737096e+19 Units: 
    uint64 DgnInf_raw;
} DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN;


void DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN_Init(DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN * pMsg);
int DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN_Transmit(DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN * pMsg);
int DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN_Transmit_raw(DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN * pMsg);
int DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN_UpdateBytesFromSignals(DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN * pMsg);
int DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN_UpdateBytesFromRawSignals(DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN * pMsg);
#define DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN_DgnInf_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN_Index, 0, dPhysicalValue);
#define DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Phy_USDT_Resp_F_ECC_To_TestToo_HS_CAN_Index, 0)
extern int DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double DgnInf; /// Min: 0 Max: 1.84467440737096e+19 Units: 
    uint64 DgnInf_raw;
} DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN;


void DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN_Init(DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN * pMsg);
int DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN_Transmit(DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN * pMsg);
int DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN_Transmit_raw(DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN * pMsg);
int DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN_UpdateBytesFromSignals(DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN * pMsg);
int DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN_UpdateBytesFromRawSignals(DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN * pMsg);
#define DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN_DgnInf_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN_Index, 0, dPhysicalValue);
#define DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Phy_UUDT_Resp_F_ECC_To_TestToo_HS_CAN_Index, 0)
extern int DB_Front_Seat_Heat_Cool_Switches_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double DrvHCSeatSw1Act; /// Min: 0 Max: 1 Units: 
    BYTE DrvHCSeatSw1Act_raw;
    double DrvHCSeatSw2Act; /// Min: 0 Max: 1 Units: 
    BYTE DrvHCSeatSw2Act_raw;
    double DrvHCSeatSw3Act; /// Min: 0 Max: 1 Units: 
    BYTE DrvHCSeatSw3Act_raw;
    double PassHCSeatSw1Act; /// Min: 0 Max: 1 Units: 
    BYTE PassHCSeatSw1Act_raw;
    double PassHCSeatSw2Act; /// Min: 0 Max: 1 Units: 
    BYTE PassHCSeatSw2Act_raw;
    double PassHCSeatSw3Act; /// Min: 0 Max: 1 Units: 
    BYTE PassHCSeatSw3Act_raw;
} DB_Front_Seat_Heat_Cool_Switches_HS_CAN;

#pragma warning(disable : 4005)
#define DB_Front_Seat_Heat_Cool_Switches_HS_CAN_$_DrvHCSeatSw1Act_$$_False 0
#define DB_Front_Seat_Heat_Cool_Switches_HS_CAN_$_DrvHCSeatSw1Act_$$_True 1
#define DB_Front_Seat_Heat_Cool_Switches_HS_CAN_$_DrvHCSeatSw2Act_$$_False 0
#define DB_Front_Seat_Heat_Cool_Switches_HS_CAN_$_DrvHCSeatSw2Act_$$_True 1
#define DB_Front_Seat_Heat_Cool_Switches_HS_CAN_$_DrvHCSeatSw3Act_$$_False 0
#define DB_Front_Seat_Heat_Cool_Switches_HS_CAN_$_DrvHCSeatSw3Act_$$_True 1
#define DB_Front_Seat_Heat_Cool_Switches_HS_CAN_$_PassHCSeatSw1Act_$$_False 0
#define DB_Front_Seat_Heat_Cool_Switches_HS_CAN_$_PassHCSeatSw1Act_$$_True 1
#define DB_Front_Seat_Heat_Cool_Switches_HS_CAN_$_PassHCSeatSw2Act_$$_False 0
#define DB_Front_Seat_Heat_Cool_Switches_HS_CAN_$_PassHCSeatSw2Act_$$_True 1
#define DB_Front_Seat_Heat_Cool_Switches_HS_CAN_$_PassHCSeatSw3Act_$$_False 0
#define DB_Front_Seat_Heat_Cool_Switches_HS_CAN_$_PassHCSeatSw3Act_$$_True 1
#pragma warning(default : 4005)

void DB_Front_Seat_Heat_Cool_Switches_HS_CAN_Init(DB_Front_Seat_Heat_Cool_Switches_HS_CAN * pMsg);
int DB_Front_Seat_Heat_Cool_Switches_HS_CAN_Transmit(DB_Front_Seat_Heat_Cool_Switches_HS_CAN * pMsg);
int DB_Front_Seat_Heat_Cool_Switches_HS_CAN_Transmit_raw(DB_Front_Seat_Heat_Cool_Switches_HS_CAN * pMsg);
int DB_Front_Seat_Heat_Cool_Switches_HS_CAN_UpdateBytesFromSignals(DB_Front_Seat_Heat_Cool_Switches_HS_CAN * pMsg);
int DB_Front_Seat_Heat_Cool_Switches_HS_CAN_UpdateBytesFromRawSignals(DB_Front_Seat_Heat_Cool_Switches_HS_CAN * pMsg);
#define DB_Front_Seat_Heat_Cool_Switches_HS_CAN_DrvHCSeatSw1Act_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Front_Seat_Heat_Cool_Switches_HS_CAN_Index, 0, dPhysicalValue);
#define DB_Front_Seat_Heat_Cool_Switches_HS_CAN_DrvHCSeatSw2Act_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Front_Seat_Heat_Cool_Switches_HS_CAN_Index, 1, dPhysicalValue);
#define DB_Front_Seat_Heat_Cool_Switches_HS_CAN_DrvHCSeatSw3Act_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Front_Seat_Heat_Cool_Switches_HS_CAN_Index, 2, dPhysicalValue);
#define DB_Front_Seat_Heat_Cool_Switches_HS_CAN_PassHCSeatSw1Act_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Front_Seat_Heat_Cool_Switches_HS_CAN_Index, 3, dPhysicalValue);
#define DB_Front_Seat_Heat_Cool_Switches_HS_CAN_PassHCSeatSw2Act_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Front_Seat_Heat_Cool_Switches_HS_CAN_Index, 4, dPhysicalValue);
#define DB_Front_Seat_Heat_Cool_Switches_HS_CAN_PassHCSeatSw3Act_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Front_Seat_Heat_Cool_Switches_HS_CAN_Index, 5, dPhysicalValue);
#define DB_Front_Seat_Heat_Cool_Switches_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Front_Seat_Heat_Cool_Switches_HS_CAN_Index, 0)
extern int DB_Auxiliary_Heater_Status_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double AuxHtrAtv; /// Min: 0 Max: 1 Units: 
    BYTE AuxHtrAtv_raw;
    double CCClntCrcFlwRtReq; /// Min: 0 Max: 100.000035 Units: %
    BYTE CCClntCrcFlwRtReq_raw;
    double HtrCoreInltClntTmpCalc; /// Min: -40 Max: 215 Units: degC
    BYTE HtrCoreInltClntTmpCalc_raw;
    double HtrCoreInltClntTmpCalcV; /// Min: 0 Max: 1 Units: 
    BYTE HtrCoreInltClntTmpCalcV_raw;
} DB_Auxiliary_Heater_Status_HS_CAN;

#pragma warning(disable : 4005)
#define DB_Auxiliary_Heater_Status_HS_CAN_$_AuxHtrAtv_$$_False 0
#define DB_Auxiliary_Heater_Status_HS_CAN_$_AuxHtrAtv_$$_True 1
#define DB_Auxiliary_Heater_Status_HS_CAN_$_HtrCoreInltClntTmpCalcV_$$_Valid 0
#define DB_Auxiliary_Heater_Status_HS_CAN_$_HtrCoreInltClntTmpCalcV_$$_Invalid 1
#pragma warning(default : 4005)

void DB_Auxiliary_Heater_Status_HS_CAN_Init(DB_Auxiliary_Heater_Status_HS_CAN * pMsg);
int DB_Auxiliary_Heater_Status_HS_CAN_Transmit(DB_Auxiliary_Heater_Status_HS_CAN * pMsg);
int DB_Auxiliary_Heater_Status_HS_CAN_Transmit_raw(DB_Auxiliary_Heater_Status_HS_CAN * pMsg);
int DB_Auxiliary_Heater_Status_HS_CAN_UpdateBytesFromSignals(DB_Auxiliary_Heater_Status_HS_CAN * pMsg);
int DB_Auxiliary_Heater_Status_HS_CAN_UpdateBytesFromRawSignals(DB_Auxiliary_Heater_Status_HS_CAN * pMsg);
#define DB_Auxiliary_Heater_Status_HS_CAN_AuxHtrAtv_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Auxiliary_Heater_Status_HS_CAN_Index, 0, dPhysicalValue);
#define DB_Auxiliary_Heater_Status_HS_CAN_CCClntCrcFlwRtReq_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Auxiliary_Heater_Status_HS_CAN_Index, 1, dPhysicalValue);
#define DB_Auxiliary_Heater_Status_HS_CAN_HtrCoreInltClntTmpCalc_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Auxiliary_Heater_Status_HS_CAN_Index, 2, dPhysicalValue);
#define DB_Auxiliary_Heater_Status_HS_CAN_HtrCoreInltClntTmpCalcV_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Auxiliary_Heater_Status_HS_CAN_Index, 3, dPhysicalValue);
#define DB_Auxiliary_Heater_Status_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Auxiliary_Heater_Status_HS_CAN_Index, 0)
extern int DB_Rear_Window_Defog_Status_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double RrWndDfgOn; /// Min: 0 Max: 1 Units: 
    BYTE RrWndDfgOn_raw;
} DB_Rear_Window_Defog_Status_HS_CAN;

#pragma warning(disable : 4005)
#define DB_Rear_Window_Defog_Status_HS_CAN_$_RrWndDfgOn_$$_False 0
#define DB_Rear_Window_Defog_Status_HS_CAN_$_RrWndDfgOn_$$_True 1
#pragma warning(default : 4005)

void DB_Rear_Window_Defog_Status_HS_CAN_Init(DB_Rear_Window_Defog_Status_HS_CAN * pMsg);
int DB_Rear_Window_Defog_Status_HS_CAN_Transmit(DB_Rear_Window_Defog_Status_HS_CAN * pMsg);
int DB_Rear_Window_Defog_Status_HS_CAN_Transmit_raw(DB_Rear_Window_Defog_Status_HS_CAN * pMsg);
int DB_Rear_Window_Defog_Status_HS_CAN_UpdateBytesFromSignals(DB_Rear_Window_Defog_Status_HS_CAN * pMsg);
int DB_Rear_Window_Defog_Status_HS_CAN_UpdateBytesFromRawSignals(DB_Rear_Window_Defog_Status_HS_CAN * pMsg);
#define DB_Rear_Window_Defog_Status_HS_CAN_RrWndDfgOn_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Rear_Window_Defog_Status_HS_CAN_Index, 0, dPhysicalValue);
#define DB_Rear_Window_Defog_Status_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Rear_Window_Defog_Status_HS_CAN_Index, 0)
extern int DB_PPEI_Engine_General_Status_1_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double AccActPos; /// Min: 0 Max: 100.000035 Units: %
    BYTE AccActPos_raw;
    double AccActPosV; /// Min: 0 Max: 1 Units: 
    BYTE AccActPosV_raw;
    double CrsCntAtv; /// Min: 0 Max: 1 Units: 
    BYTE CrsCntAtv_raw;
    double CrsCntEnbld; /// Min: 0 Max: 1 Units: 
    BYTE CrsCntEnbld_raw;
    double Eng12vStrtrMtrCmmdOn; /// Min: 0 Max: 1 Units: 
    BYTE Eng12vStrtrMtrCmmdOn_raw;
    double EngCntrlRunCrnkTrmSt; /// Min: 0 Max: 1 Units: 
    BYTE EngCntrlRunCrnkTrmSt_raw;
    double EngIdlAtv; /// Min: 0 Max: 1 Units: 
    BYTE EngIdlAtv_raw;
    double EngAirIntBstPr; /// Min: -128 Max: 127 Units: kPaG
    BYTE EngAirIntBstPr_raw;
    double EngAirIntBstPrV; /// Min: 0 Max: 1 Units: 
    BYTE EngAirIntBstPrV_raw;
    double EngRunAtv; /// Min: 0 Max: 1 Units: 
    BYTE EngRunAtv_raw;
    double EngSpd; /// Min: 0 Max: 16383.75 Units: rpm
    WORD EngSpd_raw;
    double EngSpdStat; /// Min: 0 Max: 3 Units: 
    BYTE EngSpdStat_raw;
    double PT_BrkPedDscrtInpStat; /// Min: 0 Max: 1 Units: 
    BYTE PT_BrkPedDscrtInpStat_raw;
    double PT_BrkPedDscrtInpStatV; /// Min: 0 Max: 1 Units: 
    BYTE PT_BrkPedDscrtInpStatV_raw;
    double PTCrnkAbrted; /// Min: 0 Max: 1 Units: 
    BYTE PTCrnkAbrted_raw;
    double PT_CrnkAct; /// Min: 0 Max: 1 Units: 
    BYTE PT_CrnkAct_raw;
    double PTRunAbrt; /// Min: 0 Max: 1 Units: 
    BYTE PTRunAbrt_raw;
    double RmVhStrtEngRng; /// Min: 0 Max: 1 Units: 
    BYTE RmVhStrtEngRng_raw;
    double SpdLmtrSpdWrngEnbld; /// Min: 0 Max: 1 Units: 
    BYTE SpdLmtrSpdWrngEnbld_raw;
} DB_PPEI_Engine_General_Status_1_HS_CAN;

#pragma warning(disable : 4005)
#define DB_PPEI_Engine_General_Status_1_HS_CAN_$_AccActPosV_$$_Valid 0
#define DB_PPEI_Engine_General_Status_1_HS_CAN_$_AccActPosV_$$_Invalid 1
#define DB_PPEI_Engine_General_Status_1_HS_CAN_$_CrsCntAtv_$$_False 0
#define DB_PPEI_Engine_General_Status_1_HS_CAN_$_CrsCntAtv_$$_True 1
#define DB_PPEI_Engine_General_Status_1_HS_CAN_$_CrsCntEnbld_$$_False 0
#define DB_PPEI_Engine_General_Status_1_HS_CAN_$_CrsCntEnbld_$$_True 1
#define DB_PPEI_Engine_General_Status_1_HS_CAN_$_Eng12vStrtrMtrCmmdOn_$$_False 0
#define DB_PPEI_Engine_General_Status_1_HS_CAN_$_Eng12vStrtrMtrCmmdOn_$$_True 1
#define DB_PPEI_Engine_General_Status_1_HS_CAN_$_EngCntrlRunCrnkTrmSt_$$_Inactive 0
#define DB_PPEI_Engine_General_Status_1_HS_CAN_$_EngCntrlRunCrnkTrmSt_$$_Active 1
#define DB_PPEI_Engine_General_Status_1_HS_CAN_$_EngIdlAtv_$$_False 0
#define DB_PPEI_Engine_General_Status_1_HS_CAN_$_EngIdlAtv_$$_True 1
#define DB_PPEI_Engine_General_Status_1_HS_CAN_$_EngAirIntBstPrV_$$_Valid 0
#define DB_PPEI_Engine_General_Status_1_HS_CAN_$_EngAirIntBstPrV_$$_Invalid 1
#define DB_PPEI_Engine_General_Status_1_HS_CAN_$_EngRunAtv_$$_False 0
#define DB_PPEI_Engine_General_Status_1_HS_CAN_$_EngRunAtv_$$_True 1
#define DB_PPEI_Engine_General_Status_1_HS_CAN_$_EngSpdStat_$$_Normal_Operation 0
#define DB_PPEI_Engine_General_Status_1_HS_CAN_$_EngSpdStat_$$_Degraded_Operation 1
#define DB_PPEI_Engine_General_Status_1_HS_CAN_$_EngSpdStat_$$_Invalid 3
#define DB_PPEI_Engine_General_Status_1_HS_CAN_$_PT_BrkPedDscrtInpStat_$$_Brake_Not_Applied 0
#define DB_PPEI_Engine_General_Status_1_HS_CAN_$_PT_BrkPedDscrtInpStat_$$_Brake_Applied 1
#define DB_PPEI_Engine_General_Status_1_HS_CAN_$_PT_BrkPedDscrtInpStatV_$$_Valid 0
#define DB_PPEI_Engine_General_Status_1_HS_CAN_$_PT_BrkPedDscrtInpStatV_$$_Invalid 1
#define DB_PPEI_Engine_General_Status_1_HS_CAN_$_PTCrnkAbrted_$$_False 0
#define DB_PPEI_Engine_General_Status_1_HS_CAN_$_PTCrnkAbrted_$$_True 1
#define DB_PPEI_Engine_General_Status_1_HS_CAN_$_PT_CrnkAct_$$_False 0
#define DB_PPEI_Engine_General_Status_1_HS_CAN_$_PT_CrnkAct_$$_True 1
#define DB_PPEI_Engine_General_Status_1_HS_CAN_$_PTRunAbrt_$$_False 0
#define DB_PPEI_Engine_General_Status_1_HS_CAN_$_PTRunAbrt_$$_True 1
#define DB_PPEI_Engine_General_Status_1_HS_CAN_$_RmVhStrtEngRng_$$_False 0
#define DB_PPEI_Engine_General_Status_1_HS_CAN_$_RmVhStrtEngRng_$$_True 1
#define DB_PPEI_Engine_General_Status_1_HS_CAN_$_SpdLmtrSpdWrngEnbld_$$_False 0
#define DB_PPEI_Engine_General_Status_1_HS_CAN_$_SpdLmtrSpdWrngEnbld_$$_True 1
#pragma warning(default : 4005)

void DB_PPEI_Engine_General_Status_1_HS_CAN_Init(DB_PPEI_Engine_General_Status_1_HS_CAN * pMsg);
int DB_PPEI_Engine_General_Status_1_HS_CAN_Transmit(DB_PPEI_Engine_General_Status_1_HS_CAN * pMsg);
int DB_PPEI_Engine_General_Status_1_HS_CAN_Transmit_raw(DB_PPEI_Engine_General_Status_1_HS_CAN * pMsg);
int DB_PPEI_Engine_General_Status_1_HS_CAN_UpdateBytesFromSignals(DB_PPEI_Engine_General_Status_1_HS_CAN * pMsg);
int DB_PPEI_Engine_General_Status_1_HS_CAN_UpdateBytesFromRawSignals(DB_PPEI_Engine_General_Status_1_HS_CAN * pMsg);
#define DB_PPEI_Engine_General_Status_1_HS_CAN_AccActPos_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PPEI_Engine_General_Status_1_HS_CAN_Index, 0, dPhysicalValue);
#define DB_PPEI_Engine_General_Status_1_HS_CAN_AccActPosV_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PPEI_Engine_General_Status_1_HS_CAN_Index, 1, dPhysicalValue);
#define DB_PPEI_Engine_General_Status_1_HS_CAN_CrsCntAtv_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PPEI_Engine_General_Status_1_HS_CAN_Index, 2, dPhysicalValue);
#define DB_PPEI_Engine_General_Status_1_HS_CAN_CrsCntEnbld_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PPEI_Engine_General_Status_1_HS_CAN_Index, 3, dPhysicalValue);
#define DB_PPEI_Engine_General_Status_1_HS_CAN_Eng12vStrtrMtrCmmdOn_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PPEI_Engine_General_Status_1_HS_CAN_Index, 4, dPhysicalValue);
#define DB_PPEI_Engine_General_Status_1_HS_CAN_EngCntrlRunCrnkTrmSt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PPEI_Engine_General_Status_1_HS_CAN_Index, 5, dPhysicalValue);
#define DB_PPEI_Engine_General_Status_1_HS_CAN_EngIdlAtv_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PPEI_Engine_General_Status_1_HS_CAN_Index, 6, dPhysicalValue);
#define DB_PPEI_Engine_General_Status_1_HS_CAN_EngAirIntBstPr_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PPEI_Engine_General_Status_1_HS_CAN_Index, 7, dPhysicalValue);
#define DB_PPEI_Engine_General_Status_1_HS_CAN_EngAirIntBstPrV_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PPEI_Engine_General_Status_1_HS_CAN_Index, 8, dPhysicalValue);
#define DB_PPEI_Engine_General_Status_1_HS_CAN_EngRunAtv_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PPEI_Engine_General_Status_1_HS_CAN_Index, 9, dPhysicalValue);
#define DB_PPEI_Engine_General_Status_1_HS_CAN_EngSpd_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PPEI_Engine_General_Status_1_HS_CAN_Index, 10, dPhysicalValue);
#define DB_PPEI_Engine_General_Status_1_HS_CAN_EngSpdStat_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PPEI_Engine_General_Status_1_HS_CAN_Index, 11, dPhysicalValue);
#define DB_PPEI_Engine_General_Status_1_HS_CAN_PT_BrkPedDscrtInpStat_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PPEI_Engine_General_Status_1_HS_CAN_Index, 12, dPhysicalValue);
#define DB_PPEI_Engine_General_Status_1_HS_CAN_PT_BrkPedDscrtInpStatV_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PPEI_Engine_General_Status_1_HS_CAN_Index, 13, dPhysicalValue);
#define DB_PPEI_Engine_General_Status_1_HS_CAN_PTCrnkAbrted_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PPEI_Engine_General_Status_1_HS_CAN_Index, 14, dPhysicalValue);
#define DB_PPEI_Engine_General_Status_1_HS_CAN_PT_CrnkAct_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PPEI_Engine_General_Status_1_HS_CAN_Index, 15, dPhysicalValue);
#define DB_PPEI_Engine_General_Status_1_HS_CAN_PTRunAbrt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PPEI_Engine_General_Status_1_HS_CAN_Index, 16, dPhysicalValue);
#define DB_PPEI_Engine_General_Status_1_HS_CAN_RmVhStrtEngRng_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PPEI_Engine_General_Status_1_HS_CAN_Index, 17, dPhysicalValue);
#define DB_PPEI_Engine_General_Status_1_HS_CAN_SpdLmtrSpdWrngEnbld_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PPEI_Engine_General_Status_1_HS_CAN_Index, 18, dPhysicalValue);
#define DB_PPEI_Engine_General_Status_1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_PPEI_Engine_General_Status_1_HS_CAN_Index, 0)
extern int DB_Climate_Control_General_Status_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double ACCmpsrFldOn; /// Min: 0 Max: 1 Units: 
    BYTE ACCmpsrFldOn_raw;
    double ACCompModReq; /// Min: 0 Max: 3 Units: 
    BYTE ACCompModReq_raw;
    double ACCompNormLd; /// Min: 0 Max: 25.5 Units: l/min
    BYTE ACCompNormLd_raw;
    double ACCompNormLdV; /// Min: 0 Max: 1 Units: 
    BYTE ACCompNormLdV_raw;
    double ACCmEngRunReq; /// Min: 0 Max: 1 Units: 
    BYTE ACCmEngRunReq_raw;
    double ClmtCtrlTrgtTemp; /// Min: -10 Max: 92.3 Units: degC
    WORD ClmtCtrlTrgtTemp_raw;
} DB_Climate_Control_General_Status_HS_CAN;

#pragma warning(disable : 4005)
#define DB_Climate_Control_General_Status_HS_CAN_$_ACCmpsrFldOn_$$_False 0
#define DB_Climate_Control_General_Status_HS_CAN_$_ACCmpsrFldOn_$$_True 1
#define DB_Climate_Control_General_Status_HS_CAN_$_ACCompModReq_$$_Disengage_Immediately 0
#define DB_Climate_Control_General_Status_HS_CAN_$_ACCompModReq_$$_Disengage 1
#define DB_Climate_Control_General_Status_HS_CAN_$_ACCompModReq_$$_Engage 2
#define DB_Climate_Control_General_Status_HS_CAN_$_ACCompModReq_$$_No_Action 3
#define DB_Climate_Control_General_Status_HS_CAN_$_ACCompNormLdV_$$_Valid 0
#define DB_Climate_Control_General_Status_HS_CAN_$_ACCompNormLdV_$$_Invalid 1
#define DB_Climate_Control_General_Status_HS_CAN_$_ACCmEngRunReq_$$_No_Action 0
#define DB_Climate_Control_General_Status_HS_CAN_$_ACCmEngRunReq_$$_Engine_Run_Requested 1
#pragma warning(default : 4005)

void DB_Climate_Control_General_Status_HS_CAN_Init(DB_Climate_Control_General_Status_HS_CAN * pMsg);
int DB_Climate_Control_General_Status_HS_CAN_Transmit(DB_Climate_Control_General_Status_HS_CAN * pMsg);
int DB_Climate_Control_General_Status_HS_CAN_Transmit_raw(DB_Climate_Control_General_Status_HS_CAN * pMsg);
int DB_Climate_Control_General_Status_HS_CAN_UpdateBytesFromSignals(DB_Climate_Control_General_Status_HS_CAN * pMsg);
int DB_Climate_Control_General_Status_HS_CAN_UpdateBytesFromRawSignals(DB_Climate_Control_General_Status_HS_CAN * pMsg);
#define DB_Climate_Control_General_Status_HS_CAN_ACCmpsrFldOn_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Climate_Control_General_Status_HS_CAN_Index, 0, dPhysicalValue);
#define DB_Climate_Control_General_Status_HS_CAN_ACCompModReq_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Climate_Control_General_Status_HS_CAN_Index, 1, dPhysicalValue);
#define DB_Climate_Control_General_Status_HS_CAN_ACCompNormLd_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Climate_Control_General_Status_HS_CAN_Index, 2, dPhysicalValue);
#define DB_Climate_Control_General_Status_HS_CAN_ACCompNormLdV_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Climate_Control_General_Status_HS_CAN_Index, 3, dPhysicalValue);
#define DB_Climate_Control_General_Status_HS_CAN_ACCmEngRunReq_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Climate_Control_General_Status_HS_CAN_Index, 4, dPhysicalValue);
#define DB_Climate_Control_General_Status_HS_CAN_ClmtCtrlTrgtTemp_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Climate_Control_General_Status_HS_CAN_Index, 5, dPhysicalValue);
#define DB_Climate_Control_General_Status_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Climate_Control_General_Status_HS_CAN_Index, 0)
extern int DB_Network_Management_BCM_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double SrcNodeID; /// Min: 0 Max: 255 Units: 
    BYTE SrcNodeID_raw;
    double UDat; /// Min: 0 Max: 281474976710655 Units: 
    uint64 UDat_raw;
} DB_Network_Management_BCM_HS_CAN;


void DB_Network_Management_BCM_HS_CAN_Init(DB_Network_Management_BCM_HS_CAN * pMsg);
int DB_Network_Management_BCM_HS_CAN_Transmit(DB_Network_Management_BCM_HS_CAN * pMsg);
int DB_Network_Management_BCM_HS_CAN_Transmit_raw(DB_Network_Management_BCM_HS_CAN * pMsg);
int DB_Network_Management_BCM_HS_CAN_UpdateBytesFromSignals(DB_Network_Management_BCM_HS_CAN * pMsg);
int DB_Network_Management_BCM_HS_CAN_UpdateBytesFromRawSignals(DB_Network_Management_BCM_HS_CAN * pMsg);
#define DB_Network_Management_BCM_HS_CAN_SrcNodeID_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Network_Management_BCM_HS_CAN_Index, 0, dPhysicalValue);
#define DB_Network_Management_BCM_HS_CAN_UDat_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Network_Management_BCM_HS_CAN_Index, 1, dPhysicalValue);
#define DB_Network_Management_BCM_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Network_Management_BCM_HS_CAN_Index, 0)
void SpyAppSig_AS_appSig_mpiRead_bytesBMPNAC(double dNewValue);
void SpyAppSig_AS_appSig_mpiRead_bytesDUNS(double dNewValue);
void SpyAppSig_AS_appSig_mpiRead_bytesECUID(double dNewValue);
void SpyAppSig_AS_appSig_mpiRead_bytesEMPNAC(double dNewValue);
void SpyAppSig_AS_appSig_mpiRead_bytesMTC(double dNewValue);
void SpyAppSig_AS_appSig_mpiRead_bytesVPPS(double dNewValue);
void SpyAppSig_AS_appSig_mpiWrite_BMPNAC(double dNewValue);
void SpyAppSig_AS_appSig_mpiWrite_EMPNAC(double dNewValue);
void SpyAppSig_AS_appSig_mpiWrite_MTC(double dNewValue);
void SpyAppSig_AS_appSig_sapaWrite_bytesSeedKey(double dNewValue);
void SpyAppSig_AS_appSig_sapaWrite_bytesSeed(double dNewValue);
void SpyAppSig_AS_appSig_sapaRead_bytesSeed(double dNewValue);

#endif // VSPY_GENERATED_HEADER
