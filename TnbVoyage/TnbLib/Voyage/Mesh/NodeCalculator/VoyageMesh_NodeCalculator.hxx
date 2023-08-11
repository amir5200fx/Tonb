#pragma once
#ifndef _VoyageMesh_NodeCalculator_Header
#define _VoyageMesh_NodeCalculator_Header

#include <Pnt2d.hxx>

#include <memory>

namespace tnbLib
{

	//- Forward Declarations
	class VoyageMesh_Edge;

	class VoyageMesh_NodeCalculator
	{

		/*Private Data*/

	public:

		//- default constructor

		VoyageMesh_NodeCalculator()
		{}

		//- constructors


		//- Public functions and operators

		virtual Pnt2d CalcCoord(const std::shared_ptr<VoyageMesh_Edge>&, const Standard_Real theSize) const = 0;


	};
}

#endif // !_VoyageMesh_NodeCalculator_Header
