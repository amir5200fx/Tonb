#include <SectPx_UnaryOpFieldFun_Cos.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::unaryOpFieldFun::Cos<std::shared_ptr<tnbLib::SectPx_FieldFun>>::typeName_ = "cos unary op field func.";
const char* tnbLib::unaryOpFieldFun::Cos<std::weak_ptr<tnbLib::SectPx_FieldFun>>::typeName_ = "cos unary op field func.";

tnbLib::word
tnbLib::unaryOpFieldFun::Cos<std::shared_ptr<tnbLib::SectPx_FieldFun>>::RegObjTypeName() const
{
    return typeName_;
}

Standard_Real
tnbLib::unaryOpFieldFun::Cos<std::shared_ptr<tnbLib::SectPx_FieldFun>>::Value() const
{
    if (NOT FieldFun())
    {
        FatalErrorIn(FunctionSIG) << endl
            << "No field function has been detected." << endl
            << abort(FatalError);
    }
    return std::cos(FieldFun()->Value());
}

tnbLib::word
tnbLib::unaryOpFieldFun::Cos<std::weak_ptr<tnbLib::SectPx_FieldFun>>::RegObjTypeName() const
{
    return typeName_;
}

Standard_Real
tnbLib::unaryOpFieldFun::Cos<std::weak_ptr<tnbLib::SectPx_FieldFun>>::Value() const
{
    const auto field = FieldFun().lock();
    if (NOT field)
    {
        FatalErrorIn(FunctionSIG) << endl
            << "No field function has been detected." << endl
            << abort(FatalError);
    }
    return std::cos(field->Value());
}
