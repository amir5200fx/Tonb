#pragma once
#ifndef _MeshPost_IdeasUNV_Header
#define _MeshPost_IdeasUNV_Header

#include <MeshPost_Module.hxx>
#include <Geo3d_FVMeshFwd.hxx>
#include <Global_TypeDef.hxx>
#include <OFstream.hxx>

#include <string>
#include <memory>
#include <vector>
#include <fstream>

namespace tnbLib
{

	// Forward Declarations [8/17/2023 aamir]
	class Geo_ElemGeom;

	class MeshPost_IdeasUNV
	{

	public:

		enum class System
		{
			SI = 1,
			BG,
			MG,
			BA,
			MM,
			CM,
			IN,
			GM,
			US,
			MN
		};

	private:

		/*Private Data*/

		std::shared_ptr<Geo3d_FVMesh> theMesh_;

		System theSystem_;

		// Private functions and operators [8/17/2023 aamir]

		TnbMeshPost_EXPORT void WriteHeader(std::fstream&) const;
		TnbMeshPost_EXPORT void WriteHeader(std::stringstream&) const;
		TnbMeshPost_EXPORT void WriteCoordinates(std::fstream&) const;
		TnbMeshPost_EXPORT void WriteCoordinates(std::stringstream&) const;
		TnbMeshPost_EXPORT void WriteElements(std::fstream&) const;
		TnbMeshPost_EXPORT void WriteElements(std::stringstream&) const;
		//void WriteGroups(OFstream&) const;
		//void WriteBoundaries(OFstream&) const;

		TnbMeshPost_EXPORT void WriteElement(const std::shared_ptr<Geo_ElemGeom>&, std::fstream&) const;
		TnbMeshPost_EXPORT void WriteElement(const std::shared_ptr<Geo_ElemGeom>&, std::stringstream&) const;


	public:

		// default constructor [8/17/2023 aamir]

		MeshPost_IdeasUNV()
			: theSystem_(System::SI)
		{}

		// constructors [8/17/2023 aamir]


		// Public functions and operators [8/17/2023 aamir]

		auto GetSystem() const { return theSystem_; }
		const auto& Mesh() const { return theMesh_; }

		TnbMeshPost_EXPORT void Perform(const std::string& theName);
		TnbMeshPost_EXPORT void Perform(std::stringstream& theStream);

		void SetMesh(const std::shared_ptr<Geo3d_FVMesh>& theMesh) { theMesh_ = theMesh; }
		void SetMesh(std::shared_ptr<Geo3d_FVMesh>&& theMesh) { theMesh_ = std::move(theMesh); }

	};
}

#endif // !_MeshPost_IdeasUNV_Header
