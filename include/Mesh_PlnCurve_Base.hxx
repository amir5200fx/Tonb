#pragma once
#ifndef _Mesh_PlnCurve_Base_Header
#define _Mesh_PlnCurve_Base_Header

#include <Mesh_Module.hxx>
#include <Entity2d_Chain.hxx>
#include <Entity2d_Polygon.hxx>
#include <Global_Handle.hxx>

#include <memory>
#include <vector>

class Geom2d_Curve;

namespace tnbLib
{

	// Forward Declarations
	class Geo_ApprxCurve_Info;
	class Mesh_Curve_Info;

	template<class SizeFun, class MetricFun>
	class Geo_MetricPrcsr;

	class Mesh_PlnCurve_Base
	{

	protected:

		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& /*ar*/, const unsigned int /*file_version*/)
		{}


		template<class SizeFun, class MetricFun = void>
		static std::shared_ptr<Entity2d_Polygon> Mesh
		(
			const Handle(Geom2d_Curve)& theCurve,
			const Standard_Real theU0,
			const Standard_Real theU1,
			const std::shared_ptr<Geo_MetricPrcsr<SizeFun, MetricFun>>& theMap,
			const std::shared_ptr<Mesh_Curve_Info>& theInfo
		);

		static TnbMesh_EXPORT std::shared_ptr<Entity2d_Polygon> Discrete
		(
			const Handle(Geom2d_Curve)& theCurve,
			const Standard_Real theU0,
			const Standard_Real theU1,
			const std::shared_ptr<Geo_ApprxCurve_Info>& theInfo
		);
	};
}

#endif // !_Mesh_PlnCurve_Base_Header