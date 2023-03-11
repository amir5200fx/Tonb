#pragma once
#ifndef _Aft3d_GeoPrcsr_Header
#define _Aft3d_GeoPrcsr_Header

#include <Entity3d_BoxFwd.hxx>
#include <Pnt3d.hxx>

#include <memory>

namespace tnbLib
{

	namespace legLib
	{

		// Forward Declarations [2/26/2023 Payvand]

		class Aft3d_Facet;

		class Aft3d_GeoPrcsr
		{

			/*Private Data*/

			std::shared_ptr<Entity3d_Box> theDomain_;

		protected:

			// default constructor [3/1/2023 Payvand]

			Aft3d_GeoPrcsr()
			{}

			// constructors [3/1/2023 Payvand]

			explicit Aft3d_GeoPrcsr(const std::shared_ptr<Entity3d_Box>& theDomain)
				: theDomain_(theDomain)
			{}

			Aft3d_GeoPrcsr(std::shared_ptr<Entity3d_Box>&& theDomain)
				: theDomain_(std::move(theDomain))
			{}

		public:


			// constructors [3/1/2023 Payvand]


			// public functions and operators [3/1/2023 Payvand]

			const auto& Domain() const { return theDomain_; }

			virtual Standard_Real BaseSize() const = 0;
			virtual Standard_Real DimSize() const = 0;

			virtual Standard_Real ElementSize(const Pnt3d&) const = 0;
			virtual Standard_Real ElementSize(const Aft3d_Facet&) const = 0;

			virtual Standard_Real Oriented(const Pnt3d& theP0, const Pnt3d& theP1, const Pnt3d& theP2, const Pnt3d& theCoord) const = 0;

			virtual Standard_Real CalcSquareDistance(const Pnt3d& theP0, const Pnt3d& theP1) const = 0;
			virtual Standard_Real CalcDistance(const Pnt3d& theP0, const Pnt3d& theP1) const = 0;

			virtual Standard_Real CalcDistanceFromTriangle(const Pnt3d& theCoord, const Pnt3d& theP0, const Pnt3d& theP1, const Pnt3d& theP2) const = 0;
			virtual Standard_Real CalcSquareDistanceFromTriangle(const Pnt3d& theCoord, const Pnt3d& theP0, const Pnt3d& theP1, const Pnt3d& theP2) const = 0;

			virtual Standard_Real CalcDistanceEdgeFromEdge(const Pnt3d& theP0, const Pnt3d& theP1, const Pnt3d& theQ0, const Pnt3d& theQ1) const = 0;
			virtual Standard_Real CalcSquareDistanceEdgeFromEdge(const Pnt3d& theP0, const Pnt3d& theP1, const Pnt3d& theQ0, const Pnt3d& theQ1) const = 0;

			virtual Entity3d_Box CalcSearchingRegion(const Standard_Real theRadius, const Pnt3d&) const = 0;
			virtual Entity3d_Box CalcSearchingRegion(const Standard_Real theRadius, const Pnt3d&, const Aft3d_Facet&) const = 0;
			virtual Entity3d_Box CalcSearchingRegion(const Standard_Real theRadius, const Aft3d_Facet&) const = 0;
			virtual Entity3d_Box CalcEffectiveFront(const Standard_Real theRadius, const Pnt3d&, const Aft3d_Facet&) const = 0;
		};
	}
}

#endif // !_Aft3d_GeoPrcsr_Header
