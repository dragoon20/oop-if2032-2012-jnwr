#include "Sel.h"

Sel::Sel()
{
    //ctor
}

Sel::~Sel()
{
    //dtor
}

Sel::Sel(const Sel& other)
{
    //copy ctor
    x = other.x;
    y = other.y;
    t = other.t;
}

//Getter
point getp()
{
    point P;
    P.x=x;
    P.y=y;
    return P;
}

tes gett()
{
    tes T;
    T=t;
    return T;
}

//setter
void setp(const point& p)
{
    x=P.x;
    y=P.y;
}

void sett(const tes& T)
{
    t=T;
}
