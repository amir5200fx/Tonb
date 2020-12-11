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
	const std::shared_ptr<Marine_Body>& theBody,
	const Marine_MultLevWaterDomain & theWaters,
	const Standard_Real x0, 
	const gp_Ax1 & theK, 
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	if (theBody->IsHull())
	{
		auto body = std::dynamic_pointer_cast<marineLib::Body_Displacer>(theBody);
		if (NOT body)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "the body type is not displacer" << endl
				<< abort(FatalError);
		}

		auto curves = CrossCurve(*body, theWaters, x0, theK, theInfo);
		return std::move(curves);
	}
	else if (theBody->IsTank())
	{
		auto body = std::dynamic_pointer_cast<marineLib::Body_Tank>(theBody);
		Debug_Null_Pointer(body);

		auto curves = CrossCurve(*body, theWaters, x0, theK, theInfo);
		return std::move(curves);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid body type has been detected: Sail" << endl
			<< abort(FatalError);
		return xSectParList();
	}
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