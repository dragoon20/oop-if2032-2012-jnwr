// File : latar.h

#ifndef _LATAR_
#define _LATAR_

#include "../Sel/sel.h"
#include "../Matrix/matrix.h"
#include <iostream>
#include <assert.h>

using namespace std;

// template <class atype>
// extern const atype blank;

template <class atype>
class latar
{
	private:
		// atribut
		int M;		// lebar dari latar
		int N;		// panjang dari latar
		sel<atype>** isi;	// isi sel dari latar
	
	public:
		// 5 sekawan
		latar ();
		latar (int,int,sel<atype>);
		latar (const latar&);
		~latar ();
		latar<atype>& operator = (const latar&);
		friend ostream& operator << (ostream& out, latar& l)
		// operator ostream
		{
			for (int i=0;i<l.getm();++i)
			{
				for (int j=0;j<l.getn();++j)
				{
					out << l[i][j];			
				}
				out << endl;
			}
			return out;
		}
		friend matrix<atype>& operator << (matrix<atype>& temp, latar& l)
		{
		// operator ostream untuk matrix
			for (int i=0;i<l.getm();++i)
			{
				for (int j=0;j<l.getn();++j)
				{
					temp[i][j] = l[i][j].gett();			
				}
			}
			return temp;
		}
		// operator overloading []
		sel<atype>* operator [] (int) const;
		
		// getter setter
		int getm ();
		int getn ();
		void setm (int);
		void setn (int);
		
		//method
		
};

// 5 sekawan
template <class atype>
latar<atype>::latar ()
// ctor
{
	M = 20;
	N = 40;
	isi = new sel<atype> *[M];
	for (int i=0;i<M;++i)
	{
		isi[i] = new sel<atype> [N];
		for (int j=0;j<N;++i)
		{
			isi[i][j].SetX(j);
			isi[i][j].SetY(M-i-1);
		}
	}
}

template <class atype>
latar<atype>::latar (int m, int n, sel<atype> c)
// ctor dengan parameter
{
	assert (m > 0);
	assert (n > 0);
	M = m;
	N = n;
	isi = new sel<atype> *[M];
	for (int i=0;i<M;++i)
	{
		isi[i] = new sel<atype> [N];
		for (int j=0;j<N;++j)
		{
			isi[i][j]=c;			
			isi[i][j].SetX(j);
			isi[i][j].SetY(M-i-1);
		}
	}
}

template <class atype>
latar<atype>::latar (const latar& l)
// cctor
{
	M = l.M;
	N = l.N;
	isi = new sel<atype> *[M];
	for (int i=0;i<M;++i)
	{
		isi[i] = new sel<atype> [N];
		for (int j=0;j<N;++i)
		{
			isi[i][j] = l[i][j];
		}
	}
}

template <class atype>
latar<atype>::~latar ()
// dtor
{
	delete [] isi;
}

template <class atype>
latar<atype>& latar<atype>::operator = (const latar& l)
// operator assignment
{
	delete [] isi;
	M = l.M;
	N = l.N;
	isi = new sel<atype> *[M];
	for (int i=0;i<M;++i)
	{
		isi[i] = new sel<atype> [N];
		for (int j=0;j<N;++i)
		{
			isi[i][j] = l[i][j];
		}
	}
	return *this;
}

//template <class atype>
//ostream& operator << (ostream& out, latar<atype>& l)

// operator overloading []
template <class atype>
sel<atype>* latar<atype>::operator [] (int i) const
{
	return isi[i];
}

// getter setter
template <class atype>
int latar<atype>::getm ()
// mengembalikan lebar dari latar
{
	return M;
}

template <class atype>
int latar<atype>::getn ()
// mengembalikan panjang dari latar
{
	return N;
}

template <class atype>
void latar<atype>::setm (int m)
// menge-set nilai lebar dari latar
{
	M = m;
}

template <class atype>
void latar<atype>::setn (int n)
// menge-set nilai panjang dari latar
{
	N = n;
}

//method

#endif
