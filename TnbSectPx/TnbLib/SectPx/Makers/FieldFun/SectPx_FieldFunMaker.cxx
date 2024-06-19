#include <SectPx_FieldFunMaker.hxx>

#include <SectPx_ParRegistry.hxx>
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

	const auto id = Registry()->Import(field);

	field->SetPar(thePar);
	field->IsRegistered() = Standard_True;

	Debug_Null_Pointer(Registry());
	return id;
}

Standard_Integer 
tnbLib::maker::FieldFun::CreateInverse
(
	const std::shared_ptr<SectPx_Par>& thePar
) const
{
	auto field = std::make_shared<sectPxLib::FieldFun_Minus>();
	Debug_Null_Pointer(field);

	const auto id = Registry()->Import(field);

	field->SetPar(thePar);
	field->IsRegistered() = Standard_True;

	Debug_Null_Pointer(Registry());
	return id;
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

		const auto id = Registry()->Import(field);

		field->SetField(theField);
		field->IsRegistered() = Standard_True;

		Debug_Null_Pointer(Registry());
		return id;
	}
	else
	{
		auto field = std::make_shared<unaryOpFieldFun::Plus<std::shared_ptr<SectPx_FieldFun>>>();
		Debug_Null_Pointer(field);

		const auto id = Registry()->Import(field);

		field->SetField(theField);
		field->IsRegistered() = Standard_True;

		Debug_Null_Pointer(Registry());
		return id;
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

		const auto id = Registry()->Import(field);

		field->SetField(theField);
		field->IsRegistered() = Standard_True;

		Debug_Null_Pointer(Registry());
		return id;
	}
	else
	{
		auto field = std::make_shared<unaryOpFieldFun::Minus<std::shared_ptr<SectPx_FieldFun>>>();
		Debug_Null_Pointer(field);

		const auto id = Registry()->Import(field);

		field->SetField(theField);
		field->IsRegistered() = Standard_True;

		Debug_Null_Pointer(Registry());
		return id;
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

	const auto id = Registry()->Import(field);

	field->IsRegistered() = Standard_True;

	Debug_Null_Pointer(Registry());
	return id;
}

Standard_Integer 
tnbLib::maker::FieldFun::CreateReadingY
(
	const std::shared_ptr<SectPx_Coord>& theCoord
) const
{
	auto field = std::make_shared<sectPxLib::FieldFun_readY>(theCoord);
	Debug_Null_Pointer(field);

	const auto id = Registry()->Import(field);

	field->IsRegistered() = Standard_True;

	Debug_Null_Pointer(Registry());
	return id;
}

Standard_Integer 
tnbLib::maker::FieldFun::CreateExpression
(
	const word & expr
) const
{
	auto field = std::make_shared<sectPxLib::FieldFun_Expr>(expr);
	Debug_Null_Pointer(field);

	const auto id = Registry()->Import(field);

	field->IsRegistered() = Standard_True;

	Debug_Null_Pointer(Registry());
	return id;
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

	Registry()->Import(par);

	par->SetPar(thePar);

	auto field = theF0 + (theF1 - theF0)*par;
	Debug_Null_Pointer(field);

	const auto id = Registry()->Import(field);

	field->IsRegistered() = Standard_True;
	return id;
}

Standard_Integer tnbLib::maker::FieldFun::CreateMin(const std::shared_ptr<SectPx_FieldFun>& theField0,
	const std::shared_ptr<SectPx_FieldFun>& theField1) const
{
	const auto field = min(theField0, theField1);
	Debug_Null_Pointer(field);
	const auto id = Registry()->Import(field);
	field->IsRegistered() = Standard_True;
	return id;
}

Standard_Integer tnbLib::maker::FieldFun::CreateMax(const std::shared_ptr<SectPx_FieldFun>& theField0,
	const std::shared_ptr<SectPx_FieldFun>& theField1) const
{
	const auto field = max(theField0, theField1);
	Debug_Null_Pointer(field);
	const auto id = Registry()->Import(field);
	field->IsRegistered() = Standard_True;
	return id;
}

