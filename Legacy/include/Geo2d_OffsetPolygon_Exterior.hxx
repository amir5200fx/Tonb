#pragma once
#ifndef _Geo2d_OffsetPolygon_Exterior_Header
#define _Geo2d_OffsetPolygon_Exterior_Header

#include <Entity2d_PolygonFwd.hxx>
#include <Geo_Module.hxx>
#include <Global_Done.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations [8/30/2023 aamir]

	class Geo2d_OffsetPolygon_Exterior
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<Entity2d_Polygon> thePolygon_;
		
		Standard_Real theMaxOffset_;

		// results [8/30/2023 aamir]

		std::vector<std::shared_ptr<Entity2d_Polygon>> theOffsets_;

	public:

		// default constructor [8/30/2023 aamir]

		Geo2d_OffsetPolygon_Exterior()
			: theMaxOffset_(0)
		{}

		Geo2d_OffsetPolygon_Exterior
		(
			const std::shared_ptr<Entity2d_Polygon>& thePolygon, 
			const Standard_Real theOffset
		)
			: thePolygon_(thePolygon)
			, theMaxOffset_(theOffset)
		{}

		// Public functions and operators [8/30/2023 aamir]

		const auto& Polygon() const { return thePolygon_; }

		auto MaxOffset() const { return theMaxOffset_; }

		const auto& Offsets() const { return theOffsets_; }

		TnbGeo_EXPORT void Perform();

		void SetPolygon(const std::shared_ptr<Entity2d_Polygon>& thePolygon) { thePolygon_ = thePolygon; }
		void SetMaxOffset(const Standard_Real theValue) { theMaxOffset_ = theValue; }


	};
}

#endif // !_Geo2d_OffsetPolygon_Exterior_Header
