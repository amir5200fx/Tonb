#pragma once
#ifndef _VoyageMesh_RefNode_Header
#define _VoyageMesh_RefNode_Header

#include <VoyageMesh_Node.hxx>

namespace tnbLib
{

	class VoyageMesh_RefNode
		: public VoyageMesh_Node
	{

		/*private Data*/

	public:

		//- default constructor

		VoyageMesh_RefNode()
		{}


		//- constructors

		VoyageMesh_RefNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
			: VoyageMesh_Node(theIndex, theCoord)
		{}

		VoyageMesh_RefNode(const Standard_Integer theIndex, Pnt2d&& theCoord)
			: VoyageMesh_Node(theIndex, std::move(theCoord))
		{}


		//- Public functions and operators

	};

}

#endif // !_VoyageMesh_RefNode_Header
