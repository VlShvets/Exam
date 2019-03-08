#include "xmlparser.h"

XmlParser::XmlParser(QList<Customer *> &_customers)
{
    customers = &_customers;
}

XmlParser::~XmlParser()
{
    if(doc)
        delete doc;

    customers = nullptr;
}

void XmlParser::readXml(QFile &file)
{
    for(Customer *customer : *customers)
        delete customer;
    customers->clear();

    doc = new QDomDocument;
    if(doc->setContent(&file))
    {
        QDomElement domElement = doc->documentElement();
        traverseNode(domElement);
    }
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
                if(domElement.tagName() == "customer")
                    customers->push_back(new Customer(domElement.attribute("surname", "")));
                if(domElement.tagName() == "order")
                {
                    if(domElement.attribute("isLoading", "0").toInt() == 1)
                        customers->last()->orders.push_back(new OrderWithLoading());
                    else
                        customers->last()->orders.push_back(new OrderWithoutLoading());
                }
                else if(domElement.tagName() == "shippingCost")
                    customers->last()->orders.last()->setShippingCost(domElement.text().toFloat());
                else if(domElement.tagName() == "loadingCost")
                    customers->last()->orders.last()->setLoadingCost(domElement.text().toFloat());
                else if(domElement.tagName() == "stayingTime")
                    customers->last()->orders.last()->setStayingTime(domElement.text().toInt());
                else if(domElement.tagName() == "stayingCost")
                    OrderWithoutLoading::setStayingCost(domElement.attribute("cost", "0").toFloat());
            }
        }
        traverseNode(domNode);
        domNode = domNode.nextSibling();
    }
}
