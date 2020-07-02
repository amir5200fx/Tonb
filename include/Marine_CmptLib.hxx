#pragma once
#ifndef _Marine_GraphCmptLib_Header
#define _Marine_GraphCmptLib_Header

#include <Standard_TypeDef.hxx>
#include <Marine_VesselParams.hxx>
#include <Marine_BodiesFwd.hxx>

#include <memory>
#include <tuple>

class gp_Ax1;

namespace tnbLib
{

	// Forward Declarations
	class Marine_Body;
	class Marine_CmpSection;
	class Marine_xCmpSection;
	class Marine_zCmpSection;
	class Marine_BaseLine;
	class NumAlg_AdaptiveInteg_Info;

	class Marine_CmptLib
	{

	public:

		typedef NumAlg_AdaptiveInteg_Info info;

		static std::tuple<marineLib::LOA, marineLib::B, marineLib::D>
			CalcBasicDim
			(
				const Marine_Body& theBody
			);

		static marineLib::D
			SpecifyD
			(
				const Standard_Real theD
			);

		static marineLib::APP
			CalcAPP
			(
				const marineLib::Body_Wetted& theBody
			);

		static marineLib::APP
			CalcAPP
			(
				const gp_Ax1& theAx
			);

		static marineLib::FPP
			CalcFPP
			(
				const marineLib::Body_Wetted& theBody
			);

		static marineLib::MPP
			CalcMPP
			(
				const marineLib::APP& theApp,
				const marineLib::FPP& theFpp
			);

		static marineLib::LWL
			CalcLWL
			(
				const std::shared_ptr<marineLib::Body_Wetted>& theBody
			);

		static marineLib::LWL
			CalcLWL
			(
				const marineLib::Body_Wetted& theBody
			);

		static marineLib::LWL
			CalcLWL
			(
				const marineLib::Body_WettedS& theBody
			);

		static marineLib::BWL
			CalcBWL
			(
				const marineLib::Body_Wetted& theBody
			);

		static marineLib::FWL
			CalcFWL
			(
				const marineLib::Body_Wetted& theBody
			);

		static marineLib::AWL
			CalcAWL
			(
				const marineLib::Body_Wetted& theBody
			);

		static marineLib::FUW
			CalcFUW
			(
				const marineLib::Body_Wetted& theBody
			);

		static marineLib::AUW
			CalcAUW
			(
				const marineLib::Body_Wetted& theBody
			);

		static marineLib::LOS
			CalcLOS
			(
				const marineLib::AUW& theAuw, 
				const marineLib::FUW& theFuw
			);

		static marineLib::LPP
			CalcLPP
			(
				const marineLib::APP& theAft, 
				const marineLib::FPP& theFp
			);

		static marineLib::LCF 
			CalcLCF
			(
				const marineLib::Body_Wetted& theBody,
				const Standard_Real x0, 
				const std::shared_ptr<info>& theInfo
			);

		static marineLib::LCB 
			CalcLCB
			(
				const marineLib::Body_Wetted& theBody,
				const Standard_Real x0, 
				const std::shared_ptr<info>& theInfo
			);

		static marineLib::DISPV 
			CalcDISPV
			(
				const marineLib::Body_Wetted& theBody,
				const std::shared_ptr<info>& theInfo
			);

		static marineLib::BM 
			CalcBM
			(
				const Marine_CmpSection& theWPlane,
				const Standard_Real yc,
				const marineLib::DISPV& theVolume,
				const std::shared_ptr<info>& theInfo
			);

		static marineLib::BML
			CalcBML
			(
				const Marine_CmpSection& theWPlane, 
				const Standard_Real xc,
				const marineLib::DISPV& theVolume,
				const std::shared_ptr<info>& theInfo
			);

		static marineLib::TM
			CalcTM
			(
				const marineLib::Body_Wetted& theBody
			);

		static marineLib::AM
			CalcAM
			(
				const marineLib::Body_Wetted& theBody,
				const std::shared_ptr<info>& theInfo
			);

		/*static Standard_Real CalcKM(const Marine_WettedBody& theBody, const std::shared_ptr<info>& theInfo);

		static Standard_Real CalcKML(const Marine_WettedBody& theBody, const std::shared_ptr<info>& theInfo);*/

		static marineLib::KB 
			CalcKB
			(
				const marineLib::Body_Wetted& theBody,
				const Marine_BaseLine& theBase,
				const std::shared_ptr<info>& theInfo
			);

		static marineLib::MCT 
			CalcMCT
			(
				const marineLib::BML& theBML,
				const marineLib::DISPV& theVolume, 
				const marineLib::LPP& theLpp
			);

		static marineLib::AW 
			CalcAW
			(
				const marineLib::Body_Wetted& theBody,
				const std::shared_ptr<info>& theInfo
			);

		static marineLib::AW
			CalcAW
			(
				const Marine_CmpSection& theWPlane,
				const std::shared_ptr<info>& theInfo
			);

		static marineLib::CB
			CalcCB
			(
				const marineLib::DISPV& theVolume, 
				const marineLib::LPP& theLpp,
				const marineLib::BWL& theB,
				const marineLib::TM& theTm
			);

		static marineLib::CWL
			CalcCWL
			(
				const marineLib::AW& theAw, 
				const marineLib::LWL& theLwl,
				const marineLib::BWL& theB
			);

		static marineLib::CM
			CalcCM
			(
				const marineLib::AM& theAm, 
				const marineLib::BWL& theB,
				const marineLib::TM& theTm
			);

		static marineLib::CP
			CalcCP
			(
				const marineLib::DISPV& theVolume, 
				const marineLib::AM& theAm,
				const marineLib::LWL& theLwl
			);

		static marineLib::CVP
			CalcCVP
			(
				const marineLib::DISPV& theVolume, 
				const marineLib::AW& theAw, 
				const marineLib::TM& theTm
			);
	};
}

#endif // !_Marine_GraphCmptLib_Header
