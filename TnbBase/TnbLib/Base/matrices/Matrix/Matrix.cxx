#include <Matrix.hxx>

// * * * * * * * * * * * * * * * Static Members  * * * * * * * * * * * * * * //

template<class Form, class Type>
const tnbLib::Matrix<Form, Type> tnbLib::Matrix<Form, Type>::zero;


// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

template<class Form, class Type>
void tnbLib::Matrix<Form, Type>::allocate()
{
	if (n_ && m_)
	{
		v_ = new Type*[n_];
		v_[0] = new Type[n_*m_];

		for (register label i = 1; i < n_; i++)
		{
			v_[i] = v_[i - 1] + m_;
		}
	}
}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

template<class Form, class Type>
tnbLib::Matrix<Form, Type>::~Matrix()
{
	if (v_)
	{
		delete[](v_[0]);
		delete[] v_;
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Form, class Type>
tnbLib::Matrix<Form, Type>::Matrix(const label n, const label m)
	:
	v_(NULL),
	n_(n),
	m_(m)
{
	if (n_ < 0 || m_ < 0)
	{
		FatalErrorIn
		(
			"Matrix<Form, Type>::Matrix(const label n, const label m)"
		) << "bad n, m " << n_ << ", " << m_
			<< abort(FatalError);
	}

	allocate();
}


template<class Form, class Type>
tnbLib::Matrix<Form, Type>::Matrix(const label n, const label m, const Type& a)
	:
	v_(NULL),
	n_(n),
	m_(m)
{
	if (n_ < 0 || m_ < 0)
	{
		FatalErrorIn
		(
			"Matrix<Form, Type>::Matrix"
			"(const label n, const label m, const T&)"
		) << "bad n, m " << n_ << ", " << m_
			<< abort(FatalError);
	}

	allocate();

	if (v_)
	{
		Type* v = v_[0];

		label nm = n_ * m_;

		for (register label i = 0; i < nm; i++)
		{
			v[i] = a;
		}
	}
}


template<class Form, class Type>
tnbLib::Matrix<Form, Type>::Matrix(const Matrix<Form, Type>& a)
	:
	v_(NULL),
	n_(a.n_),
	m_(a.m_)
{
	if (a.v_)
	{
		allocate();
		Type* v = v_[0];
		const Type* av = a.v_[0];

		label nm = n_ * m_;
		for (register label i = 0; i < nm; i++)
		{
			v[i] = av[i];
		}
	}
}


template<class Form, class Type>
void tnbLib::Matrix<Form, Type>::clear()
{
	if (v_)
	{
		delete[](v_[0]);
		delete[] v_;
	}
	n_ = 0;
	m_ = 0;
	v_ = NULL;
}


template<class Form, class Type>
void tnbLib::Matrix<Form, Type>::transfer(Matrix<Form, Type>& a)
{
	clear();

	n_ = a.n_;
	a.n_ = 0;

	m_ = a.m_;
	a.m_ = 0;

	v_ = a.v_;
	a.v_ = NULL;
}


template<class Form, class Type>
Form tnbLib::Matrix<Form, Type>::T() const
{
	const Matrix<Form, Type>& A = *this;
	Form At(m(), n());

	for (register label i = 0; i < n(); i++)
	{
		for (register label j = 0; j < m(); j++)
		{
			At[j][i] = A[i][j];
		}
	}

	return At;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Form, class Type>
void tnbLib::Matrix<Form, Type>::operator=(const Type& t)
{
	if (v_)
	{
		Type* v = v_[0];

		label nm = n_ * m_;
		for (register label i = 0; i < nm; i++)
		{
			v[i] = t;
		}
	}
}


// Assignment operator. Takes linear time.
template<class Form, class Type>
void tnbLib::Matrix<Form, Type>::operator=(const Matrix<Form, Type>& a)
{
	if (this == &a)
	{
		FatalErrorIn
		(
			"Matrix<Form, Type>::operator=(const Matrix<Form, Type>&)"
		) << "attempted assignment to self"
			<< abort(FatalError);
	}

	if (n_ != a.n_ || m_ != a.m_)
	{
		clear();
		n_ = a.n_;
		m_ = a.m_;
		allocate();
	}

	if (v_)
	{
		Type* v = v_[0];
		const Type* av = a.v_[0];

		label nm = n_ * m_;
		for (register label i = 0; i < nm; i++)
		{
			v[i] = av[i];
		}
	}
}


// * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

template<class Form, class Type>
const Type& tnbLib::max(const Matrix<Form, Type>& a)
{
	label nm = a.n()*a.m();

	if (nm)
	{
		label curMaxI = 0;
		const Type* v = a[0];

		for (register label i = 1; i < nm; i++)
		{
			if (v[i] > v[curMaxI])
			{
				curMaxI = i;
			}
		}

		return v[curMaxI];
	}
	else
	{
		FatalErrorIn("max(const Matrix<Form, Type>&)")
			<< "matrix is empty"
			<< abort(FatalError);

		// Return in error to keep compiler happy
		return a[0][0];
	}
}


template<class Form, class Type>
const Type& tnbLib::min(const Matrix<Form, Type>& a)
{
	label nm = a.n()*a.m();

	if (nm)
	{
		label curMinI = 0;
		const Type* v = a[0];

		for (register label i = 1; i < nm; i++)
		{
			if (v[i] < v[curMinI])
			{
				curMinI = i;
			}
		}

		return v[curMinI];
	}
	else
	{
		FatalErrorIn("min(const Matrix<Form, Type>&)")
			<< "matrix is empty"
			<< abort(FatalError);

		// Return in error to keep compiler happy
		return a[0][0];
	}
}


// * * * * * * * * * * * * * * * Global Operators  * * * * * * * * * * * * * //

template<class Form, class Type>
Form tnbLib::operator-(const Matrix<Form, Type>& a)
{
	Form na(a.n(), a.m());

	if (a.n() && a.m())
	{
		Type* nav = na[0];
		const Type* av = a[0];

		label nm = a.n()*a.m();
		for (register label i = 0; i < nm; i++)
		{
			nav[i] = -av[i];
		}
	}

	return na;
}


template<class Form, class Type>
Form tnbLib::operator+(const Matrix<Form, Type>& a, const Matrix<Form, Type>& b)
{
	if (a.n() != b.n())
	{
		FatalErrorIn
		(
			"Matrix<Form, Type>::operator+(const Matrix<Form, Type>&, "
			"const Matrix<Form, Type>&)"
		) << "attempted add matrices with different number of rows: "
			<< a.n() << ", " << b.n()
			<< abort(FatalError);
	}

	if (a.m() != b.m())
	{
		FatalErrorIn
		(
			"Matrix<Form, Type>::operator+(const Matrix<Form, Type>&, "
			"const Matrix<Form, Type>&)"
		) << "attempted add matrices with different number of columns: "
			<< a.m() << ", " << b.m()
			<< abort(FatalError);
	}

	Form ab(a.n(), a.m());

	Type* abv = ab[0];
	const Type* av = a[0];
	const Type* bv = b[0];

	label nm = a.n()*a.m();
	for (register label i = 0; i < nm; i++)
	{
		abv[i] = av[i] + bv[i];
	}

	return ab;
}


template<class Form, class Type>
Form tnbLib::operator-(const Matrix<Form, Type>& a, const Matrix<Form, Type>& b)
{
	if (a.n() != b.n())
	{
		FatalErrorIn
		(
			"Matrix<Form, Type>::operator-(const Matrix<Form, Type>&, "
			"const Matrix<Form, Type>&)"
		) << "attempted add matrices with different number of rows: "
			<< a.n() << ", " << b.n()
			<< abort(FatalError);
	}

	if (a.m() != b.m())
	{
		FatalErrorIn
		(
			"Matrix<Form, Type>::operator-(const Matrix<Form, Type>&, "
			"const Matrix<Form, Type>&)"
		) << "attempted add matrices with different number of columns: "
			<< a.m() << ", " << b.m()
			<< abort(FatalError);
	}

	Form ab(a.n(), a.m());

	Type* abv = ab[0];
	const Type* av = a[0];
	const Type* bv = b[0];

	label nm = a.n()*a.m();
	for (register label i = 0; i < nm; i++)
	{
		abv[i] = av[i] - bv[i];
	}

	return ab;
}


template<class Form, class Type>
Form tnbLib::operator*(const scalar s, const Matrix<Form, Type>& a)
{
	Form sa(a.n(), a.m());

	if (a.n() && a.m())
	{
		Type* sav = sa[0];
		const Type* av = a[0];

		label nm = a.n()*a.m();
		for (register label i = 0; i < nm; i++)
		{
			sav[i] = s * av[i];
		}
	}

	return sa;
}


// * * * * * * * * * * * * * * * *  IOStream operators * * * * * * * * * * * //

#include <MatrixIO.cxx>