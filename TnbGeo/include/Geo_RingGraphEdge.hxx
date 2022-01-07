#pragma once
#ifndef _Geo_RingGraphEdge_Header
#define _Geo_RingGraphEdge_Header

#include <Geo_GraphEdge.hxx>

namespace tnbLib
{

	template<class EdgeTraits>
	class Geo_RingGraphEdge
		: public Geo_GraphEdge<EdgeTraits>
	{

	public:

		typedef Geo_GraphEdge<EdgeTraits> base;

		typedef typename EdgeTraits::nodeType nodeType;
		typedef Geo_GraphEdgeAdaptor<typename EdgeTraits::edgeAdaptType> adaptor;

	private:

		/*Private Data*/

		std::shared_ptr<nodeType> theNode_;

	public:

		// default constructor [1/5/2022 Amir]

		Geo_RingGraphEdge()
		{}

		// constructors [1/5/2022 Amir]

		explicit Geo_RingGraphEdge
		(
			const Standard_Integer theIndex
		)
			: base(theIndex)
		{}

		Geo_RingGraphEdge
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<nodeType>& theNode

		)
			: base(theIndex)
			, theNode_(theNode)
		{}

		// public functions and operators [1/5/2022 Amir]

		static void deAttach(const std::shared_ptr<Geo_RingGraphEdge>& theEdge);

		// override functions and operators [1/5/2022 Amir]

		Standard_Boolean IsRing() const override
		{
			return Standard_True;
		}

		//- Macros
		GLOBAL_ACCESS_SINGLE(std::shared_ptr<nodeType>, Node)
	};
}

#include <Geo_RingGraphEdgeI.hxx>

#endif // !_Geo_RingGraphEdge_Header
