#pragma once
#ifndef _VoyageMesh_StdOptNode_Calculator_Header
#define _VoyageMesh_StdOptNode_Calculator_Header

#include <VoyageMesh_OptNode_Calculator.hxx>

namespace tnbLib
{

	// Forward Declarations [2/24/2022 Amir]

	class VoyageMesh_StdOptNode_Calculator
		: public VoyageMesh_OptNode_Calculator
	{

		/*Private Data*/

		// private functions and operators [2/24/2022 Amir]


		// private static functions [2/24/2022 Amir]


	public:

		// default constructor [2/24/2022 Amir]

		VoyageMesh_StdOptNode_Calculator()
		{}

		// constructors [2/24/2022 Amir]


		// override functions and operators [2/24/2022 Amir]

		TnbMesh_EXPORT void Perform() override;

		// public functions and operators [2/24/2022 Amir]

		/*static TnbMesh_EXPORT Pnt2d
			CorrectCoord
			(
				const Pnt2d& theCentre,
				const Pnt2d& theCoord,
				const Entity2d_Box&
			);*/

	};

}

#endif // !_VoyageMesh_StdOptNode_Calculator_Header
