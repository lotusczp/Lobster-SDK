#ifndef LYAVUSBADCDLLWRAPPER_H
#define LYAVUSBADCDLLWRAPPER_H

#include <QLibrary>

typedef int ( FindDeviceFunc)( void );
typedef int ( OpenYavDeviceFunc)(unsigned short TaskID);
typedef int ( GetYavDataFunc)(unsigned short TaskID, int *DAQDataBuffer, unsigned int DataSize,  int *YavParam,  int *CNTBuffer, unsigned int *IOBuffer);

class LYavUsbAdcDllWrapper
{
public:
    LYavUsbAdcDllWrapper();

    FindDeviceFunc*         FindDevice;
    OpenYavDeviceFunc*      OpenYavDevice;
    GetYavDataFunc*         GetYavData;

private:
    QLibrary m_library;
};

#endif // LYAVUSBADCDLLWRAPPER_H
