#include <SectPx_BinaryOpFieldFun_Cross.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::binaryOpsFieldFun::Cross::typeName_ = "cross binary op fieldFun";

tnbLib::word 
tnbLib::binaryOpsFieldFun::Cross::RegObjTypeName() const
{
	return typeName_;
}

Standard_Real
tnbLib::binaryOpsFieldFun::Cross::Value() const
{
	if (NOT Left())
	{
		FatalErrorIn(FunctionSIG)
			<< "the is no field function in  left side" << endl
			<< abort(FatalError);
	}

	if (NOT Right())
	{
		FatalErrorIn(FunctionSIG)
			<< "there is no field function in right side" << endl
			<< abort(FatalError);
	}
	return Left()->Value() * Right()->Value();
}