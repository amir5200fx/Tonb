#pragma once
#ifndef _HydStatic_CmptLib_Header
#define _HydStatic_CmptLib_Header

#include <Standard_TypeDef.hxx>
#include <Marine_VesselParam_DISPV.hxx>
#include <HydStatic_Module.hxx>
#include <HydStatic_rArmCurvesFwd.hxx>
#include <HydStatic_ShapesFwd.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

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
	class HydStatic_Spacing;
	class HydStatic_TankShape;
	class NumAlg_AdaptiveInteg_Info;

	struct HydStatic_Bonjean_Entity;

	namespace marineLib { struct xSectionParam; }
	namespace hydStcLib { class rArmCurve_Eff; }

	class HydStatic_CmptLib
	{

	public:

		static TnbHydStatic_EXPORT Standard_Real 
			RetrieveDispv
			(
				const HydStatic_TankShape& theTank
			);

		static TnbHydStatic_EXPORT Standard_Real
			CalcArea
			(
				const HydStatic_ArmCurve& theCurve,
				const Standard_Real y0, 
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbHydStatic_EXPORT Standard_Real
			Draft
			(
				const Standard_Real x, 
				const Standard_Real theTa, 
				const Standard_Real xTa, 
				const Standard_Real theTf, 
				const Standard_Real xTf
			);

		static TnbHydStatic_EXPORT Standard_Real
			Draft
			(
				const Marine_CmpSection& theSect,
				const Standard_Real theTa, 
				const Standard_Real xTa, 
				const Standard_Real theTf, 
				const Standard_Real xTf
			);

		static TnbHydStatic_EXPORT std::vector<Standard_Real>
			RetrieveDrafts
			(
				const Marine_Body& theBody,
				const Standard_Real theTa, 
				const Standard_Real xTa, 
				const Standard_Real theTf, 
				const Standard_Real xTf
			);

		static TnbHydStatic_EXPORT std::vector<Standard_Real>
			RetrieveXs
			(
				const Marine_Body& theBody
			);

		static std::vector<std::shared_ptr<HydStatic_Bonjean_Entity>>
			RetrieveBnjCurves(const HydStatic_Bonjean& theBonjean)
		{
			NotImplemented;
			return std::vector<std::shared_ptr<HydStatic_Bonjean_Entity>>();
		}

		static std::vector<marineLib::xSectionParam>
			RetrieveAreas(const std::vector<std::shared_ptr<HydStatic_Bonjean_Entity>>& theCurves, const std::vector<Standard_Real>& theT)
		{
			NotImplemented;
			return std::vector<marineLib::xSectionParam>();
		}

		static TnbHydStatic_EXPORT std::vector<marineLib::xSectionParam>
			RetrieveAreas
			(
				const HydStatic_Bonjean& theBonjean,
				const Standard_Real theTa, 
				const Standard_Real xTa,
				const Standard_Real theTf, 
				const Standard_Real xTf
			);

		static TnbHydStatic_EXPORT std::vector<HydStatic_GzQ>
			LeverArms
			(
				const std::vector<std::shared_ptr<HydStatic_CrsCurve>>& theCurves, 
				const Standard_Real theVol
			);

		static TnbHydStatic_EXPORT std::vector<marineLib::xSectionParam>
			GZ
			(
				const std::vector<HydStatic_GzQ>& thePairs, 
				const Standard_Real theKG
			);

		static TnbHydStatic_EXPORT std::vector<marineLib::xSectionParam> 
			FSE
			(
				const std::vector<HydStatic_GzQ>& thePairs, 
				const marineLib::DISPV& theTank,
				const marineLib::DISPV& theShip
			);

		static TnbHydStatic_EXPORT HydStatic_GzQP
			CalcMaxRightingArm
			(
				const HydStatic_ArmCurve& theCurve
			);

		static TnbHydStatic_EXPORT HydStatic_GzQP
			CalcMaxRightingArmPort
			(
				const HydStatic_ArmCurve& theCurve
			);

		static TnbHydStatic_EXPORT std::vector<HydStatic_GzQP>
			CalcStaticalStabilityPoints
			(
				const HydStatic_rArmCurve& theCurve,
				const Standard_Real theMoment
			);

		static TnbHydStatic_EXPORT std::vector<HydStatic_GzQP2>
			CalcStaticalStabilityPoints
			(
				const HydStatic_rArmCurve& theCurve,
				const HydStatic_hArmCurve& theHeeling
			);

		static TnbHydStatic_EXPORT std::tuple<HydStatic_EqQ, HydStatic_EqQ>
			CalcStaticalStabilityPoints_Starboard
			(
				const std::shared_ptr<HydStatic_rArmCurve>& theCurve,
				const std::shared_ptr<HydStatic_hArmCurve>& theHeeling
			);

		static TnbHydStatic_EXPORT const HydStatic_EqQ&
			GetStable
			(
				const std::tuple<HydStatic_EqQ, HydStatic_EqQ>& t
			);

		static TnbHydStatic_EXPORT const HydStatic_EqQ&
			GetUnStable
			(
				const std::tuple<HydStatic_EqQ, HydStatic_EqQ>& t
			);

		static TnbHydStatic_EXPORT std::vector<HydStatic_GzQP2>
			CalcDynamicalStabilityPoints
			(
				const hydStcLib::rArmCurve_Eff& theRighting,
				const HydStatic_hArmCurve& theHeeling
			);

		static TnbHydStatic_EXPORT std::vector<HydStatic_GzQP>
			CalcDynamicalStabilityPoints
			(
				const HydStatic_WDiffCurve& theWDiffCurve
			);

		static TnbHydStatic_EXPORT std::shared_ptr<HydStatic_WDiffCurve>
			CalcWorkDifference
			(
				const std::shared_ptr<HydStatic_hArmCurve>& theHeeling, 
				const std::shared_ptr<hydStcLib::rArmCurve_Eff>& theRighting
			);

		static TnbHydStatic_EXPORT std::vector<marineLib::xSectionParam> 
			CalcAreaBetween
			(
				const std::shared_ptr<HydStatic_hArmCurve>& theHeeling,
				const std::shared_ptr<hydStcLib::rArmCurve_Eff>& theRighting,
				const std::shared_ptr<HydStatic_Spacing>& theSpacing
			);

		static TnbHydStatic_EXPORT std::vector<HydStatic_GzQ>
			CalcAuCurve
			(
				const HydStatic_ArmCurve& theCurve, 
				const Standard_Real y0,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbHydStatic_EXPORT std::shared_ptr<hydStcLib::rArmCurve_Eff> 
			CalcEffectiveRightingArm
			(
				const std::shared_ptr<hydStcLib::rArmCurve_Body>& theBody, 
				const std::shared_ptr<hydStcLib::rArmCurve_Tanks>& theTanks
			);

		static TnbHydStatic_EXPORT std::shared_ptr<hydStcLib::rArmCurve_Eff>
			CalcEffectiveRightingArm
			(
				const std::shared_ptr<hydStcLib::rArmCurve_Body>& theBody
			);

		static TnbHydStatic_EXPORT void
			CalcParameters
			(
				const std::shared_ptr<HydStatic_ArmCurve>& theArm
			);
	
		static TnbHydStatic_EXPORT void 
			CalcDomain
			(
				const std::shared_ptr<HydStatic_TankShape>& theTank
			);
	};
}

#endif // !_HydStatic_CmptLib_Header
