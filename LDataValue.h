#ifndef LDATAVALUE_H
#define LDATAVALUE_H

#include <QObject>
#include <QDateTime>

/// \note The implementation of the following classes
/// must exist in this header file.   The Lobster &
/// transmission plugin both need them.

class LDataValue
{
public:
    enum DataStatus {
        eAvailable = 0,
        eNotAvailable
    };

    enum CommStatus {
        eCommLoss = 0,
        eNormal = 1
    };

    LDataValue() : m_dValue(0.0), m_iAbsTime(0){m_eDataStatus = eNotAvailable; m_eCommStatus = eNormal;}
    ~LDataValue(){}

    void set(double a_dlValue, qint64 a_iAbsTime = -1, DataStatus a_eStatus = eAvailable)
    {
        m_dValue = a_dlValue;

        if (a_iAbsTime == -1) {
            m_iAbsTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
        }
        else {
            m_iAbsTime = a_iAbsTime;
        }

        m_eDataStatus = a_eStatus;
    }

    double getValue() const
    {
        return m_dValue;
    }

    qint64 getAbsTime() const
    {
        return m_iAbsTime;
    }

    void setStatus(DataStatus a_eStatus)
    {
        m_eDataStatus = a_eStatus;
    }

    DataStatus getStatus() const
    {
        return m_eDataStatus;
    }

    void setCommStatus(CommStatus a_eCommStatus)
    {
        m_eCommStatus = a_eCommStatus;
    }

    CommStatus getCommStatus() const
    {
        return m_eCommStatus;
    }

protected:
    double      m_dValue;
    qint64      m_iAbsTime;

    DataStatus  m_eDataStatus;

    CommStatus  m_eCommStatus;
};


#endif // LDATAVALUE_H
