#pragma once
#ifndef _Geo_SegmentGraphEdge_Header
#define _Geo_SegmentGraphEdge_Header

#include <Geo_GraphEdge.hxx>

namespace tnbLib
{

	template<class EdgeTraits>
	class Geo_SegmentGraphEdge
		: public Geo_GraphEdge<EdgeTraits>
	{

	public:

		typedef Geo_GraphEdge<EdgeTraits> base;

		typedef typename EdgeTraits::nodeType nodeType;
		typedef Geo_GraphEdgeAdaptor<typename EdgeTraits::edgeAdaptType> adaptor;

	private:

		/*Private Data*/

		std::shared_ptr<nodeType> theNode0_;
		std::shared_ptr<nodeType> theNode1_;

	public:

		// default constructor [1/5/2022 Amir]

		Geo_SegmentGraphEdge()
		{}

		// constructors [1/5/2022 Amir]

		explicit Geo_SegmentGraphEdge
		(
			const Standard_Integer theIndex
		)
			: base(theIndex)
		{}

		Geo_SegmentGraphEdge
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<nodeType>& theNode0,
			const std::shared_ptr<nodeType>& theNode1

		)
			: base(theIndex)
			, theNode0_(theNode0)
			, theNode1_(theNode1)
		{}

		Geo_SegmentGraphEdge
		(
			const Standard_Integer theIndex,
			std::shared_ptr<nodeType>&& theNode0,
			std::shared_ptr<nodeType>&& theNode1

		)
			: base(theIndex)
			, theNode0_(std::move(theNode0))
			, theNode1_(std::move(theNode1))
		{}


		// public functions and operators [1/5/2022 Amir]

		static void deAttach(const std::shared_ptr<Geo_SegmentGraphEdge>& theEdge);

		// override functions and operators [1/5/2022 Amir]

		Standard_Boolean IsSegment() const override
		{
			return Standard_True;
		}

		//- Macros
		GLOBAL_ACCESS_SINGLE(std::shared_ptr<nodeType>, Node0)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<nodeType>, Node1)


	};
}

#include <Geo_SegmentGraphEdgeI.hxx>

#endif // !_Geo_SegmentGraphEdge_Header
