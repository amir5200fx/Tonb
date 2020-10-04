#include <SectPx_BinaryOpFieldFun_Divide.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

#include <gp.hxx>

const char* tnbLib::binaryOpsFieldFun::Divide
<
	std::shared_ptr<tnbLib::SectPx_FieldFun>,
	std::shared_ptr<tnbLib::SectPx_FieldFun>
>::typeName_ = "divide binary op fieldFun";

const char* tnbLib::binaryOpsFieldFun::Divide
<
	std::weak_ptr<tnbLib::SectPx_FieldFun>,
	std::shared_ptr<tnbLib::SectPx_FieldFun>
>::typeName_ = "divide binary op fieldFun";

const char* tnbLib::binaryOpsFieldFun::Divide
<
	std::shared_ptr<tnbLib::SectPx_FieldFun>,
	std::weak_ptr<tnbLib::SectPx_FieldFun>
>::typeName_ = "divide binary op fieldFun";

const char* tnbLib::binaryOpsFieldFun::Divide
<
	std::weak_ptr<tnbLib::SectPx_FieldFun>,
	std::weak_ptr<tnbLib::SectPx_FieldFun>
>::typeName_ = "divide binary op fieldFun";


Standard_Real
tnbLib::binaryOpsFieldFun::Divide
<
	std::shared_ptr<tnbLib::SectPx_FieldFun>,
	std::shared_ptr<tnbLib::SectPx_FieldFun>
>::Value() const
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

Standard_Real
tnbLib::binaryOpsFieldFun::Divide
<
	std::weak_ptr<tnbLib::SectPx_FieldFun>,
	std::shared_ptr<tnbLib::SectPx_FieldFun>
>::Value() const
{
	if (NOT Left().lock())
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

	return Left().lock()->Value() / Right()->Value();
}

Standard_Real
tnbLib::binaryOpsFieldFun::Divide
<
	std::shared_ptr<tnbLib::SectPx_FieldFun>,
	std::weak_ptr<tnbLib::SectPx_FieldFun>
>::Value() const
{
	if (NOT Left())
	{
		FatalErrorIn(FunctionSIG)
			<< "the is no field function in  left side" << endl
			<< abort(FatalError);
	}

	if (NOT Right().lock())
	{
		FatalErrorIn(FunctionSIG)
			<< "there is no field function in right side" << endl
			<< abort(FatalError);
	}

	if (Right().lock()->Value() <= gp::Resolution())
	{
		FatalErrorIn(FunctionSIG)
			<< "divided by zero is encountered!" << endl
			<< abort(FatalError);
	}

	return Left()->Value() / Right().lock()->Value();
}

Standard_Real
tnbLib::binaryOpsFieldFun::Divide
<
	std::weak_ptr<tnbLib::SectPx_FieldFun>,
	std::weak_ptr<tnbLib::SectPx_FieldFun>
>::Value() const
{
	if (NOT Left().lock())
	{
		FatalErrorIn(FunctionSIG)
			<< "the is no field function in  left side" << endl
			<< abort(FatalError);
	}

	if (NOT Right().lock())
	{
		FatalErrorIn(FunctionSIG)
			<< "there is no field function in right side" << endl
			<< abort(FatalError);
	}

	if (Right().lock()->Value() <= gp::Resolution())
	{
		FatalErrorIn(FunctionSIG)
			<< "divided by zero is encountered!" << endl
			<< abort(FatalError);
	}

	return Left().lock()->Value() / Right().lock()->Value();
}