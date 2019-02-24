#include "order.h"

float Order::stayingCost = 0.0;

void Order::setNum(int value)
{
    num = value;
}

void Order::setSurname(const QString &value)
{
    surname = value;
}

void Order::setShippingCost(float value)
{
    shippingCost = value;
}

void Order::setIsLoading(bool value)
{
    isLoading = value;
}

void Order::setLoadingCost(float value)
{
    loadingCost = value;
}

void Order::setStayingTime(const uint &value)
{
    stayingTime = value;
}

void Order::setSumCost(float value)
{
    sumCost = value;
}

void Order::setStayingCost(float value)
{
    stayingCost = value;
}
