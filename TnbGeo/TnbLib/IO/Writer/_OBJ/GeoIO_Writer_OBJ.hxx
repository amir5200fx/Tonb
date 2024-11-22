#pragma once
#ifndef _GeoIO_Writer_OBJ_Header
#define _GeoIO_Writer_OBJ_Header

#include <Entity3d_TriangulationFwd.hxx>
#include <Global_TypeDef.hxx>
#include <word.hxx>

#include <memory>

namespace tnbLib
{

	class GeoIO_Writer_OBJ
	{

	public:

		struct ElmSet 
		{
			std::string name;
			std::vector<Standard_Integer> elements;
		};

		struct MTLLib
		{
			std::string name;
		};

	private:

		/*Private Data*/

		std::shared_ptr<Entity3d_Triangulation> theMesh_;
		std::vector<std::shared_ptr<ElmSet>> theSets_;
		std::shared_ptr<MTLLib> theMtl_;

	public:

		// default constructor [9/6/2023 aamir]

		GeoIO_Writer_OBJ()
		{}

		// constructors [9/6/2023 aamir]

		GeoIO_Writer_OBJ
		(
			const std::shared_ptr<Entity3d_Triangulation>& theMesh,
			const std::vector<std::shared_ptr<ElmSet>>& theSets, 
			const std::shared_ptr<MTLLib>& theMtl
		)
			: theMesh_(theMesh)
			, theSets_(theSets)
			, theMtl_(theMtl)
		{}

		// Public functions and operators [9/6/2023 aamir]

		const auto& Mesh() const { return theMesh_; }
		const auto& Sets() const { return theSets_; }
		const auto& Mtl() const { return theMtl_; }

		void Perform(const std::string&);

		void SetMesh(const std::shared_ptr<Entity3d_Triangulation>& theMesh) { theMesh_ = theMesh; }
		void SetSets(const std::vector<std::shared_ptr<ElmSet>>& theSets) { theSets_ = theSets; }
		void SetMtl(const std::shared_ptr<MTLLib>& theMtl) { theMtl_ = theMtl; }

	};

}

#endif // !_GeoIO_Writer_OBJ_Header
