#pragma once
#ifndef _Model_DisplNo1xPars_Header
#define _Model_DisplNo1xPars_Header

#include <Global_AccessMethod.hxx>

#include <vector>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	class Model_DisplNo1xPars
	{

		/*Private Data*/

		std::vector<Standard_Real> theXCoords_;
		std::vector<Standard_Real> theYCoords_;
		std::vector<Standard_Real> theZCoords_;

		std::vector<Standard_Real> theXDepth_;

		std::vector<Standard_Real> theXTightness_;
		std::vector<Standard_Real> theXFlare_;
		std::vector<Standard_Real> theXDeadrise_;
		std::vector<Standard_Real> theXSideslope_;
		std::vector<Standard_Real> theXSideslopeAngle_;

		std::vector<Standard_Real> theXRake_;

	public:

		// default constructor [12/23/2022 Payvand]

		Model_DisplNo1xPars()
		{}

		// constructors [12/23/2022 Payvand]


		// Public functions and operators [12/23/2022 Payvand]


		// Macros [12/23/2022 Payvand]

		GLOBAL_ACCESS_SINGLE(std::vector<Standard_Real>, XCoords)
			GLOBAL_ACCESS_SINGLE(std::vector<Standard_Real>, YCoords)
			GLOBAL_ACCESS_SINGLE(std::vector<Standard_Real>, ZCoords)
			GLOBAL_ACCESS_SINGLE(std::vector<Standard_Real>, XDepth)
			GLOBAL_ACCESS_SINGLE(std::vector<Standard_Real>, XTightness)
			GLOBAL_ACCESS_SINGLE(std::vector<Standard_Real>, XFlare)
			GLOBAL_ACCESS_SINGLE(std::vector<Standard_Real>, XDeadrise)
			GLOBAL_ACCESS_SINGLE(std::vector<Standard_Real>, XSideslope)
			GLOBAL_ACCESS_SINGLE(std::vector<Standard_Real>, XSideslopeAngle)
			GLOBAL_ACCESS_SINGLE(std::vector<Standard_Real>, XRake)

	};
}

#endif // !_Model_DisplNo1xPars_Header
