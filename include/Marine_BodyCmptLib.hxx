#pragma once
#ifndef _Marine_BodyCmptLib_Header
#define _Marine_BodyCmptLib_Header

#include <Marine_BodiesFwd.hxx>
#include <Marine_xSectionParam.hxx>
#include <Marine_Module.hxx>

#include <memory>
#include <vector>

class gp_Ax1;

namespace tnbLib
{

	// Forward Declarations
	class NumAlg_AdaptiveInteg_Info;
	class Marine_MultLevWaterDomain;

	class Marine_BodyCmptLib
	{

	public:

		static TnbMarine_EXPORT marineLib::xSectionParam
			LeverArm
			(
				const std::shared_ptr<Marine_Body>& theBody,
				const Standard_Real x0,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT marineLib::xSectionParam
			LeverArm
			(
				const marineLib::Body_Displacer& theBody,
				const Standard_Real x0, 
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT marineLib::xSectionParam
			LeverArm
			(
				const marineLib::Body_Tank& theBody,
				const Standard_Real x0,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT Standard_Real
			LeverArm
			(
				const std::shared_ptr<Marine_Body>& theBody,
				const Standard_Real x0,
				const Standard_Real theVolume,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT Standard_Real
			LeverArm
			(
				const marineLib::Body_Displacer& theBody,
				const Standard_Real x0,
				const Standard_Real theVolume,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT Standard_Real
			LeverArm
			(
				const marineLib::Body_Tank& theBody,
				const Standard_Real x0, 
				const Standard_Real theVolume, 
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		//- Throw an exception if body is not displacer or tank
		static TnbMarine_EXPORT xSectParList
			CrossCurve
			(
				const std::shared_ptr<Marine_Body>& theBody,
				const Marine_MultLevWaterDomain& theWaters,
				const Standard_Real x0,
				const gp_Ax1& theK,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT xSectParList
			CrossCurve
			(
				const marineLib::Body_Displacer& theBody, 
				const Marine_MultLevWaterDomain& theWaters,
				const Standard_Real x0, 
				const gp_Ax1& theK, 
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT xSectParList
			CrossCurve
			(
				const marineLib::Body_Tank& theBody, 
				const Marine_MultLevWaterDomain& theWaters,
				const Standard_Real x0, 
				const gp_Ax1& theK,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);
	};
}

#endif // !_Marine_BodyCmptLib_Header
