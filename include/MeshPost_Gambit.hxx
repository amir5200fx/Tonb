#pragma once
#ifndef _MeshPost_Gambit_Header
#define _MeshPost_Gambit_Header

#include <MeshPost_Module.hxx>
#include <Geo3d_FVMeshFwd.hxx>
#include <Global_TypeDef.hxx>
#include <OFstream.hxx>

#include <string>
#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations [8/15/2023 aamir]

	class MeshPost_Gambit
	{

	public:

		enum DataType
		{
			node = 0,
			elementOrCell
		};

		enum BoundaryEntityType
		{
			UNSPECIFIED = 0,
			AXIS,
			CONJUGATE,
			CONVECTION,
			CYCLIC,
			DEAD,
			ELEMENT_SIDE,
			ESPECIES,
			EXHAUST_FAN,
			FAN,
			FREE_SURFACE,
			GAP,
			INFLOW,
			INLET,
			INLET_VENT,
			INTAKE_FAN,
			INTERFACE,
			INTERIOR,
			INTERNAL,
			LIVE,
			MASS_FLOW_INLET,
			MELT,
			MELT_INTERFACE,
			MOVING_BOUNDARY,
			NODE,
			OUTFLOW,
			OUTLET,
			OUTLET_VENT,
			PERIODIC,
			PLOT,
			POROUS,
			POROUS_JUMP,
			PRESSURE,
			PRESSURE_FAR_FIELD,
			PRESSURE_INFLOW,
			PRESSURE_INLET,
			PRESSURE_OUTFLOW,
			PRESSURE_OUTLET,
			RADIATION,
			RADIATOR,
			RECIRCULATION_INLET,
			RECIRCULATION_OUTLET,
			SLIP,
			SREACTION,
			SURFACE,
			SYMMETRY,
			TRACTION,
			TRAJECTORY,
			VELOCITY,
			VELOCITY_INLET,
			VENT,
			WALL,
			SPRING
		};

		enum ElemenetGeomType
		{
			Edge = 1,
			Quadrilateral,
			Triangle,
			Brick,
			Wedge,
			Tetrahedron,
			Pyramid
		};

		enum MaterailType
		{
			Undefined = 0,
			Conjugate,
			Fluid,
			Porous,
			Solid,
			Deformable
		};

	private:

		/*Private Data*/

		std::shared_ptr<Geo3d_FVMesh> theMesh_;

		// Private functions and operators [8/14/2023 aamir]

		std::string theTitle_;

		TnbMeshPost_EXPORT void WriteHeader(OFstream&) const;
		TnbMeshPost_EXPORT void WriteCoordinates(OFstream&) const;
		TnbMeshPost_EXPORT void WriteElements(OFstream&) const;
		TnbMeshPost_EXPORT void WriteGroups(OFstream&) const;
		TnbMeshPost_EXPORT void WriteBoundaries(OFstream&) const;

	public:

		// default constructor [8/14/2023 aamir]

		MeshPost_Gambit()
		{}

		// constructors [8/14/2023 aamir]


		// Public functions and operators [8/14/2023 aamir]

		const auto& Mesh() const { return theMesh_; }
		
		TnbMeshPost_EXPORT void Perform(const std::string& theName);

		void SetMesh(const std::shared_ptr<Geo3d_FVMesh>& theMesh) { theMesh_ = theMesh; }
		void SetMesh(std::shared_ptr<Geo3d_FVMesh>&& theMesh) { theMesh_ = std::move(theMesh); }

		static TnbMeshPost_EXPORT std::vector<Standard_Integer> 
			ConnectivityMatrix(const std::vector<Standard_Integer>& theIndices);
	};
}

#endif // !_MeshPost_Gambit_Header
