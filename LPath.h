#ifndef LPATH_H
#define LPATH_H

#include <QObject>
#include <QString>
#include <QDir>

/// \note The path class fixes the current path at the beginning of starting
///       the lobster application.   Rusk met some problem of changing current
///       path on the fly (don't know why) during debugging.

/// Path enumeration, the sequence of the enums are the mapping in path string array,
/// So be careful of modifying the enum sequence.
enum SubPath {
    ePathRoot = 0,
    ePathImage,
    ePathScript,
    ePathDoc,
    ePathAudio,
    ePathProject,
    ePathDatalog,
    ePathPlugin,

    ePathNum
};

const QString c_strSubPathArray[ePathNum] = {
    "/",
    "/images/",
    "/script/",
    "/documentation/",
    "/audio/",
    "/projects/",
    "/datalog/",
    "/plugin/",
};

class LPath
{
public:
    /// This method should be called at very beginning of application start, it should only be called once.
    void setCurPath()
    {
        m_strCurPath = QDir::currentPath();
    }

    void setProjectPath(QString a_strPath)
    {
        m_strProjectPath = a_strPath;
    }

    /// Get the path according to enum input, if the file name is empty, return the folder path.
    QString getPath(SubPath a_eSubPath, QString a_strFile = "")
    {
        if(a_eSubPath == ePathProject) return m_strProjectPath+"/"+a_strFile;

        return m_strCurPath + getSubPath(a_eSubPath) + a_strFile;
    }

protected:
    /// Get the path according to input enumeration
    QString getSubPath(SubPath a_eSubPath)
    {
        return (a_eSubPath < ePathNum) ? c_strSubPathArray[a_eSubPath] : "";
    }

protected:
    QString m_strCurPath;         //!< Fixed current path
    QString m_strProjectPath;     //!< Fixed current path
};


#endif // LPATH_H
