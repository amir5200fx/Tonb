#pragma once
#ifndef _Voyage_PathOnEarth_Header
#define _Voyage_PathOnEarth_Header

#include <Voyage_Module.hxx>
#include <Entity3d_PolygonFwd.hxx>
#include <Global_Done.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations [8/27/2023 aamir]
	class VoyageGeo_Earth;
	class VoyageGeo_Path2;

	class Voyage_PathOnEarth
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<VoyageGeo_Earth> theEarth_;
		std::shared_ptr<VoyageGeo_Path2> thePath_;

		std::vector<std::shared_ptr<Entity3d_Polygon>> thePath3D_;

	public:

		// Default constructor [8/27/2023 aamir]

		Voyage_PathOnEarth()
		{}

		// constructors [8/27/2023 aamir]

		Voyage_PathOnEarth
		(
			const std::shared_ptr<VoyageGeo_Earth>& theEarth, 
			const std::shared_ptr<VoyageGeo_Path2>& thePath
		)
			: theEarth_(theEarth)
			, thePath_(thePath)
		{}

		// Public functions and operators [8/27/2023 aamir]

		const auto& Earth() const { return theEarth_; }
		const auto& Path() const { return thePath_; }

		const auto& Path3D() const { return thePath3D_; }

		TnbVoyage_EXPORT void Perform();

		void SetEarth(const std::shared_ptr<VoyageGeo_Earth>& theEarth) { theEarth_ = theEarth; }
		void SetPath(const std::shared_ptr<VoyageGeo_Path2>& thePath) { thePath_ = thePath; }


	};
}

#endif // !_Voyage_PathOnEarth_Header
