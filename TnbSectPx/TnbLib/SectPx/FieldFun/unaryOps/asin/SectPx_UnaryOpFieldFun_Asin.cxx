#include <SectPx_UnaryOpFieldFun_Asin.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::unaryOpFieldFun::Asin<std::shared_ptr<tnbLib::SectPx_FieldFun>>::typeName_ = "asin unary op field func.";
const char* tnbLib::unaryOpFieldFun::Asin<std::weak_ptr<tnbLib::SectPx_FieldFun>>::typeName_ = "asin unary op field func.";

tnbLib::word
tnbLib::unaryOpFieldFun::Asin<std::shared_ptr<tnbLib::SectPx_FieldFun>>::RegObjTypeName() const
{
    return typeName_;
}

Standard_Real
tnbLib::unaryOpFieldFun::Asin<std::shared_ptr<tnbLib::SectPx_FieldFun>>::Value() const
{
    if (NOT FieldFun())
    {
        FatalErrorIn(FunctionSIG) << endl
            << "No field function has been detected." << endl
            << abort(FatalError);
    }
    return std::asin(FieldFun()->Value());
}

tnbLib::word
tnbLib::unaryOpFieldFun::Asin<std::weak_ptr<tnbLib::SectPx_FieldFun>>::RegObjTypeName() const
{
    return typeName_;
}

Standard_Real
tnbLib::unaryOpFieldFun::Asin<std::weak_ptr<tnbLib::SectPx_FieldFun>>::Value() const
{
    const auto field = FieldFun().lock();
    if (NOT field)
    {
        FatalErrorIn(FunctionSIG) << endl
            << "No field function has been detected." << endl
            << abort(FatalError);
    }
    return std::asin(field->Value());
}
