#include <constantHeatCapacity.hxx>

#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class equationOfState>
tnbLib::constantHeatCapacity<equationOfState>::constantHeatCapacity(Istream& is)
	:
	equationOfState(is),
	//CL: reads specific perfect gas heat capacity
	Cp0_(readScalar(is)),
	cp0_(Cp0_*this->W()),
	//CL: values for some need terms at std
	e0_std(e0(this->Tstd())),
	s0_std(s0(this->Tstd())),
	integral_p_dv_std(this->integral_p_dv(this->rhostd(), this->Tstd())),
	integral_dpdT_dv_std(this->integral_dpdT_dv(this->rhostd(), this->Tstd())),
	//CL: cp @ STD (needed to limit cp for stability)
	cp_std(this->cp_nonLimited(this->rhostd(), this->Tstd()))
{
	is.check("constantHeatCapacity::constantHeatCapacity(Istream& is)");
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

template<class equationOfState>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const constantHeatCapacity<equationOfState>& np
	)
{
	os << static_cast<const equationOfState&>(np) << tab
		<< np.Cp0_;
	os.check("Ostream& operator<<(Ostream& os, const constantHeatCapacity& np)");
	return os;
}


// ************************************************************************* //