#pragma once
// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class EquationOfState, int PolySize>
inline tnbLib::hPolynomialThermo<EquationOfState, PolySize>::hPolynomialThermo
(
	const EquationOfState& pt,
	const scalar Hf,
	const scalar Sf,
	const Polynomial<PolySize>& cpPoly,
	const typename Polynomial<PolySize>::intPolyType& hPoly,
	const Polynomial<PolySize>& sPoly
)
	:
	EquationOfState(pt),
	Hf_(Hf),
	Sf_(Sf),
	cpPolynomial_(cpPoly),
	hPolynomial_(hPoly),
	sPolynomial_(sPoly)
{}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class EquationOfState, int PolySize>
inline tnbLib::hPolynomialThermo<EquationOfState, PolySize>::hPolynomialThermo
(
	const hPolynomialThermo& pt
)
	:
	EquationOfState(pt),
	Hf_(pt.Hf_),
	Sf_(pt.Sf_),
	cpPolynomial_(pt.cpPolynomial_),
	hPolynomial_(pt.hPolynomial_),
	sPolynomial_(pt.sPolynomial_)
{}


template<class EquationOfState, int PolySize>
inline tnbLib::hPolynomialThermo<EquationOfState, PolySize>::hPolynomialThermo
(
	const word& name,
	const hPolynomialThermo& pt
)
	:
	EquationOfState(name, pt),
	Hf_(pt.Hf_),
	Sf_(pt.Sf_),
	cpPolynomial_(pt.cpPolynomial_),
	hPolynomial_(pt.hPolynomial_),
	sPolynomial_(pt.sPolynomial_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class EquationOfState, int PolySize>
inline tnbLib::scalar tnbLib::hPolynomialThermo<EquationOfState, PolySize>::cp
(
	const scalar T
) const
{
	return cpPolynomial_.evaluate(T);
}


template<class EquationOfState, int PolySize>
inline tnbLib::scalar tnbLib::hPolynomialThermo<EquationOfState, PolySize>::h
(
	const scalar T
) const
{
	return hPolynomial_.evaluate(T);
}


template<class EquationOfState, int PolySize>
inline tnbLib::scalar tnbLib::hPolynomialThermo<EquationOfState, PolySize>::hs
(
	const scalar T
) const
{
	return h(T) - hc();
}


template<class EquationOfState, int PolySize>
inline tnbLib::scalar tnbLib::hPolynomialThermo<EquationOfState, PolySize>::hc()
const
{
	return Hf_;
}


template<class EquationOfState, int PolySize>
inline tnbLib::scalar tnbLib::hPolynomialThermo<EquationOfState, PolySize>::s
(
	const scalar T
) const
{
	return sPolynomial_.evaluate(T);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class EquationOfState, int PolySize>
inline tnbLib::hPolynomialThermo<EquationOfState, PolySize>&
tnbLib::hPolynomialThermo<EquationOfState, PolySize>::operator=
(
	const hPolynomialThermo<EquationOfState, PolySize>& pt
	)
{
	EquationOfState::operator=(pt);

	Hf_ = pt.Hf_;
	Sf_ = pt.Sf_;
	cpPolynomial_ = pt.cpPolynomial_;
	hPolynomial_ = pt.hPolynomial_;
	sPolynomial_ = pt.sPolynomial_;

	return *this;
}


template<class EquationOfState, int PolySize>
inline void tnbLib::hPolynomialThermo<EquationOfState, PolySize>::operator+=
(
	const hPolynomialThermo<EquationOfState, PolySize>& pt
	)
{
	scalar molr1 = this->nMoles();

	EquationOfState::operator+=(pt);

	molr1 /= this->nMoles();
	scalar molr2 = pt.nMoles() / this->nMoles();

	Hf_ = molr1 * Hf_ + molr2 * pt.Hf_;
	Sf_ = molr1 * Sf_ + molr2 * pt.Sf_;
	cpPolynomial_ = molr1 * cpPolynomial_ + molr2 * pt.cpPolynomial_;
	hPolynomial_ = molr1 * hPolynomial_ + molr2 * pt.hPolynomial_;
	sPolynomial_ = molr1 * sPolynomial_ + molr2 * pt.sPolynomial_;
}


template<class EquationOfState, int PolySize>
inline void tnbLib::hPolynomialThermo<EquationOfState, PolySize>::operator-=
(
	const hPolynomialThermo<EquationOfState, PolySize>& pt
	)
{
	scalar molr1 = this->nMoles();

	EquationOfState::operator-=(pt);

	molr1 /= this->nMoles();
	scalar molr2 = pt.nMoles() / this->nMoles();

	Hf_ = molr1 * Hf_ - molr2 * pt.Hf_;
	Sf_ = molr1 * Sf_ - molr2 * pt.Sf_;
	cpPolynomial_ = molr1 * cpPolynomial_ - molr2 * pt.cpPolynomial_;
	hPolynomial_ = molr1 * hPolynomial_ - molr2 * pt.hPolynomial_;
	sPolynomial_ = molr1 * sPolynomial_ - molr2 * pt.sPolynomial_;
}


template<class EquationOfState, int PolySize>
inline void tnbLib::hPolynomialThermo<EquationOfState, PolySize>::operator*=
(
	const scalar s
	)
{
	EquationOfState::operator*=(s);
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

template<class EquationOfState, int PolySize>
inline tnbLib::hPolynomialThermo<EquationOfState, PolySize> tnbLib::operator+
(
	const hPolynomialThermo<EquationOfState, PolySize>& pt1,
	const hPolynomialThermo<EquationOfState, PolySize>& pt2
	)
{
	EquationOfState eofs = pt1;
	eofs += pt2;

	scalar molr1 = pt1.nMoles() / eofs.nMoles();
	scalar molr2 = pt2.nMoles() / eofs.nMoles();

	return hPolynomialThermo<EquationOfState, PolySize>
		(
			eofs,
			molr1*pt1.Hf_ + molr2 * pt2.Hf_,
			molr1*pt1.Sf_ + molr2 * pt2.Sf_,
			molr1*pt1.cpPolynomial_ + molr2 * pt2.cpPolynomial_,
			molr1*pt1.hPolynomial_ + molr2 * pt2.hPolynomial_,
			molr1*pt1.sPolynomial_ + molr2 * pt2.sPolynomial_
			);
}


template<class EquationOfState, int PolySize>
inline tnbLib::hPolynomialThermo<EquationOfState, PolySize> tnbLib::operator-
(
	const hPolynomialThermo<EquationOfState, PolySize>& pt1,
	const hPolynomialThermo<EquationOfState, PolySize>& pt2
	)
{
	EquationOfState eofs = pt1;
	eofs -= pt2;

	scalar molr1 = pt1.nMoles() / eofs.nMoles();
	scalar molr2 = pt2.nMoles() / eofs.nMoles();

	return hPolynomialThermo<EquationOfState, PolySize>
		(
			eofs,
			molr1*pt1.Hf_ - molr2 * pt2.Hf_,
			molr1*pt1.Sf_ - molr2 * pt2.Sf_,
			molr1*pt1.cpPolynomial_ - molr2 * pt2.cpPolynomial_,
			molr1*pt1.hPolynomial_ - molr2 * pt2.hPolynomial_,
			molr1*pt1.sPolynomial_ - molr2 * pt2.sPolynomial_
			);
}


template<class EquationOfState, int PolySize>
inline tnbLib::hPolynomialThermo<EquationOfState, PolySize> tnbLib::operator*
(
	const scalar s,
	const hPolynomialThermo<EquationOfState, PolySize>& pt
	)
{
	return hPolynomialThermo<EquationOfState, PolySize>
		(
			s*static_cast<const EquationOfState&>(pt),
			pt.Hf_,
			pt.Sf_,
			pt.cpPolynomial_,
			pt.hPolynomial_,
			pt.sPolynomial_
			);
}


template<class EquationOfState, int PolySize>
inline tnbLib::hPolynomialThermo<EquationOfState, PolySize> tnbLib::operator==
(
	const hPolynomialThermo<EquationOfState, PolySize>& pt1,
	const hPolynomialThermo<EquationOfState, PolySize>& pt2
	)
{
	return pt2 - pt1;
}


// ************************************************************************* //