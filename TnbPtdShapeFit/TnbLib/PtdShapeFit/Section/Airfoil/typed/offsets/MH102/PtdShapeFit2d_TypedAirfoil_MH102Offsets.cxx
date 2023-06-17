#include <PtdShapeFit2d_TypedAirfoil_MH102Offsets.hxx>

#include <Geo_AirfoilOffsets_MH102.hxx>

const char* tnbLib::airfoilLib::offsetsLib::MH102::type_name = "mh_102";
const char* tnbLib::airfoilLib::offsetsLib::MH102::airfoil_type_name = "MH102";

void tnbLib::airfoilLib::offsetsLib::MH102::SetAirfoilName()
{
	this->SetName(airfoil_type_name);
}

void tnbLib::airfoilLib::offsetsLib::MH102::SetOffsets()
{
	auto& coords = CoordsRef();
	coords = geoLib::airfoilOffsetsLib::coords;
}

tnbLib::airfoilLib::offsetsLib::MH102::MH102()
{
	SetAirfoilName();
	SetOffsets();
}

tnbLib::word 
tnbLib::airfoilLib::offsetsLib::MH102::OffsetTypeName() const
{
	return word(type_name);
}