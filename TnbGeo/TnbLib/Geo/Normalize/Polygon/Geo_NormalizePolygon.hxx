#pragma once
#ifndef _Geo_NormalizePolygon_Header
#define _Geo_NormalizePolygon_Header

#include <Geo2d_NormalizePts.hxx>
#include <Entity_Polygon.hxx>

#include <memory>

namespace tnbLib
{

	template<class Point>
	class Geo_NormalizePolygon
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<Entity_Polygon<Point>> thePolygon_;

		// results [5/28/2022 Amir]

		std::shared_ptr<Entity_Polygon<Point>> theNormalized_;


		// private functions and operators [5/28/2022 Amir]

		auto& NormalizedRef()
		{
			return theNormalized_;
		}

	public:

		// default constructor [5/28/2022 Amir]

		Geo_NormalizePolygon()
		{}

		// constructors [5/28/2022 Amir]

		explicit Geo_NormalizePolygon
		(
			const std::shared_ptr<Entity_Polygon<Point>>& thePoly
		)
			: thePolygon_(thePoly)
		{}


		// public functions and operators [5/28/2022 Amir]

		const auto& Polygon() const
		{
			return thePolygon_;
		}

		const auto& Normalized() const
		{
			return theNormalized_;
		}

		void Perform();

		void SetPolygon(const std::shared_ptr<Entity_Polygon<Point>>& thePoly)
		{
			thePolygon_ = thePoly;
		}

		void SetPolygon(std::shared_ptr<Entity_Polygon<Point>>&& thePoly)
		{
			thePolygon_ = std::move(thePoly);
		}
	};
}

#include <Geo_NormalizePolygonI.hxx>

#endif // !_Geo_NormalizePolygon_Header
