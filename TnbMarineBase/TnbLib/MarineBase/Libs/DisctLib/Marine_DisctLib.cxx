#include <Marine_DisctLib.hxx>

#include <Geo_xDistb.hxx>
#include <Marine_Water.hxx>
#include <Marine_WireFrameShapes.hxx>
#include <Marine_Shapes.hxx>
#include <Marine_Distrb.hxx>
#include <Marine_xCmpSection.hxx>
#include <Marine_zCmpSection.hxx>
#include <Marine_WaterDomain.hxx>
#include <Marine_Bodies.hxx>
#include <Marine_SectTools.hxx>
#include <Marine_FlatWave.hxx>
#include <MarineBase_Tools.hxx>
#include <Marine_BooleanOps.hxx>
#include <Marine_BodyTools.hxx>
#include <Marine_DisctTools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif

#include <gp_Pln.hxx>
#include <GeomAPI_IntSS.hxx>
#include <BRepAlgoAPI_Section.hxx>


std::shared_ptr<tnbLib::Marine_WireFrameShape> 
tnbLib::Marine_DisctLib::xWireFrameModel
(
	const std::shared_ptr<Marine_Shape> & theModel,
	const Marine_Distrb & theX,
	const Standard_Real theMinTol, 
	const Standard_Real theMaxTol
)
{
	Debug_Null_Pointer(theModel);

	const auto& sys = theX.CoordinateSystem();
	gp_Ax2 syst0(sys.Location(), sys.XDirection(), sys.YDirection());

	std::vector<TopoDS_Shape> shapes;
	std::vector<gp_Ax2> systems;

	const auto& xSections = theX.X()->Values();
	systems.reserve(xSections.size());

	auto x0 = syst0.Location().Z();
	for (auto x : xSections)
	{
		auto syst = syst0.Translated(gp_Vec(x - x0, 0, 0));
		systems.push_back(syst);

		auto sect = Marine_DisctTools::Section(theModel->Shape(), syst);
		shapes.push_back(std::move(sect));
	}

	auto model = std::make_shared<marineLib::WireFrameShape_Shape>();
	Debug_Null_Pointer(model);

	std::shared_ptr<Marine_Body> body;

	switch (theModel->Type())
	{
	case Marine_ShapeType::hull:
	{
		body = std::make_shared<marineLib::BodyConstructor_Shape<marineLib::Body_Displacer>>();
		Debug_Null_Pointer(body);

		std::dynamic_pointer_cast
			<
			marineLib::BodyConstructor_Shape<marineLib::Body_Displacer>
			>
			(
				body
				)->SetShape(theModel);
	}
	case Marine_ShapeType::sail:
	{
		body = std::make_shared<marineLib::BodyConstructor_Shape<marineLib::Body_Sail>>();
		Debug_Null_Pointer(body);

		std::dynamic_pointer_cast
			<
			marineLib::BodyConstructor_Shape<marineLib::Body_Sail>
			>
			(
				body
				)->SetShape(theModel);
	}
	case Marine_ShapeType::tank:
	{
		body = std::make_shared<marineLib::BodyConstructor_Shape<marineLib::Body_Tank>>();
		Debug_Null_Pointer(body);

		std::dynamic_pointer_cast
			<
			marineLib::BodyConstructor_Shape<marineLib::Body_Tank>
			>
			(
				body
				)->SetShape(theModel);
	}
	default:
		FatalErrorIn(FunctionSIG)
			<< "Invalid type of the model!" << endl
			<< abort(FatalError);
		break;
	}

	Debug_Null_Pointer(body);

	auto& sections = body->ChangeSections();
	sections.reserve(xSections.size());

	Standard_Integer i = 0;
	Standard_Integer K = 0;
	for (const auto& x : shapes)
	{
		switch (theModel->Type())
		{
		case Marine_ShapeType::hull:
		{
			auto section =
				Marine_SectTools::CmpSectionCreator
				(
					Marine_SectTools::SectionCreator
					(
						x, systems[i++],
						Marine_SectionType::displacer,
						theMinTol, theMaxTol
					));
			Debug_Null_Pointer(section);
			section->SetIndex(++K);
			sections.push_back
			(
				std::move(section));
			
		}
		case Marine_ShapeType::sail:
		{
			auto section =
				Marine_SectTools::CmpSectionCreator
				(
					Marine_SectTools::SectionCreator
					(
						x, systems[i++],
						Marine_SectionType::sail,
						theMinTol, theMaxTol
					));
			Debug_Null_Pointer(section);
			section->SetIndex(++K);
			sections.push_back
			(
				std::move(section));
		}
		case Marine_ShapeType::tank:
		{
			auto section =
				Marine_SectTools::CmpSectionCreator
				(
					Marine_SectTools::SectionCreator
					(
						x, systems[i++],
						Marine_SectionType::tank,
						theMinTol, theMaxTol
					));
			Debug_Null_Pointer(section);
			section->SetIndex(++K);
			sections.push_back
			(
				std::move(section));
		}
		default:
			FatalErrorIn(FunctionSIG)
				<< "Invalid type of the model!" << endl
				<< abort(FatalError);
			break;
		}
		
	}

	model->ChangeBody() = std::move(body);
	model->ChangeShape() = theModel;

	return std::move(model);
}

