#include <SectPx_FieldFun_Minus.hxx>

#include <SectPx_Par.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::sectPxLib::FieldFun_Minus::typeName_ = "minus fieldFun";

tnbLib::word 
tnbLib::sectPxLib::FieldFun_Minus::RegObjTypeName() const
{
	return typeName_;
}

Standard_Real 
tnbLib::sectPxLib::FieldFun_Minus::Value() const
{
	Debug_Null_Pointer(Par().lock());
	const auto par = Par().lock();
	if (NOT par->IsComplete())
	{
		FatalErrorIn("Standard_Real Value() const")
			<< "the parameter is not complete!" << endl
			<< abort(FatalError);
	}
	return -par->Value();
}