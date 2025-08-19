#include <SeriesProps_WagenB_TableThreeBladed.hxx>

#include <SeriesProps_WagenBTools.hxx>
#include <NumAlg_SteffenInterplFunc.hxx>
#include <Global_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const std::vector<Standard_Real> tnbLib::wagenB::TableThreeBladed::rPerR = { 0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0 };
const std::vector<Standard_Real> tnbLib::wagenB::TableThreeBladed::cPerD = { 1.633,1.832,2.000,2.120,2.186,2.168,2.127,1.657,0.000 };
const std::vector<Standard_Real> tnbLib::wagenB::TableThreeBladed::aPerc = { 0.616,0.611,0.599,0.583,0.558,0.526,0.481,0.400,0.000 };
const std::vector<Standard_Real> tnbLib::wagenB::TableThreeBladed::bPerc = { 0.350,0.350,0.350,0.355,0.389,0.442,0.478,0.500,0.000 };
const std::vector<Standard_Real> tnbLib::wagenB::TableThreeBladed::Ar = { 0.0526,0.0464,0.0402,0.0340,0.0278,0.0216,0.0154,0.0092,0.0030 };
const std::vector<Standard_Real> tnbLib::wagenB::TableThreeBladed::Br = { 0.0040,0.0035,0.0030,0.0025,0.0020,0.0015,0.0010,0.0005,0.0000 };

const std::shared_ptr<tnbLib::NumAlg_InterplFunc> tnbLib::wagenB::TableThreeBladed::Interpl_cPerD =
std::make_shared<tnbLib::NumAlg_SteffenInterplFunc>
(
	tnbLib::Global_Tools::ConvertToPairedList(tnbLib::wagenB::TableThreeBladed::rPerR, tnbLib::wagenB::TableThreeBladed::cPerD)
	);

const std::shared_ptr<tnbLib::NumAlg_InterplFunc> tnbLib::wagenB::TableThreeBladed::Interpl_aPerc =
std::make_shared<tnbLib::NumAlg_SteffenInterplFunc>
(
	tnbLib::Global_Tools::ConvertToPairedList(tnbLib::wagenB::TableThreeBladed::rPerR, tnbLib::wagenB::TableThreeBladed::aPerc)
	);

const std::shared_ptr<tnbLib::NumAlg_InterplFunc> tnbLib::wagenB::TableThreeBladed::Interpl_bPerc =
std::make_shared<tnbLib::NumAlg_SteffenInterplFunc>
(
	tnbLib::Global_Tools::ConvertToPairedList(tnbLib::wagenB::TableThreeBladed::rPerR, tnbLib::wagenB::TableThreeBladed::bPerc)
	);

const std::shared_ptr<tnbLib::NumAlg_InterplFunc> tnbLib::wagenB::TableThreeBladed::Interpl_Ar =
std::make_shared<tnbLib::NumAlg_SteffenInterplFunc>
(
	tnbLib::Global_Tools::ConvertToPairedList(tnbLib::wagenB::TableThreeBladed::rPerR, tnbLib::wagenB::TableThreeBladed::Ar)
	);

const std::shared_ptr<tnbLib::NumAlg_InterplFunc> tnbLib::wagenB::TableThreeBladed::Interpl_Br =
std::make_shared<tnbLib::NumAlg_SteffenInterplFunc>
(
	tnbLib::Global_Tools::ConvertToPairedList(tnbLib::wagenB::TableThreeBladed::rPerR, tnbLib::wagenB::TableThreeBladed::Br)
	);

Standard_Real
tnbLib::wagenB::TableThreeBladed::CalcChord
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
tnbLib::wagenB::TableThreeBladed::CalcA
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
tnbLib::wagenB::TableThreeBladed::CalcB
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
tnbLib::wagenB::TableThreeBladed::CalcThickness
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