#include <SectPx_BinaryOpFieldFun_Min.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::binaryOpsFieldFun::Min<std::shared_ptr<tnbLib::SectPx_FieldFun>, std::shared_ptr<
	                                           tnbLib::SectPx_FieldFun>>::typeName_ = "min. binary op fieldFun";
const char* tnbLib::binaryOpsFieldFun::Min<std::shared_ptr<tnbLib::SectPx_FieldFun>, std::weak_ptr<
	                                           tnbLib::SectPx_FieldFun>>::typeName_ = "min. binary op fieldFun";
const char* tnbLib::binaryOpsFieldFun::Min<std::weak_ptr<tnbLib::SectPx_FieldFun>, std::shared_ptr<
	                                           tnbLib::SectPx_FieldFun>>::typeName_ = "min. binary of fieldFun";
const char* tnbLib::binaryOpsFieldFun::Min<std::weak_ptr<tnbLib::SectPx_FieldFun>, std::weak_ptr<
	                                           tnbLib::SectPx_FieldFun>>::typeName_ = "min. binary of fieldFun";

tnbLib::word tnbLib::binaryOpsFieldFun::Min<std::shared_ptr<tnbLib::SectPx_FieldFun>, std::shared_ptr<tnbLib::
SectPx_FieldFun>>::RegObjTypeName() const
{
	return typeName_;
}

Standard_Real tnbLib::binaryOpsFieldFun::Min<std::shared_ptr<tnbLib::SectPx_FieldFun>, std::shared_ptr<tnbLib::
SectPx_FieldFun>>::Value() const
{
	if (NOT Left())
	{
		FatalErrorIn(FunctionSIG) << endl
			<< " there is no field function in the left side of the operator." << endl
			<< abort(FatalError);
	}
	if (NOT Right())
	{
		FatalErrorIn(FunctionSIG) << endl
			<< " there is no field function in the right side of the operator." << endl
			<< abort(FatalError);
	}
	return std::min(Left()->Value(), Right()->Value());
}

tnbLib::word tnbLib::binaryOpsFieldFun::Min<std::shared_ptr<tnbLib::SectPx_FieldFun>, std::weak_ptr<tnbLib::
SectPx_FieldFun>>::RegObjTypeName() const
{
	return typeName_;
}

Standard_Real tnbLib::binaryOpsFieldFun::Min<std::shared_ptr<tnbLib::SectPx_FieldFun>, std::weak_ptr<tnbLib::
SectPx_FieldFun>>::Value() const
{
	if (NOT Left())
	{
		FatalErrorIn(FunctionSIG) << endl
			<< " there is no field function in the left side of the operator." << endl
			<< abort(FatalError);
	}
	const auto right = Right().lock();
	if (NOT right)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< " there is no field function in the right side of the operator." << endl
			<< abort(FatalError);
	}
	return std::min(Left()->Value(), right->Value());
}

tnbLib::word tnbLib::binaryOpsFieldFun::Min<std::weak_ptr<tnbLib::SectPx_FieldFun>, std::shared_ptr<tnbLib::
SectPx_FieldFun>>::RegObjTypeName() const
{
	return typeName_;
}

Standard_Real tnbLib::binaryOpsFieldFun::Min<std::weak_ptr<tnbLib::SectPx_FieldFun>, std::shared_ptr<tnbLib::
SectPx_FieldFun>>::Value() const
{
	const auto left = Left().lock();
	if (NOT left)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< " there is no field function in the left side of the operator." << endl
			<< abort(FatalError);
	}
	if (NOT Right())
	{
		FatalErrorIn(FunctionSIG) << endl
			<< " there is no field function in the right side of the operator." << endl
			<< abort(FatalError);
	}
	return std::min(left->Value(), Right()->Value());
}

tnbLib::word tnbLib::binaryOpsFieldFun::Min<std::weak_ptr<tnbLib::SectPx_FieldFun>, std::weak_ptr<tnbLib::
SectPx_FieldFun>>::RegObjTypeName() const
{
	return typeName_;
}

Standard_Real tnbLib::binaryOpsFieldFun::Min<std::weak_ptr<tnbLib::SectPx_FieldFun>, std::weak_ptr<tnbLib::
SectPx_FieldFun>>::Value() const
{
	const auto left = Left().lock();
	if (NOT left)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< " there is no field function in the left side of the operator." << endl
			<< abort(FatalError);
	}
	const auto right = Right().lock();
	if (NOT right)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< " there is no field function in the right side of the operator." << endl
			<< abort(FatalError);
	}
	return std::min(left->Value(), right->Value());
}



