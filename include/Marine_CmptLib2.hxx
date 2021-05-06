#pragma once
#ifndef _Marine_CmptLib2_Header
#define _Marine_CmptLib2_Header

#include <Marine_SectionsFwd.hxx>
#include <Marine_xSectionParam.hxx>
#include <Marine_Module.hxx>

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

		static TnbMarine_EXPORT unsigned short LeverArm_Verbose1;
		static TnbMarine_EXPORT unsigned short LeverArm_Verbose2;
		static TnbMarine_EXPORT unsigned short CrossCurve_Verbose;
		static TnbMarine_EXPORT unsigned short Volume_Verbose;

		static TnbMarine_EXPORT Standard_Real vol_criterion;

		static TnbMarine_EXPORT marineLib::xSectionParam
			LeverArm
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections,
				const Standard_Real x0,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT Standard_Real
			LeverArm
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections,
				const Standard_Real x0,
				const Standard_Real theVolume,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT std::vector<marineLib::xSectionParam>
			CrossCurve
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections,
				const std::vector<std::shared_ptr<Marine_WaterDomain>>& theWaters,
				const Standard_Real x0,
				const gp_Ax1& theK,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT std::vector<marineLib::xSectionParam>
			Volume
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections, 
				const std::vector<std::shared_ptr<Marine_WaterDomain>>& theWaters, 
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);
	};
}

#endif // !_Marine_CmptLib2_Header
