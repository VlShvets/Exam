#ifndef XMLPARSER_H
#define XMLPARSER_H

#include "customer.h"
#include "orderwithloading.h"
#include "orderwithoutloading.h"

#include <QFile>
#include <QMultiMap>
#include <QDomDocument>

class XmlParser
{
public:
    XmlParser(QList <Customer *> &_customers);
    ~XmlParser();

    void readXml(QFile &file);

private:
    void traverseNode(const QDomNode& node);

    QDomDocument *doc;

    QList <Customer *> *customers;    
};

#endif // XMLPARSER_H
