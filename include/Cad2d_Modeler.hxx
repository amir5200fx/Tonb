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
	class Pln_Segment;
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


		//- private functions and operators

		TNB_SERIALIZATION(TnbCad2d_EXPORT);
	
	public:

		typedef cad2dLib::Modeler_SelectList selctList;

		static TnbCad2d_EXPORT unsigned short verbose;

	private:

		/*Private Data*/

		TnbCad2d_EXPORT void RemoveVertex
		(
			const std::shared_ptr<Pln_Vertex>& theVtx
		);

		TnbCad2d_EXPORT void RemoveVertex
		(
			const std::shared_ptr<Pln_Vertex>& theVtx,
			const std::shared_ptr<corner>& theCorner
		);

		TnbCad2d_EXPORT void RemoveSegment
		(
			const std::shared_ptr<cad2dLib::Modeler_Segment>& theSegmnt
		);

		TnbCad2d_EXPORT void RemoveRing(const std::shared_ptr<Pln_Ring>& theRing);

		TnbCad2d_EXPORT std::shared_ptr<cad2dLib::Modeler_Corner>
			AddVertex
			(
				const std::shared_ptr<Pln_Vertex>& theVtx,
				const Standard_Integer theEdgeIndex
			);

		TnbCad2d_EXPORT Standard_Integer
			AddEdge
			(
				const std::shared_ptr<Pln_Segment>& theEdge
			);

		TnbCad2d_EXPORT Standard_Integer
			AddRing
			(
				const std::shared_ptr<Pln_Ring>& theRing
			);

		TnbCad2d_EXPORT Standard_Integer
			AddPlane
			(
				const std::shared_ptr<Cad2d_Plane>& thePlane
			);

		TnbCad2d_EXPORT Standard_Integer
			AddPlane
			(
				std::shared_ptr<Cad2d_Plane>&& thePlane
			);

		TnbCad2d_EXPORT Standard_Integer
			AddSegment
			(
				const std::shared_ptr<cad2dLib::Modeler_Segment>& theSegmnt
			);

		TnbCad2d_EXPORT std::vector<std::shared_ptr<Pln_Edge>> MakeChain(selctList& theList);

		TnbCad2d_EXPORT virtual void
			CheckCurveType
			(
				const std::shared_ptr<Pln_Edge>& theEdge,
				const char* name
			) const;

	public:

		using cad2dLib::Modeler_Registry::IsNull;

		TnbCad2d_EXPORT Cad2d_Modeler();

		TnbCad2d_EXPORT Standard_Boolean HasDuplication
		(
			const std::shared_ptr<Pln_Edge>& theEdge, 
			cad2dLib::Modeler_SelectList& theList
		) const;

		//- throw an exception if found any duplication.
		//- Check consistency with the "HasDuplication" method
		TnbCad2d_EXPORT void Select
		(
			const std::shared_ptr<Pln_Edge>& theEdge,
			selctList& theList
		) const;

		TnbCad2d_EXPORT void SelectAll(selctList& theList) const;

		//- throw an exception if the edge is not in the tree
		//- Check consistency with the "HasDuplication" method
		TnbCad2d_EXPORT void deSelect
		(
			const std::shared_ptr<Pln_Edge>& theEdge, 
			selctList& theList
		) const;

		TnbCad2d_EXPORT void deSelectAll(selctList& theList) const;

		TnbCad2d_EXPORT void RemoveEdge
		(
			const std::shared_ptr<Pln_Edge>& theEdge
		);

		TnbCad2d_EXPORT Standard_Integer Import
		(
			const std::shared_ptr<Pln_Edge>& theEdge
		);

		/*TnbCad2d_EXPORT Standard_Integer Import
		(
			std::shared_ptr<Pln_Edge>&& theEdge
		);*/

		TnbCad2d_EXPORT void Import
		(
			const std::vector<std::shared_ptr<Pln_Edge>>& theEdegs
		);

		/*TnbCad2d_EXPORT void Import
		(
			std::vector<std::shared_ptr<Pln_Edge>>&& theEdegs
		);*/

		TnbCad2d_EXPORT void Trim
		(
			const std::shared_ptr<Pln_Edge>& theEdge0, 
			const std::shared_ptr<Pln_Edge>& theEdge1
		);

		TnbCad2d_EXPORT std::pair<Standard_Boolean, Standard_Integer>
			Union
			(
				const Standard_Integer plnId0, 
				const Standard_Integer plnId1
			);

		TnbCad2d_EXPORT std::pair<Standard_Boolean, std::vector<Standard_Integer>>
			Subtract
			(
				const Standard_Integer plnId0, 
				const Standard_Integer plnId1
			);

		TnbCad2d_EXPORT std::pair<Standard_Boolean, std::vector<Standard_Integer>>
			Intersection
			(
				const Standard_Integer plnId0,
				const Standard_Integer plnId1
			);

		//- the list will get empty after successfully creating plane
		TnbCad2d_EXPORT std::vector<Standard_Integer>
			MakePlanes
			(
				selctList& theList, 
				const gp_Ax2& ax = gp::XOY()
			);

		//- the list will get empty after successfully creating plane
		TnbCad2d_EXPORT Standard_Integer
			MakePlane
			(
				selctList& theList,
				const gp_Ax2& ax = gp::XOY()
			);
	};
}

#endif // !_Cad2d_Modeler_Header
