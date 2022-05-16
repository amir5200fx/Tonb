#pragma once
#ifndef _Aft2d_PoleEdgeTemplate_Header
#define _Aft2d_PoleEdgeTemplate_Header

#include <Aft2d_SingularEdgeTemplate.hxx>
#include <Entity2d_PolygonFwd.hxx>

//#include "Aft2d_gSegmentEdge.hxx"

#include <vector>

namespace tnbLib
{

	template<class BndEdgeType>
	class Aft2d_PoleEdgeTemplate
		: public Aft2d_SingularEdgeTemplate<BndEdgeType>
	{

		/*Private Data*/

	public:

		typedef Aft2d_SingularEdgeTemplate<BndEdgeType> base;
		typedef typename base::bndNodeType bndNodeType;
		typedef typename base::bndEdgeType bndEdgeType;

		typedef typename bndEdgeType::edgeType edgeType;
		typedef typename bndEdgeType::nodeType nodeType;
		typedef typename BndEdgeType::curveType curveType;


		// default constructor [4/25/2022 Amir]

		Aft2d_PoleEdgeTemplate()
		{}


		// constructors [4/25/2022 Amir]

		explicit Aft2d_PoleEdgeTemplate(const Standard_Integer theIndex)
			: Aft2d_SingularEdgeTemplate<BndEdgeType>(theIndex)
		{}

		Aft2d_PoleEdgeTemplate
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<typename BndEdgeType::nodeType>& theNode0,
			const std::shared_ptr<typename BndEdgeType::nodeType>& theNode1
		)
			: Aft2d_SingularEdgeTemplate<BndEdgeType>(theIndex, theNode0, theNode1)
		{}

		// public functions and operators [4/25/2022 Amir]

		Standard_Boolean IsPoleSingular() const override;

		void SingularityContraction(const typename BndEdgeType::metricPrcsr& thePrcsr) override;

		//- Static functions and operators

		static std::vector<std::shared_ptr<BndEdgeType>>
			GetTopology
			(
				const Entity2d_Polygon& ,
				const std::shared_ptr<curveType>& theCurve
			);
	};
}

#include <Aft2d_PoleEdgeTemplateI.hxx>

#endif // !_Aft2d_PoleEdgeTemplate_Header
