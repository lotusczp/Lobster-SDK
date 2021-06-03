#include "LUsbAdcDataManager.h"
#include "LYavUsbAdcDllWrapper.h"

#define SCAN_INTERVAL_ms    200
#define BUFFER_SIZE         512

LUsbAdcDataManager::LUsbAdcDataManager(QObject *parent) : QObject(parent)
{
    m_pScanTimer = new QTimer;
    m_pScanTimer->setInterval(SCAN_INTERVAL_ms);
    connect(m_pScanTimer, &QTimer::timeout, this, &LUsbAdcDataManager::handleReceiveScan);

    connect(this, SIGNAL(startScan()), m_pScanTimer, SLOT(start()));
    connect(this, SIGNAL(stopScan()), m_pScanTimer, SLOT(stop()));

    m_pYavUsbAdcDllWrapper = new LYavUsbAdcDllWrapper;
}

LUsbAdcDataManager::~LUsbAdcDataManager()
{
    m_pScanTimer->stop();

    delete m_pScanTimer;
    delete m_pYavUsbAdcDllWrapper;
}

void LUsbAdcDataManager::setReceiveScanInterval(int ms)
{
    m_pScanTimer->setInterval(ms);
}

void LUsbAdcDataManager::startReceive(bool a_bStart)
{
    if(a_bStart){
        emit startScan();
    }
    else {
        emit stopScan();
    }
}

int LUsbAdcDataManager::findDevice()
{
    return m_pYavUsbAdcDllWrapper->FindDevice();
}

int LUsbAdcDataManager::openDevice()
{
    return m_pYavUsbAdcDllWrapper->OpenYavDevice(0);
}

void LUsbAdcDataManager::registerReceiver(LUsbAdcDataReceiver *a_pReceiver)
{
    if(a_pReceiver->getPortNum() < USBADC_CHANNEL_NUM) {
        m_mapReceivers[a_pReceiver->getPortNum()] = a_pReceiver;
    }
}

void LUsbAdcDataManager::handleReceiveScan()
{
    int DAQDataBuffer[BUFFER_SIZE]={0};
    int YavParam[1]={0};
    int CNTBuffer[2]={0};
    unsigned int IOBuffer[2]={0};

    m_pYavUsbAdcDllWrapper->GetYavData(0,DAQDataBuffer,BUFFER_SIZE,YavParam,CNTBuffer,IOBuffer);

    int groupNum = BUFFER_SIZE/USBADC_CHANNEL_NUM;
    unsigned long long sum[USBADC_CHANNEL_NUM] = {0, };
    for(int i=0; i<groupNum; i++) {
        for(int channel=0; channel<USBADC_CHANNEL_NUM; channel++) {
            sum[channel] += DAQDataBuffer[i*USBADC_CHANNEL_NUM+channel];
        }
    }

    unsigned long long result[USBADC_CHANNEL_NUM] = {0, };
    for(int port=0; port<USBADC_CHANNEL_NUM; port++) {
        result[port] = sum[port]/groupNum;
    }

    QMapIterator<int, LUsbAdcDataReceiver*> it(m_mapReceivers);
    while(it.hasNext()) {
        it.next();
        LUsbAdcDataReceiver* pReceiver = it.value();
        if(pReceiver) {
            pReceiver->receiveMsgCallback(result[pReceiver->getPortNum()], result[pReceiver->getPortNum()]*10.0/4095);
        }
    }
}
