#include <AirfoilPx.hxx>

#include <AirfoilPx_PxCamberProfile.hxx>
#include <AirfoilPx_PxThickProfile.hxx>
#include <Airfoil_Tools.hxx>
#include <Pln_CurveTools.hxx>
#include <Pln_Curve.hxx>
#include <Geo_xDistb.hxx>
#include <Entity2d_Polygon.hxx>
#include <NumAlg_BisectionSolver.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	class BisectLeadEdgeRadiusObjFun
		: public NumAlg_Bisection_Function
	{

		/*Private Data*/

		std::shared_ptr<Pln_Curve> theCurve_;

		Standard_Real theRadius_;

		Pnt2d theOrigin_;


		void SetOrigin();

	public:

		// default constructor [4/27/2023 Payvand]

		// constructors [4/27/2023 Payvand]

		BisectLeadEdgeRadiusObjFun(const std::shared_ptr<Pln_Curve>& theCurve, const Standard_Real theRadius)
			: theCurve_(theCurve)
			, theRadius_(theRadius)
		{
			SetOrigin();
		}

		// Public functions and operators [4/27/2023 Payvand]

		const auto& Origin() const { return theOrigin_; }
		const auto& Curve() const { return theCurve_; }
		auto Radius() const { return theRadius_; }

		Standard_Real Value(const Standard_Real) const override;

		void SetRadius(const Standard_Real theRadius) { theRadius_ = theRadius; }

	};
}

void tnbLib::BisectLeadEdgeRadiusObjFun::SetOrigin()
{
	theOrigin_ = Curve()->FirstCoord();
}

Standard_Real 
tnbLib::BisectLeadEdgeRadiusObjFun::Value(const Standard_Real x) const
{
	const auto pt = Curve()->Value(x);
	//const auto d = pt.Distance(Origin());
	return pt.Distance(Origin()) - Radius();
}

void tnbLib::AirfoilPx::SmoothLeading(const Standard_Real theRadius)
{
	NumAlg_BisectionSolver_Info bisectInfo;
	const auto& c0 = CamberProfile()->Curves().at(0);
	BisectLeadEdgeRadiusObjFun bisectObj(c0, LeadRadius());
	NumAlg_BisectionSolver<BisectLeadEdgeRadiusObjFun> alg(bisectObj, bisectInfo);

	alg.Perform(0.001, 0.5);
	auto xm = bisectInfo.Result();

	auto pm = c0->Value(xm);
}

void tnbLib::AirfoilPx::Perform()
{
	if (NOT CamberProfile())
	{
		FatalErrorIn(FunctionSIG)
			<< " No camber profile has been found." << endl
			<< abort(FatalError);
	}
	if (NOT ThickProfile())
	{
		FatalErrorIn(FunctionSIG)
			<< " No thickness profile has been found." << endl
			<< abort(FatalError);
	}
	if (NOT Xs())
	{
		FatalErrorIn(FunctionSIG)
			<< " No distribution has been found." << endl
			<< abort(FatalError);
	}
	const auto chordLen = Xs()->Upper() - Xs()->Lower();
	CamberProfile()->SetChordLen(chordLen);
	ThickProfile()->SetChordLen(chordLen);

	CamberProfile()->Perform();
	ThickProfile()->Perform();

	auto poly1 = Pln_Curve::Discretize(*CamberProfile()->Curves().at(0), 100);
	auto poly2 = Pln_Curve::Discretize(*ThickProfile()->Curves().at(0), 100);

	OFstream myFile("curves.plt");
	poly1->ExportToPlt(myFile);
	poly2->ExportToPlt(myFile);

	const auto [xc, yc, tc] = 
		Airfoil_Tools::CalcCamberPoints
		(
			*Xs(), 
			CamberProfile()->Curves(), 
			CamberProfile()->Spans()
		);
	const auto yt = 
		Airfoil_Tools::CalcThicknessPoints
		(
			*Xs(), 
			ThickProfile()->Curves(), 
			ThickProfile()->Spans()
		);

	auto uYt = yt;
	for (auto& x : uYt)
		x *= 0.5;
	auto lYt = uYt;

	const auto uPts = Airfoil_Tools::CalcUpperOffsets(xc, yc, uYt, tc);
	const auto lPts = Airfoil_Tools::CalcLowerOffsets(xc, yc, lYt, tc);
	
	auto c0 = Pln_CurveTools::Interpolation(uPts);
	auto c1 = Pln_CurveTools::Interpolation(lPts);

	theUpperSurface_ = std::make_shared<Pln_Curve>(0, "upper profile", std::move(c0));
	theLowerSurface_ = std::make_shared<Pln_Curve>(1, "lower profile", std::move(c1));

	Change_IsDone() = Standard_True;
}