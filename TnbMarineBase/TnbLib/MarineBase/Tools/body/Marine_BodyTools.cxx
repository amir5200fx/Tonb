#include <Marine_BodyTools.hxx>

#include <Marine_BooleanOps.hxx>
#include <Marine_Bodies.hxx>
#include <Marine_WaterDomain.hxx>
#include <error.hxx>
#include <OSstream.hxx>

Standard_Boolean 
tnbLib::Marine_BodyTools::IsWetted
(
	const Marine_Body & theBody
)
{
	return theBody.Type() IS_EQUAL Marine_BodyType::wetted;
}

Standard_Boolean 
tnbLib::Marine_BodyTools::IsDry
(
	const Marine_Body & theBody
)
{
	return theBody.Type() IS_EQUAL Marine_BodyType::dry;
}

Standard_Boolean 
tnbLib::Marine_BodyTools::IsTank
(
	const Marine_Body & theBody
)
{
	return theBody.Type() IS_EQUAL Marine_BodyType::tank;
}

Standard_Boolean 
tnbLib::Marine_BodyTools::IsSail
(
	const Marine_Body & theBody
)
{
	return theBody.Type() IS_EQUAL Marine_BodyType::sail;
}

Standard_Boolean 
tnbLib::Marine_BodyTools::IsDisplacer(const Marine_Body & theBody)
{
	return theBody.Type() IS_EQUAL Marine_BodyType::displacer;
}

std::shared_ptr<tnbLib::marineLib::Body_Wetted> 
tnbLib::Marine_BodyTools::WettedBody
(
	const std::shared_ptr<Marine_Body>& theBody
)
{
	auto wetted = std::dynamic_pointer_cast<marineLib::Body_Wetted>(theBody);
	if (NOT wetted)
	{
		FatalErrorIn(FunctionSIG)
			<< "the body is not wetted!" << endl
			<< abort(FatalError);
	}
	return std::move(wetted);
}

std::shared_ptr<tnbLib::marineLib::Body_Dry> 
tnbLib::Marine_BodyTools::DryBody
(
	const std::shared_ptr<Marine_Body>& theBody
)
{
	auto dry = std::dynamic_pointer_cast<marineLib::Body_Dry>(theBody);
	if (NOT dry)
	{
		FatalErrorIn(FunctionSIG)
			<< "the body is not dry!" << endl
			<< abort(FatalError);
	}
	return std::move(dry);
}

std::shared_ptr<tnbLib::marineLib::Body_Tank> 
tnbLib::Marine_BodyTools::TankBody
(
	const std::shared_ptr<Marine_Body>& theBody
)
{
	auto tank = std::dynamic_pointer_cast<marineLib::Body_Tank>(theBody);
	if (NOT tank)
	{
		FatalErrorIn(FunctionSIG)
			<< "the body is not tank!" << endl
			<< abort(FatalError);
	}
	return std::move(tank);
}

std::shared_ptr<tnbLib::marineLib::Body_Sail> 
tnbLib::Marine_BodyTools::SailBody
(
	const std::shared_ptr<Marine_Body>& theBody
)
{
	auto sail = std::dynamic_pointer_cast<marineLib::Body_Sail>(theBody);
	if (NOT sail)
	{
		FatalErrorIn(FunctionSIG)
			<< "the body is not sail!" << endl
			<< abort(FatalError);
	}
	return std::move(sail);
}

std::shared_ptr<tnbLib::marineLib::Body_Displacer> 
tnbLib::Marine_BodyTools::DisplacerBody
(
	const std::shared_ptr<Marine_Body>& theBody
)
{
	auto displacer = std::dynamic_pointer_cast<marineLib::Body_Displacer>(theBody);
	if (NOT displacer)
	{
		FatalErrorIn(FunctionSIG)
			<< "the body is not displacer!" << endl
			<< abort(FatalError);
	}
	return std::move(displacer);
}

