#pragma once
#ifndef _HydStatic_Tools_Header
#define _HydStatic_Tools_Header

#include <Standard_Handle.hxx>
#include <Standard_TypeDef.hxx>
#include <Marine_xSectionParam.hxx>
#include <Marine_VesselParams.hxx>
#include <Marine_EnvtParams.hxx>
#include <Marine_CoeffParams.hxx>
#include <HydStatic_rArmCurvesFwd.hxx>
#include <HydStatic_rArmCurve_PrimsFwd.hxx>
#include <HydStatic_Module.hxx>
#include <HydStatic_CurveMakerType.hxx>
#include <HydStatic_xDraft.hxx>
#include <HydStatic_rArmCurve_Cmpt.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <vector>
#include <memory>

class Geom2d_Curve;

namespace tnbLib
{

	namespace marineLib { struct xSectionParam; }

	// Forward Declarations
	class TModel_Surface;
	class HydStatic_GzQ;
	class HydStatic_GzQP;
	class HydStatic_rArmCurve;
	class HydStatic_hArmCurve;
	class HydStatic_AuCurve;
	class HydStatic_rAuCurve;
	class HydStatic_Spacing;
	class HydStatic_CrsCurve;
	class HydStatic_CrsCurveQ;
	class HydStatic_TankCapacityCurveQ;
	class NumAlg_AdaptiveInteg_Info;
	
	class Pnt2d;

	namespace hydStcLib { class rArmCurve_Eff; }

	class HydStatic_Tools
	{

	public:

		typedef NumAlg_AdaptiveInteg_Info info;

		static TnbHydStatic_EXPORT Standard_Real 
			CalcWindHeelingArm
			(
				const marineLib::Pressure& theWindPrss, 
				const marineLib::Av& theAv,
				const marineLib::Hv& theHv, 
				const marineLib::T& theDraft, 
				const marineLib::Gravity& theG,
				const marineLib::DISPM& theDispl,
				const marineLib::HEELANG& theAngl
			);

		//- Quoting Handbuch der werfen, Vol. VII, Wegner shows that for 95% of 80 cargo ships the values of CD 
		//- ranged between 0.19 and 0.25. For a few trawlers the values ranged between 0.3 and 0.35. ref: Ship Hydrostatics and Stability
		static TnbHydStatic_EXPORT Standard_Real
			CalcTurningHeelingArm
			(
				const marineLib::coeff::CD& theCd,
				const marineLib::Velocity& theVel,
				const marineLib::Gravity& theG,
				const marineLib::LPP& theLpp, 
				const marineLib::KG& theKg, 
				const marineLib::T& theDraft, 
				const marineLib::HEELANG& theAngl
			);

		static TnbHydStatic_EXPORT std::vector<hydStcGphLib::xDraft> 
			SteffenTessellation
			(
				const std::vector<hydStcGphLib::xDraft>& theQ,
				const unsigned int nbPts
			);

		static TnbHydStatic_EXPORT std::shared_ptr<HydStatic_Spacing>
			UniformSpacing
			(
				const Standard_Integer n, 
				const Standard_Real u0, 
				const Standard_Real u1
			);

		static TnbHydStatic_EXPORT std::shared_ptr<HydStatic_Spacing> 
			CustomSpacing
			(
				const std::vector<Standard_Real>& Us,
				const Standard_Real u0, 
				const Standard_Real u1
			);

		static TnbHydStatic_EXPORT std::shared_ptr<HydStatic_CrsCurveQ>
			Trim
			(
				const std::shared_ptr<HydStatic_CrsCurveQ>& theCurve, 
				const Standard_Real x0,
				const Standard_Real x1, 
				const hydStcLib::CurveMakerType t,
				const Standard_Real tol = gp::Resolution()
			);

		static TnbHydStatic_EXPORT Standard_Real 
			CalcZ
			(
				const HydStatic_TankCapacityCurveQ&, 
				const Standard_Real theVolume
			);

		static TnbHydStatic_EXPORT std::shared_ptr<HydStatic_CrsCurve> 
			CrossCurve
			(
				const Handle(Geom2d_Curve)& theGeom, 
				const hydStcLib::CurveMakerType t
			);

		static TnbHydStatic_EXPORT std::shared_ptr<HydStatic_CrsCurve> 
			CrossCurve
			(
				Handle(Geom2d_Curve)&& theGeom, 
				const hydStcLib::CurveMakerType t
			);

		static TnbHydStatic_EXPORT std::shared_ptr<HydStatic_hArmCurve> 
			HeelingCurve
			(
				const std::vector<HydStatic_GzQP>& theQs,
				const hydStcLib::CurveMakerType t
			);

		static TnbHydStatic_EXPORT std::shared_ptr<HydStatic_hArmCurve> 
			HeelingCurve
			(
				const std::vector<HydStatic_GzQP>&& theQs,
				const hydStcLib::CurveMakerType t
			);

		static TnbHydStatic_EXPORT std::vector<HydStatic_GzQ> 
			MirroredByO
			(
				const std::vector<HydStatic_GzQ>& theQs
			);

		static TnbHydStatic_EXPORT std::vector<HydStatic_GzQP> 
			MirroredByO
			(
				const std::vector<HydStatic_GzQP>& theQs
			);

