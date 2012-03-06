
#ifndef _BIDANG_
#define _BIDANG_

#include "../Sel/sel.h"
#include "../Point/point.h"
#include "../Matrix/matrix.h"
#include <iostream>

using namespace std;

template <class atype>
class bidang
{
	private:
		// atribut
		int ukuran;
		const int M,N;
		sel<atype>* isi;
		
	public:
		// 5 sekawan
		bidang ();
		bidang (int,int,int,atype);
		bidang (const bidang&);
		~bidang ();
		bidang& operator = (const bidang&);
		friend ostream& operator << (ostream& out, bidang& b)
		{
			for (int i=0;i<b.getukuran();++i)
			{
				out << b[i];
			}
			return out;
		}
		friend matrix<atype>& operator << (matrix<atype>& temp, bidang& b)
		{
			for (int i=0;i<b.getukuran();++i)
			{
				temp[b.getm()-b[i].GetY()-1][b[i].GetX()] = b[i].gett();
			}
			return temp;
		}
		
		// operator overloading []
		sel<atype>& operator [] (int i) const;
		
		// getter setter
		int getukuran ();
		void setukuran (int);
		int getm ();
		int getn ();
		
		// method
		void move (int,int);
		void mirror (point);
		void rotate (point,int);
		void fillbidang (atype);
		void resize (int);
		void addpoint (point);
		void deletepoint (point);
		
};

// 5 sekawan
template <class atype>
bidang<atype>::bidang ()
{
	ukuran = 0;
}

template <class atype>
bidang<atype>::bidang (int m, int n, int segi, atype c) : M(m), N(n)
{
	ukuran = segi;
	isi = new sel<atype> [ukuran];
	for (int i=0;i<ukuran;++i)
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
			for (int j=0;j<i;++j)
			{
				if ((isi[j].GetX()==x)&&(isi[j].GetY()==y))
				{
					throw "Titik yang ingin dimasukkan sudah menjadi salah satu titik batas.";
				}
			}
			isi[i] = sel<atype>(point(x,y),c);
		}
		catch (const char* s)
		{
			cout << "Terjadi kesalahan: " << endl << s << endl;
			--i;
		}
	}
}

template <class atype>
bidang<atype>::bidang (const bidang<atype>& b) : M(b.M), N(b.N)
{
	ukuran = b.ukuran;
	isi = new sel<atype> [ukuran];
	for (int i=0;i<ukuran;++i)
	{
		isi[i]=b[i];
	}
}

template <class atype>
bidang<atype>::~bidang ()
{
	delete [] isi;
}

template <class atype>
bidang<atype>& bidang<atype>::operator = (const bidang<atype>& b)
{
	delete [] isi;
	ukuran = b.ukuran;
	isi = new sel<atype> [ukuran];
	for (int i=0;i<ukuran;++i)
	{
		isi[i]=b[i];
	}
	return *this;
}

// template <class atype>
// ostream& operator << (ostream out, bidang<atype> &b)


// operator overloading []
template <class atype>
sel<atype>& bidang<atype>::operator [] (int i) const
{
	return isi[i];
}


// getter setter
template <class atype>
int bidang<atype>::getukuran ()
{
	return ukuran;
}

template <class atype>
void bidang<atype>::setukuran (int i)
{
	ukuran = i;
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
	point P[ukuran];
	
	try
	{
		for (int i=0;i<ukuran;++i)
		{
			P[i] = isi[i].getp();
			P[i].move(a,b);
			int x = P[i].GetX();
			int y = P[i].GetY();
			if ((x>=N)||(x<0)||(y>=M)||(y<0))
			{
				throw "Titik pada bidang menjadi berada di luar batas latar saat dipindahkan.";
			}
		}
		for (int i=0;i<ukuran;++i)
		{
			isi[i].setp(P[i]);
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
	point Q[ukuran];
	try
	{
		for (int i=0;i<ukuran;++i)
		{
			Q[i] = isi[i].getp();
			Q[i].mirror(P);
			int x = Q[i].GetX();
			int y = Q[i].GetY();
			if ((x>=N)||(x<0)||(y>=M)||(y<0))
			{
				throw "Titik pada bidang menjadi berada di luar batas latar saat dicerminkan.";
			}
		}
		for (int i=0;i<ukuran;++i)
		{
			isi[i].setp(Q[i]);
		}
	}
	catch (const char* s)
	{
		cout << "Terjadi kesalahan: " << endl << s << endl;
	}
}

template <class atype>
void bidang<atype>::rotate (point P, int t)
{
	point Q[ukuran];
	try
	{
		for (int i=0;i<ukuran;++i)
		{
	
			Q[i] = isi[i].getp();
			Q[i].rotate(P,t);
			int x = Q[i].GetX();
			int y = Q[i].GetY();
			if ((x>=N)||(x<0)||(y>=M)||(y<0))
			{
				throw "Titik pada bidang menjadi berada di luar batas latar saat diputar.";
			}
		}
		for (int i=0;i<ukuran;++i)
		{
			isi[i].setp(Q[i]);
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
	isi[ukuran] = P;
	ukuran++;
}

template <class atype>
void bidang<atype>::deletepoint (point P)
{
	int i = 0;
	bool cek = true;
	while (i<ukuran)
	{
		if ((cek) && (isi[i] = P))
		{
			cek =false;
		}
		if (!cek)
		{
			isi[i] = isi [i+1];
		}
		i++;
	}
	ukuran--;
}

#endif