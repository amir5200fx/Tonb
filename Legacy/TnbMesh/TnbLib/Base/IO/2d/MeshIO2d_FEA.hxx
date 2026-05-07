#pragma once
#ifndef _MeshIO2d_FEA_Header
#define _MeshIO2d_FEA_Header

#include <Mesh_Module.hxx>
#include <Entity2d_TriangulationFwd.hxx>
#include <Entity_Connectivity.hxx>
#include <Global_Serialization.hxx>

#include <memory>
#include <map>

namespace tnbLib
{

	// Forward Delarations
	class Entity2d_CmpMesh;

	class MeshIO2d_FEA
	{

		/*Private Data*/

		std::shared_ptr<Entity2d_CmpMesh> theMesh_;
		
		std::map<word, std::shared_ptr<std::vector<connectivity::dual>>> theBoundaries_;


		// Private functions and operators [7/4/2023 Payvand]

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	public:

		static TnbMesh_EXPORT const std::string extension;

		// default constructor [7/4/2023 Payvand]

		TnbMesh_EXPORT MeshIO2d_FEA();

		// constructors [7/4/2023 Payvand]

		// Public functions and operators [7/4/2023 Payvand]

		const auto& Mesh() const { return theMesh_; }
		const auto& Boundaries() const { return theBoundaries_; }
		
		void SetMesh(const std::shared_ptr<Entity2d_CmpMesh>& theMesh) { theMesh_ = theMesh; }
		void SetMesh(std::shared_ptr<Entity2d_CmpMesh>&& theMesh) { theMesh_ = std::move(theMesh); }

		void SetBoundaries(const std::map<word, std::shared_ptr<std::vector<connectivity::dual>>>& theBoundaries)
		{
			theBoundaries_ = theBoundaries;
		}

		void SetBoundaries(std::map<word, std::shared_ptr<std::vector<connectivity::dual>>>&& theBoundaries)
		{
			theBoundaries_ = std::move(theBoundaries);
		}

	};
}

#endif // !_MeshIO2d_FEA_Header
