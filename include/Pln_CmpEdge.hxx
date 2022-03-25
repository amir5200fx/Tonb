#pragma once
#ifndef _Pln_CmpEdge_Header
#define _Pln_CmpEdge_Header

#include <Pln_Entity.hxx>
#include <OFstream.hxx>
#include <Global_Serialization.hxx>
#include <Cad2d_Module.hxx>

class gp_Trsf2d;

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Vertex;
	class Pln_Edge;
	class Pln_Wire;
	class Pln_Tools;

	class Pln_CmpEdge
	{

		friend class Pln_Edge;
		friend class Pln_Wire;
		friend class Pln_Tools;

		/*Private Data*/

		std::vector<std::shared_ptr<Pln_Edge>> theEdges_;


		/*private functions and operators*/

		TNB_SERIALIZATION(TnbCad2d_EXPORT);

	protected:


		auto& ChangeEdges()
		{
			return theEdges_;
		}

		void Insert
		(
			const std::shared_ptr<Pln_Edge>& theEdge
		)
		{
			theEdges_.push_back(theEdge);
		}

		void Insert
		(
			std::shared_ptr<Pln_Edge>&& theEdge
		)
		{
			theEdges_.push_back(std::move(theEdge));
		}

	public:

		// default constructor [3/24/2022 Amir]

		Pln_CmpEdge()
		{}

		// constructors [3/24/2022 Amir]

		// public functions and operators [3/24/2022 Amir]

		Standard_Boolean IsValidForWire
		(
			const Standard_Real theTol
		) const;

		auto NbEdges() const
		{
			return (Standard_Integer)theEdges_.size();
		}

		const auto& Edges() const
		{
			return theEdges_;
		}

		TnbCad2d_EXPORT std::shared_ptr<Pln_CmpEdge>
			Copy() const;

		TnbCad2d_EXPORT std::vector<std::shared_ptr<Pln_Vertex>>
			RetrieveVertices() const;

		TnbCad2d_EXPORT void Transform(const gp_Trsf2d& t);

		TnbCad2d_EXPORT void RetrieveVerticesTo
		(
			std::vector<std::shared_ptr<Pln_Vertex>>& theVertices
		) const;

		TnbCad2d_EXPORT void Reverse();

		TnbCad2d_EXPORT void ExportToPlt
		(
			OFstream& File
		) const;

	};
}

#endif // !_Pln_CmpEdge_Header
