#include <HydDyna_Holtrop_Veriables.hxx>

Standard_Real 
tnbLib::holtropLib::HoltropCoeffs::CalcWaveResistance
(
	const Standard_Real theVel, 
	const Standard_Real theGravity, 
	const Standard_Real theDensity,
	const Standard_Real theL,
	const Standard_Real theDispv
)
{
	const Standard_Real d = -0.9;
	const auto fn = theVel / std::sqrt(theGravity * theL);

	auto rw=c1*c2*c5*
		theDispv*theDensity*theGravity*
		std::exp(m1 * std::pow(fn, d) + m2 * std::exp(-0.1 * std::pow(fn, -2.0)) * std::cos(landa * std::pow(fn, -2.0)));
	return rw;
}

void tnbLib::holtropLib::HoltropCoeffs::CalcCoefficients
(
	const ShipPrincipals& theShip,
	const Standard_Real theCSTEM, 
	const Standard_Real theLR
)
{
	iE =
		1.0 +
		89.0 * std::exp(
			-std::pow(theShip.L() / theShip.B(), 0.80856) *
			std::pow(1.0 - theShip.CWP(), 0.30484) *
			std::pow(1.0 - theShip.CP() - 0.0225 * theShip.LCB(), 0.6367) *
			std::pow(theLR / theShip.B(), 0.34574) *
			std::pow(100.0 * theShip.DISPV() / (std::pow(theShip.L(), 3.0)), 0.16302));

	Standard_Real BperL = theShip.B() / theShip.L();
	Standard_Real TperL;

	TperL = theShip.T() / theShip.L();

	if (TperL > 0.05)
		c12 = std::pow(TperL, 0.2228446);
	else if (TperL < 0.02)
		c12 = 0.479948;
	else
		c12 = 48.2 * std::pow(TperL - 0.02, 2.078) + 0.479948;

	c13 = 1.0 + 0.003 * theCSTEM;
	c14 = 1.0 + 0.011 * theCSTEM;

	if (BperL < 0.11)
		c7 = 0.229577 * std::pow(BperL, 0.33333);
	else if (BperL > 0.25)
		c7 = 0.5 - 0.0625 * BperL;
	else
		c7 = BperL;

	double TFperL = theShip.TF() / theShip.L();

	if (TFperL <= 0.04)
		c4 = TFperL;
	else
		c4 = 0.04;

	c5 = 1.0 - 0.8 * theShip.AT() / (theShip.B() * theShip.T() * theShip.CM());

	c3 = 0.56 * std::pow(theShip.ABT(), 1.5) / (theShip.B() * theShip.T() *
		(0.31 * std::sqrt(theShip.ABT()) + theShip.TF() - theShip.HB()));

	c2 = std::exp(-1.89 * std::sqrt(c3));

	c1 = 2223105.0 * std::pow(c7, 3.78613) * std::pow(theShip.T() / theShip.B(), 1.07961) * std::pow(90.0 - iE, -1.37565);

	double LperB = theShip.L() / theShip.B();

	if (LperB < 12.0)
		landa = 1.446 * theShip.CP() - 0.03 * LperB;
	else
		landa = 1.446 * theShip.CP() - 0.36;

	double L3perDispv = std::pow(theShip.L(), 3.0) / theShip.DISPV();

	if (L3perDispv < 512)
		c15 = -1.69385;
	else if (L3perDispv > 1727)
		c15 = 0;
	else
		c15 = -1.69385 + (theShip.L() / std::pow(theShip.DISPV(), 1.0 / 3.0) - 8.0) / 2.36;

	if (theShip.CP() < 0.8)
		c16 = 8.07981 * theShip.CP() - 13.8673 * theShip.CP() * theShip.CP() + 6.984388 * theShip.CP() * theShip.CP() * theShip.CP();
	else
		c16 = 1.73014 - 0.7067 * theShip.CP();

	m1 = 0.0140407 * theShip.L() / theShip.T() -
		1.75254 * std::pow(theShip.DISPV(), 1.0 / 3.0) / theShip.L() -
		4.79323 * BperL -
		c16;

	m2 = c15 * theShip.CP() * theShip.CP();

	S = theShip.L() *
		(2 * theShip.T() + theShip.B()) *
		std::sqrt(theShip.CM()) *
		(0.453 +
			0.4425 * theShip.CB() -
			0.2862 * theShip.CM() -
			0.003467 * theShip.B() / theShip.T() +
			0.3696 * theShip.CWP()) +
		2.38 * theShip.ABT() / theShip.CB();

	CA =
		0.006 * std::pow(theShip.L() + 100.0, -0.16) -
		0.00205 +
		0.003 * std::sqrt(theShip.L() / 7.5) * std::pow(theShip.CB(), 4.0) * c2 * (0.04 - c4);

	/*_1plusK1_ =
	0.93 +
	0.487118*c14_*std::pow(theShip.B_ / theShip.T_, 1.06806)*std::pow(theShip.T_ / theShip.T_, 0.46106)*
	std::pow(theShip.L() / theShip.LR_, 0.121563)*
	std::pow(std::pow(theShip.L(), 3.0) / theShip.DISPV_, 0.36486)*
	std::pow((1.0 - theShip.CP()), -0.604247);*/

	_1plusK1 =
		c13 * (0.93 + c12 * std::pow(theShip.B() / theLR, 0.92497) *
			std::pow(0.95 - theShip.CP(), -0.521448) * std::pow(1.0 - theShip.CP() + 0.0225 * theShip.LCB(), 0.6906));
}

void tnbLib::holtropLib::Froudes::CalcVariables
(
	const ShipPrincipals& theShip,
	const Standard_Real theVel, 
	const Standard_Real theGravity
)
{
	Fni = theVel / std::sqrt(
		theGravity * (theShip.TF() - theShip.HB() - 0.25 * std::sqrt(theShip.ABT())) + 0.15 * theVel * theVel);

	FnT = theVel / std::sqrt(
		2.0 * theGravity * theShip.AT() / (theShip.B() + theShip.B() * theShip.CWP()));
}