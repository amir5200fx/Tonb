#pragma once
#ifndef _ShapePx_Tip_Header
#define _ShapePx_Tip_Header

#include <ShapePx_Entity.hxx>

namespace tnbLib
{

	class ShapePx_Tip
		: public ShapePx_Entity
	{

		/*Private Data*/

	protected:


		template<class... _Types>
		ShapePx_Tip(_Types&&... _Args)
			: ShapePx_Entity(_Args...)
		{}

	public:

		virtual Standard_Boolean IsSpherical() const;

		virtual Standard_Boolean IsCylindrical() const;
	};
}

#endif // !_ShapePx_Tip_Header
