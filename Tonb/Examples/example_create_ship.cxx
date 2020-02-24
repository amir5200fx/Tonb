#include <Tnb_Examples.hxx>

#include <LegModel_DispNo1.hxx>
#include <Cad_Tools.hxx>

using namespace tnbLib;

void tnbLib::example_create_ship()
{
	auto ship = std::make_shared<LegModel_DispNo1>();
	Debug_Null_Pointer(ship);

	ship->Perform();
	//ship->PerformToPreview();

	const auto& hull = ship->Entity();
	Cad_Tools::ExportToIGES("m", hull, "example_create_ship.igs");
}