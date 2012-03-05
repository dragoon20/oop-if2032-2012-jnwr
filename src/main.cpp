
#include "Latar/latar.h"
#include "Bidang/bidang.h"
#include <iostream>
#include <conio.h>

using namespace std;

const char blank = '_';

int getinput()
{
	if (_kbhit())
	{
		_getch();
		return 0;
	}
	return -1;
}

int main()
{
	int M,N,x;
	char c;
	
	cout << "Masukkan ukuran latar belakang (M, N): ";
	cin >> M >> N;
	latar<char> background(M,N,(sel<char>(point(0,0),blank)));

	cout << "Masukkan kode bidang (dalam angka): ";
	cin >> x;
	bidang<char> shape(M,N,x,'*');
	
	cout << endl << background << endl << shape << endl;

	cout << "Press any key..." << endl;
	while (getinput()==-1)
	{
	};
	
	return 0;
}