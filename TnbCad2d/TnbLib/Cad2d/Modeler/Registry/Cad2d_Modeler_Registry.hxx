#pragma once
#ifndef _Cad2d_Modeler_Registry_Header
#define _Cad2d_Modeler_Registry_Header

#include <Standard_TypeDef.hxx>

#include <map>
#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Vertex;
	class Pln_Edge;

	class Cad2d_Modeler_Registry
	{

		/*Private Data*/

		/*std::map<Standard_Integer, std::shared_ptr<Pln_Vertex>>
			theVertices_;*/
		std::map<Standard_Integer, std::shared_ptr<Pln_Edge>>
			theEdges_;

	protected:

		Cad2d_Modeler_Registry();


		/*auto NbVertices() const
		{
			return (Standard_Integer)theVertices_.size();
		}*/

		auto NbEdges() const
		{
			return (Standard_Integer)theEdges_.size();
		}

		/*const auto& Vertices() const
		{
			return theVertices_;
		}*/

		const auto& Edges() const
		{
			return theEdges_;
		}

		/*std::shared_ptr<Pln_Vertex> 
			RemoveVertexFromRegistry
			(
				const Standard_Integer theIndex
			);*/

		std::shared_ptr<Pln_Edge> 
			RemoveEdgeFromRegistry
			(
				const Standard_Integer theIndex
			);

		/*void RegisterToVertices
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<Pln_Vertex>& theVtx
		);*/

		void RegisterToEdges
		(
			const Standard_Integer theIndex, 
			const std::shared_ptr<Pln_Edge>& theEdge
		);

	public:

		//static const std::shared_ptr<Pln_Vertex> null_vertex;
		static const std::shared_ptr<Pln_Edge> null_edge;

		/*const std::shared_ptr<Pln_Vertex>& 
			SelectVertex
			(
				const Standard_Integer theIndex
			) const;*/

		const std::shared_ptr<Pln_Edge>& 
			SelectEdge
			(
				const Standard_Integer theIndex
			) const;

		/*static Standard_Boolean
			IsNull_Vertex
			(
				const std::shared_ptr<Pln_Vertex>& theVtx
			);*/

		static Standard_Boolean 
			IsNull
			(
				const std::shared_ptr<Pln_Edge>& theEdge
			);
	};
}

#endif // !_Cad2d_Modeler_Registry_Header
