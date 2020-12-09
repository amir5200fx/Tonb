#include <HydStatic_Model.hxx>

#include <Marine_Domain.hxx>
#include <Marine_Models.hxx>
#include <Marine_Bodies.hxx>
#include <Marine_BodyTools.hxx>
#include <Marine_WaterDomain.hxx>
#include <Marine_WaterLib.hxx>
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

void tnbLib::HydStatic_Model::CalcDomain()
{
	theDomain_ = std::make_shared<Marine_Domain>(0, "domain");
	Debug_Null_Pointer(theDomain_);

	const auto& model = StbModel();
	if (NOT model->Hull())
	{
		FatalErrorIn(FunctionSIG)
			<< "the model has no hull!" << endl
			<< abort(FatalError);
	}
	auto b = StbGMaker_Tools::BoundingBox(model);
	theDomain_->Perform(b);
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

	auto wettedBody = 
		Marine_BodyTools::WettedBody
		(
			Marine_BodyTools::WettedBody(displacer, waterDomain)
		);
	Debug_Null_Pointer(wettedBody);

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

	if (verbose) Info << " - calculating the domain..." << endl;
	CalcDomain();

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
}