#pragma once
#ifndef _SectPx_FieldFunCloud_Header
#define _SectPx_FieldFunCloud_Header

#include <SectPx_Parent.hxx>

#include <memory>

namespace tnbLib
{

	class SectPx_FieldFunCloud_Temp
	{

		/*Private Data*/

		mutable std::vector<Standard_Real> theTemp_;

	protected:

		SectPx_FieldFunCloud_Temp()
		{}

		auto& Temp() const
		{
			return theTemp_;
		}
	};

	class SectPx_FieldFunCloud
		: public SectPx_Parent
		, public SectPx_FieldFunCloud_Temp
	{

		/*Private Data*/

		mutable Standard_Boolean IsRegistered_;

	protected:

		template<class... _Types>
		SectPx_FieldFunCloud(_Types&&... _Args)
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

		virtual Standard_Boolean IsComplete() const = 0;

		virtual std::vector<Standard_Real> Value() const = 0;

		friend std::shared_ptr<SectPx_FieldFunCloud>
			operator+
			(
				const std::shared_ptr<SectPx_FieldFunCloud>& f0,
				const std::shared_ptr<SectPx_FieldFunCloud>& f1
				);
		friend std::shared_ptr<SectPx_FieldFunCloud>
			operator-
			(
				const std::shared_ptr<SectPx_FieldFunCloud>& f0,
				const std::shared_ptr<SectPx_FieldFunCloud>& f1
				);
		friend std::shared_ptr<SectPx_FieldFunCloud>
			operator*
			(
				const std::shared_ptr<SectPx_FieldFunCloud>& f0,
				const std::shared_ptr<SectPx_FieldFunCloud>& f1
				);
		friend std::shared_ptr<SectPx_FieldFunCloud>
			operator/
			(
				const std::shared_ptr<SectPx_FieldFunCloud>& f0,
				const std::shared_ptr<SectPx_FieldFunCloud>& f1
				);
	};
}

#endif // !_SectPx_FieldFunCloud_Header
