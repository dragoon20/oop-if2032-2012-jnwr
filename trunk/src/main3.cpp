
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

void tambahstate (int *a, int *b, int *c)
{
	*a = (*a+1) % 100;
	if (*a == *b)
	{
		*b += 1;
	}
	*c = *a;
}

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
	
	bidang<char>*** shape;
	shape = new bidang<char>** [100];	
	
	for (int i =0;i<100;++i)
	{
		shape[i] = new bidang<char>* [100];
		for (int j=0;j<100;++j)
		{
			shape[i][j] = new bidang<char>(M,N);
		}
	}
	

	shape[0][0][0].getinput(x);
	
	int nstate[100], bstate[100], lstate[100], select;
	int jumlah = 1;
	select = 0;
	for (int i=0;i<100;++i)
	{
		nstate[i] = bstate[i] = lstate [i] = 0;
	}
	
	m << background;
	m << shape[select][nstate[select]][0];
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
			tambahstate (&nstate[select],&bstate[select],&lstate[select]);
			shape[select][nstate[select]][0] = shape[select][nstate[select]-1][0];
			shape[select][nstate[select]][0].fillbidang(' ');
		}
		// F
		if (temp == 70) 
		{
			tambahstate (&nstate[select],&bstate[select],&lstate[select]);
			shape[select][nstate[select]][0] = shape[select][nstate[select]-1][0];
			shape[select][nstate[select]][0].fillbidang('*');
		}
		// C
		if (temp == 67) 
		{
			int luas = shape[select][nstate[select][0].countluas();
			int hasil = (M*N) - luas;
			cout << "Kepadatan bidang = " << luas << ":" << hasil << endl;
		}
		
		// S
		if (temp == 83) 
		{
			int luas = shape[select][nstate[select][0].countluas() - shape[select][nstate[select][0].countchar(' ');
			int hasil = (M*N) - luas;
			cout << "Karakter bukan blank = " << luas << ":" << hasil << endl;
		}
		
		// A
		if (temp == 65)
		{
			if (jumlah!=99)
			{
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
				shape[jumlah++][0][0].getinput(x);
				select=jumlah-1;
			}	
		}
		
		// D
		if (temp == 68)
		{
			if (jumlah>0)
			{
				jumlah--;
				if (select == jumlah)
				{
					select--;
				}
			}
		}
		
		// H
		if (temp == 72)
		{
			cout << "+---------------------------------------------------------------------------------------------+" << endl;
			cout << "| Tombol Q : Menampilkan “Bye...” dan memberhentikan program                                  |" << endl;
			cout << "| Tombol E : Menghapus semua karakter dalam bidang menjadi blank                              |" << endl;
			cout << "| Tombol F : Mengubah semua titik yang kosong pada bidang menjadi karakter ‘*’                |" << endl;
			cout << "| Tombol C : Menghitung kepadatan bidang dan menampilkannya                                   |" << endl;
			cout << "| Tombol S : Menghitung perbandingan karakter bidang yang tidak kosong dengan karakter kosong |" << endl;
			cout << "| Tombol direction : Untuk menggerakkan bidang sesuai arah                                    |" << endl;
			cout << "| Tombol A : Menambah bidang baru (bidang baru akan menimpa di atas bidang yang lama)         |" << endl;
			cout << "| Tombol P : Memilih bidang yang akan dipakai di antara 2 bidang atau lebih                   |" << endl;
			cout << "| Tombol U : Meng-undo aksi yang dilakukan sebelumnya                                         |" << endl;
			cout << "| Tombol R : Me-redo aksi yang sudah pernah dilakukan sebelumnya                              |" << endl;
			cout << "| Tombol , : Me-rotate bidang 90 derajat berlawanan arah jarum jam                            |" << endl;
			cout << "| Tombol . : Me-rotate bidang 90 derajat searah jarum jam                                     |" << endl;
			cout << "| Tombol D : Menghapus bidang terakhir yang sudah dibentuk                                    |" << endl;
			cout << "| Tombol H : Memunculkan perintah bantuan                                                     |" << endl;
			cout << "+---------------------------------------------------------------------------------------------+" << endl;
		}
		
		// P
		if (temp == 80)
		{
			cout << "Masukkan bidang yang ingin dipilih: ";
			int temp2;
			cin >> temp2;
			temp2--;
			select = temp2;
		}
		
		// U
		if (temp == 85)
		{
			if (nstate[select]!=bstate[select])
			{
				nstate[select] = ((nstate[select]+100)-1)%100;
			}
		}
		
		// R
		if (temp == 82)
		{
			if (nstate[select]!=lstate[select])
			{
				nstate[select] = (nstate[select]+1)%100;
			}
		}

		// move
		if (temp == 27)
		{
			temp = getkey();
			if (temp==91)
			{	
				temp = getkey();
				tambahstate (&nstate[select],&bstate[select],&lstate[select]); 	
				shape[select][nstate[select]][0] = shape[select][nstate[select]-1][0];
				if (temp==65)
				{
					shape[select][nstate[select]][0].move(0,1);
				}
				if (temp==68)
				{
					shape[select][nstate[select]][0].move(-1,0);
				}
				if (temp==67)
				{
					shape[select][nstate[select]][0].move(1,0);
				}
				if (temp==66)
				{
					shape[select][nstate[select]][0].move(0,-1);
				}
			}
		}
		
		// .
		if (temp==46)
		{
			tambahstate (&nstate[select],&bstate[select],&lstate[select]);
			shape[select][nstate[select]][0] = shape[select][nstate[select]-1][0];
			shape[select][nstate[select]][0].rotate(1);
		}
		
		// ,
		if (temp==44)
		{
			tambahstate (&nstate[select],&bstate[select],&lstate[select]);
			shape[select][nstate[select]][0] = shape[select][nstate[select]-1][0];
			shape[select][nstate[select]][0].rotate(3);
		}
	
		if (temp!=-1)
		{
			system("clear");
			m << background;
			for (int i=0;i<jumlah;++i)
			{
				m << shape[i][nstate[i]][0];
			}
			cout << m << endl;
		}
		
	} while (temp!=81);
	
	cout << "Bye..." << endl;
	
	return 0;
}
