#include <HydStatic_FormDim_Wetted.hxx>

#include <Marine_Bodies.hxx>
#include <Marine_CmptLib.hxx>
#include <Marine_MidSection.hxx>
#include <Marine_MidSectionApprox_Near.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

unsigned short tnbLib::formDim::Wetted::verbose(0);

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
	const auto& pars = Parameters();
	if (NOT Body()->Mid())
	{
		if (verbose)
		{
			Info << " no mid ship section has been found" << endl;
			Info << " attempting to construct a midship section..." << endl;
		}

		const auto& displacer = Body()->Displacer();
		Marine_MidSection midSect(displacer, Body(), Wave());
		if (displacer->ShapeType())
		{
			auto x = MEAN(pars->App(), pars->Fpp());
			midSect.ApplyAt(x);
		}
		else
		{
			marineLib::MidSectionApprox_Near approx;
			approx.LoadBody(displacer);
			
			approx.Perform(MEAN(pars->App(), pars->Fpp()));
			Debug_If_Condition_Message(NOT approx.IsDone(), "the approximate mid-section is not performed!");

			Debug_Null_Pointer(approx.Section());
			midSect.ApplyAt(approx.Section());
		}
		
		if (verbose)
		{
			Info << " midShip section is added to the wetted body, successfully!" << endl;
		}
	}

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

	theAppMode_ = appMode::Auto;
}

tnbLib::formDim::Wetted::Wetted()
{
	// empty body
}

tnbLib::formDim::Wetted::Wetted
(
	const std::shared_ptr<marineLib::Body_Wetted>& theBody,
	const std::shared_ptr<Marine_Wave>& theWave
)
	: theBody_(theBody)
	, theWave_(theWave)
{
	// empty body
}

void tnbLib::formDim::Wetted::Perform
(
	const Standard_Real theRudderAxis
)
{
	
	if (verbose)
	{
		Info << endl;
		Info << "******* Calculating Wetted Form Dimensions ********" << endl;
		Info << endl;
	}

	if (NOT Body())
	{
		FatalErrorIn(FunctionSIG)
			<< "the body has not been loaded!" << endl
			<< abort(FatalError);
	}

	AllocateMemory();

	const auto& pars = Parameters();

	if (verbose) Info << " calculating the FUW..." << endl;
	CalcFUW();
	if (verbose) Info << pars->Fuw << endl << endl;

	if (verbose) Info << " calculating the AUW..." << endl;
	CalcAUW();
	if (verbose) Info << pars->Auw << endl << endl;

	if (verbose) Info << " calculating the AWL..." << endl;
	CalcAWL();
	if (verbose) Info << pars->Awl << endl << endl;

	if (verbose) Info << " calculating the FWL..." << endl;
	CalcFWL();
	if (verbose) Info << pars->Fwl << endl << endl;

	if (verbose) Info << " calculating the FPP..." << endl;
	CalcFPP();
	if (verbose) Info << pars->Fpp << endl << endl;

	if (verbose)
	{
		Info << " App mode is set to: " 
			<< (AppMode() IS_EQUAL appMode::rudderAxis ? ("Rudder") : ("Auto")) 
			<< endl;
		Info << " calculating the APP..." << endl;
	}
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
	if (verbose) Info << pars->App << endl << endl;

	if (verbose) Info << " calculating the LPP..." << endl;
	CalcLPP();
	if (verbose) Info << pars->Lpp << endl << endl;

	if (verbose) Info << " calculating the MPP..." << endl;
	CalcMPP();
	if (verbose) Info << pars->Mpp << endl << endl;

	if (verbose) Info << " calculating the LWL..." << endl;
	CalcLWL();
	if (verbose) Info << pars->Lwl << endl << endl;

	if (verbose) Info << " calculating the LOS..." << endl;
	CalcLOS();
	if (verbose) Info << pars->Los << endl << endl;

	if (verbose) Info << " calculating the BWL..." << endl;
	CalcBWL();
	if (verbose) Info << pars->Bwl << endl << endl;

	if (verbose) Info << " calculating the TM..." << endl;
	CalcTM();
	if (verbose) Info << pars->Tm << endl << endl;

	Change_IsDone() = Standard_True;

	if (verbose)
	{
		Info << endl;
		Info << "******* End of Calculating Wetted Form Dimensions ********" << endl;
		Info << endl;
	}
}

void tnbLib::formDim::Wetted::LoadBody
(
	const std::shared_ptr<marineLib::Body_Wetted>& theBody
)
{
	theBody_ = theBody;
}

void tnbLib::formDim::Wetted::LoadWave
(
	const std::shared_ptr<Marine_Wave>& theWave
)
{
	theWave_ = theWave;
}

void tnbLib::formDim::Wetted::SetAppMode
(
	const appMode mode
)
{
	theAppMode_ = mode;
}