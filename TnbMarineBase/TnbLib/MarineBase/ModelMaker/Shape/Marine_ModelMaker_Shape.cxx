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

tnbLib::Marine_ModelMaker::Marine_ModelMaker
(
	const Standard_Integer theIndex,
	const word & theName
)
	: Marine_Entity(theIndex, theName)
	, theMinTolerance_(1.0E-6)
	, theMaxTolerance_(1.0E-3)
{
}

void tnbLib::Marine_ModelMaker_Shape::Perform()
{
	if (Shape().IsNull())
	{
		FatalErrorIn("void tnbLib::Marine_ModelMaker_Shape::Perform()")
			<< "the model is not loaded!" << endl
			<< abort(FatalError);
	}

	gp_Ax2 system(System().Location(), System().XDirection(), System().Direction());

	BRepAlgoAPI_Section alg;
	alg.Init2(Shape());
	alg.ComputePCurveOn1(Standard_True);
	alg.SetRunParallel(Standard_True);

	std::vector<TopoDS_Shape> shapes;

	const auto& xSections = Distributor()->Sections();
	for (auto x : xSections)
	{
		auto x0 = system.Location().X();

		system.Translate(gp_Vec(0, 0, x - x0));

		gp_Pln plane(system);

		alg.Init1(plane);
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
	for (const auto& x : shapes)
	{
		sections.push_back(Marine_CmpSection::CreateCmpSection(x, MinTolerance(), MaxTolerance()));
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