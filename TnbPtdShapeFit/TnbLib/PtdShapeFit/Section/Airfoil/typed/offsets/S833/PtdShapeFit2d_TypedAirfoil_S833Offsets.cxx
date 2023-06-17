#include <PtdShapeFit2d_TypedAirfoil_S833Offsets.hxx>

#include <Geo_AirfoilOffsets_S833.hxx>

const char* tnbLib::airfoilLib::offsetsLib::S833::type_name = "s_833";
const char* tnbLib::airfoilLib::offsetsLib::S833::airfoil_type_name = "S833";

void tnbLib::airfoilLib::offsetsLib::S833::SetAirfoilName()
{
	this->SetName(airfoil_type_name);
}

void tnbLib::airfoilLib::offsetsLib::S833::SetOffsets()
{
	auto& coords = CoordsRef();
	coords = geoLib::airfoilOffsetsLib::S833::coords;
}

tnbLib::airfoilLib::offsetsLib::S833::S833()
{
	SetAirfoilName();
	SetOffsets();
}

tnbLib::word
tnbLib::airfoilLib::offsetsLib::S833::OffsetTypeName() const
{
	return word(type_name);
}