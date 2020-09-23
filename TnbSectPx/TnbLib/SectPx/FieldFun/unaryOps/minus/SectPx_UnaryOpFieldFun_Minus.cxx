#include <SectPx_UnaryOpFieldFun_Minus.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::unaryOpFieldFun::Minus::typeName_ = "minus unary op fieldFun";

tnbLib::word
tnbLib::unaryOpFieldFun::Minus::RegObjTypeName() const
{
	return typeName_;
}

Standard_Real
tnbLib::unaryOpFieldFun::Minus::Value() const
{
	if (NOT FieldFun())
	{
		FatalErrorIn(FunctionSIG)
			<< "there is no field" << endl
			<< abort(FatalError);
	}
	return -FieldFun()->Value();
}