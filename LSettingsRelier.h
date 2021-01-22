#ifndef LSETTINGSRELIER_H
#define LSETTINGSRELIER_H

#include <QString>

#include "LTree.h"
#include "LObixObj.h"

// Tree for configuration
typedef LTree<LObixObj>::Iterator       LObixTreeMutableIter;
typedef LTree<LObixObj>::ConstIterator  LObixTreeIter;

class LSettingsRelier
{
public:
    LSettingsRelier() {}

    virtual ~LSettingsRelier() {}


    void setRegisterName(const QString& a_rName) {m_strRegisterName = a_rName;}

    QString getRegisterName() const {return m_strRegisterName;}


    void setMutableIterator(const LObixTreeMutableIter& a_rMutableIterator) {m_obixMutableIter = a_rMutableIterator;}


    virtual void parseFromSetting(LObixTreeIter a_obixIter) = 0;

    virtual void convertToSetting() = 0;


protected:
    QString m_strRegisterName;

    LObixTreeMutableIter m_obixMutableIter;


};

#endif // LSETTINGSRELIER_H
