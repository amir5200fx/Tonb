#pragma once
#ifndef _Mesh3d_BoundarySizeMapTool_Header
#define _Mesh3d_BoundarySizeMapTool_Header

#include <Mesh3d_SizeMapTool.hxx>

#include <set>

namespace tnbLib
{

	// Forward Declarations [6/23/2022 Amir]
	class TModel_Vertex;
	class TModel_Paired;
	class TModel_Surface;

	class Mesh3d_BoundarySizeMapTool
		: public Mesh3d_SizeMapTool
	{

	public:

		using Mesh3d_SizeMapTool::boxType;

	private:

		/*Private Data*/

		std::set<word> thePatches_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Mesh3d_SizeMapTool>(*this);

			ar & thePatches_;
		}

	protected:

		// default constructor [6/23/2022 Amir]

		Mesh3d_BoundarySizeMapTool()
		{}


		// constructors [6/23/2022 Amir]

		Mesh3d_BoundarySizeMapTool
		(
			const std::shared_ptr<Cad_TModel>& theModel, 
			const std::shared_ptr<Entity3d_Box>& theDomain,
			const std::shared_ptr<Mesh3d_ReferenceValues>& theRef
		)
			: Mesh3d_SizeMapTool(theRef, theDomain, theModel)
		{}

	public:

		// public functions and operators [6/23/2022 Amir]

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

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Mesh3d_BoundarySizeMapTool);

#endif // !_Mesh3d_BoundarySizeMapTool_Header
