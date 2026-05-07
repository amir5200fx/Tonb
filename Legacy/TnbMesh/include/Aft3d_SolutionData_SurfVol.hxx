#pragma once
#ifndef _Aft3d_SolutionData_SurfVol_Header
#define _Aft3d_SolutionData_SurfVol_Header

#include <Mesh_Module.hxx>
#include <Geo3d_SizeFunctionFwd.hxx>
#include <Entity3d_TriangulationFwd.hxx>
#include <Global_Serialization.hxx>

#include <map>
#include <memory>

namespace tnbLib
{
	// Forward Declarations
	class Aft_MetricPrcsrAnIso_Info;
	class Mesh_Curve_Info;
	class Cad_Volume;

	class Aft3d_SolutionData_SurfVol
	{
		/*Private Data*/
		std::shared_ptr<Cad_Volume> theVolume_;

		// the global size function
		std::shared_ptr<Geo3d_SizeFunction> theSizeFun_;

		// the curve info
		std::shared_ptr<Mesh_Curve_Info> theCurveInfo_;

		// the metric processor info
		std::shared_ptr<Aft_MetricPrcsrAnIso_Info> theMetricProcessor_;

		// results
		std::map<Standard_Integer, std::shared_ptr<Entity3d_Triangulation>> theTris_;
		std::shared_ptr<Entity3d_Triangulation> theMerged_;

		// Private functions and operators

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	public:

		static TnbMesh_EXPORT const std::string extension;

		// default constructor

		Aft3d_SolutionData_SurfVol() = default;

		// constructors

		// Public functions and operators

		const auto& Geometry() const { return theVolume_; }
		const auto& SizeFunction() const { return theSizeFun_; }
		const auto& CurveInfo() const { return theCurveInfo_; }
		const auto& MetricProcessorInfo() const { return theMetricProcessor_; }

		void SetGeometry(const std::shared_ptr<Cad_Volume>& theGeom) { theVolume_ = theGeom; }
		void SetSizeFunction(const std::shared_ptr<Geo3d_SizeFunction>& theFun) { theSizeFun_ = theFun; }
		void SetCurveInfo(const std::shared_ptr<Mesh_Curve_Info>& theInfo) { theCurveInfo_ = theInfo; }
		void SetMetricProcessorInfo(const std::shared_ptr<Aft_MetricPrcsrAnIso_Info>& theInfo) { theMetricProcessor_ = theInfo; }

		// the results
		const auto& Tris() const { return theTris_; }
		auto& TrisRef() { return theTris_; }
		const auto& Merged() const { return theMerged_; }
		auto& MergedRef() { return theMerged_; }
	};
}

#endif