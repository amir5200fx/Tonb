#include <HydStatic_Model.hxx>

#include <Marine_Domain.hxx>
#include <Marine_Models.hxx>
#include <Marine_Bodies.hxx>
#include <Marine_BodyTools.hxx>
#include <Marine_WaterDomain.hxx>
#include <Marine_WaterLib.hxx>
#include <Marine_FlatWave.hxx>
#include <StbGMaker_Model.hxx>
#include <StbGMaker_Tools.hxx>
#include <HydStatic_FloatBody.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

unsigned short tnbLib::HydStatic_Model::verbose(0);

tnbLib::HydStatic_Model::HydStatic_Model
(
	const Standard_Integer theIndex, 
	const word & theName
)
	: HydStatic_Entity(theIndex, theName)
{
	// empty body
}

void tnbLib::HydStatic_Model::CalcWater()
{
	const auto& model = StbModel();
	if (NOT model->Hull())
	{
		FatalErrorIn(FunctionSIG)
			<< "the model has no hull!" << endl
			<< abort(FatalError);
	}
	auto domain = 
		Marine_WaterLib::WaterDomain(*model->Hull()->Body(), Wave(), Domain(), 1.0E-6, 1.0E-4);
	Debug_Null_Pointer(domain);

	theWater_ = std::move(domain->Water());
}

void tnbLib::HydStatic_Model::CalcFloatBody()
{
	const auto& model = StbModel();
	if (NOT model->Hull())
	{
		FatalErrorIn(FunctionSIG)
			<< "the model has no hull!" << endl
			<< abort(FatalError);
	}

	if (NOT Domain())
	{
		FatalErrorIn(FunctionSIG)
			<< "no domain has been found" << endl
			<< abort(FatalError);
	}

	if (NOT Wave())
	{
		FatalErrorIn(FunctionSIG)
			<< "no wave has been found" << endl
			<< abort(FatalError);
	}

	auto waterDomain = 
		std::make_shared<Marine_WaterDomain>
		(
			Domain(),
			Water(),
			Wave()
			);
	Debug_Null_Pointer(waterDomain);

	auto displacer = 
		RetrieveDisplacer
		(
			model, 
			"void tnbLib::HydStatic_Model::CalcFloatBody()"
		);
	Debug_Null_Pointer(displacer);

	if (verbose) Info << " calculating the wetted body..." << endl;
	auto wettedBody = 
		Marine_BodyTools::WettedBody
		(
			Marine_BodyTools::WettedBody(displacer, waterDomain)
		);
	Debug_Null_Pointer(wettedBody);

	if (verbose) Info << " calculating the dry body..." << endl;
	auto dryBody = 
		Marine_BodyTools::DryBody
		(
			Marine_BodyTools::DryBody(displacer, waterDomain)
		);
	Debug_Null_Pointer(dryBody);

	auto floatBody = 
		std::make_shared<HydStatic_FloatBody>
		(
			0, "float body",
			std::move(dryBody), 
			std::move(wettedBody)
			);
	Debug_Null_Pointer(floatBody);

	theFloatBody_ = std::move(floatBody);
}

std::shared_ptr<tnbLib::marineLib::Body_Displacer> 
tnbLib::HydStatic_Model::RetrieveDisplacer
(
	const std::shared_ptr<StbGMaker_Model>& theModel, 
	const char * name
)
{
	const auto& hull = theModel->Hull();
	if (NOT hull)
	{
		FatalErrorIn(FunctionSIG)
			<< "the model has no hull!" << endl
			<< abort(FatalError);
	}

	const auto& body = hull->Body();
	if (NOT body)
	{
		FatalErrorIn(FunctionSIG)
			<< "there is no body in the hull!" << endl
			<< abort(FatalError);
	}

	auto displacer = 
		std::dynamic_pointer_cast<marineLib::Body_Displacer>(body);
	return std::move(displacer);
}

const tnbLib::Marine_BaseLine & 
tnbLib::HydStatic_Model::BaseLine() const
{
	const auto& model = StbModel();
	if (NOT model->Hull())
	{
		FatalErrorIn(FunctionSIG)
			<< "the model has no hull!" << endl
			<< abort(FatalError);
	}

	const auto& body = model->Hull()->Body();
	if (NOT body)
	{
		FatalErrorIn(FunctionSIG)
			<< " the hull has no body" << endl
			<< abort(FatalError);
	}

	return body->BaseLine();
}

void tnbLib::HydStatic_Model::Perform()
{
	if (verbose)
	{
		Info << endl;
		Info << "******* Constructing Hydrostatic Model ********" << endl;
		Info << endl;
	}

	if (NOT StbModel())
	{
		FatalErrorIn(FunctionSIG)
			<< "no model has been loaded" << endl
			<< abort(FatalError);
	}

	if (NOT Wave())
	{
		FatalErrorIn(FunctionSIG)
			<< "no wave has been loaded" << endl
			<< abort(FatalError);
	}

	if (verbose) Info << " - calculating the water..." << endl;
	CalcWater();

	if (verbose) Info << " - calculating the floating body..." << endl;
	CalcFloatBody();

	if (verbose)
	{
		Info << endl;
		Info << "******* End of the Constructing Hydrostatic Model ********" << endl;
		Info << endl;
	}

	Change_IsDone() = Standard_True;
}