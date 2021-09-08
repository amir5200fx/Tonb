#pragma once
#ifndef _ShapePx_TopoSection_Header
#define _ShapePx_TopoSection_Header

#include <ShapePx_TopoSectEntity.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class ShapePx_TopoSectSegment;

	class ShapePx_TopoSection
		: public ShapePx_TopoSectEntity
	{

		/*Private Data*/

		std::vector<std::shared_ptr<ShapePx_TopoSectSegment>> theSegments_;

		Standard_Real theX_;

		//- Private functions and operators

		TNB_SERIALIZATION(TnbShapePx_EXPORT);

	protected:

		//- default constructor

		ShapePx_TopoSection()
		{}

	public:


		//- constructors


		ShapePx_TopoSection
		(
			const std::vector<std::shared_ptr<ShapePx_TopoSectSegment>>& theSegments, 
			const Standard_Real x
		)
			: theSegments_(theSegments)
			, theX_(x)
			
		{}

		ShapePx_TopoSection
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::vector<std::shared_ptr<ShapePx_TopoSectSegment>>& theSegments,
			const Standard_Real x
		)
			: ShapePx_TopoSectEntity(theIndex, theName)
			, theSegments_(theSegments)
			, theX_(x)
		{}

		ShapePx_TopoSection
		(
			std::vector<std::shared_ptr<ShapePx_TopoSectSegment>>&& theSegments,
			const Standard_Real x
		)
			: theSegments_(std::move(theSegments))
			, theX_(x)
		{}

		ShapePx_TopoSection
		(
			const Standard_Integer theIndex,
			const word& theName, 
			std::vector<std::shared_ptr<ShapePx_TopoSectSegment>>&& theSegments,
			const Standard_Real x
		)
			: ShapePx_TopoSectEntity(theIndex, theName)
			, theSegments_(std::move(theSegments))
			, theX_(x)
		{}


		//- public functions and operators

		const auto& Segments() const
		{
			return theSegments_;
		}

		auto X() const
		{
			return theX_;
		}

		void SetX(const Standard_Real x)
		{
			theX_ = x;
		}

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::ShapePx_TopoSection);

#endif // !_ShapePx_TopoSection_Header
