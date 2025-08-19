#include <Cad_ModifySingularPlaneTools.hxx>

#include <Aft2d_gPlnCurveSurface.hxx>
#include <Aft2d_gRegionPlaneSurface.hxx>
#include <Aft2d_gPlnWireSurface.hxx>
#include <Cad_gApprxPlnWireSurface.hxx>
#include <GModel_ParaCurve.hxx>
#include <TModel_ParaCurve.hxx>
#include <Geo_ApprxCurve_Info.hxx>
#include <Pln_Tools.hxx>
#include <Global_Precision.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
std::pair
<
	std::shared_ptr<tnbLib::Aft2d_gPlnCurveSurface>, 
	std::shared_ptr<tnbLib::Aft2d_gPlnCurveSurface>
>
tnbLib::Cad_ModifySingularPlaneTools<tnbLib::Aft2d_gRegionPlaneSurface>::Split
(
	const Standard_Real x, 
	const std::shared_ptr<Aft2d_gPlnCurveSurface>& theCurve
)
{
	Debug_Null_Pointer(theCurve);
	/*const auto& curve = theCurve->Curve();
	Debug_Null_Pointer(curve);

	auto[c0, c1] = GModel_ParaCurve::Split(x, curve);
	if (NOT c0)
	{
		FatalErrorIn(FunctionSIG)
			<< "the curve is null" << endl
			<< abort(FatalError);
	}
	if (NOT c1)
	{
		FatalErrorIn(FunctionSIG)
			<< "the curve is null" << endl
			<< abort(FatalError);
	}
	auto C0 = std::make_shared<Aft2d_gPlnCurveSurface>(std::move(c0));
	auto C1 = std::make_shared<Aft2d_gPlnCurveSurface>(std::move(c1));
	auto t = std::make_pair(std::move(C0), std::move(C1));
	return std::move(t);*/
	return theCurve->Split(x);
}

template<>
std::shared_ptr<tnbLib::Entity2d_Polygon> 
tnbLib::Cad_ModifySingularPlaneTools<tnbLib::Aft2d_gRegionPlaneSurface>::GetPolygon
(
	const std::shared_ptr<Aft2d_gPlnWireSurface>& theWire,
	const std::shared_ptr<Geo_ApprxCurve_Info>& theInfo
)
{
	Debug_Null_Pointer(theWire);
	Debug_Null_Pointer(theInfo);
	const auto& curves = theWire->Curves();
	
	auto alg = std::make_shared<Cad_gApprxPlnWireSurface>(theWire, theInfo);
	Debug_Null_Pointer(alg);

	alg->Perform();
	Debug_If_Condition_Message(NOT alg->IsDone(), "the application is not performed!");

	const auto& polygons = alg->Polygons();
	Pln_Tools::WatertightWire(polygons);

	return  Pln_Tools::MergeApproxWire(polygons, Precision::PConfusion());
}

#ifdef _DEBUG
#include <Cad_gSubdivideHorizon.hxx>
template<>
std::vector<std::shared_ptr<tnbLib::Aft2d_gPlnCurveSurface>> 
tnbLib::Cad_ModifySingularPlaneTools<tnbLib::Aft2d_gRegionPlaneSurface>::SubCurves
(
	const std::shared_ptr<Aft2d_gPlnCurveSurface>& theCurve, 
	const std::list<Standard_Real>& thePars,
	const Standard_Real theTol
)
{
#ifdef _DEBUG
	{
		auto x0 = thePars.front();
		for (auto x : thePars)
		{
			if (x < x0)
			{
				FatalErrorIn(FunctionSIG)
					<< "the list is not sorted!" << endl
					<< abort(FatalError);
			}
			x0 = x;
		}
	}
#endif // _DEBUG
	std::vector<std::shared_ptr<Aft2d_gPlnCurveSurface>> curves;
	auto curve = theCurve;
	for (auto x : thePars)
	{
		auto x0 = curve->FirstParameter();
		auto x1 = curve->LastParameter();

		if (x < x0) x = x0;
		if (x > x1) x = x1;

		if (std::abs(x - x0) <= theTol OR std::abs(x - x1) <= theTol)
		{
			continue;
		}
		auto[c0, c1] = Split(x, curve);

		curves.push_back(std::move(c0));
		curve = std::move(c1);
	}
	curves.push_back(std::move(curve));
	return std::move(curves);
}

