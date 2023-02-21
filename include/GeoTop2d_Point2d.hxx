#pragma once
#ifndef _GeoTop2d_Point2d_Header
#define _GeoTop2d_Point2d_Header

#include <GeoTop2d_Point.hxx>
#include <Pnt2d.hxx>

namespace tnbLib
{

	class GeoTop2d_Point2d
		: public GeoTop2d_Point
	{

		/*Private data*/

		Pnt2d theCoord_;


		// Private functions and operators [2/17/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& boost::serialization::base_object<GeoTop2d_Point>(*this);
			ar& theCoord_;
		}

	public:

		// default constructor [2/17/2023 Payvand]

		GeoTop2d_Point2d()
		{}

		// constructors [2/17/2023 Payvand]

		GeoTop2d_Point2d(const Pnt2d& theCoord)
			: theCoord_(theCoord)
		{}

		GeoTop2d_Point2d(Pnt2d&& theCoord)
			: theCoord_(std::move(theCoord))
		{}

		// Public functions and operators [2/17/2023 Payvand]

		Standard_Boolean Is2d() const override
		{
			return Standard_True;
		}

		const auto& Coord() const
		{
			return theCoord_;
		}

		auto& CoordRef()
		{
			return theCoord_;
		}

	 	TnbGeo_EXPORT std::shared_ptr<GeoTop2d_Point> Copy() const override;

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::GeoTop2d_Point2d);

#endif // !_GeoTop2d_Point2d_Header
