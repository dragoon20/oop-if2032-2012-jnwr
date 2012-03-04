// File : Point.h
//

#ifndef _Point_H
#define _Point_H

#include <iostream>

using namespace std;

class Point { 
public:
	// 5 sekawan
	Point ();												// ctor
	Point (int, int);										// ctor dengan parameter
	Point (const Point&) ;									// cctor
	~Point ();												// dtor
	Point& operator= (const Point& P1);								// operator assignment
	friend ostream &operator<< (ostream& out, const Point& P); 	// operator ostream	
	
	// Getter & Setter
	int GetX ();
	int GetY ();
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
	int XLT(Point P1);
	// true jika absis Current_Object lebih besar dari absis P1
	
	int YLT(Point P1);
	// true jika ordinat Current_Object lebih besar dari ordinat P1

	// Method
	void move (int X, int Y);
	// memindahkan current_object sejauh X absis dan Y ordinat
	
	void mirror (Point P);
	// membuat current_object menjadi cerminannya terhadap titik P

	void rotate (Point P, int i); 
	// membuat current object diputar searah jarum jam terhadap titik P sejauh 90 (i = 1), 180 (i = 2), atau 270 (i = 3) derajat

	int kuadran ();
	// mengembalikan kuadran dari current_object. Mengembalikan 0 jika Point merupakan titik origin atau berada pada sumbu X atau sumbu Y

private: 	// atribut ADT : private 
	int x; 	//absis
	int y; 	// ordinat

} ;
#endif
