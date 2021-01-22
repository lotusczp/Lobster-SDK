#ifndef LUSBCANDLLWRAPPER_H
#define LUSBCANDLLWRAPPER_H

#include <QLibrary>

// Ported from ControlCAN.h
//----------------------------------------------------------
#define VCI_PCI5121         1
#define VCI_PCI9810         2
#define VCI_USBCAN1         3
#define VCI_USBCAN2         4
#define VCI_USBCAN2A        4
#define VCI_PCI9820         5
#define VCI_CAN232          6
#define VCI_PCI5110         7
#define VCI_CANLITE         8
#define VCI_ISA9620         9
#define VCI_ISA5420         10
#define VCI_PC104CAN        11
#define VCI_CANETUDP        12
#define VCI_CANETE          12
#define VCI_DNP9810         13
#define VCI_PCI9840         14
#define VCI_PC104CAN2       15
#define VCI_PCI9820I        16
#define VCI_CANETTCP        17
#define VCI_PEC9920         18
#define VCI_PCIE_9220       18
#define VCI_PCI5010U        19
#define VCI_USBCAN_E_U      20
#define VCI_USBCAN_2E_U     21
#define VCI_PCI5020U        22
#define VCI_EG20T_CAN       23
#define VCI_PCIE9221        24
#define VCI_WIFICAN_TCP     25
#define VCI_WIFICAN_UDP     26
#define VCI_PCIe9120        27
#define VCI_PCIe9110        28
#define VCI_PCIe9140        29
#define VCI_USBCAN_4E_U     31
#define VCI_CANDTU_200UR    32
#define VCI_CANDTU_MINI     33
#define VCI_USBCAN_8E_U     34
#define VCI_CANREPLAY       35
#define VCI_CANDTU_NET      36
#define VCI_CANDTU_100UR    37

#define ERR_CAN_OVERFLOW            0x0001
#define ERR_CAN_ERRALARM            0x0002
#define ERR_CAN_PASSIVE             0x0004
#define ERR_CAN_LOSE                0x0008
#define ERR_CAN_BUSERR              0x0010
#define ERR_CAN_BUSOFF              0x0020
#define ERR_CAN_BUFFER_OVERFLOW     0x0040

#define ERR_DEVICEOPENED            0x0100
#define ERR_DEVICEOPEN              0x0200
#define ERR_DEVICENOTOPEN           0x0400
#define ERR_BUFFEROVERFLOW          0x0800
#define ERR_DEVICENOTEXIST          0x1000
#define ERR_LOADKERNELDLL           0x2000
#define ERR_CMDFAILED               0x4000
#define ERR_BUFFERCREATE            0x8000

#define ERR_CANETE_PORTOPENED       0x00010000
#define ERR_CANETE_INDEXUSED        0x00020000
#define ERR_REF_TYPE_ID             0x00030000
#define ERR_CREATE_SOCKET           0x00030002
#define ERR_OPEN_CONNECT            0x00030003
#define ERR_NO_STARTUP              0x00030004
#define ERR_NO_CONNECTED            0x00030005
#define ERR_SEND_PARTIAL            0x00030006
#define ERR_SEND_TOO_FAST           0x00030007

#define STATUS_OK                   1
#define STATUS_ERR                  0

#define CMD_DESIP                   0
#define CMD_DESPORT                 1
#define CMD_CHGDESIPANDPORT         2
#define CMD_SRCPORT                 2
#define CMD_TCP_TYPE                4
#define TCP_CLIENT                  0
#define TCP_SERVER                  1

#define CMD_CLIENT_COUNT            5
#define CMD_CLIENT                  6
#define CMD_DISCONN_CLINET          7
#define CMD_SET_RECONNECT_TIME      8

#define CMD_GET_GPS                 9
#define CMD_GET_GPS_NUM             10

typedef unsigned long       DWORD, ULONG;
typedef int                 INT;
typedef void*				HANDLE;
typedef unsigned char       BYTE;
typedef unsigned short      USHORT;
typedef char				CHAR;
typedef unsigned int        UINT;
typedef unsigned char		UCHAR;
typedef unsigned short      UINT16;
typedef void*				PVOID;

