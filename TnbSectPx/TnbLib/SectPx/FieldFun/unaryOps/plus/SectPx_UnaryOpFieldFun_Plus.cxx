#include <SectPx_UnaryOpFieldFun_Plus.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::unaryOpFieldFun::Plus<std::shared_ptr<tnbLib::SectPx_FieldFun>>::typeName_ = "plus unary op fieldFun";
const char* tnbLib::unaryOpFieldFun::Plus<std::weak_ptr<tnbLib::SectPx_FieldFun>>::typeName_ = "plus unary op fieldFun";

Standard_Real
tnbLib::unaryOpFieldFun::Plus<std::shared_ptr<tnbLib::SectPx_FieldFun>>::Value() const
{
	if (NOT this->FieldFun())
	{
		FatalErrorIn(FunctionSIG)
			<< "there is no field" << endl
			<< abort(FatalError);
	}
	return this->FieldFun()->Value();
}

Standard_Real
tnbLib::unaryOpFieldFun::Plus<std::weak_ptr<tnbLib::SectPx_FieldFun>>::Value() const
{
	if (NOT this->FieldFun().lock())
	{
		FatalErrorIn(FunctionSIG)
			<< "there is no field" << endl
			<< abort(FatalError);
	}
	return this->FieldFun().lock()->Value();
}