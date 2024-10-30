#pragma once
#ifndef _Entity3d_CmpMesh_Header
#define _Entity3d_CmpMesh_Header

#include <Entity3d_HexahedralizationFwd.hxx>
#include <Entity3d_TetrahedralizationFwd.hxx>
#include <Entity3d_BoxFwd.hxx>
#include <Pnt3d.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Entity3d_CmpConnect;

	class Entity3d_CmpMesh
	{

		/*Private Data*/

		std::vector<Pnt3d> theCoords_;
		std::vector<std::shared_ptr<Entity3d_CmpConnect>> theIndices_;

		// Private functions and operators

	public:

		typedef Pnt3d ptType;
		typedef std::shared_ptr<Entity3d_CmpConnect> connectType;

		static TnbGeo_EXPORT const std::string extension;

		// default constructor

		TnbGeo_EXPORT Entity3d_CmpMesh();

		// constructors

		Entity3d_CmpMesh
		(
			std::vector<Pnt3d> theCoords,
			std::vector<std::shared_ptr<Entity3d_CmpConnect>> theIds
		)
			: theCoords_(std::move(theCoords))
			, theIndices_(std::move(theIds))
		{}

		TnbGeo_EXPORT Entity3d_CmpMesh(const Entity3d_CmpMesh& theMesh);
		TnbGeo_EXPORT Entity3d_CmpMesh(Entity3d_CmpMesh&& other) noexcept;


		// Public functions and operators

		TnbGeo_EXPORT Entity3d_CmpMesh& operator=(const Entity3d_CmpMesh&);
		TnbGeo_EXPORT Entity3d_CmpMesh& operator=(Entity3d_CmpMesh&& other) noexcept;

		const auto& Coords() const { return theCoords_; }
		const auto& Points() const { return theCoords_; }
		auto& Points() { return theCoords_; }
		const auto& Indices() const { return theIndices_; }
		const auto& Connectivity() const { return theIndices_; }
		auto& Connectivity() { return theIndices_; }

		auto& CoordsRef() { return theCoords_; }
		auto& IndicesRef() { return theIndices_; }

		TnbGeo_EXPORT Standard_Integer NbElements() const;
		TnbGeo_EXPORT std::vector<Pnt3d> GetElement(const Standard_Integer theIndex) const;
		TnbGeo_EXPORT std::shared_ptr<Entity3d_Box> CalcBoundingBox() const;
		TnbGeo_EXPORT std::shared_ptr<Entity3d_CmpMesh> Copy() const;

		// Warning: You may consider the fact that if the mesh has elements other than tetrahedron it's
		// going to throw an exception
		TnbGeo_EXPORT std::shared_ptr<Entity3d_Tetrahedralization> ExportAsTetrahedral() const;
		// Warning: It doesn't support Pyramid shape elements. For other type of elements other than hexahedron
		// it produces degenerated hexahedrons.
		// This function is usually used for displaying purposes not as a computational tasks.
		TnbGeo_EXPORT std::shared_ptr<Entity3d_Hexahedralization> ExportAsHexahedral() const;

		TnbGeo_EXPORT void Add(const Entity3d_CmpMesh&);
		TnbGeo_EXPORT void Add(const Entity3d_Tetrahedralization&);
		// It's going to erase the old data
		TnbGeo_EXPORT void Import(const Entity3d_CmpMesh&);
		TnbGeo_EXPORT void Import(const Entity3d_Tetrahedralization&);

		TnbGeo_EXPORT void ExportToPlt(OFstream&) const;
		TnbGeo_EXPORT void ExportToPlt(std::fstream&) const;
		TnbGeo_EXPORT void ExportToVtk(OFstream&) const;
		TnbGeo_EXPORT void ExportToVtk(std::fstream&) const;

		// Static functions
		static TnbGeo_EXPORT std::shared_ptr<Entity3d_CmpMesh> Convert(const Entity3d_Tetrahedralization&);
		static TnbGeo_EXPORT void Merge(Entity3d_CmpMesh&, const Standard_Real theTot = 1.e-6);
		static TnbGeo_EXPORT void CheckInverseElements(const Entity3d_CmpMesh&);
	};
}

#endif