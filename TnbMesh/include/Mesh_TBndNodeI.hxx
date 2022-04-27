#pragma once
#include <Global_Macros.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	template<class TBndNodeTraits>
	inline Standard_Boolean
		Mesh_TBndNode<TBndNodeTraits, Mesh_BndNode_Position_Corner>::IsSingular() const
	{
		return Standard_False;
	}

	template<class TBndNodeTraits>
	inline Standard_Boolean
		Mesh_TBndNode<TBndNodeTraits, Mesh_BndNode_Position_Segment>::IsSingular() const
	{
		return Standard_False;
	}

	template<class TBndNodeTraits>
	inline Standard_Boolean 
		Mesh_TBndNode<TBndNodeTraits, Mesh_BndNode_Position_Segment>::IsSegment() const
	{
		return Standard_True;
	}

	template<class TBndNodeTraits>
	std::shared_ptr<Mesh_TBndNode<TBndNodeTraits, Mesh_BndNode_Position_Corner>> 
		Mesh_TBndNode<TBndNodeTraits, Mesh_BndNode_Position_Corner>::MergeNodes
	(
		const std::shared_ptr<Mesh_TBndNode>& theNode0,
		const std::shared_ptr<Mesh_TBndNode>& theNode1,
		const Mesh_BndMergeAlg theAlg
	)
	{
		if (theAlg IS_EQUAL Mesh_BndMergeAlg::FirstPreferred)
		{
			auto node = theNode0;
			return std::move(node);
		}
		else if (theAlg IS_EQUAL Mesh_BndMergeAlg::SecondPreferred)
		{
			auto node = MergeNodes(theNode1, theNode0, Mesh_BndMergeAlg::FirstPreferred);
			return std::move(node);
		}
		else if (theAlg IS_EQUAL Mesh_BndMergeAlg::New)
		{
			auto node =
				std::make_shared<Mesh_TBndNode>(0, MEAN(theNode0->Coord(), theNode1->Coord()));
			return std::move(node);
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "undefined merging alg has been detected!" << endl
				<< abort(FatalError);
			return theNode0;
		}
	}

	template<class TBndNodeTraits>
	std::shared_ptr<Mesh_TBndNode<TBndNodeTraits, Mesh_BndNode_Position_Segment>>
		Mesh_TBndNode<TBndNodeTraits, Mesh_BndNode_Position_Segment>::MergeNodes
		(
			const std::shared_ptr<Mesh_TBndNode>& theNode0,
			const std::shared_ptr<Mesh_TBndNode>& theNode1,
			const Mesh_BndMergeAlg theAlg
		)
	{
		if (theAlg IS_EQUAL Mesh_BndMergeAlg::FirstPreferred)
		{
			auto node = theNode0;
			return std::move(node);
		}
		else if (theAlg IS_EQUAL Mesh_BndMergeAlg::SecondPreferred)
		{
			auto node = MergeNodes(theNode1, theNode0, Mesh_BndMergeAlg::FirstPreferred);
			return std::move(node);
		}
		else if (theAlg IS_EQUAL Mesh_BndMergeAlg::New)
		{
			auto node =
				std::make_shared<Mesh_TBndNode>(0, MEAN(theNode0->Coord(), theNode1->Coord()));
			return std::move(node);
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "undefined merging alg has been detected!" << endl
				<< abort(FatalError);
			return theNode0;
		}
	}
}