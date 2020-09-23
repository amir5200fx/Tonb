#pragma once
#ifndef _SectPx_TPntAdaptor_Header
#define _SectPx_TPntAdaptor_Header

#include <Standard_TypeDef.hxx>

#include <vector>
#include <memory>
#include <map>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Edge;
	class SectPx_ProfileMaker;
	class SectPx_PntTools;

	class SectPx_TPntAdaptor
	{

		friend class SectPx_ProfileMaker;
		friend class SectPx_PntTools;

		/*Private Data*/

		std::map<Standard_Integer, std::weak_ptr<SectPx_Edge>>
			theEdges_;

	protected:

		SectPx_TPntAdaptor()
		{}

		std::weak_ptr<SectPx_Edge> 
			RemoveFromEdges
			(
				const Standard_Integer theIndex
			);

		void Import
		(
			const Standard_Integer theIndex, 
			const std::shared_ptr<SectPx_Edge>& theEdge
		);

	public:

		auto NbEdges() const
		{
			return (Standard_Integer)theEdges_.size();
		}

		const auto& Edges() const
		{
			return theEdges_;
		}
	};
}

#endif // !_SectPx_TPntAdaptor_Header
