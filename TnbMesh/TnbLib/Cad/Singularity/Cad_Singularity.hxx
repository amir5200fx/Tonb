#pragma once
#ifndef _Cad_Singularity_Header
#define _Cad_Singularity_Header

#include <Cad_SingularityBase.hxx>
#include <Cad_SingularityTraits.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>
#include <GeoMesh2d_DataFwd.hxx>
#include <Mesh_Module.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Global_Done.hxx>

#include <memory>
#include <vector>

class Geom_Surface;

namespace tnbLib
{

	// Forward Declarations [12/31/2021 Amir]
	class Cad_SingularityHorizons;
	class Cad_ColorApprxMetric;
	class Pln_Curve;

	template<class SurfPln>
	class Cad_SingularZone;

	template<class SurfType>
	class Cad_Singularity
		: public Global_Done
		, public Cad_SingularityBase<typename cad_singularity_traits<SurfType>::parCurveType>
	{

	public:

		typedef typename cad_singularity_traits<SurfType>::plnType plnType;
		typedef typename cad_singularity_traits<SurfType>::parCurveType parCurveType;

		typedef Cad_SingularZone<plnType> singularZone;

	private:

		/*Private Data*/

		std::shared_ptr<Cad_SingularityHorizons> theHorizons_;
		std::shared_ptr<Cad_ColorApprxMetric> theColors_;

		std::shared_ptr<Geo2d_SizeFunction> theSizeFun_;
		std::shared_ptr<plnType> thePlane_;

		Standard_Real theWeight_;
		mutable Standard_Integer theNbZones_;


		// Results [3/28/2022 Amir]

		std::vector<std::shared_ptr<singularZone>> theZones_;


		// private functions and operators [3/28/2022 Amir]

		auto& ZonesRef()
		{
			return theZones_;
		}

		auto& NbZonesRef() const
		{
			return theNbZones_;
		}

		std::shared_ptr<singularZone> TypeDetection(const Entity2d_Polygon& thePoly, const GeoMesh2d_Data& theBMesh, const std::vector<std::shared_ptr<Pln_Curve>>& theSides, const Geom_Surface&) const;
		std::shared_ptr<singularZone> TypeDetection(const Entity2d_Polygon& thePoly0, const Entity2d_Polygon& thePoly1, const GeoMesh2d_Data& theBMesh, const std::vector<std::shared_ptr<Pln_Curve>>& theSides, const Geom_Surface&) const;

		static std::pair<std::shared_ptr<Entity2d_Polygon>, std::shared_ptr<Entity2d_Polygon>> RetrievePair(const std::vector<std::shared_ptr<Entity2d_Polygon>>&);

	public:

		typedef Cad_SingularityBase<typename cad_singularity_traits<SurfType>::parCurveType> base;

		static TnbMesh_EXPORT unsigned short verbose;

		// default constructor [12/31/2021 Amir]

		Cad_Singularity()
		{}

		// constructors [12/31/2021 Amir]


		// public functions and operators [12/31/2021 Amir]

		auto NbZones() const
		{
			return (Standard_Integer)theZones_.size();
		}

		auto Weight() const
		{
			return theWeight_;
		}

		const auto& Zones() const
		{
			return theZones_;
		}

		const auto& Horizons() const
		{
			return theHorizons_;
		}

		const auto& Colors() const
		{
			return theColors_;
		}

		const auto& SizeFun() const
		{
			return theSizeFun_;
		}

		const auto& ParaPlane() const
		{
			return thePlane_;
		}

		void Perform();

		static Pnt2d GetSamplePoint(const Entity2d_Polygon&);
	};
}

#include <Cad_SingularityI.hxx>

#endif // !_Cad_Singularity_Header
