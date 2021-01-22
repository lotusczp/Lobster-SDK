#ifndef LUSBADCDATAMANAGER_H
#define LUSBADCDATAMANAGER_H

#include <QObject>
#include <QList>
#include <QTimer>
#include "LUsbAdcDataReceiver.h"

#define USBADC_CHANNEL_NUM  (8)

//! \note   The UsbAdcDataManage only support single device right now.
//!
class LUsbAdcDataManager : public QObject
{
    Q_OBJECT
public:
    explicit LUsbAdcDataManager(QObject *parent = nullptr);
    virtual ~LUsbAdcDataManager();

    void setReceiveScanInterval(int ms);

    void startReceive(bool a_bStart);

    int findDevice();

    int openDevice();

    void registerReceiver(LUsbAdcDataReceiver* a_pReceiver);

signals:
    void startScan();

    void stopScan();

protected:
    void handleReceiveScan();

private:
    QTimer                          *m_pScanTimer;
    QList<LUsbAdcDataReceiver*>     m_listReceivers;
    LYavUsbAdcDllWrapper            *m_pYavUsbAdcDllWrapper;
};

#endif // LUSBADCDATAMANAGER_H
