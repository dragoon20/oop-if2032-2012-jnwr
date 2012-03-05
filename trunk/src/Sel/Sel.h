#ifndef SEL_H
#define SEL_H
#include "../Point/point.h"
template <class tes>

class sel<tes> : public point
{
    public:
        sel();
        sel(point, tes);
        virtual ~sel();
        sel(const sel&)
{
    //copy ctor
    x = other.x;
    y = other.y;
    t = other.t;
}
        sel& operator=(const sel&){ x = sel.x;
                                    y = sel.y;
                                    tes = sel.tes;}
        //Getter
        point getp(){
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
        void setp(const point& p);
{
    x=P.x;
    y=P.y;
}

        void sett(const tes& t);
{
    t=T;
}

    private:
        tes t;
};

#endif // SEL_H
