#include <SectPx_BinaryOpFieldFun_Sum.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::binaryOpsFieldFun::Sum::typeName_ = "sum binary op fieldFun";

tnbLib::word 
tnbLib::binaryOpsFieldFun::Sum::RegObjTypeName() const
{
	return typeName_;
}

Standard_Real 
tnbLib::binaryOpsFieldFun::Sum::Value() const
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
	return Left()->Value() + Right()->Value();
}