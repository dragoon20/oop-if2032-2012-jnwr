//File : mbidang.cpp

#include "../Bidang/bidang.h"
#include <iostream>

using namespace std;
int main()
{
	bidang<char> bidtes(15,15);
	cout<<"segi bidang ="<<bidtes.getsegi()<<endl;
	cout<<"ganti segi menjadi 4"<<endl;
	bidtes.setsegi(4);
	cout<<bidtes<<endl;

	cout<<"method move"<<endl;
	bidtes.move (1,1);
	cout<<bidtes<<endl;

	cout<<"method rotate"<<endl;
	bidtes.rotate(3);
	cout<<bidtes<<endl;

}
