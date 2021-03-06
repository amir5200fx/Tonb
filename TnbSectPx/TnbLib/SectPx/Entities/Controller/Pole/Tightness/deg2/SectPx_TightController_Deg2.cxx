#include <SectPx_TightController_Deg2.hxx>

#include <SectPx_SegmentController.hxx>
#include <SectPx_CPtsMap.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const short tnbLib::sectPxLib::TightController_Deg2::degree_(2);
const char* tnbLib::sectPxLib::TightController_Deg2::typeName_("degree2 tightness");


//- constructors

tnbLib::sectPxLib::TightController_Deg2::TightController_Deg2
(
	const std::shared_ptr<sectPxLib::Pole_Corner>& theCorner
)
	: SectPx_TightController(theCorner)
{
	// empty body
}

tnbLib::sectPxLib::TightController_Deg2::TightController_Deg2
(
	std::shared_ptr<sectPxLib::Pole_Corner>&& theCorner
)
	: SectPx_TightController(std::move(theCorner))
{
	// empty body
}

tnbLib::sectPxLib::TightController_Deg2::TightController_Deg2
(
	const Standard_Integer theIndex,
	const std::shared_ptr<sectPxLib::Pole_Corner>& theCorner
)
	: SectPx_TightController(theIndex, theCorner)
{
	// empty body
}

tnbLib::sectPxLib::TightController_Deg2::TightController_Deg2
(
	const Standard_Integer theIndex,
	std::shared_ptr<sectPxLib::Pole_Corner>&& theCorner
)
	: SectPx_TightController(theIndex, std::move(theCorner))
{
	// empty body
}

tnbLib::sectPxLib::TightController_Deg2::TightController_Deg2
(
	const Standard_Integer theIndex,
	const word & theName,
	const std::shared_ptr<sectPxLib::Pole_Corner>& theCorner
)
	: SectPx_TightController(theIndex, theName, theCorner)
{
	// empty body
}

tnbLib::sectPxLib::TightController_Deg2::TightController_Deg2
(
	const Standard_Integer theIndex,
	const word& theName,
	std::shared_ptr<sectPxLib::Pole_Corner>&& theCorner
)
	: SectPx_TightController(theIndex, theName, std::move(theCorner))
{
	// empty body
}

//- functions and operators

short 
tnbLib::sectPxLib::TightController_Deg2::Degree() const
{
	return degree_;
}

void tnbLib::sectPxLib::TightController_Deg2::SetLeft
(const std::shared_ptr<SectPx_SegmentController>& theController)
{
	Debug_Null_Pointer(theController);

	const auto& cpts = theController->CPts();
	Debug_Null_Pointer(cpts);

	if (cpts->NbPts() < 1)
	{
		FatalErrorIn(FunctionSIG)
			<< "not enough nb. of control points for this tightController!" << endl
			<< abort(FatalError);
	}

	SectPx_TightController::SetLeft(theController);
}

void tnbLib::sectPxLib::TightController_Deg2::SetRight
(
	const std::shared_ptr<SectPx_SegmentController>& theController
)
{
	Debug_Null_Pointer(theController);

	const auto& cpts = theController->CPts();
	Debug_Null_Pointer(cpts);

	if (cpts->NbPts() < 1)
	{
		FatalErrorIn(FunctionSIG)
			<< "not enough nb. of control points for this tightController!" << endl
			<< abort(FatalError);
	}

	SectPx_TightController::SetRight(theController);
}

tnbLib::word 
tnbLib::sectPxLib::TightController_Deg2::RegObjTypeName() const
{
	return typeName_;
}