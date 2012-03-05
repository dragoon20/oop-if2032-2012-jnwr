
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
				temp[b[i].GetY()][b[i].GetX()] = b[i].gett();
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
		isi[i] = sel<atype>(point(x,y),c);
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


// method
template <class atype>
void bidang<atype>::move (int x, int y)
{
	for (int i=0;i<ukuran;++i)
	{
		isi[i].move(x,y);
	}
}

template <class atype>
void bidang<atype>::mirror (point P)
{
	for (int i=0;i<ukuran;++i)
	{
		isi[i].move(P);
	}
}

template <class atype>
void bidang<atype>::rotate (point P, int i)
{
	for (int i=0;i<ukuran;++i)
	{
		isi[i].rotate(P,i);
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