typedef struct tagRemoteClient{
    int     iIndex;
    DWORD   port;
    HANDLE  hClient;
    char    szip[32];
}REMOTE_CLIENT;

typedef struct _tagChgDesIPAndPort
{
    char    szpwd[10];
    char    szdesip[20];
    int     desport;
    BYTE    blistenonly;
}CHGDESIPANDPORT;

typedef  struct  _VCI_BOARD_INFO{
    USHORT  hw_Version;
    USHORT  fw_Version;
    USHORT  dr_Version;
    USHORT  in_Version;
    USHORT  irq_Num;
    BYTE    can_Num;
    CHAR    str_Serial_Num[20];
    CHAR    str_hw_Type[40];
    USHORT  Reserved[4];
} VCI_BOARD_INFO,*PVCI_BOARD_INFO;

typedef  struct  _VCI_CAN_OBJ{
    UINT    ID;
    UINT    TimeStamp;
    BYTE    TimeFlag;
    BYTE    SendType;
    BYTE    RemoteFlag;
    BYTE    ExternFlag;
    BYTE    DataLen;
    BYTE    Data[8];
    BYTE    Reserved[3];
}VCI_CAN_OBJ,*PVCI_CAN_OBJ;

typedef struct _VCI_CAN_STATUS{
    UCHAR   ErrInterrupt;
    UCHAR   regMode;
    UCHAR   regStatus;
    UCHAR   regALCapture;
    UCHAR   regECCapture;
    UCHAR   regEWLimit;
    UCHAR   regRECounter;
    UCHAR   regTECounter;
    DWORD   Reserved;
}VCI_CAN_STATUS,*PVCI_CAN_STATUS;

typedef struct _VCI_ERR_INFO{
    UINT    ErrCode;
    BYTE    Passive_ErrData[3];
    BYTE    ArLost_ErrData;
} VCI_ERR_INFO,*PVCI_ERR_INFO;

typedef struct _VCI_INIT_CONFIG{
    DWORD    AccCode;
    DWORD    AccMask;
    DWORD    Reserved;
    UCHAR    Filter;
    UCHAR    Timing0;
    UCHAR    Timing1;
    UCHAR    Mode;
}VCI_INIT_CONFIG,*PVCI_INIT_CONFIG;

///////// new add struct for filter /////////
typedef struct _VCI_FILTER_RECORD{
    DWORD   ExtFrame;
    DWORD   Start;
    DWORD   End;
}VCI_FILTER_RECORD,*PVCI_FILTER_RECORD;

typedef struct _VCI_AUTO_SEND_OBJ{
    BYTE    Enable;
    BYTE    Index;
    DWORD   Interval;
    VCI_CAN_OBJ obj;
}VCI_AUTO_SEND_OBJ,*PVCI_AUTO_SEND_OBJ;

typedef struct _VCI_INDICATE_LIGHT{
    BYTE    Indicate;
    BYTE    AttribRedMode:2;
    BYTE    AttribGreenMode:2;
    BYTE    AttribReserved:4;
    BYTE    FrequenceRed:2;
    BYTE    FrequenceGreen:2;
    BYTE    FrequenceReserved:4;
} VCI_INDICATE_LIGHT,*PVCI_INDICATE_LIGHT;

typedef struct _VCI_CAN_OBJ_REDIRECT{
    BYTE    Action;
    BYTE    DestCanIndex;
} VCI_CAN_OBJ_REDIRECT,*PVCI_CAN_OBJ_REDIRECT;

typedef struct _CANDTUTIME {
    UINT16 wYear;
    UINT16 wMonth;
    UINT16 wDay;
    UINT16 wHour;
    UINT16 wMinute;
    UINT16 wSecond;
} CANDTUTIME;

typedef struct _tagCANDTUGPSData
{
    float       fLatitude;
    float       fLongitude;
    float       fSpeed;
    CANDTUTIME  candtuTime;
}CANDTUGPSData, *PCANDTUGPSData;

