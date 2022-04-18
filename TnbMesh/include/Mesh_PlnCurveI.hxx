#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
#include <MeshBase_Tools.hxx>
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