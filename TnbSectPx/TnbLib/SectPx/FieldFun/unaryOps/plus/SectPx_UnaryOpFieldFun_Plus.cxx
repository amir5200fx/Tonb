#include <SectPx_UnaryOpFieldFun_Plus.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::unaryOpFieldFun::Plus::typeName_ = "plus unary op fieldFun";

tnbLib::word 
tnbLib::unaryOpFieldFun::Plus::RegObjTypeName() const
{
	return typeName_;
}

Standard_Real
tnbLib::unaryOpFieldFun::Plus::Value() const
{
	if (NOT FieldFun())
	{
		FatalErrorIn(FunctionSIG)
			<< "there is no field" << endl
			<< abort(FatalError);
	}
	return FieldFun()->Value();
}