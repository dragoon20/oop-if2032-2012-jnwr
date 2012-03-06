// File : point.h
//

#ifndef _POINT_H
#define _POINT_H

#include <iostream>

using namespace std;

class point { 
public:
	// 5 sekawan
	point ();												// ctor
	point (int, int);										// ctor dengan parameter
	point (const point&) ;									// cctor
	virtual ~point ();												// dtor
	point& operator= (const point& P1);								// operator assignment
	friend ostream& operator<< (ostream& out, point P); 	// operator ostream	
	
	// Getter & Setter
	int GetX () const;
	int GetY () const;
	void SetX (int);
	void SetY (int);

	// Predikat
	int IsOrigin ();
	// mengirim true (1) jika Current_Object =(0,0); false(0)jika bukan Origin
	
	int IsSumbuX ();
	// mengirim true jika Current_Object berada pada sumbu X
	
	int IsSumbuY ();
	// mengirim true jika Current_Object berada pada sumbu Y
	
	// Relasional
	int XLT(point P1);
	// true jika absis Current_Object lebih besar dari absis P1
	
	int YLT(point P1);
	// true jika ordinat Current_Object lebih besar dari ordinat P1

	// Method
	void move (int X, int Y);
	// memindahkan current_object sejauh X absis dan Y ordinat
	
	void mirror (point P);
	// membuat current_object menjadi cerminannya terhadap titik P

	void rotate (point P, int i); 
	// membuat current object diputar searah jarum jam terhadap titik P sejauh 90 (i = 1), 180 (i = 2), atau 270 (i = 3) derajat

	int kuadran ();
	// mengembalikan kuadran dari current_object. Mengembalikan 0 jika Point merupakan titik origin atau berada pada sumbu X atau sumbu Y

protected: 	// atribut ADT : private 
	int x; 	//absis
	int y; 	// ordinat

} ;
#endif
