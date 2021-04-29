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

	protected:

		//- default constructor
		Mesh2d_BoundarySizeMapTool()
		{}


		//- constructor

		Mesh2d_BoundarySizeMapTool
		(
			const std::shared_ptr<Mesh_ReferenceValues>& theRef,
			const std::shared_ptr<Cad2d_Plane>& thePlane
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

		void ImportCornerPatch(const word& patchName);
		void ImportSegmentPatch(const word& patchName);

		void RetrieveCornersTo(std::vector<std::shared_ptr<Pln_Vertex>>&) const;
		void RetrieveSegmentsTo(std::vector<std::shared_ptr<Pln_Edge>>&) const;

		std::vector<std::shared_ptr<Pln_Vertex>> RetrieveCorners() const;
		std::vector<std::shared_ptr<Pln_Edge>> RetrieveSegments() const;
	};
}

#endif // !_Mesh2d_BoundarySizeMapTool_Header
