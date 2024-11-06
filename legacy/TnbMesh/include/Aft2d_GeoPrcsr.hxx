#pragma once
#ifndef _Aft2d_GeoPrcsr_Header
#define _Aft2d_GeoPrcsr_Header

#include <Entity2d_BoxFwd.hxx>
#include <Pnt2d.hxx>

namespace tnbLib
{

	namespace legLib
	{

		// Forward Declarations [2/1/2023 Payvand]

		class Aft2d_Edge;

		class Aft2d_GeoPrcsr
		{

		public:

			virtual Standard_Real BaseSize() const = 0;

			virtual Standard_Real ElementSize(const Pnt2d&) const = 0;
			virtual Standard_Real ElementSize(const Aft2d_Edge&) const = 0;

			virtual Standard_Real Oriented(const Pnt2d& theP0, const Pnt2d& theP1, const Pnt2d& theCoord) const = 0;

			virtual Standard_Real CalcUnitDistance(const Pnt2d& theP0, const Pnt2d& theP1) const = 0;
			virtual Standard_Real CalcDistance(const Pnt2d& theP0, const Pnt2d& theP1) const = 0;
			virtual Standard_Real CalcDistanceSQ(const Pnt2d& theP0, const Pnt2d& theP1) const = 0;

			virtual Standard_Real CalcDistanceFromSegment(const Pnt2d& theCoord, const Pnt2d& theP0, const Pnt2d& theP1) const = 0;
			virtual Standard_Real CalcDistanceFromSegmentSQ(const Pnt2d& theCoord, const Pnt2d& theP0, const Pnt2d& theP1) const = 0;

			virtual Pnt2d CalcOptmCoord(const Standard_Real, const Aft2d_Edge&) const = 0;
			virtual Pnt2d CalcCentre(const Pnt2d& theP0, const Pnt2d& theP1) const = 0;

			virtual Entity2d_Box CalcSearchRegion(const Standard_Real theRadius, const Pnt2d& theCentre) const = 0;
			virtual Entity2d_Box CalcSearchRegion(const Standard_Real theRadius, const Pnt2d& theCoord, const Aft2d_Edge& theEdge) const = 0;


		};
	}
}

#endif // !_Aft2d_GeoPrcsr_Header
