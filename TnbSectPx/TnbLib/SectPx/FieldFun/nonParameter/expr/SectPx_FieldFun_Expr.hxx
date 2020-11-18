#pragma once
#ifndef _SectPx_FieldFun_Expr_Header
#define _SectPx_FieldFun_Expr_Header

#include <SectPx_nonParFieldFun.hxx>
#include <SectPx_ParsFwd.hxx>

#include <map>

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

		public:


			/*Private Data*/

			std::map<word, std::weak_ptr<SectPx_FieldFun>> theParameters_;

			std::string theExpr_;

			Standard_Boolean addConstants_;


			DECLARE_SAVE_LOAD_HEADER(TnbSectPx_EXPORT);

			TnbSectPx_EXPORT void AddParameter(const word&, const std::weak_ptr<SectPx_FieldFun>& p);

			TnbSectPx_EXPORT void RemoveParameter(const word&);


		protected:

			FieldFun_Expr()
			{}

		public:

			static TnbSectPx_EXPORT const char* typeName_;

			TnbSectPx_EXPORT FieldFun_Expr
			(
				const word& theExpr
			);

			TnbSectPx_EXPORT FieldFun_Expr
			(
				const Standard_Integer theIndex,
				const word& theExpr
			);

			TnbSectPx_EXPORT FieldFun_Expr
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

			TnbSectPx_EXPORT word RegObjTypeName() const override;

			TnbSectPx_EXPORT Standard_Real Value() const override;

			TnbSectPx_EXPORT void AddVariable
			(
				const word& name, const std::shared_ptr<SectPx_FieldFun>& x
			);

			TnbSectPx_EXPORT void RemoveVariable
			(
				const word& name,
				const Standard_Boolean delete_node = Standard_True
			);

			TnbSectPx_EXPORT void SetAddConstants
			(
				const Standard_Boolean addConstants
			);
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::sectPxLib::FieldFun_Expr);

#endif // !_SectPx_FieldFun_Expr_Header
