#include "xmlparser.h"

XmlParser::XmlParser(QList <Order *> *_orders)
{
    orders = _orders;
}

XmlParser::~XmlParser()
{
    orders = nullptr;

    if(doc)
        delete doc;
}

QString XmlParser::createXml()
{
    QString output;
    doc = new QDomDocument("orders");
    QDomElement domElement = doc->createElement("orders");
    doc->appendChild(domElement);

    QDomElement domElement2 = doc->createElement("stayingCost");
    QDomAttr domAttr = doc->createAttribute("cost");
    domAttr.setValue(QString::number(Order::getStayingCost()));
    domElement2.setAttributeNode(domAttr);
    domElement.appendChild(domElement2);

    int iNumber = 0;

    for(Order *order : *orders)
    {
        ++iNumber;

        QDomElement orderLine = makeOrder(order->getSurname(),
                                          QString::number(order->getShippingCost()),
                                          QString::number(order->getIsLoading()),
                                          QString::number(order->getLoadingCost()),
                                          QString::number(order->getStayingTime()),
                                          iNumber);

        domElement.appendChild(orderLine);
    }

    output = doc->toString();
    delete doc;

    return output;
}

void XmlParser::readXml(QFile &file)
{
    for(Order *order : *orders)
        delete order;
    orders->clear();

    doc = new QDomDocument;
    if(doc->setContent(&file))
    {
        QDomElement domElement = doc->documentElement();
        traverseNode(domElement);
    }
}

QDomElement XmlParser::makeOrder(const QString &surname,
                                 const QString &shippingCost,
                                 const QString &isLoading,
                                 const QString &loadingCost,
                                 const QString &stayingTime,
                                 const int num)
{
    QDomElement domElement = makeElement("order", QString().setNum(num));

    domElement.appendChild(makeElement("surname", "", surname));
    domElement.appendChild(makeElement("shippingCost", "", shippingCost));
    domElement.appendChild(makeElement("isLoading", "", isLoading));
    domElement.appendChild(makeElement("loadingCost", "", loadingCost));
    domElement.appendChild(makeElement("stayingTime", "", stayingTime));

    return domElement;
}

QDomElement XmlParser::makeElement(const QString &strName, const QString &strAttr, const QString &strText)
{
    QDomElement domElement = doc->createElement(strName);

    if(!strAttr.isEmpty())
    {
        QDomAttr domAttr = doc->createAttribute("number");
        domAttr.setValue(strAttr);
        domElement.setAttributeNode(domAttr);
    }

    if(!strText.isEmpty())
    {
        QDomText domText = doc->createTextNode(strText);
        domElement.appendChild(domText);
    }

    return domElement;
}

void XmlParser::traverseNode(const QDomNode &node)
{
    QDomNode domNode = node.firstChild();
    while(!domNode.isNull())
    {
        if(domNode.isElement())
        {
            QDomElement domElement = domNode.toElement();
            if(!domElement.isNull())
            {
                if(domElement.tagName() == "order")
                {
                    orders->append(new Order);
                    orders->last()->setNum(domElement.attribute("number", "0").toInt());
                }
                else if(domElement.tagName() == "surname")
                    orders->last()->setSurname(domElement.text());
                else if(domElement.tagName() == "shippingCost")
                    orders->last()->setShippingCost(domElement.text().toFloat());
                else if(domElement.tagName() == "isLoading")
                    orders->last()->setIsLoading(domElement.text() == "1" ? true : false);
                else if(domElement.tagName() == "loadingCost")
                    orders->last()->setLoadingCost(domElement.text().toFloat());
                else if(domElement.tagName() == "stayingTime")
                    orders->last()->setStayingTime(domElement.text().toInt());
                else if(domElement.tagName() == "stayingCost")
                    Order::setStayingCost(domElement.attribute("cost", "0").toFloat());
            }
        }
        traverseNode(domNode);
        domNode = domNode.nextSibling();
    }
}
