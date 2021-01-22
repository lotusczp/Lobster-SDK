#ifndef LCANDATAMANAGER_H
#define LCANDATAMANAGER_H

#include <QObject>
#include <QMap>
#include <QTimer>
#include <QMutex>
#include "LCanDataReceiver.h"

#define DEFAULT_DEV         VCI_USBCAN2
#define RX_BUFFER_LENGTH    1000


typedef VCI_CAN_OBJ     CanObj;
typedef VCI_BOARD_INFO  CanInfo;
typedef VCI_CAN_STATUS  CanStatus;

enum CanBaudRate
{
    eCanBaudRate_1Mbps,
    eCanBaudRate_500Kbps,
    eCanBaudRate_250Kbps,
};



class LCanDataManager : public QObject
{
    Q_OBJECT
public:
    explicit LCanDataManager(QObject *parent = nullptr);
    virtual ~LCanDataManager();

    void startReceive(bool a_bStart);

    unsigned long openDevice(unsigned long DeviceInd=0, unsigned long DeviceType=DEFAULT_DEV);

    unsigned long closeDevice(unsigned long DeviceInd=0, unsigned long DeviceType=DEFAULT_DEV);

    unsigned long initCAN(CanBaudRate a_eBaudrate, unsigned long DeviceInd=0, unsigned long CANInd=0, unsigned long DeviceType=DEFAULT_DEV);

    unsigned long readBoardInfo(unsigned int *pErrorCode, unsigned long DeviceInd=0, unsigned long CANInd=0, unsigned long DeviceType=DEFAULT_DEV);

    unsigned long readErrInfo(unsigned int *pErrorCode, unsigned long DeviceInd=0, unsigned long CANInd=0, unsigned long DeviceType=DEFAULT_DEV);

    unsigned long setReference(unsigned long RefType, void* pData, unsigned long DeviceInd=0, unsigned long CANInd=0, unsigned long DeviceType=DEFAULT_DEV);

    unsigned long startCAN(unsigned long DeviceInd=0, unsigned long CANInd=0, unsigned long DeviceType=DEFAULT_DEV);

    unsigned long resetCAN(unsigned long DeviceInd=0, unsigned long CANInd=0, unsigned long DeviceType=DEFAULT_DEV);

    unsigned long clearBuffer(unsigned long DeviceInd=0, unsigned long CANInd=0, unsigned long DeviceType=DEFAULT_DEV);

    unsigned long transmit(CanObj *pSend, unsigned long len, unsigned long DeviceInd=0, unsigned long CANInd=0, unsigned long DeviceType=DEFAULT_DEV);

    void registerReceiver(LCanDataReceiver* a_pReceiver, unsigned long DeviceInd=0, unsigned long CANInd=0, unsigned long DeviceType=DEFAULT_DEV);

signals:
    void startScan();

    void stopScan();

protected:
    void handleReceiveScan();

private:
    struct Info
    {
        unsigned long deviceIndex;
        unsigned long canIndex;
        unsigned long deviceType;

        Info(unsigned long DeviceInd=0, unsigned long CANInd=0, unsigned long DeviceType=DEFAULT_DEV)
            : deviceIndex(DeviceInd),
              canIndex(CANInd),
              deviceType(DeviceType)
        {}
    };
private:
    QTimer                          *m_pScanTimer;

    QMap<QString, Info>             m_mapInfo;
    QMap<QString, QMap<unsigned int, LCanDataReceiver*>> m_mapRecievers;
    LUsbCanDllWrapper               *m_pUsbCanDllWrapper;
};

#endif // LCANDATAMANAGER_H
