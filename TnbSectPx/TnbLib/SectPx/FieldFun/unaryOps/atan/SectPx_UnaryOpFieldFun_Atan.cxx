#include <SectPx_UnaryOpFieldFun_Atan.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::unaryOpFieldFun::Atan<std::shared_ptr<tnbLib::SectPx_FieldFun>>::typeName_ = "atan unary op field func.";
const char* tnbLib::unaryOpFieldFun::Atan<std::weak_ptr<tnbLib::SectPx_FieldFun>>::typeName_ = "atan unary op field func.";

tnbLib::word
tnbLib::unaryOpFieldFun::Atan<std::shared_ptr<tnbLib::SectPx_FieldFun>>::RegObjTypeName() const
{
    return typeName_;
}

Standard_Real
tnbLib::unaryOpFieldFun::Atan<std::shared_ptr<tnbLib::SectPx_FieldFun>>::Value() const
{
    if (NOT FieldFun())
    {
        FatalErrorIn(FunctionSIG) << endl
            << "No field function has been detected." << endl
            << abort(FatalError);
    }
    return std::atan(FieldFun()->Value());
}

tnbLib::word
tnbLib::unaryOpFieldFun::Atan<std::weak_ptr<tnbLib::SectPx_FieldFun>>::RegObjTypeName() const
{
    return typeName_;
}

Standard_Real
tnbLib::unaryOpFieldFun::Atan<std::weak_ptr<tnbLib::SectPx_FieldFun>>::Value() const
{
    const auto field = FieldFun().lock();
    if (NOT field)
    {
        FatalErrorIn(FunctionSIG) << endl
            << "No field function has been detected." << endl
            << abort(FatalError);
    }
    return std::atan(field->Value());
}
