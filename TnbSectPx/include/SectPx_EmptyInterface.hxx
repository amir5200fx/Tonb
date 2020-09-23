#pragma once
#ifndef _SectPx_EmptyInterface_Header
#define _SectPx_EmptyInterface_Header

#include <SectPx_Interface.hxx>

namespace tnbLib
{

	class SectPx_EmptyInterface
		: public SectPx_Interface
	{

		/*Private Data*/

	public:

		static const char* typeName_;

		template<class... _Types>
		SectPx_EmptyInterface(_Types&&... _Args)
			: SectPx_Interface(_Args...)
		{}

		Standard_Boolean IsEmpty() const override;

		word RegObjTypeName() const override;

		sectPxLib::interfaceType InterfaceType() const override;

		void disJoint() override;
	};
}

#endif // !_SectPx_EmptyInterface_Header
