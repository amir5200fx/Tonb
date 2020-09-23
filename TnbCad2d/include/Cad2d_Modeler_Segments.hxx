#pragma once
#ifndef _Cad2d_Modeler_Segments_Header
#define _Cad2d_Modeler_Segments_Header

#include <Standard_TypeDef.hxx>

#include <map>
#include <memory>

namespace tnbLib
{

	namespace cad2dLib
	{

		// Forward Declarations
		class Modeler_Segment;

		class Modeler_Segments
		{

			/*Private Data*/

			std::map<Standard_Integer, std::shared_ptr<Modeler_Segment>>
				theSegments_;

		protected:

			Modeler_Segments()
			{}

			void InsertToSegments
			(
				const Standard_Integer theIndex, 
				const std::shared_ptr<Modeler_Segment>& theSeg
			);

			std::shared_ptr<Modeler_Segment> 
				RemoveFromSegments
				(
					const Standard_Integer theIndex
				);

		public:

			Standard_Boolean 
				IsContainsSegment
				(
					const Standard_Integer theIndex
				) const;

			Standard_Boolean 
				IsContainsSegment
				(
					const std::shared_ptr<Modeler_Segment>& theSegmnt
				) const;

			auto NbSegments() const
			{
				return (Standard_Integer)theSegments_.size();
			}

			const auto& Segments() const
			{
				return theSegments_;
			}


		};
	}
}

#endif // !_Cad2d_Modeler_Segments_Header
