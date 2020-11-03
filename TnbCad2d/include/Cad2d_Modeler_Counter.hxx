#pragma once
#ifndef _Cad2d_Modeler_Counter_Header
#define _Cad2d_Modeler_Counter_Header

#include <Geo_ItemCounter.hxx>
#include <Global_Serialization.hxx>

namespace tnbLib
{

	namespace cad2dLib
	{

		class Modeler_Counter
		{

			/*Private Data*/

			mutable Geo_ItemCounter theVertexCounter_;
			mutable Geo_ItemCounter theEdgeCounter_;
			mutable Geo_ItemCounter thePlaneCounter_;
			mutable Geo_ItemCounter theSegmntCounter_;

			/*private functions and operators*/

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int version)
			{
				ar & VertexCounter();
				ar & EdgeCounter();
				ar & PlaneCounter();
				ar & SegmntCounter();
			}

		protected:

			Modeler_Counter()
			{}

			auto& VertexCounter() const
			{
				return theVertexCounter_;
			}

			auto& EdgeCounter() const
			{
				return theEdgeCounter_;
			}

			auto& PlaneCounter() const
			{
				return thePlaneCounter_;
			}

			auto& SegmntCounter() const
			{
				return theSegmntCounter_;
			}
		};
	}
}

#endif // !_Cad2d_Modeler_Counter_Header
