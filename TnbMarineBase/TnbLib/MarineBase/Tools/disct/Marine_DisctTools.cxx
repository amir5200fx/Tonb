#include <Marine_DisctTools.hxx>

#include <Marine_CmpSection.hxx>
#include <Marine_Section.hxx>
#include <Marine_BooleanOps.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <gp_Ax2.hxx>
#include <gp_Pln.hxx>
#include <GeomAPI_IntSS.hxx>
#include <BRepAlgoAPI_Section.hxx>
#include <TopoDS_Shape.hxx>

TopoDS_Shape 
tnbLib::Marine_DisctTools::Section
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

std::vector<std::shared_ptr<tnbLib::Marine_CmpSection>> 
tnbLib::Marine_DisctTools::WettedSections
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections, 
	const std::vector<std::shared_ptr<Marine_Section>>& theWaters
)
{
	std::vector<std::shared_ptr<Marine_CmpSection>> wetted;
	Standard_Integer K = 0;
	for (const auto& x : theSections)
	{
		Debug_Null_Pointer(x);

		const auto& wa = theWaters[K++];
		Debug_Null_Pointer(wa);

		auto wet = Marine_BooleanOps::WettedSection(x, wa);
		if (wet)
		{
			wet->SetCoordinateSystem(x->CoordinateSystem());
			wetted.push_back(std::move(wet));
		}
	}
	return std::move(wetted);
}