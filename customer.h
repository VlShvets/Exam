#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "order.h"

#include <QString>
#include <QList>

struct Customer
{
private:
    QString surname;

public:
    Customer(QString _surname);
    ~Customer();

    void setSurname(QString _surname);
    inline QString getSurname() const;

    QList <Order *> orders;
};

QString Customer::getSurname() const
{
    return surname;
}

#endif // CUSTOMER_H
