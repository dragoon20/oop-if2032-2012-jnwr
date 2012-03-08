// File: bidang.h

#ifndef _BIDANG_
#define _BIDANG_

#include "../Sel/sel.h"
#include "../Point/point.h"
#include "../Matrix/matrix.h"
#include <iostream>
#include <cstdlib>
#include <assert.h>

using namespace std;

template <class atype>
class bidang
{
	private:
		// atribut
		int segi;			// menyatakan jumlah titik sudut yang ada
		int jumlah;			// menyatakan jumlah titik selain titik sudut pada bidang
		const int M,N;		// menyatakan batas ukuran latar M*N
		sel<atype>* batas;	// menyatakan titik-titik sudut
		sel<atype>* isi;	// menyatakan titik-titik selain titik-titik sudut
		
	public:
		// 5 sekawan
		bidang ();
		bidang (int,int);
		bidang (const bidang&);
		~bidang ();
		bidang& operator = (const bidang&);
		friend ostream& operator << (ostream& out, bidang& b)
		{
			for (int i=0;i<b.getsegi();++i)
			{
				out << b.batas[i];
			}
			for (int i=0;i<b.getjumlah();++i)
			{
				out << b.isi[i];
			}
			return out;
		}
		
		// menyimpan hasil tampilan sementara dari bidang dalam matrix
		friend matrix<atype>& operator << (matrix<atype>& temp, bidang& b)
		{
			for (int i=0;i<b.getsegi();++i)
			{
				temp[b.getm()-b.batas[i].GetY()-1][b.batas[i].GetX()] = b.batas[i].gett();
			}
			for (int i=0;i<b.getjumlah();++i)
			{
				temp[b.getm()-b.isi[i].GetY()-1][b.isi[i].GetX()] = b.isi[i].gett();
			}
			return temp;
		}
				
		// getter setter
		int getsegi ();
		void setsegi (int);
		int getjumlah ();
		int getm ();
		int getn ();
		sel<atype> getisi (int);
		sel<atype> getbatas (int);
		
		// method
		void move (int,int);
		void rotate (int);
		void fillbidang (atype);
		void getinput (int);
		int countluas();
		int countchar(atype);
};


// 5 sekawan
template <class atype>
bidang<atype>::bidang (): M(20), N(40) 	// ctor
{
	segi = 0;
}

template <class atype>
bidang<atype>::bidang (int m, int n) : M(m), N(n)	// ctor dengar parameter
{
	segi = 0;
	jumlah = 0;
}

template <class atype>
bidang<atype>::bidang (const bidang<atype>& b) : M(b.M), N(b.N)	// cctor
{
	segi = b.segi;
	jumlah = b.jumlah;
	batas = new sel<atype> [segi];
	isi = new sel<atype> [jumlah];
	for (int i=0;i<segi;++i)
	{
		batas[i]=b[i];
	}
	for (int i=0;i<jumlah;++i)
	{
		isi[i] = b.isi[i];
	}
}
template <class atype>
bidang<atype>::~bidang ()	// dtor
{
	delete [] batas;
}

template <class atype>
bidang<atype>& bidang<atype>::operator = (const bidang<atype>& b)	// operator =
{
	if (segi > 0)
	{
		delete [] batas;
	}
	if (jumlah >0)
	{
		delete [] isi;
	}
	segi = b.segi;
	jumlah = b.jumlah;
	batas = new sel<atype> [segi];
	isi = new sel<atype> [jumlah];
	for (int i=0;i<segi;++i)
	{
		batas[i]= b.batas[i];
	}
	for (int i=0;i<jumlah;++i)
	{
		isi[i] = b.isi[i];
	}
	return *this;
}

// getter setter
template <class atype>
int bidang<atype>::getsegi ()	// mengembalikan jumlah titik sudut
{
	return segi;
}

template <class atype>
void bidang<atype>::setsegi (int i)	// mengeset jumlah titik sudut
{
	segi = i;
}

template <class atype>
int bidang<atype>::getjumlah ()	// mengembalikan jumlah titik selain titik-titik sudut
{
	return jumlah;
}

template <class atype>
int bidang<atype>::getm ()	// mengembalikan baris maksimal dari latar
{
	return M;
}

template <class atype>
int bidang<atype>::getn ()	// mengembalikan kolom maksimal dari latar
{
	return N;
}

template <class atype>
sel<atype> bidang<atype>::getisi (int i)	// mengembalikan sel pada isi bidang
{
	return isi[i];
}

template <class atype>
sel<atype> bidang<atype>::getbatas (int i)	// mengembalikan sel pada batas bidang
{
	return batas[i];
}


// method
template <class atype>
void bidang<atype>::move (int a, int b)	// menggerakan bidang searah sumbu x sejauh a dan searah sumbu y sejauh b
{
	point P[segi];
	
	for (int i=0;i<segi;++i)
	{
		if (a==-1)
		{
			assert(batas[i].getp().GetX()!=0);
		}
		if (b==-1)
		{
			assert(batas[i].getp().GetY()!=0);
		}
		if (a==1)
		{
			assert(batas[i].getp().GetX()!=N-1);
		}
		if (b==1)
		{
			assert(batas[i].getp().GetY()!=M-1);
		}
	}
	for (int i=0;i<segi;++i)
	{
		P[i] = batas[i].getp();
		P[i].move(a,b);
		int x = P[i].GetX();
		int y = P[i].GetY();
	}
	for (int i=0;i<jumlah;++i)
	{
		isi[i].move(a,b);
	}
	for (int i=0;i<segi;++i)
	{
		batas[i].setp(P[i]);
	}
}

