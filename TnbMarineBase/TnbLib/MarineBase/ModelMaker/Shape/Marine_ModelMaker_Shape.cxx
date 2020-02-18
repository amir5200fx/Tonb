#include <Marine_ModelMaker_Shape.hxx>

#include <Marine_SectionDistribution.hxx>
#include <Marine_CmpSection.hxx>
#include <Marine_VesselModel.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <gp_Ax2.hxx>
#include <gp_Pln.hxx>
#include <TopoDS_Edge.hxx>
#include <BRepAlgoAPI_Section.hxx>

tnbLib::Marine_ModelMaker::Marine_ModelMaker()
	: theMinTolerance_(1.0E-6)
	, theMaxTolerance_(1.0E-3)
{
}

//tnbLib::Marine_ModelMaker::Marine_ModelMaker
//(
//	const Standard_Integer theIndex,
//	const word & theName
//)
//	: Marine_Entity(theIndex, theName)
//	, theMinTolerance_(1.0E-6)
//	, theMaxTolerance_(1.0E-3)
//{
//}

void tnbLib::Marine_ModelMaker_Shape::Perform()
{
	if (Shape().IsNull())
	{
		FatalErrorIn("void tnbLib::Marine_ModelMaker_Shape::Perform()")
			<< "the model is not loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Distributor())
	{
		FatalErrorIn("void tnbLib::Marine_ModelMaker_Shape::Perform()")
			<< "the distributor is not loaded!" << endl
			<< abort(FatalError);
	}

	const auto& sys = Distributor()->CoordinateSystem();
	gp_Ax2 syst0(sys.Location(), sys.XDirection(), sys.Direction());

	std::vector<TopoDS_Shape> shapes;
	std::vector<gp_Ax2> systems;

	const auto& xSections = Distributor()->Sections();
	systems.reserve(xSections.size());

	auto x0 = syst0.Location().Z();
	for (auto x : xSections)
	{
		auto syst = syst0.Translated(gp_Vec(x - x0, 0, 0));
		systems.push_back(syst);

		gp_Pln plane(syst);

		BRepAlgoAPI_Section alg;	
		alg.ComputePCurveOn1(Standard_True);
		alg.SetRunParallel(Standard_True);
		alg.Init1(plane);
		alg.Init2(Shape());
		alg.Build();

		if (alg.Shape().IsNull())
		{
			FatalErrorIn("void tnbLib::Marine_ModelMaker_Shape::Perform()")
				<< "Failed to calculate intersection" << endl
				<< abort(FatalError);
		}

		shapes.push_back(alg.Shape());
	}

	std::vector<std::shared_ptr<Marine_CmpSection>>
		sections;
	sections.reserve(xSections.size());
	
	Standard_Integer i = 0;
	for (const auto& x : shapes)
	{
		sections.push_back
		(
			Marine_CmpSection::CreateCmpSection
			(x, systems[i++], MinTolerance(), MaxTolerance()));
	}

	auto model = std::make_shared<Marine_VesselModel>();
	Debug_Null_Pointer(model);

	Standard_Integer K = 0;
	for (const auto& x : sections)
	{
		Debug_Null_Pointer(x);
		model->ImportSection(++K, x);
	}

	ChangeModel() = std::move(model);

	Change_IsDone() = Standard_True;
}