#pragma once
#ifndef _SectPx_BinaryOpFieldFun_Header
#define _SectPx_BinaryOpFieldFun_Header

#include <SectPx_nonParFieldFun.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_FieldFun;

	class SectPx_BinaryOpFieldFun
		: public SectPx_nonParFieldFun
	{

		/*Private Data*/

		std::shared_ptr<SectPx_FieldFun> theLeft_;
		std::shared_ptr<SectPx_FieldFun> theRight_;

	protected:

		template<class... _Types>
		SectPx_BinaryOpFieldFun(_Types&&... _Args)
			: SectPx_nonParFieldFun(_Args...)
		{}

	public:

		const auto& Left() const
		{
			return theLeft_;
		}

		const auto& Right() const
		{
			return theRight_;
		}

		void SetLeft
		(
			const std::shared_ptr<SectPx_FieldFun>& theField
		)
		{
			theLeft_ = theField;
		}

		void SetLeft
		(
			std::shared_ptr<SectPx_FieldFun>&& theField
		)
		{
			theLeft_ = std::move(theField);
		}

		void SetRight
		(
			const std::shared_ptr<SectPx_FieldFun>& theField
		)
		{
			theRight_ = theField;
		}

		void SetRight
		(
			std::shared_ptr<SectPx_FieldFun>&& theField
		)
		{
			theRight_ = std::move(theField);
		}
	};
}

#endif // !_SectPx_BinaryOpFieldFun_Header
