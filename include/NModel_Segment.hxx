#pragma once
#ifndef _NModel_Paired_Header
#define _NModel_Paired_Header

#include <Global_AccessMethod.hxx>
#include <NModel_Entity.hxx>
#include <NModel_SegmentGeometry.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class NModel_Edge;

	class NModel_Paired
		: public NModel_Entity
		, public NModel_SegmentGeometry
	{

		/*Private Data*/

		std::map<Standard_Integer, std::shared_ptr<NModel_Edge>>
			theEdges_;

	public:

		NModel_Paired
		(
			const std::shared_ptr<NModel_Edge>& theEdge0,
			const std::shared_ptr<NModel_Edge>& theEdge1
		);

		NModel_Paired
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<NModel_Edge>& theEdge0,
			const std::shared_ptr<NModel_Edge>& theEdge1
		);

		NModel_Paired
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<NModel_Edge>& theEdge0,
			const std::shared_ptr<NModel_Edge>& theEdge1
		);

		auto NbEdges() const
		{
			return (Standard_Integer)theEdges_.size();
		}

		const auto& Edges() const
		{
			return theEdges_;
		}

		std::shared_ptr<NModel_Edge> RemoveFromEdges(const Standard_Integer theIndex) const;

		std::vector<std::shared_ptr<NModel_Edge>> RetrieveEdges() const;

		void InsertToEdges(const Standard_Integer theIndex, const std::shared_ptr<NModel_Edge>& theEdge);

		void RetrieveEdgesTo(std::vector<std::shared_ptr<NModel_Edge>>& theEdges) const;
	};
}

#endif // !_NModel_Paired_Header
