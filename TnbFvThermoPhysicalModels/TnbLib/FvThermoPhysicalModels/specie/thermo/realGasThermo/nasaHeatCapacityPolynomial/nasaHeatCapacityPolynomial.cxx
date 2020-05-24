#include <nasaHeatCapacityPolynomial.hxx>

#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class equationOfState>
tnbLib::nasaHeatCapacityPolynomial<equationOfState>::nasaHeatCapacityPolynomial(Istream& is)
	:
	equationOfState(is),
	a1_(readScalar(is)),
	a2_(readScalar(is)),
	a3_(readScalar(is)),
	a4_(readScalar(is)),
	a5_(readScalar(is)),
	a6_(readScalar(is)),
	a7_(readScalar(is)),
	//CL: values at std needed to calculate enthalpy and entropy
	//CL: enthalpy and entropy = 0 @ std
	e0_std(e0(this->Tstd())),
	s0_std(s0(this->Tstd())),
	integral_p_dv_std(this->integral_p_dv(this->rhostd(), this->Tstd())),
	integral_dpdT_dv_std(this->integral_dpdT_dv(this->rhostd(), this->Tstd())),
	//cp @ STD (needed to limit cp for stability)
	cp_std(this->cp_nonLimited(this->rhostd(), this->Tstd()))
{
	is.check("nasaHeatCapacityPolynomial::nasaHeatCapacityPolynomial(Istream& is)");
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

template<class equationOfState>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const nasaHeatCapacityPolynomial<equationOfState>& np
	)
{
	os << static_cast<const equationOfState&>(np) << tab
		<< np.a1_ << tab << np.a2_ << tab << np.a3_ << tab << np.a4_ << tab << np.a5_ << tab << np.a6_ << tab << np.a7_;
	os.check("Ostream& operator<<(Ostream& os, const nasaHeatCapacityPolynomial& np)");
	return os;
}


// ************************************************************************* //