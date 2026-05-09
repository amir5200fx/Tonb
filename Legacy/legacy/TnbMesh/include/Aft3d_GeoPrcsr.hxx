#pragma once
#ifndef _Aft3d_GeoPrcsr_Header
#define _Aft3d_GeoPrcsr_Header
#include <Mesh_Module.hxx>
#include <Entity3d_BoxFwd.hxx>
#include <Pnt3d.hxx>

#include <memory>

namespace tnbLib
{

	namespace legLib
	{

		// Forward Declarations [2/26/2023 Payvand]
		class Aft3d_Facet;
		class Aft3d_SizeFun;

		class Aft3d_GeoPrcsr
		{
			/*Private Data*/
			std::shared_ptr<Aft3d_SizeFun> theSizeFun_;
		protected:
			

		public:

			// constructors [3/1/2023 Payvand]
			Aft3d_GeoPrcsr(std::shared_ptr<Aft3d_SizeFun> theSizeFun)
				: theSizeFun_(std::move(theSizeFun))
			{}

			// public functions and operators [3/1/2023 Payvand]

			TnbLegMesh_EXPORT const std::shared_ptr<Entity3d_Box>& Domain() const;
			TnbLegMesh_EXPORT Standard_Real DimSize() const;
			const auto& SizeFun() const { return theSizeFun_; }

			TnbLegMesh_EXPORT virtual Standard_Real ElementSize(const Pnt3d&) const;
			TnbLegMesh_EXPORT virtual Standard_Real ElementSize(const Aft3d_Facet&) const;

			TnbLegMesh_EXPORT virtual Standard_Real Oriented(const Pnt3d& theP0, const Pnt3d& theP1, const Pnt3d& theP2,
			                                                 const Pnt3d& theCoord) const;

			TnbLegMesh_EXPORT virtual Standard_Real CalcSquareDistance(const Pnt3d& theP0, const Pnt3d& theP1) const;
			TnbLegMesh_EXPORT virtual Standard_Real CalcDistance(const Pnt3d& theP0, const Pnt3d& theP1) const;

			TnbLegMesh_EXPORT virtual Pnt3d CalcCentre(const Pnt3d& theP0, const Pnt3d& theP1, const Pnt3d& theP2) const;

			TnbLegMesh_EXPORT virtual Standard_Real CalcDistanceFromTriangle(
				const Pnt3d& theCoord, const Pnt3d& theP0, const Pnt3d& theP1, const Pnt3d& theP2) const;
			TnbLegMesh_EXPORT virtual Standard_Real CalcSquareDistanceFromTriangle(
				const Pnt3d& theCoord, const Pnt3d& theP0, const Pnt3d& theP1, const Pnt3d& theP2) const;

			TnbLegMesh_EXPORT virtual Standard_Real CalcDistanceEdgeFromEdge(
				const Pnt3d& theP0, const Pnt3d& theP1, const Pnt3d& theQ0, const Pnt3d& theQ1) const;
			TnbLegMesh_EXPORT virtual Standard_Real CalcSquareDistanceEdgeFromEdge(
				const Pnt3d& theP0, const Pnt3d& theP1, const Pnt3d& theQ0, const Pnt3d& theQ1) const;

			TnbLegMesh_EXPORT virtual Entity3d_Box CalcSearchingRegion(const Standard_Real theRadius, const Pnt3d&) const;
			TnbLegMesh_EXPORT virtual Entity3d_Box CalcSearchingRegion(const Standard_Real theRadius, const Pnt3d&, const Aft3d_Facet&) const;
			TnbLegMesh_EXPORT virtual Entity3d_Box CalcSearchingRegion(const Standard_Real theRadius, const Aft3d_Facet&) const;
			TnbLegMesh_EXPORT virtual Entity3d_Box CalcEffectiveFront(const Standard_Real theRadius, const Pnt3d&, const Aft3d_Facet&) const;
		};
	}
}

#endif // !_Aft3d_GeoPrcsr_Header
