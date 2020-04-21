#include <ISC08_GustWind.hxx>

#include <HydStatic_CmptLib.hxx>
#include <ISC08_CmptLib.hxx>
#include <error.hxx>
#include <OSstream.hxx>

tnbLib::ISC08_GustWind::ISC08_GustWind()
	: thePhi0_(isc08Lib::Phi::null)
	, thePhi1_(isc08Lib::Phi::null)
	, thePhi2_(isc08Lib::Phi::null)
	, theLw2_(isc08Lib::Lw::null)
{
}

tnbLib::ISC08_GustWind::ISC08_GustWind
(
	const std::shared_ptr<HydStatic_DynStbGraph>& theStability,
	const isc08Lib::Phi& thePhi0,
	const isc08Lib::Phi& thePhi1,
	const isc08Lib::Lw& theLw2
)
	: theStability_(theStability)
	, thePhi0_(thePhi0)
	, thePhi1_(thePhi1)
	, theLw2_(theLw2)
	, thePhi2_(isc08Lib::Phi::null)
{
}

void tnbLib::ISC08_GustWind::Perform()
{
	if (NOT Stability())
	{
		FatalErrorIn("void tnbLib::ISC08_GustWind::Perform()")
			<< "no stability curve is loaded!" << endl
			<< abort(FatalError);
	}

	if (Phi0().IsNull())
	{
		FatalErrorIn("void tnbLib::ISC08_GustWind::Perform()")
			<< "no phi0 angle is assigned!" << endl
			<< abort(FatalError);
	}

	if (Phi1().IsNull())
	{
		FatalErrorIn("void tnbLib::ISC08_GustWind::Perform()")
			<< "no phi1 angle is assigned!" << endl
			<< abort(FatalError);
	}


}