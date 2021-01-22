#ifndef LOBIXOBJ_H
#define LOBIXOBJ_H

#include <QMap>
#include <QString>

typedef QMap<QString, QString> PropertyMap;

//! type of obix
enum LObixType {
    eObj,
    eStr,
    eList,
    eInt,
    eReal,
    eEnum,
    eRelTime
};

//! element type of search table
struct ObixTypeTableElement {
    QString str;
    LObixType eType;
};

//! search table for type
const ObixTypeTableElement c_obixTypeSearchTable[] = {
    {"obj", eObj},
    {"str", eStr},
    {"list", eList},
    {"int", eInt},
    {"real", eReal},
    {"enum", eEnum},
    {"reltime", eRelTime},

    //this is the flag of end, do not use it
    {"end element", eObj}
};

class LObixObj
{
public:
    //! default constructor
    LObixObj() {}
    //! an easier constructor
    LObixObj(const QString &a_rstrType, const QString &a_rstrKey, const QString &a_rstrValue) {
        const ObixTypeTableElement* it = c_obixTypeSearchTable;
        while(it->str != "end element") {
            if (a_rstrType == it->str) {
                m_eType = it->eType;
                break;
            }
            it++;
        }
        m_mapProps[a_rstrKey] = a_rstrValue;
    }

    //! set the type of obix obj using string
    void setType(const QString &a_rstrType)
    {
        const ObixTypeTableElement* it = c_obixTypeSearchTable;
        while(it->str != "end element") {
            if (a_rstrType == it->str) {
                m_eType = it->eType;
                break;
            }
            it++;
        }
    }

    //! get the type information
    LObixType getType() const {return m_eType;}

    //! get the type information as string format
    QString getTypeString() const
    {
        QString result = "";
        const ObixTypeTableElement* it = c_obixTypeSearchTable;
        while(it->str != "end element") {
            if (m_eType == it->eType) {
                result = it->str;
            }
            it++;
        }
        return result;
    }

    //! add a property
    void addProperty(const QString &a_rstrKey, const QString &a_rstrValue) {m_mapProps[a_rstrKey] = a_rstrValue;}

    //! get a property with the key
    QString getProperty(const QString &a_rstrKey) const {if(m_mapProps.contains(a_rstrKey)) return m_mapProps[a_rstrKey]; else return "";}

    //! get the whole property map
    const PropertyMap &getPropertyMap() const {return m_mapProps;}

    //! overload "==" operator
    //! \note the order of properties should be the same too
    //!       ["is"]["name"] ["val"]["1"]  and ["val"]["1"] ["is"]["name"] will be considered as different objects
    bool operator == (const LObixObj& other) const
    {
        if ( (this->m_eType == other.m_eType)
             && (this->m_mapProps == other.m_mapProps) ) {
            return true;
        }
        else {
            return false;
        }
    }


private:
    LObixType m_eType;          //!< type of obix obj

    PropertyMap m_mapProps;     //!< proper map, which is [key][value] pairs
};

#endif // LOBIXOBJ_H
