#ifndef SEL_H
#define SEL_H
#include "../Point/point.h"

template <class tes>
class sel : public point
{
	// atribut
	private:
		tes t;

    public:
		// 5 sekawan
        sel();
        sel(point, tes);
        ~sel();
        sel(const sel&);
        sel<tes>& operator=(const sel&);
        friend ostream& operator << (ostream& out, sel& s)
		{
			out<<s.t;
			return out;
		}
        //Getter Setter
        point getp();
        tes gett();
        void setp(const point& p);
        void sett(const tes& t);

};

template <class tes>
sel<tes>::sel()
{
}

template <class tes>
sel<tes>::sel(point P, tes T)
{
	t = T;
	x = P.GetX();
	y = P.GetY();
}

template <class tes>
sel<tes>::~sel()
{
}

template <class tes>
sel<tes>::sel(const sel<tes>& s)
{
	t = s.t;
	x = s.x;
	y = s.y;
}

template <class tes>
sel<tes>& sel<tes>::operator = (const sel& s)
{
	t = s.t;
	x = s.x;
	y = s.y;
	return *this;
}

//Getter Setter
template <class tes>
point sel<tes>::getp()
{
	return point(x,y);
}

template <class tes>
tes sel<tes>::gett()
{
	return t;
}

template <class tes>
void sel<tes>::setp(const point& p)
{
	x = p.GetX();
	y = p.GetY();
}

template <class tes>
void sel<tes>::sett(const tes& T)
{
	t = T;
}

#endif // SEL_H
