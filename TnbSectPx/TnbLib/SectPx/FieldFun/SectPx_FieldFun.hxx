#pragma once
#ifndef _SectPx_FieldFun_Header
#define _SectPx_FieldFun_Header

#include <SectPx_Parent.hxx>

namespace tnbLib
{

	class SectPx_FieldFun_Temp
	{

		/*Private Data*/

		mutable Standard_Real theTemp_;

	protected:

		SectPx_FieldFun_Temp()
		{}

		auto& Temp() const
		{
			return theTemp_;
		}

	};

	// Forward Declarations
	namespace maker { class FieldFun; }

	class SectPx_FieldFun
		: public SectPx_Parent
		, public SectPx_FieldFun_Temp
	{

		friend class maker::FieldFun;

		/*Private Data*/

		mutable Standard_Boolean IsRegistered_;

	protected:

		template<class... _Types>
		SectPx_FieldFun(_Types&&... _Args)
			: SectPx_Parent(_Args...)
			, IsRegistered_(Standard_False)
		{}

		auto& IsRegistered() const
		{
			return IsRegistered_;
		}

	public:

		auto& xRef()
		{
			Temp() = Value();
			return Temp();
		}

		const auto& xRef() const
		{
			Temp() = Value();
			return Temp();
		}

		Standard_Boolean IsFieldFun() const override;

		sectPxLib::regObjType RegObjType() const override;

		virtual Standard_Boolean IsComplete() const = 0;

		virtual Standard_Real Value() const = 0;

		friend std::shared_ptr<SectPx_FieldFun> 
			operator+
			(
				const std::shared_ptr<SectPx_FieldFun>& f0,
				const std::shared_ptr<SectPx_FieldFun>& f1
				);
		friend std::shared_ptr<SectPx_FieldFun> 
			operator-
			(
				const std::shared_ptr<SectPx_FieldFun>& f0, 
				const std::shared_ptr<SectPx_FieldFun>& f1
				);
		friend std::shared_ptr<SectPx_FieldFun> 
			operator*
			(
				const std::shared_ptr<SectPx_FieldFun>& f0,
				const std::shared_ptr<SectPx_FieldFun>& f1
				);
		friend std::shared_ptr<SectPx_FieldFun> 
			operator/
			(
				const std::shared_ptr<SectPx_FieldFun>& f0,
				const std::shared_ptr<SectPx_FieldFun>& f1
				);
	};
}

#endif // !_SectPx_FieldFun_Header
