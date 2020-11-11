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

			class Parameter
			{

				friend class boost::serialization::access;
				template<class Archive>
				void serialize(Archive& ar, const unsigned int version)
				{}

			protected:

				Parameter()
				{}

			public:

				virtual Standard_Boolean IsConst() const
				{
					return Standard_False;
				}

				virtual Standard_Boolean IsVariable() const
				{
					return Standard_False;
				}

			};

			class Constant
				: public Parameter
			{

				friend boost::serialization::access;
				template<class Archive>
				void serialize(Archive &ar, const unsigned int file_version)
				{
					ar & boost::serialization::base_object<Parameter>(*this);
					ar & static_cast<Standard_Real&>(theX_);
				}

				/*Private Data*/

				const Standard_Real & theX_;

				static const Standard_Real null;

				Constant()
					: theX_(null)
				{}

				void SetX(const Standard_Real& x)
				{
					const_cast<Standard_Real&>(theX_) = x;
				}

			public:

				Constant(const Standard_Real & x)
					: theX_(x)
				{}

				Standard_Boolean IsConst() const override
				{
					return Standard_True;
				}

				const Standard_Real & X() const
				{
					return theX_;
				}
			};

			class Variable
				: public Parameter
			{

				friend boost::serialization::access;
				template<class Archive>
				void serialize(Archive &ar, const unsigned int file_version)
				{
					ar & boost::serialization::base_object<Parameter>(*this);
					ar & theX_;
				}

				/*Private Data*/

				Standard_Real & theX_;

				static Standard_Real null;

				Variable()
					: theX_(null)
				{}

				void SetX(Standard_Real & x)
				{
					theX_ = x;
				}

			public:

				Variable(Standard_Real& x)
					: theX_(x)
				{}

				Standard_Boolean IsVariable() const override
				{
					return Standard_True;
				}

				Standard_Real & X()
				{
					return theX_;
				}
			};

			friend boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int file_version)
			{
				ar & boost::serialization::base_object<SectPx_nonParFieldFun>(*this);
				ar & theParameters_;
				ar & theExpr_;
				ar & addConstants_;
			}

			/*Private Data*/

			std::map<word, std::shared_ptr<Parameter>> theParameters_;


			void AddParameter(const word&, std::shared_ptr<Parameter>&& p);

			void RemoveParameter(const word&);

			std::string theExpr_;

			Standard_Boolean addConstants_;


		protected:

			FieldFun_Expr()
			{}

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

			void AddVariable
			(
				const word& name,
				Standard_Real& x
			);

			void AddVariable
			(
				const word& name, SectPx_FieldFun& x
			);

			void AddVariable
			(
				const word& name,
				SectPx_FixedPar& par
			);

			void AddConstant
			(
				const word& name,
				const Standard_Real& x
			);

			void AddConstant
			(
				const word& name,
				const SectPx_FieldFun& x
			);

			void AddConstant
			(
				const word& name,
				const SectPx_ConstPar& par
			);

			void RemoveVariable
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

BOOST_CLASS_EXPORT_KEY(tnbLib::sectPxLib::FieldFun_Expr);

#endif // !_SectPx_FieldFun_Expr_Header
