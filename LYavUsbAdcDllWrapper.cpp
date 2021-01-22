#include "LYavUsbAdcDllWrapper.h"
#include <QMessageBox>

LYavUsbAdcDllWrapper::LYavUsbAdcDllWrapper()
    : m_library("./thirdparty/ADIO86.dll")
{

    FindDevice = (FindDeviceFunc*)m_library.resolve("FindDevice");
    OpenYavDevice = (OpenYavDeviceFunc*)m_library.resolve("OpenYavDevice");
    GetYavData = (GetYavDataFunc*)m_library.resolve("GetYavData");

    if(FindDevice == nullptr
            || OpenYavDevice == nullptr
            || GetYavData == nullptr)
    {
        QMessageBox::warning(0, QObject::tr("Warning"), "Can not parse ADIO86.dll, please check whether it exists in ./thirdparty/ ");
    }
}
