#include "customer.h"

Customer::Customer(QString _surname)
{
    setSurname(_surname);
}

Customer::~Customer()
{
}

void Customer::setSurname(QString _surname)
{
    surname = _surname;
}
