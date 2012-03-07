
#ifndef _BIDANG_
#define _BIDANG_

#include "../Sel/sel.h"
#include "../Point/point.h"
#include "../Matrix/matrix.h"
#include <vector>
#include <iostream>

using namespace std;

template <class atype>
class bidang
{
	private:
		// atribut
		int segi;
		int jumlah;
		const int M,N;
		sel<atype>* batas;
		vector< sel<atype> > isi;
		
	public:
		// 5 sekawan
		bidang ();
		bidang (int,int,int,atype);
		bidang (const bidang&);
		~bidang ();
		bidang& operator = (const bidang&);
		friend ostream& operator << (ostream& out, bidang& b)
		{
			for (int i=0;i<b.getsegi();++i)
			{
				out << b[i];
			}
			return out;
		}
		friend matrix<atype>& operator << (matrix<atype>& temp, bidang& b)
		{
			for (int i=0;i<b.getsegi();++i)
			{
				temp[b.getm()-b[i].GetY()-1][b[i].GetX()] = b[i].gett();
			}
			for (int i=0;i<b.getjumlah();++i)
			{
				temp[b.getm()-b.isi[i].GetY()-1][b.isi[i].GetX()] = b.isi[i].gett();
			}
			return temp;
		}
		
		// operator overloading []
		sel<atype>& operator [] (int i) const;
		
		// getter setter
		int getsegi ();
		void setsegi (int);
		int getjumlah ();
		int getm ();
		int getn ();
		
		// method
		void move (int,int);
		void mirror (point);
		void rotate (int);
		void fillbidang (atype);
		void resize (int);
		void addpoint (point);
		void deletepoint (point);
		
};

// 5 sekawan
template <class atype>
bidang<atype>::bidang ()
{
	segi = 0;
}

template <class atype>
bidang<atype>::bidang (int m, int n, int segibaru, atype c) : M(m), N(n)
{
	segi = segibaru;
	batas = new sel<atype> [segi];
	int MinX=N,MinY=M,MaxX=0,MaxY=0;
	for (int i=0;i<segi;++i)
	{
		int x,y;
		cout << "Masukkan koordinat dari sel: ";
		cin >> x >> y;
		x--;
		y--;
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
	
	cout << Xt << Yt << endl;
	
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
			while ((cek)&&(k<segi))
			{
				int next = (k+1)%segi;
				int temp = side(batas[k].getp(),batas[next].getp(),point(i,j));
				if (temp==0)
				{
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
				isi.push_back(sel<atype>(point(i,j),c));
			}
		}
	}
	jumlah = isi.size();
}

template <class atype>
bidang<atype>::bidang (const bidang<atype>& b) : M(b.M), N(b.N)
{
	segi = b.segi;
	jumlah = b.jumlah;
	isi = new sel<atype> [segi];
	for (int i=0;i<segi;++i)
	{
		batas[i]=b[i];
	}
	for (int i=0;i<jumlah;++i)
	{
		isi.pushback(b.isi[i]);
	}
}

template <class atype>
bidang<atype>::~bidang ()
{
	delete [] batas;
}

template <class atype>
bidang<atype>& bidang<atype>::operator = (const bidang<atype>& b)
{
	delete [] batas;
	for (int i=0;i<jumlah;++i)
	{
		isi.popback();
	}
	segi = b.segi;
	jumlah = b.jumlah;
	isi = new sel<atype> [segi];
	for (int i=0;i<segi;++i)
	{
		isi[i]=b[i];
	}
	for (int i=0;i<jumlah;++i)
	{
		isi.pushback(b.isi[i]);
	}
	return *this;
}

// template <class atype>
// ostream& operator << (ostream out, bidang<atype> &b)


// operator overloading []
template <class atype>
sel<atype>& bidang<atype>::operator [] (int i) const
{
	return batas[i];
}


// getter setter
template <class atype>
int bidang<atype>::getsegi ()
{
	return segi;
}

template <class atype>
void bidang<atype>::setsegi (int i)
{
	segi = i;
}

template <class atype>
int bidang<atype>::getjumlah ()
{
	return jumlah;
}

template <class atype>
int bidang<atype>::getm ()
{
	return M;
}

template <class atype>
int bidang<atype>::getn ()
{
	return N;
}

// method
template <class atype>
void bidang<atype>::move (int a, int b)
{
	point P[segi];
	
	try
	{
		for (int i=0;i<segi;++i)
		{
			P[i] = batas[i].getp();
			P[i].move(a,b);
			int x = P[i].GetX();
			int y = P[i].GetY();
			if ((x>=N)||(x<0)||(y>=M)||(y<0))
			{
				throw "Titik pada bidang menjadi berada di luar batas latar saat dipindahkan.";
			}
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
	catch (const char* s)
	{
		cout << "Terjadi kesalahan: " << endl << s << endl;
	}
}

template <class atype>
void bidang<atype>::mirror (point P)
{
	point Q[segi];
	try
	{
		for (int i=0;i<segi;++i)
		{
			Q[i] = batas[i].getp();
			Q[i].mirror(P);
			int x = Q[i].GetX();
			int y = Q[i].GetY();
			if ((x>=N)||(x<0)||(y>=M)||(y<0))
			{
				throw "Titik pada bidang menjadi berada di luar batas latar saat dicerminkan.";
			}
		}
		for (int i=0;i<jumlah;++i)
		{
			isi[i]=isi[i].mirror(P);
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
void bidang<atype>::rotate (int t)
{
	point Q[segi];
	try
	{
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
			if ((x>=N)||(x<0)||(y>=M)||(y<0))
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
void bidang<atype>::fillbidang (atype)
{
	
}

template <class atype>
void bidang<atype>::resize (int)
{
}

template <class atype>
void bidang<atype>::addpoint (point P)
{
	isi[segi] = P;
	segi++;
}

template <class atype>
void bidang<atype>::deletepoint (point P)
{
	int i = 0;
	bool cek = true;
	while (i<segi)
	{
		if ((cek) && (isi[i] = P))
		{
			cek =false;
		}
		if (!cek)
		{
			isi[i] = batas [i+1];
		}
		i++;
	}
	segi--;
}

#endif