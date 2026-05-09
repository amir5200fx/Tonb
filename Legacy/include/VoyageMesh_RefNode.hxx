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

		virtual Standard_Boolean IsDeparture() const { return Standard_False; }
		virtual Standard_Boolean IsArrival() const { return Standard_False; }

		Standard_Boolean IsReference() const override { return Standard_True; }
		Standard_Boolean IsBoundary() const override { return Standard_True; }

		Standard_Boolean IsTip() const override { return Standard_False; }

	};

}

#endif // !_VoyageMesh_RefNode_Header
