#pragma once
#ifndef _MeshIO3d_FEA_Header
#define _MeshIO3d_FEA_Header

#include <Mesh_Module.hxx>
#include <Entity3d_TetrahedralizationFwd.hxx>
#include <Entity_Connectivity.hxx>
#include <Global_Serialization.hxx>

#include <memory>
#include <map>

namespace tnbLib
{

	class MeshIO3d_FEA
	{

		/*Private Data*/

		std::shared_ptr<Entity3d_Tetrahedralization> theMesh_;

		std::map<word, std::shared_ptr<std::vector<connectivity::triple>>> theBoundaries_;

		// Private functions and operators

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	public:

		static TnbMesh_EXPORT const std::string extension;

		// default constructor

		MeshIO3d_FEA()
		{}

		// constructors

		//- Public functions and operators

		const auto& Mesh() const { return theMesh_; }
		const auto& Boundaries() const { return theBoundaries_; }

		void SetMesh(const std::shared_ptr<Entity3d_Tetrahedralization>& theMesh) { theMesh_ = theMesh; }
		void SetMesh(std::shared_ptr<Entity3d_Tetrahedralization>&& theMesh) { theMesh_ = std::move(theMesh); }

		void SetBoundaries(const std::map<word, std::shared_ptr<std::vector<connectivity::triple>>>& theBoundaries)
		{
			theBoundaries_ = theBoundaries;
		}

		void SetBoundaries(std::map<word, std::shared_ptr<std::vector<connectivity::triple>>>&& theBoundaries)
		{
			theBoundaries_ = std::move(theBoundaries);
		}
		
	};
}

#endif // !_MeshIO3d_FEA_Header
