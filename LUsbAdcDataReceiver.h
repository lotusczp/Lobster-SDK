#ifndef LUSBADCDATARECEIVER_H
#define LUSBADCDATARECEIVER_H

#include "LYavUsbAdcDllWrapper.h"

class LUsbAdcDataReceiver
{
public:
    LUsbAdcDataReceiver(unsigned int a_uiPortNum) : m_uiPortNum(a_uiPortNum){}

    virtual ~LUsbAdcDataReceiver() {}

    unsigned int getPortNum() const {return m_uiPortNum;}

    virtual void receiveMsgCallback(int rawValue, double voltage) = 0;

private:
    LUsbAdcDataReceiver() {}

protected:
    unsigned int m_uiPortNum;
};

#endif // LUSBADCDATARECEIVER_H
