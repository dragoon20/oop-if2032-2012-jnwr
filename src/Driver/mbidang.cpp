//File : mlatar.cpp

#include "../Bidang/bidang.h"
#include <iostream>

using namespace std;
int main()
{
	bidang<char> bidtes(15,15,3,'#');
	cout<<"ukuran bidang ="<<bidtes.getukuran()<<endl;
	cout<<"ganti ukuran menjadi 4"<<endl;
	bidtes.setukuran(4);
	cout<<bidtes<<endl;

	cout<<"method move"<<endl;
	bidtes.move (1,1);
	cout<<bidtes<<endl;

	point P(5,5);
	cout<<"method mirror"<<endl;
	bidtes.mirror(P);
	cout<<bidtes<<endl;

	cout<<"method rotate"<<endl;
	bidtes.rotate(P,3);
	cout<<bidtes<<endl;


}
