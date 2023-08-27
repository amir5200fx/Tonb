#pragma once
#ifndef _VoyageGeo_PathGeneration_Header
#define _VoyageGeo_PathGeneration_Header

#include <Voyage_Module.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Global_Done.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	// Forward Declarations [7/27/2023 Payvand]
	class Voyage_MetricInfo;
	class VoyageGeo_Earth;
	class VoyageGeo_Path2;
	class Cad_GeomCurve;
	class Cad_GeomSurface;
	class Mesh_Curve_Info;
	class Geo_MetricPrcsrAnIso_Info;

	class VoyageGeo_PathGeneration
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<Entity2d_Polygon> theOffsets_;

		std::shared_ptr<VoyageGeo_Earth> theEarth_;

		Standard_Integer theNbSamples_;

		// results [7/27/2023 Payvand]

		std::shared_ptr<VoyageGeo_Path2> thePath_;

	public:

		static TnbVoyage_EXPORT Standard_Integer DEFAULT_NB_SAMPLES;

		// default constructor [7/27/2023 Payvand]

		VoyageGeo_PathGeneration()
			: theNbSamples_(DEFAULT_NB_SAMPLES)
		{}

		// constructors [7/27/2023 Payvand]

		VoyageGeo_PathGeneration
		(
			const std::shared_ptr<Entity2d_Polygon>& theOffsets, 
			const std::shared_ptr<VoyageGeo_Earth>& theEarth
		)
			: theOffsets_(theOffsets)
			, theEarth_(theEarth)
			, theNbSamples_(DEFAULT_NB_SAMPLES)
		{}


		// Public functions and operators [7/27/2023 Payvand]

		const auto& Offsets() const { return theOffsets_; }
		const auto& Earth() const { return theEarth_; }

		const auto& Path() const { return thePath_; }

		auto NbSamples() const { return theNbSamples_; }

		TnbVoyage_EXPORT void Perform();

		void SetOffsets(const std::shared_ptr<Entity2d_Polygon>& theOffsets) { theOffsets_ = theOffsets; }
		void SetOffsets(std::shared_ptr<Entity2d_Polygon>&& theOffsets) { theOffsets_ = std::move(theOffsets); }
		void SetEarth(const std::shared_ptr<VoyageGeo_Earth>& theEarth) { theEarth_ = theEarth; }
	
		void SetNbSamples(const Standard_Integer theNbSamples) { theNbSamples_ = theNbSamples; }
		
		static Standard_Real CalcMinAngularDistance(const Pnt2d& theP0, const Pnt2d& theP1);

	};
}

#endif // !_VoyageGeo_PathGeneration_Header
