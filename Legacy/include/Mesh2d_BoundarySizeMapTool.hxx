#pragma once
#ifndef _Mesh2d_BoundarySizeMapTool_Header
#define _Mesh2d_BoundarySizeMapTool_Header

#include <Mesh2d_SizeMapTool.hxx>

#include <set>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Vertex;
	class Pln_Edge;

	class Mesh2d_BoundarySizeMapTool
		: public Mesh2d_SizeMapTool
	{

		/*Private Data*/

		std::set<word> thePatches_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Mesh2d_SizeMapTool>(*this);

			ar& thePatches_;
		}

	protected:

		//- default constructor
		Mesh2d_BoundarySizeMapTool()
		{}


		//- constructor

		Mesh2d_BoundarySizeMapTool
		(
			const std::shared_ptr<Cad2d_Plane>& thePlane,
			const std::shared_ptr<Entity2d_Box>& theDomain,
			const std::shared_ptr<Mesh2d_ReferenceValues>& theRef
		)
			: Mesh2d_SizeMapTool(theRef, theDomain, thePlane)
		{}


	public:


		// Public functions and operators [6/23/2023 Payvand]
		
		auto NbPatches() const
		{
			return (Standard_Integer)thePatches_.size();
		}

		const auto& Patches() const
		{
			return thePatches_;
		}

		TnbMesh_EXPORT void ImportPatch(const word& patchName);
		TnbMesh_EXPORT void RemovePatch(const word& patchName);
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Mesh2d_BoundarySizeMapTool);

#endif // !_Mesh2d_BoundarySizeMapTool_Header
