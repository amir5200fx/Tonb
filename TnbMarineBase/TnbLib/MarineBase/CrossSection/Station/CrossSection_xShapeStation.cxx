#include <CrossSection_xShapeStation.hxx>

#include <Marine_SectionDistribution.hxx>
#include <Marine_CmpSection.hxx>
#include <Marine_VesselModel.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <gp_Ax2.hxx>
#include <gp_Pln.hxx>
#include <TopoDS_Edge.hxx>
#include <BRepAlgoAPI_Section.hxx>

void tnbLib::CrossSection_xShapeStation::Perform()
{
	if (Shape().IsNull())
	{
		FatalErrorIn("void tnbLib::CrossSection_xShapeStation::Perform()")
			<< "the model is not loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Distributor())
	{
		FatalErrorIn("void tnbLib::CrossSection_xShapeStation::Perform()")
			<< "the distributor is not loaded!" << endl
			<< abort(FatalError);
	}

	const auto& sys = Distributor()->CoordinateSystem();
	gp_Ax2 syst0(sys.Location(), sys.XDirection(), sys.Direction());

	std::vector<TopoDS_Shape> shapes;
	std::vector<gp_Ax2> systems;

	const auto& xSections = Distributor()->Sections();
	systems.reserve(xSections.size());

	BRepAlgoAPI_Section alg;
	alg.ComputePCurveOn1(Standard_True);
	alg.SetRunParallel(Standard_True);
	alg.Init2(Shape());

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
			FatalErrorIn("void tnbLib::CrossSection_xShapeStation::Perform()")
				<< "Failed to calculate intersection" << endl
				<< abort(FatalError);
		}

		shapes.push_back(alg.Shape());
	}

	auto& sections = ChangeSections();
	sections.reserve(xSections.size());

	Standard_Integer i = 0;
	Standard_Integer K = 0;
	for (const auto& x : shapes)
	{
		auto section = 
			Marine_CmpSection::CreateCmpSection
			(
				x, systems[i++], MinTolerance(), 
				MaxTolerance());
		Debug_Null_Pointer(section);

		section->SetIndex(++K);

		sections.push_back
		(
			std::move(section));
	}

	Change_IsDone() = Standard_True;
}