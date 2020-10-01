#include <HydStatic_FormCoeff.hxx>

#include <Standard_Real.hxx>
#include <HydStatic_FormDims.hxx>
#include <MarineBase_Tools.hxx>
#include <Marine_CmpSection.hxx>
#include <Marine_CmptLib.hxx>
#include <Marine_System.hxx>
#include <Marine_Bodies.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <gp.hxx>

#ifdef SET_PARAM
#undef SET_PARAM
#endif // SET_PARAM

#define SET_PARAM(Name)  ParametersRef()->Name = std::move(param)

namespace tnbLib
{
	void CheckValue(const char* name, const word& parName, const Standard_Real v)
	{
		if (v <= RealSmall())
		{
			FatalErrorIn(name) << endl
				<< "very small parameter has been detected!" << endl
				<< " parameter's name = " << parName << endl
				<< abort(FatalError);
		}
	}
}

void tnbLib::formCoeff::Wetted::CalcDISPV
(
	const marineLib::Body_Wetted & theBody
)
{
	auto param =
		Marine_CmptLib::CalcDISPV
		(
			theBody,
			sysLib::gl_marine_integration_info
		);
	SET_PARAM(Dispv);
}

void tnbLib::formCoeff::Wetted::CalcCB
(
	const marineLib::Body_Wetted & theBody
)
{
	Debug_Null_Pointer(WettedFormDim());
	const auto& dim = *WettedFormDim();

	const auto dispv = Parameters()->Dispv();
	const auto bwl = dim.Parameters()->Bwl();
	const auto lwl = dim.Parameters()->Lwl();
	const auto tm = dim.Parameters()->Tm();

	CheckValue("void CalcCB(const marineLib::Body_Wetted &)", Parameters()->Dispv.Name(), dispv);
	CheckValue("void CalcCB(const marineLib::Body_Wetted &)", dim.Parameters()->Bwl.Name(), bwl);
	CheckValue("void CalcCB(const marineLib::Body_Wetted &)", dim.Parameters()->Lwl.Name(), lwl);
	CheckValue("void CalcCB(const marineLib::Body_Wetted &)", dim.Parameters()->Tm.Name(), tm);

	ParametersRef()->Cb() = dispv / (bwl*lwl*tm);
}

void tnbLib::formCoeff::Wetted::CalcAM
(
	const marineLib::Body_Wetted & theBody
)
{
	if (NOT theBody.Mid())
	{
		FatalErrorIn(FunctionSIG)
			<< "no middle section has been found for this body" << endl
			<< abort(FatalError);
	}
	const auto& mid = *theBody.Mid();
	auto param = 
		Marine_CmptLib::CalcAM
		(
			theBody, 
			sysLib::gl_marine_integration_info
		);
	SET_PARAM(Am);
}

void tnbLib::formCoeff::Wetted::CalcCP()
{
	Debug_Null_Pointer(WettedFormDim());
	const auto& dim = *WettedFormDim();

	const auto am = Parameters()->Am();
	const auto bwl = dim.Parameters()->Bwl();
	const auto tm = dim.Parameters()->Tm();

	CheckValue("void CalcCP()", Parameters()->Am.Name(), am);
	CheckValue("void CalcCP()", dim.Parameters()->Bwl.Name(), bwl);
	CheckValue("void CalcCP()", dim.Parameters()->Tm.Name(), tm);

	ParametersRef()->Cp() = am / (bwl*tm);
}

void tnbLib::formCoeff::Wetted::CalcCM()
{
	Debug_Null_Pointer(WettedFormDim());
	const auto& dim = *WettedFormDim();

	const auto am = Parameters()->Am();
	const auto bwl = dim.Parameters()->Bwl();
	const auto tm = dim.Parameters()->Tm();

	CheckValue("void CalcCM()", Parameters()->Am.Name(), am);
	CheckValue("void CalcCM()", dim.Parameters()->Bwl.Name(), bwl);
	CheckValue("void CalcCM()", dim.Parameters()->Tm.Name(), tm);

	ParametersRef()->Cm() = am / (bwl*tm);
}

void tnbLib::formCoeff::Wetted::CalcAW
(
	const marineLib::Body_Wetted & theBody
)
{
	auto param = 
		Marine_CmptLib::CalcAW
		(
			theBody,
			sysLib::gl_marine_integration_info
		);
	SET_PARAM(Aw);
}

void tnbLib::formCoeff::Wetted::CalcCWL()
{
	Debug_Null_Pointer(WettedFormDim());
	const auto& dim = *WettedFormDim();

	const auto aw = Parameters()->Aw();
	const auto bwl = dim.Parameters()->Bwl();
	const auto lwl = dim.Parameters()->Lwl();

	CheckValue("void CalcCWL()", Parameters()->Aw.Name(), aw);
	CheckValue("void CalcCWL()", dim.Parameters()->Bwl.Name(), bwl);
	CheckValue("void CalcCWL()", dim.Parameters()->Lwl.Name(), lwl);

	auto param = 
		Marine_CmptLib::CalcCWL
		(
			Parameters()->Aw,
			dim.Parameters()->Lwl,
			dim.Parameters()->Bwl
		);
	SET_PARAM(Cwl);
}

void tnbLib::formCoeff::Wetted::CalcCVP()
{
	Debug_Null_Pointer(WettedFormDim());
	const auto& dim = *WettedFormDim();

	const auto aw = Parameters()->Aw();
	const auto tm = dim.Parameters()->Tm();

	CheckValue("void CalcCVP()", Parameters()->Aw.Name(), aw);
	CheckValue("void CalcCVP()", dim.Parameters()->Tm.Name(), tm);

	auto param = 
		Marine_CmptLib::CalcCVP
		(
			Parameters()->Dispv,
			Parameters()->Aw,
			dim.Parameters()->Tm
		);
	SET_PARAM(Cvp);
}

void tnbLib::formCoeff::Wetted::Perform()
{
	if (NOT WettedFormDim())
	{
		FatalErrorIn("void tnbLib::formCoeff::Wetted::Perform()")
			<< "no wetted form dim has been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT WettedFormDim()->IsDone())
	{
		FatalErrorIn("void tnbLib::formCoeff::Wetted::Perform()")
			<< "formDim is not performed!" << endl
			<< abort(FatalError);
	}

	Debug_Null_Pointer(WettedFormDim()->Body());
	const auto& body = *WettedFormDim()->Body();

	CalcDISPV(body);
	CalcCB(body);
	CalcAM(body);

	CalcCP();
	CalcCM();

	CalcAW(body);

	CalcCWL();
	CalcCVP();

	Change_IsDone() = Standard_True;
}

