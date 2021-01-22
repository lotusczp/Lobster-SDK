#ifndef LTRANSMISSION_H
#define LTRANSMISSION_H


//---> Pick up the required headers <------------------------------------
// Qt headers
#include <QObject>
#include <QString>
#include <QList>
#include <QtPlugin>

// Our headers
#include "LCommon.h"



//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//------------------|  LTransmission class definition  |-----------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
///
/// This is the base class of the transmission plugins.  It defines the
/// transmission plugin interfaces.   The transmission should run in its
/// own thread.
///
class LTransmission : public QObject
{
    Q_OBJECT
public:
    //! Default class destractor, nothing to do here
    virtual ~LTransmission(){}

    //! Configurate the transmission, like port, baudrate, etc...
    virtual void configurate(const LObixObjIter &a_rConfigIter) = 0;

    //! return false if some error occurs when parsing the configuration tree,
    //! else return true and set the a_rWholeDataList the whole data list included in the configuration tree
    virtual bool getDataList(LDataNameList &a_rDataNameList) const = 0;

    //! Clear the current data map container and fill in new data
    //! The data is user cared variables.
    virtual void resetCaredDataList(const LDataNameList &a_rCaredDataNameList) = 0;

    //! Start data processing and transmission
    virtual void start() = 0;

    //! Stop data processing and transmission
    virtual void stop() = 0;

    //! Set the prefix of channel name to all the cared data value uploaded
    //! So that the main program can distinguish datas with the same name from different channels but using the same transmission plugin
    virtual void setChannelPrefix(const QString &a_rPrefix) = 0;

    //! Get the protocol name
    virtual const QString &getProtocolName() const = 0;

    //! Get the SW version number
    virtual const QString &getSwVersion() const = 0;

    //! Widget for configuration of this plugin
    virtual QWidget* getSettingsWidget() = 0;

    //! Settings relier of this plugin
    virtual LSettingsRelier* getSettingsRelier() = 0;

    //! Tool widget of this plugin
    virtual QWidget* getToolWidget() = 0;

    //! Set value by lobster main program
    virtual void setDataValue(QString a_strDataName, LDataValue a_dataValue) = 0;

    //! Set the unique resource access interface
    virtual void setUniqueResource(const LUniqueResource&) {}

    //! Force to pull attributes from this plugin
    virtual void pullAttributes() {}

    //! Force to pull value of a certain point from this plugin
    virtual void pullDataValue(QString a_strDataName) {}

signals:
    //! Notify signal for passing received data to user by data list
    void notifySingleVar(QString a_strDataName, LDataValueList a_lstDataValue);

    //! Notify signal for passing received data to user by a map of data
    void notifyMultiVar(LDataValueMap a_mapDataValue);

    //! Error signal for passing error code and related information to user
    void errorInfo(qint32 a_iErrorCode, QString a_strDescription, QString a_strSource);

    //! Notify signal for passing a map of attributes to user
    void notifyVarAttributes(LAttributesMap a_mapAttributes);

protected:
    //! Default class constractor, instantiate its derived class only
    LTransmission(){}

};

Q_DECLARE_INTERFACE(LTransmission, "Lobster.LTransmission")

#endif // LTRANSMISSION_H
