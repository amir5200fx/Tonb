#pragma once
#ifndef _MeshBLayer2d_BndEdge_Header
#define _MeshBLayer2d_BndEdge_Header

#include <MeshBLayer2d_Edge.hxx>

namespace tnbLib
{

	class MeshBLayer2d_BndEdge
		: public MeshBLayer2d_Edge
	{

		/*Private Data*/

	protected:

		// default constructor [1/31/2023 Payvand]

		MeshBLayer2d_BndEdge()
		{}


		// Constructors [1/31/2023 Payvand]

		explicit MeshBLayer2d_BndEdge(const Standard_Integer theIndex)
			: MeshBLayer2d_Edge(theIndex)
		{}

		MeshBLayer2d_BndEdge
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<MeshBLayer2d_Node>& theNode0,
			const std::shared_ptr<MeshBLayer2d_Node>& theNode1
		)
			: MeshBLayer2d_Edge(theIndex, theNode0, theNode1)
		{}


		// Public functions and operators [1/31/2023 Payvand]

		virtual Standard_Boolean IsSegment() const;

		Standard_Boolean IsBoundary() const override;

	};
}

#endif // !_MeshBLayer2d_BndEdge_Header
