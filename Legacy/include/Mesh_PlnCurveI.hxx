#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
#include <MeshBase_Tools.hxx>
template<class CurveType, class SizeFun, class MetricFun>
inline Standard_Boolean 
tnbLib::Mesh_PlnCurve<CurveType, SizeFun, MetricFun>::IsSingular() const
{
	return Standard_False;
}

template<class CurveType, class SizeFun, class MetricFun>
inline void tnbLib::Mesh_PlnCurve<CurveType, SizeFun, MetricFun>::OrientWith
(
	const std::shared_ptr<Mesh_PlnCurve>&
)
{
	FatalErrorIn(FunctionSIG)
		<< "it's not supposed to be called!" << endl
		<< abort(FatalError);
}

template<class CurveType, class SizeFun, class MetricFun>
inline tnbLib::Pnt2d 
tnbLib::Mesh_PlnCurve<CurveType, SizeFun, MetricFun>::FirstCoord() const
{
	auto pt = Value(FirstParameter());
	return std::move(pt);
}

template<class CurveType, class SizeFun, class MetricFun>
inline tnbLib::Pnt2d 
tnbLib::Mesh_PlnCurve<CurveType, SizeFun, MetricFun>::LastCoord() const
{
	auto pt = Value(LastParameter());
	return std::move(pt);
}

template<class CurveType, class SizeFun, class MetricFun>
inline Standard_Real 
tnbLib::Mesh_PlnCurve<CurveType, SizeFun, MetricFun>::CalcCharLength
(
	const Pnt2d& theP0, 
	const Pnt2d& theP1,
	const std::shared_ptr<metricMap>& theSizeMap
) const
{
	Debug_Null_Pointer(theSizeMap);
	return theSizeMap->CalcDistance(theP0, theP1);
}

template<class CurveType, class SizeFun, class MetricFun>
inline tnbLib::Pnt2d 
tnbLib::Mesh_PlnCurve<CurveType, SizeFun, MetricFun>::CalcCentre
(
	const Pnt2d & theP0,
	const Pnt2d & theP1, 
	const std::shared_ptr<metricMap>& theSizeMap
) const
{
	Debug_Null_Pointer(theSizeMap);
	auto pt = theSizeMap->CalcCentre(theP0, theP1);
	return std::move(pt);
}

template<class CurveType, class SizeFun, class MetricFun>
inline std::pair<tnbLib::Pnt2d, tnbLib::Pnt2d> 
tnbLib::Mesh_PlnCurve<CurveType, SizeFun, MetricFun>::BoundCoords() const
{
	auto P0 = FirstCoord();
	auto P1 = LastCoord();
	auto t = std::make_pair(std::move(P0), std::move(P1));
	return std::move(t);
}

template<class CurveType, class SizeFun, class MetricFun>
inline std::pair<Standard_Real, Standard_Real> 
tnbLib::Mesh_PlnCurve<CurveType, SizeFun, MetricFun>::Bounds() const
{
	auto t = std::make_pair(FirstParameter(), LastParameter());
	return std::move(t);
}

namespace tnbLib
{

	template<class CurveType, class SizeFun, class MetricFun>
	std::shared_ptr<Entity2d_Polygon>
		Mesh_PlnCurve<CurveType, SizeFun, MetricFun>::Discrete
		(
			const std::shared_ptr<Geo_ApprxCurve_Info>& theInfo
		) const
	{
		if (NOT Curve())
		{
			FatalErrorIn(FunctionSIG)
				<< "no curve has been loaded" << endl
				<< abort(FatalError);
		}
		auto mesh =
			base::Discrete
			(
				MeshBase_Tools::Geometry(Curve()),
				MeshBase_Tools::FirstParameter(Curve()), MeshBase_Tools::LastParameter(Curve()),
				theInfo);
		return std::move(mesh);
	}

	template<class CurveType, class SizeFun, class MetricFun>
	std::shared_ptr<Entity2d_Polygon>
		Mesh_PlnCurve<CurveType, SizeFun, MetricFun>::Mesh
		(
			const std::shared_ptr<metricMap>& theMetricMap,
			const std::shared_ptr<Mesh_Curve_Info>& theInfo
		) const
	{
		if (NOT Curve())
		{
			FatalErrorIn(FunctionSIG)
				<< "no curve has been loaded" << endl
				<< abort(FatalError);
		}
		auto mesh =
			base::Mesh<SizeFun, MetricFun>
			(
				MeshBase_Tools::Geometry(Curve()),
				MeshBase_Tools::FirstParameter(Curve()),
				MeshBase_Tools::LastParameter(Curve()), theMetricMap, theInfo
				);
		return std::move(mesh);
	}
}