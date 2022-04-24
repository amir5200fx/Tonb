#include <Cad_SingularCurve.hxx>

#include <Cad_ApprxCurveOnSurface.hxx>
#include <Pln_Tools.hxx>
#include <Geo_ApprxCurve_Info.hxx>
#include <Merge3d_Pnt.hxx>
#include <Entity2d_Polygon.hxx>
#include <Entity3d_Box.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2d_Curve.hxx>
#include <Geom_Surface.hxx>
#include <TColgp_HArray1OfPnt.hxx>
#include <GeomAPI_Interpolate.hxx>

std::shared_ptr<tnbLib::Geo_ApprxCurve_Info> tnbLib::Cad_SingularCurveBase::ApproxInfo =
std::make_shared<tnbLib::Geo_ApprxCurve_Info>();

namespace tnbLib
{

	class SingularCurveApproxInfoRunTime
	{

		/*Private Data*/

	public:

		// default constructor [4/18/2022 Amir]

		SingularCurveApproxInfoRunTime()
		{
			SetInfo();
		}

		static void SetInfo();
	};
}

static tnbLib::SingularCurveApproxInfoRunTime mySingularCurveApproxInfoRunTime;

void tnbLib::SingularCurveApproxInfoRunTime::SetInfo()
{
	const auto& myInfo = Cad_SingularCurveBase::ApproxInfo;
	myInfo->SetAngle(5.0);
	myInfo->SetApprox(0.0025);
	myInfo->SetInitNbSubdivision(2);
	myInfo->SetMaxNbSubdivision(6);
	myInfo->SetMinSize(1.0e-5);
}

namespace tnbLib
{
	namespace meshLib
	{

		namespace singularLib
		{

			static std::vector<Pnt3d> CalcOffsets(const std::vector<Pnt2d>& pts, const Geom_Surface& theSurf)
			{
#ifdef CHECK_BOUNDED_SURFACE
				Standard_Real u0, u1, v0, v1;
				theSurf.Bounds(u0, u1, v0, v1);
				Entity2d_Box b(Pnt2d(u0, v0), Pnt2d(u1, v1));
#endif // CHECK_BOUNDED_SURFACE
				std::vector<Pnt3d> qs;
				qs.reserve(pts.size());
				for (const auto& x : pts)
				{
#ifdef CHECK_BOUNDED_SURFACE
					if (NOT b.IsInside(p))
					{
						FatalErrorIn(FunctionSIG)
							<< "the point is outside of the domain!" << endl
							<< abort(FatalError);
				}
#endif // CHECK_BOUNDED_SURFACE
					auto p = theSurf.Value(x.X(), x.Y());
					qs.push_back(std::move(p));
				}
				return std::move(qs);
			}

			static Handle(Geom_Curve) Interpolate(const std::vector<Pnt3d>& pts, const Standard_Real tol)
			{
				Handle(TColgp_HArray1OfPnt) Offsets = new TColgp_HArray1OfPnt(1, pts.size() + 1);
				Standard_Integer id = 0;
				for (const auto& x : pts)
				{
					Offsets->SetValue(++id, x);
				}
				try
				{
					GeomAPI_Interpolate Interpol(Offsets, Standard_False, tol);
					Interpol.Perform();
					if (NOT Interpol.IsDone())
					{
						FatalErrorIn(FunctionSIG)
							<< "unable to interpolate the offsets!" << endl
							<< abort(FatalError);
					}
					return Interpol.Curve();
				}
				catch (const Standard_Failure& x)
				{
					FatalErrorIn(FunctionSIG)
						<< x.GetMessageString() << endl
						<< " - nb. of points: " << pts.size() << endl
						<< abort(FatalError);
					return nullptr;
				}
			}

			static std::vector<Pnt3d> Merge(const std::vector<Pnt3d>& thePts, const Standard_Real tol)
			{
				if (thePts.size() < 2)
				{
					FatalErrorIn(FunctionSIG)
						<< "invalid nb. of pts has been detected!" << endl
						<< abort(FatalError);
				}
				std::vector<Pnt3d> pts;
				pts.reserve(thePts.size());
				auto iter = thePts.begin();
				pts.push_back(*iter);
				iter++;
				while (iter NOT_EQUAL thePts.end())
				{
					if ((*iter).Distance(LastItem(pts)) <= tol)
					{
						continue;
					}
					pts.push_back(*iter);
					iter++;
				}
				return std::move(pts);
			}
		}
	}
}

Handle(Geom_Curve) 
tnbLib::Cad_SingularCurveBase::CalcCurve3d
(
	const Handle(Geom2d_Curve)& para, 
	const Handle(Geom_Surface)& theSurf, 
	const std::shared_ptr<Geo_ApprxCurve_Info>& theInfo
)
{
	Debug_Null_Pointer(para);
	Debug_Null_Pointer(theSurf);
	Debug_Null_Pointer(theInfo);

	if (NOT Pln_Tools::IsBounded(para))
	{
		FatalErrorIn(FunctionSIG)
			<< "the para curve is not bounded!" << endl
			<< abort(FatalError);
	}

	static const Standard_Integer nbPts = 50;
	std::vector<Pnt2d> ppts;
	ppts.reserve(nbPts);
	auto du = (para->LastParameter() - para->FirstParameter()) / (Standard_Real)nbPts;
	for (Standard_Integer i = 0; i <= nbPts; i++)
	{
		auto u = para->FirstParameter() + i * du;
		if (u < para->FirstParameter()) u = para->FirstParameter();
		if (u > para->LastParameter()) u = para->LastParameter();
		auto p = para->Value(u);
		ppts.push_back(std::move(p));
	}

	/*auto alg = std::make_shared<Cad_ApprxCurveOnSurface>();
	Debug_Null_Pointer(alg);

	alg->SetParaCurve(para, para->FirstParameter(), para->LastParameter());
	alg->SetSurface(theSurf);
	alg->SetApproxInfo(theInfo);

	alg->Perform();
	Debug_If_Condition_Message(NOT alg->IsDone(), "the application is not performed!");

	const auto& poly = alg->Approx();
	Debug_Null_Pointer(poly);*/

	auto pts = meshLib::singularLib::CalcOffsets(ppts, *theSurf);
	auto b = Entity3d_Box::BoundingBoxOf(pts);
	auto tol = b.Diameter()*1.0E-6;
	auto merged = meshLib::singularLib::Merge(pts, tol);

	auto c = meshLib::singularLib::Interpolate(pts, tol);
	return std::move(c);
}