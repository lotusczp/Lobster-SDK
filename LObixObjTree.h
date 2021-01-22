#ifndef LOBIXOBJTREE_H
#define LOBIXOBJTREE_H

// QT headers
#include <QFile>
#include <QXmlStreamReader>

// Our headers
#include "LObixObj.h"
#include "LTree.h"

typedef LTree<LObixObj> LObixObjTree;

class LObixObjTreeCreator
{
public:
    LObixObjTreeCreator() {}
    ~LObixObjTreeCreator() {}

    static LObixObjTree *create(const QString &a_rstrType,
                         const QString &a_rstrKey,
                         const QString &a_rstrValue)
    {
        LObixObj theRoot(a_rstrType, a_rstrKey, a_rstrValue);
        return new LObixObjTree(theRoot);
    }

    static void destroy(LObixObjTree *&a_rpTree)
    {
        delete a_rpTree, a_rpTree = NULL;
    }

    static bool load(LObixObjTree *a_pTree, QFile &a_rFile)
    {
        QXmlStreamReader theReader(&a_rFile);
        return parseObixXml(a_pTree, theReader);
    }

    static bool load(LObixObjTree *a_pTree, QString &a_rstrXml)
    {
        QXmlStreamReader theReader(a_rstrXml);
        return parseObixXml(a_pTree, theReader);
    }

protected:

    /// This method parse the input XML stream into a ObixObj tree.
    static bool parseObixXml(LObixObjTree *a_pTree, QXmlStreamReader &a_rReader)
    {
        const int ciStartElement = 0;
        const int ciEndElement = 1;
        int lastElement = ciStartElement;

        // Iterator for parsing
        LObixObjTree::Iterator it(*a_pTree);
        // Move to the root node
        it.moveToRoot();

        // Loop to parse the XML file
        while (!a_rReader.atEnd()) {
            // Is it the start element?
            if (a_rReader.isStartElement()) {
                // Yes. Temporary obix object to save parsing result
                LObixObj obixObjTmp;
                // First of all, set the XML tag which is also Obix type here!
                obixObjTmp.setType(a_rReader.name().toString());
                // Is there any attributes?
                if (!a_rReader.attributes().isEmpty()) {
                    // Yes. Set the Obix properties.
                    QVectorIterator<QXmlStreamAttribute> iter(a_rReader.attributes());
                    while(iter.hasNext()) {
                        QXmlStreamAttribute attribute = iter.next();
                        obixObjTmp.addProperty(attribute.name().toString(), attribute.value().toString());
                    }
                }
                // If last element is start element, then this node should be its child
                if (lastElement == ciStartElement) {
                    it.addChild(obixObjTmp);
                }
                // If last element is end element, then this node should be its sibling
                else if(lastElement == ciEndElement) {
                    while(it.hasSibling()) {
                        it.moveToNextSibling();
                    }
                    it.insertSibling(obixObjTmp);
                }
                lastElement = ciStartElement;
            }
            // Is it the end element
            else if(a_rReader.isEndElement()) {
                // Yes. If last element is start element, just complete the node, nothing to do
                // If last element is end element, move the iterator to its parent
                if (lastElement == ciEndElement) {
                    it.moveToParent();
                }
                lastElement = ciEndElement;
            }
            // Deal with the next element
            a_rReader.readNext();
        }

        it.moveToRoot();

        return true;
    }

};

#endif // LOBIXOBJTREE_H
