#pragma once
#ifndef _TModel_System_Header
#define _TModel_System_Header

#include <Cad_Module.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class TModel_FixWire_Info;

	namespace sysLib
	{

		extern TnbCad_EXPORT std::shared_ptr<TModel_FixWire_Info> tmodel_fix_wire_info;

		TnbCad_EXPORT void init_tmodel_fix_wire_info();
	}
}

#endif // !_TModel_System_Header
