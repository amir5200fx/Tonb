#pragma once
#ifndef _GeoTop2d_Point3d_Header
#define _GeoTop2d_Point3d_Header

#include <GeoTop2d_Point.hxx>
#include <Pnt3d.hxx>

namespace tnbLib
{

	class GeoTop2d_Point3d
		: public GeoTop2d_Point
	{

		/*Private Data*/

		Pnt3d theCoord_;

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

		GeoTop2d_Point3d()
		{}

		// constructors [2/17/2023 Payvand]

		GeoTop2d_Point3d(const Pnt3d& theCoord)
			: theCoord_(theCoord)
		{}

		GeoTop2d_Point3d(Pnt3d&& theCoord)
			: theCoord_(std::move(theCoord))
		{}


		// Public functions and operators [2/17/2023 Payvand]

		Standard_Boolean Is3d() const override
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

BOOST_CLASS_EXPORT_KEY(tnbLib::GeoTop2d_Point3d);

#endif // !_GeoTop2d_Point3d_Header
