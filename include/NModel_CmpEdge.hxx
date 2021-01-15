#pragma once
#ifndef _NModel_CmpEdge_Header
#define _NModel_CmpEdge_Header

#include <NModel_Entity.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class NModel_Edge;
	class NModel_Wire;
	class Cad_Tools;

	class NModel_CmpEdge
		: public NModel_Entity
	{

		typedef std::vector<std::shared_ptr<NModel_Edge>> edgeList;

		friend class NModel_Edge;
		friend class NModel_Wire;
		friend class Cad_Tools;

		/*Private Data*/

		edgeList theEdges_;

	protected:

		void Insert(const std::shared_ptr<NModel_Edge>& theEdge)
		{
			theEdges_.push_back(theEdge);
		}

		edgeList& ChangeEdges()
		{
			return theEdges_;
		}

	public:

		NModel_CmpEdge()
		{}

		NModel_CmpEdge
		(
			const Standard_Integer theIndex
		)
			: NModel_Entity(theIndex)
		{}

		NModel_CmpEdge
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: NModel_Entity(theIndex, theName)
		{}


		auto NbEdges() const
		{
			return (Standard_Integer)theEdges_.size();
		}

		const auto& Edges() const
		{
			return theEdges_;
		}

		//void Reverse();


	};
}

#endif // !_NModel_CmpEdge_Header