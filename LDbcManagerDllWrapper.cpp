#include "LDbcManagerDllWrapper.h"
#include <QMessageBox>

LDbcManagerDllWrapper::LDbcManagerDllWrapper() :
    m_library("./thirdparty/LibDBCManager.dll")
{
    DBC_Init = (DBC_InitType*)m_library.resolve("DBC_Init");
    DBC_Release = (DBC_ReleaseType*)m_library.resolve("DBC_Release");
    DBC_LoadFile = (DBC_LoadFileType*)m_library.resolve("DBC_LoadFile");
    DBC_GetFirstMessage = (DBC_GetFirstMessageType*)m_library.resolve("DBC_GetFirstMessage");
    DBC_GetNextMessage = (DBC_GetNextMessageType*)m_library.resolve("DBC_GetNextMessage");
    DBC_GetMessageById = (DBC_GetMessageByIdType*)m_library.resolve("DBC_GetMessageById");
    DBC_GetMessageCount = (DBC_GetMessageCountType*)m_library.resolve("DBC_GetMessageCount");
    DBC_Analyse = (DBC_AnalyseType*)m_library.resolve("DBC_Analyse");
    DBC_OnReceive = (DBC_OnReceiveType*)m_library.resolve("DBC_OnReceive");
    DBC_SetSender = (DBC_SetSenderType*)m_library.resolve("DBC_SetSender");
    DBC_SetOnMultiTransDoneFunc = (DBC_SetOnMultiTransDoneFuncType*)m_library.resolve("DBC_SetOnMultiTransDoneFunc");
    DBC_Send = (DBC_SendType*)m_library.resolve("DBC_Send");

    if(DBC_Init == nullptr
            || DBC_Release == nullptr
            || DBC_LoadFile == nullptr
            || DBC_GetFirstMessage == nullptr
            || DBC_GetNextMessage == nullptr
            || DBC_GetMessageById == nullptr
            || DBC_GetMessageCount == nullptr
            || DBC_Analyse == nullptr
            || DBC_OnReceive == nullptr
            || DBC_SetSender == nullptr
            || DBC_SetOnMultiTransDoneFunc == nullptr
            || DBC_Send == nullptr) {
        QMessageBox::warning(0, QObject::tr("Warning"), "Can not parse LibDBCManager.dll, please check whether it exists in ./thirdparty/ ");
    }
}
