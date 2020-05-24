#pragma once
// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<int PolySize>
inline tnbLib::icoPolynomial<PolySize>::icoPolynomial
(
	const specie& sp,
	const Polynomial<PolySize>& rhoPoly
)
	:
	specie(sp),
	rhoPolynomial_(rhoPoly)
{}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<int PolySize>
inline tnbLib::icoPolynomial<PolySize>::icoPolynomial
(
	const icoPolynomial<PolySize>& ip
)
	:
	specie(ip),
	rhoPolynomial_(ip.rhoPolynomial_)
{}


template<int PolySize>
inline tnbLib::icoPolynomial<PolySize>::icoPolynomial
(
	const word& name,
	const icoPolynomial<PolySize>& ip
)
	:
	specie(name, ip),
	rhoPolynomial_(ip.rhoPolynomial_)
{}


template<int PolySize>
inline tnbLib::autoPtr<tnbLib::icoPolynomial<PolySize> >
tnbLib::icoPolynomial<PolySize>::clone() const
{
	return autoPtr<icoPolynomial<PolySize> >
		(
			new icoPolynomial<PolySize>(*this)
			);
}


template<int PolySize>
inline tnbLib::autoPtr<tnbLib::icoPolynomial<PolySize> >
tnbLib::icoPolynomial<PolySize>::New(Istream& is)
{
	return autoPtr<icoPolynomial<PolySize> >(new icoPolynomial<PolySize>(is));
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<int PolySize>
inline tnbLib::scalar tnbLib::icoPolynomial<PolySize>::rho(scalar, scalar T) const
{
	return rhoPolynomial_.evaluate(T) / this->W();
}


template<int PolySize>
inline tnbLib::scalar tnbLib::icoPolynomial<PolySize>::psi(scalar, scalar) const
{
	return 0.0;
}


template<int PolySize>
inline tnbLib::scalar tnbLib::icoPolynomial<PolySize>::Z(scalar, scalar) const
{
	return 0.0;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<int PolySize>
inline tnbLib::icoPolynomial<PolySize>& tnbLib::icoPolynomial<PolySize>::operator=
(
	const icoPolynomial<PolySize>& ip
	)
{
	specie::operator=(ip);

	rhoPolynomial_ = ip.rhoPolynomial_;

	return *this;
}


template<int PolySize>
inline void tnbLib::icoPolynomial<PolySize>::operator+=
(
	const icoPolynomial<PolySize>& ip
	)
{
	scalar molr1 = this->nMoles();

	specie::operator+=(ip);

	molr1 /= this->nMoles();
	scalar molr2 = ip.nMoles() / this->nMoles();

	rhoPolynomial_ = molr1 * rhoPolynomial_ + molr2 * ip.rhoPolynomial_;
}


template<int PolySize>
inline void tnbLib::icoPolynomial<PolySize>::operator-=
(
	const icoPolynomial<PolySize>& ip
	)
{
	scalar molr1 = this->nMoles();

	specie::operator-=(ip);

	molr1 /= this->nMoles();
	scalar molr2 = ip.nMoles() / this->nMoles();

	rhoPolynomial_ = molr1 * rhoPolynomial_ - molr2 * ip.rhoPolynomial_;
}


template<int PolySize>
inline void tnbLib::icoPolynomial<PolySize>::operator*=(const scalar s)
{
	specie::operator*=(s);
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

template<int PolySize>
tnbLib::icoPolynomial<PolySize> tnbLib::operator+
(
	const icoPolynomial<PolySize>& ip1,
	const icoPolynomial<PolySize>& ip2
	)
{
	scalar nMoles = ip1.nMoles() + ip2.nMoles();
	scalar molr1 = ip1.nMoles() / nMoles;
	scalar molr2 = ip2.nMoles() / nMoles;

	return icoPolynomial<PolySize>
		(
			static_cast<const specie&>(ip1)
			+ static_cast<const specie&>(ip2),
			molr1*ip1.rhoPolynomial_ + molr2 * ip2.rhoPolynomial_
			);
}


template<int PolySize>
tnbLib::icoPolynomial<PolySize> tnbLib::operator-
(
	const icoPolynomial<PolySize>& ip1,
	const icoPolynomial<PolySize>& ip2
	)
{
	scalar nMoles = ip1.nMoles() + ip2.nMoles();
	scalar molr1 = ip1.nMoles() / nMoles;
	scalar molr2 = ip2.nMoles() / nMoles;

	return icoPolynomial<PolySize>
		(
			static_cast<const specie&>(ip1)
			- static_cast<const specie&>(ip2),
			molr1*ip1.rhoPolynomial_ - molr2 * ip2.rhoPolynomial_
			);
}


template<int PolySize>
tnbLib::icoPolynomial<PolySize> tnbLib::operator*
(
	const scalar s,
	const icoPolynomial<PolySize>& ip
	)
{
	return icoPolynomial<PolySize>
		(
			s*static_cast<const specie&>(ip),
			ip.rhoPolynomial_
			);
}


template<int PolySize>
tnbLib::icoPolynomial<PolySize> tnbLib::operator==
(
	const icoPolynomial<PolySize>& ip1,
	const icoPolynomial<PolySize>& ip2
	)
{
	return ip2 - ip1;
}


// ************************************************************************* //