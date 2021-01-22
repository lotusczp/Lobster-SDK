#include "LUsbCanDllWrapper.h"
#include <QMessageBox>

LUsbCanDllWrapper::LUsbCanDllWrapper()
    : m_library("./thirdparty/ControlCAN.dll")
{
    VCI_OpenDevice = (VCI_OpenDeviceFunc*)m_library.resolve("VCI_OpenDevice");
    VCI_CloseDevice = (VCI_CloseDeviceFunc*)m_library.resolve("VCI_CloseDevice");
    VCI_InitCAN = (VCI_InitCANFunc*)m_library.resolve("VCI_InitCAN");

    VCI_ReadBoardInfo = (VCI_ReadBoardInfoFunc*)m_library.resolve("VCI_ReadBoardInfo");
    VCI_ReadErrInfo = (VCI_ReadErrInfoFunc*)m_library.resolve("VCI_ReadErrInfo");
    VCI_ReadCANStatus = (VCI_ReadCANStatusFunc*)m_library.resolve("VCI_ReadCANStatus");

    VCI_GetReference = (VCI_GetReferenceFunc*)m_library.resolve("VCI_GetReference");
    VCI_SetReference = (VCI_SetReferenceFunc*)m_library.resolve("VCI_SetReference");

    VCI_GetReceiveNum = (VCI_GetReceiveNumFunc*)m_library.resolve("VCI_GetReceiveNum");
    VCI_ClearBuffer = (VCI_ClearBufferFunc*)m_library.resolve("VCI_ClearBuffer");

    VCI_StartCAN = (VCI_StartCANFunc*)m_library.resolve("VCI_StartCAN");
    VCI_ResetCAN = (VCI_ResetCANFunc*)m_library.resolve("VCI_ResetCAN");

    VCI_Transmit = (VCI_TransmitFunc*)m_library.resolve("VCI_Transmit");
    VCI_Receive = (VCI_ReceiveFunc*)m_library.resolve("VCI_Receive");

    if(VCI_OpenDevice == nullptr
            || VCI_CloseDevice == nullptr
            || VCI_InitCAN == nullptr
            || VCI_ReadBoardInfo == nullptr
            || VCI_ReadErrInfo == nullptr
            || VCI_ReadCANStatus == nullptr
            || VCI_GetReference == nullptr
            || VCI_SetReference == nullptr
            || VCI_GetReceiveNum == nullptr
            || VCI_ClearBuffer == nullptr
            || VCI_StartCAN == nullptr
            || VCI_ResetCAN == nullptr
            || VCI_Transmit == nullptr
            || VCI_Receive == nullptr) {
        QMessageBox::warning(0, QObject::tr("Warning"), "Can not parse ControlCAN.dll, please check whether it exists in ./thirdparty/ ");
    }
}
