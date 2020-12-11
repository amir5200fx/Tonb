#pragma once
#ifndef _HydStatic_CurveLib_Header
#define _HydStatic_CurveLib_Header

#include <Marine_BodiesFwd.hxx>
#include <Marine_VesselParams.hxx>
#include <HydStatic_HydGphCurvesFwd.hxx>
#include <HydStatic_xDraft.hxx>
#include <HydStatic_Module.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Geo_xDistb;
	class Marine_BaseLine;
	class Marine_Domain;
	class Marine_WaterDomain;
	class Marine_WaterDomains;
	class Marine_WireFrameShape;
	class NumAlg_AdaptiveInteg_Info;

	namespace marineLib { struct xSectionParam; }

	class HydStatic_CurveLib
	{

		static TnbHydStatic_EXPORT Standard_Real theMinTol_;
		static TnbHydStatic_EXPORT Standard_Real theMaxTol_;

	public:

		typedef NumAlg_AdaptiveInteg_Info info;

		static TnbHydStatic_EXPORT const Standard_Real DEFAULT_MIN_TOL;
		static TnbHydStatic_EXPORT const Standard_Real DEFAULT_MAX_TOL;

		static TnbHydStatic_EXPORT Standard_Real MinTol();

		static TnbHydStatic_EXPORT Standard_Real MaxTol();

		static TnbHydStatic_EXPORT void SetMinTol(const Standard_Real theTol);

		static TnbHydStatic_EXPORT void SetMaxTol(const Standard_Real theTol);

		static TnbHydStatic_EXPORT std::vector<hydStcGphLib::xDraft>
			CalcLCB
			(
				const std::vector<std::shared_ptr<marineLib::Body_Wetted>>& theBodies,
				const std::vector<Standard_Real>& theTs,
				const std::shared_ptr<info>& theInfo
			);

		static TnbHydStatic_EXPORT std::vector<hydStcGphLib::xDraft>
			CalcLCB
			(
				const std::shared_ptr<Marine_WireFrameShape>& theBody,
				const Geo_xDistb& theDistb,
				const std::shared_ptr<Marine_Domain>& theDomain,
				const std::shared_ptr<info>& theInfo
			);

		static TnbHydStatic_EXPORT std::vector<hydStcGphLib::xDraft>
			CalcLCF
			(
				const std::vector<std::shared_ptr<marineLib::Body_Wetted>>& theBodies,
				const std::vector<Standard_Real>& theTs,
				const std::shared_ptr<info>& theInfo
			);

		static TnbHydStatic_EXPORT std::vector<hydStcGphLib::xDraft>
			CalcLCF
			(
				const std::shared_ptr<Marine_WireFrameShape>& theBody,
				const Geo_xDistb& theDistb,
				const std::shared_ptr<Marine_Domain>& theDomain,
				const std::shared_ptr<info>& theInfo
			);

		static TnbHydStatic_EXPORT std::vector<hydStcGphLib::xDraft>
			CalcAW
			(
				const std::vector<std::shared_ptr<marineLib::Body_Wetted>>& theBodies,
				const std::vector<Standard_Real>& theTs,
				const std::shared_ptr<info>& theInfo
			);

		static TnbHydStatic_EXPORT std::vector<hydStcGphLib::xDraft>
			CalcAW
			(
				const std::shared_ptr<Marine_WireFrameShape>& theBody,
				const Geo_xDistb& theDistb,
				const std::shared_ptr<Marine_Domain>& theDomain,
				const std::shared_ptr<info>& theInfo
			);

		static TnbHydStatic_EXPORT std::vector<hydStcGphLib::xDraft>
			CalcDISPV
			(
				const std::vector<std::shared_ptr<marineLib::Body_Wetted>>& theBodies,
				const std::vector<Standard_Real>& theTs,
				const std::shared_ptr<info>& theInfo
			);

		static TnbHydStatic_EXPORT std::vector<hydStcGphLib::xDraft>
			CalcDISPV
			(
				const std::shared_ptr<Marine_WireFrameShape>& theBody,
				const Geo_xDistb& theDistb,
				const std::shared_ptr<Marine_Domain>& theDomain,
				const std::shared_ptr<info>& theInfo
			);

		static TnbHydStatic_EXPORT std::vector<hydStcGphLib::xDraft>
			CalcMCT
			(
				const std::vector<std::shared_ptr<marineLib::Body_Wetted>>& theBodies,
				const std::vector<hydStcGphLib::xDraft>& theVolume,
				const std::shared_ptr<info>& theInfo
			);

		static TnbHydStatic_EXPORT std::vector<hydStcGphLib::xDraft>
			CalcMCT
			(
				const std::shared_ptr<Marine_WireFrameShape>& theBody,
				const Geo_xDistb& theDistb,
				const std::shared_ptr<Marine_Domain>& theDomain,
				const std::shared_ptr<info>& theInfo
			);

		static TnbHydStatic_EXPORT std::vector<hydStcGphLib::xDraft>
			CalcKB
			(
				const std::vector<std::shared_ptr<marineLib::Body_Wetted>>& theBodies,
				const Marine_BaseLine& theBase,
				const std::vector<Standard_Real>& theTs,
				const std::shared_ptr<info>& theInfo
			);

		static TnbHydStatic_EXPORT std::vector<hydStcGphLib::xDraft>
			CalcKB
			(
				const std::shared_ptr<Marine_WireFrameShape>& theBody,
				const Marine_BaseLine& theBase,
				const Geo_xDistb& theDistb,
				const std::shared_ptr<Marine_Domain>& theDomain,
				const std::shared_ptr<info>& theInfo
			);

		static TnbHydStatic_EXPORT std::vector<hydStcGphLib::xDraft>
			CalcBM
			(
				const std::vector<std::shared_ptr<marineLib::Body_Wetted>>& theBodies,
				const std::vector<hydStcGphLib::xDraft>& theVolume,
				const std::shared_ptr<info>& theInfo
			);

		static TnbHydStatic_EXPORT std::vector<hydStcGphLib::xDraft>
			CalcBM
			(
				const std::shared_ptr<Marine_WireFrameShape>& theBody,
				const Geo_xDistb& theDistb,
				const std::shared_ptr<Marine_Domain>& theDomain,
				const std::shared_ptr<info>& theInfo
			);

		static TnbHydStatic_EXPORT std::vector<hydStcGphLib::xDraft>
			CalcBML
			(
				const std::vector<std::shared_ptr<marineLib::Body_Wetted>>& theBodies,
				const std::vector<hydStcGphLib::xDraft>& theVolume,
				const std::shared_ptr<info>& theInfo
			);

		static TnbHydStatic_EXPORT std::vector<hydStcGphLib::xDraft>
			CalcBML
			(
				const std::shared_ptr<Marine_WireFrameShape>& theBody,
				const Geo_xDistb& theDistb,
				const std::shared_ptr<Marine_Domain>& theDomain,
				const std::shared_ptr<info>& theInfo
			);

		static TnbHydStatic_EXPORT marineLib::LCB Value(const hydStcGphLib::LCB& theCurve, const Standard_Real theT);


	};
}

#endif // !_HydStatic_CurveLib_Header
