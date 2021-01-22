#include "LTmctlWrapper.h"
#include <QMessageBox>

LTmctlWrapper::LTmctlWrapper()
    : m_library("./thirdparty/tmctl.dll")
{
    initialize = (TmcInitialize*)m_library.resolve("TmcInitialize");
    send = (TmcSend*)m_library.resolve("TmcSend");
    sendByLength = (TmcSendByLength*)m_library.resolve("TmcSendByLength");
    receive = (TmcReceive*)m_library.resolve("TmcReceive");
    receiveBlockHeader = (TmcReceiveBlockHeader*)m_library.resolve("TmcReceiveBlockHeader");
    receiveBlockData = (TmcReceiveBlockData*)m_library.resolve("TmcReceiveBlockData");

    if(initialize == nullptr
            || send == nullptr
            || sendByLength == nullptr
            || receive == nullptr
            || receiveBlockHeader == nullptr
            || receiveBlockData == nullptr)
    {
        QMessageBox::warning(nullptr, QObject::tr("Warning"), "Can not parse tmctl.dll, please check whether it exists in ./thirdparty/ ");
    }
}
