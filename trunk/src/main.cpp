
#include "Latar/latar.h"
#include "Bidang/bidang.h"
#include "Matrix/matrix.h"
#include <iostream>
#include <conio.h>
#include <cstdlib>

using namespace std;

const char blank = ' ';

int getinput()
{
	if (_kbhit())
	{
		int temp=_getch();
		if (temp!=224)
		{
			return temp;
		}
		return _getch();
	}
	return -1;
}

int main()
{
	int M,N,x;
	char c;
	
	bool cek = true;
	
	while (cek)
	{
		try
		{
			cout << "Masukkan ukuran latar belakang (M, N): ";
			cin >> M >> N;
			if ((M<=0)||(N<=0))
			{
				throw "Luas latar minimal adalah 1.";
			}
			cek = false;
		}
		catch (const char *s)
		{
			cout << "Terjadi kesalahan: " << endl << s << endl;
		}
	}
	latar<char> background(M,N,(sel<char>(point(0,0),blank)));
	matrix<char> m(M,N,blank);

	cek = true;
	while (cek)
	{
		try
		{
			cout << "Masukkan kode bidang (dalam angka): ";
			cin >> x;
			if (x>(M*N))
			{
				throw "Jumlah titik batas bidang lebih banyak dari latar yang tersedia.";
			}
			cek=false;
		}
		catch (const char *s)
		{
			cout << "Terjadi kesalahan: " << endl << s << endl;
		}
	}

	bidang<char> shape(M,N,x,'*');
	
	m << background;
	m << shape;
	cout << m << endl;

	// cout << "Press any key..." << endl;
	
	
	do
	{
		int temp = getinput();
		
		// move
		if (temp==72)
		{
			shape.move(0,1);
		}
		if (temp==75)
		{
			shape.move(-1,0);
		}
		if (temp==77)
		{
			shape.move(1,0);
		}
		if (temp==80)
		{
			shape.move(0,-1);
		}
		
		// rotate
		if (temp==46)
		{
			shape.rotate(1);
		}
		if (temp==44)
		{
			shape.rotate(3);
		}
		
		if (temp!=-1)
		{
			system("cls");
			m << background;
			m << shape;
			cout << m << endl;
		}
		
		cek = ((temp==-1)||(temp==72)||(temp==75)||(temp==77)||(temp==80)||(temp==44)||(temp==46));
	} while (cek);
	
	return 0;
}