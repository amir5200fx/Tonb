#pragma once
#include <specie.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Thermo, int PolySize>
inline tnbLib::polynomialTransport<Thermo, PolySize>::polynomialTransport
(
	const polynomialTransport& pt
)
	:
	Thermo(pt),
	muPolynomial_(pt.muPolynomial_),
	kappaPolynomial_(pt.kappaPolynomial_)
{}


template<class Thermo, int PolySize>
inline tnbLib::polynomialTransport<Thermo, PolySize>::polynomialTransport
(
	const Thermo& t,
	const Polynomial<PolySize>& muPoly,
	const Polynomial<PolySize>& kappaPoly
)
	:
	Thermo(t),
	muPolynomial_(muPoly),
	kappaPolynomial_(kappaPoly)
{}


template<class Thermo, int PolySize>
inline tnbLib::polynomialTransport<Thermo, PolySize>::polynomialTransport
(
	const word& name,
	const polynomialTransport& pt
)
	:
	Thermo(name, pt),
	muPolynomial_(pt.muPolynomial_),
	kappaPolynomial_(pt.kappaPolynomial_)
{}


template<class Thermo, int PolySize>
inline tnbLib::autoPtr<tnbLib::polynomialTransport<Thermo, PolySize> >
tnbLib::polynomialTransport<Thermo, PolySize>::clone() const
{
	return autoPtr<polynomialTransport<Thermo, PolySize> >
		(
			new polynomialTransport<Thermo, PolySize>(*this)
			);
}


template<class Thermo, int PolySize>
inline tnbLib::autoPtr<tnbLib::polynomialTransport<Thermo, PolySize> >
tnbLib::polynomialTransport<Thermo, PolySize>::New(Istream& is)
{
	return autoPtr<polynomialTransport<Thermo, PolySize> >
		(
			new polynomialTransport<Thermo, PolySize>(is)
			);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Thermo, int PolySize>
inline tnbLib::scalar tnbLib::polynomialTransport<Thermo, PolySize>::mu
(
	const scalar T
) const
{
	return muPolynomial_.evaluate(T) / this->W();
}


template<class Thermo, int PolySize>
inline tnbLib::scalar tnbLib::polynomialTransport<Thermo, PolySize>::kappa
(
	const scalar T
) const
{
	return kappaPolynomial_.evaluate(T) / this->W();
}


template<class Thermo, int PolySize>
inline tnbLib::scalar tnbLib::polynomialTransport<Thermo, PolySize>::alpha
(
	const scalar T
) const
{
	scalar deltaT = T - specie::Tstd();
	scalar CpBar =
		(deltaT*(this->H(T) - this->H(specie::Tstd())) + this->Cp(T))
		/ (sqr(deltaT) + 1);

	return kappa(T) / CpBar;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Thermo, int PolySize>
inline tnbLib::polynomialTransport<Thermo, PolySize>&
tnbLib::polynomialTransport<Thermo, PolySize>::operator=
(
	const polynomialTransport<Thermo, PolySize>& pt
	)
{
	Thermo::operator=(pt);

	muPolynomial_ = pt.muPolynomial_;
	kappaPolynomial_ = pt.kappaPolynomial_;

	return *this;
}


template<class Thermo, int PolySize>
inline void tnbLib::polynomialTransport<Thermo, PolySize>::operator+=
(
	const polynomialTransport<Thermo, PolySize>& pt
	)
{
	scalar molr1 = this->nMoles();

	Thermo::operator+=(pt);

	molr1 /= this->nMoles();
	scalar molr2 = pt.nMoles() / this->nMoles();

	muPolynomial_ = molr1 * muPolynomial_ + molr2 * pt.muPolynomial_;
	kappaPolynomial_ = molr1 * kappaPolynomial_ + molr2 * pt.kappaPolynomial_;
}


template<class Thermo, int PolySize>
inline void tnbLib::polynomialTransport<Thermo, PolySize>::operator-=
(
	const polynomialTransport<Thermo, PolySize>& pt
	)
{
	scalar molr1 = this->nMoles();

	Thermo::operator-=(pt);

	molr1 /= this->nMoles();
	scalar molr2 = pt.nMoles() / this->nMoles();

	muPolynomial_ = molr1 * muPolynomial_ - molr2 * pt.muPolynomial_;
	kappaPolynomial_ = molr1 * kappaPolynomial_ - molr2 * pt.kappaPolynomial_;
}


template<class Thermo, int PolySize>
inline void tnbLib::polynomialTransport<Thermo, PolySize>::operator*=
(
	const scalar s
	)
{
	Thermo::operator*=(s);
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

template<class Thermo, int PolySize>
inline tnbLib::polynomialTransport<Thermo, PolySize> tnbLib::operator+
(
	const polynomialTransport<Thermo, PolySize>& pt1,
	const polynomialTransport<Thermo, PolySize>& pt2
	)
{
	Thermo t
	(
		static_cast<const Thermo&>(pt1) + static_cast<const Thermo&>(pt2)
	);

	scalar molr1 = pt1.nMoles() / t.nMoles();
	scalar molr2 = pt2.nMoles() / t.nMoles();

	return polynomialTransport<Thermo, PolySize>
		(
			t,
			molr1*pt1.muPolynomial_ + molr2 * pt2.muPolynomial_,
			molr1*pt1.kappaPolynomial_ + molr2 * pt2.kappaPolynomial_
			);
}


template<class Thermo, int PolySize>
inline tnbLib::polynomialTransport<Thermo, PolySize> tnbLib::operator-
(
	const polynomialTransport<Thermo, PolySize>& pt1,
	const polynomialTransport<Thermo, PolySize>& pt2
	)
{
	Thermo t
	(
		static_cast<const Thermo&>(pt1) - static_cast<const Thermo&>(pt2)
	);

	scalar molr1 = pt1.nMoles() / t.nMoles();
	scalar molr2 = pt2.nMoles() / t.nMoles();

	return polynomialTransport<Thermo, PolySize>
		(
			t,
			molr1*pt1.muPolynomial_ - molr2 * pt2.muPolynomial_,
			molr1*pt1.kappaPolynomial_ - molr2 * pt2.kappaPolynomial_
			);
}


template<class Thermo, int PolySize>
inline tnbLib::polynomialTransport<Thermo, PolySize> tnbLib::operator*
(
	const scalar s,
	const polynomialTransport<Thermo, PolySize>& pt
	)
{
	return polynomialTransport<Thermo, PolySize>
		(
			s*static_cast<const Thermo&>(pt),
			pt.muPolynomial_,
			pt.kappaPolynomial_
			);
}


template<class Thermo, int PolySize>
inline tnbLib::polynomialTransport<Thermo, PolySize> tnbLib::operator==
(
	const polynomialTransport<Thermo, PolySize>& pt1,
	const polynomialTransport<Thermo, PolySize>& pt2
	)
{
	return pt2 - pt1;
}


// ************************************************************************* //