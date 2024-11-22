#pragma once
#ifndef _Cad2d_Modeler_CornerAdaptor_Header
#define _Cad2d_Modeler_CornerAdaptor_Header

#include <Cad2d_Module.hxx>
#include <Global_Serialization.hxx>
#include <Global_TypeDef.hxx>

#include <memory>
#include <map>

namespace tnbLib
{

	namespace cad2dLib
	{

		// Forward Declarations
		class Modeler_Segment;

		class Modeler_CornerAdaptor
		{

			/*Private Data*/

			std::map<Standard_Integer, std::weak_ptr<Modeler_Segment>>
				theSegments_;


			/*private functions and operators*/
			TNB_SERIALIZATION(TnbCad2d_EXPORT);

			auto& ChangeSegments()
			{
				return theSegments_;
			}

		protected:

			Modeler_CornerAdaptor()
			{}

		public:

			auto NbSegments() const
			{
				return (Standard_Integer)theSegments_.size();
			}

			const auto& Segments() const
			{
				return theSegments_;
			}

			TnbCad2d_EXPORT Standard_Boolean
				IsContains
				(
					const std::shared_ptr<Modeler_Segment>& theSegmnt
				) const;

			TnbCad2d_EXPORT std::weak_ptr<Modeler_Segment>
				RemoveFromSegments
				(
					const Standard_Integer theIndex
				);

			TnbCad2d_EXPORT void ImportToSegments
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<Modeler_Segment>& theSegmnt
			);


		};
	}
}

#endif // !_Cad2d_Modeler_CornerAdaptor_Header
