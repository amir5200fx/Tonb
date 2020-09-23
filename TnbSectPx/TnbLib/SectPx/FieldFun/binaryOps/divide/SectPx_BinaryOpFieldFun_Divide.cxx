#include <SectPx_BinaryOpFieldFun_Divide.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

#include <gp.hxx>

const char* tnbLib::binaryOpsFieldFun::Divide::typeName_ = "divide binary op fieldFun";

tnbLib::word 
tnbLib::binaryOpsFieldFun::Divide::RegObjTypeName() const
{
	return typeName_;
}

Standard_Real 
tnbLib::binaryOpsFieldFun::Divide::Value() const
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

	if (Right()->Value() <= gp::Resolution())
	{
		FatalErrorIn(FunctionSIG)
			<< "divided by zero is encountered!" << endl
			<< abort(FatalError);
	}

	return Left()->Value() / Right()->Value();
}