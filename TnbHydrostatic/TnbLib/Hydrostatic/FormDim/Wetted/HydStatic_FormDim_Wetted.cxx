#include <HydStatic_FormDim_Wetted.hxx>

#include <Marine_Bodies.hxx>
#include <Marine_CmptLib.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::formDim::Wetted::Parameter::Parameter()
	: Tm(0)
	, App(0)
	, Fpp(0)
	, Mpp(0)
	, Lpp(0)
	, Bwl(0)
	, Lwl(0)
	, Fwl(0)
	, Awl(0)
	, Fuw(0)
	, Auw(0)
	, Los(0)
{
	// empty body
}

void tnbLib::formDim::Wetted::CalcTM()
{
	Debug_Null_Pointer(Body());
	const auto par = Marine_CmptLib::CalcTM(*Body());

	Debug_Null_Pointer(ChangeParameters());
	ChangeParameters()->Tm = std::move(par);
}

void tnbLib::formDim::Wetted::CalcFUW()
{
	Debug_Null_Pointer(Body());
	const auto par = Marine_CmptLib::CalcFUW(*Body());

	Debug_Null_Pointer(ChangeParameters());
	ChangeParameters()->Fuw = std::move(par);
}

void tnbLib::formDim::Wetted::CalcAUW()
{
	Debug_Null_Pointer(Body());
	const auto par = Marine_CmptLib::CalcAUW(*Body());

	Debug_Null_Pointer(ChangeParameters());
	ChangeParameters()->Auw = std::move(par);
}

void tnbLib::formDim::Wetted::CalcAWL()
{
	Debug_Null_Pointer(Body());
	const auto par = Marine_CmptLib::CalcAWL(*Body());

	Debug_Null_Pointer(ChangeParameters());
	ChangeParameters()->Awl = std::move(par);
}

void tnbLib::formDim::Wetted::CalcFWL()
{
	Debug_Null_Pointer(Body());
	const auto par = Marine_CmptLib::CalcFWL(*Body());

	Debug_Null_Pointer(ChangeParameters());
	ChangeParameters()->Fwl = std::move(par);
}

void tnbLib::formDim::Wetted::CalcBWL()
{
	Debug_Null_Pointer(Body());
	const auto par = Marine_CmptLib::CalcBWL(*Body());

	Debug_Null_Pointer(ChangeParameters());
	ChangeParameters()->Bwl = std::move(par);
}

void tnbLib::formDim::Wetted::CalcFPP()
{
	Debug_Null_Pointer(Body());
	const auto par = Marine_CmptLib::CalcFPP(*Body());

	Debug_Null_Pointer(ChangeParameters());
	ChangeParameters()->Fpp = std::move(par);
}

void tnbLib::formDim::Wetted::CalcAPP
(
	const Standard_Real theAxis
)
{
	marineLib::APP par(theAxis);

	Debug_Null_Pointer(ChangeParameters());
	ChangeParameters()->App = std::move(par);
}

void tnbLib::formDim::Wetted::CalcAPP()
{
	Debug_Null_Pointer(Body());
	const auto par = Marine_CmptLib::CalcAPP(*Body());

	Debug_Null_Pointer(ChangeParameters());
	ChangeParameters()->App = std::move(par);
}

void tnbLib::formDim::Wetted::CalcLPP()
{
	Debug_Null_Pointer(Parameters());
	const auto par = 
		Marine_CmptLib::CalcLPP
		(
			Parameters()->App, 
			Parameters()->Fpp
		);

	ChangeParameters()->Lpp = std::move(par);
}

void tnbLib::formDim::Wetted::CalcMPP()
{
	Debug_Null_Pointer(Parameters());
	const auto par = 
		Marine_CmptLib::CalcMPP
		(
			Parameters()->App, 
			Parameters()->Fpp
		);

	ChangeParameters()->Mpp = std::move(par);
}

void tnbLib::formDim::Wetted::CalcLWL()
{
	Debug_Null_Pointer(Body());

	if (Body()->ShapeType())
	{
		auto shaped = 
			std::dynamic_pointer_cast
			<
			marineLib::BodyConstructor_Shape<marineLib::Body_Wetted>
			>(Body());

		Debug_Null_Pointer(shaped);
		const auto par = Marine_CmptLib::CalcLWL(*shaped);

		Debug_Null_Pointer(ChangeParameters());
		ChangeParameters()->Lwl = std::move(par);
	}
	else
	{
		auto noShape =
			std::dynamic_pointer_cast
			<
			marineLib::BodyConstructor_noShape<marineLib::Body_Wetted>
			>(Body());

		Debug_Null_Pointer(noShape);
		const auto par = Marine_CmptLib::CalcLWL(*noShape);

		Debug_Null_Pointer(ChangeParameters());
		ChangeParameters()->Lwl = std::move(par);
	}
}

void tnbLib::formDim::Wetted::CalcLOS()
{
	Debug_Null_Pointer(Body());
	Debug_Null_Pointer(Parameters());

	auto par = 
		Marine_CmptLib::CalcLOS
		(
			Parameters()->Auw, 
			Parameters()->Fuw
		);
	ChangeParameters()->Los = std::move(par);
}

void tnbLib::formDim::Wetted::AllocateMemory()
{
	auto p = std::make_shared<Parameter>();
	Debug_Null_Pointer(p);

	ChangeParameters() = std::move(p);
}

tnbLib::formDim::Wetted::Wetted()
{
	// empty body
}

tnbLib::formDim::Wetted::Wetted
(
	const std::shared_ptr<marineLib::Body_Wetted>& theBody
)
	: theBody_(theBody)
{
	// empty body
}

void tnbLib::formDim::Wetted::Perform
(
	const Standard_Real theRudderAxis
)
{
	if (NOT Body())
	{
		FatalErrorIn(FunctionSIG)
			<< "the body has not been loaded!" << endl
			<< abort(FatalError);
	}

	CalcFUW();
	CalcAUW();
	CalcAWL();
	CalcFWL();

	CalcFPP();

	if (AppMode() IS_EQUAL appMode::Auto)
	{
		CalcAPP();
	}
	else if (AppMode() IS_EQUAL appMode::rudderAxis)
	{
		CalcAPP(theRudderAxis);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "Unspecified mode of the App" << endl
			<< abort(FatalError);
	}

	CalcLPP();
	CalcMPP();
	CalcLWL();
	CalcLOS();

	CalcBWL();

	Change_IsDone() = Standard_True;
}

void tnbLib::formDim::Wetted::LoadBody
(
	const std::shared_ptr<marineLib::Body_Wetted>& theBody
)
{
	theBody_ = theBody;
}