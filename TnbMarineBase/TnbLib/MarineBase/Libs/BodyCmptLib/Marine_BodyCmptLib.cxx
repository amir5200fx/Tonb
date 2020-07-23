#include <Marine_BodyCmptLib.hxx>

#include <Marine_Bodies.hxx>
#include <Marine_BodyTools.hxx>
#include <Marine_CmptLib2.hxx>
#include <Marine_MultLevWaterDomain.hxx>

tnbLib::marineLib::xSectionParam 
tnbLib::Marine_BodyCmptLib::LeverArm
(
	const marineLib::Body_Displacer & theBody,
	const Standard_Real x0,
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
#ifdef _DEBUG
	Marine_BodyTools::CheckTypeConsistency(theBody);
#endif // _DEBUG

	auto xParams = Marine_CmptLib2::LeverArm(theBody.Sections(), x0, theInfo);
	return std::move(xParams);
}

tnbLib::marineLib::xSectionParam 
tnbLib::Marine_BodyCmptLib::LeverArm
(
	const marineLib::Body_Tank & theBody, 
	const Standard_Real x0,
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
#ifdef _DEBUG
	Marine_BodyTools::CheckTypeConsistency(theBody);
#endif // _DEBUG

	auto xParams = Marine_CmptLib2::LeverArm(theBody.Sections(), x0, theInfo);
	return std::move(xParams);
}

Standard_Real 
tnbLib::Marine_BodyCmptLib::LeverArm
(
	const marineLib::Body_Displacer & theBody, 
	const Standard_Real x0, 
	const Standard_Real theVolume,
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
#ifdef _DEBUG
	Marine_BodyTools::CheckTypeConsistency(theBody);
#endif // _DEBUG

	return Marine_CmptLib2::LeverArm(theBody.Sections(), x0, theVolume, theInfo);
}

Standard_Real 
tnbLib::Marine_BodyCmptLib::LeverArm
(
	const marineLib::Body_Tank & theBody,
	const Standard_Real x0, 
	const Standard_Real theVolume, 
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
#ifdef _DEBUG
	Marine_BodyTools::CheckTypeConsistency(theBody);
#endif // _DEBUG

	return Marine_CmptLib2::LeverArm(theBody.Sections(), x0, theVolume, theInfo);
}

tnbLib::xSectParList 
tnbLib::Marine_BodyCmptLib::CrossCurve
(
	const marineLib::Body_Displacer & theBody,
	const Marine_MultLevWaterDomain & theWaters,
	const Standard_Real x0,
	const gp_Ax1 & theK, 
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
#ifdef _DEBUG
	Marine_BodyTools::CheckTypeConsistency(theBody);
#endif // _DEBUG

	auto params = 
		Marine_CmptLib2::CrossCurve
		(
			theBody.Sections(), theWaters.Domains(), 
			x0, theK, theInfo
		);
	return std::move(params);
}

tnbLib::xSectParList 
tnbLib::Marine_BodyCmptLib::CrossCurve
(
	const marineLib::Body_Tank & theBody, 
	const Marine_MultLevWaterDomain & theWaters,
	const Standard_Real x0,
	const gp_Ax1 & theK,
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
#ifdef _DEBUG
	Marine_BodyTools::CheckTypeConsistency(theBody);
#endif // _DEBUG

	auto params =
		Marine_CmptLib2::CrossCurve
		(
			theBody.Sections(), theWaters.Domains(),
			x0, theK, theInfo
		);
	return std::move(params);
}