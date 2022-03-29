#pragma once
#ifndef _Cad_Singularity_Header
#define _Cad_Singularity_Header

#include <Global_Done.hxx>
#include <Cad_SingularityTraits.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>
#include <GeoMesh2d_DataFwd.hxx>
#include <Entity2d_PolygonFwd.hxx>

#include <memory>
#include <vector>

class Geom_Surface;

namespace tnbLib
{

	// Forward Declarations [12/31/2021 Amir]
	class Cad_PoleSingularZone;
	class Cad_SingularityHorizons;
	class Cad_ColorApprxMetric;
	class Pln_Curve;

	template<class SurfPln>
	class Cad_SingularZone;

	template<class SurfType>
	class Cad_Singularity
		: public Global_Done
	{

	public:

		typedef typename cad_singularity_traits<SurfType>::plnType plnType;
		typedef typename cad_singularity_traits<SurfType>::parCurveType parCurveType;

		typedef Cad_SingularZone<SurfType> singularZone;

	private:

		/*Private Data*/

		std::shared_ptr<Cad_SingularityHorizons> theHorizons_;
		std::shared_ptr<Cad_ColorApprxMetric> theColors_;

		std::shared_ptr<Geo2d_SizeFunction> theSizeFun_;


		// Results [3/28/2022 Amir]

		std::vector<std::shared_ptr<singularZone>> theZones_;


		// private functions and operators [3/28/2022 Amir]

		auto& ZonesRef()
		{
			return theZones_;
		}


		std::shared_ptr<singularZone> TypeDetection(const Entity2d_Polygon& thePoly, const GeoMesh2d_Data& theBMesh, const std::vector<std::shared_ptr<Pln_Curve>>& theSides, const Geom_Surface&) const;
		std::shared_ptr<singularZone> TypeDetection(const Entity2d_Polygon& thePoly0, const Entity2d_Polygon& thePoly1, const GeoMesh2d_Data& theBMesh, const std::vector<std::shared_ptr<Pln_Curve>>& theSides, const Geom_Surface&) const;

	public:

		static unsigned short verbose;

		// default constructor [12/31/2021 Amir]

		Cad_Singularity()
		{}

		// constructors [12/31/2021 Amir]


		// public functions and operators [12/31/2021 Amir]

		auto NbZones() const
		{
			return (Standard_Integer)theZones_.size();
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

		void Perform();
	};
}

#endif // !_Cad_Singularity_Header
