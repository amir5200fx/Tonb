#pragma once
#ifndef _Voyage_Edge_Header
#define _Voyage_Edge_Header

#include <Voyage_Entity.hxx>

#include <array>
#include <memory>

namespace tnbLib
{

	// Forward Declarations [6/17/2023 Payvand]
	class Voyage_Node;
	class VoyageGeo_Curve;

	class Voyage_Edge
		: public Voyage_Entity
	{

		/*Private Data*/

		std::shared_ptr<Voyage_Node> theNode0_;
		std::shared_ptr<Voyage_Node> theNode1_;

		Standard_Real theCost_;

	public:

		// default constructor [6/17/2023 Payvand]

		Voyage_Edge()
			: theCost_(0)
		{}

		// constructors [6/17/2023 Payvand]

		Voyage_Edge
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<Voyage_Node>& theNode0,
			const std::shared_ptr<Voyage_Node>& theNode1
		)
			: Voyage_Entity(theIndex)
			, theNode0_(theNode0)
			, theNode1_(theNode1)
			, theCost_(0)
		{}

		//  Public functions and operators [7/21/2023 Payvand]

		const auto& Node0() const { return theNode0_; }
		const auto& Node1() const { return theNode1_; }

		auto Cost() const { return theCost_; }

		void SetNode0(const std::shared_ptr<Voyage_Node>& theNode)
		{
			theNode0_ = theNode;
		}

		void SetNode1(const std::shared_ptr<Voyage_Node>& theNode)
		{
			theNode1_ = theNode;
		}

		void SetCost(const Standard_Real x) { theCost_ = x; }

	};
}

#endif // !_Voyage_Edge_Header
