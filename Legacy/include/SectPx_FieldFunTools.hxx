#pragma once
#ifndef _SectPx_FieldFunTools_Header
#define _SectPx_FieldFunTools_Header

#include <SectPx_Module.hxx>
#include <Global_TypeDef.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_FieldFun;
	class SectPx_RegObj;

	class SectPx_FieldFunTools
	{

	public:

		static TnbSectPx_EXPORT Standard_Boolean IsRemovable(const std::shared_ptr<SectPx_FieldFun>&);

		static TnbSectPx_EXPORT Standard_Boolean IsFieldFun(const std::shared_ptr<SectPx_RegObj>& theObj);

		static TnbSectPx_EXPORT std::shared_ptr<SectPx_FieldFun> FieldFun(const std::shared_ptr<SectPx_RegObj>& theObj);
	};
}

#endif // !_SectPx_FieldFunTools_Header