std::shared_ptr<tnbLib::marineLib::Body_Wetted> 
tnbLib::Marine_DisctLib::WettedBody
(
	const marineLib::Body_Tank & theModel,
	const Marine_WaterDomain & theWaterDomain,
	const Standard_Real theMinTol,
	const Standard_Real theMaxTol
)
{
	std::shared_ptr<marineLib::Body_Wetted> body;
	if (theModel.ShapeType())
	{
		body = std::make_shared<marineLib::BodyConstructor_Shape<marineLib::Body_Wetted>>();
		Debug_Null_Pointer(body);

		auto t = 
			std::dynamic_pointer_cast
			<
			marineLib::BodyConstructor_Shape<marineLib::Body_Tank>
			>(theModel.This());
		Debug_Null_Pointer(t);

		std::dynamic_pointer_cast
			<
			marineLib::BodyConstructor_Shape<marineLib::Body_Wetted>
			>(body)->SetShape(t->Shape());
	}
	else
	{
		body = std::make_shared<marineLib::BodyConstructor_noShape<marineLib::Body_Wetted>>();
		Debug_Null_Pointer(body);
	}

	const auto& wave = theWaterDomain.Wave();
	if (NOT wave)
	{
		FatalErrorIn("std::shared_ptr<Marine_WettedBody> WettedBody(Args...)")
			<< " no wave has been loaded!" << endl
			<< abort(FatalError);
	}

	Debug_Null_Pointer(theWaterDomain.Water());
	const auto& waterSections = theWaterDomain.Water()->Sections();
	auto wetted = Marine_DisctTools::WettedSections(theModel.Sections(), waterSections);

	body->ChangeSections() = std::move(wetted);
	return std::move(body);
}

std::shared_ptr<tnbLib::marineLib::Body_Wetted> 
tnbLib::Marine_DisctLib::WettedBody
(
	const marineLib::Body_Displacer & theModel, 
	const Marine_WaterDomain & theWaterDomain,
	const Standard_Real theMinTol,
	const Standard_Real theMaxTol
)
{
	std::shared_ptr<marineLib::Body_Wetted> body;
	if (theModel.ShapeType())
	{
		body = std::make_shared<marineLib::BodyConstructor_Shape<marineLib::Body_Wetted>>();
		Debug_Null_Pointer(body);

		auto t =
			std::dynamic_pointer_cast
			<
			marineLib::BodyConstructor_Shape<marineLib::Body_Displacer>
			>(theModel.This());
		Debug_Null_Pointer(t);

		std::dynamic_pointer_cast
			<
			marineLib::BodyConstructor_Shape<marineLib::Body_Wetted>
			>(body)->SetShape(t->Shape());
	}
	else
	{
		body = std::make_shared<marineLib::BodyConstructor_noShape<marineLib::Body_Wetted>>();
		Debug_Null_Pointer(body);
	}
	body->SetDisplacer(std::dynamic_pointer_cast<marineLib::Body_Displacer>(theModel.This()));
	const auto& wave = theWaterDomain.Wave();
	if (NOT wave)
	{
		FatalErrorIn("std::shared_ptr<Marine_WettedBody> WettedBody(Args...)")
			<< " no wave has been loaded!" << endl
			<< abort(FatalError);
	}

	Debug_Null_Pointer(theWaterDomain.Water());
	const auto& waterSections = theWaterDomain.Water()->Sections();
	auto wetted = Marine_DisctTools::WettedSections(theModel.Sections(), waterSections);

	body->ChangeSections() = std::move(wetted);
	return std::move(body);
}

std::shared_ptr<tnbLib::marineLib::Body_Wetted> 
tnbLib::Marine_DisctLib::WettedBody
(
	const std::shared_ptr<Marine_WireFrameShape>& theModel, 
	const Marine_WaterDomain & theWaterDomain, 
	const Standard_Real theMinTol,
	const Standard_Real theMaxTol
)
{
	Debug_Null_Pointer(theModel);

	if (theModel->HasShape())
	{
		auto model = std::dynamic_pointer_cast<marineLib::WireFrameShape_Shape>(theModel);
		Debug_Null_Pointer(model);

		auto body = WettedBody(*model, theWaterDomain, theMinTol, theMaxTol);
		return std::move(body);
	}
	else
	{
		auto model = std::dynamic_pointer_cast<marineLib::WireFrameShape_Offset>(theModel);
		Debug_Null_Pointer(model);

		auto body = WettedBody(*model, theWaterDomain, theMinTol, theMaxTol);
		return std::move(body);
	}
}

