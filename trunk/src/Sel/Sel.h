#ifndef SEL_H
#define SEL_H
#include "../Point/point.h
template <class tes>
class sel<tes>:public point
{
    public:
        sel();
        sel(point, tes);
        virtual ~sel();
        sel(const sel&);
        sel& operator=(const sel&);
        //Getter
        point getp();
        tes gett();

        //setter
        void setp(const point& p);
        void sett(const tes& t);


    private:
        tes t;
};

#endif // SEL_H
