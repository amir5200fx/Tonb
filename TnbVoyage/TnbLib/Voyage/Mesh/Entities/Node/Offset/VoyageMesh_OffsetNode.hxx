#pragma once
#ifndef _VoyageMesh_OffsetNode_Header
#define _VoyageMesh_OffsetNode_Header

#include <VoyageMesh_Node.hxx>

namespace tnbLib
{

	class VoyageMesh_OffsetNode
		: public VoyageMesh_Node
	{

		/*Private Data*/

	public:

		//- default constructor

		VoyageMesh_OffsetNode()
		{}

		//- constructors

		VoyageMesh_OffsetNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
			: VoyageMesh_Node(theIndex, theCoord)
		{}

		VoyageMesh_OffsetNode(const Standard_Integer theIndex, Pnt2d&& theCoord)
			: VoyageMesh_Node(theIndex, std::move(theCoord))
		{}

		//- Public functions and operators



	};

}

#endif // !_VoyageMesh_OffsetNode_Header
