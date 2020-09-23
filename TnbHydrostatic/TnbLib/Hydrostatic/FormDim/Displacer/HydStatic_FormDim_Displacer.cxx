#include <HydStatic_FormDim_Displacer.hxx>

tnbLib::formDim::Displacer::Parameter::Parameter()
	: B(0)
	, D(0)
	, Loa(0)
{
	// empty body
}

tnbLib::formDim::Displacer::Displacer
(
	const std::shared_ptr<marineLib::Body_Displacer>& theBody
)
	: theBody_(theBody)
{
	//- empty body
}

void tnbLib::formDim::Displacer::LoadBody
(
	const std::shared_ptr<marineLib::Body_Displacer>& theBody
)
{
	theBody_ = theBody;
}

#include <Marine_Bodies.hxx>
#include <Marine_CmptLib.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::formDim::Displacer::AllocateMemory()
{
	auto p = std::make_shared<Parameter>();
	Debug_Null_Pointer(p);

	ChangeParameters() = std::move(p);
}

void tnbLib::formDim::Displacer::CalcDims()
{
	Debug_Null_Pointer(Body());
	const auto[loa, b, d] = Marine_CmptLib::CalcBasicDim(*Body());

	Debug_Null_Pointer(ChangeParameters());
	auto& params = *ChangeParameters();

	params.B = std::move(b);
	params.D = std::move(d);
	params.Loa = std::move(loa);
}

void tnbLib::formDim::Displacer::Perform()
{
	if (NOT Body())
	{
		FatalErrorIn(FunctionSIG)
			<< "no body has been loaded!" << endl
			<< abort(FatalError);
	}

	AllocateMemory();

	CalcDims();

	Change_IsDone() = Standard_True;
}