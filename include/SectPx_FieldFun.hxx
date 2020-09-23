#pragma once
#ifndef _SectPx_FieldFun_Header
#define _SectPx_FieldFun_Header

#include <SectPx_Parent.hxx>

namespace tnbLib
{

	class SectPx_FieldFun
		: public SectPx_Parent
	{

		/*Private Data*/

	protected:

		template<class... _Types>
		SectPx_FieldFun(_Types&&... _Args)
			: SectPx_Parent(_Args...)
		{}

	public:

		Standard_Boolean IsFieldFun() const override;

		sectPxLib::regObjType RegObjType() const override;

		virtual Standard_Boolean IsComplete() const = 0;

		virtual Standard_Real Value() const = 0;

		friend std::shared_ptr<SectPx_FieldFun> operator+(const std::shared_ptr<SectPx_FieldFun>& f0, const std::shared_ptr<SectPx_FieldFun>& f1);
		friend std::shared_ptr<SectPx_FieldFun> operator-(const std::shared_ptr<SectPx_FieldFun>& f0, const std::shared_ptr<SectPx_FieldFun>& f1);
		friend std::shared_ptr<SectPx_FieldFun> operator*(const std::shared_ptr<SectPx_FieldFun>& f0, const std::shared_ptr<SectPx_FieldFun>& f1);
		friend std::shared_ptr<SectPx_FieldFun> operator/(const std::shared_ptr<SectPx_FieldFun>& f0, const std::shared_ptr<SectPx_FieldFun>& f1);
	};
}

#endif // !_SectPx_FieldFun_Header
