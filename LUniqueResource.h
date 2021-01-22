#ifndef LUNIQUERESOURCE_H
#define LUNIQUERESOURCE_H

#include <QNetworkAccessManager>
#include "LPath.h"
#include "LCanDataManager.h"
#include "LUsbAdcDataManager.h"
#include "LDbcManagerDllWrapper.h"
#include "LTmctlWrapper.h"

class LUniqueResource {
public:
    LUniqueResource() :
        pNetworkMgr(nullptr),
        pPath(nullptr),
        pUsbCan(nullptr),
        pUsbAdc(nullptr),
        pDbcMgr(nullptr),
        pTmctl(nullptr)
    {}

    QNetworkAccessManager       *pNetworkMgr;   //!< Network manager, one instance should be enough for an application
    LPath                       *pPath;         //!< Path handler, there must be one instance for an application
    LCanDataManager             *pUsbCan;       //!<
    LUsbAdcDataManager          *pUsbAdc;
    LDbcManagerDllWrapper       *pDbcMgr;
    LTmctlWrapper               *pTmctl;
};

class LUniqueResourceMgr
{
public:
    static LUniqueResourceMgr* instance()
    {
        // Do we have an object yet?
        if(s_pInstance == nullptr) {
          // No, create it
          s_pInstance = new LUniqueResourceMgr();
        }
        // Return the instance ptr
        return s_pInstance;
    }

    static void destroy()
    {
        // Clean up the pointer
        if(s_pInstance != nullptr) {
            delete s_pInstance, s_pInstance = NULL;
        }
    }

    //! get the resources pointers
    const LUniqueResource& getUniqueResource ()
    {
        return m_uniqueResource;
    }

private:
    LUniqueResourceMgr()
    {
        m_uniqueResource.pNetworkMgr = new QNetworkAccessManager;
        m_uniqueResource.pPath = new LPath;
        m_uniqueResource.pUsbCan = new LCanDataManager;
        m_uniqueResource.pUsbAdc = new LUsbAdcDataManager;
        m_uniqueResource.pDbcMgr = new LDbcManagerDllWrapper;
        m_uniqueResource.pTmctl = new LTmctlWrapper;
    }

    ~LUniqueResourceMgr()
    {
        delete m_uniqueResource.pNetworkMgr;
        delete m_uniqueResource.pPath;
        delete m_uniqueResource.pUsbCan;
        delete m_uniqueResource.pUsbAdc;
        delete m_uniqueResource.pDbcMgr;
        delete m_uniqueResource.pTmctl;
    }

private:
    static LUniqueResourceMgr   *s_pInstance;       //!< instance ptr

    LUniqueResource             m_uniqueResource;   //!< resources pointers
};

//! \brief  Short cut for accessers
//! \note   Do NOT use them in plugins
#define PATH_ACCESSER       LUniqueResourceMgr::instance()->getUniqueResource().pPath
#define NET_ACCESSER        LUniqueResourceMgr::instance()->getUniqueResource().pNetworkMgr
#define USBCAN_ACCESSER     LUniqueResourceMgr::instance()->getUniqueResource().pUsbCan
#define USBADC_ACCESSER     LUniqueResourceMgr::instance()->getUniqueResource().pUsbAdc
#define DBCMGR_ACCESSER     LUniqueResourceMgr::instance()->getUniqueResource().pDbcMgr
#define TMCTL_ACCESSER      LUniqueResourceMgr::instance()->getUniqueResource().pTmctl


#endif // LUNIQUERESOURCE_H
