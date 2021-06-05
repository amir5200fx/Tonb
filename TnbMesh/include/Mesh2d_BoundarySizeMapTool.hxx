#pragma once
#ifndef _Mesh2d_BoundarySizeMapTool_Header
#define _Mesh2d_BoundarySizeMapTool_Header

#include <Mesh2d_SizeMapTool.hxx>

#include <list>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Vertex;
	class Pln_Edge;

	class Mesh2d_BoundarySizeMapTool
		: public Mesh2d_SizeMapTool
	{

		/*Private Data*/

		std::list<word> theCornerPatches_;
		std::list<word> theSegmentPatches_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Mesh2d_SizeMapTool>(*this);

			ar & theCornerPatches_;
			ar & theSegmentPatches_;
		}

	protected:

		//- default constructor
		Mesh2d_BoundarySizeMapTool()
		{}


		//- constructor

		Mesh2d_BoundarySizeMapTool
		(
			const std::shared_ptr<Cad2d_Plane>& thePlane,
			const std::shared_ptr<Mesh_ReferenceValues>& theRef
		)
			: Mesh2d_SizeMapTool(theRef, thePlane)
		{}


	public:

		auto NbCornerPatches() const
		{
			return (Standard_Integer)theCornerPatches_.size();
		}

		auto NbSegmentPatches() const
		{
			return (Standard_Integer)theSegmentPatches_.size();
		}

		const auto& CornerPatches() const
		{
			return theCornerPatches_;
		}

		const auto& SegmentPatches() const
		{
			return theSegmentPatches_;
		}

		TnbMesh_EXPORT void ImportCornerPatch(const word& patchName);
		TnbMesh_EXPORT void ImportSegmentPatch(const word& patchName);

		TnbMesh_EXPORT void RetrieveCornersTo(std::vector<std::shared_ptr<Pln_Vertex>>&) const;
		TnbMesh_EXPORT void RetrieveSegmentsTo(std::vector<std::shared_ptr<Pln_Edge>>&) const;

		TnbMesh_EXPORT std::vector<std::shared_ptr<Pln_Vertex>> RetrieveCorners() const;
		TnbMesh_EXPORT std::vector<std::shared_ptr<Pln_Edge>> RetrieveSegments() const;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Mesh2d_BoundarySizeMapTool);

#endif // !_Mesh2d_BoundarySizeMapTool_Header