std::shared_ptr<tnbLib::Marine_Body> 
tnbLib::Marine_BodyTools::BodyCreator
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections, 
	const Marine_BodyType t
)
{
	CheckTypeConsistency(theSections);

	switch (t)
	{
	case Marine_BodyType::displacer:
	{
		auto body = std::make_shared<marineLib::BodyConstructor_noShape<marineLib::Body_Displacer>>();
		Debug_Null_Pointer(body);

		auto sections = body->ChangeSections();
		sections.reserve(theSections.size());
		for (const auto& x : theSections)
		{
			Debug_Null_Pointer(x);
			sections.push_back(x);
		}
		return std::move(body);
	}
	case Marine_BodyType::dry:
	{
		auto body = std::make_shared<marineLib::BodyConstructor_noShape<marineLib::Body_Dry>>();
		Debug_Null_Pointer(body);

		auto sections = body->ChangeSections();
		sections.reserve(theSections.size());
		for (const auto& x : theSections)
		{
			Debug_Null_Pointer(x);
			sections.push_back(x);
		}
		return std::move(body);
	}
	case Marine_BodyType::wetted:
	{
		auto body = std::make_shared<marineLib::BodyConstructor_noShape<marineLib::Body_Wetted>>();
		Debug_Null_Pointer(body);

		auto sections = body->ChangeSections();
		sections.reserve(theSections.size());
		for (const auto& x : theSections)
		{
			Debug_Null_Pointer(x);
			sections.push_back(x);
		}
		return std::move(body);
	}
	case Marine_BodyType::sail:
	{
		auto body = std::make_shared<marineLib::BodyConstructor_noShape<marineLib::Body_Sail>>();
		Debug_Null_Pointer(body);

		auto sections = body->ChangeSections();
		sections.reserve(theSections.size());
		for (const auto& x : theSections)
		{
			Debug_Null_Pointer(x);
			sections.push_back(x);
		}
		return std::move(body);
	}
	case Marine_BodyType::tank:
	{
		auto body = std::make_shared<marineLib::BodyConstructor_noShape<marineLib::Body_Tank>>();
		Debug_Null_Pointer(body);

		auto sections = body->ChangeSections();
		sections.reserve(theSections.size());
		for (const auto& x : theSections)
		{
			Debug_Null_Pointer(x);
			sections.push_back(x);
		}
		return std::move(body);
	}
	default:
		FatalErrorIn(FunctionSIG)
			<< "Wrong body type!" << endl
			<< abort(FatalError);
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Marine_Body> 
tnbLib::Marine_BodyTools::BodyCreator
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections, 
	const std::shared_ptr<Marine_Shape>& theShape, 
	const Marine_BodyType t
)
{
	CheckTypeConsistency(theSections);

	switch (t)
	{
	case Marine_BodyType::displacer:
	{
		auto body = std::make_shared<marineLib::BodyConstructor_Shape<marineLib::Body_Displacer>>();
		Debug_Null_Pointer(body);

		body->SetShape(theShape);

		auto sections = body->ChangeSections();
		sections.reserve(theSections.size());
		for (const auto& x : theSections)
		{
			Debug_Null_Pointer(x);
			sections.push_back(x);
		}
		return std::move(body);
	}
	case Marine_BodyType::dry:
	{
		auto body = std::make_shared<marineLib::BodyConstructor_Shape<marineLib::Body_Dry>>();
		Debug_Null_Pointer(body);

		body->SetShape(theShape);

		auto sections = body->ChangeSections();
		sections.reserve(theSections.size());
		for (const auto& x : theSections)
		{
			Debug_Null_Pointer(x);
			sections.push_back(x);
		}
		return std::move(body);
	}
	case Marine_BodyType::wetted:
	{
		auto body = std::make_shared<marineLib::BodyConstructor_Shape<marineLib::Body_Wetted>>();
		Debug_Null_Pointer(body);

		body->SetShape(theShape);

		auto sections = body->ChangeSections();
		sections.reserve(theSections.size());
		for (const auto& x : theSections)
		{
			Debug_Null_Pointer(x);
			sections.push_back(x);
		}
		return std::move(body);
	}
	case Marine_BodyType::sail:
	{
		auto body = std::make_shared<marineLib::BodyConstructor_Shape<marineLib::Body_Sail>>();
		Debug_Null_Pointer(body);

		body->SetShape(theShape);

		auto sections = body->ChangeSections();
		sections.reserve(theSections.size());
		for (const auto& x : theSections)
		{
			Debug_Null_Pointer(x);
			sections.push_back(x);
		}
		return std::move(body);
	}
	case Marine_BodyType::tank:
	{
		auto body = std::make_shared<marineLib::BodyConstructor_Shape<marineLib::Body_Tank>>();
		Debug_Null_Pointer(body);

		body->SetShape(theShape);

		auto sections = body->ChangeSections();
		sections.reserve(theSections.size());
		for (const auto& x : theSections)
		{
			Debug_Null_Pointer(x);
			sections.push_back(x);
		}
		return std::move(body);
	}
	default:
		FatalErrorIn(FunctionSIG)
			<< "Wrong body type!" << endl
			<< abort(FatalError);
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Marine_Body> 
tnbLib::Marine_BodyTools::WettedBody
(
	const std::shared_ptr<marineLib::Body_Displacer>& theBody,
	const std::shared_ptr<Marine_WaterDomain>& theDomain
)
{
	Debug_Null_Pointer(theBody);
	Debug_Null_Pointer(theDomain);

	auto sections = 
		Marine_BooleanOps::WettedSections
		(
			theBody->Sections(), 
			theDomain->Waters()
		);

	if (theBody->ShapeType())
	{
		auto t = 
			std::dynamic_pointer_cast
			<
			marineLib::BodyConstructor_Shape<marineLib::Body_Displacer>
			>(theBody);
		Debug_Null_Pointer(t);

		auto wetted = BodyCreator(sections, t->Shape(), Marine_BodyType::wetted);
		return std::move(wetted);
	}
	else
	{
		auto wetted = BodyCreator(sections, Marine_BodyType::wetted);
		return std::move(wetted);
	}	
}

std::shared_ptr<tnbLib::Marine_Body> 
tnbLib::Marine_BodyTools::DryBody
(
	const std::shared_ptr<marineLib::Body_Displacer>& theBody,
	const std::shared_ptr<Marine_WaterDomain>& theDomain
)
{
	Debug_Null_Pointer(theBody);
	Debug_Null_Pointer(theDomain);

	auto sections =
		Marine_BooleanOps::DrySections
		(
			theBody->Sections(),
			theDomain->Waters()
		);

	if (theBody->ShapeType())
	{
		auto t =
			std::dynamic_pointer_cast
			<
			marineLib::BodyConstructor_Shape<marineLib::Body_Displacer>
			>(theBody);
		Debug_Null_Pointer(t);

		auto wetted = BodyCreator(sections, t->Shape(), Marine_BodyType::dry);
		return std::move(wetted);
	}
	else
	{
		auto dry = BodyCreator(sections, Marine_BodyType::dry);
		return std::move(dry);
	}	
}