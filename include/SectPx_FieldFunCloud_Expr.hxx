//#pragma once
//#ifndef _SectPx_FieldFunCloud_Expr_Header
//#define _SectPx_FieldFunCloud_Expr_Header
//
//#include <SectPx_nonParFieldFunCloud.hxx>
//#include <SectPx_ParCloudsFwd.hxx>
//
//#include <map>
//
//namespace exprtk
//{
//	// Forward Declarations
//
//	template <typename T>
//	class symbol_table;
//}
//
//namespace tnbLib
//{
//
//	// Forward Declarations
//	class SectPx_FieldFunCloud;
//
//	namespace sectPxLib
//	{
//
//		class FieldFunCloud_Expr
//			: public SectPx_nonParFieldFunCloud
//		{
//
//			/*Private Data*/
//
//			string theExpr_;
//
//			/*std::map<word, Standard_Real&> theVariables_;
//			std::map<word, const Standard_Real&> theConstants_;*/
//
//			std::shared_ptr<exprtk::symbol_table<std::vector<Standard_Real>>> symbol_table_ptr;
//
//			Standard_Boolean addConstants_;
//
//
//			void AllocateMemory();
//
//		public:
//
//			static const char* typeName_;
//
//			FieldFunCloud_Expr
//			(
//				const word& theExpr
//			);
//
//			FieldFunCloud_Expr
//			(
//				const Standard_Integer theIndex,
//				const word& theExpr
//			);
//
//			FieldFunCloud_Expr
//			(
//				const Standard_Integer theIndex,
//				const word& theName,
//				const word& theExpr
//			);
//
//
//			const auto& Expression() const
//			{
//				return theExpr_;
//			}
//
//			word RegObjTypeName() const override;
//
//			std::vector<Standard_Real> Value() const override;
//
//			Standard_Boolean
//				AddVariable
//				(
//					const word& name,
//					std::vector<Standard_Real>& x
//				);
//
//			Standard_Boolean
//				AddVariable
//				(
//					const word& name, SectPx_FieldFunCloud& x
//				);
//
//			Standard_Boolean
//				AddVariable
//				(
//					const word& name,
//					SectPx_FixedParCloud& par
//				);
//
//			Standard_Boolean
//				AddConstant
//				(
//					const word& name,
//					const std::vector<Standard_Real>& x
//				);
//
//			Standard_Boolean
//				AddConstant
//				(
//					const word& name,
//					const SectPx_FieldFunCloud& x
//				);
//
//			Standard_Boolean
//				AddConstant
//				(
//					const word& name,
//					const SectPx_ConstParCloud& par
//				);
//
//			Standard_Boolean
//				RemoveVariable
//				(
//					const word& name,
//					const Standard_Boolean delete_node = Standard_True
//				);
//
//			void SetAddConstants
//			(
//				const Standard_Boolean addConstants
//			);
//
//		};
//	}
//}
//
//#endif // !_SectPx_FieldFunCloud_Expr_Header
