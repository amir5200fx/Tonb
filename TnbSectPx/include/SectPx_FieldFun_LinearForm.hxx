#pragma once
#ifndef _SectPx_FieldFun_LinearForm_Header
#define _SectPx_FieldFun_LinearForm_Header

#include <SectPx_oneParFieldFun.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_FieldFun;

	namespace sectPxLib
	{

		class FieldFun_LinearForm
			: public SectPx_oneParFieldFun
		{

			/*Private Data*/

			std::shared_ptr<SectPx_FieldFun> theF0_;
			std::shared_ptr<SectPx_FieldFun> theF1_;

		public:

			static const char* typeName_;

			template<class... _Types>
			FieldFun_LinearForm(_Types&&... _Args)
				: SectPx_oneParFieldFun(_Args...)
			{}


			const auto& F0() const
			{
				return theF0_;
			}

			const auto& F1() const
			{
				return theF1_;
			}

			word RegObjTypeName() const override;

			Standard_Real Value() const override;

			void SetF0
			(
				const std::shared_ptr<SectPx_FieldFun>& theF0
			)
			{
				theF0_ = theF0;
			}

			void SetF0
			(
				std::shared_ptr<SectPx_FieldFun>&& theF0
			)
			{
				theF0_ = std::move(theF0);
			}

			void SetF1
			(
				const std::shared_ptr<SectPx_FieldFun>& theF1
			)
			{
				theF1_ = theF1;
			}

			void SetF1
			(
				std::shared_ptr<SectPx_FieldFun>&& theF1
			)
			{
				theF1_ = std::move(theF1);
			}
		};
	}
}

#endif // !_SectPx_FieldFun_LinearForm_Header
