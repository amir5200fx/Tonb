#include <SectPx_FreePar.hxx>

#include <SectPx_Parent.hxx>
#include <SectPx_ParTools.hxx>
#include <SectPx_FieldFun.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::SectPx_FreePar::typeName_ = "free_parameter";

tnbLib::SectPx_FreePar::SectPx_FreePar
(
	const std::shared_ptr<SectPx_FieldFun>& theFun
)
	: theFun_(theFun)
{
	//- empty body
}

tnbLib::SectPx_FreePar::SectPx_FreePar
(
	std::shared_ptr<SectPx_FieldFun>&& theFun
)
	: theFun_(std::move(theFun))
{
	//- empty body
}

tnbLib::SectPx_FreePar::SectPx_FreePar
(
	const Standard_Integer theIndex,
	const std::shared_ptr<SectPx_FieldFun>& theFun
)
	: SectPx_Par(theIndex)
	, theFun_(theFun)
{
	//- empty body
}

tnbLib::SectPx_FreePar::SectPx_FreePar
(
	const Standard_Integer theIndex, 
	const word & theName,
	const std::shared_ptr<SectPx_FieldFun>& theFun
)
	: SectPx_Par(theIndex, theName)
	, theFun_(theFun)
{
	//- empty body
}

Standard_Boolean 
tnbLib::SectPx_FreePar::HasFieldFun() const
{
	return (Standard_Boolean)FieldFun();
}

tnbLib::word 
tnbLib::SectPx_FreePar::RegObjTypeName() const
{
	return typeName_;
}

typename tnbLib::sectPxLib::parType 
tnbLib::SectPx_FreePar::ParType() const
{
	return sectPxLib::parType::free;
}

Standard_Boolean 
tnbLib::SectPx_FreePar::IsFree() const
{
	return Standard_True;
}

Standard_Boolean 
tnbLib::SectPx_FreePar::IsComplete() const
{
	return HasFieldFun();
}

Standard_Boolean 
tnbLib::SectPx_FreePar::InCycle() const
{
	const auto par = std::dynamic_pointer_cast<SectPx_Par>(This());
	auto parents =
		SectPx_ParTools::RetrieveParents
		(
			par
		);
	for (const auto& x : parents)
	{
		Debug_Null_Pointer(x);
		if (x->HasChild(par))
		{
			return Standard_True;
		}
	}
	return Standard_False;
}

Standard_Real 
tnbLib::SectPx_FreePar::Value() const
{
	const auto& field = FieldFun();
	if (NOT field)
	{
		FatalErrorIn
		(
			"Standard_Real Value() const override"
		)
			<< "no field fun has been assigned to the free parameter!" << endl
			<< abort(FatalError);
	}

	return field->Value();
}