#include <HsModel_FormCoeff.hxx>

#include <HydroStatic_Tools.hxx>
#include <HsEntity_Section.hxx>
#include <HsModel_FormDim.hxx>
#include <HsEntity_Vessel.hxx>
#include <error.hxx>
#include <OSstream.hxx>

void tnbLib::HsModel_FormCoeff::CalcVolume()
{
	Debug_Null_Pointer(Vessel());

	std::vector<hsLib::xSection> areaList;
	for (const auto& x : Vessel()->Sections())
	{
		if (x->HasWettedArea())
		{
			hsLib::xSection sec;

			sec.x = x->X();
			sec.value = x->WettedArea();

			areaList.push_back(std::move(sec));
		}
	}

	ChangeDISPV()() = HydroStatic_Tools::CalcArea(areaList);
}

void tnbLib::HsModel_FormCoeff::CalcCB()
{
	Debug_Null_Pointer(FormDim());
	Debug_Null_Pointer(Vessel());
	Debug_Null_Pointer(Vessel()->MidSection());

	const auto& dim = *FormDim();
	const auto& mid = *Vessel()->MidSection();

	ChangeCB()() = DISPV()() / (dim.BWL()()*dim.LWL()()*mid.Draft());
}

void tnbLib::HsModel_FormCoeff::CalcAM()
{
	Debug_Null_Pointer(Vessel());
	Debug_Null_Pointer(Vessel()->MidSection());

	const auto& mid = *Vessel()->MidSection();

	ChangeAM()() = mid.WettedArea();
}

void tnbLib::HsModel_FormCoeff::CalcCP()
{
	Debug_Null_Pointer(FormDim());
	Debug_Null_Pointer(Vessel());
	Debug_Null_Pointer(Vessel()->MidSection());

	const auto& mid = *Vessel()->MidSection();
	const auto& dim = *FormDim();

	ChangeCP()() = AM()() / (dim.BWL()()*mid.Draft());
}

void tnbLib::HsModel_FormCoeff::CalcCM()
{
	Debug_Null_Pointer(FormDim());
	Debug_Null_Pointer(Vessel());
	Debug_Null_Pointer(Vessel()->MidSection());

	const auto& mid = *Vessel()->MidSection();
	const auto& dim = *FormDim();

	ChangeCM()() = AM()() / (dim.BWL()()*mid.Draft());
}

void tnbLib::HsModel_FormCoeff::CalcAW()
{
	Debug_Null_Pointer(FormDim());
	const auto& dim = *FormDim();

	ChangeCWL()() = AW()() / (dim.LWL()()*dim.BWL()());
}

void tnbLib::HsModel_FormCoeff::CalcCWL()
{
	Debug_Null_Pointer(FormDim());
	Debug_Null_Pointer(Vessel());
	Debug_Null_Pointer(Vessel()->MidSection());

	const auto& mid = *Vessel()->MidSection();
	const auto& dim = *FormDim();

	ChangeCVP()() = AW()() / (dim.LWL()()*mid.Draft());
}

void tnbLib::HsModel_FormCoeff::CalcCVP()
{
	Debug_Null_Pointer(FormDim());
	Debug_Null_Pointer(Vessel());
	Debug_Null_Pointer(Vessel()->MidSection());

	const auto& mid = *Vessel()->MidSection();
	const auto& dim = *FormDim();

	ChangeKB()() = mid.Draft() + VCB()();
}