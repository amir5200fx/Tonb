#include <Mesh_VariationRate.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

static const Standard_Real DEFAULT_VERYLOWRATE = 0.1;
static const Standard_Real DEFAULT_LOWRATE = 0.2;
static const Standard_Real DEFAULT_MODERATE = 0.35;
static const Standard_Real DEFAULT_FASTRATE = 0.5;

Standard_Real tnbLib::Mesh_VariationRate::customValue = DEFAULT_MODERATE;

Standard_Real 
tnbLib::Mesh_VariationRate::VeryLowrate()
{
	return DEFAULT_VERYLOWRATE;
}

Standard_Real 
tnbLib::Mesh_VariationRate::Lowrate()
{
	return DEFAULT_LOWRATE;
}

Standard_Real 
tnbLib::Mesh_VariationRate::Moderate()
{
	return DEFAULT_MODERATE;
}

Standard_Real 
tnbLib::Mesh_VariationRate::Highrate()
{
	return DEFAULT_FASTRATE;
}

Standard_Real 
tnbLib::Mesh_VariationRate::Rate
(
	const Mesh_VariationRateInfo Info
)
{
	switch (Info)
	{
	case Mesh_VariationRateInfo::verySlow:
		return VeryLowrate();
	case Mesh_VariationRateInfo::slow:
		return Lowrate();
	case Mesh_VariationRateInfo::moderate:
		return Moderate();
	case Mesh_VariationRateInfo::fast:
		return Highrate();
	case Mesh_VariationRateInfo::custom:
		return customValue;
	default:
		FatalErrorIn(FunctionSIG)
			<< "Invalid rate of variation has been detected!" << endl
			<< abort(FatalError);
		break;
	}
	return Moderate();
}