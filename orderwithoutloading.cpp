#include "orderwithoutloading.h"

float OrderWithoutLoading::stayingCost = 0.0;

OrderWithoutLoading::OrderWithoutLoading()
{
    setIsLoading(false);
}

OrderWithoutLoading::~OrderWithoutLoading()
{
}

void OrderWithoutLoading::setStayingTime(const int _stayingTime)
{
    stayingTime = _stayingTime;
}

void OrderWithoutLoading::setStayingCost(const float _stayingCost)
{
    stayingCost = _stayingCost;
}

void OrderWithoutLoading::solveSumCost()
{
    setSumCost(getShippingCost() + getStayingTime() * getStayingCost());
}
