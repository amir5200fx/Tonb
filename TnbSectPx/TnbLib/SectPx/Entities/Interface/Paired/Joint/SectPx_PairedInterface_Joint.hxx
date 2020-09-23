#pragma once
#ifndef _SectPx_PairedInterface_Joint_Header
#define _SectPx_PairedInterface_Joint_Header

#include <SectPx_PairedInterface.hxx>

namespace tnbLib
{

	namespace sectPxLib
	{

		class PairedInterface_Joint
			: public SectPx_PairedInterface
		{

			/*Private Data*/

		public:

			static const char* typeName_;

			template<class... _Types>
			PairedInterface_Joint(_Types&&... _Args)
				: SectPx_PairedInterface(_Args...)
			{}

			word RegObjTypeName() const override;

			sectPxLib::interfaceType InterfaceType() const override;

		};
	}
}

#endif // !_SectPx_PairedInterface_Joint_Header

