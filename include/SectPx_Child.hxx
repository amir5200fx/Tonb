#pragma once
#ifndef _SectPx_Child_Header
#define _SectPx_Child_Header

#include <SectPx_RegObj.hxx>
#include <SectPx_ParentAdaptor.hxx>

namespace tnbLib
{

	class SectPx_Child
		: public SectPx_RegObj
		, public SectPx_ParentAdaptor
	{

		/*Private Data*/

	protected:

		template<class... _Types>
		SectPx_Child(_Types&&... _Args)
			: SectPx_RegObj(_Args...)
		{}

	public:

		Standard_Boolean IsChild() const override;

	};
}

#endif // !_SectPx_Child_Header
