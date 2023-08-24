#pragma once
#ifndef _MeshIO3d_PentaFEA_Header
#define _MeshIO3d_PentaFEA_Header

#include <Mesh_Module.hxx>
#include <Entity3d_PentahedralizationFwd.hxx>
#include <Entity_Connectivity.hxx>
#include <Global_Serialization.hxx>

#include <memory>
#include <map>

namespace tnbLib
{

	class MeshIO3d_PentaFEA
	{

		/*Private Data*/

		std::shared_ptr<Entity3d_Pentahedrolization> theMesh_;
		std::map<word, std::shared_ptr<std::vector<connectivity::quadruple>>> theBoundaries_;

		// Private functions and operators [8/11/2023 aamir]

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	public:

		static TnbMesh_EXPORT const std::string extension;

		// default constructor [8/11/2023 aamir]

		MeshIO3d_PentaFEA()
		{}

		// constructors [8/11/2023 aamir]


		// Public functions and operators [8/11/2023 aamir]

		const auto& Mesh() const { return theMesh_; }
		const auto& Boundaries() const { return theBoundaries_; }

		void SetMesh(const std::shared_ptr<Entity3d_Pentahedrolization>& theMesh) { theMesh_ = theMesh; }
		void SetMesh(std::shared_ptr<Entity3d_Pentahedrolization>&& theMesh) { theMesh_ = std::move(theMesh); }

		void SetBoundaries(const std::map<word, std::shared_ptr<std::vector<connectivity::quadruple>>>& theBoundaries)
		{
			theBoundaries_ = theBoundaries;
		}

		void SetBoundaries(std::map<word, std::shared_ptr<std::vector<connectivity::quadruple>>>&& theBoundaries)
		{
			theBoundaries_ = std::move(theBoundaries);
		}

	};
}

#endif // !_MeshIO3d_PentaFEA_Header
