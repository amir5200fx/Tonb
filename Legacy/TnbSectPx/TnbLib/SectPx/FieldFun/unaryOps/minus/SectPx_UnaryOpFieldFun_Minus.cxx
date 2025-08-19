#include <SectPx_UnaryOpFieldFun_Minus.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::unaryOpFieldFun::Minus<std::shared_ptr<tnbLib::SectPx_FieldFun>>::typeName_ = "minus unary op fieldFun";
const char* tnbLib::unaryOpFieldFun::Minus<std::weak_ptr<tnbLib::SectPx_FieldFun>>::typeName_ = "minus unary op fieldFun";


Standard_Real
tnbLib::unaryOpFieldFun::Minus<std::shared_ptr<tnbLib::SectPx_FieldFun>>::Value() const
{
	if (NOT this->FieldFun())
	{
		FatalErrorIn(FunctionSIG)
			<< "there is no field" << endl
			<< abort(FatalError);
	}
	return -this->FieldFun()->Value();
}

Standard_Real
tnbLib::unaryOpFieldFun::Minus<std::weak_ptr<tnbLib::SectPx_FieldFun>>::Value() const
{
	if (NOT this->FieldFun().lock())
	{
		FatalErrorIn(FunctionSIG)
			<< "there is no field" << endl
			<< abort(FatalError);
	}
	return -this->FieldFun().lock()->Value();
}