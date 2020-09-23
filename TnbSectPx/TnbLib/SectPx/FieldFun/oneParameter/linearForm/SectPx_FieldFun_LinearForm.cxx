#include <SectPx_FieldFun_LinearForm.hxx>

#include <SectPx_Par.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::sectPxLib::FieldFun_LinearForm::typeName_ = "fieldFun_linearForm";

tnbLib::word 
tnbLib::sectPxLib::FieldFun_LinearForm::RegObjTypeName() const
{
	return typeName_;
}

Standard_Real 
tnbLib::sectPxLib::FieldFun_LinearForm::Value() const
{
	Debug_Null_Pointer(Par().lock());
	const auto par = Par().lock();
	if (NOT par->IsComplete())
	{
		FatalErrorIn("Standard_Real Value() const")
			<< "the parameter is not complete!" << endl
			<< abort(FatalError);
	}

	const auto t = par->Value();

	Debug_Null_Pointer(F0());
	Debug_Null_Pointer(F1());

	const auto f0 = F0()->Value();
	const auto f1 = F1()->Value();

	return f0 + (f1 - f0)*t;
}