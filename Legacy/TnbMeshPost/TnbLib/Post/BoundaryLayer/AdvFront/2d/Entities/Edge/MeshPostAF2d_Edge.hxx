#pragma once
#ifndef _MeshPostAF2d_Edge_Header
#define _MeshPostAF2d_Edge_Header

#include <MeshPostAF2d_EdgeBase.hxx>

namespace tnbLib
{

	class MeshPostAF2d_Edge
		: public MeshPostAF2d_EdgeBase
	{

		/*Private Data*/

	public:

		// default constructor [8/31/2023 aamir]

		MeshPostAF2d_Edge()
		{}

		// constructors [8/31/2023 aamir]

		MeshPostAF2d_Edge(const Standard_Integer theIndex)
			: MeshPostAF2d_EdgeBase(theIndex)
		{}

		MeshPostAF2d_Edge
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<MeshPostAF2d_Node>& theNode0, 
			const std::shared_ptr<MeshPostAF2d_Node>& theNode1
		)
			: MeshPostAF2d_EdgeBase(theIndex, theNode0, theNode1)
		{}

		// Public functions and operators [8/31/2023 aamir]



	};

}

#endif // !_MeshPostAF2d_Edge_Header
