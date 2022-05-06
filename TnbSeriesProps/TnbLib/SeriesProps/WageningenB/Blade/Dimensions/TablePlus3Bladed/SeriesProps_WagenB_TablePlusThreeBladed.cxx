#include <SeriesProps_WagenB_TablePlusThreeBladed.hxx>

#include <SeriesProps_WagenBTools.hxx>
#include <NumAlg_SteffenInterplFunc.hxx>
#include <Global_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const std::vector<Standard_Real> tnbLib::wagenB::TablePlusThreeBladed::rPerR = { 0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0 };
const std::vector<Standard_Real> tnbLib::wagenB::TablePlusThreeBladed::cPerD = { 1.662,1.882,2.050,2.152,2.187,2.144,1.970,1.582,0.000 };
const std::vector<Standard_Real> tnbLib::wagenB::TablePlusThreeBladed::aPerc = { 0.617,0.613,0.601,0.586,0.561,0.524,0.463,0.351,0.000 };
const std::vector<Standard_Real> tnbLib::wagenB::TablePlusThreeBladed::bPerc = { 0.350,0.350,0.351,0.355,0.389,0.443,0.479,0.500,0.000 };
const std::vector<Standard_Real> tnbLib::wagenB::TablePlusThreeBladed::Ar = { 0.0526,0.0464,0.0402,0.0340,0.0278,0.0216,0.0154,0.0092,0.0030 };
const std::vector<Standard_Real> tnbLib::wagenB::TablePlusThreeBladed::Br = { 0.0040,0.0035,0.0030,0.0025,0.0020,0.0015,0.0010,0.0005,0.0000 };

const std::shared_ptr<tnbLib::NumAlg_InterplFunc> tnbLib::wagenB::TablePlusThreeBladed::Interpl_cPerD = 
std::make_shared<tnbLib::NumAlg_SteffenInterplFunc>
(
	tnbLib::Global_Tools::ConvertToPairedList(tnbLib::wagenB::TablePlusThreeBladed::rPerR, tnbLib::wagenB::TablePlusThreeBladed::cPerD)
	);

const std::shared_ptr<tnbLib::NumAlg_InterplFunc> tnbLib::wagenB::TablePlusThreeBladed::Interpl_aPerc =
std::make_shared<tnbLib::NumAlg_SteffenInterplFunc>
(
	tnbLib::Global_Tools::ConvertToPairedList(tnbLib::wagenB::TablePlusThreeBladed::rPerR, tnbLib::wagenB::TablePlusThreeBladed::aPerc)
	);

const std::shared_ptr<tnbLib::NumAlg_InterplFunc> tnbLib::wagenB::TablePlusThreeBladed::Interpl_bPerc =
std::make_shared<tnbLib::NumAlg_SteffenInterplFunc>
(
	tnbLib::Global_Tools::ConvertToPairedList(tnbLib::wagenB::TablePlusThreeBladed::rPerR, tnbLib::wagenB::TablePlusThreeBladed::bPerc)
	);

const std::shared_ptr<tnbLib::NumAlg_InterplFunc> tnbLib::wagenB::TablePlusThreeBladed::Interpl_Ar =
std::make_shared<tnbLib::NumAlg_SteffenInterplFunc>
(
	tnbLib::Global_Tools::ConvertToPairedList(tnbLib::wagenB::TablePlusThreeBladed::rPerR, tnbLib::wagenB::TablePlusThreeBladed::Ar)
	);

const std::shared_ptr<tnbLib::NumAlg_InterplFunc> tnbLib::wagenB::TablePlusThreeBladed::Interpl_Br =
std::make_shared<tnbLib::NumAlg_SteffenInterplFunc>
(
	tnbLib::Global_Tools::ConvertToPairedList(tnbLib::wagenB::TablePlusThreeBladed::rPerR, tnbLib::wagenB::TablePlusThreeBladed::Br)
	);

Standard_Real 
tnbLib::wagenB::TablePlusThreeBladed::CalcChord
(
	const Standard_Real rPerR,
	const Standard_Real Dia,
	const Standard_Real AePerAo, 
	const Standard_Integer Z
)
{
	Debug_Null_Pointer(Interpl_cPerD);
	const auto value = Interpl_cPerD->Value(rPerR);
	return (value*AePerAo*Dia) / (Standard_Real)Z;
}

Standard_Real 
tnbLib::wagenB::TablePlusThreeBladed::CalcA
(
	const Standard_Real rPerR,
	const Standard_Real c
)
{
	Debug_Null_Pointer(Interpl_aPerc);
	const auto value = Interpl_aPerc->Value(rPerR);
	return c * value;
}

Standard_Real 
tnbLib::wagenB::TablePlusThreeBladed::CalcB
(
	const Standard_Real rPerR, 
	const Standard_Real c
)
{
	Debug_Null_Pointer(Interpl_bPerc);
	const auto value = Interpl_bPerc->Value(rPerR);
	return c * value;
}

Standard_Real 
tnbLib::wagenB::TablePlusThreeBladed::CalcThickness
(
	const Standard_Real rPerR,
	const Standard_Real Dia, 
	const Standard_Integer Z
)
{
	Debug_Null_Pointer(Interpl_Ar);
	Debug_Null_Pointer(Interpl_Br);

	const auto ar = Interpl_Ar->Value(rPerR);
	const auto br = Interpl_Br->Value(rPerR);

	const auto value = ar - (Standard_Real)Z*br;
	return value * Dia;
}