#include <HydStatic_CmptLib.hxx>

#include <Marine_Body.hxx>
#include <Marine_CmpSection.hxx>
#include <MarineBase_Tools.hxx>
#include <HydStatic_Bonjean.hxx>
#include <HydStatic_BnjCurve.hxx>
#include <error.hxx>
#include <OSstream.hxx>

Standard_Real 
tnbLib::HydStatic_CmptLib::Draft
(
	const Standard_Real x, 
	const Standard_Real theTa, 
	const Standard_Real xTa, 
	const Standard_Real theTf, 
	const Standard_Real xTf
)
{
	if (xTf <= xTa)
	{
		FatalErrorIn("Standard_Real Draft(Args...)")
			<< "Invalid data: " << endl
			<< " xTA = " << xTa << endl
			<< " xTF = " << xTf << endl
			<< abort(FatalError);
	}

	const auto m = (theTf - theTa) / (xTf - xTa);
	const auto d = m * (x - xTa) + theTa;
	return d;
}

Standard_Real 
tnbLib::HydStatic_CmptLib::Draft
(
	const Marine_CmpSection & theSect, 
	const Standard_Real theTa,
	const Standard_Real xTa, 
	const Standard_Real theTf, 
	const Standard_Real xTf
)
{
	const auto x = theSect.X();
	return Draft(x, theTa, xTa, theTf, xTf);
}

std::vector<Standard_Real> 
tnbLib::HydStatic_CmptLib::RetrieveDrafts
(
	const Marine_Body & theBody,
	const Standard_Real theTa,
	const Standard_Real xTa, 
	const Standard_Real theTf,
	const Standard_Real xTf
)
{
	std::vector<Standard_Real> drafts;
	drafts.reserve(theBody.NbSections());

	for (const auto& x : theBody.Sections())
	{
		Debug_Null_Pointer(x);

		auto d = Draft(*x, theTa, xTa, theTf, xTf);
		drafts.push_back(d);
	}
	return std::move(drafts);
}

std::vector<Standard_Real> 
tnbLib::HydStatic_CmptLib::RetrieveXs
(
	const Marine_Body & theBody
)
{
	std::vector<Standard_Real> X;
	X.reserve(theBody.NbSections());

	for (const auto& x : theBody.Sections())
	{
		Debug_Null_Pointer(x);

		X.push_back(x->X());
	}
	return std::move(X);
}

std::vector<tnbLib::marineLib::xSectionParam> 
tnbLib::HydStatic_CmptLib::RetrieveAreas
(
	const HydStatic_Bonjean & theBonjean,
	const Standard_Real theTa, 
	const Standard_Real xTa, 
	const Standard_Real theTf, 
	const Standard_Real xTf
)
{
	if (NOT theBonjean.IsDone())
	{
		FatalErrorIn("std::vector<marineLib::xSectionParam> RetrieveAreas(Args...)")
			<< "the Bonjean curves is not performed!" << endl
			<< abort(FatalError);
	}

	Debug_Null_Pointer(theBonjean.Body());
	const auto& body = *theBonjean.Body();

	const auto bnjCurves = HydStatic_CmptLib::RetrieveBnjCurves(theBonjean);

	const auto Ts = HydStatic_CmptLib::RetrieveDrafts(body, theTa, xTa, theTf, xTf);
	auto As = HydStatic_CmptLib::RetrieveAreas(bnjCurves, Ts);

	return std::move(As);
}