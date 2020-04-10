#pragma once
#ifndef _Marine_PortLib_Header
#define _Marine_PortLib_Header

#include <Standard_TypeDef.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Marine_CmpSection;
	class Marine_Body;
	class Marine_HullBody;
	class Marine_WettedBody;

	class Marine_PortLib
	{

	public:

		static std::shared_ptr<Marine_WettedBody> CalcWettedBody(const std::shared_ptr<Marine_HullBody>& theBody);
	};
}

#endif // !_Marine_PortLib_Header
