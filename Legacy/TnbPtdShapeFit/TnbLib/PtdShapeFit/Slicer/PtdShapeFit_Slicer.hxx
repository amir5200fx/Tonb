#pragma once
#ifndef _PtdShapeFit_Slicer_Header
#define _PtdShapeFit_Slicer_Header

#include <Entity3d_TriangulationFwd.hxx>
#include <Global_Done.hxx>

#include <memory>

#include <TopoDS_Face.hxx>

namespace tnbLib
{

	// Forward Declarations [2/19/2023 Payvand]
	class Entity3d_TriangulationPatch;

	class PtdShapeFit_Slicer
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<Entity3d_TriangulationPatch> theMesh_;
		TopoDS_Face theFace_;

		// Results [2/19/2023 Payvand]

		std::shared_ptr<Entity3d_Triangulation> thePatch_;

	public:

		// default constructor [2/18/2023 Payvand]

		PtdShapeFit_Slicer()
		{}

		// Constructors [2/19/2023 Payvand]


		// Public functions and operators [2/19/2023 Payvand]

		const auto& Mesh() const
		{
			return theMesh_;
		}

		const auto& Face() const
		{
			return theFace_;
		}

		const auto& Cut() const
		{
			return thePatch_;
		}

		void Perform();

		void SetMesh(const std::shared_ptr<Entity3d_TriangulationPatch>& theMesh)
		{
			theMesh_ = theMesh;
		}

		void SetFace(const TopoDS_Face& theFace)
		{
			theFace_ = theFace;
		}

	};
}

#endif // !_PtdShapeFit_Slicer_Header