typedef struct _VCI_CANDTU_GPS_DATA
{
    PCANDTUGPSData pGPSData;
    ULONG          nGPSDataCnt;
}VCI_CANDTU_GPS_DATA, *PVCI_CANDTU_GPS_DATA;
//----------------------------------------------------------

typedef DWORD (__stdcall VCI_OpenDeviceFunc)(DWORD DeviceType,DWORD DeviceInd,DWORD Reserved);
typedef DWORD (__stdcall VCI_CloseDeviceFunc)(DWORD DeviceType,DWORD DeviceInd);
typedef DWORD (__stdcall VCI_InitCANFunc)(DWORD DeviceType, DWORD DeviceInd, DWORD CANInd, PVCI_INIT_CONFIG pInitConfig);

typedef DWORD (__stdcall VCI_ReadBoardInfoFunc)(DWORD DeviceType,DWORD DeviceInd,PVCI_BOARD_INFO pInfo);
typedef DWORD (__stdcall VCI_ReadErrInfoFunc)(DWORD DeviceType,DWORD DeviceInd,DWORD CANInd,PVCI_ERR_INFO pErrInfo);
typedef DWORD (__stdcall VCI_ReadCANStatusFunc)(DWORD DeviceType,DWORD DeviceInd,DWORD CANInd,PVCI_CAN_STATUS pCANStatus);

typedef DWORD (__stdcall VCI_GetReferenceFunc)(DWORD DeviceType,DWORD DeviceInd,DWORD CANInd,DWORD RefType,PVOID pData);
typedef DWORD (__stdcall VCI_SetReferenceFunc)(DWORD DeviceType,DWORD DeviceInd,DWORD CANInd,DWORD RefType,PVOID pData);

typedef ULONG (__stdcall VCI_GetReceiveNumFunc)(DWORD DeviceType,DWORD DeviceInd,DWORD CANInd);
typedef DWORD (__stdcall VCI_ClearBufferFunc)(DWORD DeviceType,DWORD DeviceInd,DWORD CANInd);

typedef DWORD (__stdcall VCI_StartCANFunc)(DWORD DeviceType,DWORD DeviceInd,DWORD CANInd);
typedef DWORD (__stdcall VCI_ResetCANFunc)(DWORD DeviceType,DWORD DeviceInd,DWORD CANInd);

typedef ULONG (__stdcall VCI_TransmitFunc)(DWORD DeviceType,DWORD DeviceInd,DWORD CANInd,PVCI_CAN_OBJ pSend,ULONG Len);
typedef ULONG (__stdcall VCI_ReceiveFunc)(DWORD DeviceType,DWORD DeviceInd,DWORD CANInd,PVCI_CAN_OBJ pReceive,ULONG Len,INT WaitTime);


class LUsbCanDllWrapper
{
public:

    LUsbCanDllWrapper();

    VCI_OpenDeviceFunc*      VCI_OpenDevice;
    VCI_CloseDeviceFunc*     VCI_CloseDevice;
    VCI_InitCANFunc*         VCI_InitCAN;

    VCI_ReadBoardInfoFunc*   VCI_ReadBoardInfo;
    VCI_ReadErrInfoFunc*     VCI_ReadErrInfo;
    VCI_ReadCANStatusFunc*   VCI_ReadCANStatus;

    VCI_GetReferenceFunc*    VCI_GetReference;
    VCI_SetReferenceFunc*    VCI_SetReference;

    VCI_GetReceiveNumFunc*   VCI_GetReceiveNum;
    VCI_ClearBufferFunc*     VCI_ClearBuffer;

    VCI_StartCANFunc*        VCI_StartCAN;
    VCI_ResetCANFunc*        VCI_ResetCAN;

    VCI_TransmitFunc*        VCI_Transmit;
    VCI_ReceiveFunc*         VCI_Receive;

private:
    QLibrary m_library;
};


#endif // LCANBUSDLLWRAPPER_H
