#pragma once
#ifndef _Aft2d_GapEdgeTemplate_Header
#define _Aft2d_GapEdgeTemplate_Header

#include <Entity2d_PolygonFwd.hxx>

#include <Standard_TypeDef.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	template<class BndEdgeType>
	class Aft2d_GapEdgeTemplate
		: public BndEdgeType
	{

		/*Private Data*/

	public:

		// default constructor [5/12/2022 Amir]

		Aft2d_GapEdgeTemplate()
		{}


		// constructors [5/12/2022 Amir]

		explicit Aft2d_GapEdgeTemplate(const Standard_Integer theIndex)
			: BndEdgeType(theIndex)
		{}

		Aft2d_GapEdgeTemplate
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<typename BndEdgeType::nodeType>& theNode0,
			const std::shared_ptr<typename BndEdgeType::nodeType>& theNode1
		)
			: BndEdgeType(theIndex, theNode0, theNode1)
		{}

	public:

		typedef typename BndEdgeType::edgeType edgeType;
		typedef typename BndEdgeType::nodeType nodeType;
		typedef typename BndEdgeType::curveType curveType;

		typedef BndEdgeType base;

		// override functions and operators [5/12/2022 Amir]

		Standard_Boolean IsGap() const override
		{
			return Standard_True;
		}
		
		// public functions and operators [5/12/2022 Amir]

		void Contraction(const typename BndEdgeType::metricPrcsr& thePrcsr);


		//- Static functions and operators

		static std::vector<std::shared_ptr<BndEdgeType>>
			GetTopology
			(
				const Entity2d_Polygon&,
				const std::shared_ptr<curveType>& theCurve
			);
	};
}

#endif // !_Aft2d_GapEdgeTemplate_Header
