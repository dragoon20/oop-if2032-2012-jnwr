
#ifndef _LATAR_
#define _LATAR_

#include "../Sel/sel.h"
#include "../Matrix/matrix.h"
#include <iostream>

using namespace std;

// template <class atype>
// extern const atype blank;

template <class atype>
class latar
{
	private:
		// atribut
		int M;
		int N;
		sel<atype>** isi;
	
	public:
		// 5 sekawan
		latar ();
		latar (int,int,sel<atype>);
		latar (const latar&);
		~latar ();
		latar<atype>& operator = (const latar&);
		friend ostream& operator << (ostream& out, latar& l)
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
		void filllatar (atype);
		
};

// 5 sekawan
template <class atype>
latar<atype>::latar ()
{
	M = 20;
	N = 40;
	isi = new sel<atype> *[M];
	for (int i=0;i<M;++i)
	{
		isi[i] = new sel<atype> [N];
		for (int j=0;j<N;++i)
		{
		
		}
	}
}

template <class atype>
latar<atype>::latar (int m, int n, sel<atype> c)
{
	M = m;
	N = n;
	isi = new sel<atype> *[M];
	for (int i=0;i<M;++i)
	{
		isi[i] = new sel<atype> [N];
		for (int j=0;j<N;++j)
		{
			isi[i][j]=c;			
		}
	}
}

template <class atype>
latar<atype>::latar (const latar& l)
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
{
	delete [] isi;
}

template <class atype>
latar<atype>& latar<atype>::operator = (const latar& l)
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
{
	return M;
}

template <class atype>
int latar<atype>::getn ()
{
	return N;
}

template <class atype>
void latar<atype>::setm (int m)
{
	M = m;
}

template <class atype>
void latar<atype>::setn (int n)
{
	N = n;
}

//method
template <class atype>
void latar<atype>::filllatar (atype)
{
}

#endif