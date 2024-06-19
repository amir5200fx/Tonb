#include <SectPx_UnaryOpFieldFun_Tan.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::unaryOpFieldFun::Tan<std::shared_ptr<tnbLib::SectPx_FieldFun>>::typeName_ = "tan unary op field func.";
const char* tnbLib::unaryOpFieldFun::Tan<std::weak_ptr<tnbLib::SectPx_FieldFun>>::typeName_ = "tan unary op field func.";

tnbLib::word
tnbLib::unaryOpFieldFun::Tan<std::shared_ptr<tnbLib::SectPx_FieldFun>>::RegObjTypeName() const
{
    return typeName_;
}

Standard_Real
tnbLib::unaryOpFieldFun::Tan<std::shared_ptr<tnbLib::SectPx_FieldFun>>::Value() const
{
    if (NOT FieldFun())
    {
        FatalErrorIn(FunctionSIG) << endl
            << "No field function has been detected." << endl
            << abort(FatalError);
    }
    return std::tan(FieldFun()->Value());
}

tnbLib::word
tnbLib::unaryOpFieldFun::Tan<std::weak_ptr<tnbLib::SectPx_FieldFun>>::RegObjTypeName() const
{
    return typeName_;
}

Standard_Real
tnbLib::unaryOpFieldFun::Tan<std::weak_ptr<tnbLib::SectPx_FieldFun>>::Value() const
{
    const auto field = FieldFun().lock();
    if (NOT field)
    {
        FatalErrorIn(FunctionSIG) << endl
            << "No field function has been detected." << endl
            << abort(FatalError);
    }
    return std::tan(field->Value());
}
