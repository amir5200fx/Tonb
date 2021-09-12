#include <Cad_PreviewTools.hxx>

#include <Global_Macros.hxx>
#include <Entity3d_Box.hxx>
#include <Entity3d_Polygon.hxx>
#include <Entity3d_Chain.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Geo_Tools.hxx>
#include <Cad_Tools.hxx>
#include <Cad_ShapeTools.hxx>
#include <Cad_FastDiscrete.hxx>
#include <FastDiscrete_Params.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Poly_Triangulation.hxx>
#include <Geom_BoundedCurve.hxx>
#include <Geom_Surface.hxx>
#include <Geom_BSplineSurface.hxx>
#include <BRep_Tool.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Face.hxx>
#include <TopExp_Explorer.hxx>

std::shared_ptr<tnbLib::Entity3d_Chain> 
tnbLib::Cad_PreviewTools::RetrieveChain
(
	const std::vector<std::vector<Pnt3d>>& theRows
)
{
	if (theRows.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "empty list is detected!" << endl
			<< abort(FatalError);
	}

	const auto& row0 = theRows[0];
	if (row0.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "no points has been found at row0" << endl
			<< abort(FatalError);
	}

	const auto nRows = theRows.size();
	const auto nCols = row0.size();
	for (const auto& x : theRows)
	{
		if (x.size() NOT_EQUAL nCols)
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid net of the points" << endl
				<< abort(FatalError);
		}
	}

	auto rowChain = std::make_shared<Entity3d_Chain>(theRows[0], dualConnectivityList_Chain(nCols - 1));
	for (size_t i = 1; i < theRows.size(); i++)
	{
		auto chain = std::make_shared<Entity3d_Chain>(theRows[i], dualConnectivityList_Chain(nCols - 1));
		rowChain->Add(*chain);
	}

	connectivity::dual a0;
	a0.Value(0) = 1;
	a0.Value(1) = 1;

	auto& netConnect = rowChain->Connectivity();
	for (size_t i = 0; i < nCols; i++)
	{
		//auto indices = dualConnectivityList_Chain((Standard_Integer)nRows - 1);	
		std::vector<connectivity::dual> indices((Standard_Integer)nRows - 1, a0);
		size_t k = 0;
		for (auto& x : indices)
		{
			auto v0 = x.Value(0);
			auto v1 = x.Value(1);

			v0 += k * nCols + i;
			v1 += (k + 1) * nCols + i;

			x.Value(0) = v0;
			x.Value(1) = v1;

			++k;
		}

		for (auto& x : indices)
		{
			netConnect.push_back(std::move(x));
		}
	}
	return std::move(rowChain);
}

//std::shared_ptr<tnbLib::Entity3d_Triangulation> 
//tnbLib::Cad_PreviewTools::PreviewPatchCurves
//(
//	const Handle(Geom_Surface)& theSurface,
//	const Standard_Integer theNbSegments_U,
//	const Standard_Integer theNbSegments_V
//)
//{
//	auto bspline = Handle(Geom_BSplineSurface)::DownCast(theSurface);
//	if (NOT bspline)
//	{
//		FatalErrorIn("std::shared_ptr<Entity3d_Triangulation> PreviewPatchCurves(Args...)")
//			<< "Invalid Data: the surface is not bspline!" << endl
//			<< " - first, convert the surface to RectangularTrimmedSurface then convert it to BSpline" << endl
//			<< abort(FatalError);
//	}
//
//
//}

std::shared_ptr<tnbLib::Entity3d_Chain>
tnbLib::Cad_PreviewTools::PreviewUnMergedPatchCurves
(
	const Handle(Geom_Surface)& theSurface,
	const Standard_Integer theNbSegments_U, 
	const Standard_Integer theNbSegments_V
)
{
	auto bspline = Handle(Geom_BSplineSurface)::DownCast(theSurface);
	if (NOT bspline)
	{
		FatalErrorIn("std::shared_ptr<Entity3d_Triangulation> PreviewUnMergedPatchCurves(Args...)")
			<< "Invalid Data: the surface is not bspline!" << endl
			<< " - first, convert the surface to RectangularTrimmedSurface then convert it to BSpline" << endl
			<< abort(FatalError);
	}

	auto uknots = bspline->UKnots();
	auto vknots = bspline->VKnots();

	std::vector<std::shared_ptr<Entity3d_Polygon>> polygons;
	polygons.reserve(uknots.Size() + vknots.Size());

	forThose(i, 1, uknots.Size())
	{
		auto tr = PreviewCurveOnSurface_U(theSurface, uknots.Value(i), theNbSegments_U);
		Debug_Null_Pointer(tr);

		polygons.push_back(std::move(tr));
	}

	forThose(i, 1, vknots.Size())
	{
		auto tr = PreviewCurveOnSurface_V(theSurface, vknots.Value(i), theNbSegments_V);
		Debug_Null_Pointer(tr);

		polygons.push_back(std::move(tr));
	}

	auto chain = Geo_Tools::RetrieveChain(polygons);
	Debug_Null_Pointer(chain);

	return std::move(chain);
}

std::shared_ptr<tnbLib::Entity3d_Chain> 
tnbLib::Cad_PreviewTools::PreviewUnMergedPatchCurves
(
	const TopoDS_Face & theFace, 
	const Standard_Integer theNbSegments_U,
	const Standard_Integer theNbSegments_V
)
{
	auto geom = BRep_Tool::Surface(theFace);
	if (NOT geom)
	{
		FatalErrorIn("std::shared_ptr<Entity3d_Triangulation> PreviewPatchCurves()")
			<< "the face has no geometry!" << endl
			<< abort(FatalError);
	}

	auto tri = PreviewUnMergedPatchCurves(geom, theNbSegments_U, theNbSegments_V);
	return std::move(tri);
}

