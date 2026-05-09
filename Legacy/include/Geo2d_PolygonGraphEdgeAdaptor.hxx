#pragma once
#ifndef _Geo2d_PolygonGraphEdgeAdaptor_Header
#define _Geo2d_PolygonGraphEdgeAdaptor_Header

#include <Geo_GraphEdgeAdaptor.hxx>
#include <Entity2d_PolygonFwd.hxx>

#include <memory>

namespace tnbLib
{

	template<>
	class Geo_GraphEdgeAdaptor<Entity2d_Polygon>
	{

		/*private Data*/

		std::shared_ptr<Entity2d_Polygon> thePolygon_;

	protected:

		// default constructor [1/5/2022 Amir]

		Geo_GraphEdgeAdaptor()
		{}

		// constructors [1/5/2022 Amir]


	public:

		// public functions and operators [1/5/2022 Amir]

		const auto& Polygon() const
		{
			return thePolygon_;
		}

		void SetPolygon(const std::shared_ptr<Entity2d_Polygon>& thePolygon)
		{
			thePolygon_ = thePolygon;
		}

		void SetPolygon(std::shared_ptr<Entity2d_Polygon>&& thePolygon)
		{
			thePolygon_ = std::move(thePolygon);
		}
	};
}

#endif // !_Geo2d_PolygonGraphEdgeAdaptor_Header