		static TnbHydStatic_EXPORT std::vector<HydStatic_GzQ> 
			MirroredByOy
			(
				const std::vector<HydStatic_GzQ>& theQs
			);

		static TnbHydStatic_EXPORT std::vector<HydStatic_GzQP> 
			MirroredByOy
			(
				const std::vector<HydStatic_GzQP>& theQs
			);

		static TnbHydStatic_EXPORT std::vector<HydStatic_GzQ> 
			Merged
			(
				const std::vector<HydStatic_GzQ>& theQs
			);

		/*WARNING: the parameter for GzQP is set to zero after merging!*/
		static TnbHydStatic_EXPORT std::vector<HydStatic_GzQP> 
			Merged
			(
				const std::vector<HydStatic_GzQP>& theQs
			);

		static TnbHydStatic_EXPORT std::shared_ptr<hydStcLib::rArmCurve_Body> 
			ExpandToPort
			(
				const std::shared_ptr<hydStcLib::rArmCurve_Body>& theGZ
			);

		static TnbHydStatic_EXPORT std::shared_ptr<hydStcLib::rArmCurve_FSLq> 
			ExpandToPort
			(
				const std::shared_ptr<hydStcLib::rArmCurve_FSLq>& theGz
			);

		static TnbHydStatic_EXPORT std::shared_ptr<hydStcLib::rArmCurve_Hlds> 
			ExpandToPort
			(
				const std::shared_ptr<hydStcLib::rArmCurve_Hlds>& theGZ
			);

		static TnbHydStatic_EXPORT std::shared_ptr<hydStcLib::rArmCurve_LDT> 
			ExpandToPort
			(
				const std::shared_ptr<hydStcLib::rArmCurve_LDT>& theGZ
			);

		static TnbHydStatic_EXPORT std::shared_ptr<hydStcLib::rArmCurve_LDV> 
			ExpandToPort
			(
				const std::shared_ptr<hydStcLib::rArmCurve_LDV>& theGZ
			);

		static std::shared_ptr<HydStatic_rArmCurve> ExpandRigthingArmToPort(const HydStatic_rArmCurve& theCurve, const marineLib::KG& theKG)
		{
			NotImplemented;
			return std::shared_ptr<HydStatic_rArmCurve>();
		}

		static TnbHydStatic_EXPORT std::vector<marineLib::xSectionParam> 
			OffsetsFrom
			(
				const std::vector<HydStatic_GzQ>& theQs
			);

		static TnbHydStatic_EXPORT std::vector<marineLib::xSectionParam> 
			OffsetsFrom
			(
				const std::vector<HydStatic_GzQP>& theQs
			);

		//- return true if the Arm curve is covering the target curve
		static TnbHydStatic_EXPORT Standard_Boolean 
			IsCoating
			(
				const std::shared_ptr<HydStatic_rArmCurve>& theArm,
				const std::shared_ptr<HydStatic_rArmCurve>& theTarget
			);

		static TnbHydStatic_EXPORT std::vector<HydStatic_GzQ> 
			Union
			(
				const std::shared_ptr<HydStatic_rArmCurve>& theC0,
				const std::shared_ptr<HydStatic_rArmCurve>& theC1
			);

		static TnbHydStatic_EXPORT std::vector<HydStatic_GzQ> 
			Subtract
			(
				const std::shared_ptr<HydStatic_rArmCurve>& theC0,
				const std::shared_ptr<HydStatic_rArmCurve>& theC1
			);

		template<class CurveType>
		static std::shared_ptr<CurveType> MakeRightCurve
		(
			const std::vector<marineLib::xSectionParam>& theQs,
			const hydStcLib::CurveMakerType t
		);

		static TnbHydStatic_EXPORT std::shared_ptr<HydStatic_hArmCurve> 
			MakeHeelCurve
			(
				const std::vector<marineLib::xSectionParam>& theQs
			);

		static TnbHydStatic_EXPORT std::shared_ptr<hydStcLib::rArmCurve_Eff> 
			MakeEffRightCurve
			(
				const std::vector<marineLib::xSectionParam>& theQs
			);

		static TnbHydStatic_EXPORT std::shared_ptr<hydStcLib::rArmCurve_Tanks> 
			MakeTanksRightCurve
			(
				std::shared_ptr<hydStcLib::rArmCurve_Cmpt<hydStcLib::rArmCurve_FSLq>>&& theCmpt
			);

		static TnbHydStatic_EXPORT void
			AuCurve
			(
				const std::shared_ptr<hydStcLib::rArmCurve_Eff>& theCurve, 
				const hydStcLib::CurveMakerType t,
				const Standard_Real y0, 
				const std::shared_ptr<info>& theInfo
			);

		static TnbHydStatic_EXPORT void
			AuCurve
			(
				const std::shared_ptr<HydStatic_hArmCurve>& theCurve,
				const hydStcLib::CurveMakerType t,
				const Standard_Real y0,
				const std::shared_ptr<info>& theInfo
			);


	};
}

#include <HydStatic_ToolsI.hxx>

#endif // !_HydStatic_Tools_Header
