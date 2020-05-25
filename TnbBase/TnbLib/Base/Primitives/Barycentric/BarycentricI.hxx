#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Cmpt>
inline tnbLib::Barycentric<Cmpt>::Barycentric()
{}


template<class Cmpt>
inline tnbLib::Barycentric<Cmpt>::Barycentric(const tnbLib::zero)
	:
	Barycentric::vsType(Zero)
{}


template<class Cmpt>
inline tnbLib::Barycentric<Cmpt>::Barycentric
(
	const Cmpt& va,
	const Cmpt& vb,
	const Cmpt& vc,
	const Cmpt& vd
)
{
	this->v_[A] = va;
	this->v_[B] = vb;
	this->v_[C] = vc;
	this->v_[D] = vd;
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Cmpt>
inline const Cmpt& tnbLib::Barycentric<Cmpt>::a() const
{
	return this->v_[A];
}


template<class Cmpt>
inline const Cmpt& tnbLib::Barycentric<Cmpt>::b() const
{
	return this->v_[B];
}


template<class Cmpt>
inline const Cmpt& tnbLib::Barycentric<Cmpt>::c() const
{
	return this->v_[C];
}


template<class Cmpt>
inline const Cmpt& tnbLib::Barycentric<Cmpt>::d() const
{
	return this->v_[D];
}


template<class Cmpt>
inline Cmpt& tnbLib::Barycentric<Cmpt>::a()
{
	return this->v_[A];
}


template<class Cmpt>
inline Cmpt& tnbLib::Barycentric<Cmpt>::b()
{
	return this->v_[B];
}


template<class Cmpt>
inline Cmpt& tnbLib::Barycentric<Cmpt>::c()
{
	return this->v_[C];
}


template<class Cmpt>
inline Cmpt& tnbLib::Barycentric<Cmpt>::d()
{
	return this->v_[D];
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Global Operators  * * * * * * * * * * * * * //

	template<class Cmpt>
	inline Cmpt operator&(const Barycentric<Cmpt>& b1, const Barycentric<Cmpt>& b2)
	{
		return b1.a()*b2.a() + b1.b()*b2.b() + b1.c()*b2.c() + b1.d()*b2.d();
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //