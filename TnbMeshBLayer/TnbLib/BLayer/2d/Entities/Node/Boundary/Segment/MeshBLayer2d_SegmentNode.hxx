#pragma once
#ifndef _MeshBLayer2d_SegmentNode_Header
#define _MeshBLayer2d_SegmentNode_Header

#include <MeshBLayer2d_BndNode.hxx>

namespace tnbLib
{

	class MeshBLayer2d_SegmentNode
		: public MeshBLayer2d_BndNode
	{

		/*Private Data*/

	public:

		// default constructor [1/31/2023 Payvand]

		MeshBLayer2d_SegmentNode()
		{}

		// constructors [1/31/2023 Payvand]

		MeshBLayer2d_SegmentNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
			: MeshBLayer2d_BndNode(theIndex, theCoord)
		{}

		MeshBLayer2d_SegmentNode(const Standard_Integer theIndex, Pnt2d&& theCoord)
			: MeshBLayer2d_BndNode(theIndex, std::move(theCoord))
		{}


		// Public functions and operators [1/31/2023 Payvand]

		Standard_Boolean IsSegment() const override;
	};
}

#endif // !_MeshBLayer2d_SegmentNode_Header
