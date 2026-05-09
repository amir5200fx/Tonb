#pragma once
#ifndef _MeshBLayer2d_InnerNode_Header
#define _MeshBLayer2d_InnerNode_Header

#include <MeshBLayer2d_Node.hxx>

namespace tnbLib
{

	class MeshBLayer2d_InnerNode
		: public MeshBLayer2d_Node
	{

		/*Private Data*/

	public:

		// default constructor [1/31/2023 Payvand]

		MeshBLayer2d_InnerNode()
		{}


		// constructors [1/31/2023 Payvand]

		MeshBLayer2d_InnerNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
			: MeshBLayer2d_Node(theIndex, theCoord)
		{}

		MeshBLayer2d_InnerNode(const Standard_Integer theIndex, Pnt2d&& theCoord)
			: MeshBLayer2d_Node(theIndex, std::move(theCoord))
		{}


		// Public functions and operators [1/31/2023 Payvand]

		Standard_Boolean IsInner() const override;
	};
}

#endif // !_MeshBLayer2d_InnerNode_Header
