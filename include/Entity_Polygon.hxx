#pragma once
#ifndef _Entity_Polygon_Header
#define _Entity_Polygon_Header

#include <Standard_TypeDef.hxx>
#include <Geo_Traits.hxx>
#include <Geo_Module.hxx>
#include <Global_Serialization.hxx>
#include <OFstream.hxx>

#include <vector>
#include <fstream>

namespace tnbLib
{

	template<class Point>
	class Entity_Polygon
	{

		using coord = typename entity_coord<Point>::coord;
		typedef std::vector<Point> pointList;

		/*Private Data*/

		pointList thePoints_;

		Standard_Real theDeflection_ = 0;


		/*private functions and operators*/


		const coord& Coord(const Standard_Integer) const;
		coord& Coord(const Standard_Integer);

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & thePoints_;
			ar & theDeflection_;
		}

	public:

		static TnbGeo_EXPORT const std::string extension;

		// default constructor [7/14/2021 Amir]

		Entity_Polygon() = default;
		Entity_Polygon(const Entity_Polygon&) = default;


		// constructors [7/14/2021 Amir]

		Entity_Polygon(pointList thePoints, const Standard_Real theDeflection)
			: thePoints_(std::move(thePoints))
			, theDeflection_(theDeflection)
		{}

		Entity_Polygon(Entity_Polygon&& other) noexcept
			: thePoints_(std::move(other.thePoints_))
			  , theDeflection_(std::move(other.theDeflection_))
		{}


		// public functions and operators [7/14/2021 Amir]

		Entity_Polygon& operator=(Entity_Polygon&& other) noexcept
		{
			if (this != &other)
			{
				thePoints_ = std::move(other.thePoints_);
				theDeflection_ = std::move(other.theDeflection_);
			}
			return *this;
		}
		Entity_Polygon& operator=(const Entity_Polygon&) = default;

		Entity_Polygon Reversed() const
		{
			Entity_Polygon copy = *this;
			copy.Reverse();
			return copy;
		}

		const pointList& Points() const
		{
			return thePoints_;
		}

		pointList& Points()
		{
			return thePoints_;
		}

		Standard_Real Deflection() const
		{
			return theDeflection_;
		}

		Standard_Real& Deflection()
		{
			return theDeflection_;
		}

		Standard_Integer NbPoints() const
		{
			return static_cast<Standard_Integer>(thePoints_.size());
		}

		Standard_Boolean IsClosed() const
		{
			const auto& p0 = Coord(0);
			const auto& p1 = Coord(static_cast<Standard_Integer>(thePoints_.size()) - 1);

			return p0.Distance(p1) <= gp::Resolution();
		}

		const coord& GetPoint(const Standard_Integer theIndex) const
		{
			return Coord(theIndex);
		}

		coord& GetPoint(const Standard_Integer theIndex)
		{
			return Coord(theIndex);
		}

		const coord& FirstPoint() const;
		const coord& LastPoint() const;

		coord& FirstPointRef();
		coord& LastPointRef();

		void Transform
		(
			const typename transform_point_type<coord>::type& theTrasf
		)
		{
			for (Standard_Integer i = 0; i < NbPoints(); i++)
				Coord(i).Transform(theTrasf);
		}

		void Reverse();

		void Smoothing(const Standard_Real Omega, const Standard_Integer NbIterations);

		void ExportToPlt(std::fstream& File) const;
		void ExportToPlt(OFstream& File) const;
		void ExportToPlt(std::stringstream&) const;
		void ExportToVtk(OFstream&) const;
		void ExportToVtk(std::fstream&) const;
		void ExportToVtk(std::stringstream&) const;

		static void Check(const Entity_Polygon<Point>&);
	};
}

#include <Entity_PolygonI.hxx>

#include <Entity2d_Polygon.hxx>
#include <Entity3d_Polygon.hxx>

#endif // !_Entity_Polygon_Header
