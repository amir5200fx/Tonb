#include <SectPx_FieldFun_Expr.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

const char* tnbLib::sectPxLib::FieldFun_Expr::typeName_ = "expr fieldFun";

#include <exprtk.hpp>

//typedef exprtk::symbol_table<double> symbol_table_double;
typedef exprtk::expression<double>          expression_t;
typedef exprtk::parser<double>                  parser_t;
typedef exprtk::parser_error::type            err_t;

void tnbLib::sectPxLib::FieldFun_Expr::AllocateMemory()
{
	symbol_table_ptr = std::make_shared<exprtk::symbol_table<double>>();
}

tnbLib::sectPxLib::FieldFun_Expr::FieldFun_Expr
(
	const word & theExpr
)
	: theExpr_(theExpr)
{
	AllocateMemory();
}

tnbLib::sectPxLib::FieldFun_Expr::FieldFun_Expr
(
	const Standard_Integer theIndex, 
	const word & theExpr
)
	: SectPx_nonParFieldFun(theIndex)
	, theExpr_(theExpr)
{
	AllocateMemory();
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
	AllocateMemory();
}

tnbLib::word 
tnbLib::sectPxLib::FieldFun_Expr::RegObjTypeName() const
{
	return typeName_;
}

Standard_Real 
tnbLib::sectPxLib::FieldFun_Expr::Value() const
{
	Debug_Null_Pointer(symbol_table_ptr);

	if (addConstants_)
		symbol_table_ptr->add_constants();

	expression_t expression;
	expression.register_symbol_table(*symbol_table_ptr);

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

Standard_Boolean 
tnbLib::sectPxLib::FieldFun_Expr::AddVariable
(
	const word & name,
	double & x
)
{
	Debug_Null_Pointer(symbol_table_ptr);
	return symbol_table_ptr->add_variable(name, x);
}

Standard_Boolean 
tnbLib::sectPxLib::FieldFun_Expr::AddConstant
(
	const word & name,
	const double & x
)
{
	Debug_Null_Pointer(symbol_table_ptr);
	return symbol_table_ptr->add_constant(name, x);
}

void tnbLib::sectPxLib::FieldFun_Expr::SetAddConstants
(
	const Standard_Boolean addConstants
)
{
	addConstants_ = addConstants;
}