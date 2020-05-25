#pragma once
// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class equationOfState>
inline tnbLib::hConstThermo<equationOfState>::hConstThermo
(
	const equationOfState& st,
	const scalar cp,
	const scalar hf
)
	:
	equationOfState(st),
	Cp_(cp),
	Hf_(hf)
{}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class equationOfState>
inline tnbLib::hConstThermo<equationOfState>::hConstThermo
(
	const word& name,
	const hConstThermo& ct
)
	:
	equationOfState(name, ct),
	Cp_(ct.Cp_),
	Hf_(ct.Hf_)
{}


template<class equationOfState>
inline tnbLib::autoPtr<tnbLib::hConstThermo<equationOfState> >
tnbLib::hConstThermo<equationOfState>::clone() const
{
	return autoPtr<hConstThermo<equationOfState> >
		(
			new hConstThermo<equationOfState>(*this)
			);
}


template<class equationOfState>
inline tnbLib::autoPtr<tnbLib::hConstThermo<equationOfState> >
tnbLib::hConstThermo<equationOfState>::New(Istream& is)
{
	return autoPtr<hConstThermo<equationOfState> >
		(
			new hConstThermo<equationOfState>(is)
			);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class equationOfState>
inline tnbLib::scalar tnbLib::hConstThermo<equationOfState>::cp
(
	const scalar
) const
{
	return Cp_ * this->W();
}


template<class equationOfState>
inline tnbLib::scalar tnbLib::hConstThermo<equationOfState>::h
(
	const scalar T
) const
{
	return (Cp_*T + Hf_)*this->W();
}


template<class equationOfState>
inline tnbLib::scalar tnbLib::hConstThermo<equationOfState>::hs
(
	const scalar T
) const
{
	return Cp_ * T*this->W();
}


template<class equationOfState>
inline tnbLib::scalar tnbLib::hConstThermo<equationOfState>::hc() const
{
	return Hf_ * this->W();
}


template<class equationOfState>
inline tnbLib::scalar tnbLib::hConstThermo<equationOfState>::s
(
	const scalar T
) const
{
	notImplemented
	(
		"scalar hConstThermo<equationOfState>::s(const scalar T) const"
	);
	return T;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class equationOfState>
inline void tnbLib::hConstThermo<equationOfState>::operator+=
(
	const hConstThermo<equationOfState>& ct
	)
{
	scalar molr1 = this->nMoles();

	equationOfState::operator+=(ct);

	molr1 /= this->nMoles();
	scalar molr2 = ct.nMoles() / this->nMoles();

	Cp_ = molr1 * Cp_ + molr2 * ct.Cp_;
	Hf_ = molr1 * Hf_ + molr2 * ct.Hf_;
}


template<class equationOfState>
inline void tnbLib::hConstThermo<equationOfState>::operator-=
(
	const hConstThermo<equationOfState>& ct
	)
{
	scalar molr1 = this->nMoles();

	equationOfState::operator-=(ct);

	molr1 /= this->nMoles();
	scalar molr2 = ct.nMoles() / this->nMoles();

	Cp_ = molr1 * Cp_ - molr2 * ct.Cp_;
	Hf_ = molr1 * Hf_ - molr2 * ct.Hf_;
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

template<class equationOfState>
inline tnbLib::hConstThermo<equationOfState> tnbLib::operator+
(
	const hConstThermo<equationOfState>& ct1,
	const hConstThermo<equationOfState>& ct2
	)
{
	equationOfState eofs
	(
		static_cast<const equationOfState&>(ct1)
		+ static_cast<const equationOfState&>(ct2)
	);

	return hConstThermo<equationOfState>
		(
			eofs,
			ct1.nMoles() / eofs.nMoles()*ct1.Cp_
			+ ct2.nMoles() / eofs.nMoles()*ct2.Cp_,
			ct1.nMoles() / eofs.nMoles()*ct1.Hf_
			+ ct2.nMoles() / eofs.nMoles()*ct2.Hf_
			);
}


template<class equationOfState>
inline tnbLib::hConstThermo<equationOfState> tnbLib::operator-
(
	const hConstThermo<equationOfState>& ct1,
	const hConstThermo<equationOfState>& ct2
	)
{
	equationOfState eofs
	(
		static_cast<const equationOfState&>(ct1)
		- static_cast<const equationOfState&>(ct2)
	);

	return hConstThermo<equationOfState>
		(
			eofs,
			ct1.nMoles() / eofs.nMoles()*ct1.Cp_
			- ct2.nMoles() / eofs.nMoles()*ct2.Cp_,
			ct1.nMoles() / eofs.nMoles()*ct1.Hf_
			- ct2.nMoles() / eofs.nMoles()*ct2.Hf_
			);
}


template<class equationOfState>
inline tnbLib::hConstThermo<equationOfState> tnbLib::operator*
(
	const scalar s,
	const hConstThermo<equationOfState>& ct
	)
{
	return hConstThermo<equationOfState>
		(
			s*static_cast<const equationOfState&>(ct),
			ct.Cp_,
			ct.Hf_
			);
}


template<class equationOfState>
inline tnbLib::hConstThermo<equationOfState> tnbLib::operator==
(
	const hConstThermo<equationOfState>& ct1,
	const hConstThermo<equationOfState>& ct2
	)
{
	return ct2 - ct1;
}


// ************************************************************************* //