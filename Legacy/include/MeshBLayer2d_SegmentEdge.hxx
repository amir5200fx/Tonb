#pragma once
#ifndef _MeshBLayer2d_SegmentEdge_Header
#define _MeshBLayer2d_SegmentEdge_Header

#include <MeshBLayer2d_BndEdge.hxx>

namespace tnbLib
{

	class MeshBLayer2d_SegmentEdge
		: public MeshBLayer2d_BndEdge
	{

		/*Private Data*/

	public:

		// default constructor [1/31/2023 Payvand]

		MeshBLayer2d_SegmentEdge()
		{}

		// constructors [1/31/2023 Payvand]

		explicit MeshBLayer2d_SegmentEdge(const Standard_Integer theIndex)
			: MeshBLayer2d_BndEdge(theIndex)
		{}


		MeshBLayer2d_SegmentEdge
		(
			const Standard_Integer theIndex, 
			const std::shared_ptr<MeshBLayer2d_Node>& theNode0, 
			const std::shared_ptr<MeshBLayer2d_Node>& theNode1
		)
			: MeshBLayer2d_BndEdge(theIndex, theNode0, theNode1)
		{}


		// Public functions and operators [1/31/2023 Payvand]

		Standard_Boolean IsSegment() const override;
		
	};
}

#endif // !_MeshBLayer2d_SegmentEdge_Header