template <class atype>
void bidang<atype>::rotate (int t)	// memutar bidang terhadap titik pusat bidang di mana untuk t = 1 berputar 90 derajat berlawanan jarum jam
									// dan untuk t = 2 berputar 90 derajat searah jarum jam
{
	try
	{
		point Q[segi];
		point P;
		int Xt = 0;
		int Yt = 0;
		
		for (int k=0;k<segi;++k)
		{
			Xt += batas[k].getp().GetX();
			Yt += batas[k].getp().GetY();
		}
		
		Xt /= segi;
		Yt /= segi;
		
		P.SetX(Xt);
		P.SetY(Yt);
		
		for (int i=0;i<segi;++i)
		{
	
			Q[i] = batas[i].getp();
			Q[i].rotate(P,t);
			int x = Q[i].GetX();
			int y = Q[i].GetY();
			if ((x>=N-1)||(x<0)||(y>=M-1)||(y<0))
			{
				throw "Titik pada bidang menjadi berada di luar batas latar saat diputar.";
			}
		}
		for (int i=0;i<jumlah;++i)
		{
			isi[i].rotate(P,t);
		}
		for (int i=0;i<segi;++i)
		{
			batas[i].setp(Q[i]);
		}
	}	
	catch (const char* s)
	{
		cout << "Terjadi kesalahan: " << endl << s << endl;
	}
}

template <class atype>
void bidang<atype>::fillbidang (atype c)	// mengisi semua titik pada bidang dengan c
{
	for (int i=0;i<segi;++i)
	{
		batas[i].sett(c);
	}
	for (int i=0;i<jumlah;++i)
	{
		isi[i].sett(c);
	}
}

template <class atype>
void bidang<atype>::getinput (int segibaru)	// meminta input dari user akan titik-titik batas dan menentukan semua titik yang ada dalam bidang
											// serta mengisi semua titik pada bidang dengan character random
{
	atype c;

	segi = segibaru;
	jumlah = 0;
	batas = new sel<atype> [segi];
	isi = new sel<atype> [M*N];
	
	int MinX=N,MinY=M,MaxX=0,MaxY=0;
	for (int i=0;i<segi;++i)
	{
		int x,y;
		cout << "Masukkan koordinat dari sel: ";
		cin >> x >> y;
		try
		{
			if ((x>=N)||(x<0)||(y>=M)||(y<0))
			{
				throw "Titik pada bidang berada di luar batas latar.";
			}
			
			if (x < MinX)
			{
				MinX = x;
			}
			if (x > MaxX)
			{
				MaxX = x;
			}
			if (y < MinY)
			{
				MinY = y;
			}
			if (y > MaxY)
			{
				MaxY = y;
			}
			
			for (int j=0;j<i;++j)
			{
				if ((batas[j].GetX()==x)&&(batas[j].GetY()==y))
				{
					throw "Titik yang ingin dimasukkan sudah menjadi salah satu titik batas.";
				}
			}
			
			c = (rand() % 93) + '!';

			
			batas[i] = sel<atype>(point(x,y),c);
		}
		catch (const char* s)
		{
			cout << "Terjadi kesalahan: " << endl << s << endl;
			--i;
		}
	}
	
	point P;
	int Xt = 0;
	int Yt = 0;
	
	for (int k=0;k<segi;++k)
	{
		Xt += batas[k].getp().GetX();
		Yt += batas[k].getp().GetY();
	}
	Xt /= segi;
	Yt /= segi;
	
	// cout << Xt << Yt << endl;
	
	P.SetX(Xt);
	P.SetY(Yt);
	
	int hasil[5];
	for (int k=0;k<segi;++k)
	{
		int next = (k+1)%segi;
		hasil[k] = side(batas[k].getp(),batas[next].getp(),P);
	}
	
	for (int j=MinY;j<=MaxY;++j)
	{
		for (int i=MinX;i<=MaxX;++i)
		{
			int k=0;
			bool cek=true;
			while (k<segi)
			{
				int next = (k+1)%segi;
				int temp = side(batas[k].getp(),batas[next].getp(),point(i,j));
				if (temp==0)
				{
					cek = true;
					int x1 = batas[k].getp().GetX();
					int x2 = batas[next].getp().GetX();
					int y1 = batas[k].getp().GetY();
					int y2 = batas[next].getp().GetY();
					
					int lo_x = (x1 < x2) ? x1: x2;
					int hi_x = (x1 > x2) ? x1: x2;
					int lo_y = (y1 < y2) ? y1: y2;
					int hi_y = (y1 > y2) ? y1: y2;
					
					if ((i<lo_x)||(i>hi_x)||(j<lo_y)||(j>hi_y))
					{
						cek = false;
					}
					
					k = segi;
				}
				else if ((temp!=hasil[k]))
				{
					cek=false;
				}
				++k;
			}		
			if (cek)
			{
				c = (rand() % 93) + '!';
				
				isi[jumlah] = sel<atype>(point(i,j),c);
				jumlah++;
			}
		}
	}
}

template <class atype>
int bidang<atype>::countluas()	// mengembalikan luas yang merupakan jumlah semua titik pada bidang
{
	return (getsegi() + getjumlah()) ;
}

template <class atype>
int bidang<atype>::countchar(atype ch)	// mengembalikan jumlah isi sel yang sama dengan ch pada bidang
{	
	int count = 0 ;
	for (int i = 0; i <= segi-1 ; i++)
	{
		if (ch == batas[i].gett())
			count++ ;
	}
	for (int i = 0; i <= jumlah-1 ; i++)
	{
		if (ch == isi[i].gett())
			count++ ;
	}
	return count;
}

#endif
