#pragma once
#ifndef _HydStatic_CurveLib_Header
#define _HydStatic_CurveLib_Header

#include <Marine_BodiesFwd.hxx>
#include <Marine_VesselParams.hxx>
#include <HydStatic_HydGphCurvesFwd.hxx>
#include <HydStatic_xDraft.hxx>

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
	class Marine_WireFrameModel;
	class NumAlg_AdaptiveInteg_Info;

	namespace marineLib { struct xSectionParam; }

	class HydStatic_CurveLib
	{

		static Standard_Real theMinTol_;
		static Standard_Real theMaxTol_;

	public:

		typedef NumAlg_AdaptiveInteg_Info info;

		static const Standard_Real DEFAULT_MIN_TOL;
		static const Standard_Real DEFAULT_MAX_TOL;

		static Standard_Real MinTol();

		static Standard_Real MaxTol();

		static void SetMinTol(const Standard_Real theTol);

		static void SetMaxTol(const Standard_Real theTol);

		static std::vector<hydStcGphLib::xDraft> 
			CalcLCB
			(
				const std::vector<std::shared_ptr<marineLib::Body_Wetted>>& theBodies,
				const std::vector<Standard_Real>& theTs,
				const std::shared_ptr<info>& theInfo
			);

		static std::vector<hydStcGphLib::xDraft> 
			CalcLCB
			(
				const Marine_WireFrameModel& theBody,
				const Geo_xDistb& theDistb,
				const std::shared_ptr<Marine_Domain>& theDomain,
				const std::shared_ptr<info>& theInfo
			);

		static std::vector<hydStcGphLib::xDraft>
			CalcLCF
			(
				const std::vector<std::shared_ptr<marineLib::Body_Wetted>>& theBodies,
				const std::vector<Standard_Real>& theTs,
				const std::shared_ptr<info>& theInfo
			);

		static std::vector<hydStcGphLib::xDraft>
			CalcLCF
			(
				const Marine_WireFrameModel& theBody,
				const Geo_xDistb& theDistb,
				const std::shared_ptr<Marine_Domain>& theDomain,
				const std::shared_ptr<info>& theInfo
			);

		static std::vector<hydStcGphLib::xDraft>
			CalcAW
			(
				const std::vector<std::shared_ptr<marineLib::Body_Wetted>>& theBodies,
				const std::vector<Standard_Real>& theTs,
				const std::shared_ptr<info>& theInfo
			);

		static std::vector<hydStcGphLib::xDraft>
			CalcAW
			(
				const Marine_WireFrameModel& theBody,
				const Geo_xDistb& theDistb,
				const std::shared_ptr<Marine_Domain>& theDomain,
				const std::shared_ptr<info>& theInfo
			);

		static std::vector<hydStcGphLib::xDraft>
			CalcDISPV
			(
				const std::vector<std::shared_ptr<marineLib::Body_Wetted>>& theBodies,
				const std::vector<Standard_Real>& theTs,
				const std::shared_ptr<info>& theInfo
			);

		static std::vector<hydStcGphLib::xDraft>
			CalcDISPV
			(
				const Marine_WireFrameModel& theBody,
				const Geo_xDistb& theDistb,
				const std::shared_ptr<Marine_Domain>& theDomain,
				const std::shared_ptr<info>& theInfo
			);

		static std::vector<hydStcGphLib::xDraft>
			CalcMCT
			(
				const std::vector<std::shared_ptr<marineLib::Body_Wetted>>& theBodies,
				const std::vector<hydStcGphLib::xDraft>& theVolume,
				const std::shared_ptr<info>& theInfo
			);

		static std::vector<hydStcGphLib::xDraft>
			CalcMCT
			(
				const Marine_WireFrameModel& theBody,
				const Geo_xDistb& theDistb,
				const std::shared_ptr<Marine_Domain>& theDomain,
				const std::shared_ptr<info>& theInfo
			);

		static std::vector<hydStcGphLib::xDraft>
			CalcKB
			(
				const std::vector<std::shared_ptr<marineLib::Body_Wetted>>& theBodies,
				const Marine_BaseLine& theBase,
				const std::vector<Standard_Real>& theTs,
				const std::shared_ptr<info>& theInfo
			);

		static std::vector<hydStcGphLib::xDraft>
			CalcKB
			(
				const Marine_WireFrameModel& theBody,
				const Marine_BaseLine& theBase,
				const Geo_xDistb& theDistb,
				const std::shared_ptr<Marine_Domain>& theDomain,
				const std::shared_ptr<info>& theInfo
			);

		static std::vector<hydStcGphLib::xDraft>
			CalcBM
			(
				const std::vector<std::shared_ptr<marineLib::Body_Wetted>>& theBodies,
				const std::vector<hydStcGphLib::xDraft>& theVolume,
				const std::shared_ptr<info>& theInfo
			);

		static std::vector<hydStcGphLib::xDraft>
			CalcBM
			(
				const Marine_WireFrameModel& theModel,
				const Geo_xDistb& theDistb,
				const std::shared_ptr<Marine_Domain>& theDomain,
				const std::shared_ptr<info>& theInfo
			);

		static std::vector<hydStcGphLib::xDraft>
			CalcBML
			(
				const std::vector<std::shared_ptr<marineLib::Body_Wetted>>& theBodies,
				const std::vector<hydStcGphLib::xDraft>& theVolume,
				const std::shared_ptr<info>& theInfo
			);

		static std::vector<hydStcGphLib::xDraft>
			CalcBML
			(
				const Marine_WireFrameModel& theModel,
				const Geo_xDistb& theDistb,
				const std::shared_ptr<Marine_Domain>& theDomain,
				const std::shared_ptr<info>& theInfo
			);

		static marineLib::LCB Value(const hydStcGphLib::LCB& theCurve, const Standard_Real theT);


	};
}

#endif // !_HydStatic_CurveLib_Header
