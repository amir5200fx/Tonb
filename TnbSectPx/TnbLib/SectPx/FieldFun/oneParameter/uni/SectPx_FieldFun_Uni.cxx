#include <SectPx_FieldFun_Uni.hxx>

#include <SectPx_Par.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::sectPxLib::FieldFun_Uni::typeName_ = "fieldFun_uni";

Standard_Real 
tnbLib::sectPxLib::FieldFun_Uni::Value() const
{
	Debug_Null_Pointer(Par().lock());
	const auto par = Par().lock();
	if (NOT par->IsComplete())
	{
		FatalErrorIn("Standard_Real Value() const")
			<< "the parameter is not complete!" << endl
			<< abort(FatalError);
	}
	return par->Value();
}

tnbLib::word 
tnbLib::sectPxLib::FieldFun_Uni::RegObjTypeName() const
{
	return typeName_;
}