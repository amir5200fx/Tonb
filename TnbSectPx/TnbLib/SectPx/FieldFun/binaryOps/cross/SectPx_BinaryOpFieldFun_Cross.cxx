#include <SectPx_BinaryOpFieldFun_Cross.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::binaryOpsFieldFun::Cross
<
	std::shared_ptr<tnbLib::SectPx_FieldFun>,
	std::shared_ptr<tnbLib::SectPx_FieldFun>
>::typeName_ = "cross binary op fieldFun";

const char* tnbLib::binaryOpsFieldFun::Cross
<
	std::weak_ptr<tnbLib::SectPx_FieldFun>,
	std::shared_ptr<tnbLib::SectPx_FieldFun>
>::typeName_ = "cross binary op fieldFun";

const char* tnbLib::binaryOpsFieldFun::Cross
<
	std::shared_ptr<tnbLib::SectPx_FieldFun>,
	std::weak_ptr<tnbLib::SectPx_FieldFun>
>::typeName_ = "cross binary op fieldFun";

const char* tnbLib::binaryOpsFieldFun::Cross
<
	std::weak_ptr<tnbLib::SectPx_FieldFun>,
	std::weak_ptr<tnbLib::SectPx_FieldFun>
>::typeName_ = "cross binary op fieldFun";


Standard_Real
tnbLib::binaryOpsFieldFun::Cross
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
	return Left()->Value() * Right()->Value();
}

Standard_Real
tnbLib::binaryOpsFieldFun::Cross
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
	return Left().lock()->Value() * Right()->Value();
}

Standard_Real
tnbLib::binaryOpsFieldFun::Cross
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
	return Left()->Value() * Right().lock()->Value();
}

Standard_Real
tnbLib::binaryOpsFieldFun::Cross
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
	return Left().lock()->Value() * Right().lock()->Value();
}