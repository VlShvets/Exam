#ifndef ORDER_H
#define ORDER_H

#include <QString>

struct Order
{
private:
    int num;
    QString surname;
    float shippingCost;
    bool isLoading;
    float loadingCost;
    uint stayingTime;
    float sumCost = 0.0;

    static float stayingCost;

public:
    inline int getNum() const;
    void setNum(int value);

    inline QString getSurname() const;
    void setSurname(const QString &value);

    inline float getShippingCost() const;
    void setShippingCost(float value);

    inline bool getIsLoading() const;
    void setIsLoading(bool value);

    inline float getLoadingCost() const;
    void setLoadingCost(float value);

    inline uint getStayingTime() const;
    void setStayingTime(const uint &value);

    inline float getSumCost() const;
    void setSumCost(float value);

    inline static float getStayingCost();
    static void setStayingCost(float value);
};

#endif // ORDER_H

int Order::getNum() const
{
    return num;
}

QString Order::getSurname() const
{
    return surname;
}

float Order::getShippingCost() const
{
    return shippingCost;
}

bool Order::getIsLoading() const
{
    return isLoading;
}

float Order::getLoadingCost() const
{
    return loadingCost;
}

uint Order::getStayingTime() const
{
    return stayingTime;
}

float Order::getSumCost() const
{
    return sumCost;
}


float Order::getStayingCost()
{
    return stayingCost;
}
