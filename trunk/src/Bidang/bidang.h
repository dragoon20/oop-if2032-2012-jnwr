
#IFNDEF _BIDANG_
#DEFINE _BIDANG_

#include <../Sel/sel.h>
#include <iostream>

using namespace std;

template <class atype>
class bidang<atype>
{
	private:
		// atribut
		int ukuran;
		const int M,N;
		sel* isi<atype>;
		
	public:
		// 5 sekawan
		bidang ();
		bidang (int,int,int,<atype>);
		bidang (const bidang&);
		~bidang ();
		bidang& operator = (const bidang&);
		friend ostream& operator << (ostream, bidang);
		
		// operator overloading []
		sel& operator [] (int i);
		
		// getter setter
		int getukuran ();
		void setukuran (int);
		
		// method
		void move (int,int);
		void mirror (Point);
		void rotate (Point,int);
		void fillbidang (<atype>);
		void resize (int);
		void addpoint (Point);
		void deletepoint (Point);
		
}

// 5 sekawan
template <class atype>
bidang<atype>::bidang ()
{
	ukuran = 0;
}

template <class atype>
bidang<atype>::bidang (int m, int n, int segi, <atype> c) : M(m), N(n)
{
	ukuran = segi;
	isi = new sel [ukuran];
	for (int i=0;i<ukuran;++i)
	{
		int x,y;
		cout >> "Masukkan koordinat dari sel: "
		cin << x << y;
		isi[i] = sel(point(x,y),c);
	}
}

template <class atype>
bidang<atype>::bidang (const bidang& b)
{
	ukuran = b.ukuran;
	isi = new sel [ukuran]
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
bidang<atype>::bidang& operator = (const bidang&)
{
	delete [] isi;
	ukuran = b.ukuran;
	isi = new sel [ukuran]
	for (int i=0;i<ukuran;++i)
	{
		isi[i]=b[i];
	}
	return *this;
}

ostream& operator << (ostream out, bidang b)
{
	for (int i=0;i<ukuran;++i)
	{
		out << b[i];
	}
	return *out;
}


// operator overloading []
template <class atype>
bidang<atype>::sel& operator [] (int i)
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
void bidang<atype>::mirror (Point P)
{
	for (int i=0;i<ukuran;++i)
	{
		isi[i].move(P);
	}
}

template <class atype>
void bidang<atype>::rotate (Point P, int i)
{
	for (int i=0;i<ukuran;++i)
	{
		isi[i].rotate(P,i);
	}
}

template <class atype>
void bidang<atype>::fillbidang (<atype>)
{
	
}

template <class atype>
void bidang<atype>::resize (int)
{
}

template <class atype>
void bidang<atype>::addpoint (Point P)
{
	isi[ukuran] = P;
	ukuran++;
}

template <class atype>
void bidang<atype>::deletepoint (Point P)
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

#ENDIF