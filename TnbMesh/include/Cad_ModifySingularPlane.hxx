#pragma once
#ifndef _Cad_ModifySingularPlane_Header
#define _Cad_ModifySingularPlane_Header

#include <Cad_SingularityTopology.hxx>
#include <Cad_ModifySingularPlaneTools.hxx>
#include <Cad_SingularityTraits.hxx>
#include <Cad_ModifySingularPlane_PolygonFwd.hxx>
#include <Mesh_Module.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Global_Done.hxx>

#include <memory>
#include <vector>

#include "GModel_Surface.hxx"

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	// Forward Declarations [3/31/2022 Amir]
	class Cad_ColorApprxMetric;

	template<class SurfPln>
	class Cad_SingularZone;

	template<class SurfType>
	class Cad_SingularityTopology;

	template<class WireType, bool RandSamples>
	class Cad_ApprxWire;

	class Cad_ModifySingularPlaneBase
	{

		/*Private Data*/

		std::vector<std::shared_ptr<meshLib::singularity::Polygon>> thePolygons_;

	protected:

		// default constructor [4/3/2022 Amir]

		Cad_ModifySingularPlaneBase()
		{}

		// protected functions and operators [4/3/2022 Amir]

		auto& PolygonsRef()
		{
			return thePolygons_;
		}

		TnbMesh_EXPORT void RegisterPolygon(const Entity2d_Polygon&);
		TnbMesh_EXPORT void Reserve(const size_t);

		TnbMesh_EXPORT Standard_Boolean InsidePolygon(const Standard_Integer theIndex, const Pnt2d&) const;

	public:

		// public functions and operators [4/3/2022 Amir]

		const auto& Polygons() const
		{
			return thePolygons_;
		}
	};

	template<class SurfType>
	class Cad_ModifySingularPlane
		: public Global_Done
		, public Cad_ModifySingularPlaneBase
	{

	public:

		typedef typename cad_singularity_traits<SurfType>::plnType plnType;
		typedef typename cad_singularity_traits<SurfType>::parWireType parWireType;
		typedef typename cad_singularity_traits<SurfType>::parCurveType parCurveType;
		typedef Cad_SingularZone<plnType> singularZoneType;

	private:


		/*Private Data*/

		// inputs [3/31/2022 Amir]

		std::shared_ptr<Geo_ApprxCurve_Info> theApproxInfo_;

		std::vector<std::shared_ptr<singularZoneType>> theZones_;

		std::shared_ptr<plnType> thePlane_;
		std::shared_ptr<SurfType> theSurface_;

		std::shared_ptr<Cad_ColorApprxMetric> theColors_;
	

		Standard_Real theTolerance_;


		// outputs [3/31/2022 Amir]
		std::vector<std::shared_ptr<plnType>> theModifieds_;


		// private functions and operators [4/1/2022 Amir]

		auto& ModifiedPlanesRef()
		{
			return theModifieds_;
		}

		
		void RegisterPolygons(const std::vector<std::shared_ptr<Entity2d_Polygon>>&);

		static std::shared_ptr<parWireType> 
			GetWire
			(
				const Geo2d_TopoChainAnalysis::entityType&, 
				const typename Cad_SingularityTopology<SurfType>::edgeToCurveMap&
			);

		static std::vector<std::shared_ptr<plnType>> 
			FormNewPlanes
			(
				const std::vector<std::shared_ptr<Geo2d_TopoChainAnalysis::entityType>>& theOuters, 
				const std::vector<std::shared_ptr<Geo2d_TopoChainAnalysis::entityType>>& theInners, 
				const typename Cad_SingularityTopology<SurfType>::edgeToCurveMap&
			);

		static Pnt2d 
			GetSample
			(
				const Geo2d_TopoChainAnalysis::entityType&, 
				const typename Cad_SingularityTopology<SurfType>::edgeToCurveMap&
			);

		static Standard_Boolean 
			IsOuterWire
			(
				const Geo2d_TopoChainAnalysis::entityType&,
				const typename Cad_SingularityTopology<SurfType>::edgeToCurveMap&, 
				const std::map<std::shared_ptr<parCurveType>, Cad_ModifySingularPlaneToolsBase::pCurveType>&
			);

		static Cad_ModifySingularPlaneToolsBase::pCurveType
			RetrieveType
			(
				const Geo2d_TopoChainAnalysis::entityType&,
				const typename Cad_SingularityTopology<SurfType>::edgeToCurveMap&,
				const std::map<std::shared_ptr<parCurveType>, Cad_ModifySingularPlaneToolsBase::pCurveType>&
			);

		void RemoveOutOfBoundaryHorizons
		(
			Cad_SingularityTopology<SurfType>&, 
			const Standard_Integer nbWires, 
			const typename Cad_SingularityTopology<SurfType>::edgeToCurveMap&, 
			const std::map<std::shared_ptr<parCurveType>, Cad_ModifySingularPlaneToolsBase::pCurveType>&
		);

		static void RemoveColoredEdges
		(
			Cad_SingularityTopology<SurfType>&,
			const Cad_ColorApprxMetric&,
			const typename Cad_SingularityTopology<SurfType>::edgeToCurveMap&, 
			const std::map<std::shared_ptr<parCurveType>, Cad_ModifySingularPlaneToolsBase::pCurveType>&, 
			std::map<std::shared_ptr<Geo2d_TopoChainAnalysis::entityType>, Standard_Integer>&
		);

	public:


		Standard_Boolean IsZonesLoaded() const;
		Standard_Boolean IsPlaneLoaded() const;
		Standard_Boolean IsColorsLoaded() const;
		Standard_Boolean IsSurfaceLoaded() const;

		auto Tolerance() const
		{
			return theTolerance_;
		}

		const auto& Zones() const
		{
			return theZones_;
		}

		const auto& Plane() const
		{
			return thePlane_;
		}

		const auto& Surface() const
		{
			return theSurface_;
		}

		const auto& Colors() const
		{
			return theColors_;
		}

		const auto& ApproxInfo() const
		{
			return theApproxInfo_;
		}

		void Perform();


		static std::vector<std::shared_ptr<parWireType>> RetrieveWires(const plnType&);
	};
}

#include <Cad_ModifySingularPlaneI.hxx>

#endif // !_Cad_ModifySingularPlane_Header
