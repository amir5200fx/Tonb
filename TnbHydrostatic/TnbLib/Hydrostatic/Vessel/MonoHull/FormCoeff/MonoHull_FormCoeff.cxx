#include <MonoHull_FormCoeff.hxx>

#include <HydroStatic_Tools.hxx>
#include <MonoHull_Section.hxx>
#include <MonoHull_FormDim.hxx>
#include <HsEntity_MonoHull.hxx>
#include <error.hxx>
#include <OSstream.hxx>

void tnbLib::MonoHull_FormCoeff::CalcVolume()
{
	Debug_Null_Pointer(Model());

	std::vector<hsLib::xSection> areaList;
	for (const auto& x : Model()->Sections())
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

void tnbLib::MonoHull_FormCoeff::CalcCB()
{
	Debug_Null_Pointer(FormDim());
	Debug_Null_Pointer(Model());
	Debug_Null_Pointer(Model()->MidSection());

	const auto& dim = *FormDim();
	const auto& mid = *Model()->MidSection();

	ChangeCB()() = DISPV()() / (dim.BWL()()*dim.LWL()()*mid.Draft());
}

void tnbLib::MonoHull_FormCoeff::CalcAM()
{
	Debug_Null_Pointer(Model());
	Debug_Null_Pointer(Model()->MidSection());

	const auto& mid = *Model()->MidSection();

	ChangeAM()() = mid.WettedArea();
}

void tnbLib::MonoHull_FormCoeff::CalcCP()
{
	Debug_Null_Pointer(FormDim());
	Debug_Null_Pointer(Model());
	Debug_Null_Pointer(Model()->MidSection());

	const auto& mid = *Model()->MidSection();
	const auto& dim = *FormDim();

	ChangeCP()() = AM()() / (dim.BWL()()*mid.Draft());
}

void tnbLib::MonoHull_FormCoeff::CalcCM()
{
	Debug_Null_Pointer(FormDim());
	Debug_Null_Pointer(Model());
	Debug_Null_Pointer(Model()->MidSection());

	const auto& mid = *Model()->MidSection();
	const auto& dim = *FormDim();

	ChangeCM()() = AM()() / (dim.BWL()()*mid.Draft());
}

void tnbLib::MonoHull_FormCoeff::CalcCWL()
{
	Debug_Null_Pointer(FormDim());
	const auto& dim = *FormDim();

	ChangeCWL()() = AW()() / (dim.LWL()()*dim.BWL()());
}

void tnbLib::MonoHull_FormCoeff::CalcCVP()
{
	Debug_Null_Pointer(FormDim());
	Debug_Null_Pointer(Model());
	Debug_Null_Pointer(Model()->MidSection());

	const auto& mid = *Model()->MidSection();
	const auto& dim = *FormDim();

	ChangeCVP()() = AW()() / (dim.LWL()()*mid.Draft());
}

void tnbLib::MonoHull_FormCoeff::CalcKB()
{
	Debug_Null_Pointer(FormDim());
	Debug_Null_Pointer(Model());
	Debug_Null_Pointer(Model()->MidSection());

	const auto& mid = *Model()->MidSection();
	const auto& dim = *FormDim();

	ChangeKB()() = mid.Draft() + VCB()();
}