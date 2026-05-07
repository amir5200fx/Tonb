#pragma once
#ifndef _GeoIO_UNVPoint_3D_Header
#define _GeoIO_UNVPoint_3D_Header

#include <GeoIO_UNVPoint.hxx>
#include <Pnt3d.hxx>

namespace tnbLib
{

	class GeoIO_UNVPoint_3D
		: public GeoIO_UNVPoint
	{

		/*Private Data*/

		Pnt3d theCoord_;

	public:

		// default constructor [9/4/2023 aamir]

		GeoIO_UNVPoint_3D()
		{}

		// constructors [9/4/2023 aamir]

		GeoIO_UNVPoint_3D(const Pnt3d& theCoord)
			: theCoord_(theCoord)
		{}

		GeoIO_UNVPoint_3D(Pnt3d&& theCoord)
			: theCoord_(std::move(theCoord))
		{}


		// Public functions and operators [9/4/2023 aamir]

		const auto& Coord() const { return theCoord_; }

		std::vector<Standard_Real> Components() const override;
		dim Dimension() const override;

		void SetCoord(const Pnt3d& theCoord) { theCoord_ = theCoord; }
		void SetCoord(Pnt3d&& theCoord) { theCoord_ = std::move(theCoord); }

	};

}

#endif // !_GeoIO_UNVPoint_3D_Header
