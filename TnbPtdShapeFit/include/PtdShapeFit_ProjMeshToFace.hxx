#pragma once
#ifndef _PtdShapeFit_ProjMeshToFace_Header
#define _PtdShapeFit_ProjMeshToFace_Header

#include <PtdShapeFit_Module.hxx>
#include <Entity3d_TriangulationFwd.hxx>
#include <Entity3d_PolygonFwd.hxx>
#include <Entity3d_ChainFwd.hxx>
#include <Entity_Connectivity.hxx>
#include <Pnt3d.hxx>
#include <Pnt2d.hxx>
#include <Global_Done.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	// Forward Declarations [2/18/2023 Payvand]

	class Cad_GeomSurface;
	class Entity3d_TriangulationPatch;

	class PtdShapeFit_ProjMeshToFace
		: public Global_Done
	{

	public:

		struct Node2d;

		struct Node3d
		{
			Pnt3d coord;

			std::shared_ptr<Node2d> parNode;
		};

		struct Node2d
		{
			Pnt2d coord;

			std::weak_ptr<Node3d> parent;
		};


	private:

		/*Private Data*/

		std::shared_ptr<Entity3d_Triangulation> theMesh_;
		std::shared_ptr<std::vector<connectivity::dual>> theBoundary_;
		std::shared_ptr<Cad_GeomSurface> theFace_;


		// Results [2/18/2023 Payvand]

		std::vector<std::shared_ptr<Node3d>> theNodes_;


		static TnbPtdShapeFit_EXPORT std::shared_ptr<Entity3d_Polygon> 
			GetPolygon
			(
				const std::vector<Pnt3d>&, 
				const std::vector<connectivity::dual>&
			);

		static TnbPtdShapeFit_EXPORT std::vector<std::shared_ptr<Node3d>> 
			GetNodes
			(
				const Entity3d_Polygon&
			);

	public:

		// default constructor [2/18/2023 Payvand]

		PtdShapeFit_ProjMeshToFace()
		{}


		// constructors [2/18/2023 Payvand]


		// Public functions and operators [2/18/2023 Payvand]

		const auto& Mesh() const
		{
			return theMesh_;
		}

		const auto& Boundary() const
		{
			return theBoundary_;
		}

		const auto& Face() const
		{
			return theFace_;
		}

		const auto& Projected() const
		{
			return theNodes_;
		}

		TnbPtdShapeFit_EXPORT void Perform();

		void SetMesh(const std::shared_ptr<Entity3d_Triangulation>& theMesh)
		{
			theMesh_ = theMesh;
		}

		void SetBoundary(const std::shared_ptr<std::vector<connectivity::dual>>& theBoundary)
		{
			theBoundary_ = theBoundary;
		}

		void SetFace(const std::shared_ptr<Cad_GeomSurface>& theFace)
		{
			theFace_ = theFace;
		}

	};
}

#endif // !_PtdShapeFit_ProjMeshToFace_Header
