#pragma once
#ifndef _GeoIO_INPPoint_Header
#define _GeoIO_INPPoint_Header

#include <Pnt3d.hxx>
#include <Global_Indexed.hxx>
#include <Istream.hxx>

namespace tnbLib
{

	// Forward Declarations [9/5/2023 aamir]
	class GeoIO_INPPoint;

	TnbGeo_EXPORT Istream& operator>>(Istream& is, GeoIO_INPPoint&);
	TnbGeo_EXPORT std::istream& operator>>(std::istream& is, GeoIO_INPPoint&);

	class GeoIO_INPPoint
		: public Global_Indexed
	{

		/*Private Data*/

		Pnt3d theCoord_;

		// Private functions and operators [9/5/2023 aamir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& boost::serialization::base_object<Global_Indexed>(*this);
			ar& theCoord_;
		}

	public:

		// default constructor [9/5/2023 aamir]

		GeoIO_INPPoint()
		{}

		// constructors [9/5/2023 aamir]

		GeoIO_INPPoint
		(
			const Standard_Integer theIndex,
			const Pnt3d& theCoord
		)
			: Global_Indexed(theIndex)
			, theCoord_(theCoord)
		{}

		GeoIO_INPPoint
		(
			const Standard_Integer theIndex,
			Pnt3d&& theCoord
		)
			: Global_Indexed(theIndex)
			, theCoord_(std::move(theCoord))
		{}

		TnbGeo_EXPORT GeoIO_INPPoint(Istream& is);
		TnbGeo_EXPORT GeoIO_INPPoint(std::istream& is);


		// Public functions and operators [9/5/2023 aamir]

		const auto& Coord() const { return theCoord_; }

		void SetCoord(const Pnt3d& theCoord) { theCoord_ = theCoord; }
		void SetCoord(Pnt3d&& theCoord) { theCoord_ = std::move(theCoord); }

	};
}

#endif // !_GeoIO_INPPoint_Header
