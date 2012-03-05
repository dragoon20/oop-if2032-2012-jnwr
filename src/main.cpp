
#include "Latar/latar.h"
#include "Bidang/bidang.h"
#include <iostream>

using namespace std;

const char blank = ' ';

int main()
{
	int M,N,x;
	
	cout << "Masukkan ukuran latar belakang (M, N): ";
	cin >> M >> N;
	latar<char> background(M,N,(sel<char>(point(0,0),blank)));

	cout << "Masukkan kode bidang (dalam angka): ";
	cin >> x;
	bidang<char> shape(M,N,x,'*');
	
	cout << endl;
	cout << background;
	cout << endl;
	cout << shape;
	
	return 0;
}