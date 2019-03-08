#ifndef ORDERWITHLOADING_H
#define ORDERWITHLOADING_H

#include "order.h"

struct OrderWithLoading : public Order
{
private:
    float loadingCost;

public:
    OrderWithLoading();
    ~OrderWithLoading();

    void setLoadingCost(const float _loadingCost);
    inline float getLoadingCost() const;

    void solveSumCost();
};

float OrderWithLoading::getLoadingCost() const
{
    return loadingCost;
}

#endif // ORDERWITHLOADING_H
