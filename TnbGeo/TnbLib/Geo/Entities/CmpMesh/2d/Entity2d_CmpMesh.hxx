#pragma once
#ifndef _Entity2d_CmpMesh_Header
#define _Entity2d_CmpMesh_Header

#include <Entity2d_QuadMeshFwd.hxx>
#include <Entity2d_TriangulationFwd.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Pnt2d.hxx>
#include <OFstream.hxx>

#include <memory>
#include <vector>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Entity2d_CmpConnect;

	class Entity2d_CmpMesh
	{

		/*Private Data*/

		std::vector<Pnt2d> theCoords_;
		std::vector<std::shared_ptr<Entity2d_CmpConnect>> theIndices_;

		// private functions and operators

		TNB_SERIALIZATION(TnbGeo_EXPORT);

	public:

		typedef Pnt2d ptType;
		typedef  Entity2d_CmpConnect connectType;

		static TnbGeo_EXPORT const std::string extension;

		// default constructor

		TnbGeo_EXPORT Entity2d_CmpMesh();

		// Constructors

		Entity2d_CmpMesh
		(
			const std::vector<Pnt2d>& theCoords,
			const std::vector<std::shared_ptr<Entity2d_CmpConnect>>& theIds
		)
			: theCoords_(theCoords)
			, theIndices_(theIds)
		{}

		Entity2d_CmpMesh
		(
			std::vector<Pnt2d>&& theCoords,
			std::vector<std::shared_ptr<Entity2d_CmpConnect>>&& theIds
		)
			: theCoords_(std::move(theCoords))
			, theIndices_(std::move(theIds))
		{}

		TnbGeo_EXPORT Entity2d_CmpMesh(const Entity2d_CmpMesh& theMesh);

		// Public functions and operators

		TnbGeo_EXPORT Entity2d_CmpMesh& operator=(const Entity2d_CmpMesh&);

		[[nodiscard]] const auto& Coords() const { return theCoords_; }
		[[nodiscard]] const auto& Indices() const { return theIndices_; }

		auto& CoordsRef() { return theCoords_; }
		auto& IndicesRef() { return theIndices_; }

		TnbGeo_EXPORT Standard_Integer NbElements() const;
		TnbGeo_EXPORT std::vector<Pnt2d> GetElement(const Standard_Integer theIndex) const;
		TnbGeo_EXPORT std::shared_ptr<Entity2d_Box> CalcBoundingBox() const;
		TnbGeo_EXPORT std::shared_ptr<Entity2d_CmpMesh> Copy() const;

		TnbGeo_EXPORT void Add(const Entity2d_CmpMesh&);
		TnbGeo_EXPORT void Add(const Entity2d_Triangulation&);
		TnbGeo_EXPORT void Add(const Entity2d_QuadMesh&);
		TnbGeo_EXPORT void Import(const Entity2d_Triangulation&);
		TnbGeo_EXPORT void Import(const Entity2d_QuadMesh&);

		TnbGeo_EXPORT void ExportToPlt(OFstream&) const;

		// Static functions
		
		static TnbGeo_EXPORT std::shared_ptr<Entity2d_CmpMesh> Convert(const Entity2d_Triangulation&);
		static TnbGeo_EXPORT std::shared_ptr<Entity2d_CmpMesh> Convert(const Entity2d_QuadMesh&);
		static TnbGeo_EXPORT void Merge(Entity2d_CmpMesh&, const Standard_Real theTol = 1.0e-6);
		static TnbGeo_EXPORT void CheckInverseElements(const Entity2d_CmpMesh&);
		
		
	};
}

#endif
