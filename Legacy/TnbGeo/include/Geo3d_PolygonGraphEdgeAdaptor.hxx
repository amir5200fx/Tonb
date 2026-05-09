#pragma once
#ifndef _Geo3d_PolygonGraphEdgeAdaptor_Header
#define _Geo3d_PolygonGraphEdgeAdaptor_Header

#include <Geo_GraphEdgeAdaptor.hxx>
#include <Entity3d_PolygonFwd.hxx>

#include <memory>

namespace tnbLib
{

	template<>
	class Geo_GraphEdgeAdaptor<Entity3d_Polygon>
	{

		/*private Data*/

		std::shared_ptr<Entity3d_Polygon> thePolygon_;

	protected:

		// default constructor 

		Geo_GraphEdgeAdaptor()
		{}

		// constructors 


	public:

		// public functions and operators 

		const auto& Polygon() const
		{
			return thePolygon_;
		}

		void SetPolygon(const std::shared_ptr<Entity3d_Polygon>& thePolygon)
		{
			thePolygon_ = thePolygon;
		}

		void SetPolygon(std::shared_ptr<Entity3d_Polygon>&& thePolygon)
		{
			thePolygon_ = std::move(thePolygon);
		}
	};
}

#endif // !_Geo3d_PolygonGraphEdgeAdaptor_Header
