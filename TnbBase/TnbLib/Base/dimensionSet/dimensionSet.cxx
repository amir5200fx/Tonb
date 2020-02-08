#include <dimensionSet.hxx>

#include <dimensionedScalar.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

defineTypeNameAndDebug(tnbLib::dimensionSet, 1);
const tnbLib::scalar tnbLib::dimensionSet::smallExponent = SMALL;


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::dimensionSet::dimensionSet
(
	const scalar mass,
	const scalar length,
	const scalar time,
	const scalar temperature,
	const scalar moles,
	const scalar current,
	const scalar luminousIntensity
)
{
	exponents_[MASS] = mass;
	exponents_[LENGTH] = length;
	exponents_[TIME] = time;
	exponents_[TEMPERATURE] = temperature;
	exponents_[MOLES] = moles;
	exponents_[CURRENT] = current;
	exponents_[LUMINOUS_INTENSITY] = luminousIntensity;
}


tnbLib::dimensionSet::dimensionSet
(
	const scalar mass,
	const scalar length,
	const scalar time,
	const scalar temperature,
	const scalar moles
)
{
	exponents_[MASS] = mass;
	exponents_[LENGTH] = length;
	exponents_[TIME] = time;
	exponents_[TEMPERATURE] = temperature;
	exponents_[MOLES] = moles;
	exponents_[CURRENT] = 0;
	exponents_[LUMINOUS_INTENSITY] = 0;
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::dimensionSet::dimensionless() const
{
	bool Dimensionless = true;

	for (int Dimension = 0; Dimension < nDimensions; Dimension++)
	{
		Dimensionless = Dimensionless &&
			(
				exponents_[Dimension] < smallExponent
				&& exponents_[Dimension] > -smallExponent
				);
	}

	return Dimensionless;
}


void tnbLib::dimensionSet::reset(const dimensionSet& ds)
{
	for (int Dimension = 0; Dimension < nDimensions; Dimension++)
	{
		exponents_[Dimension] = ds.exponents_[Dimension];
	}
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

tnbLib::scalar tnbLib::dimensionSet::operator[](const dimensionType type) const
{
	return exponents_[type];
}

tnbLib::scalar& tnbLib::dimensionSet::operator[](const dimensionType type)
{
	return exponents_[type];
}


bool tnbLib::dimensionSet::operator==(const dimensionSet& ds) const
{
	bool equall = true;

	for (int Dimension = 0; Dimension < nDimensions; Dimension++)
	{
		equall = equall &&
			(mag(exponents_[Dimension] - ds.exponents_[Dimension])
				< smallExponent);
	}

	return equall;
}

bool tnbLib::dimensionSet::operator!=(const dimensionSet& ds) const
{
	return !(operator==(ds));
}


bool tnbLib::dimensionSet::operator=(const dimensionSet& ds) const
{
	if (dimensionSet::debug && *this != ds)
	{
		FatalErrorIn("dimensionSet::operator=(const dimensionSet& ds) const")
			<< "Different dimensions for =" << endl
			<< "     dimensions : " << *this << " = " << ds << endl
			<< abort(FatalError);
	}

	return true;
}


bool tnbLib::dimensionSet::operator+=(const dimensionSet& ds) const
{
	if (dimensionSet::debug && *this != ds)
	{
		FatalErrorIn("dimensionSet::operator+=(const dimensionSet& ds) const")
			<< "Different dimensions for +=" << endl
			<< "     dimensions : " << *this << " = " << ds << endl
			<< abort(FatalError);
	}

	return true;
}

bool tnbLib::dimensionSet::operator-=(const dimensionSet& ds) const
{
	if (dimensionSet::debug && *this != ds)
	{
		FatalErrorIn("dimensionSet::operator-=(const dimensionSet& ds) const")
			<< "Different dimensions for -=" << endl
			<< "     dimensions : " << *this << " = " << ds << endl
			<< abort(FatalError);
	}

	return true;
}

bool tnbLib::dimensionSet::operator*=(const dimensionSet& ds)
{
	reset((*this)*ds);

	return true;
}

bool tnbLib::dimensionSet::operator/=(const dimensionSet& ds)
{
	reset((*this) / ds);

	return true;
}


// * * * * * * * * * * * * * * * Friend functions * * * * * * * * * * * * * * //

tnbLib::dimensionSet tnbLib::max(const dimensionSet& ds1, const dimensionSet& ds2)
{
	if (dimensionSet::debug && ds1 != ds2)
	{
		FatalErrorIn("max(const dimensionSet& ds1, const dimensionSet& ds2)")
			<< "Arguments of max have different dimensions" << endl
			<< "     dimensions : " << ds1 << " and " << ds2 << endl
			<< abort(FatalError);
	}

	return ds1;
}

tnbLib::dimensionSet tnbLib::min(const dimensionSet& ds1, const dimensionSet& ds2)
{
	if (dimensionSet::debug && ds1 != ds2)
	{
		FatalErrorIn("min(const dimensionSet& ds1, const dimensionSet& ds2)")
			<< "Arguments of min have different dimensions" << endl
			<< "     dimensions : " << ds1 << " and " << ds2 << endl
			<< abort(FatalError);
	}

	return ds1;
}


tnbLib::dimensionSet tnbLib::cmptMultiply
(
	const dimensionSet& ds1,
	const dimensionSet& ds2
)
{
	return ds1 * ds2;
}


tnbLib::dimensionSet tnbLib::cmptDivide
(
	const dimensionSet& ds1,
	const dimensionSet& ds2
)
{
	return ds1 / ds2;
}


tnbLib::dimensionSet tnbLib::pow(const dimensionSet& ds, const scalar p)
{
	dimensionSet dimPow
	(
		ds[dimensionSet::MASS] * p,
		ds[dimensionSet::LENGTH] * p,
		ds[dimensionSet::TIME] * p,
		ds[dimensionSet::TEMPERATURE] * p,
		ds[dimensionSet::MOLES] * p,
		ds[dimensionSet::CURRENT] * p,
		ds[dimensionSet::LUMINOUS_INTENSITY] * p
	);

	return dimPow;
}

tnbLib::dimensionSet tnbLib::pow
(
	const dimensionSet& ds,
	const dimensionedScalar& dS
)
{
	if (dimensionSet::debug && !dS.dimensions().dimensionless())
	{
		FatalErrorIn("pow(const dimensionSet& ds, const dimensionedScalar& dS)")
			<< "Exponent of pow are not dimensionless"
			<< abort(FatalError);
	}

	dimensionSet dimPow
	(
		ds[dimensionSet::MASS] * dS.value(),
		ds[dimensionSet::LENGTH] * dS.value(),
		ds[dimensionSet::TIME] * dS.value(),
		ds[dimensionSet::TEMPERATURE] * dS.value(),
		ds[dimensionSet::MOLES] * dS.value(),
		ds[dimensionSet::CURRENT] * dS.value(),
		ds[dimensionSet::LUMINOUS_INTENSITY] * dS.value()
	);

	return dimPow;
}

tnbLib::dimensionSet tnbLib::pow
(
	const dimensionedScalar& dS,
	const dimensionSet& ds
)
{
	if
		(
			dimensionSet::debug
			&& !dS.dimensions().dimensionless()
			&& !ds.dimensionless())
	{
		FatalErrorIn("pow(const dimensionedScalar& dS, const dimensionSet& ds)")
			<< "Argument or exponent of pow not dimensionless" << endl
			<< abort(FatalError);
	}

	return ds;
}


tnbLib::dimensionSet tnbLib::sqr(const dimensionSet& ds)
{
	return pow(ds, 2);
}

tnbLib::dimensionSet tnbLib::pow3(const dimensionSet& ds)
{
	return pow(ds, 3);
}

tnbLib::dimensionSet tnbLib::pow4(const dimensionSet& ds)
{
	return pow(ds, 4);
}

tnbLib::dimensionSet tnbLib::pow5(const dimensionSet& ds)
{
	return pow(ds, 5);
}

tnbLib::dimensionSet tnbLib::pow6(const dimensionSet& ds)
{
	return pow(ds, 6);
}

tnbLib::dimensionSet tnbLib::sqrt(const dimensionSet& ds)
{
	return pow(ds, 0.5);
}

tnbLib::dimensionSet tnbLib::magSqr(const dimensionSet& ds)
{
	return pow(ds, 2);
}

tnbLib::dimensionSet tnbLib::mag(const dimensionSet& ds)
{
	return ds;
}

tnbLib::dimensionSet tnbLib::sign(const dimensionSet&)
{
	return dimless;
}

tnbLib::dimensionSet tnbLib::pos(const dimensionSet&)
{
	return dimless;
}

tnbLib::dimensionSet tnbLib::neg(const dimensionSet&)
{
	return dimless;
}

tnbLib::dimensionSet tnbLib::inv(const dimensionSet& ds)
{
	return dimless / ds;
}

tnbLib::dimensionSet tnbLib::hinv(const dimensionSet& ds)
{
	return inv(ds);
}

tnbLib::dimensionSet tnbLib::trans(const dimensionSet& ds)
{
	if (dimensionSet::debug && !ds.dimensionless())
	{
		FatalErrorIn("trans(const dimensionSet& ds)")
			<< "Argument of trancendental function not dimensionless"
			<< abort(FatalError);
	}

	return ds;
}

tnbLib::dimensionSet tnbLib::transform(const dimensionSet& ds)
{
	return ds;
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

tnbLib::dimensionSet tnbLib::operator-(const dimensionSet& ds)
{
	return ds;
}

tnbLib::dimensionSet tnbLib::operator+
(
	const dimensionSet& ds1,
	const dimensionSet& ds2
	)
{
	dimensionSet dimSum(ds1);

	if (dimensionSet::debug && ds1 != ds2)
	{
		FatalErrorIn
		("operator+(const dimensionSet& ds1, const dimensionSet& ds2)")
			<< "LHS and RHS of + have different dimensions" << endl
			<< "     dimensions : " << ds1 << " + " << ds2 << endl
			<< abort(FatalError);
	}

	return dimSum;
}

tnbLib::dimensionSet tnbLib::operator-
(
	const dimensionSet& ds1,
	const dimensionSet& ds2
	)
{
	dimensionSet dimDifference(ds1);

	if (dimensionSet::debug && ds1 != ds2)
	{
		FatalErrorIn
		("operator-(const dimensionSet& ds1, const dimensionSet& ds2)")
			<< "LHS and RHS of - have different dimensions" << endl
			<< "     dimensions : " << ds1 << " - " << ds2 << endl
			<< abort(FatalError);
	}

	return dimDifference;
}

tnbLib::dimensionSet tnbLib::operator*
(
	const dimensionSet& ds1,
	const dimensionSet& ds2
	)
{
	dimensionSet dimProduct(ds1);

	for (int Dimension = 0; Dimension < dimensionSet::nDimensions; Dimension++)
	{
		dimProduct.exponents_[Dimension] += ds2.exponents_[Dimension];
	}

	return dimProduct;
}

tnbLib::dimensionSet tnbLib::operator/
(
	const dimensionSet& ds1,
	const dimensionSet& ds2
	)
{
	dimensionSet dimQuotient(ds1);

	for (int Dimension = 0; Dimension < dimensionSet::nDimensions; Dimension++)
	{
		dimQuotient.exponents_[Dimension] -= ds2.exponents_[Dimension];
	}

	return dimQuotient;
}


tnbLib::dimensionSet tnbLib::operator&
(
	const dimensionSet& ds1,
	const dimensionSet& ds2
	)
{
	return ds1 * ds2;
}

tnbLib::dimensionSet tnbLib::operator^
(
	const dimensionSet& ds1,
	const dimensionSet& ds2
	)
{
	return ds1 * ds2;
}

tnbLib::dimensionSet tnbLib::operator&&
(
	const dimensionSet& ds1,
	const dimensionSet& ds2
	)
{
	return ds1 * ds2;
}


// ************************************************************************* //