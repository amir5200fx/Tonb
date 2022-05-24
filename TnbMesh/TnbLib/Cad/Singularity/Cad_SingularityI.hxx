#pragma once
#ifndef _DEBUG
#include <Cad_SingularityHorizons.hxx>
#include <Cad_ColorApprxMetric.hxx>
#include <Cad_SingularityTools.hxx>
#include <GeoMesh2d_Data.hxx>
#include <Geo_BoxTools.hxx>
#include <Geo2d_PolygonGraph.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
#endif // !_DEBUG

#ifndef _DEBUG
template<class SurfType>
inline void tnbLib::Cad_Singularity<SurfType>::Perform()
{
	if (NOT SizeFun())
	{
		FatalErrorIn(FunctionSIG)
			<< "no size fun has been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT ParaPlane())
	{
		FatalErrorIn(FunctionSIG)
			<< "no plane has been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Horizons())
	{
		FatalErrorIn(FunctionSIG)
			<< "no Horizon analysis has been found" << endl
			<< abort(FatalError);
	}

	if (NOT Horizons()->MetricCalculator())
	{
		FatalErrorIn(FunctionSIG)
			<< "no metric calculator has been found!" << endl
			<< abort(FatalError);
	}

	if (NOT Colors())
	{
		FatalErrorIn(FunctionSIG)
			<< "no coloring has been found!" << endl
			<< abort(FatalError);
	}

	if (NOT Horizons()->Geometry())
	{
		FatalErrorIn(FunctionSIG)
			<< "no geometry has been found!" << endl
			<< abort(FatalError);
	}

	if (NOT Horizons()->HasHorizon())
	{
		Change_IsDone() = Standard_True;
	}
	else
	{
		auto d = Cad_SingularityHorizons::RetrieveDomain(*Horizons());
		//d.Expand(0.1*d.Diameter());
		const auto& gsurf = Horizons()->Geometry();

		const auto& colors = *Colors();

		std::map
			<
			Standard_Integer,
			std::shared_ptr<std::vector<std::shared_ptr<Entity2d_Polygon>>>
			>
			horizonMap;

		const auto& edges = Horizons()->Horizons()->Edges();
		for (const auto& x : edges)
		{
			Debug_Null_Pointer(x.second);
			const auto& e = x.second;

			const auto& poly = e->Polygon();
			Debug_Null_Pointer(poly);

			const auto& horizon = *poly;
#ifdef _DEBUG
			Cad_ColorApprxMetric::Check(horizon, colors);
#endif // _DEBUG
			const auto icolor = colors.Value(GetSamplePoint(horizon));
			auto iter = horizonMap.find(icolor);
			if (iter IS_EQUAL horizonMap.end())
			{
				auto polyList = std::make_shared<std::vector<std::shared_ptr<Entity2d_Polygon>>>();
				Debug_Null_Pointer(polyList);

				polyList->reserve(2);
				auto paired = std::make_pair(icolor, std::move(polyList));
				horizonMap.insert(std::move(paired));
			}
			horizonMap.at(icolor)->push_back(poly);
		}

		const auto tris = Cad_SingularityTools::GetTriangulation(d);
		const auto sides = Cad_SingularityTools::RetrieveSides(d);

		GeoMesh2d_Data bmesh;
		bmesh.Construct(*tris);

		auto& zones = ZonesRef();
		zones.reserve(horizonMap.size());

		for (const auto& x : horizonMap)
		{
			Debug_Null_Pointer(x.second);
			const auto& l = *x.second;

			if (l.empty())
			{
				FatalErrorIn(FunctionSIG)
					<< "empty list has been detected!" << endl
					<< abort(FatalError);
			}
			if (l.size() IS_EQUAL 1)
			{
				Debug_Null_Pointer(l.front());
				auto t = TypeDetection(l.front(), bmesh, sides, *gsurf);
				Debug_Null_Pointer(t);

				t->SetIndex(x.first);
				zones.push_back(std::move(t));
			}
			else if (l.size() IS_EQUAL 2)
			{
				const auto[pl0, pl1] = Cad_SingularityNonTempBase::RetrievePair(l);
				Debug_Null_Pointer(pl0);
				Debug_Null_Pointer(pl1);

				auto t = TypeDetection(pl0, pl1, bmesh, sides, *gsurf);
				Debug_Null_Pointer(t);

				t->SetIndex(x.first);
				zones.push_back(std::move(t));
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "unexpected situation has been detected!" << endl
					<< abort(FatalError);
			}
		}
	}

	Change_IsDone() = Standard_True;
}
#endif // __DEBUG

#include <Cad_ColorApprxMetric.hxx>

template<class SurfType>
inline tnbLib::Pnt2d 
tnbLib::Cad_Singularity<SurfType>::GetCorner
(
	const Standard_Integer zoneId
) const
{
	Debug_Null_Pointer(Colors());
	Debug_Null_Pointer(Colors()->Approximation());
	Debug_Null_Pointer(Colors()->Approximation()->BoundingBox());
	const Entity2d_Box b = *Colors()->Approximation()->BoundingBox();
	switch (zoneId)
	{
	case 1: return b.Corner(Box2d_PickAlgorithm_SW);
	case 2: return b.Corner(Box2d_PickAlgorithm_SE);
	case 3: return b.Corner(Box2d_PickAlgorithm_NE);
	case 4: return b.Corner(Box2d_PickAlgorithm_NW);
	default:
		FatalErrorIn(FunctionSIG)
			<< "invalid zone Id." << endl
			<< abort(FatalError);
		return Pnt2d::null;
	}
}