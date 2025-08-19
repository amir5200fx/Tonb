#include <PtdModel_SolidMaker_Propeller.hxx>

#include <PtdModel_Shape_PropBlades.hxx>
#include <PtdModel_Shape_PropHub.hxx>
#include <PtdModel_PropShape.hxx>
#include <Cad_Shape.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepOffsetAPI_Sewing.hxx>
#include <BRepBuilderAPI_MakeSolid.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Shell.hxx>
#include <TopoDS_CompSolid.hxx>
#include <TopoDS_Builder.hxx>
#include <TopoDS.hxx>
#include <TopExp_Explorer.hxx>

void tnbLib::ptdModel::SolidMaker_Propeller::Perform()
{
	if (NOT Blades())
	{
		FatalErrorIn(FunctionSIG)
			<< "no blades object has been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Hub())
	{
		FatalErrorIn(FunctionSIG)
			<< "no hub object has been loaded!" << endl
			<< abort(FatalError);
	}

	const auto& bladesShape = Blades()->Shape();
	if (NOT bladesShape)
	{
		FatalErrorIn(FunctionSIG)
			<< "no shape of the blades has been found!" << endl
			<< abort(FatalError);
	}

	const auto& hubShape = Hub()->Shape();
	if (NOT hubShape)
	{
		FatalErrorIn(FunctionSIG)
			<< "no shape of the hub has been found!" << endl
			<< abort(FatalError);
	}

	BRepOffsetAPI_Sewing bSewing;
	bSewing.Add(bladesShape->Shape());
	bSewing.Perform();

	TopoDS_Shape bSewed = bSewing.SewedShape();

	TopoDS_CompSolid compound;
	TopoDS_Builder builder;
	builder.MakeCompSolid(compound);

	for (TopExp_Explorer explorer(bSewed, TopAbs_SHELL); explorer.More(); explorer.Next())
	{
		TopoDS_Shell shell = TopoDS::Shell(explorer.Current());

		BRepBuilderAPI_MakeSolid brep_solid(shell);
		TopoDS_Solid solid = brep_solid.Solid();

		builder.Add(compound, solid);
	}

	BRepOffsetAPI_Sewing hSewing;
	hSewing.Add(hubShape->Shape());
	hSewing.Perform();

	TopoDS_Shape hSewed = hSewing.SewedShape();

	BRepBuilderAPI_MakeSolid brep_solid2(TopoDS::Shell(hSewed));

	TopoDS_Shape myShape = BRepAlgoAPI_Fuse(compound, brep_solid2.Solid());
	auto myPropShape = std::make_shared<Cad_Shape>(0, "propeller", std::move(myShape));

	auto myProp = std::make_shared<PtdModel_PropShape>(Hub(), Blades());
	Debug_Null_Pointer(myProp);

	myProp->SetShape(std::move(myPropShape));

	Change_IsDone() = Standard_True;
}

void tnbLib::ptdModel::SolidMaker_Propeller::LoadBlades(const std::shared_ptr<ptdModel::Shape_PropBlades>& theBlades)
{
	theBlades_ = theBlades;
}

void tnbLib::ptdModel::SolidMaker_Propeller::LoadBlades(std::shared_ptr<ptdModel::Shape_PropBlades>&& theBlades)
{
	theBlades_ = std::move(theBlades);
}

void tnbLib::ptdModel::SolidMaker_Propeller::LoadHub(const std::shared_ptr<ptdModel::Shape_PropHub>& theHub)
{
	theHub_ = theHub;
}

void tnbLib::ptdModel::SolidMaker_Propeller::LoadHub(std::shared_ptr<ptdModel::Shape_PropHub>&& theHub)
{
	theHub_ = std::move(theHub);
}