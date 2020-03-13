#include <HsModel_FormDim.hxx>

#include <HsEntity_Vessel.hxx>
#include <HsEntity_Section.hxx>
#include <error.hxx>
#include <OSstream.hxx>

void tnbLib::HsModel_FormDim::CalcFUW()
{
	Debug_Null_Pointer(Vessel());

	ChangeFUW()() = Vessel()->LastUnderWaterSectionX();
}

void tnbLib::HsModel_FormDim::CalcAUW()
{
	Debug_Null_Pointer(Vessel());

	ChangeAUW()() = Vessel()->FirstUnderWaterSectionX();
}

void tnbLib::HsModel_FormDim::CalcAWL()
{
	Debug_Null_Pointer(Vessel());

	ChangeAWL()() = Vessel()->FirstWaterLineSectionX();
}

void tnbLib::HsModel_FormDim::CalcFWL()
{
	Debug_Null_Pointer(Vessel());

	ChangeFWL()() = Vessel()->LastWaterLineSectionX();
}

void tnbLib::HsModel_FormDim::CalcB()
{
	Debug_Null_Pointer(Vessel());

	auto maxB = RealFirst();
	for (const auto& x : Vessel()->Sections())
	{
		Debug_Null_Pointer(x);

		auto b = x->MaxBeam();
		if (b > maxB)
			maxB = b;
	}
	ChangeB()() = maxB;
}

void tnbLib::HsModel_FormDim::CalcBWL()
{
	Debug_Null_Pointer(Vessel());

	auto maxB = RealFirst();
	for (const auto& x : Vessel()->Sections())
	{
		Debug_Null_Pointer(x);

		auto b = x->MaxWetBeam();
		if (b > maxB)
			maxB = b;
	}
	ChangeBWL()() = maxB;
}

void tnbLib::HsModel_FormDim::CalcD()
{
	Debug_Null_Pointer(Vessel());

	auto maxD = RealFirst();
	for (const auto& x : Vessel()->Sections())
	{
		Debug_Null_Pointer(x);

		auto depth = x->Depth();
		if (depth > maxD)
			maxD = depth;
	}
	ChangeD()() = maxD;
}

void tnbLib::HsModel_FormDim::CalcFPP()
{
	if (NOT FWL())
	{
		FatalErrorIn("void MonoHull_FormDim::CalcFPP()")
			<< "FWL is not calculated" << endl
			<< abort(FatalError);
	}
	ChangeFPP()() = FWL()();
}

void tnbLib::HsModel_FormDim::CalcAPP()
{
	if (NOT APP())
	{
		ChangeAPP()() = AWL()();
	}
}

void tnbLib::HsModel_FormDim::CalcLPP()
{
	ChangeLPP()() = FPP()() - APP()();
}

void tnbLib::HsModel_FormDim::CalcMPP()
{
	ChangeMPP()() = MEAN(FPP()(), APP()());
}

void tnbLib::HsModel_FormDim::CalcLWL()
{
	ChangeLWL()() = FWL()() - AWL()();
}

void tnbLib::HsModel_FormDim::CalcLOS()
{
	ChangeLOS()() = FUW()() - AUW()();
}

void tnbLib::HsModel_FormDim::CalcLOA()
{
	Debug_Null_Pointer(Vessel());

	ChangeLOA()() = Vessel()->LastSectionX() - Vessel()->FirstSectionX();
}

void tnbLib::HsModel_FormDim::Perform()
{
	CalcFUW();
	CalcAUW();
	CalcAWL();
	CalcFWL();

	CalcFPP();
	CalcAPP();
	CalcLPP();
	CalcMPP();
	CalcLWL();
	CalcLOS();
	CalcLOA();

	CalcB();
	CalcBWL();
	CalcD();
}