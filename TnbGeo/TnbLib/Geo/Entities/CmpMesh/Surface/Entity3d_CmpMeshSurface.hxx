#pragma once
#ifndef _Entity3d_CmpMeshSurface_Header
#define _Entity3d_CmpMeshSurface_Header

#include <Entity3d_BoxFwd.hxx>
#include <Pnt3d.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{
	// Forward Declarations
	class Entity2d_CmpConnect;

	class Entity3d_CmpMeshSurface
	{
		/*Private Data*/
		std::vector<Pnt3d> theCoords_;
		std::vector<std::shared_ptr<Entity2d_CmpConnect>> theIndices_;

		// Private functions and operators
	public:
		// default constructor
		Entity3d_CmpMeshSurface() = default;

		// constructors
		Entity3d_CmpMeshSurface
		(
			const std::vector<Pnt3d>& theCoords, 
			const std::vector<std::shared_ptr<Entity2d_CmpConnect>>& theIds
		)
			: theCoords_(theCoords)
			, theIndices_(theIds)
		{}
		Entity3d_CmpMeshSurface
		(
			std::vector<Pnt3d>&& theCoords,
			std::vector<std::shared_ptr<Entity2d_CmpConnect>>&& theIds
		)
			: theCoords_(std::move(theCoords))
			, theIndices_(std::move(theIds))
		{}

		// Public functions and operators
		const auto& Coords() const { return theCoords_; }
		const auto& Indices() const { return theIndices_; }

		auto& CoordsRef() { return theCoords_; }
		auto& IndicesRef() { return theIndices_; }

		TnbGeo_EXPORT Standard_Integer NbPoints() const;
		TnbGeo_EXPORT Standard_Integer NbElements() const;
		TnbGeo_EXPORT std::vector<Pnt3d> GetElement(const Standard_Integer theIndex) const;
		TnbGeo_EXPORT std::shared_ptr<Entity3d_Box> CalcBoundingBox() const;
		TnbGeo_EXPORT std::shared_ptr<Entity3d_CmpMeshSurface> Copy() const;

		TnbGeo_EXPORT void Add(const Entity3d_CmpMeshSurface&);
		void Import(const Entity3d_CmpMeshSurface&);

		TnbGeo_EXPORT void ExportToPlt(OFstream&) const;
		TnbGeo_EXPORT void ExportToVtk(std::fstream&) const;

	};
}

#endif