#pragma once
#ifndef _VoyageMesh_Element_Header
#define _VoyageMesh_Element_Header

#include <VoyageMesh_Entity.hxx>
#include <VoyageMesh_Node.hxx>
#include <Aft2d_ElementSurface.hxx>

namespace tnbLib
{

	class VoyageMesh_Element
		: public VoyageMesh_Entity<Aft2d_ElementSurface>
	{

	public:

		typedef VoyageMesh_Entity<Aft2d_ElementSurface> baseType;

	private:

		/*Private Data*/

	public:

		//- default constructor

		VoyageMesh_Element()
		{}

		//- constructors

		VoyageMesh_Element
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<VoyageMesh_Node>& theNode0,
			const std::shared_ptr<VoyageMesh_Node>& theNode1,
			const std::shared_ptr<VoyageMesh_Node>& theNode2
		)
			: baseType(theIndex, theNode0, theNode1, theNode2)
		{}


		//- Public functions and operators



	};

}

#endif // !_VoyageMesh_Element_Header
