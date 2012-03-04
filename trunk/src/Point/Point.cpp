// File : point.cpp
//

#include "point.h"
using namespace std ;

// 5 sekawan
point::point ()								// ctor
{}

point::point (int Newx, int Newy)			// ctor dengan parameter
{
	x = Newx;
	y = Newy;
}

point::point (const point& P) 
{
	x = P.x ;
	y = P.y ;
}

point::~point ()							// dtor
{}

point& point::operator= (const point& P1)				// operator assignment
{
	x = P1.x ;
	y = P1.y ;
	return *this ;
}

ostream &point::operator<< (ostream& out, const point& P)	// operator ostream	
{
	out << "(" ; out  << P.x ; out << "," ; out  << P.y ; out << ")" ;
	return out ;
}

// Getter & Setter
int point::GetX ()
{
	return x;
}

int point::GetY ()
{
	return y;
}

void point::SetX (int NewX)
{
	x = NewX;
}

void point::SetY (int NewY)
{
	y = NewY;
}

// Predikat
int point::IsOrigin ()
// mengirim true (1) jika Current_Object =(0,0); false(0)jika bukan Origin
{	
	return (x == 0 && y == 0);
}	

int point::IsSumbuX ()
// mengirim true jika Current_Object berada pada sumbu X
{
	return (GetY() == 0) ;
}

int point::IsSumbuY ()
// mengirim true jika Current_Object berada pada sumbu Y
{
	return (GetX() == 0) ;
}

// Relasional	
int point::XLT(point P1)
// true jika absis Current_Object lebih besar dari absis P1
{
	return (GetX() > P1.GetX());
}

int point::YLT(point P1)
// true jika ordinat Current_Object lebih besar dari ordinat P1
{
	return (GetY() > P1.GetY());
}

// Method
void point::move (int X, int Y)
// memindahkan current_object sejauh X absis dan Y ordinat
{
	int newabsis ; int newordinat ;
	newabsis = GetX() + X ;
	newordinat = GetY() + Y ;
	SetX(newabsis) ; SetY(newabsis) ;
}

void point::mirror (point P)
// membuat current_object menjadi cerminannya terhadap titik P
{
	int newabsis ; int newordinat ;
	newabsis = -1 * (GetX() - P.GetX()) + P.GetX() ;
	newordinat = -1 * (GetY() - P.GetY()) + P.GetY() ;
	SetX(newabsis) ; SetY(newabsis) ;
}

void point::rotate (point P, int i)
// membuat current object diputar searah jarum jam terhadap titik P sejauh 90 (i = 1), 180 (i = 2), atau 270 (i = 3) derajat
{
	if (i == 1) 
	{
		int newabsis ; int newordinat ;
		newabsis = GetY() ;
		newordinat = -1 * (GetX() - P.GetY()) + P.GetY() ;
		SetX(newabsis) ; SetY(newabsis) ;
	}
	else if (i == 2)
	{
		mirror(P) ;
	}
	else if (i == 3)
	{
		int newabsis ; int newordinat ;
		newabsis = -1 * (GetY() - P.GetX()) + P.GetX() ;
		newordinat = GetX() ;
		SetX(newabsis) ; SetY(newabsis) ;
	}
	else
	{
		cout << "Masukan i salah!" << endl ;
	}
}

int point::kuadran ()
// mengembalikan kuadran dari current_object. Mengembalikan 0 jika point merupakan titik origin atau berada pada sumbu X atau sumbu Y
{
	point P(0,0) ;
	if (IsOrigin() || IsSumbuX() || IsSumbuY())
		return 0 ;
	else if (XLT(P) && YLT(P))
		return 1 ;
	else if (!XLT(P) && YLT(P))
		return 2 ;
	else if (!XLT(P) && !YLT(P))
		return 3 ;
	else if (XLT(P) && !YLT(P))
		return 4 ;
}
