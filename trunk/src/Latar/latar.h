
#IFNDEF _LATAR_
#DEFINE _LATAR_

#include <../Sel/sel.h>
#include <iostream>

using namespace std;

template <class atype>
extern const <atype> blank;

template <class atype>
class latar<atype>
{
	private:
		// atribut
		int M;
		int N;
		<atype>* isi;
	
	public:
		// 5 sekawan
		latar ();
		latar (int,int,<atype>);
		latar (const latar&);
		~latar ();
		latar& operator = (const latar&);
		friend ostream& operator << (ostream, latar);
		
		// operator overloading []
		sel& operator [] (int,int);
		
		// getter setter
		int getm ();
		int getn ();
		void setm (int);
		void setn (int);
		
		//method
		void filllatar (<atype>);
		
}

// 5 sekawan
template <class atype>
latar<atype>::latar ()
{
	M = 20;
	N = 40;
	isi = new sel [M][N];
	for (int i=0;i<M;++i)
	{
		for (int j=0;j<N;++i)
		{
			isi[i][j]=blank;			
		}
	}
}

template <class atype>
latar<atype>::latar (int m, int n, <atype> c)
{
	M = m;
	N = n;
	isi = new sel [M][N];
	for (int i=0;i<M;++i)
	{
		for (int j=0;j<N;++i)
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
	isi = new sel [M][N];
	for (int i=0;i<M;++i)
	{
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
latar<atype>::latar& operator = (const latar& l)
{
	delete [] isi;
	M = l.M;
	N = l.N;
	isi = new sel [M][N];
	for (int i=0;i<M;++i)
	{
		for (int j=0;j<N;++i)
		{
			isi[i][j] = l[i][j];			
		}
	}
	return *this;
}

friend ostream& operator << (ostream out, latar l)
{
	for (int i=0;i<M;++i)
	{
		for (int j=0;j<N;++i)
		{
			out << l[i][j];			
		}
		out << endl;
	}
	return *out;
}

// operator overloading []
template <class atype>
latar<atype>::sel& operator [] (int i, int j)
{
	return isi[i][j];
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
void latar<atype>::filllatar (<atype>)
{
}

#ENDIF