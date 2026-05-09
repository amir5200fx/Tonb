#pragma once
#ifndef _VoyageMesh_DepartureNode_Header
#define _VoyageMesh_DepartureNode_Header

#include <VoyageMesh_RefNode.hxx>

namespace tnbLib
{

	class VoyageMesh_DepartureNode
		: public VoyageMesh_RefNode
	{

		/*Private Data*/

	public:

		// default constructor [9/2/2023 Payvand]

		VoyageMesh_DepartureNode()
		{}

		// constructors [9/2/2023 Payvand]

		VoyageMesh_DepartureNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
			: VoyageMesh_RefNode(theIndex, theCoord)
		{}

		VoyageMesh_DepartureNode(const Standard_Integer theIndex, Pnt2d&& theCoord)
			: VoyageMesh_RefNode(theIndex, std::move(theCoord))
		{}


		// Public functions and operators [9/2/2023 Payvand]

		Standard_Boolean IsDeparture() const override { return Standard_True; }

	};

}

#endif // !_VoyageMesh_DepartureNode_Header
