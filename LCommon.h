#ifndef LCOMMON_H
#define LCOMMON_H

// QT headers
#include <QVector>
#include <QMap>

// Our headers
#include "LObixObjTree.h"
#include "LDataValue.h"
#include "LSettingsRelier.h"
#include "LUniqueResource.h"
#include "LAttributes.h"

// list for data value
typedef QList<LDataValue>               LDataValueList;

// value map for each data
typedef QMap<QString, LDataValue>       LDataValueMap;

// Tree for configuration
typedef LTree<LObixObj>::ConstIterator  LObixObjIter;

// list of data names
typedef QList<QString>                  LDataNameList;

// iterator of data name list
typedef QListIterator<QString>          LDataNameListIter;

// map of attributes
typedef QMap<QString, LAttributes>      LAttributesMap;


#endif // LCOMMON_H
