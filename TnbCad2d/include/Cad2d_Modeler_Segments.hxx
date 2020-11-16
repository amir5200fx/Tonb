#pragma once
#ifndef _Cad2d_Modeler_Segments_Header
#define _Cad2d_Modeler_Segments_Header

#include <Standard_TypeDef.hxx>
#include <Cad2d_Module.hxx>
#include <Global_Serialization.hxx>

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

			/*private functions and operators*/
			DECLARE_SAVE_LOAD_HEADER(TnbCad2d_EXPORT);

			auto& ChangeSegments()
			{
				return theSegments_;
			}

		protected:

			Modeler_Segments()
			{}

			TnbCad2d_EXPORT void InsertToSegments
			(
				const Standard_Integer theIndex, 
				const std::shared_ptr<Modeler_Segment>& theSeg
			);

			TnbCad2d_EXPORT std::shared_ptr<Modeler_Segment>
				RemoveFromSegments
				(
					const Standard_Integer theIndex
				);

		public:

			TnbCad2d_EXPORT Standard_Boolean
				IsContainsSegment
				(
					const Standard_Integer theIndex
				) const;

			TnbCad2d_EXPORT Standard_Boolean
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
