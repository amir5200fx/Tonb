#pragma once
#ifndef _Cad2d_Modeler_Counter_Header
#define _Cad2d_Modeler_Counter_Header

#include <Geo_ItemCounter.hxx>

namespace tnbLib
{

	namespace cad2dLib
	{

		class Modeler_Counter
		{

			/*Private Data*/

			mutable Geo_ItemCounter theVertexCounter_;
			mutable Geo_ItemCounter theEdgeCounter_;
			mutable Geo_ItemCounter theCornerCounter_;


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

			auto& CornerCounter() const
			{
				return theCornerCounter_;
			}

		};
	}
}

#endif // !_Cad2d_Modeler_Counter_Header
