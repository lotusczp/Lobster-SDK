#ifndef LCANDATARECEIVER_H
#define LCANDATARECEIVER_H

#include "LUsbCanDllWrapper.h"

class LCanDataReceiver
{
public:
    LCanDataReceiver(unsigned int a_uiCanId) : m_uiCanId(a_uiCanId){}

    virtual ~LCanDataReceiver() {}

    unsigned int getCanId() {return m_uiCanId;}

    virtual void receiveMsgCallback(const VCI_CAN_OBJ& a_rMsg) = 0;

private:
    LCanDataReceiver() {}

private:
    unsigned int m_uiCanId;
};

#endif // LCANDATARECEIVER_H
