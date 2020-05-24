#include <soaveRedlichKwong.hxx>

#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::soaveRedlichKwong::soaveRedlichKwong(Istream& is)
	:
	specie(is),
	pcrit_(readScalar(is)),
	Tcrit_(readScalar(is)),
	azentricFactor_(readScalar(is)),
	a0_(0.42747*pow(this->RR(), 2)*pow(Tcrit_, 2) / pcrit_),
	b_(0.08664*this->RR()*Tcrit_ / pcrit_),
	n_(0.48508 + 1.55171*azentricFactor_ - 0.15613*pow(azentricFactor_, 2)),
	b2_(b_*b_),
	//CL: Only uses the default values
	rhoMin_(1e-3),
	rhoMax_(1500),
	aSave(0.0),
	daSave(0.0),
	d2aSave(0.0),
	TSave(0.0),
	// Starting GUESS for the density by ideal gas law
	rhostd_(this->rho(this->Pstd(), this->Tstd(), this->Pstd() / (this->Tstd()*this->R())))
{
	is.check("soaveRedlichKwong::soaveRedlichKwong(Istream& is)");
}

//CL: Constructed needed in OpenFOAM 2.x.x
//CL: Code works fine, but compiling problem in OpenFOAM 1.6.ext
//CL:  because specie has no constructor using dict
/*
soaveRedlichKwong::soaveRedlichKwong(const dictionary& dict)
:
	specie(dict),
	pcrit_(readScalar(dict.subDict("equationOfState").lookup("pCritical"))),
	Tcrit_(readScalar(dict.subDict("equationOfState").lookup("TCritical"))),
	azentricFactor_(readScalar(dict.subDict("equationOfState").lookup("azentricFactor"))),
	a0_(0.42747*pow(this->RR(), 2)*pow(Tcrit_, 2)/pcrit_),
	b_(0.08664*this->RR()*Tcrit_/pcrit_),
	n_(0.48508 + 1.55171*azentricFactor_ - 0.15613*pow(azentricFactor_, 2)),
	b2_(b_*b_),
	b3_(b_*b2_),
	b5_(b3_*b2_),
	//CL: rhoMin and rhoMax are only used as boundaries for the bisection method (see rho function)
	//CL: important: rhoMin and rhoMax are not used as boundary for the newton solver
	//CL: therefore, rho can be larger than rhoMax and smaller than rhoMin
	rhoMin_(dict.subDict("equationOfState").lookupOrDefault("rhoMin",1e-3)),
	rhoMax_(dict.subDict("equationOfState").lookupOrDefault("rhoMax",1500)),
	aSave(0.0),
	daSave(0.0),
	d2aSave(0.0),
	TSave(0.0),
	// Starting GUESS for the density by ideal gas law
	rhostd_(this->rho(this->Pstd(), this->Tstd(), this->Pstd()/(this->Tstd()*this->R())))
{
	is.check("soaveRedlichKwong::soaveRedlichKwong(Istream& is)");
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::soaveRedlichKwong::write(Ostream& os) const
{
	specie::write(os);

	dictionary dict("equationOfState");
	dict.add("pCritical", pcrit_);
	dict.add("TCritical", Tcrit_);
	dict.add("azentricFactor", azentricFactor_);
	dict.add("rhoMin", rhoMin_);
	dict.add("rhoMax", rhoMax_);

	os  << indent << dict.dictName() << dict;
}
*/


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const soaveRedlichKwong& srk)
{
	os << static_cast<const specie&>(srk) << token::SPACE
		<< srk.pcrit_ << tab << srk.Tcrit_ << tab << srk.azentricFactor_;

	os.check("Ostream& operator<<(Ostream& os, const soaveRedlichKwong& st)");
	return os;
}


// ************************************************************************* //