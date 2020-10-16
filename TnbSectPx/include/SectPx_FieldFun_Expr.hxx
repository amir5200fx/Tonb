#pragma once
#ifndef _SectPx_FieldFun_Expr_Header
#define _SectPx_FieldFun_Expr_Header

#include <SectPx_nonParFieldFun.hxx>
#include <SectPx_ParsFwd.hxx>

namespace exprtk
{
	// Forward Declarations

	template <typename T>
	class symbol_table;
}

namespace tnbLib
{

	// Forward Declarations
	class SectPx_FieldFun;

	namespace sectPxLib
	{

		class FieldFun_Expr
			: public SectPx_nonParFieldFun
		{

			/*Private Data*/

			string theExpr_;

			std::shared_ptr<exprtk::symbol_table<Standard_Real>> symbol_table_ptr;

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

			auto& ExpressionRef()
			{
				return theExpr_;
			}

			word RegObjTypeName() const override;

			Standard_Real Value() const override;

			Standard_Boolean 
				AddVariable
				(
					const word& name,
					Standard_Real& x
				);

			Standard_Boolean 
				AddVariable
				(
					const word& name, SectPx_FieldFun& x
				);

			Standard_Boolean 
				AddVariable
				(
					const word& name,
					SectPx_FixedPar& par
				);

			Standard_Boolean 
				AddConstant
				(
					const word& name, 
					const Standard_Real& x
				);

			Standard_Boolean 
				AddConstant
				(
					const word& name,
					const SectPx_FieldFun& x
				);

			Standard_Boolean 
				AddConstant
				(
					const word& name,
					const SectPx_ConstPar& par
				);

			Standard_Boolean 
				RemoveVariable
				(
					const word& name,
					const Standard_Boolean delete_node = Standard_True
				);

			void SetAddConstants
			(
				const Standard_Boolean addConstants
			);
		};
	}
}

#endif // !_SectPx_FieldFun_Expr_Header
