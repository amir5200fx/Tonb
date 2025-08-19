//#include <SectPx_FieldCloud.hxx>
//
//#include <SectPx_FieldFun.hxx>
//#include <SectPx_Pars.hxx>
//#include <TnbError.hxx>
//#include <OSstream.hxx>
//
//#ifdef DebugInfo
//#undef DebugInfo
//#endif // DebugInfo
//
//#include <exprtk.hpp>
//
////typedef exprtk::symbol_table<double> symbol_table_double;
//typedef exprtk::expression<Standard_Real>          expression_t;
//typedef exprtk::parser<Standard_Real>                  parser_t;
//typedef exprtk::parser_error::type            err_t;
//
//void tnbLib::SectPx_FieldCloud::AllocateMemory()
//{
//	symbol_table_ptr = std::make_shared<exprtk::symbol_table<Standard_Real>>();
//}
//
//tnbLib::SectPx_FieldCloud::SectPx_FieldCloud
//(
//	const word & theExpr
//)
//	: theExpr_(theExpr)
//{
//	AllocateMemory();
//}
//
//tnbLib::SectPx_FieldCloud::SectPx_FieldCloud
//(
//	const Standard_Integer theIndex,
//	const word & theExpr
//)
//	: SectPx_Cloud(theIndex)
//	, theExpr_(theExpr)
//{
//	AllocateMemory();
//}
//
//tnbLib::SectPx_FieldCloud::SectPx_FieldCloud
//(
//	const Standard_Integer theIndex,
//	const word & theName, 
//	const word & theExpr
//)
//	: SectPx_Cloud(theIndex)
//	, theExpr_(theExpr)
//{
//	AllocateMemory();
//}

//std::vector<tnbLib::Pnt2d> 
//tnbLib::SectPx_FieldCloud::GetCoords() const
//{
//	return std::vector<Pnt2d>();
//}