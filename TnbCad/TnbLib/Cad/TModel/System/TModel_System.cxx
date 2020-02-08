#include <TModel_System.hxx>

#include <TModel_FixWire_Info.hxx>

std::shared_ptr<tnbLib::TModel_FixWire_Info>
tnbLib::sysLib::tmodel_fix_wire_info = std::make_shared<tnbLib::TModel_FixWire_Info>();

void tnbLib::sysLib::init_tmodel_fix_wire_info()
{
	auto& inf = *tmodel_fix_wire_info;

	inf.SetPrecision(1.0E-3);
	inf.SetMaxTolerance(1.0E-2);
	inf.SetMinTolerance(1.0E-6);
}