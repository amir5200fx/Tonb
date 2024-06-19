#include <SectPx_UnaryOpFieldFun_Abs.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::unaryOpFieldFun::Abs<std::shared_ptr<tnbLib::SectPx_FieldFun>>::typeName_ = "abs unary op field func.";
const char* tnbLib::unaryOpFieldFun::Abs<std::weak_ptr<tnbLib::SectPx_FieldFun>>::typeName_ = "abs unary of field func.";

tnbLib::word
tnbLib::unaryOpFieldFun::Abs<std::shared_ptr<tnbLib::SectPx_FieldFun>>::RegObjTypeName() const
{
	return typeName_;
}

Standard_Real
tnbLib::unaryOpFieldFun::Abs<std::shared_ptr<tnbLib::SectPx_FieldFun>>::Value() const
{
	if (NOT FieldFun())
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "No field function has been detected." << endl
			<< abort(FatalError);
	}
	return std::abs(FieldFun()->Value());
}

tnbLib::word
tnbLib::unaryOpFieldFun::Abs<std::weak_ptr<tnbLib::SectPx_FieldFun>>::RegObjTypeName() const
{
	return typeName_;
}

Standard_Real
tnbLib::unaryOpFieldFun::Abs<std::weak_ptr<tnbLib::SectPx_FieldFun>>::Value() const
{
	const auto field = FieldFun().lock();
	if (NOT field)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "No field function has been detected." << endl
			<< abort(FatalError);
	}
	return std::abs(field->Value());
}

