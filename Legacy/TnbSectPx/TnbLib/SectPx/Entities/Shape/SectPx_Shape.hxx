#pragma once
#ifndef _SectPx_Shape_Header
#define _SectPx_Shape_Header

#include <SectPx_RegObj.hxx>

namespace tnbLib
{

	class SectPx_Shape
		: public SectPx_RegObj
	{

		/*Private Data*/

	protected:


		template<class... _Types>
		SectPx_Shape(_Types&&... _Args)
			: SectPx_RegObj(_Args...)
		{}

	public:

		static TnbSectPx_EXPORT const char* typeName_;

		TnbSectPx_EXPORT word RegObjTypeName() const override;

		TnbSectPx_EXPORT sectPxLib::regObjType RegObjType() const override;

		TnbSectPx_EXPORT virtual Standard_Boolean IsSection() const;

		TnbSectPx_EXPORT virtual Standard_Boolean IsProfile() const;
	};
}

#endif // !_SectPx_Shape_Header
