#include <ISC08_CmptLib.hxx>

#include <ISC08_Table.hxx>
#include <ISC08_Tools.hxx>

tnbLib::isc08Lib::Phi 
tnbLib::ISC08_CmptLib::CalcAngleOfRoll
(
	const marineLib::B & B,
	const marineLib::TM & d,
	const marineLib::CB & CB,
	const marineLib::LWL & lwl, 
	const marineLib::KG & KG, 
	const isc08Lib::Ak & Ak,
	const isc08Lib::T & T,
	const isc08Lib::BilgeBarCondition cond
)
{
	static const Standard_Real c0 = 0.73;
	static const Standard_Real c1 = 0.6;

	/*X1 = factor as shown in table 2.3.4-1*/
	const auto X1 = ISC08_Tools::Table(B() / d(), isc08Lib::table2341);

	/*X2 = factor as shown in table 2.3.4-2*/
	const auto X2 = ISC08_Tools::Table(CB(), isc08Lib::table2342);

	const auto k = ISC08_Tools::Factor(Ak()*100.0 / (lwl()*B()), cond);

	const auto OG = KG() - d();
	const auto r = c0 + c1 * OG / d();

	const auto s = ISC08_Tools::Table(T(), isc08Lib::table2344);

	const auto t = isc08Lib::Phi(109.0*k*X1*X2*sqrt(r*s));
	return std::move(t);
}

tnbLib::isc08Lib::Lw 
tnbLib::ISC08_CmptLib::CalcWindHeelingLever
(
	const isc08Lib::P & theP,
	const isc08Lib::A & theArea,
	const isc08Lib::Z & theZ, 
	const isc08Lib::g & theG, 
	const marineLib::DISPM & theDispm
)
{
	const auto t = isc08Lib::Lw(theP()*theArea()*theZ() / (1000.0*theG()*theDispm()));
	return std::move(t);
}

tnbLib::isc08Lib::Lw 
tnbLib::ISC08_CmptLib::CalcGustWind
(
	const isc08Lib::Lw & theLw
)
{
	const auto t = isc08Lib::Lw(1.5*theLw());
	return std::move(t);
}

tnbLib::isc08Lib::T 
tnbLib::ISC08_CmptLib::CalcRollingPeriod
(
	const marineLib::B & B, 
	const marineLib::TM & d, 
	const marineLib::LWL & lwl, 
	const marineLib::GM & gm
)
{
	static const Standard_Real c0 = 0.373;
	static const Standard_Real c1 = 0.023;
	static const Standard_Real c2 = 0.043;
	static const Standard_Real c3 = 100.0;

	const auto C = c0 + c1 * (B() / d()) - c2 * (lwl() / c3);
	const auto T = (2.0*C*B()) / sqrt(gm());
	
	const auto t = isc08Lib::T(T);
	return std::move(t);
}