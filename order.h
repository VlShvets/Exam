#ifndef ORDER_H
#define ORDER_H

struct Order
{
private:
    bool isLoading;
    float shippingCost;    
    float sumCost = 0.0;

public:
    void setIsLoading(bool _isLoading);
    inline bool getIsLoading() const;

    void setShippingCost(float _shippingCost);
    inline float getShippingCost() const;

    void setSumCost(float _sumCost);
    inline float getSumCost() const;

    virtual void setLoadingCost(const float) {}
    virtual inline float getLoadingCost() const;

    virtual void setStayingTime(const int) {}
    virtual inline int getStayingTime() const;

    virtual void solveSumCost() = 0;
};

float Order::getShippingCost() const
{
    return shippingCost;
}

bool Order::getIsLoading() const
{
    return isLoading;
}

float Order::getSumCost() const
{
    return sumCost;
}

float Order::getLoadingCost() const
{
    return 0.0;
}

int Order::getStayingTime() const
{
    return 0;
}

#endif // ORDER_H
