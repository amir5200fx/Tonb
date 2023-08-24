#include <VoyageMesh_BaseSize.hxx>

#include <VoyageMesh_BaseSizeInfo.hxx>
#include <Geo2d_2ndNurbsPx_3Pts.hxx>
#include <Geo_Tools.hxx>
#include <Geo_ProfileFun_Geom.hxx>
#include <Geo_ProfileFun_Linear.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <TColgp_Array1OfPnt2d.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <StdFail_NotDone.hxx>

Standard_Real 
tnbLib::VoyageMesh_BaseSize::RetrieveHmax
(
	const Standard_Integer id,
	const std::vector<Standard_Real>& theHs
) const
{
	Debug_Null_Pointer(GetInfo());
	return GetInfo()->MaxDeviation() * theHs.at(id);
}

Standard_Real 
tnbLib::VoyageMesh_BaseSize::RetrieveH0
(
	const Standard_Integer id,
	const std::vector<Standard_Real>& theHs
) const
{
	if (NOT id) return 0.;
	else
	{
		return GetInfo()->MaxDeviation() * theHs.at(id - 1);
	}
}

Standard_Real 
tnbLib::VoyageMesh_BaseSize::RetrieveH1
(
	const Standard_Integer id, 
	const std::vector<Standard_Real>& theHs
) const
{
	if (id IS_EQUAL theHs.size()) return 0.0;
	else
	{
		return GetInfo()->MaxDeviation() * theHs.at(id);
	}
}

std::shared_ptr<tnbLib::Geo_ProfileFun> 
tnbLib::VoyageMesh_BaseSize::CalcProfile
(
	const Standard_Real theH0, 
	const Standard_Real theH1, 
	const Standard_Real theHm
) const
{
	const auto start_transPoint = TRANS_POINT_CONST;
	const auto end_transPoint = 1.0 - TRANS_POINT_CONST;
	if (theHm < theH0 AND theH1)
	{
		auto profile = 
			std::make_shared<geoLib::ProfileFun_Linear>
			(theH0, theH1, 0., 1.0);
		return std::move(profile);
	}
	else if (theHm <= theH0)
	{
		auto profile =
			std::make_shared<geoLib::ProfileFun_Linear>
			(theH0, theH1, 0., 1.0);
		return std::move(profile);
	}
	else if (theHm <= theH1)
	{
		auto profile =
			std::make_shared<geoLib::ProfileFun_Linear>
			(theH0, theH1, 0., 1.0);
		return std::move(profile);
	}
	else
	{
		Standard_Real x0 = 0.0;
		Standard_Real h0 = theH0;

		Standard_Real x1 = start_transPoint;
		Standard_Real h1 = theHm;

		Standard_Real x2 = end_transPoint;
		Standard_Real h2 = theHm;

		Standard_Real x3 = 1.0;
		Standard_Real h3 = 1.0;

		const auto angle = GetInfo()->Angle();

		static const Standard_Integer nbPoles = 7;
		TColgp_Array1OfPnt2d pnts(1, nbPoles);
		pnts.SetValue(1, { x0,h0 });
		pnts.SetValue(2, { Geo_Tools::LinearInterpolate(x1,x0,angle),h1 });
		pnts.SetValue(3, { x1,h1 });
		pnts.SetValue(4, { MEAN(x1,x2),h1 });
		pnts.SetValue(5, { x2,h2 });
		pnts.SetValue(6, { Geo_Tools::LinearInterpolate(x2,x3,angle),h2 });
		pnts.SetValue(7, { x3,h3 });

		TColStd_Array1OfReal weights(1, nbPoles);
		weights.SetValue(1, 1.0);
		weights.SetValue(2, GetInfo()->GrowthRate());
		weights.SetValue(3, 1.0);
		weights.SetValue(4, 1.0);
		weights.SetValue(5, 1.0);
		weights.SetValue(6, GetInfo()->GrowthRate());
		weights.SetValue(7, 1.0);

		TColStd_Array1OfReal knots(1, 4);
		knots.SetValue(1, 0.0);
		knots.SetValue(2, 1.0 / 3.0);
		knots.SetValue(3, 2.0 / 3.0);
		knots.SetValue(4, 1.0);

		TColStd_Array1OfInteger mults(1, 4);
		mults.SetValue(1, 3);
		mults.SetValue(2, 2);
		mults.SetValue(3, 2);
		mults.SetValue(4, 3);

		try
		{
			auto profile =
				std::make_shared<geoLib::ProfileFun_Geom>
				(
					new Geom2d_BSplineCurve(pnts, weights, knots, mults, 2), 0, 1.0
				);
			return std::move(profile);
		}
		catch (const StdFail_NotDone& x)
		{
			FatalErrorIn(FunctionSIG)
				<< x.GetMessageString() << endl
				<< abort(FatalError);
		}
	}
}