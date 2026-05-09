#pragma once
#ifndef _MeshPostAF2d_Node_Header
#define _MeshPostAF2d_Node_Header

#include <MeshPostAF2d_NodeBase.hxx>

namespace tnbLib
{

	class MeshPostAF2d_Node
		: public MeshPostAF2d_NodeBase
	{

		/*Private Data*/

	public:

		// default constructor [8/31/2023 aamir]

		MeshPostAF2d_Node()
		{}

		// constructors [8/31/2023 aamir]

		MeshPostAF2d_Node(const Standard_Integer theIndex, const Pnt2d& theCoord)
			: MeshPostAF2d_NodeBase(theIndex, theCoord)
		{}

		MeshPostAF2d_Node(const Standard_Integer theIndex, Pnt2d&& theCoord)
			: MeshPostAF2d_NodeBase(theIndex, std::move(theCoord))
		{}

		// Public functions and operators [8/31/2023 aamir]



	};
}

#endif // !_MeshPostAF2d_Node_Header
