#include <MonoHull_FormDim.hxx>

#include <HsEntity_MonoHull.hxx>
#include <MonoHull_Section.hxx>
#include <error.hxx>
#include <OSstream.hxx>

void tnbLib::MonoHull_FormDim::CalcFUW()
{
	Debug_Null_Pointer(Model());

	ChangeFUW()() = Model()->LastUnderWaterSectionX();
}

void tnbLib::MonoHull_FormDim::CalcAUW()
{
	Debug_Null_Pointer(Model());

	ChangeAUW()() = Model()->FirstUnderWaterSectionX();
}

void tnbLib::MonoHull_FormDim::CalcAWL()
{
	Debug_Null_Pointer(Model());

	ChangeAWL()() = Model()->FirstWaterLineSectionX();
}

void tnbLib::MonoHull_FormDim::CalcFWL()
{
	Debug_Null_Pointer(Model());

	ChangeFWL()() = Model()->LastWaterLineSectionX();
}

void tnbLib::MonoHull_FormDim::CalcB()
{
	Debug_Null_Pointer(Model());

	auto maxB = RealFirst();
	for (const auto& x : Model()->Sections())
	{
		Debug_Null_Pointer(x);

		auto b = x->MaxBeam();
		if (b > maxB)
			maxB = b;
	}
	ChangeB()() = maxB;
}

void tnbLib::MonoHull_FormDim::CalcBWL()
{
	Debug_Null_Pointer(Model());

	auto maxB = RealFirst();
	for (const auto& x : Model()->Sections())
	{
		Debug_Null_Pointer(x);

		auto b = x->MaxWetBeam();
		if (b > maxB)
			maxB = b;
	}
	ChangeBWL()() = maxB;
}

void tnbLib::MonoHull_FormDim::CalcD()
{
	Debug_Null_Pointer(Model());

	auto maxD = RealFirst();
	for (const auto& x : Model()->Sections())
	{
		Debug_Null_Pointer(x);

		auto depth = x->Depth();
		if (depth > maxD)
			maxD = depth;
	}
	ChangeD()() = maxD;
}

void tnbLib::MonoHull_FormDim::CalcFPP()
{
	if (NOT FWL())
	{
		FatalErrorIn("void MonoHull_FormDim::CalcFPP()")
			<< "FWL is not calculated" << endl
			<< abort(FatalError);
	}
	ChangeFPP()() = FWL()();
}

void tnbLib::MonoHull_FormDim::CalcAPP()
{
	if (NOT APP())
	{
		ChangeAPP()() = AWL()();
	}
}

void tnbLib::MonoHull_FormDim::CalcLPP()
{
	ChangeLPP()() = FPP()() - APP()();
}

void tnbLib::MonoHull_FormDim::CalcMPP()
{
	ChangeMPP()() = MEAN(FPP()(), APP()());
}

void tnbLib::MonoHull_FormDim::CalcLWL()
{
	ChangeLWL()() = FWL()() - AWL()();
}

void tnbLib::MonoHull_FormDim::CalcLOS()
{
	ChangeLOS()() = FUW()() - AUW()();
}

void tnbLib::MonoHull_FormDim::CalcLOA()
{
	Debug_Null_Pointer(Model());

	ChangeLOA()() = Model()->LastSectionX() - Model()->FirstSectionX();
}

void tnbLib::MonoHull_FormDim::Perform()
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