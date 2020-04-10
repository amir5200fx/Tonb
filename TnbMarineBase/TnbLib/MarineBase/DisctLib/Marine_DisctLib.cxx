#include <Marine_DisctLib.hxx>

#include <Geo_xDistb.hxx>
#include <Marine_WireFrameModel.hxx>
#include <Marine_VesselHull.hxx>
#include <Marine_Distrb.hxx>
#include <Marine_xCmpSection.hxx>
#include <Marine_zCmpSection.hxx>
#include <Marine_WaterDomain.hxx>
#include <Marine_WettedBody.hxx>
#include <Marine_FlatWave.hxx>
#include <MarineBase_Tools.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <gp_Pln.hxx>
#include <GeomAPI_IntSS.hxx>
#include <BRepAlgoAPI_Section.hxx>

std::shared_ptr<tnbLib::Marine_WireFrameModel> 
tnbLib::Marine_DisctLib::WireFrameModel
(
	const Marine_VesselHull & theHull, 
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

	BRepAlgoAPI_Section alg;
	alg.ComputePCurveOn1(Standard_True);
	alg.SetRunParallel(Standard_True);
	alg.Init2(theHull.Shape());
	alg.Approximation(Standard_True);

	auto x0 = syst0.Location().Z();
	for (auto x : xSections)
	{
		auto syst = syst0.Translated(gp_Vec(x - x0, 0, 0));
		systems.push_back(syst);

		gp_Pln plane(syst);

		alg.Init1(plane);
		alg.Build();

		if (alg.Shape().IsNull())
		{
			FatalErrorIn("std::shared_ptr<Marine_WireFrameModel> WireFrameModel(const Marine_VesselHull& theHull, const Marine_Distrb& theX)")
				<< "Failed to calculate intersection" << endl
				<< abort(FatalError);
		}

		shapes.push_back(alg.Shape());
	}

	auto model = std::make_shared<Marine_WireFrameModel>(theHull.Shape());
	Debug_Null_Pointer(model);

	auto& sections = model->ChangeSections();
	sections.reserve(xSections.size());

	Standard_Integer i = 0;
	Standard_Integer K = 0;
	for (const auto& x : shapes)
	{
		auto section =
			Marine_xCmpSection::CreateCmpSection
			(
				x, systems[i++], theMinTol,
				theMaxTol);
		Debug_Null_Pointer(section);

		section->SetIndex(++K);

		sections.push_back
		(
			std::move(section));
	}
	return std::move(model);
}

std::shared_ptr<tnbLib::Marine_WettedBody> 
tnbLib::Marine_DisctLib::WettedBody
(
	const Marine_WireFrameModel & theModel,
	const Marine_WaterDomain & theWaterDomain,
	const Standard_Real theMinTol,
	const Standard_Real theMaxTol
)
{
	auto body = std::make_shared<Marine_WettedBody>();
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
		Marine_zCmpSection::CreateCmpSection
		(
			alg.Shape(), theWaterDomain.CoordinateSystem(), theMinTol,
			theMaxTol);
	Debug_Null_Pointer(section);

	body->ChangeWater() = std::move(section);

	const auto& waterSections = theWaterDomain.Waters();
	auto& wetted = body->ChangeSections();

	Standard_Integer K = 0;
	for (const auto& x : theModel.Sections())
	{
		Debug_Null_Pointer(x);

		const auto& wa = waterSections[K++];
		Debug_Null_Pointer(wa);

		auto wet = MarineBase_Tools::WettedSection(x, wa);
		if (wet)
		{
			wet->SetCoordinateSystem(x->CoordinateSystem());
			wetted.push_back(std::move(wet));
		}
	}
	return std::move(body);
}