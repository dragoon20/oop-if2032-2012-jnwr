
#include "Latar/latar.h"
#include "Bidang/bidang.h"
#include "Matrix/matrix.h"
#include <iostream>
#include <termios.h>
#include <cstdio>
#include <cstring>
// #include <conio.h>
#include <cstdlib>

using namespace std;

const char blank = ' ';

int getkey() 
{
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

/*int getinput()
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
}*/

int main()
{
	int M,N,x;
	int temp;
	
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

	bidang<char> shape(M,N,x)[100][100];
	int nstate, bstate, lstate, select;
	nstate = bstate = lstate = select = 0;
	
	m << background;
	m << shape;
	cout << m << endl;

	getkey ();

	do
	{
		temp = getkey();
		
		if ((temp>=97)&&(temp<=122))
		{
			temp -= 32;
		} 
		
		// E
		if (temp == 69) 
		{
			shape.fillbidang(' ');
		}
		// F
		if (temp == 70) 
		{
			shape.fillbidang('*');
		}
		// C
		if (temp == 67) 
		{
		}
		// S
		if (temp == 83) 
		{
		}

		// move
		if (temp == 27)
		{
			temp = getkey();
			if (temp==91)
			{	
				temp = getkey();
				if (temp==65)
				{
					shape.move(0,1);
				}
				if (temp==68)
				{
					shape.move(-1,0);
				}
				if (temp==67)
				{
					shape.move(1,0);
				}
				if (temp==66)
				{
					shape.move(0,-1);
				}
			}
		}
		/*if (temp==72)
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
		}*/
	
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
			system("clear");
			m << background;
			m << shape;
			cout << m << endl;
		}
		
	} while (temp!=81);
	
	cout << "Bye..." << endl;
	
	return 0;
}
