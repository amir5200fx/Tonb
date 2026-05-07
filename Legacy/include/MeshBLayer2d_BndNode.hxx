#pragma once
#ifndef _MeshBLayer2d_BndNode_Header
#define _MeshBLayer2d_BndNode_Header

#include <MeshBLayer2d_Node.hxx>

namespace tnbLib
{

	class MeshBLayer2d_BndNode
		: public MeshBLayer2d_Node
	{

		/*Private Data*/

	protected:

		// default constructor [1/31/2023 Payvand]

		MeshBLayer2d_BndNode()
		{}


		// constructors [1/31/2023 Payvand]

		MeshBLayer2d_BndNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
			: MeshBLayer2d_Node(theIndex, theCoord)
		{}

		MeshBLayer2d_BndNode(const Standard_Integer theIndex, Pnt2d&& theCoord)
			: MeshBLayer2d_Node(theIndex, std::move(theCoord))
		{}

	public:

		// Public functions and operators [1/31/2023 Payvand]

		virtual Standard_Boolean IsSegment() const;
		virtual Standard_Boolean IsCorner() const;

		Standard_Boolean IsBoundary() const override;
	};
}

#endif // !_MeshBLayer2d_BndNode_Header
