#include <SectPx_UnaryOpFieldFun_Sqrt.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::unaryOpFieldFun::Sqrt<std::shared_ptr<tnbLib::SectPx_FieldFun>>::typeName_ = "sqrt unary op field func.";
const char* tnbLib::unaryOpFieldFun::Sqrt<std::weak_ptr<tnbLib::SectPx_FieldFun>>::typeName_ = "sqrt unary op field func.";

tnbLib::word
tnbLib::unaryOpFieldFun::Sqrt<std::shared_ptr<tnbLib::SectPx_FieldFun>>::RegObjTypeName() const
{
    return typeName_;
}

Standard_Real
tnbLib::unaryOpFieldFun::Sqrt<std::shared_ptr<tnbLib::SectPx_FieldFun>>::Value() const
{
    if (NOT FieldFun())
    {
        FatalErrorIn(FunctionSIG) << endl
            << "No field function has been detected." << endl
            << abort(FatalError);
    }
    return std::sqrt(FieldFun()->Value());
}

tnbLib::word
tnbLib::unaryOpFieldFun::Sqrt<std::weak_ptr<tnbLib::SectPx_FieldFun>>::RegObjTypeName() const
{
    return typeName_;
}

Standard_Real
tnbLib::unaryOpFieldFun::Sqrt<std::weak_ptr<tnbLib::SectPx_FieldFun>>::Value() const
{
    const auto field = FieldFun().lock();
    if (NOT field)
    {
        FatalErrorIn(FunctionSIG) << endl
            << "No field function has been detected." << endl
            << abort(FatalError);
    }
    return std::sqrt(field->Value());
}
