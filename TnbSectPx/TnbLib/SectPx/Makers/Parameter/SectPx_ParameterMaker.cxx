#include <SectPx_ParameterMaker.hxx>

#include <SectPx_ParRegistry.hxx>
#include <SectPx_Pars.hxx>
#include <SectPx_ParTools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::shared_ptr<tnbLib::SectPx_Par> 
tnbLib::maker::Parameter::SelectParameter
(
	const Standard_Integer theIndex
) const
{
	Debug_Null_Pointer(Registry());
	const auto& registry = *Registry();

	auto item = registry.SelectObj(theIndex);
	Debug_Null_Pointer(item);

	auto par = std::dynamic_pointer_cast<SectPx_Par>(item);
	if (NOT par)
	{
		FatalErrorIn("std::shared_ptr<SectPx_Par> SelectParameter(const Standard_Integer) const")
			<< "the selected item is not a parameter!" << endl
			<< " - index = " << theIndex << endl
			<< abort(FatalError);
	}
	return std::move(par);
}

Standard_Integer 
tnbLib::maker::Parameter::CreateFree
(
	const std::shared_ptr<SectPx_FieldFun>& theField
) const
{
	auto freeParam = std::make_shared<SectPx_FreePar>(theField);
	Debug_Null_Pointer(freeParam);

	Debug_Null_Pointer(Registry());
	return Registry()->Import(std::move(freeParam));
}

Standard_Integer 
tnbLib::maker::Parameter::CreateFree
(
	const word & theName, 
	const std::shared_ptr<SectPx_FieldFun>& theField
) const
{
	auto freeParam = std::make_shared<SectPx_FreePar>(theField);
	Debug_Null_Pointer(freeParam);

	Debug_Null_Pointer(Registry());
	return Registry()->Import(theName, std::move(freeParam));
}

Standard_Integer 
tnbLib::maker::Parameter::CreateFixed
(
	const Standard_Real x,
	const Standard_Real theMin,
	const Standard_Real theMax
) const
{
	auto fixedParam = std::make_shared<SectPx_FixedPar>(x, theMin, theMax);
	Debug_Null_Pointer(fixedParam);

	Debug_Null_Pointer(Registry());
	return Registry()->Import(std::move(fixedParam));
}

Standard_Integer 
tnbLib::maker::Parameter::CreateFixed
(
	const word & theName,
	const Standard_Real x,
	const Standard_Real theMin,
	const Standard_Real theMax
) const
{
	auto fixedParam = std::make_shared<SectPx_FixedPar>(x, theMin, theMax);
	Debug_Null_Pointer(fixedParam);

	Debug_Null_Pointer(Registry());
	return Registry()->Import(theName, std::move(fixedParam));
}

Standard_Integer 
tnbLib::maker::Parameter::CreateConstant
(
	const Standard_Real x
) const
{
	auto constParam = std::make_shared<SectPx_ConstPar>(x);
	Debug_Null_Pointer(constParam);

	Debug_Null_Pointer(Registry());
	return Registry()->Import(std::move(constParam));
}

Standard_Integer 
tnbLib::maker::Parameter::CreateConstant
(
	const word & theName,
	const Standard_Real x
) const
{
	auto constParam = std::make_shared<SectPx_ConstPar>(x);
	Debug_Null_Pointer(constParam);

	Debug_Null_Pointer(Registry());
	return Registry()->Import(theName, std::move(constParam));
}

std::shared_ptr<tnbLib::SectPx_Par> 
tnbLib::maker::Parameter::RemoveParameter
(
	const Standard_Integer theIndex
) const
{
	auto phi = SelectParameter(theIndex);
	Debug_Null_Pointer(phi);

	if (NOT SectPx_ParTools::IsRemovable(phi))
	{
		FatalErrorIn
		(
			"std::shared_ptr<SectPx_Par> RemoveParameter(const Standard_Integer theIndex)"
		)
			<< "the parameter is not removable!" << endl
			<< abort(FatalError);
	}

	Debug_Null_Pointer(Registry());
	Registry()->Remove(phi);
	return std::move(phi);
}

std::vector<std::shared_ptr<tnbLib::SectPx_Par>> 
tnbLib::maker::Parameter::RetrieveFixedParameters() const
{
	std::vector<std::shared_ptr<SectPx_Par>>
		parameters;
	for (const auto& x : Registry()->Objects())
	{
		Debug_Null_Pointer(x.second);
		const auto& obj = x.second;
		if (SectPx_ParTools::IsParameter(obj))
		{
			auto par = std::dynamic_pointer_cast<SectPx_Par>(obj);
			Debug_Null_Pointer(par);

			if (par->IsFixed())
			{
				parameters.push_back(par);
			}
		}
	}
	return std::move(parameters);
}

std::vector<std::shared_ptr<tnbLib::SectPx_Par>> 
tnbLib::maker::Parameter::RetrieveFreeParameters() const
{
	std::vector<std::shared_ptr<SectPx_Par>>
		parameters;
	for (const auto& x : Registry()->Objects())
	{
		Debug_Null_Pointer(x.second);
		const auto& obj = x.second;
		if (SectPx_ParTools::IsParameter(obj))
		{
			auto par = std::dynamic_pointer_cast<SectPx_Par>(obj);
			Debug_Null_Pointer(par);

			if (par->IsFree())
			{
				parameters.push_back(par);
			}
		}
	}
	return std::move(parameters);
}

std::vector<std::shared_ptr<tnbLib::SectPx_Par>> 
tnbLib::maker::Parameter::RetrieveConstParameters() const
{
	std::vector<std::shared_ptr<SectPx_Par>>
		parameters;
	for (const auto& x : Registry()->Objects())
	{
		Debug_Null_Pointer(x.second);
		const auto& obj = x.second;
		if (SectPx_ParTools::IsParameter(obj))
		{
			auto par = std::dynamic_pointer_cast<SectPx_Par>(obj);
			Debug_Null_Pointer(par);

			if (par->IsConstant())
			{
				parameters.push_back(par);
			}
		}
	}
	return std::move(parameters);
}

std::vector<std::shared_ptr<tnbLib::SectPx_Par>> 
tnbLib::maker::Parameter::RetrieveParameters() const
{
	std::vector<std::shared_ptr<SectPx_Par>>
		parameters;
	for (const auto& x : Registry()->Objects())
	{
		Debug_Null_Pointer(x.second);
		const auto& obj = x.second;
		if (SectPx_ParTools::IsParameter(obj))
		{
			auto par = std::dynamic_pointer_cast<SectPx_Par>(obj);
			Debug_Null_Pointer(par);

			parameters.push_back(par);
		}
	}
	return std::move(parameters);
}