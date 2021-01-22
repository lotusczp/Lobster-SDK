#ifndef LATTRIBUTES_H
#define LATTRIBUTES_H

#include <QString>
#include <QMap>

class LAttributes
{
public:
    typedef QMap<int, QString> Enums;

    LAttributes()
    {
        m_strUnit = "NA";
    }

    //! Get the Unit
    const QString& getUnit() const
    {
        return m_strUnit;
    }

    //! Set the unit
    void setUnit(const QString& a_rstrUnit)
    {
        m_strUnit = a_rstrUnit;
    }

    //! Get the size of Enum
    int getEnumsSize() const
    {
        return m_mapEnums.size();
    }

    //! Get the enums
    const Enums& getEnums() const
    {
        return m_mapEnums;
    }

    //! Insert the pair to enum
    void insertEnum(int a_iIndex, const QString &a_rstrName)
    {
        m_mapEnums.insert(a_iIndex, a_rstrName);
    }

    //! Unite another enums map with the current one
    void uniteEnums(const Enums& a_rOther)
    {
        m_mapEnums.unite(a_rOther);
    }

    //! Remove this enum, if this enum does not exist, do nothing
    void removeEnum(int a_iIndex)
    {
        if(m_mapEnums.contains(a_iIndex)) {
            m_mapEnums.remove(a_iIndex);
        }
    }

    void setWritable(bool a_bIsWritable)
    {
        m_bWritable = a_bIsWritable;
    }

    bool writable() const
    {
        return m_bWritable;
    }

private:
    QString     m_strUnit;      //!< Attribute - unit
    Enums       m_mapEnums;     //!< Attribute - enums
    bool        m_bWritable;    //!< Attribute - writable
};

#endif // LATTRIBUTES_H
