#include <PtdModel_SolidMaker_PropBlade.hxx>

#include <PtdModel_Shape_PropBladeParent.hxx>
#include <PtdModel_BladeFaces.hxx>
#include <PtdModel_PropBlade.hxx>
#include <PtdModel_Face.hxx>
#include <PtdModel_BladeInfo.hxx>
#include <Cad_Shape.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#undef DebugInfo

#include <Geom_BSplineCurve.hxx>
#include <Geom_BSplineSurface.hxx>
#include <GeomFill_BSplineCurves.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRep_Tool.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Compound.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Builder.hxx>
#include <TopExp_Explorer.hxx>

namespace tnbLib
{
	const Standard_Real tnbLib::ptdModel::SolidMaker_PropBlade::DEFAULT_TOLERANCE(1.0E-6);
}

std::pair<Handle(Geom_Surface), Handle(Geom_Surface)>
tnbLib::ptdModel::SolidMaker_PropBlade::RetrievePatches
(
	const std::shared_ptr<PtdModel_PropBlade>& theBlade
)
{
	const auto& facePatch = theBlade->FacePatch();
	if (NOT facePatch)
	{
		FatalErrorIn(FunctionSIG)
			<< "no face surface has been found!" << endl
			<< abort(FatalError);
	}

	const auto& backPatch = theBlade->BackPatch();
	if (NOT backPatch)
	{
		FatalErrorIn(FunctionSIG)
			<< "no back surface has been found!" << endl
			<< abort(FatalError);
	}

	const auto gFacePatch = facePatch->Surface();
	const auto gBackPatch = backPatch->Surface();

	auto t = std::make_pair(std::move(gFacePatch), std::move(gBackPatch));
	return std::move(t);
}

std::vector<Handle(Geom_BSplineCurve)>
tnbLib::ptdModel::SolidMaker_PropBlade::RetrieveCurves(const TopoDS_Shape& theShape)
{
	static const size_t nbCurves = 8;

	std::vector<Handle(Geom_BSplineCurve)> curves;
	curves.reserve(nbCurves);
	for (TopExp_Explorer explorer(theShape, TopAbs_EDGE); explorer.More(); explorer.Next())
	{
		auto edge = TopoDS::Edge(explorer.Current());
		TopLoc_Location loc;
		Standard_Real first, last;
		auto curve = BRep_Tool::Curve(edge, first, last);

		auto bSplCurve = Handle(Geom_BSplineCurve)::DownCast(curve);
		if (bSplCurve.IsNull())
		{
			FatalErrorIn(FunctionSIG)
				<< "null curve has been detected!" << endl
				<< abort(FatalError);
		}
		curves.push_back(std::move(bSplCurve));
	}
	return std::move(curves);
}

void tnbLib::ptdModel::SolidMaker_PropBlade::Perform()
{
	if (NOT Blade())
	{
		FatalErrorIn(FunctionSIG)
			<< "no blade has been loaded!" << endl
			<< abort(FatalError);
	}

	const auto& blade = Blade();

	const auto[gFacePatch, gBackPatch] = RetrievePatches(blade);

	if (NOT gFacePatch)
	{
		FatalErrorIn(FunctionSIG)
			<< "null geometry has been detected!" << endl
			<< abort(FatalError);
	}
	if (NOT gBackPatch)
	{
		FatalErrorIn(FunctionSIG)
			<< "null geometry has been detected!" << endl
			<< abort(FatalError);
	}

	//auto faces = std::make_shared<Faces>();
	std::vector<std::shared_ptr<PtdModel_Face>> faces;

	faces.push_back(std::make_shared<ptdModel::BladeFace_Suct>(gBackPatch));
	faces.push_back(std::make_shared<ptdModel::BladeFace_Press>(gFacePatch));

	auto faceFace = BRepBuilderAPI_MakeFace(gFacePatch, 1.0E-3);
	auto backFace = BRepBuilderAPI_MakeFace(gBackPatch, 1.0E-3);

	TopoDS_Compound compound;
	TopoDS_Builder builder;
	builder.MakeCompound(compound);

	builder.Add(compound, faceFace);
	builder.Add(compound, backFace);

	auto curves = RetrieveCurves(compound);

	GeomFill_BSplineCurves gRootFace(curves[0], curves[4], GeomFill_CoonsStyle);
	GeomFill_BSplineCurves gTipFace(curves[3], curves[7], GeomFill_CoonsStyle);

	/*faces->Root = std::make_shared<ptdModel::BladeFace_Root>(gRootFace.Surface());
	faces->Tip = std::make_shared<ptdModel::BladeFace_Tip>(gTipFace.Surface());*/

	auto rootFace = std::make_shared<ptdModel::BladeFace_Root>(gRootFace.Surface());
	//auto tipFace = std::make_shared<ptdModel::BladeFace_Tip>(gTipFace.Surface());

	faces.push_back(std::move(rootFace));
	//faces.push_back(std::move(tipFace));

	builder.Add(compound, BRepBuilderAPI_MakeFace(gRootFace.Surface(), Tolerance()));
	builder.Add(compound, BRepBuilderAPI_MakeFace(gTipFace.Surface(), Tolerance()));

	if (HasLeadingPatch())
	{
		GeomFill_BSplineCurves gTeFace(curves[2], curves[6], GeomFill_CoonsStyle);

		/*faces->Leading = std::make_shared<ptdModel::BladeFace_Lead>(gTeFace.Surface());*/
		auto leadingFace = std::make_shared<ptdModel::BladeFace_Lead>(gTeFace.Surface());
		faces.push_back(std::move(leadingFace));

		builder.Add(compound, BRepBuilderAPI_MakeFace(gTeFace.Surface(), Tolerance()));
	}

	if (HasTrailingPatch())
	{
		GeomFill_BSplineCurves gLeFace(curves[1], curves[5], GeomFill_CoonsStyle);

		/*faces->Trailing = std::make_shared<ptdModel::BladeFace_Trail>(gLeFace.Surface());*/
		auto trailingFace = std::make_shared<ptdModel::BladeFace_Trail>(gLeFace.Surface());
		faces.push_back(std::move(trailingFace));

		builder.Add(compound, BRepBuilderAPI_MakeFace(gLeFace.Surface(), Tolerance()));
	}

	//myShape.Reverse();

	auto myBladeShape = std::make_shared<Cad_Shape>(0, "myShape", std::move(compound));

	auto glInfo = blade->BladeInfo()->Globals();
	theShape_ = std::make_shared<ptdModel::Shape_PropBladeParent>(0, "parent blade", std::move(glInfo), std::move(myBladeShape), std::move(faces));

	//theFaces_ = std::move(faces);

	Change_IsDone() = Standard_True;
}