#ifndef LDBCMANAGERDLLWRAPPER_H
#define LDBCMANAGERDLLWRAPPER_H

#include <QLibrary>

// Ported from IDBCManager.h
//----------------------------------------------------------
#define INVALID_DBC_HANDLE        -1

#define _MAX_FILE_PATH_           260
#define _DBC_NAME_LENGTH_         127
#define _DBC_COMMENT_MAX_LENGTH_  200
#define _DBC_UNIT_MAX_LENGTH_     10
#define _DBC_SIGNAL_MAX_COUNT_    128

//multiplexer type
#define MUTIPLEXER_NONE     0
#define MUTIPLEXER_M_VALUE  1
#define MUTIPLEXER_M_SWITCH 2

struct DBCSignal
{
    uint32_t nStartBit;
    uint32_t nLen;
    double nFactor;
    double nOffset;
    double nMin;
    double nMax;
    double nValue;
    uint64_t nRawValue;
    bool is_signed;
    bool is_motorola;
    uint8_t multiplexer_type;//see 'multiplexer type' above
    uint8_t multiplexer_value;
    char unit[_DBC_UNIT_MAX_LENGTH_+1];
    char strName[_DBC_NAME_LENGTH_+1];
    char strComment[_DBC_COMMENT_MAX_LENGTH_+1];
    char strValDesc[_DBC_NAME_LENGTH_+1];
};

struct DBCMessage
{
    uint32_t nSignalCount;
    uint32_t nID;
    uint8_t nExtend;
    uint32_t nSize;
    DBCSignal vSignals[_DBC_SIGNAL_MAX_COUNT_];
    char strName[_DBC_NAME_LENGTH_+1];
    char strComment[_DBC_COMMENT_MAX_LENGTH_+1];
};

#define PROTOCOL_J1939   0
#define PROTOCOL_OTHER 1
struct FileInfo
{
    char strFilePath[_MAX_FILE_PATH_+1];
    uint8_t type;
    uint8_t merge;
};

// Callbacks
typedef bool (__stdcall *OnSend)(void* ctx, void* pObj);
typedef void (__stdcall *OnMultiTransDone)(void* ctx, DBCMessage* pMsg, uint8_t* data, uint16_t nLen, uint8_t nDirection);

typedef unsigned int     DBCHandle;

typedef DBCHandle (__stdcall DBC_InitType)();
typedef void (__stdcall DBC_ReleaseType)( DBCHandle hDBC );
typedef bool (__stdcall DBC_LoadFileType)( DBCHandle hDBC, const FileInfo* pFileInfo );
typedef bool (__stdcall DBC_GetFirstMessageType)( DBCHandle hDBC, DBCMessage* pMsg );
typedef bool (__stdcall DBC_GetNextMessageType)( DBCHandle hDBC, DBCMessage* pMsg );
typedef bool (__stdcall DBC_GetMessageByIdType)( DBCHandle hDBC, uint32_t nID, DBCMessage* pMsg );
typedef uint32_t (__stdcall DBC_GetMessageCountType)( DBCHandle hDBC );
typedef bool (__stdcall DBC_AnalyseType)( DBCHandle hDBC, const void* pObj, DBCMessage* pMsg );
typedef void (__stdcall DBC_OnReceiveType)( DBCHandle hDBC, const void* pObj );
typedef void (__stdcall DBC_SetSenderType)( DBCHandle hDBC, OnSend sender, void* ctx );
typedef void (__stdcall DBC_SetOnMultiTransDoneFuncType)( DBCHandle hDBC, OnMultiTransDone func, void* ctx);
typedef bool (__stdcall DBC_SendType)( DBCHandle hDBC, const DBCMessage* pMsg );

class LDbcManagerDllWrapper
{
public:
    LDbcManagerDllWrapper();

    DBC_InitType*                       DBC_Init;
    DBC_ReleaseType*                    DBC_Release;
    DBC_LoadFileType*                   DBC_LoadFile;
    DBC_GetFirstMessageType*            DBC_GetFirstMessage;
    DBC_GetNextMessageType*             DBC_GetNextMessage;
    DBC_GetMessageByIdType*             DBC_GetMessageById;
    DBC_GetMessageCountType*            DBC_GetMessageCount;
    DBC_AnalyseType*                    DBC_Analyse;
    DBC_OnReceiveType*                  DBC_OnReceive;
    DBC_SetSenderType*                  DBC_SetSender;
    DBC_SetOnMultiTransDoneFuncType*    DBC_SetOnMultiTransDoneFunc;
    DBC_SendType*                       DBC_Send;

private:
    static LDbcManagerDllWrapper   *s_pInstance;       //!< instance ptr

    QLibrary m_library;
};

#endif // LDBCMANAGERDLLWRAPPER_H
