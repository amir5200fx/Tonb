#pragma once
#ifndef _VoyageMesh_Edge_Header
#define _VoyageMesh_Edge_Header

#include <VoyageMesh_Entity.hxx>
#include <VoyageMesh_Node.hxx>
#include <Aft2d_EdgeSurface.hxx>

namespace tnbLib
{

	//- Forward Declarations
	class VoyageMesh_Node;

	class VoyageMesh_Edge
		: public VoyageMesh_Entity<Aft2d_EdgeSurface>
	{

	public:

		typedef VoyageMesh_Entity<Aft2d_EdgeSurface> baseType;

	private:

		/*Private Data*/

	public:

		//- default constructor

		VoyageMesh_Edge()
		{}

		VoyageMesh_Edge
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<VoyageMesh_Node>& theNode0, 
			const std::shared_ptr<VoyageMesh_Node>& theNode1
		)
			: baseType(theIndex, theNode0, theNode1)
		{}

		//- Public functions and operators

	};

}

#endif // !_VoyageMesh_Edge_Header