template<>
std::vector<std::shared_ptr<tnbLib::Aft2d_gPlnWireSurface>>
tnbLib::Cad_ModifySingularPlaneTools<tnbLib::Aft2d_gRegionPlaneSurface>::ModifyWires
(
	const std::vector<std::shared_ptr<Aft2d_gPlnWireSurface>>& theWires,
	const std::map<std::shared_ptr<curveType>, std::shared_ptr<std::list<Standard_Real>>>& theSubMap,
	const Standard_Real theTol
)
{
	std::vector<std::shared_ptr<wireType>> mWires;
	for (const auto& wire : theWires)
	{
		Debug_Null_Pointer(wire);

		std::vector<std::shared_ptr<curveType>> curves;
		for (const auto& x : wire->Curves())
		{
			Debug_Null_Pointer(x);
			const auto iter = theSubMap.find(x);
			if (iter IS_EQUAL theSubMap.end())
			{
				FatalErrorIn(FunctionSIG)
					<< "the curve is not found!" << endl
					<< abort(FatalError);
			}

			Debug_Null_Pointer(iter->second);
			auto& l = *iter->second;

			if (l.empty())
			{
				curves.push_back(x);
			}
			else
			{
				if (l.size() > 2)
				{
					l.sort();
				}
				auto subCurves = SubCurves(x, l, theTol);
				for (auto& sub : subCurves)
				{
					Debug_Null_Pointer(sub);
					curves.push_back(std::move(sub));
				}
			}
		}

		auto newWire =
			std::make_shared<wireType>(wire->Index(), wire->Name(), std::move(curves));
		Debug_Null_Pointer(newWire);
		mWires.push_back(std::move(newWire));
	}
	return std::move(mWires);
}

template<>
std::list<std::shared_ptr<tnbLib::Cad_gSubdivideHorizon>> 
tnbLib::Cad_ModifySingularPlaneTools<tnbLib::Aft2d_gRegionPlaneSurface>::CalcParts
(
	const std::vector<std::shared_ptr<Cad_gSingularZone>>& theZones,
	const std::vector<std::shared_ptr<Aft2d_gPlnCurveSurface>>& theCurves
)
{
	std::list<std::shared_ptr<Cad_gSubdivideHorizon>> subsList;
	for (const auto& x : theZones)
	{
		Debug_Null_Pointer(x);
		const auto& zone = *x;

		for (Standard_Integer iz = 0; iz < zone.NbHorizons(); iz++)
		{
			const auto& horizon = zone.Horizon(iz);
			Debug_Null_Pointer(horizon);

			auto alg = std::make_shared<Cad_gSubdivideHorizon>(horizon);
			Debug_Null_Pointer(alg);

			alg->Perform(theCurves);
			Debug_If_Condition_Message(NOT alg->IsDone(), "the application is not performed!");
			subsList.push_back(std::move(alg));
		}
	}
	return std::move(subsList);
}

template<>
std::vector<std::shared_ptr<tnbLib::Aft2d_gPlnCurveSurface>>
tnbLib::Cad_ModifySingularPlaneTools<tnbLib::Aft2d_gRegionPlaneSurface>::ModifyHorizons
(
	const std::vector<std::shared_ptr<Aft2d_gPlnCurveSurface>>& theCurves, 
	const std::map<std::shared_ptr<Aft2d_gPlnCurveSurface>, std::shared_ptr<std::list<Standard_Real>>>& theSubMap,
	const Standard_Real theTol
)
{
	std::vector<std::shared_ptr<curveType>> curves;
	for (const auto& x : theCurves)
	{
		Debug_Null_Pointer(x);
		const auto iter = theSubMap.find(x);
		if (iter IS_EQUAL theSubMap.end())
		{
			FatalErrorIn(FunctionSIG)
				<< "the curve is not found!" << endl
				<< abort(FatalError);
		}

		Debug_Null_Pointer(iter->second);
		auto& l = *iter->second;

		if (l.empty())
		{
			curves.push_back(x);
		}
		else
		{
			if (l.size() > 2)
			{
				l.sort();
			}
			auto subCurves = SubCurves(x, l, theTol);
			if (subCurves.size())
			{
				for (auto& sub : subCurves)
				{
					Debug_Null_Pointer(sub);
					curves.push_back(std::move(sub));
				}
			}
			else
			{
				curves.push_back(x);
			}
		}
	}
	return std::move(curves);
}
#endif // _DEBUG
