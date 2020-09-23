#pragma once
#ifndef _SectPx_nonParFieldFun_Header
#define _SectPx_nonParFieldFun_Header

#include <SectPx_FieldFun.hxx>

namespace tnbLib
{

	class SectPx_nonParFieldFun
		: public SectPx_FieldFun
	{

		/*Private Data*/

	protected:

		template<class... _Types>
		SectPx_nonParFieldFun(_Types&&... _Args)
			: SectPx_FieldFun(_Args...)
		{}

	public:

		Standard_Boolean IsComplete() const override;

		Standard_Boolean HasChild
		(
			const std::shared_ptr<SectPx_Par>& thePar
		) const override;

		void RemoveThisFromChilds() const override;

		void AddThisToChilds() const override;

		void AddThisToChild
		(
			const std::shared_ptr<SectPx_Par>& thePar
		) const override;

		void RemoveThisFromChild
		(
			const std::shared_ptr<SectPx_Par>& thePar
		) const override;

	};
}

#endif // !_SectPx_nonParFieldFun_Header