std::shared_ptr<tnbLib::Entity3d_Chain> 
tnbLib::Cad_PreviewTools::PreviewUnMergedPatchCurves
(
	const TopoDS_Shape & theShape, 
	const Standard_Integer theNbSegments_U,
	const Standard_Integer theNbSegments_V
)
{
	std::vector<std::shared_ptr<Entity3d_Chain>> preview;
	for
		(
			TopExp_Explorer Explorer(theShape, TopAbs_FACE);
			Explorer.More();
			Explorer.Next()
			)
	{
		auto face = TopoDS::Face(Explorer.Current());

		auto curve = PreviewUnMergedPatchCurves(face, theNbSegments_U, theNbSegments_V);
		Debug_Null_Pointer(curve);

		preview.push_back(curve);
	}

	auto chain = Geo_Tools::RetrieveChain(preview);
	Debug_Null_Pointer(chain);

	return std::move(chain);
}

std::shared_ptr<tnbLib::Entity3d_Polygon> 
tnbLib::Cad_PreviewTools::PreviewCurveOnSurface_U
(
	const Handle(Geom_Surface)& theSurface,
	const Standard_Real u, 
	const Standard_Integer theNbSegments
)
{
	auto trimmed = Handle(Geom_BoundedSurface)::DownCast(theSurface);
	if (NOT trimmed)
	{
		FatalErrorIn("std::shared_ptr<Entity3d_Polygon>  PreviewCurveOnSurface_U(...)")
			<< "Invalid Data: the surface is not bounded!" << endl
			<< " - first, convert the surface to RectangularTrimmedSurface then convert it to BSpline" << endl
			<< abort(FatalError);
	}

	Standard_Real u0, u1, v0, v1;
	theSurface->Bounds(u0, u1, v0, v1);

	auto ply = std::make_shared<Entity3d_Polygon>();
	Debug_Null_Pointer(ply);

	auto& pts = ply->Points();

	auto nbsegts = MAX(theNbSegments, 3);
	auto dv = (v1 - v0) / (Standard_Real)nbsegts;

	pts.reserve(nbsegts + 1);
	forThose(Index, 0, nbsegts)
	{
		auto v = Index * dv + v0;
		auto pt = theSurface->Value(u, v);

		pts.push_back(std::move(pt));
	}
	return std::move(ply);
}

std::shared_ptr<tnbLib::Entity3d_Polygon> 
tnbLib::Cad_PreviewTools::PreviewCurveOnSurface_V
(
	const Handle(Geom_Surface)& theSurface,
	const Standard_Real v, 
	const Standard_Integer theNbSegments
)
{
	auto trimmed = Handle(Geom_BoundedSurface)::DownCast(theSurface);
	if (NOT trimmed)
	{
		FatalErrorIn("std::shared_ptr<Entity3d_Polygon>  PreviewCurveOnSurface_V(...)")
			<< "Invalid Data: the surface is not bounded!" << endl
			<< " - first, convert the surface to RectangularTrimmedSurface then convert it to BSpline" << endl
			<< abort(FatalError);
	}

	Standard_Real u0, u1, v0, v1;
	theSurface->Bounds(u0, u1, v0, v1);

	auto ply = std::make_shared<Entity3d_Polygon>();
	Debug_Null_Pointer(ply);

	auto& pts = ply->Points();

	auto nbsegts = MAX(theNbSegments, 3);
	auto du = (u1 - u0) / (Standard_Real)nbsegts;

	pts.reserve(nbsegts + 1);
	forThose(Index, 0, nbsegts)
	{
		auto u = Index * du + u0;
		auto pt = theSurface->Value(u, v);

		pts.push_back(std::move(pt));
	}
	return std::move(ply);
}

std::shared_ptr<tnbLib::Entity3d_Polygon> 
tnbLib::Cad_PreviewTools::PreviewCurve
(
	const Handle(Geom_Curve)& theCurve,
	const Standard_Integer theNbSegments
)
{
	auto bounded = Handle(Geom_BoundedCurve)::DownCast(theCurve);
	if (NOT bounded)
	{
		FatalErrorIn("std::shared_ptr<Entity3d_Polygon>  PreviewPatchCurves(const Handle(Geom_Surface)& theSurface)")
			<< " invalid Data: the curve is not bounded!" << endl
			<< " - first, convert the it to a trimmed one" << endl
			<< abort(FatalError);
	}

	auto ply = std::make_shared<Entity3d_Polygon>();
	Debug_Null_Pointer(ply);

	auto& pts = ply->Points();

	auto nbsegts = MAX(theNbSegments, 3);
	auto u0 = theCurve->FirstParameter();
	auto u1 = theCurve->LastParameter();
	auto du = (u1 - u0) / (Standard_Real)nbsegts;

	pts.reserve(nbsegts + 1);
	forThose(Index, 0, nbsegts)
	{
		auto u = Index * du + u0;
		auto pt = theCurve->Value(u);

		pts.push_back(std::move(pt));
	}
	return std::move(ply);
}

std::shared_ptr<tnbLib::Entity3d_Triangulation> 
tnbLib::Cad_PreviewTools::Box
(
	const Entity3d_Box & b
)
{
	auto shape = Cad_ShapeTools::Box(b.P0(), b.P1());

	FastDiscrete_Params inf;
	inf.Deflection = b.Diameter()*1.0E-2;

	Cad_FastDiscrete::Triangulation(shape, inf);

	auto polyList = Cad_Tools::RetrieveTriangulation(shape);
	auto merged = std::make_shared<Entity3d_Triangulation>();
	for (const auto& x : polyList)
	{
		merged->Add(*Cad_Tools::Triangulation(*x));
	}
	return std::move(merged);
}