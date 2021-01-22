#include "LCanDataManager.h"
#include "LUsbCanDllWrapper.h"

#define SCAN_INTERVAL_ms    100

QString wrapDeviceInfo(unsigned long DeviceType, unsigned long DeviceInd, unsigned long CANInd)
{
    return ("Type"+QString::number(DeviceType)+"Index"+QString::number(DeviceInd)+"Channel"+QString::number(CANInd));
}

LCanDataManager::LCanDataManager(QObject *parent) : QObject(parent)
{
    m_pUsbCanDllWrapper = new LUsbCanDllWrapper;

    m_pScanTimer = new QTimer(this);
    m_pScanTimer->setInterval(SCAN_INTERVAL_ms);
    connect(m_pScanTimer, &QTimer::timeout, this, &LCanDataManager::handleReceiveScan);

    connect(this, SIGNAL(startScan()), m_pScanTimer, SLOT(start()));
    connect(this, SIGNAL(stopScan()), m_pScanTimer, SLOT(stop()));
}

LCanDataManager::~LCanDataManager()
{
    m_pScanTimer->stop();
    delete m_pScanTimer;
    delete m_pUsbCanDllWrapper;
}

void LCanDataManager::startReceive(bool a_bStart)
{
    if(a_bStart){
        emit startScan();
    }
    else {
        emit stopScan();
    }
}

unsigned long LCanDataManager::openDevice(unsigned long DeviceInd, unsigned long DeviceType)
{
    return m_pUsbCanDllWrapper->VCI_OpenDevice(DeviceType, DeviceInd, 0);
}

unsigned long LCanDataManager::closeDevice(unsigned long DeviceInd, unsigned long DeviceType)
{
    return m_pUsbCanDllWrapper->VCI_CloseDevice(DeviceType, DeviceInd);
}

unsigned long LCanDataManager::initCAN(CanBaudRate a_eBaudrate, unsigned long DeviceInd, unsigned long CANInd, unsigned long DeviceType)
{
    VCI_INIT_CONFIG config;
    config.AccCode = 0;
    config.AccMask =0xffffffff;
    config.Filter = 1;
    config.Mode = 0;
    if(a_eBaudrate == eCanBaudRate_1Mbps) {
        config.Timing0 = 0x00;
        config.Timing1 = 0x14;
    }
    else if(a_eBaudrate == eCanBaudRate_500Kbps) {
        config.Timing0 = 0x00;
        config.Timing1 = 0x1C;
    }
    else if(a_eBaudrate == eCanBaudRate_250Kbps) {
        config.Timing0 = 0x01;
        config.Timing1 = 0x1C;
    }

    return m_pUsbCanDllWrapper->VCI_InitCAN(DeviceType, DeviceInd, CANInd, &config);
}

unsigned long LCanDataManager::readErrInfo(unsigned int *pErrorCode, unsigned long DeviceInd, unsigned long CANInd, unsigned long DeviceType)
{
    VCI_ERR_INFO errInfo;
    unsigned long retval = m_pUsbCanDllWrapper->VCI_ReadErrInfo(DeviceType, DeviceInd, CANInd, &errInfo);
    *pErrorCode = errInfo.ErrCode;
    return retval;

}

unsigned long LCanDataManager::setReference(unsigned long RefType, void *pData, unsigned long DeviceInd, unsigned long CANInd, unsigned long DeviceType)
{
    return m_pUsbCanDllWrapper->VCI_SetReference(DeviceType, DeviceInd, CANInd, RefType, pData);
}

unsigned long LCanDataManager::startCAN(unsigned long DeviceInd, unsigned long CANInd, unsigned long DeviceType)
{
    unsigned long retval = m_pUsbCanDllWrapper->VCI_StartCAN(DeviceType, DeviceInd, CANInd);
    if(retval == STATUS_OK) {
        QString strKey = wrapDeviceInfo(DeviceType, DeviceInd, CANInd);
        if(!m_mapInfo.contains(strKey)) {
            m_mapInfo[strKey] = Info(DeviceInd, CANInd, DeviceType);
        }
    }
    return retval;
}

unsigned long LCanDataManager::resetCAN(unsigned long DeviceInd, unsigned long CANInd, unsigned long DeviceType)
{
    return m_pUsbCanDllWrapper->VCI_ResetCAN(DeviceType, DeviceInd, CANInd);
}

unsigned long LCanDataManager::clearBuffer(unsigned long DeviceInd, unsigned long CANInd, unsigned long DeviceType)
{
    return m_pUsbCanDllWrapper->VCI_ClearBuffer(DeviceType, DeviceInd, CANInd);
}

unsigned long LCanDataManager::transmit(CanObj *pSend, unsigned long len, unsigned long DeviceInd, unsigned long CANInd, unsigned long DeviceType)
{
    return m_pUsbCanDllWrapper->VCI_Transmit(DeviceType, DeviceInd, CANInd, pSend, len);
}

void LCanDataManager::registerReceiver(LCanDataReceiver *a_pReceiver, unsigned long DeviceInd, unsigned long CANInd, unsigned long DeviceType)
{
    QString strKey = wrapDeviceInfo(DeviceType, DeviceInd, CANInd);
    m_mapRecievers[strKey][a_pReceiver->getCanId()] = a_pReceiver;
}

void LCanDataManager::handleReceiveScan()
{
    QMapIterator<QString, Info> it(m_mapInfo);
    while(it.hasNext()) {
        it.next();
        // For each channel
        CanObj msgBuffer[RX_BUFFER_LENGTH];
        unsigned long rxLength = m_pUsbCanDllWrapper->VCI_Receive(it.value().deviceType, it.value().deviceIndex, it.value().canIndex, msgBuffer, RX_BUFFER_LENGTH, 10);
        if(rxLength == 0xFFFFFFFF) {
            // error
        }
        else {
            for(unsigned long i=0; i < rxLength; i++) {
                if(m_mapRecievers.contains(it.key()) && m_mapRecievers[it.key()].contains(msgBuffer[i].ID)) {
                    m_mapRecievers[it.key()][msgBuffer[i].ID]->receiveMsgCallback(msgBuffer[i]);
                }
            }
        }
    }
}
