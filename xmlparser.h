#ifndef XMLPARSER_H
#define XMLPARSER_H

#include "order.h"

#include <QList>
#include <QDomDocument>

class XmlParser
{
public:
    XmlParser(QList <Order *> *orders);
    ~XmlParser();

    QString createXml();
    void readXml(QFile &file);

private:
    QList <Order *> *orders;

    QDomDocument *doc;

    QDomElement makeOrder(const QString &surname,
                          const QString &shippingCost,
                          const QString &isLoading,
                          const QString &loadingCost,
                          const QString &stayingTime,
                          const int num);

    QDomElement makeElement(const QString &strName,
                            const QString &strAttr = QString(),
                            const QString &strText = QString());

    void traverseNode(const QDomNode& node);
};

#endif // XMLPARSER_H
