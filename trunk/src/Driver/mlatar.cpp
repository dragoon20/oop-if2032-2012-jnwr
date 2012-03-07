//File : mlatar.cpp

#include "../Latar/latar.h"
#include <iostream>
const char blank = ' ';
using namespace std;
int main()
{
	latar<char> tes(5,6,(sel<char>(point(0,0),blank)));
	cout<<"nilai M ="<<tes.getm()<<endl;
	cout<<"nilai N ="<<tes.getn()<<endl;

	cout<<"ganti nilai M dengan 10"<<endl;
	tes.setm(10);
	cout<<"ganti nilai N dengan 10"<<endl;
	tes.setn(10);

	cout<<"nilai M ="<<tes.getm()<<endl;
	cout<<"nilai N ="<<tes.getn()<<endl;
}
