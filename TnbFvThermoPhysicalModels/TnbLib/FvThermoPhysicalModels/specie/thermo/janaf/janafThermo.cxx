#include <janafThermo.hxx>

#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class equationOfState>
tnbLib::janafThermo<equationOfState>::janafThermo(Istream& is)
	:
	equationOfState(is),
	Tlow_(readScalar(is)),
	Thigh_(readScalar(is)),
	Tcommon_(readScalar(is))
{
	if (Tlow_ >= Thigh_)
	{
		FatalIOErrorIn
		(
			"janafThermo<equationOfState>::janafThermo(Istream& is)",
			is
		) << "Tlow(" << Tlow_ << ") >= Thigh(" << Thigh_ << ')'
			<< exit(FatalIOError);
	}

	if (Tcommon_ <= Tlow_)
	{
		FatalIOErrorIn
		(
			"janafThermo<equationOfState>::janafThermo(Istream& is)",
			is
		) << "Tcommon(" << Tcommon_ << ") <= Tlow(" << Tlow_ << ')'
			<< exit(FatalIOError);
	}

	if (Tcommon_ > Thigh_)
	{
		FatalIOErrorIn
		(
			"janafThermo<equationOfState>::janafThermo(Istream& is)",
			is
		) << "Tcommon(" << Tcommon_ << ") > Thigh(" << Thigh_ << ')'
			<< exit(FatalIOError);
	}

	for
		(
			register label coefLabel = 0;
			coefLabel < janafThermo<equationOfState>::nCoeffs_;
			coefLabel++
			)
	{
		is >> highCpCoeffs_[coefLabel];
	}

	for
		(
			register label coefLabel = 0;
			coefLabel < janafThermo<equationOfState>::nCoeffs_;
			coefLabel++
			)
	{
		is >> lowCpCoeffs_[coefLabel];
	}

	// Check state of Istream
	is.check("janafThermo::janafThermo(Istream& is)");
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

template<class equationOfState>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const janafThermo<equationOfState>& jt
	)
{
	os << static_cast<const equationOfState&>(jt) << nl
		<< "    " << jt.Tlow_
		<< tab << jt.Thigh_
		<< tab << jt.Tcommon_;

	os << nl << "    ";

	for
		(
			register label coefLabel = 0;
			coefLabel < janafThermo<equationOfState>::nCoeffs_;
			coefLabel++
			)
	{
		os << jt.highCpCoeffs_[coefLabel] << ' ';
	}

	os << nl << "    ";

	for
		(
			register label coefLabel = 0;
			coefLabel < janafThermo<equationOfState>::nCoeffs_;
			coefLabel++
			)
	{
		os << jt.lowCpCoeffs_[coefLabel] << ' ';
	}

	os << endl;

	os.check
	(
		"operator<<(Ostream& os, const janafThermo<equationOfState>& jt)"
	);

	return os;
}


// ************************************************************************* //