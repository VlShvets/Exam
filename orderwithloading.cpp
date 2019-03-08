#include "orderwithloading.h"

OrderWithLoading::OrderWithLoading()
{
    setIsLoading(true);
}

OrderWithLoading::~OrderWithLoading()
{
}

void OrderWithLoading::setLoadingCost(const float _loadingCost)
{
    loadingCost = _loadingCost;
}

void OrderWithLoading::solveSumCost()
{
    setSumCost(getShippingCost() + getLoadingCost());
}
