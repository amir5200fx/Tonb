#pragma once
#include <messageStream.hxx>
#include <IOstreams.hxx>
// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class thermo>
inline tnbLib::specieThermo<thermo>::specieThermo
(
	const thermo& sp
)
	:
	thermo(sp)
{}


template<class thermo>
inline tnbLib::scalar tnbLib::specieThermo<thermo>::T
(
	scalar f,
	scalar T0,
	scalar(specieThermo<thermo>::*F)(const scalar) const,
	scalar(specieThermo<thermo>::*dFdT)(const scalar) const
) const
{
	scalar Test = T0;
	scalar Tnew = T0;
	scalar Ttol = T0 * tol_();
	int iter = 0;

	do
	{
		// Limit the temperature jump in a single corrector to TJump_
		// HJ, 12/Oct/2010

		Test = Tnew;
		Tnew = Test
			- tnbLib::min(((this->*F)(Test) - f) / (this->*dFdT)(Test), TJump_());

		if (iter++ > maxIter_())
		{
			// Improvements: graceful exit with recovery.  HJ, 11/Oct/2010
			InfoIn
			(
				"specieThermo<thermo>::T(scalar f, scalar T0, "
				"scalar (specieThermo<thermo>::*F)(const scalar) const, "
				"scalar (specieThermo<thermo>::*dFdT)(const scalar) const"
				") const"
			) << "Maximum number of iterations exceeded.  T0 = "
				<< T0 << " F = " << (this->*F)(Test)
				<< " dFdT = " << (this->*dFdT)(Test)
				<< endl;

			// Use value where dFdT is calculated using T0.  HJ, 11/Oct/2010
			Tnew = f / (this->*dFdT)(T0);

			return Tnew;
		}

	} while (mag(Tnew - Test) > Ttol);

	return Tnew;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class thermo>
inline tnbLib::specieThermo<thermo>::specieThermo
(
	const word& name,
	const specieThermo& st
)
	:
	thermo(name, st)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class thermo>
inline tnbLib::scalar tnbLib::specieThermo<thermo>::cv(const scalar T) const
{
	return this->cp(T) - this->RR();
}


template<class thermo>
inline tnbLib::scalar tnbLib::specieThermo<thermo>::gamma(const scalar T) const
{
	scalar CP = this->cp(T);
	return CP / (CP - this->RR());
}


template<class thermo>
inline tnbLib::scalar tnbLib::specieThermo<thermo>::e(const scalar T) const
{
	return this->h(T) - this->RR()*(T - this->Tstd());
}


template<class thermo>
inline tnbLib::scalar tnbLib::specieThermo<thermo>::es(const scalar T) const
{
	return this->hs(T) - this->RR()*(T - this->Tstd());
}


template<class thermo>
inline tnbLib::scalar tnbLib::specieThermo<thermo>::g(const scalar T) const
{
	return this->h(T) - T * this->s(T);
}


template<class thermo>
inline tnbLib::scalar tnbLib::specieThermo<thermo>::a(const scalar T) const
{
	return this->e(T) - T * this->s(T);
}


template<class thermo>
inline tnbLib::scalar tnbLib::specieThermo<thermo>::Cp(const scalar T) const
{
	return this->cp(T) / this->W();
}


template<class thermo>
inline tnbLib::scalar tnbLib::specieThermo<thermo>::Cv(const scalar T) const
{
	return this->cv(T) / this->W();
}


template<class thermo>
inline tnbLib::scalar tnbLib::specieThermo<thermo>::H(const scalar T) const
{
	return this->h(T) / this->W();
}


template<class thermo>
inline tnbLib::scalar tnbLib::specieThermo<thermo>::Hs(const scalar T) const
{
	return this->hs(T) / this->W();
}


template<class thermo>
inline tnbLib::scalar tnbLib::specieThermo<thermo>::Hc() const
{
	return this->hc() / this->W();
}


template<class thermo>
inline tnbLib::scalar tnbLib::specieThermo<thermo>::S(const scalar T) const
{
	return this->s(T) / this->W();
}


template<class thermo>
inline tnbLib::scalar tnbLib::specieThermo<thermo>::E(const scalar T) const
{
	return this->e(T) / this->W();
}


template<class thermo>
inline tnbLib::scalar tnbLib::specieThermo<thermo>::G(const scalar T) const
{
	return this->g(T) / this->W();
}


template<class thermo>
inline tnbLib::scalar tnbLib::specieThermo<thermo>::A(const scalar T) const
{
	return this->a(T) / this->W();
}


template<class thermo>
inline tnbLib::scalar tnbLib::specieThermo<thermo>::K(const scalar T) const
{
	scalar arg = -this->nMoles()*this->g(T) / (this->RR()*T);

	if (arg < 600.0)
	{
		return ::exp(arg);
	}
	else
	{
		return VGREAT;
	}
}


template<class thermo>
inline tnbLib::scalar tnbLib::specieThermo<thermo>::Kp(const scalar T) const
{
	return K(T);
}


template<class thermo>
inline tnbLib::scalar tnbLib::specieThermo<thermo>::Kc(const scalar T) const
{
	if (equal(this->nMoles(), SMALL))
	{
		return Kp(T);
	}
	else
	{
		return Kp(T)*pow(this->Pstd() / (this->RR()*T), this->nMoles());
	}
}


template<class thermo>
inline tnbLib::scalar tnbLib::specieThermo<thermo>::Kx
(
	const scalar T,
	const scalar p
) const
{
	if (equal(this->nMoles(), SMALL))
	{
		return Kp(T);
	}
	else
	{
		return Kp(T)*pow(this->Pstd() / p, this->nMoles());
	}
}


template<class thermo>
inline tnbLib::scalar tnbLib::specieThermo<thermo>::Kn
(
	const scalar T,
	const scalar p,
	const scalar n
) const
{
	if (equal(this->nMoles(), SMALL))
	{
		return Kp(T);
	}
	else
	{
		return Kp(T)*pow(n*this->Pstd() / p, this->nMoles());
	}
}


template<class thermo>
inline tnbLib::scalar tnbLib::specieThermo<thermo>::TH
(
	const scalar h,
	const scalar T0
) const
{
	return T(h, T0, &specieThermo<thermo>::H, &specieThermo<thermo>::Cp);
}


template<class thermo>
inline tnbLib::scalar tnbLib::specieThermo<thermo>::THs
(
	const scalar hs,
	const scalar T0
) const
{
	return T(hs, T0, &specieThermo<thermo>::Hs, &specieThermo<thermo>::Cp);
}


template<class thermo>
inline tnbLib::scalar tnbLib::specieThermo<thermo>::TE
(
	const scalar e,
	const scalar T0
) const
{
	return T(e, T0, &specieThermo<thermo>::E, &specieThermo<thermo>::Cv);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class thermo>
inline void tnbLib::specieThermo<thermo>::operator+=
(
	const specieThermo<thermo>& st
	)
{
	thermo::operator+=(st);
}

template<class thermo>
inline void tnbLib::specieThermo<thermo>::operator-=
(
	const specieThermo<thermo>& st
	)
{
	thermo::operator-=(st);
}

template<class thermo>
inline void tnbLib::specieThermo<thermo>::operator*=(const scalar s)
{
	thermo::operator*=(s);
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

template<class thermo>
inline tnbLib::specieThermo<thermo> tnbLib::operator+
(
	const specieThermo<thermo>& st1,
	const specieThermo<thermo>& st2
	)
{
	return specieThermo<thermo>
		(
			static_cast<const thermo&>(st1) + static_cast<const thermo&>(st2)
			);
}


template<class thermo>
inline tnbLib::specieThermo<thermo> tnbLib::operator-
(
	const specieThermo<thermo>& st1,
	const specieThermo<thermo>& st2
	)
{
	return specieThermo<thermo>
		(
			static_cast<const thermo&>(st1) - static_cast<const thermo&>(st2)
			);
}


template<class thermo>
inline tnbLib::specieThermo<thermo> tnbLib::operator*
(
	const scalar s,
	const specieThermo<thermo>& st
	)
{
	return specieThermo<thermo>
		(
			s*static_cast<const thermo&>(st)
			);
}


template<class thermo>
inline tnbLib::specieThermo<thermo> tnbLib::operator==
(
	const specieThermo<thermo>& st1,
	const specieThermo<thermo>& st2
	)
{
	return st2 - st1;
}


// ************************************************************************* //