// File: main2.cpp

#include "Latar/latar.h"
#include "Bidang/bidang.h"
#include "Matrix/matrix.h"
#include <iostream>
#include <termios.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

const char blank = ' ';

int getkey() {
    int character;
    struct termios orig_term_attr;
    struct termios new_term_attr;

    /* set the terminal to raw mode */
    tcgetattr(fileno(stdin), &orig_term_attr);
    memcpy(&new_term_attr, &orig_term_attr, sizeof(struct termios));
    new_term_attr.c_lflag &= ~(ECHO|ICANON);
    new_term_attr.c_cc[VTIME] = 0;
    new_term_attr.c_cc[VMIN] = 0;
    tcsetattr(fileno(stdin), TCSANOW, &new_term_attr);

    /* read a character from the stdin stream without blocking */
    /*   returns EOF (-1) if no character is available */
    character = fgetc(stdin);

    /* restore the original terminal attributes */
    tcsetattr(fileno(stdin), TCSANOW, &orig_term_attr);

    return character;
}


int main()
{
	int M,N,x;		// M adalah lebar dari latar, N adalah panjang dari latar, x adalah jumlah segi bidang yang dibentuk
	int temp;		// masukan key dari user
	
	bool cek = true;	// boolean untuk mengecek pengulangan try dan catch
	
	while (cek)		// exception untuk mengecek apakah panjang dan lebar masukan user sudah benar
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
	while (cek)	// exception untuk mengecek apakah masukan titik sudut bidang sudah benar
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

	bidang<char> shape(M,N);	// membentuk bidang dengan ukuran M x N
	shape.getinput(x);			// mengisi jumlah titik sudut
	
	m << background;			
	m << shape;
	cout << m << endl;

	getkey ();							// meminta masukan any key dari user
	cout << "Press any key..." << endl;
	
	do	// loop untuk meminta masukan key dari user
	{
		temp = getkey();	
	} while (temp == -1);
	
	return 0;
}
