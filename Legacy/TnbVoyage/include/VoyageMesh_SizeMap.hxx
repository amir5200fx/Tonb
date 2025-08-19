#pragma once
#ifndef _VoyageMesh_SizeMap_Header
#define _VoyageMesh_SizeMap_Header

#include <Voyage_Module.hxx>
#include <GeoMesh2d_BackgroundFwd.hxx>
#include <Global_Done.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations [8/14/2023 aamir]
	class VoyageGeo_Path2;

	class VoyageMesh_SizeMap
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<VoyageGeo_Path2> thePath_;
		std::shared_ptr<std::vector<std::vector<Standard_Real>>> theHs_;

		std::shared_ptr<GeoMesh2d_Background> theBackMesh_;

		Standard_Integer theMaxNbCorrs_;
		Standard_Real theSmoothingFactor_;

		Standard_Real theBaseSize_;

	public:

		static TnbVoyage_EXPORT Standard_Integer DEFAULT_MAX_NB_CORRS;
		static TnbVoyage_EXPORT Standard_Real DEFAULT_SMOOTH_FACTOR;

		static TnbVoyage_EXPORT Standard_Real DEFAULT_BASE_SIZE;

		static TnbVoyage_EXPORT unsigned short verbose;

		// default constructor [8/14/2023 aamir]

		VoyageMesh_SizeMap()
			: theMaxNbCorrs_(DEFAULT_MAX_NB_CORRS)
			, theSmoothingFactor_(DEFAULT_SMOOTH_FACTOR)
			, theBaseSize_(DEFAULT_BASE_SIZE)
		{}

		// constructors [8/14/2023 aamir]


		// Public functions and operators [8/14/2023 aamir]

		const auto& Path() const { return thePath_; }
		const auto& Hs() const { return theHs_; }
		const auto& BackMesh() const { return theBackMesh_; }

		auto MaxNbCorrs() const { return theMaxNbCorrs_; }
		auto SmoothingFactor() const { return theSmoothingFactor_; }

		auto BaseSize() const { return theBaseSize_; }

		TnbVoyage_EXPORT void Perform();

		void SetPath(const std::shared_ptr<VoyageGeo_Path2>& thePath) { thePath_ = thePath; }
		void SetPath(std::shared_ptr<VoyageGeo_Path2>&& thePath) { thePath_ = std::move(thePath); }
		void SetHs(const std::shared_ptr<std::vector<std::vector<Standard_Real>>>& theHs) { theHs_ = theHs; }
		void SetHs(std::shared_ptr<std::vector<std::vector<Standard_Real>>>&& theHs) { theHs_ = std::move(theHs); }

		void SetBaseSize(const Standard_Real x) { theBaseSize_ = x; }

	};
}

#endif // !_VoyageMesh_SizeMap_Header
