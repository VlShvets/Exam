#ifndef ORDERWITHOUTLOADING_H
#define ORDERWITHOUTLOADING_H

#include "order.h"

struct OrderWithoutLoading : public Order
{
private:
    int stayingTime;

    static float stayingCost;

public:    
    OrderWithoutLoading();
    ~OrderWithoutLoading();

    void setStayingTime(const int _stayingTime);
    inline int getStayingTime() const;

    static void setStayingCost(const float _stayingCost);
    inline static float getStayingCost();

    void solveSumCost();
};

int OrderWithoutLoading::getStayingTime() const
{
    return stayingTime;
}

float OrderWithoutLoading::getStayingCost()
{
    return stayingCost;
}

#endif // ORDERWITHOUTLOADING_H
