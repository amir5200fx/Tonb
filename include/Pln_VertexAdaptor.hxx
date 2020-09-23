#pragma once
#ifndef _Pln_VertexAdaptor_Header
#define _Pln_VertexAdaptor_Header

#include <Standard_TypeDef.hxx>
#include <Global_Macros.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <map>
#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Edge;

	class Pln_VertexAdaptor
	{

		/*Private Data*/

		std::map<Standard_Integer, std::weak_ptr<Pln_Edge>> theEdges_;

	protected:

		Pln_VertexAdaptor()
		{}

	public:

		auto NbEdges() const
		{
			return (Standard_Integer)theEdges_.size();
		}

		const auto& Edges() const
		{
			return theEdges_;
		}

		void InsertToEdges
		(
			const Standard_Integer theIndex,
			const std::weak_ptr<Pln_Edge>& theEdge
		);

		void RemoveFromEdges
		(
			const Standard_Integer theIndex
		);
	};
}

#endif // !_Pln_VertexAdaptor_Header
