#include <redlichKwong.hxx>

#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::redlichKwong::redlichKwong(Istream& is)
	:
	specie(is),
	pcrit_(readScalar(is)),
	Tcrit_(readScalar(is)),
	a_(0.42748*pow(this->RR(), 2)*pow(Tcrit_, 2.5) / pcrit_),
	b_(0.08664*this->RR()*Tcrit_ / pcrit_),
	b2_(b_*b_),
	b3_(b2_*b_),
	//CL: Only uses the default values
	rhoMin_(1e-3),
	rhoMax_(1500),
	// Starting GUESS for the density by ideal gas law
	rhostd_(this->rho(this->Pstd(), this->Tstd(), this->Pstd() / (this->Tstd()*this->R())))
{
	is.check("redlichKwong::redlichKwong(Istream& is)");
}

//CL: Constructed needed in OpenFOAM 2.x.x
//CL: Code works fine, but compiling problem in OpenFOAM 1.6.ext
//CL:  because specie has no constructor using dict
/*
tnbLib::redlichKwong::redlichKwong(const dictionary& dict)
:
	specie(dict),
	pcrit_(readScalar(dict.subDict("equationOfState").lookup("pCritical"))),
	Tcrit_(readScalar(dict.subDict("equationOfState").lookup("TCritical"))),
	a_(0.42748*pow(this->RR(),2)*pow(Tcrit_,2.5)/pcrit_),
	b_(0.08664*this->RR()*Tcrit_/pcrit_),
	b2_(pow(b_,2)),
	b3_(pow(b_,3)),
	//CL: rhoMin and rhoMax are only used as boundaries for the bisection methode (see rho function)
	//CL: important: rhoMin and rhoMax are not used as boundary for the newton solver
	//CL: therefore, rho can be larger than rhoMax and smaller than rhoMin
	rhoMin_(dict.subDict("equationOfState").lookupOrDefault("rhoMin",1e-3)),
	rhoMax_(dict.subDict("equationOfState").lookupOrDefault("rhoMax",1500)),
	// Starting GUESS for the density by ideal gas law
	rhostd_(this->rho(this->Pstd(), this->Tstd(), this->Pstd()/(this->Tstd()*this->R())))
{
	is.check("redlichKwong::redlichKwong(Istream& is)");
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::redlichKwong::write(Ostream& os) const
{
	specie::write(os);

	dictionary dict("equationOfState");
	dict.add("pCritical", pcrit_);
	dict.add("TCritical", Tcrit_);
	dict.add("rhoMin", rhoMin_);
	dict.add("rhoMax", rhoMax_);

	os  << indent << dict.dictName() << dict;
}
*/


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const redlichKwong& rk)
{
	os << static_cast<const specie&>(rk) << token::SPACE
		<< rk.pcrit_ << tab << rk.Tcrit_;

	os.check("Ostream& operator<<(Ostream& os, const redlichKwong& st)");
	return os;
}


// ************************************************************************* //