#pragma once
#ifndef _Marine_CmptLib2_Header
#define _Marine_CmptLib2_Header

#include <Marine_SectionsFwd.hxx>
#include <Marine_xSectionParam.hxx>

#include <vector>
#include <memory>

class gp_Ax1;

namespace tnbLib
{

	// Forward Declarations
	class NumAlg_AdaptiveInteg_Info;
	class Marine_CmpSection;
	class Marine_WaterDomain;

	class Marine_CmptLib2
	{

	public:

		static marineLib::xSectionParam
			LeverArm
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections,
				const Standard_Real x0,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static Standard_Real
			LeverArm
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections,
				const Standard_Real x0,
				const Standard_Real theVolume,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static std::vector<marineLib::xSectionParam>
			CrossCurve
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections,
				const std::vector<std::shared_ptr<Marine_WaterDomain>>& theWaters,
				const Standard_Real x0,
				const gp_Ax1& theK,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);
	};
}

#endif // !_Marine_CmptLib2_Header
