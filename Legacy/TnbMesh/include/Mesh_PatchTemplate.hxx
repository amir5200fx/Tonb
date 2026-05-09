#pragma once
#ifndef _Mesh_PatchTemplate_Header
#define _Mesh_PatchTemplate_Header

#include <Mesh_PatchTemplate_Traits.hxx>
#include <Entity2d_TriangulationFwd.hxx>
#include <Entity3d_TriangulationFwd.hxx>
#include <Global_Indexed.hxx>
#include <Global_Handle.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class NumAlg_AdaptiveInteg_Info;

	template<class CurveType, class SizeFun, class MetricFun>
	class Mesh_RegionPlane;

	template<class SurfType, class SizeFun, class MetricFun>
	class Mesh_PatchTemplate
		: public Global_Indexed
	{

		typedef NumAlg_AdaptiveInteg_Info intgInfo;

		/*Private Data*/

		std::shared_ptr<SurfType> theSurface_;

		std::shared_ptr<Entity2d_Triangulation> theParaTriangulation_;
		std::shared_ptr<Entity3d_Triangulation> theSurfaceTriangulation_;


		// private functions and operators [12/19/2021 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			Info << "This function is not supposed to be called." << endl;
			NotImplemented;
		}

	public:

		typedef typename Mesh_PatchTemplate_Traits<SurfType, SizeFun, MetricFun>::parCurveType
			parCurveType;
		typedef typename Mesh_PatchTemplate_Traits<SurfType, SizeFun, MetricFun>::plnRegion
			plnRegion;


		// default constructor [12/19/2021 Amir]

		Mesh_PatchTemplate()
		{}

		// constructors [12/19/2021 Amir]

		explicit Mesh_PatchTemplate(const std::shared_ptr<SurfType>& theSurface)
			: theSurface_(theSurface)
		{}

		Mesh_PatchTemplate(std::shared_ptr<SurfType>&& theSurface)
			: theSurface_(std::move(theSurface))
		{}

		Mesh_PatchTemplate
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<SurfType>& theSurface
		)
			: Global_Indexed(theIndex)
			, theSurface_(theSurface)
		{}

		Mesh_PatchTemplate
		(
			const Standard_Integer theIndex,
			std::shared_ptr<SurfType>&& theSurface
		)
			: Global_Indexed(theIndex)
			, theSurface_(std::move(theSurface))
		{}

		// public functions and operators [12/19/2021 Amir]

		const auto& Surface() const
		{
			return theSurface_;
		}

		const auto& ParaTriangulation() const
		{
			return theParaTriangulation_;
		}

		const auto& SurfaceTriangulation() const
		{
			return theSurfaceTriangulation_;
		}

		void SetSurface(const std::shared_ptr<SurfType>& theSurface)
		{
			theSurface_ = theSurface;
		}

		void SetSurface(std::shared_ptr<SurfType>&& theSurface)
		{
			theSurface_ = std::move(theSurface);
		}

		void SetParaTriangulation(const std::shared_ptr<Entity2d_Triangulation>& theTri)
		{
			theParaTriangulation_ = theTri;
		}

		void SetParaTriangulation(std::shared_ptr<Entity2d_Triangulation>&& theTri)
		{
			theParaTriangulation_ = std::move(theTri);
		}

		void SetSurfaceTriangulation(const std::shared_ptr<Entity3d_Triangulation>& theTri)
		{
			theSurfaceTriangulation_ = theTri;
		}

		void SetSurfaceTriangulation(std::shared_ptr<Entity3d_Triangulation>&& theTri)
		{
			theSurfaceTriangulation_ = std::move(theTri);
		}

		virtual std::shared_ptr<plnRegion> GetPlane() const;

		//- Static functions and operators

		static std::shared_ptr<SurfType>
			ReParameterization
			(
				const SurfType& theSurface,
				const Standard_Real thsScale
			);

		static std::shared_ptr<SurfType>
			ReParameterization
			(
				const SurfType& theSurface,
				intgInfo& theInfo
			);
	};
}

//#include <Mesh_PatchTemplateI.hxx>

#endif // !_Mesh_PatchTemplate_Header