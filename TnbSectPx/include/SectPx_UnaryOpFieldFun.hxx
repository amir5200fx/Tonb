#pragma once
#ifndef _SectPx_UnaryOpFieldFun_Header
#define _SectPx_UnaryOpFieldFun_Header

#include <SectPx_nonParFieldFun.hxx>

namespace tnbLib
{

	class SectPx_UnaryOpFieldFun
		: public SectPx_nonParFieldFun
	{

		/*Private Data*/

		std::shared_ptr<SectPx_FieldFun> theField_;

	protected:

		template<class... _Types>
		SectPx_UnaryOpFieldFun(_Types&&... _Args)
			: SectPx_nonParFieldFun(_Args...)
		{}

		/*SectPx_UnaryOpFieldFun()
		{}

		explicit SectPx_UnaryOpFieldFun
		(
			const Standard_Integer theIndex
		);

		SectPx_UnaryOpFieldFun
		(
			const Standard_Integer theIndex,
			const word& theName
		);

		explicit SectPx_UnaryOpFieldFun
		(
			const std::shared_ptr<SectPx_FieldFun>& theField
		);

		explicit SectPx_UnaryOpFieldFun
		(
			std::shared_ptr<SectPx_FieldFun>&& theField
		);

		SectPx_UnaryOpFieldFun
		(
			const Standard_Integer theIndex, 
			const std::shared_ptr<SectPx_FieldFun>& theField
		);

		SectPx_UnaryOpFieldFun
		(
			const Standard_Integer theIndex,
			std::shared_ptr<SectPx_FieldFun>&& theField
		);

		SectPx_UnaryOpFieldFun
		(
			const Standard_Integer theIndex, 
			const word& theName, 
			const std::shared_ptr<SectPx_FieldFun>& theField
		);

		SectPx_UnaryOpFieldFun
		(
			const Standard_Integer theIndex,
			const word& theName,
			std::shared_ptr<SectPx_FieldFun>&& theField
		);*/

	public:

		const auto& FieldFun() const
		{
			return theField_;
		}

		void SetField
		(
			const std::shared_ptr<SectPx_FieldFun>& theField
		)
		{
			theField_ = theField;
		}

		void SetField
		(
			std::shared_ptr<SectPx_FieldFun>&& theField
		)
		{
			theField_ = std::move(theField);
		}
	};
}

#endif // !_SectPx_UnaryOpFieldFun_Header
