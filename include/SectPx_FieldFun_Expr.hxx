#pragma once
#ifndef _SectPx_FieldFun_Expr_Header
#define _SectPx_FieldFun_Expr_Header

#include <SectPx_nonParFieldFun.hxx>

#include <map>

namespace exprtk
{
	// Forward Declarations

	template <typename T>
	class symbol_table;
}

namespace tnbLib
{

	namespace sectPxLib
	{

		class FieldFun_Expr
			: public SectPx_nonParFieldFun
		{

			/*Private Data*/

			string theExpr_;

			std::map<word, double&> theVariables_;
			std::map<word, const double&> theConstants_;

			std::shared_ptr<exprtk::symbol_table<double>> symbol_table_ptr;

			Standard_Boolean addConstants_;


			void AllocateMemory();

		public:

			static const char* typeName_;

			FieldFun_Expr
			(
				const word& theExpr
			);

			FieldFun_Expr
			(
				const Standard_Integer theIndex,
				const word& theExpr
			);

			FieldFun_Expr
			(
				const Standard_Integer theIndex, 
				const word& theName,
				const word& theExpr
			);
		

			const auto& Expression() const
			{
				return theExpr_;
			}

			word RegObjTypeName() const override;

			Standard_Real Value() const override;

			Standard_Boolean AddVariable(const word& name, double& x);

			Standard_Boolean AddConstant(const word& name, const double& x);

			void SetAddConstants
			(
				const Standard_Boolean addConstants
			);
		};
	}
}

#endif // !_SectPx_FieldFun_Expr_Header
