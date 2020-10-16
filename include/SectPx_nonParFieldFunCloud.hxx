#pragma once
#ifndef _SectPx_nonParFieldFunCloud_Header
#define _SectPx_nonParFieldFunCloud_Header

#include <SectPx_FieldFunCloud.hxx>

namespace tnbLib
{

	class SectPx_nonParFieldFunCloud
		: public SectPx_FieldFunCloud
	{

		/*Private Data*/

	protected:

		template<class... _Types>
		SectPx_nonParFieldFunCloud(_Types&&... _Args)
			: SectPx_FieldFunCloud(_Args...)
		{}

	public:

		Standard_Boolean IsComplete() const override;

		Standard_Boolean HasChild
		(
			const std::shared_ptr<SectPx_Child>& thePar
		) const override;

		void RemoveThisFromChildren() const override;

		void AddThisToChildren() const override;

		void AddThisToChild
		(
			const std::shared_ptr<SectPx_Child>& thePar
		) const override;

		void RemoveThisFromChild
		(
			const std::shared_ptr<SectPx_Child>& thePar
		) const override;
	};
}

#endif // !_SectPx_nonParFieldFunCloud_Header
