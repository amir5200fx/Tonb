#include <Cad_CurveLength.hxx>

#include <Cad_Tools.hxx>
#include <Geo_CurveLength.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom_Curve.hxx>

#include <Pnt3d.hxx>
#include <Dir3d.hxx>

const std::shared_ptr<tnbLib::NumAlg_AdaptiveInteg_Info> tnbLib::Cad_CurveLength::DEFAULT_INFO =
std::make_shared<tnbLib::NumAlg_AdaptiveInteg_Info>();

Standard_Real tnbLib::Cad_CurveLength::Result() const
{
	if (NOT IsDone())
	{
		FatalErrorIn(FunctionSIG)
			<< "the application has not been performed, yet!" << endl
			<< abort(FatalError);
	}
	return theLength_;
}

namespace tnbLib
{

	class CadCurveLengthRunTimeInfo
	{

		/*Private Data*/

	public:

		// default constructor [1/16/2022 Amir]

		CadCurveLengthRunTimeInfo()
		{
			SetInfo();
		}

		static void SetInfo();
	};
}

static const tnbLib::CadCurveLengthRunTimeInfo myCadCurveLengthRunTimeInfoObj;

void tnbLib::CadCurveLengthRunTimeInfo::SetInfo()
{
	const auto& myInfo = Cad_CurveLength::DEFAULT_INFO;
	myInfo->SetTolerance(1.0E-6);
	myInfo->SetMaxNbIterations(200);
	myInfo->SetNbInitIterations(8);
}

void tnbLib::Cad_CurveLength::Perform()
{
	if (NOT Geometry())
	{
		FatalErrorIn(FunctionSIG)
			<< "no geometry has been loaded, yet!" << endl
			<< abort(FatalError);
	}

	const auto lower = Geometry()->FirstParameter();
	const auto upper = Geometry()->LastParameter();

	Perform(lower, upper);
}

void tnbLib::Cad_CurveLength::Perform
(
	const Standard_Real theLower, 
	const Standard_Real theUpper
)
{
	if (NOT Geometry())
	{
		FatalErrorIn(FunctionSIG)
			<< "no geometry has been loaded, yet!" << endl
			<< abort(FatalError);
	}

	if (NOT IntegInfo())
	{
		FatalErrorIn(FunctionSIG)
			<< "no integ info has been found!" << endl
			<< abort(FatalError);
	}

	if (NOT Cad_Tools::IsBounded(Geometry()))
	{
		FatalErrorIn(FunctionSIG)
			<< "the curve is not bounded!" << endl
			<< abort(FatalError);
	}

	const auto lower = Geometry()->FirstParameter();
	const auto upper = Geometry()->LastParameter();

	if (NOT INSIDE(theLower, lower, upper))
	{
		FatalErrorIn(FunctionSIG)
			<< "the lower parameter exceeds the knot vector." << endl
			<< " - x: " << theLower << endl
			<< " - lower: " << lower << endl
			<< " - upper: " << upper << endl
			<< abort(FatalError);
	}

	if (NOT INSIDE(theUpper, lower, upper))
	{
		FatalErrorIn(FunctionSIG)
			<< "the upper parameter exceeds the knot vector." << endl
			<< " - x: " << theUpper << endl
			<< " - lower: " << lower << endl
			<< " - upper: " << upper << endl
			<< abort(FatalError);
	}

	const auto myIntegrand = std::make_shared<Geo_CurveIntegrand<Handle(Geom_Curve)>>(Geometry());
	Debug_Null_Pointer(myIntegrand);

	auto& integInfo = *IntegInfo();
	theLength_ = geoLib::CalcCurveLength<Handle(Geom_Curve)>::_(*myIntegrand, theLower, theUpper, integInfo);

	Change_IsDone() = Standard_True;
}