std::shared_ptr<tnbLib::marineLib::Body_Wetted>
tnbLib::Marine_DisctLib::WettedBody
(
	const marineLib::WireFrameShape_Shape& theModel,
	const Marine_WaterDomain & theWaterDomain,
	const Standard_Real theMinTol,
	const Standard_Real theMaxTol
)
{
	Debug_Null_Pointer(theModel.Body());
	const auto& mBody = *theModel.Body();

	if (NOT Marine_BodyTools::IsDisplacer(mBody) OR NOT Marine_BodyTools::IsTank(mBody))
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid type of the body to retrieve the wetted sections!" << endl
			<< abort(FatalError);
	}

	auto body = 
		std::make_shared<marineLib::BodyConstructor_Shape<marineLib::Body_Wetted>>();
	Debug_Null_Pointer(body);

	body->SetShape(theModel.Shape());

	const auto& wave = theWaterDomain.Wave();
	if (NOT wave)
	{
		FatalErrorIn("std::shared_ptr<Marine_WettedBody> WettedBody(Args...)")
			<< " no wave has been loaded!" << endl
			<< abort(FatalError);
	}

	const auto& shape = theModel.Shape();
	if (NOT shape)
	{
		FatalErrorIn("std::shared_ptr<Marine_WettedBody> WettedBody(Args...)")
			<< " no shape has been loaded!" << endl
			<< abort(FatalError);
	}

	const auto& gWave = wave->SurfaceGeometry();
	Debug_Null_Pointer(gWave);

	BRepAlgoAPI_Section alg;
	alg.ComputePCurveOn1(Standard_True);
	alg.SetRunParallel(Standard_True);
	alg.Init1(gWave);
	alg.Init2(shape->Shape());
	alg.Approximation(Standard_True);

	alg.Build();

	if (alg.Shape().IsNull())
	{
		FatalErrorIn("std::shared_ptr<Marine_WireFrameShape> Marine_DisctLib::WettedBody(Args...)")
			<< "Failed to calculate intersection" << endl
			<< abort(FatalError);
	}

	auto section =
		Marine_SectTools::CmpSectionCreator
		(
			Marine_SectTools::SectionCreator
			(
				alg.Shape(), theWaterDomain.CoordinateSystem(),
				Marine_SectionType::waterLine,
				theMinTol, theMaxTol
			));
	Debug_Null_Pointer(section);

	body->SetWL(std::move(section));

	Debug_Null_Pointer(theWaterDomain.Water());
	const auto& waterSections = theWaterDomain.Water()->Sections();
	auto& wetted = body->ChangeSections();

	Standard_Integer K = 0;
	for (const auto& x : theModel.Body()->Sections())
	{
		Debug_Null_Pointer(x);

		const auto& wa = waterSections[K++];
		Debug_Null_Pointer(wa);

		auto wet = Marine_BooleanOps::WettedSection(x, wa);
		if (wet)
		{
			wet->SetCoordinateSystem(x->CoordinateSystem());
			wetted.push_back(std::move(wet));
		}
	}
	return std::move(body);
}

std::shared_ptr<tnbLib::marineLib::Body_Wetted> 
tnbLib::Marine_DisctLib::WettedBody
(
	const marineLib::WireFrameShape_Offset & theModel, 
	const Marine_WaterDomain & theWaterDomain,
	const Standard_Real theMinTol,
	const Standard_Real theMaxTol
)
{
	Debug_Null_Pointer(theModel.Body());
	const auto& mBody = *theModel.Body();

	if (NOT Marine_BodyTools::IsDisplacer(mBody) OR NOT Marine_BodyTools::IsTank(mBody))
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid type of the body to retrieve the wetted sections!" << endl
			<< abort(FatalError);
	}

	auto body = 
		std::make_shared<marineLib::BodyConstructor_noShape<marineLib::Body_Wetted>>();
	Debug_Null_Pointer(body);

	const auto& wave = theWaterDomain.Wave();
	if (NOT wave)
	{
		FatalErrorIn("std::shared_ptr<Marine_WettedBody> WettedBody(Args...)")
			<< " no wave has been loaded!" << endl
			<< abort(FatalError);
	}

	Debug_Null_Pointer(theWaterDomain.Water());
	const auto& waterSections = theWaterDomain.Water()->Sections();
	auto& wetted = body->ChangeSections();

	Standard_Integer K = 0;
	for (const auto& x : theModel.Body()->Sections())
	{
		Debug_Null_Pointer(x);

		const auto& wa = waterSections[K++];
		Debug_Null_Pointer(wa);

		auto wet = Marine_BooleanOps::WettedSection(x, wa);
		if (wet)
		{
			wet->SetCoordinateSystem(x->CoordinateSystem());
			wetted.push_back(std::move(wet));
		}
	}
	return std::move(body);
}