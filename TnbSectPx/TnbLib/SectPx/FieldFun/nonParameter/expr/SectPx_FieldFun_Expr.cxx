#include <SectPx_FieldFun_Expr.hxx>

#include <SectPx_FieldFun.hxx>
#include <SectPx_Pars.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

const char* tnbLib::sectPxLib::FieldFun_Expr::typeName_ = "expr fieldFun";

#include <exprtk.hpp>

//typedef exprtk::symbol_table<double> symbol_table_double;
typedef exprtk::expression<Standard_Real>          expression_t;
typedef exprtk::parser<Standard_Real>                  parser_t;
typedef exprtk::parser_error::type            err_t;

void tnbLib::sectPxLib::FieldFun_Expr::AddParameter
(
	const word & name, 
	std::shared_ptr<Parameter>&& p
)
{
	auto paired = std::make_pair(name, std::move(p));
	auto insert = theParameters_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< " duplicate data! " << endl
			<< " - name: " << name << endl
			<< abort(FatalError);
	}
}

void tnbLib::sectPxLib::FieldFun_Expr::RemoveParameter(const word & name)
{
	auto iter = theParameters_.find(name);
	if (iter IS_EQUAL theParameters_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< " the item is not in the tree! " << endl
			<< " - name: " << name << endl
			<< abort(FatalError);
	}
	theParameters_.erase(iter);
}

tnbLib::sectPxLib::FieldFun_Expr::FieldFun_Expr
(
	const word & theExpr
)
	: theExpr_(theExpr)
{
}

tnbLib::sectPxLib::FieldFun_Expr::FieldFun_Expr
(
	const Standard_Integer theIndex, 
	const word & theExpr
)
	: SectPx_nonParFieldFun(theIndex)
	, theExpr_(theExpr)
{
}

tnbLib::sectPxLib::FieldFun_Expr::FieldFun_Expr
(
	const Standard_Integer theIndex, 
	const word & theName,
	const word & theExpr
)
	: SectPx_nonParFieldFun(theIndex, theName)
	, theExpr_(theExpr)
{
}

tnbLib::word 
tnbLib::sectPxLib::FieldFun_Expr::RegObjTypeName() const
{
	return typeName_;
}

Standard_Real 
tnbLib::sectPxLib::FieldFun_Expr::Value() const
{
	exprtk::symbol_table<Standard_Real> symbol_table;
	for (const auto& x : theParameters_)
	{
		Debug_Null_Pointer(x.second);
		const auto& ref = x.second;

		if (ref->IsConst())
		{
			auto cx = std::dynamic_pointer_cast<Constant>(ref);
			Debug_Null_Pointer(cx);

			symbol_table.add_constant(x.first, cx->X());
		}
		else
		{
			auto cx = std::dynamic_pointer_cast<Variable>(ref);
			Debug_Null_Pointer(cx);

			symbol_table.add_variable(x.first, cx->X());
		}
	}

	if (addConstants_)
		symbol_table.add_constants();

	expression_t expression;
	expression.register_symbol_table(symbol_table);

	parser_t parser;
	if (NOT parser.compile(theExpr_, expression))
	{
		FatalErrorIn(FunctionSIG)
			<< parser.error().c_str() 
			<< theExpr_ << endl
			<< abort(FatalError);
	}
	return expression.value();
}

void tnbLib::sectPxLib::FieldFun_Expr::AddVariable
(
	const word & name,
	Standard_Real & x
)
{
	auto p = std::make_shared<Variable>(x);
	AddParameter(name, std::move(p));
}

void tnbLib::sectPxLib::FieldFun_Expr::AddVariable
(
	const word & name, 
	SectPx_FieldFun & x
)
{
	auto p = std::make_shared<Variable>(x.xRef());
	AddParameter(name, std::move(p));
}

void tnbLib::sectPxLib::FieldFun_Expr::AddVariable
(
	const word & name, 
	SectPx_FixedPar & par
)
{
	auto p = std::make_shared<Variable>(par.X());
	AddParameter(name, std::move(p));
}

void tnbLib::sectPxLib::FieldFun_Expr::AddConstant
(
	const word & name,
	const Standard_Real & x
)
{
	auto p = std::make_shared<Constant>(x);
	AddParameter(name, std::move(p));
}

void tnbLib::sectPxLib::FieldFun_Expr::AddConstant
(
	const word & name,
	const SectPx_FieldFun & x
)
{
	auto p = std::make_shared<Constant>(x.xRef());
	AddParameter(name, std::move(p));
}

void tnbLib::sectPxLib::FieldFun_Expr::AddConstant
(
	const word & name, 
	const SectPx_ConstPar & par
)
{
	auto p = std::make_shared<Constant>(par.X());
	AddParameter(name, std::move(p));
}

void tnbLib::sectPxLib::FieldFun_Expr::RemoveVariable
(
	const word & name,
	const Standard_Boolean remove_node
)
{
	RemoveParameter(name);
}

void tnbLib::sectPxLib::FieldFun_Expr::SetAddConstants
(
	const Standard_Boolean addConstants
)
{
	addConstants_ = addConstants;
}