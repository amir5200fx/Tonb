#pragma once
#ifndef _VoyageMesh_OffsetEdge_Header
#define _VoyageMesh_OffsetEdge_Header

#include <VoyageMesh_Edge.hxx>

namespace tnbLib
{

	class VoyageMesh_OffsetEdge
		: public VoyageMesh_Edge
	{

		/*Private Data*/

	public:

		//- default constructor

		VoyageMesh_OffsetEdge()
		{}

		//- constructors

		VoyageMesh_OffsetEdge
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<VoyageMesh_Node>& theNode0,
			const std::shared_ptr<VoyageMesh_Node>& theNode1
		)
			: VoyageMesh_Edge(theIndex, theNode0, theNode1)
		{}


		//- Public functions and operators



	};
}

#endif // !_VoyageMesh_OffsetEdge_Header
