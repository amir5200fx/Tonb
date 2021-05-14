#pragma once
#ifndef _Marine_GraphCmptLib_Header
#define _Marine_GraphCmptLib_Header

#include <Standard_TypeDef.hxx>
#include <Marine_VesselParams.hxx>
#include <Marine_BodiesFwd.hxx>
#include <Marine_Module.hxx>

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

		static TnbMarine_EXPORT std::tuple<marineLib::LOA, marineLib::B, marineLib::D>
			CalcBasicDim
			(
				const Marine_Body& theBody
			);

		static TnbMarine_EXPORT marineLib::D
			SpecifyD
			(
				const Standard_Real theD
			);

		static TnbMarine_EXPORT marineLib::APP
			CalcAPP
			(
				const marineLib::Body_Wetted& theBody
			);

		static TnbMarine_EXPORT marineLib::APP
			CalcAPP
			(
				const gp_Ax1& theAx
			);

		static TnbMarine_EXPORT marineLib::FPP
			CalcFPP
			(
				const marineLib::Body_Wetted& theBody
			);

		static TnbMarine_EXPORT marineLib::MPP
			CalcMPP
			(
				const marineLib::APP& theApp,
				const marineLib::FPP& theFpp
			);

		static TnbMarine_EXPORT marineLib::LWL
			CalcLWL
			(
				const std::shared_ptr<marineLib::Body_Wetted>& theBody
			);

		static TnbMarine_EXPORT marineLib::LWL
			CalcLWL
			(
				const marineLib::BodyConstructor_Shape<marineLib::Body_Wetted>& theBody
			);

		static TnbMarine_EXPORT marineLib::LWL
			CalcLWL
			(
				const marineLib::BodyConstructor_noShape<marineLib::Body_Wetted>& theBody
			);

		static TnbMarine_EXPORT marineLib::BWL
			CalcBWL
			(
				const marineLib::Body_Wetted& theBody
			);

		static TnbMarine_EXPORT marineLib::FWL
			CalcFWL
			(
				const marineLib::Body_Wetted& theBody
			);

		static TnbMarine_EXPORT marineLib::AWL
			CalcAWL
			(
				const marineLib::Body_Wetted& theBody
			);

		static TnbMarine_EXPORT marineLib::FUW
			CalcFUW
			(
				const marineLib::Body_Wetted& theBody
			);

		static TnbMarine_EXPORT marineLib::AUW
			CalcAUW
			(
				const marineLib::Body_Wetted& theBody
			);

		static TnbMarine_EXPORT marineLib::LOS
			CalcLOS
			(
				const marineLib::AUW& theAuw, 
				const marineLib::FUW& theFuw
			);

		static TnbMarine_EXPORT marineLib::LPP
			CalcLPP
			(
				const marineLib::APP& theAft, 
				const marineLib::FPP& theFp
			);

		static TnbMarine_EXPORT marineLib::LCF 
			CalcLCF
			(
				const marineLib::Body_Wetted& theBody,
				const Standard_Real x0, 
				const std::shared_ptr<info>& theInfo
			);

		static TnbMarine_EXPORT marineLib::TCF
			CalcTCF
			(
				const marineLib::Body_Wetted& theBody,
				const marineLib::AW& theAw,
				const Standard_Real y0,
				const std::shared_ptr<info>& theInfo
			);

		static TnbMarine_EXPORT marineLib::LCB 
			CalcLCB
			(
				const marineLib::Body_Wetted& theBody,
				const Standard_Real x0, 
				const std::shared_ptr<info>& theInfo
			);

		static TnbMarine_EXPORT marineLib::DISPV 
			CalcDISPV
			(
				const marineLib::Body_Wetted& theBody,
				const std::shared_ptr<info>& theInfo
			);

		static TnbMarine_EXPORT marineLib::BM 
			CalcBM
			(
				const Marine_CmpSection& theWPlane,
				const Standard_Real yc,
				const marineLib::DISPV& theVolume,
				const std::shared_ptr<info>& theInfo
			);

		static TnbMarine_EXPORT marineLib::BM
			CalcBM
			(
				const marineLib::Body_Wetted& theBody,
				const Standard_Real yc,
				const marineLib::DISPV& theVolume,
				const std::shared_ptr<info>& theInfo
			);

		static TnbMarine_EXPORT marineLib::BML
			CalcBML
			(
				const Marine_CmpSection& theWPlane, 
				const Standard_Real xc,
				const marineLib::DISPV& theVolume,
				const std::shared_ptr<info>& theInfo
			);

		static TnbMarine_EXPORT marineLib::BML
			CalcBML
			(
				const marineLib::Body_Wetted& theBody,
				const Standard_Real xc,
				const marineLib::DISPV& theVolume,
				const std::shared_ptr<info>& theInfo
			);

		static TnbMarine_EXPORT marineLib::TM
			CalcTM
			(
				const marineLib::Body_Wetted& theBody
			);

		static TnbMarine_EXPORT marineLib::AM
			CalcAM
			(
				const marineLib::Body_Wetted& theBody,
				const std::shared_ptr<info>& theInfo
			);

		static TnbMarine_EXPORT marineLib::KB 
			CalcKB
			(
				const marineLib::Body_Wetted& theBody,
				const marineLib::DISPV& theDispl,
				const Marine_BaseLine& theBase,
				const std::shared_ptr<info>& theInfo
			);

		static TnbMarine_EXPORT marineLib::KM 
			CalcKM
			(
				const marineLib::KB& theKb, 
				const marineLib::BM& theBm
			);

		static TnbMarine_EXPORT marineLib::GM 
			CalcGM
			(
				const marineLib::KB& theKb, 
				const marineLib::KG& theKg
			);

		static TnbMarine_EXPORT marineLib::KML 
			CalcKML
			(
				const marineLib::KB& theKb, 
				const marineLib::BML& theBml
			);

		static TnbMarine_EXPORT marineLib::MCT 
			CalcMCT
			(
				const marineLib::BML& theBML,
				const marineLib::DISPV& theVolume, 
				const marineLib::LPP& theLpp
			);

		static TnbMarine_EXPORT marineLib::AW 
			CalcAW
			(
				const marineLib::Body_Wetted& theBody,
				const std::shared_ptr<info>& theInfo
			);

		static TnbMarine_EXPORT marineLib::AW
			CalcAW
			(
				const Marine_CmpSection& theWPlane,
				const std::shared_ptr<info>& theInfo
			);

		static TnbMarine_EXPORT marineLib::CB
			CalcCB
			(
				const marineLib::DISPV& theVolume, 
				const marineLib::LPP& theLpp,
				const marineLib::BWL& theB,
				const marineLib::TM& theTm
			);

		static TnbMarine_EXPORT marineLib::CWL
			CalcCWL
			(
				const marineLib::AW& theAw, 
				const marineLib::LWL& theLwl,
				const marineLib::BWL& theB
			);

		static TnbMarine_EXPORT marineLib::CM
			CalcCM
			(
				const marineLib::AM& theAm, 
				const marineLib::BWL& theB,
				const marineLib::TM& theTm
			);

		static TnbMarine_EXPORT marineLib::CP
			CalcCP
			(
				const marineLib::DISPV& theVolume, 
				const marineLib::AM& theAm,
				const marineLib::LWL& theLwl
			);

		static TnbMarine_EXPORT marineLib::CVP
			CalcCVP
			(
				const marineLib::DISPV& theVolume, 
				const marineLib::AW& theAw, 
				const marineLib::TM& theTm
			);
	};
}

#endif // !_Marine_GraphCmptLib_Header
