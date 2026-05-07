#pragma once
#ifndef _GeoIO_UNVPoint_2D_Header
#define _GeoIO_UNVPoint_2D_Header

#include <GeoIO_UNVPoint.hxx>
#include <Pnt2d.hxx>

namespace tnbLib
{

	class GeoIO_UNVPoint_2D
		: public GeoIO_UNVPoint
	{

		/*Private Data*/

		Pnt2d theCoord_;

	public:

		// default constructor [9/4/2023 aamir]

		GeoIO_UNVPoint_2D()
		{}

		// constructors [9/4/2023 aamir]

		GeoIO_UNVPoint_2D(const Pnt2d& theCoord)
			: theCoord_(theCoord)
		{}

		GeoIO_UNVPoint_2D(Pnt2d&& theCoord)
			: theCoord_(std::move(theCoord))
		{}


		// Public functions and operators [9/4/2023 aamir]

		std::vector<Standard_Real> Components() const override;
		dim Dimension() const override;

		const auto& Coord() const { return theCoord_; }

		void SetCoord(const Pnt2d& theCoord) { theCoord_ = theCoord; }
		void SetCoord(Pnt2d&& theCoord) { theCoord_ = std::move(theCoord); }

	};
}

#endif // !_GeoIO_UNVPoint_2D_Header
