#pragma once
#ifndef _Aft2d_SolutionDataSurface_Header
#define _Aft2d_SolutionDataSurface_Header

#include <Global_Serialization.hxx>
#include <Mesh_Module.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>
#include <Geo2d_MetricFunctionFwd.hxx>
#include <Geo3d_SizeFunctionFwd.hxx>
#include <Aft2d_OptNodeSurface_CalculatorFwd.hxx>
#include <Aft2d_SolutionDataSurface_Traits.hxx>
#include <Aft2d_MetricPrcsrSurfaceFwd.hxx>
#include <Aft2d_MetricPrcsrSurface_Method.hxx>
#include <Geo2d_MetricFunction_SurfaceMethod.hxx>

#include <memory>
#include <map>

namespace tnbLib
{

	// Forward Declarations
	class Aft_MetricPrcsrAnIso_Info;
	class Mesh_Curve_Info;
	class Aft_MetricPrcsrAnIso_Info;

	template<class ShapeType>
	class Aft2d_SolutionDataSurface
	{

		/*Private Data*/

	public:

		typedef typename shape_plane_type_trait<ShapeType>::type plnType;

	private:

		// the geometry [2/18/2022 Amir]
		std::shared_ptr<ShapeType> theShape_;


		// the parametric planes [2/23/2022 Amir]

		// the global size function [2/18/2022 Amir]
		std::shared_ptr<Geo3d_SizeFunction> theSizeFun_;

		// curves info [2/27/2022 Amir]
		std::shared_ptr<Mesh_Curve_Info> theGlobalCurveInfo_;
		std::map
			<
			Standard_Integer,
			std::shared_ptr<Mesh_Curve_Info>
			> theCurveInfo_;

		// the metric info [2/18/2022 Amir]
		std::shared_ptr<Aft_MetricPrcsrAnIso_Info> theMetricPrcsrInfo_;

		Aft2d_MetricPrcsrSurface_Method theMetricPrcsrMethod_;

		Geo2d_MetricFunction_SurfaceMethod theMetricFunMethod_;

		// the node calculator [2/18/2022 Amir]


		// results [2/18/2022 Amir]


		// private functions and operators [2/23/2022 Amir]

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	public:

		static TnbMesh_EXPORT const std::string extension;

		// default constructor [2/18/2022 Amir]

		Aft2d_SolutionDataSurface()
		{}


		// constructors [2/18/2022 Amir]


		// public functions and operators [2/18/2022 Amir]

		const auto& Geometry() const
		{
			return theShape_;
		}

		auto& GeometryRef()
		{
			return theShape_;
		}

		const auto& SizeFun() const
		{
			return theSizeFun_;
		}

		auto& SizeFunRef()
		{
			return theSizeFun_;
		}

		auto MetricPrcsrMethod() const
		{
			return theMetricPrcsrMethod_;
		}

		auto MetricFunMethod() const
		{
			return theMetricFunMethod_;
		}

		const auto& SizeFunction() const
		{
			return theSizeFun_;
		}

		auto& SizeFunctionRef()
		{
			return theSizeFun_;
		}

		const auto& GlobalCurveInfo() const
		{
			return theGlobalCurveInfo_;
		}

		auto& GlobalCurveInfoRef()
		{
			return theGlobalCurveInfo_;
		}

		const auto& MetricPrcsrInfo() const
		{
			return theMetricPrcsrInfo_;
		}

		std::shared_ptr<Mesh_Curve_Info> CurveInfo(const Standard_Integer theSurfId) const;

		void SetCurveInfo(const Standard_Integer theSurfId, const std::shared_ptr<Mesh_Curve_Info>&);
		void SetCurveInfo(const Standard_Integer theSurfId, std::shared_ptr<Mesh_Curve_Info>&&);

		void SetGlobalCurveInfo(const std::shared_ptr<Mesh_Curve_Info>& theInfo)
		{
			theGlobalCurveInfo_ = theInfo;
		}

		void SetGlobalCurveInfo(std::shared_ptr<Mesh_Curve_Info>&& theInfo)
		{
			theGlobalCurveInfo_ = std::move(theInfo);
		}

		void SetMetricPrcsrInfo(const std::shared_ptr<Aft_MetricPrcsrAnIso_Info>& theInfo)
		{
			theMetricPrcsrInfo_ = theInfo;
		}

		void SetMetricPrcsrInfo(std::shared_ptr<Aft_MetricPrcsrAnIso_Info>&& theInfo)
		{
			theMetricPrcsrInfo_ = std::move(theInfo);
		}

		void SetGeometry(const std::shared_ptr<ShapeType>& theGeometry)
		{
			theShape_ = theGeometry;
		}

		void SetGeometry(std::shared_ptr<ShapeType>&& theGeometry)
		{
			theShape_ = std::move(theGeometry);
		}

		void SetSizeFun(const std::shared_ptr<Geo3d_SizeFunction>& theSizeFun)
		{
			theSizeFun_ = theSizeFun;
		}

		void SetSizeFun(std::shared_ptr<Geo3d_SizeFunction>&& theSizeFun)
		{
			theSizeFun_ = std::move(theSizeFun);
		}

		void SetMetricPrcsrMethod(const Aft2d_MetricPrcsrSurface_Method theMethod)
		{
			theMetricPrcsrMethod_ = theMethod;
		}

		void SetMetricFunMethod(const Geo2d_MetricFunction_SurfaceMethod theMethod)
		{
			theMetricFunMethod_ = theMethod;
		}
	};
}

#include <Aft2d_SolutionDataSurfaceI.hxx>

#endif // !_Aft2d_SolutionDataSurface_Header
