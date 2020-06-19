#include <Marine_DisctLib.hxx>

#include <Geo_xDistb.hxx>
#include <Marine_WireFrameModel.hxx>
#include <Marine_Models.hxx>
#include <Marine_Distrb.hxx>
#include <Marine_xCmpSection.hxx>
#include <Marine_zCmpSection.hxx>
#include <Marine_WaterDomain.hxx>
#include <Marine_Bodies.hxx>
#include <Marine_SectTools.hxx>
#include <Marine_FlatWave.hxx>
#include <MarineBase_Tools.hxx>
#include <Marine_BooleanOps.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <gp_Pln.hxx>
#include <GeomAPI_IntSS.hxx>
#include <BRepAlgoAPI_Section.hxx>

TopoDS_Shape 
tnbLib::Marine_DisctLib::Section
(
	const TopoDS_Shape & theShape,
	const gp_Ax2 & theSys
)
{
	BRepAlgoAPI_Section alg;
	alg.ComputePCurveOn1(Standard_True);
	alg.SetRunParallel(Standard_True);
	alg.Init2(theShape);
	alg.Approximation(Standard_True);

	gp_Pln plane(theSys);

	alg.Init1(plane);
	alg.Build();

	if (alg.Shape().IsNull())
	{
		FatalErrorIn(FunctionSIG)
			<< "Failed to calculate intersection" << endl
			<< abort(FatalError);
	}
	return alg.Shape();
}

std::shared_ptr<tnbLib::Marine_WireFrameModel> 
tnbLib::Marine_DisctLib::xWireFrameModel
(
	const Marine_Model & theModel,
	const Marine_Distrb & theX,
	const Standard_Real theMinTol, 
	const Standard_Real theMaxTol
)
{
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

		auto sect = Section(theModel.Shape(), syst);
		shapes.push_back(std::move(sect));
	}

	auto model = std::make_shared<Marine_WireFrameModel>();
	Debug_Null_Pointer(model);

	std::shared_ptr<Marine_Body> body;

	switch (theModel.Type())
	{
	case Marine_ModelType::hull:
	{
		body = std::make_shared<marineLib::Body_Displacer>();
	}
	case Marine_ModelType::sail:
	{
		body = std::make_shared<marineLib::Body_Sail>();
	}
	case Marine_ModelType::tank:
	{
		body = std::make_shared<marineLib::Body_Tank>();
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
		switch (theModel.Type())
		{
		case Marine_ModelType::hull:
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
		case Marine_ModelType::sail:
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
		case Marine_ModelType::tank:
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
	model->ChangeShape() = theModel.Shape();

	return std::move(model);
}

std::shared_ptr<tnbLib::marineLib::Body_Wetted>
tnbLib::Marine_DisctLib::WettedBody
(
	const Marine_WireFrameModel & theModel,
	const Marine_WaterDomain & theWaterDomain,
	const Standard_Real theMinTol,
	const Standard_Real theMaxTol
)
{
	auto body = std::make_shared<marineLib::Body_Wetted>();
	Debug_Null_Pointer(body);

	const auto& wave = theWaterDomain.Wave();
	if (NOT wave)
	{
		FatalErrorIn("std::shared_ptr<Marine_WettedBody> WettedBody(Args...)")
			<< " no wave has been loaded!" << endl
			<< abort(FatalError);
	}

	const auto& shape = theModel.Shape();
	if (shape.IsNull())
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
	alg.Init2(theModel.Shape());
	alg.Approximation(Standard_True);

	alg.Build();

	if (alg.Shape().IsNull())
	{
		FatalErrorIn("std::shared_ptr<Marine_WireFrameModel> Marine_DisctLib::WettedBody(Args...)")
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

	body->SetWater(std::move(section));

	const auto& waterSections = theWaterDomain.Waters();
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