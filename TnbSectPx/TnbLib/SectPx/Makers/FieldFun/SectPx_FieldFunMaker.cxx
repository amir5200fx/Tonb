#include <SectPx_FieldFunMaker.hxx>

#include <SectPx_Registry.hxx>
#include <SectPx_FieldFuns.hxx>
#include <SectPx_FieldFunTools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::shared_ptr<tnbLib::SectPx_FieldFun> 
tnbLib::maker::FieldFun::SelectFieldFun
(
	const Standard_Integer theIndex
) const
{
	Debug_Null_Pointer(Registry());
	const auto& registry = *Registry();

	auto item = registry.SelectObj(theIndex);
	Debug_Null_Pointer(item);

	auto field = std::dynamic_pointer_cast<SectPx_FieldFun>(item);
	if (NOT field)
	{
		FatalErrorIn(FunctionSIG)
			<< "the selected item is not a field function!" << endl
			<< "- index = " << theIndex << endl
			<< "- type = " << item->RegObjTypeName() << endl
			<< abort(FatalError);
	}
	return std::move(field);
}

std::shared_ptr<tnbLib::SectPx_FieldFun>
tnbLib::maker::FieldFun::RemoveFieldFun
(
	const Standard_Integer theIndex
) const
{
	auto field = SelectFieldFun(theIndex);
	Debug_Null_Pointer(field);

	if (NOT SectPx_FieldFunTools::IsRemovable(field))
	{
		FatalErrorIn(FunctionSIG)
			<< "the field is not allowed to remove form the registry!" << endl
			<< abort(FatalError);
	}
	Registry()->Remove(field);
	return std::move(field);
}

Standard_Integer
tnbLib::maker::FieldFun::CreateUniform
(
	const std::shared_ptr<SectPx_Par>& thePar
) const
{
	auto field = std::make_shared<sectPxLib::FieldFun_Uni>();
	Debug_Null_Pointer(field);

	field->SetPar(thePar);
	field->IsRegistered() = Standard_True;

	Debug_Null_Pointer(Registry());
	return Registry()->Import(std::move(field));
}

Standard_Integer 
tnbLib::maker::FieldFun::CreateInverse
(
	const std::shared_ptr<SectPx_Par>& thePar
) const
{
	auto field = std::make_shared<sectPxLib::FieldFun_Minus>();
	Debug_Null_Pointer(field);

	field->SetPar(thePar);
	field->IsRegistered() = Standard_True;

	Debug_Null_Pointer(Registry());
	return Registry()->Import(std::move(field));
}

Standard_Integer 
tnbLib::maker::FieldFun::CreateUniform
(
	const std::shared_ptr<SectPx_FieldFun>& theField
) const
{
	if (theField->IsRegistered())
	{
		auto field = std::make_shared<unaryOpFieldFun::Plus<std::weak_ptr<SectPx_FieldFun>>>();
		Debug_Null_Pointer(field);

		field->SetField(theField);
		field->IsRegistered() = Standard_True;

		Debug_Null_Pointer(Registry());
		return Registry()->Import(std::move(field));
	}
	else
	{
		auto field = std::make_shared<unaryOpFieldFun::Plus<std::shared_ptr<SectPx_FieldFun>>>();
		Debug_Null_Pointer(field);

		field->SetField(theField);
		field->IsRegistered() = Standard_True;

		Debug_Null_Pointer(Registry());
		return Registry()->Import(std::move(field));
	}	
}

Standard_Integer
tnbLib::maker::FieldFun::CreateInverse
(
	const std::shared_ptr<SectPx_FieldFun>& theField
) const
{
	if (theField->IsRegistered())
	{
		auto field = std::make_shared<unaryOpFieldFun::Minus<std::weak_ptr<SectPx_FieldFun>>>();
		Debug_Null_Pointer(field);

		field->SetField(theField);
		field->IsRegistered() = Standard_True;

		Debug_Null_Pointer(Registry());
		return Registry()->Import(std::move(field));
	}
	else
	{
		auto field = std::make_shared<unaryOpFieldFun::Minus<std::shared_ptr<SectPx_FieldFun>>>();
		Debug_Null_Pointer(field);

		field->SetField(theField);
		field->IsRegistered() = Standard_True;

		Debug_Null_Pointer(Registry());
		return Registry()->Import(std::move(field));
	}
}

Standard_Integer 
tnbLib::maker::FieldFun::CreateReadingX
(
	const std::shared_ptr<SectPx_Coord>& theCoord
) const
{
	auto field = std::make_shared<sectPxLib::FieldFun_readX>(theCoord);
	Debug_Null_Pointer(field);

	field->IsRegistered() = Standard_True;

	Debug_Null_Pointer(Registry());
	return Registry()->Import(std::move(field));
}

Standard_Integer 
tnbLib::maker::FieldFun::CreateReadingY
(
	const std::shared_ptr<SectPx_Coord>& theCoord
) const
{
	auto field = std::make_shared<sectPxLib::FieldFun_readY>(theCoord);
	Debug_Null_Pointer(field);

	field->IsRegistered() = Standard_True;

	Debug_Null_Pointer(Registry());
	return Registry()->Import(std::move(field));
}

Standard_Integer 
tnbLib::maker::FieldFun::CreateExpression
(
	const word & expr
) const
{
	auto field = std::make_shared<sectPxLib::FieldFun_Expr>(expr);
	Debug_Null_Pointer(field);

	field->IsRegistered() = Standard_True;

	Debug_Null_Pointer(Registry());
	return Registry()->Import(std::move(field));
}

Standard_Integer 
tnbLib::maker::FieldFun::CreateLinearForm
(
	const std::shared_ptr<SectPx_FieldFun>& theF0, 
	const std::shared_ptr<SectPx_FieldFun>& theF1, 
	const std::shared_ptr<SectPx_Par>& thePar
) const
{
	auto par = std::make_shared<sectPxLib::FieldFun_Uni>();
	Debug_Null_Pointer(par);

	par->SetPar(thePar);

	auto field = theF0 + (theF1 - theF0)*par;
	Debug_Null_Pointer(field);

	field->IsRegistered() = Standard_True;
	return Registry()->Import(std::move(field));
}

std::vector<std::shared_ptr<tnbLib::SectPx_FieldFun>> 
tnbLib::maker::FieldFun::RetrieveFieldFuns() const
{
	Debug_Null_Pointer(Registry());
	std::vector<std::shared_ptr<SectPx_FieldFun>> fields;
	for (const auto& x : Registry()->Objects())
	{
		if (SectPx_FieldFunTools::IsFieldFun(x.second))
		{
			fields.push_back(std::dynamic_pointer_cast<SectPx_FieldFun>(x.second));
		}
	}
	return std::move(fields);
}