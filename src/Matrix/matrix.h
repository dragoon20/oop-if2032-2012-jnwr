
#ifndef _MATRIX_
#define _MATRIX_

template <class atype>
class matrix
{
	private:
		// atribut
		atype** isi;
		const int M,N;
	
	public:
		// 5 sekawan
		matrix ();
		matrix (int,int,atype);
		matrix (const matrix&);
		~matrix ();
		matrix& operator = (const matrix&);
		friend ostream& operator << (ostream& out, matrix& m)
		{
			for (int i=0;i<m.getm();++i)
			{
				for (int j=0;j<m.getn();++j)
				{
					out << m[i][j];			
				}
				out << endl;
			}
			return out;
		}
		
		// operator overloading []
		atype* operator [] (int) const;
		
		// getter dan setter
		int getm ();
		int getn ();
		
};

// 5 sekawan
template <class atype>
matrix<atype>::matrix ()
{
	M = 20;
	N = 40;
	isi = new atype *[M];
	for (int i=0;i<M;++i)
	{
		isi[i] = new atype [N];
		for (int j=0;j<N;++i)
		{
		
		}
	}
}

template <class atype>
matrix<atype>::matrix (int m,int n, atype c) : M(m), N(n)
{
	isi = new atype *[M];
	for (int i=0;i<M;++i)
	{
		isi[i] = new atype [N];
		for (int j=0;j<N;++j)
		{
			isi[i][j]=c;		
		}
	}
}

template <class atype>
matrix<atype>::matrix (const matrix& m) : M(m.M), N(m.N)
{
	isi = new atype *[M];
	for (int i=0;i<M;++i)
	{
		isi[i] = new atype [N];
		for (int j=0;j<N;++j)
		{
			isi[i][j]=m[i][j];		
		}
	}
}

template <class atype>
matrix<atype>::~matrix ()
{
}

template <class atype>
matrix<atype>& matrix<atype>::operator = (const matrix& m)
{
	delete [] isi;
	isi = new atype *[M];
	for (int i=0;i<M;++i)
	{
		isi[i] = new atype [N];
		for (int j=0;j<N;++j)
		{
			isi[i][j]=m[i][j];		
		}
	}
	return *this;
}

// operator overloading []
template <class atype>
atype* matrix<atype>::operator [] (int i) const
{
	return isi[i];
}

// getter dan setter
template <class atype>
int matrix<atype>::getm ()
{
	return M;
}

template <class atype>
int matrix<atype>::getn ()
{
	return N;
}

#endif