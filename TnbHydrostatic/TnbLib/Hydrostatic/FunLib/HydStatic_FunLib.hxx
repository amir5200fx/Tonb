#pragma once
#ifndef _HydStatic_FunLib_Header
#define _HydStatic_FunLib_Header

#include <Standard_TypeDef.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Geo_xDistb;
	class HydStatic_StbFun;
	class HydStatic_hArmFormula;
	class NumAlg_AdaptiveInteg_Info;

	namespace hydStcLib { class StbFun_rArm; }

	class HydStatic_FunLib
	{

		typedef NumAlg_AdaptiveInteg_Info info;

	public:

		static std::shared_ptr<Geo_xDistb> 
			RetrieveHeelDistb
			(
				const hydStcLib::StbFun_rArm& theRighting
			);

		static std::shared_ptr<HydStatic_StbFun> 
			HeelingArm
			(
				const std::shared_ptr<HydStatic_hArmFormula>& theHeeling,
				const std::shared_ptr<HydStatic_StbFun>& theRighting
			);

		static std::shared_ptr<HydStatic_StbFun>
			HeelingArm
			(
				const std::shared_ptr<HydStatic_hArmFormula>& theHeeling,
				const Geo_xDistb& theDist
			);

		static Standard_Real 
			Area
			(
				const std::shared_ptr<HydStatic_StbFun>& theFun,
				const Standard_Real thePhi0, 
				const Standard_Real thePhi1,
				const Standard_Real y0, 
				const std::shared_ptr<info>& theInfo
			);

		static Standard_Real MaxRightingArmHeel(const std::shared_ptr<HydStatic_StbFun>& theRighting);

		static Standard_Real MaxRightingArmHeel_Port(const std::shared_ptr<HydStatic_StbFun>& theRighting);

		static std::tuple<Standard_Real, Standard_Boolean> StaticalStability(const std::shared_ptr<HydStatic_StbFun>& theRighting, const std::shared_ptr<HydStatic_StbFun>& theHeeling);


	};
}

#endif // !_HydStatic_FunLib_Header
