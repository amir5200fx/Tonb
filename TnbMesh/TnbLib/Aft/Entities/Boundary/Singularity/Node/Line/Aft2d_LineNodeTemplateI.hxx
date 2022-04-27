#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
template<class BndNodeType>
inline Standard_Boolean 
tnbLib::Aft2d_LineNodeTemplate<BndNodeType>::IsLine() const
{
	return Standard_True;
}

template<class BndNodeType>
inline void tnbLib::Aft2d_LineNodeTemplate<BndNodeType>::RemoveThis
(
	const typename BndNodeType::metricPrcsr &
)
{
	FatalErrorIn(FunctionSIG)
		<< "invalid operator has been called!" << endl
		<< abort(FatalError);
}

namespace tnbLib
{

	template<class BndNodeType>
	inline std::shared_ptr<BndNodeType> 
		Aft2d_LineNodeTemplate<BndNodeType>::MergeNodes
		(
			const std::shared_ptr<BndNodeType>& theNode0, 
			const std::shared_ptr<BndNodeType>& theNode1, 
			const Mesh_BndMergeAlg theAlg
		)
	{
		Debug_Null_Pointer(theNode0);
		Debug_Null_Pointer(theNode1);

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
		else
		{
			auto node =
				std::make_shared<Aft2d_LineNodeTemplate>(0, MEAN(theNode0->Coord(), theNode1->Coord()));
			Debug_Null_Pointer(node);
			return std::move(node);
		}
	}
}