Standard_Integer tnbLib::maker::FieldFun::CreateAdd(const std::shared_ptr<SectPx_FieldFun>& f0,
	const std::shared_ptr<SectPx_FieldFun>& f1)
{
	const auto field = f0 + f1;
	Debug_Null_Pointer(field);
	const auto id = Registry()->Import(field);
	field->IsRegistered() = Standard_True;
	return id;
}

Standard_Integer tnbLib::maker::FieldFun::CreateSubtract(const std::shared_ptr<SectPx_FieldFun>& f0,
	const std::shared_ptr<SectPx_FieldFun>& f1)
{
	const auto field = f0 - f1;
	Debug_Null_Pointer(field);
	const auto id = Registry()->Import(field);
	field->IsRegistered() = Standard_True;
	return id;
}

Standard_Integer tnbLib::maker::FieldFun::CreateCross(const std::shared_ptr<SectPx_FieldFun>& f0,
	const std::shared_ptr<SectPx_FieldFun>& f1)
{
	const auto field = f0 * f1;
	Debug_Null_Pointer(field);
	const auto id = Registry()->Import(field);
	field->IsRegistered() = Standard_True;
	return id;
}

Standard_Integer tnbLib::maker::FieldFun::CreateDivide(const std::shared_ptr<SectPx_FieldFun>& f0,
	const std::shared_ptr<SectPx_FieldFun>& f1)
{
	if (std::abs(f1->Value()) <= gp::Resolution())
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "subdividing to zero has been detected." << endl
			<< " - Field's name: " << endl
			<< f1->Name() << endl
			<< abort(FatalError);
	}
	const auto field = f0 / f1;
	Debug_Null_Pointer(field);
	const auto id = Registry()->Import(field);
	field->IsRegistered() = Standard_True;
	return id;
}

Standard_Integer tnbLib::maker::FieldFun::CreateAbs(const std::shared_ptr<SectPx_FieldFun>& f)
{
	const auto field = abs(f);
	Debug_Null_Pointer(field);
	const auto id = Registry()->Import(field);
	field->IsRegistered() = Standard_True;
	return id;
}

Standard_Integer tnbLib::maker::FieldFun::CreateSqrt(const std::shared_ptr<SectPx_FieldFun>& f)
{
	const auto field = sqrt(f);
	Debug_Null_Pointer(field);
	const auto id = Registry()->Import(field);
	field->IsRegistered() = Standard_True;
	return id;
}

Standard_Integer tnbLib::maker::FieldFun::CreateSin(const std::shared_ptr<SectPx_FieldFun>& f)
{
	const auto field = sin(f);
	Debug_Null_Pointer(field);
	const auto id = Registry()->Import(field);
	field->IsRegistered() = Standard_True;
	return id;
}

Standard_Integer tnbLib::maker::FieldFun::CreateCos(const std::shared_ptr<SectPx_FieldFun>& f)
{
	const auto field = cos(f);
	Debug_Null_Pointer(field);
	const auto id = Registry()->Import(field);
	field->IsRegistered() = Standard_True;
	return id;
}

Standard_Integer tnbLib::maker::FieldFun::CreateTan(const std::shared_ptr<SectPx_FieldFun>& f)
{
	const auto field = tan(f);
	Debug_Null_Pointer(field);
	const auto id = Registry()->Import(field);
	field->IsRegistered() = Standard_True;
	return id;
}

Standard_Integer tnbLib::maker::FieldFun::CreateAsin(const std::shared_ptr<SectPx_FieldFun>& f)
{
	const auto field = asin(f);
	Debug_Null_Pointer(field);
	const auto id = Registry()->Import(field);
	field->IsRegistered() = Standard_True;
	return id;
}

Standard_Integer tnbLib::maker::FieldFun::CreateAcos(const std::shared_ptr<SectPx_FieldFun>& f)
{
	const auto field = acos(f);
	Debug_Null_Pointer(field);
	const auto id = Registry()->Import(field);
	field->IsRegistered() = Standard_True;
	return id;
}

Standard_Integer tnbLib::maker::FieldFun::CreateAtan(const std::shared_ptr<SectPx_FieldFun>& f)
{
	const auto field = atan(f);
	Debug_Null_Pointer(field);
	const auto id = Registry()->Import(field);
	field->IsRegistered() = Standard_True;
	return id;
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
