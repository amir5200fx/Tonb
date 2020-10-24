#pragma once
#ifndef _Cad2d_Modeler_Header
#define _Cad2d_Modeler_Header

#include <Cad2d_Modeler_Corner.hxx>
#include <Cad2d_Modeler_Counter.hxx>
#include <Cad2d_Modeler_SrchEng.hxx>
#include <Cad2d_Modeler_Segments.hxx>
#include <Cad2d_Modeler_Plane.hxx>
#include <Cad2d_Modeler_Wire.hxx>
#include <Cad2d_Modeler_Registry.hxx>
#include <Cad2d_Modeler_SelectList.hxx>
#include <Cad_EntityManager.hxx>

#include <gp.hxx>

#include <memory>
#include <map>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Edge;
	class Pln_Vertex;
	class Pln_Ring;

	class Cad2d_Modeler
		: public cad2dLib::Modeler_SrchEng
		, public cad2dLib::Modeler_Counter
		/*, public cad2dLib::Modeler_Wire*/
		, public cad2dLib::Modeler_Plane
		, public cad2dLib::Modeler_Registry
		, public cad2dLib::Modeler_Segments
	{

		typedef cad2dLib::Modeler_Corner corner;

		using cad2dLib::Modeler_SrchEng::IsNull;
		using cad2dLib::Modeler_Registry::IsContain;
		using cad2dLib::Modeler_Plane::IsContain;
		//using cad2dLib::Modeler_Wire::IsContain;
	
	public:

		typedef cad2dLib::Modeler_SelectList selctList;

	private:

		/*Private Data*/

		void RemoveVertex
		(
			const std::shared_ptr<Pln_Vertex>& theVtx
		);

		void RemoveVertex
		(
			const std::shared_ptr<Pln_Vertex>& theVtx,
			const std::shared_ptr<corner>& theCorner
		);

		void RemoveSegment
		(
			const std::shared_ptr<cad2dLib::Modeler_Segment>& theSegmnt
		);

		void RemoveRing(const std::shared_ptr<Pln_Ring>& theRing);

		std::shared_ptr<cad2dLib::Modeler_Corner>
			AddVertex
			(
				const std::shared_ptr<Pln_Vertex>& theVtx,
				const Standard_Integer theEdgeIndex
			);

		Standard_Integer
			AddEdge
			(
				const std::shared_ptr<Pln_Edge>& theEdge
			);

		Standard_Integer 
			AddRing
			(
				const std::shared_ptr<Pln_Ring>& theRing
			);

		Standard_Integer
			AddPlane
			(
				const std::shared_ptr<Cad2d_Plane>& thePlane
			);

		Standard_Integer 
			AddSegment
			(
				const std::shared_ptr<cad2dLib::Modeler_Segment>& theSegmnt
			);

		std::vector<std::shared_ptr<Pln_Edge>> MakeChain(selctList& theList);

	public:

		using cad2dLib::Modeler_Registry::IsNull;

		Cad2d_Modeler();

		Standard_Boolean HasDuplication
		(
			const std::shared_ptr<Pln_Edge>& theEdge, 
			cad2dLib::Modeler_SelectList& theList
		) const;

		//- throw an exception if found any duplication.
		//- Check consistency with the "HasDuplication" method
		void Select
		(
			const std::shared_ptr<Pln_Edge>& theEdge,
			selctList& theList
		) const;

		void SelectAll(selctList& theList) const;

		//- throw an exception if the edge is not in the tree
		//- Check consistency with the "HasDuplication" method
		void deSelect
		(
			const std::shared_ptr<Pln_Edge>& theEdge, 
			selctList& theList
		) const;

		void deSelectAll(selctList& theList) const;

		void RemoveEdge
		(
			const std::shared_ptr<Pln_Edge>& theEdge
		);

		Standard_Integer Import
		(
			const std::shared_ptr<Pln_Edge>& theEdge
		);

		Standard_Integer Import
		(
			std::shared_ptr<Pln_Edge>&& theEdge
		);

		void Import
		(
			const std::vector<std::shared_ptr<Pln_Edge>>& theEdegs
		);

		void Import
		(
			std::vector<std::shared_ptr<Pln_Edge>>&& theEdegs
		);

		void Trim
		(
			const std::shared_ptr<Pln_Edge>& theEdge0, 
			const std::shared_ptr<Pln_Edge>& theEdge1
		);

		std::vector<Standard_Integer> MakePlanes(selctList& theList, const gp_Ax2& ax = gp::XOY());

		//- the list will get empty after successfully creating plane
		Standard_Integer MakePlane(selctList& theList, const gp_Ax2& ax = gp::XOY());
	};
}

#endif // !_Cad2d_Modeler_Header
