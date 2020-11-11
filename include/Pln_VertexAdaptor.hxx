#pragma once
#ifndef _Pln_VertexAdaptor_Header
#define _Pln_VertexAdaptor_Header

#include <Standard_TypeDef.hxx>
#include <Global_Macros.hxx>
#include <Global_Serialization.hxx>
#include <Cad2d_Module.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <map>
#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Edge;

	class Pln_VertexAdaptor
	{

		/*Private Data*/

		std::map<Standard_Integer, std::weak_ptr<Pln_Edge>> theEdges_;


		/*private functions and operators*/

		auto& ChangeEdges()
		{
			return theEdges_;
		}

		DECLARE_SAVE_LOAD_HEADER(TnbCad2d_EXPORT);

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

		std::vector<std::weak_ptr<Pln_Edge>> RetrieveEdges() const;

		void InsertToEdges
		(
			const Standard_Integer theIndex,
			const std::weak_ptr<Pln_Edge>& theEdge
		);

		void RemoveFromEdges
		(
			const Standard_Integer theIndex
		);

		void RetrieveEdgesTo(std::vector<std::weak_ptr<Pln_Edge>>& theEdges) const;
	};
}

#endif // !_Pln_VertexAdaptor_Header
