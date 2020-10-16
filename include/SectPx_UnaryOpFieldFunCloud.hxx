#pragma once
#ifndef _SectPx_UnaryOpFieldFunCloud_Header
#define _SectPx_UnaryOpFieldFunCloud_Header

#include <SectPx_nonParFieldFunCloud.hxx>

namespace tnbLib
{

	class SectPx_UnaryOpFieldFunCloud
		: public SectPx_nonParFieldFunCloud
	{

		/*Private Data*/

	protected:

		template<class... _Types>
		SectPx_UnaryOpFieldFunCloud(_Types&&... _Args)
			: SectPx_nonParFieldFunCloud(_Args...)
		{}

	public:

		virtual Standard_Boolean HandleMemory() const = 0;
	};

	template<class T>
	class SectPx_UnaryOpFieldFunCloud_Memory
	{};

	template<>
	class SectPx_UnaryOpFieldFunCloud_Memory<std::shared_ptr<SectPx_FieldFunCloud>>
		: public SectPx_UnaryOpFieldFunCloud
	{

		/*Private Data*/

		std::shared_ptr<SectPx_FieldFunCloud> theField_;

	protected:

		template<class... _Types>
		SectPx_UnaryOpFieldFunCloud_Memory(_Types&&... _Args)
			: SectPx_UnaryOpFieldFunCloud(_Args...)
		{}

	public:

		Standard_Boolean HandleMemory() const override
		{
			return Standard_True;
		}

		const auto& FieldFun() const
		{
			return theField_;
		}

		void SetField
		(
			const std::shared_ptr<SectPx_FieldFunCloud>& theField
		)
		{
			theField_ = theField;
		}

		void SetField
		(
			std::shared_ptr<SectPx_FieldFunCloud>&& theField
		)
		{
			theField_ = std::move(theField);
		}
	};


	template<>
	class SectPx_UnaryOpFieldFunCloud_Memory<std::weak_ptr<SectPx_FieldFunCloud>>
		: public SectPx_UnaryOpFieldFunCloud
	{

		/*Private Data*/

		std::weak_ptr<SectPx_FieldFunCloud> theField_;

	protected:

		template<class... _Types>
		SectPx_UnaryOpFieldFunCloud_Memory(_Types&&... _Args)
			: SectPx_UnaryOpFieldFunCloud(_Args...)
		{}

	public:

		Standard_Boolean HandleMemory() const override
		{
			return Standard_False;
		}

		const auto& FieldFun() const
		{
			return theField_;
		}

		void SetField
		(
			const std::shared_ptr<SectPx_FieldFunCloud>& theField
		)
		{
			theField_ = theField;
		}
	};
}

#endif // !_SectPx_UnaryOpFieldFunCloud_Header
