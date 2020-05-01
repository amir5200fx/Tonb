#pragma once
#ifndef _HydStatic_CmptLib_Header
#define _HydStatic_CmptLib_Header

#include <Standard_TypeDef.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Pnt2d;
	class Marine_Body;
	class Marine_CmpSection;
	class Marine_GraphCurve;
	class HydStatic_BnjCurve;
	class HydStatic_Bonjean;
	class HydStatic_CrossCurves;
	class HydStatic_CrsCurve;
	class HydStatic_GzQ;
	class HydStatic_GzQP;
	class HydStatic_GzQP2;
	class HydStatic_AuCurve;
	class HydStatic_ArmCurve;
	class HydStatic_rArmCurve;
	class HydStatic_hArmCurve;
	class HydStatic_WDiffCurve;
	class HydStatic_EqQ;
	class NumAlg_AdaptiveInteg_Info;

	struct HydStatic_Bonjean_Entity;

	namespace marineLib { struct xSectionParam; }
	namespace hydStcLib { class rArmCurve_Eff; }

	class HydStatic_CmptLib
	{

	public:

		static Standard_Real 
			CalcArea
			(
				const HydStatic_ArmCurve& theCurve,
				const Standard_Real y0, 
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static Standard_Real 
			Draft
			(
				const Standard_Real x, 
				const Standard_Real theTa, 
				const Standard_Real xTa, 
				const Standard_Real theTf, 
				const Standard_Real xTf
			);

		static Standard_Real
			Draft
			(
				const Marine_CmpSection& theSect,
				const Standard_Real theTa, 
				const Standard_Real xTa, 
				const Standard_Real theTf, 
				const Standard_Real xTf
			);

		static std::vector<Standard_Real>
			RetrieveDrafts
			(
				const Marine_Body& theBody,
				const Standard_Real theTa, 
				const Standard_Real xTa, 
				const Standard_Real theTf, 
				const Standard_Real xTf
			);

		static std::vector<Standard_Real>
			RetrieveXs
			(
				const Marine_Body& theBody
			);

		static std::vector<std::shared_ptr<HydStatic_Bonjean_Entity>>
			RetrieveBnjCurves(const HydStatic_Bonjean& theBonjean);

		static std::vector<marineLib::xSectionParam>
			RetrieveAreas(const std::vector<std::shared_ptr<HydStatic_Bonjean_Entity>>& theCurves, const std::vector<Standard_Real>& theT);

		static std::vector<marineLib::xSectionParam>
			RetrieveAreas(const HydStatic_Bonjean& theBonjean, const Standard_Real theTa, const Standard_Real xTa, const Standard_Real theTf, const Standard_Real xTf);

		static std::vector<HydStatic_GzQ>
			LeverArms
			(
				const std::vector<std::shared_ptr<HydStatic_CrsCurve>>& theCurves, 
				const Standard_Real theVol
			);

		static std::vector<marineLib::xSectionParam>
			GZ
			(
				const std::vector<HydStatic_GzQ>& thePairs, 
				const Standard_Real theKG
			);

		static HydStatic_GzQP 
			CalcMaxRightingArm
			(
				const HydStatic_ArmCurve& theCurve
			);

		static HydStatic_GzQP 
			CalcMaxRightingArmPort
			(
				const HydStatic_ArmCurve& theCurve
			);

		static std::vector<HydStatic_GzQP> 
			CalcStaticalStabilityPoints
			(
				const HydStatic_rArmCurve& theCurve,
				const Standard_Real theMoment
			);

		static std::vector<HydStatic_GzQP2>
			CalcStaticalStabilityPoints
			(
				const HydStatic_rArmCurve& theCurve,
				const HydStatic_hArmCurve& theHeeling
			);

		static std::tuple<HydStatic_EqQ, HydStatic_EqQ>
			CalcStaticalStabilityPoints_Starboard
			(
				const std::shared_ptr<HydStatic_rArmCurve>& theCurve,
				const std::shared_ptr<HydStatic_hArmCurve>& theHeeling
			);

		static const HydStatic_EqQ&
			GetStable
			(
				const std::tuple<HydStatic_EqQ, HydStatic_EqQ>& t
			);

		static const HydStatic_EqQ&
			GetUnStable
			(
				const std::tuple<HydStatic_EqQ, HydStatic_EqQ>& t
			);

		static std::vector<HydStatic_GzQP2>
			CalcDynamicalStabilityPoints
			(
				const hydStcLib::rArmCurve_Eff& theRighting,
				const HydStatic_hArmCurve& theHeeling
			);

		static std::vector<HydStatic_GzQP>
			CalcDynamicalStabilityPoints
			(
				const HydStatic_WDiffCurve& theWDiffCurve
			);

		static std::shared_ptr<HydStatic_WDiffCurve>
			CalcWorkDifference
			(
				const std::shared_ptr<HydStatic_hArmCurve>& theHeeling, 
				const std::shared_ptr<hydStcLib::rArmCurve_Eff>& theRighting
			);

		static std::vector<HydStatic_GzQ> 
			CalcAuCurve
			(
				const HydStatic_ArmCurve& theCurve, 
				const Standard_Real y0,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static void 
			CalcParameters
			(
				const std::shared_ptr<HydStatic_ArmCurve>& theArm
			);
	
	};
}

#endif // !_HydStatic_CmptLib_Header
