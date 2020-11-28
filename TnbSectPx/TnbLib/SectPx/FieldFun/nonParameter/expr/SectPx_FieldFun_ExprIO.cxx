#include <SectPx_FieldFun_Expr.hxx>

#include <SectPx_FieldFun.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::sectPxLib::FieldFun_Expr)
{
	ar & boost::serialization::base_object<SectPx_nonParFieldFun>(*this);
	ar & theParameters_;
	ar & theExpr_;
	ar & addConstants_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::sectPxLib::FieldFun_Expr)
{
	ar & boost::serialization::base_object<SectPx_nonParFieldFun>(*this);
	ar & theParameters_;
	ar & theExpr_;
	ar & addConstants_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::sectPxLib::FieldFun_Expr);