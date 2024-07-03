#pragma once
#ifndef _Aft2d_UniSizeGeoPrcsr_Header
#define _Aft2d_UniSizeGeoPrcsr_Header

#include <Aft2d_GeoPrcsr.hxx>

namespace tnbLib
{

	namespace legLib
	{

		class Aft2d_UniSizeGeoPrcsr
			: public Aft2d_GeoPrcsr
		{

			/*Private Data*/

			Standard_Real theSize_;

		public:

			Standard_Real BaseSize() const override;

			Standard_Real ElementSize(const Pnt2d&) const override;
			Standard_Real ElementSize(const Aft2d_Edge&) const override;

			Standard_Real Oriented(const Pnt2d& theCoord, const Pnt2d& theP0, const Pnt2d& theP1) const override;

			Standard_Real CalcUnitDistance(const Pnt2d& theP0, const Pnt2d& theP1) const override;
			Standard_Real CalcDistance(const Pnt2d& theP0, const Pnt2d& theP1) const override;
			Standard_Real CalcDistanceSQ(const Pnt2d& theP0, const Pnt2d& theP1) const override;

			Standard_Real CalcDistanceFromSegment(const Pnt2d& theCoord, const Pnt2d& theP0, const Pnt2d& theP1) const override;
			Standard_Real CalcDistanceFromSegmentSQ(const Pnt2d& theCoord, const Pnt2d& theP0, const Pnt2d& theP1) const override;

			Pnt2d CalcOptmCoord(const Standard_Real, const Aft2d_Edge&) const = 0;
			Pnt2d CalcCentre(const Pnt2d& theP0, const Pnt2d& theP1) const = 0;

			Entity2d_Box CalcSearchRegion(const Standard_Real theRadius, const Pnt2d& theCentre) const override;
			Entity2d_Box CalcSearchRegion(const Standard_Real theRadius, const Pnt2d& theCentre, const Aft2d_Edge& theEdge) const override;
		};
	}
}

#endif // !_Aft2d_UniSizeGeoPrcsr_Header
