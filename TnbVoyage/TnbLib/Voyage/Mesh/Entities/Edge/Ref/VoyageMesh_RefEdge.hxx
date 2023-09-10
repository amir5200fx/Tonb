#pragma once
#ifndef _VoyageMesh_RefEdge_Header
#define _VoyageMesh_RefEdge_Header

#include <VoyageMesh_Edge.hxx>

namespace tnbLib
{

	class VoyageMesh_RefEdge
		: public VoyageMesh_Edge
	{

		/*Private Data*/

		Standard_Boolean theSense_;

	public:

		// default constructor [9/1/2023 aamir]

		VoyageMesh_RefEdge()
			: theSense_(Standard_True)
		{}

		// constructors [9/1/2023 aamir]

		VoyageMesh_RefEdge(const Standard_Integer theIndex)
			: VoyageMesh_Edge(theIndex)
			, theSense_(Standard_True)
		{}

		VoyageMesh_RefEdge
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<VoyageMesh_Node>& theNode0, 
			const std::shared_ptr<VoyageMesh_Node>& theNode1,
			const Standard_Boolean theSense = Standard_True
		)
			: VoyageMesh_Edge(theIndex, theNode0, theNode1)
			, theSense_(theSense)
		{}

		// Public functions and operators [9/1/2023 aamir]

		auto Sense() const { return theSense_; }

		Standard_Boolean IsReference() const override { return Standard_True; }
		Standard_Boolean IsBoundary() const override { return Standard_True; }

		TnbVoyage_EXPORT std::shared_ptr<VoyageMesh_Node> RetrieveTip() const;

		void SetSense(const Standard_Integer theSense) { theSense_ = theSense; }

	};

}

#endif // !_VoyageMesh_RefEdge_Header
