// File : mPoint.cpp
//

#include "Point.h"
#include <iostream>
#include <ostream>
using namespace std ;

int main () {
	point P1 ;
	P1.SetX(0) ;
	P1.SetY(0) ;
	cout << "Dibentuk sebuah point P1" << endl ;
	cout << "P1 = " << P1 << endl ;
	cout << endl ; 
	
	cout << "Dibentuk sebuah point P2" << endl ;
	point P2(1,1) ;
	cout << "P2 = " << P2 << endl ;
	cout << endl ;
	
	cout << "Dibentuk sebuah point P3 = P2" << endl ;
	point P3 = P2 ;
	cout << "P3 = " << P3 << endl ;
	cout << endl ;
	
	cout << "Apakah titik P1 merupakan titik origin?" << endl ;
	if (P1.IsOrigin())
		cout << "Ya" << endl ;
	else
		cout << "Tidak" << endl ;
	cout << endl ;
	
	cout << "Apakah titik P2 merupakan titik origin?" << endl ;
	if (P2.IsOrigin())
		cout << "Ya" << endl ;
	else
		cout << "Tidak" << endl ;
	cout << endl ;
	
	cout << "P3 dipindahkan sebanyak 3 ke arah sumbu X dan 1 ke arah sumbu Y" << endl ;
	P3.move(3,1) ;
	cout << "P3 = " << P3 << endl ;
	cout << endl ;
	
	cout << "P3 dicerminkan terhadap titik P2" << endl ;
	P3.mirror(P2) ;
	cout << "P3 = " << P3 << endl ;
	cout << endl ;
	
	cout << "P3 diputar 90 derajat terhadap titik P2" << endl ;
	P3.rotate(P2, 1) ;
	cout << "P3 = " << P3 << endl ;
	cout << endl ;
	
	cout << "P3 diputar 270 derajat terhadap titik P2" << endl ;
	P3.rotate(P2, 3) ;
	cout << "P3 = " << P3 << endl ;
	cout << endl ;
	
	cout << "P3 diputar 180 derajat terhadap titik P2" << endl ;
	P3.rotate(P2, 2) ;
	cout << "P3 = " << P3 << endl ;
	cout << endl ;
	
	cout << "Kuadran dari P3 adalah : " << P3.kuadran() << endl ;
	cout << "Kuadran dari P2 adalah : " << P2.kuadran() << endl ;
	cout << "Kuadran dari P1 adalah : " << P1.kuadran() << endl ;
}