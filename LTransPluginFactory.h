#ifndef LTRANSPLUGINFACTORY_H
#define LTRANSPLUGINFACTORY_H

#include <QObject>
#include "LTransmission.h"

///
/// This is the base class of the transmission plugins.
/// It's used to create the transmission instance.
/// transmission plugin interfaces.
///
class LTransPluginFactory : public QObject
{
    Q_OBJECT
public:
    //! Default class destractor, nothing to do here
    virtual ~LTransPluginFactory(){}

    //! create the transmission instance
    virtual LTransmission* createTransInstance() = 0;

protected:
    LTransPluginFactory(){}
};

Q_DECLARE_INTERFACE(LTransPluginFactory, "Lobster.LTransPluginFactory")

#endif // LTRANSPLUGINFACTORY_H
