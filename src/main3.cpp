// File: main3.cpp

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

int getkey() // fungsi untuk mengambil input dari keyboard berupa character, jika keyboard tidak ditekan maka akan mengembalikan -1
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

void tambahstate (int *a, int *b, int *c) // menambah state pada bidang, untuk versioning bidang 
										  // sehingga dapat dikembalikan bila melakukan kesalahan
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
	int M,N,x;	// deklarasi M, N, dan x di mana M dan N nantinya akan jadi ukuran latar dan x merupakan jumlah segi bidang pertama
	int temp;	// variable sementara
	
	bool cek = true;	// variable sementara
	
	while (cek)	// looping untuk memastikan ukuran latar yang dimasukkan user benar, menggunakan exception
	{
		try
		{
			cout << "Masukkan ukuran latar belakang (M, N): ";
			cin >> M >> N;
			if ((M*N)<3)
			{
				throw "Luas latar minimal adalah 3.";
			}
			cek = false;
		}
		catch (const char *s)
		{
			cout << "Terjadi kesalahan: " << endl << s << endl;
		}
	}
	
	latar<char> background(M,N,(sel<char>(point(0,0),blank)));	// mendeklarasikan latar belakang ukuran M x N diisi dengan blank
	matrix<char> m(M,N,blank);	// membuat matrix dengan ukuran M x N diisi dengan blank

	cek = true;
	while (cek)	// looping untuk memastikan jumlah titik batas bidang tidak melebihi dari luas latar yang ada
	{
		try
		{
			cout << "Masukkan kode bidang (dalam angka): ";
			cin >> x;
			if (x<3)
			{
				throw "Jumlah titik batas tidak dapat lebih kecil dari 3.";
			}
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
	
	bidang<char>*** shape;	// inisialisasi bidang
	
	// membuat bidang menjadi berukuran 100 x 100 dan menginisialisasi M dan N pada bidang dengan constructor initialization list
	shape = new bidang<char>** [100];	
	for (int i =0;i<100;++i)
	{
		shape[i] = new bidang<char>* [100];
		for (int j=0;j<100;++j)
		{
			shape[i][j] = new bidang<char>(M,N);
		}
	}
	
	shape[0][0][0].getinput(x);	// membaca input titik batas pada bidang
	
	// menginisialisasi semua state awal, akhir maupun sekarang serta bidang yang dipilih dengan 0
	// nstate = state bidang saat ini
	// bstate = state bidang paling awal
	// lstate = state bidang paling akhir
	// semua state dibikin menjadi array dengan indeks maksimal 100 untuk menyatakan bidang yang mana yang ditunjuk
	// select = bidang yang dipilih saat ini (bidang yang dapat dikendalikan)
	int nstate[100], bstate[100], lstate[100], select;
	for (int i=0;i<100;++i)
	{
		nstate[i] = bstate[i] = lstate [i] = 0;
	}
	int jumlah = 1;	// menyatakan jumlah dari bidang yang telah diciptakan oleh user
	select = 0;	// bidang yang ditunjuk saat ini adalah bidang yang pertama kali dibuat
	
	// menampilkan bidang pertama kali dengan urutan latar dimasukkan dulu kemudian bidang pertama
	system ("clear");
	cout << "Tekan tombol 'H' pada keyboard untuk menampilkan bantuan." << endl;
	m << background;
	m << shape[select][nstate[select]][0];
	cout << m << endl;

	getkey (); // mengambil karakter asing terakhir

	do
	{
		temp = getkey(); // mengambil karakter
		
		// mengubah karakter dari lowercase menjadi uppercase jika merupakan lowercase
		if ((temp>=97)&&(temp<=122))
		{
			temp -= 32;
		} 
		
		// fillbidang yang sedang dipilih dengan blank jika ditekan tombol 'E' pada keyboard
		if (temp == 69) 
		{
			tambahstate (&nstate[select],&bstate[select],&lstate[select]);
			shape[select][nstate[select]][0] = shape[select][nstate[select]-1][0];
			shape[select][nstate[select]][0].fillbidang(' ');
		}
		
		// fillbidang yang sedang dipilih dengan '*" jika ditekan tombol 'F' pada keyboard
		// hal ini dilakukan berdasarkan klarifikasi tidak mungkin ada karakter random blank pada bidang
		// sehingga hal ini hanya dapat dilakukan setelah bidang difill dengan blank dan berarti semua isi bidang difill '*'
		if (temp == 70) 
		{
			tambahstate (&nstate[select],&bstate[select],&lstate[select]);
			shape[select][nstate[select]][0] = shape[select][nstate[select]-1][0];
			shape[select][nstate[select]][0].fillbidang('*');
		}
		
		// Menghitung kepadatan bidang jika ditekan tombol 'C' pada keyboard
		if (temp == 67) 
		{
			int luas = shape[select][nstate[select]][0].countluas();
			int hasil = (M*N) - luas;
			cout << "Kepadatan bidang = " << luas << ":" << hasil << endl;
		}
		
		// Menghitung perbandingan karakter bukan blank dengan latar jika ditekan tombol 'S' pada keyboard
		if (temp == 83) 
		{
			int luas = shape[select][nstate[select]][0].countluas() - shape[select][nstate[select]][0].countchar(' ');
			int hasil = (M*N) - luas;
			cout << "Karakter bukan blank = " << luas << ":" << hasil << endl;
		}
		
		// Menambah bidang baru dan langsung menjadi bidang yang sedang dipilih jika ditekan tombol 'A' pada keyboard
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
						if (x<3)
						{
							throw "Jumlah titik batas tidak dapat lebih kecil dari 3.";
						}
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
				if (jumlah!=100)
				{
					shape[jumlah++][0][0].getinput(x);
					select=jumlah-1;
				}
				else
				{
					cout << "Bidang tidak dapat ditambahkan lagi karena jumlahnya sudah maksimal." << endl;
					temp = -1;
				}
			}	
		}
		
		// Menghapus bidang yang paling terakhir dimasukkan jika ditekan tombol 'D' pada keyboard
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
			else
			{
				cout << "Bidang sudah tidak dapat dihapus lagi." << endl;
				temp = -1;
			}
		}
		
		// Menampilkan perintah-perintah bantuan jika ditekan tombol 'H' pada keyboard
		if (temp == 72)
		{
			cout << "+---------------------------------------------------------------------------------------------+" << endl;
			cout << "| Tombol Q : Menampilkan \"Bye...\" dan memberhentikan program                                  |" << endl;
			cout << "| Tombol E : Menghapus semua karakter dalam bidang menjadi blank                              |" << endl;
			cout << "| Tombol F : Mengubah semua titik yang kosong pada bidang menjadi karakter \"*\"                |" << endl;
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
		
		// Memilih bidang dengan memasukkan nomor urutan bidang yang ingin dipilih di mana bidang yang dipilih harus sudah dibuat
		// jika ditekan tombol 'P' pada keyboard
		if (temp == 80)
		{
			cout << "Masukkan bidang yang ingin dipilih: ";
			int temp2;
			cin >> temp2;
			if (temp2>jumlah)
			{
				cout << "Bidang yang dipilih tidak ada." << endl;
			}
			else
			{
				temp2--;
				select = temp2;
			}
		}
		
		// Mengembalikan bidang yang sedang dipilih ke state sebelumnya(undo) jika ditekan tombol 'U' pada keyboard
		// Jika state yang saat ini adalah state yang paling awal maka tidak akan ada perubahan
		if (temp == 85)
		{
			if (nstate[select]!=bstate[select])
			{
				nstate[select] = ((nstate[select]+100)-1)%100;
			}
		}
		
		// Mengembalikan bidang yang sedang dipilih ke state selanjutnya(redo) jika ditekan tombol 'R' pada keyboard
		// Jika state yang saat ini adalah state yang paling akhir maka tidak akan ada perubahan
		if (temp == 82)
		{
			if (nstate[select]!=lstate[select])
			{
				nstate[select] = (nstate[select]+1)%100;
			}
		}

		// Menggerakkan bidang jika ditekan tombol direction pada keyboard
		if (temp == 27)
		{
			temp = getkey();
			if (temp==91)
			{	
				int i=0;
				int buff = shape[select][nstate[select]][0].getsegi();
				cek = true;
				
				temp = getkey();
				tambahstate (&nstate[select],&bstate[select],&lstate[select]); 	
				shape[select][nstate[select]][0] = shape[select][nstate[select]-1][0];
				
				// Bidang digerakkan ke atas
				if (temp==65)
				{
					while ((cek)&&(i<buff))
					{
						if (shape[select][nstate[select]][0].getbatas(i).GetY()==M-1)
						{
							cek=false;
						}
						++i;
					}
					if (cek)
					{
						shape[select][nstate[select]][0].move(0,1);
					}
				}
				
				// Bidang digerakkan ke kiri
				if (temp==68)
				{
					while ((cek)&&(i<buff))
					{
						if (shape[select][nstate[select]][0].getbatas(i).GetX()==0)
						{
							cek=false;
						}
						++i;
					}
					if (cek)
					{
						shape[select][nstate[select]][0].move(-1,0);
					}
				}
				
				// Bidang digerakkan ke kanan
				if (temp==67)
				{
					while ((cek)&&(i<buff))
					{
						if (shape[select][nstate[select]][0].getbatas(i).GetX()==N-1)
						{
							cek=false;
						}
						++i;
					}
					if (cek)
					{
						shape[select][nstate[select]][0].move(1,0);
					}
				}
				
				// Bidang digerakkan ke bawah
				if (temp==66)
				{
					while ((cek)&&(i<buff))
					{
						if (shape[select][nstate[select]][0].getbatas(i).GetY()==0)
						{
							cek=false;
						}
						++i;
					}
					if (cek)
					{
						shape[select][nstate[select]][0].move(0,-1);
					}
				}
				temp = 80; // memastikan temp tidak menyebabkan bidang dan latar tetap ditampilkan ulang
			}
		}
		
		// Memutar bidang sejauh 90 derajat berlawanan arah jarum jam terhadap pusat bidang jika ditekan tombol '.' pada keyboard
		if (temp==46)
		{
			tambahstate (&nstate[select],&bstate[select],&lstate[select]);
			shape[select][nstate[select]][0] = shape[select][nstate[select]-1][0];
			shape[select][nstate[select]][0].rotate(1);
		}
		
		// Memutar bidang sejauh 90 derajat searah jarum jam terhadap pusat bidang jika ditekan tombol ',' pada keyboard
		if (temp==44)
		{
			tambahstate (&nstate[select],&bstate[select],&lstate[select]);
			shape[select][nstate[select]][0] = shape[select][nstate[select]-1][0];
			shape[select][nstate[select]][0].rotate(3);
		}
	
		// menampilkan ulang bidang jika ditekan tombol sesuai fungsi2 sebelumnya
		// yang tidak menampilkan kata-kata bantuan dan atau menghitung perbandingan
		if ((temp!=-1)&&(temp!=67)&&(temp!=83)&&(temp!=72))
		{
			system("clear"); // mengosongkan layar
			
			cout << "Tekan tombol 'H' pada keyboard untuk menampilkan bantuan." << endl;
			m << background; // menampilkan latar ke matriks
			for (int i=0;i<jumlah;++i)	// menampilkan bidang ke matriks sesuai urutan pembuatan
			{
				m << shape[i][nstate[i]][0];
			}
			cout << m << endl; // menampilkan matriks ke layar
		}
		
	} while (temp!=81); // menghentikan program jika ditekan tombol 'Q' pada keyboard
	
	cout << "Bye..." << endl;
	
	return 0;
}
