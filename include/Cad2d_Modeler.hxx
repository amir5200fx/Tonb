#pragma once
#ifndef _Cad2d_Modeler_Header
#define _Cad2d_Modeler_Header

#include <Cad2d_Modeler_Corner.hxx>
#include <Cad2d_Modeler_Counter.hxx>
#include <Cad2d_Modeler_SrchEng.hxx>
#include <Cad2d_Modeler_Plane.hxx>
#include <Cad2d_Modeler_Wire.hxx>
#include <Cad2d_Modeler_Registry.hxx>
#include <Cad_EntityManager.hxx>

#include <memory>
#include <map>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Edge;
	class Pln_Vertex;

	class Cad2d_Modeler
		: public Cad2d_Modeler_SrchEng
		, public Cad2d_Modeler_Counter
		, public Cad2d_Modeler_Wire
		, public Cad2d_Modeler_Plane
		, public Cad2d_Modeler_Registry
	{

		typedef cad2dLib::Modeler_Corner corner;

		/*Private Data*/

		void RemoveEdge(const std::shared_ptr<Pln_Edge>& theEdge);

		void RemoveVertex(const std::shared_ptr<Pln_Vertex>& theVtx);

		void RemoveVertex(const std::shared_ptr<Pln_Vertex>& theVtx, const std::shared_ptr<corner>& theCorner);

		void AddVertex(const std::shared_ptr<Pln_Vertex>& theVtx, const Standard_Integer theEdgeIndex);

		void AddEdge(const std::shared_ptr<Pln_Edge>& theEdge);

	public:

		Cad2d_Modeler();


		void Import
		(
			const std::shared_ptr<Pln_Edge>& theEdge
		);

		void Trim
		(
			const std::shared_ptr<Pln_Edge>& theEdge0, 
			const std::shared_ptr<Pln_Edge>& theEdge1
		);
	};
}

#endif // !_Cad2d_Modeler_Header
