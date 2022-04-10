#include <Cad_Tools.hxx>

#include <Pln_Tools.hxx>
#include <TModel_FixWire_Info.hxx>
#include <TModel_System.hxx>
#include <TModel_Curve.hxx>
#include <TModel_ParaCurve.hxx>
#include <TModel_Edges.hxx>
#include <TModel_CmpEdge.hxx>
#include <TModel_SingularEdge.hxx>
#include <TModel_Surface.hxx>
#include <TModel_Vertex.hxx>
#include <TModel_Paired.hxx>
#include <TModel_Edges.hxx>
//#include <TModel_Ring.hxx>
#include <TModel_Paired.hxx>
#include <TModel_Wire.hxx>
#include <Cad_TModel.hxx>
#include <Cad_BlockEntity.hxx>
#include <Cad_EntityManager.hxx>
#include <Cad_CurveLength.hxx>
#include <Cad_CurveLength_Info.hxx>
#include <Cad_GeomSurface.hxx>
#include <Entity2d_Metric1.hxx>
#include <Entity3d_Box.hxx>
#include <Entity3d_Chain.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Entity2d_Polygon.hxx>
#include <Entity2d_MetricMeshValue.hxx>
#include <Entity2d_MeshValue.hxx>
#include <Adt_AvlTree.hxx>
#include <Geo_Tools.hxx>
#include <Merge3d_Chain.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <gp_Pln.hxx>
#include <Geom_Line.hxx>
#include <Geom_Plane.hxx>
#include <Geom_RectangularTrimmedSurface.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <Geom_BSplineCurve.hxx>
#include <Geom_BSplineSurface.hxx>
#include <Geom_CylindricalSurface.hxx>
#include <Geom_SphericalSurface.hxx>
#include <Geom_SweptSurface.hxx>
#include <GeomAPI_ProjectPointOnCurve.hxx>
#include <GeomAPI_ProjectPointOnSurf.hxx>
#include <Bnd_Box.hxx>
#include <BRep_Tool.hxx>
#include <BRepLib.hxx>
#include <BRepBndLib.hxx>
#include <BRepTools.hxx>
#include <BRepTools_WireExplorer.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Edge.hxx>
#include <TopLoc_Location.hxx>
#include <ShapeFix_Wire.hxx>
#include <IGESControl_Controller.hxx>
#include <IGESControl_Writer.hxx>
#include <STEPControl_Controller.hxx>
#include <STEPControl_Writer.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <TColStd_Array1OfReal.hxx>

Standard_Boolean 
tnbLib::Cad_Tools::IsBounded
(
	const std::shared_ptr<Cad_GeomSurface>& theSurface
)
{
	Debug_Null_Pointer(theSurface);
	Debug_Null_Pointer(theSurface->Geometry());
	return (Standard_Boolean)Handle(Geom_BoundedSurface)::DownCast(theSurface->Geometry());
}

Standard_Boolean 
tnbLib::Cad_Tools::IsBounded(const Handle(Geom_Surface)& theSurface)
{
	Debug_Null_Pointer(theSurface);
	return (Standard_Boolean)Handle(Geom_BoundedSurface)::DownCast(theSurface);
}

Standard_Boolean 
tnbLib::Cad_Tools::IsPlane
(
	const std::shared_ptr<Cad_GeomSurface>& theSurface
)
{
	Debug_Null_Pointer(theSurface);
	Debug_Null_Pointer(theSurface->Geometry());
	return (Standard_Boolean)Handle(Geom_Plane)::DownCast(theSurface->Geometry());
}

Standard_Boolean 
tnbLib::Cad_Tools::IsCylinder
(
	const std::shared_ptr<Cad_GeomSurface>& theSurface
)
{
	Debug_Null_Pointer(theSurface);
	Debug_Null_Pointer(theSurface->Geometry());
	return (Standard_Boolean)Handle(Geom_CylindricalSurface)::DownCast(theSurface->Geometry());
}

Standard_Boolean 
tnbLib::Cad_Tools::IsSphere
(
	const std::shared_ptr<Cad_GeomSurface>& theSurface
)
{
	Debug_Null_Pointer(theSurface);
	Debug_Null_Pointer(theSurface->Geometry());
	return (Standard_Boolean)Handle(Geom_SphericalSurface)::DownCast(theSurface->Geometry());
}

Standard_Boolean 
tnbLib::Cad_Tools::IsSwept
(
	const std::shared_ptr<Cad_GeomSurface>& theSurface
)
{
	Debug_Null_Pointer(theSurface);
	Debug_Null_Pointer(theSurface->Geometry());
	return (Standard_Boolean)Handle(Geom_SweptSurface)::DownCast(theSurface->Geometry());
}

Standard_Boolean 
tnbLib::Cad_Tools::IsUniMetric
(
	const std::shared_ptr<Cad_GeomSurface>& theSurface
)
{
	if (IsPlane(theSurface))
	{
		return Standard_True;
	}
	else if (IsCylinder(theSurface))
	{
		return Standard_True;
	}
	else
	{
		return Standard_False;
	}
}

Standard_Boolean 
tnbLib::Cad_Tools::HasTriangulation
(
	const TopoDS_Shape & theShape
)
{
	for (
		TopExp_Explorer aFaceExp(theShape, TopAbs_FACE);
		aFaceExp.More();
		aFaceExp.Next()
		)
	{
		auto raw = TopoDS::Face(aFaceExp.Current());

		if (raw.IsNull())
		{
			continue;
		}

		TopLoc_Location Loc;
		auto Triangulation = BRep_Tool::Triangulation(raw, Loc);
		if (Triangulation)
		{
			return Standard_True;
		}
	}
	return Standard_False;
}

Standard_Real
tnbLib::Cad_Tools::CalcPrecision(const TModel_Vertex & theVtx)
{
	if (theVtx.IsOrphan())
	{
		return 0;
	}
	const auto& coord = theVtx.Coord();
	Standard_Real tol = RealLast();
	for (const auto& x : theVtx.Edges())
	{
		auto edge = x.second.lock();
		Debug_Null_Pointer(edge);

		if (NOT edge->IsDegenerated())
		{
			auto g = std::dynamic_pointer_cast<TModel_GeneratedEdge>(edge);
			Debug_Null_Pointer(g);
			const auto& curve = g->Curve();
			auto p0 = curve->FirstCoord();
			auto p1 = curve->LastCoord();

			auto d = std::sqrt(std::min(p0.SquareDistance(coord), p1.SquareDistance(coord)));
			if (d <= tol)
			{
				tol = d;
			}
		}
	}
	return tol;
}

Standard_Real 
tnbLib::Cad_Tools::CalcLength
(
	const Handle(Geom_Curve)& theCurve,
	const std::shared_ptr<Cad_CurveLength_Info>& theInfo
)
{
	auto alg = std::make_shared<Cad_CurveLength>(theCurve, theInfo);
	Debug_Null_Pointer(alg);

	alg->Perform();
	Debug_If_Condition_Message(NOT alg->IsDone(), "the application is not performed!");
	return alg->Result();
}

tnbLib::Pnt3d 
tnbLib::Cad_Tools::CalcCoord
(
	const Pnt2d & thePt, 
	const Geom_Surface & theSurface
)
{
	auto pt = theSurface.Value(thePt.X(), thePt.Y());
	return std::move(pt);
}

Standard_Boolean 
tnbLib::Cad_Tools::IsBounded
(
	const Handle(Geom_Curve)& theCurve
)
{
	return (Standard_Boolean)Handle(Geom_BoundedCurve)::DownCast(theCurve);
}

Standard_Boolean
tnbLib::Cad_Tools::IsRing
(
	const Handle(Geom2d_Curve)& theCurve,
	const Standard_Real u0,
	const Standard_Real u1,
	const Standard_Real tol
)
{
	auto p0 = theCurve->Value(u0);
	auto p1 = theCurve->Value(u1);

	return (Standard_Boolean)(p0.Distance(p1) <= tol);
}

Standard_Boolean 
tnbLib::Cad_Tools::IsRing
(
	const Handle(Geom_Curve)& theCurve,
	const Standard_Real u0,
	const Standard_Real u1,
	const Standard_Real tol
)
{
	auto p0 = theCurve->Value(u0);
	auto p1 = theCurve->Value(u1);

	return (Standard_Boolean)(p0.Distance(p1) <= tol);
}

tnbLib::Entity2d_Box 
tnbLib::Cad_Tools::ParametricDomain
(
	const Geom_Surface & theSurf
)
{
	Standard_Real u0, u1, v0, v1;
	theSurf.Bounds(u0, u1, v0, v1);

	auto p0 = Pnt2d(u0, v0);
	auto p1 = Pnt2d(u1, v1);
	Entity2d_Box b(std::move(p0), std::move(p1));
	return std::move(b);
}

tnbLib::Entity3d_Box 
tnbLib::Cad_Tools::BoundingBox
(
	const Bnd_Box & theBox
)
{
	Standard_Real Xmin, Xmax;
	Standard_Real Ymin, Ymax;
	Standard_Real Zmin, Zmax;

	try
	{
		theBox.Get(Xmin, Ymin, Zmin, Xmax, Ymax, Zmax);
	}
	catch (const Standard_Failure& x)
	{
		//- the box is void

		FatalErrorIn(FunctionSIG)
			<< x.GetMessageString() << endl
			<< abort(FatalError);
	}

	Entity3d_Box 
		box(Pnt3d(Xmin, Ymin, Zmin), Pnt3d(Xmax, Ymax, Zmax));
	return std::move(box);
}

tnbLib::Entity3d_Box 
tnbLib::Cad_Tools::BoundingBox
(
	const std::vector<std::shared_ptr<TModel_Surface>>& theSurfaces
)
{
	NotImplemented;
	return Entity3d_Box();
}

//tnbLib::Entity3d_Box 
//tnbLib::Cad_Tools::BoundingBox
//(
//	const std::vector<std::shared_ptr<TModel_Surface>>& theSurfaces
//)
//{
//	Bnd_Box B;
//	for (const auto& x : theSurfaces)
//	{
//		Debug_Null_Pointer(x);
//		BRepBndLib::Add(x->Face(), B);
//	}
//	auto b = BoundingBox(B);
//	return std::move(b);
//}

Bnd_Box 
tnbLib::Cad_Tools::BoundingBox
(
	const TopoDS_Shape & theShape, 
	const Standard_Boolean useTri
)
{
	Bnd_Box B;
	BRepBndLib::AddOptimal(theShape, B, useTri, Standard_False);

	return std::move(B);
}

tnbLib::Pnt2d 
tnbLib::Cad_Tools::Project
(
	const Pnt3d & thePoint, 
	const Handle(Geom_Plane)& thePlane
)
{
	GeomAPI_ProjectPointOnSurf alg;
	alg.Init(thePoint, thePlane);
	alg.Perform(thePoint);

	if (alg.NbPoints() NOT_EQUAL 1)
	{
		FatalErrorIn(FunctionSIG)
			<< "something went wrong!" << endl
			<< " - invalid nb. of projected points has have been detected!" << endl
			<< abort(FatalError);
	}
	Standard_Real u, v;
	alg.LowerDistanceParameters(u, v);

	Pnt2d pt(u, v);
	return std::move(pt);
}

Standard_Real
tnbLib::Cad_Tools::Project
(
	const Pnt3d & thePoint, 
	const Handle(Geom_Line)& theLine
)
{
	GeomAPI_ProjectPointOnCurve alg;
	alg.Init(thePoint, theLine);
	alg.Perform(thePoint);

	if (alg.NbPoints() NOT_EQUAL 1)
	{
		FatalErrorIn(FunctionSIG)
			<< "something went wrong: unable to calculate the projected point" << endl
			<< abort(FatalError);
	}
	return alg.LowerDistanceParameter();
}

tnbLib::Entity_Segment<tnbLib::Pnt2d> 
tnbLib::Cad_Tools::Project
(
	const Entity3d_SegmentRef & theSeg,
	const Handle(Geom_Plane)& thePlane
)
{
	auto p0 = Project(theSeg.P0(), thePlane);
	auto p1 = Project(theSeg.P1(), thePlane);

	Entity_Segment<Pnt2d> seg2(std::move(p0), std::move(p1));
	return std::move(seg2);
}

Handle(Geom_BSplineCurve) 
tnbLib::Cad_Tools::BoundaryCurveU0
(
	const Handle(Geom_BSplineSurface)& thePatch
)
{
	const auto& net = thePatch->Poles();
	TColgp_Array1OfPnt poles(1, net.ColLength());
	for (Standard_Integer i = 1; i <= net.ColLength(); i++)
	{
		const auto& pt = net.Value(i, 1);
		poles.SetValue(i, pt);
	}
	
	if (thePatch->Weights())
	{
		const auto& wnet = *thePatch->Weights();
		TColStd_Array1OfReal weights(1, wnet.ColLength());
		for (Standard_Integer i = 1; i <= wnet.ColLength(); i++)
		{
			weights.SetValue(i, wnet.Value(i, 1));
		}

		try
		{
			Handle(Geom_BSplineCurve) curve =
				new Geom_BSplineCurve
				(
					poles, weights,
					thePatch->UKnots(), thePatch->UMultiplicities(),
					thePatch->UDegree(),
					thePatch->IsUPeriodic()
				);
			return std::move(curve);
		}
		catch (const Standard_Failure& x)
		{
			FatalErrorIn(FunctionSIG)
				<< x.GetMessageString() << endl
				<< abort(FatalError);
		}
	}
	else
	{
		try
		{
			Handle(Geom_BSplineCurve) curve =
				new Geom_BSplineCurve
				(
					poles,
					thePatch->UKnots(), thePatch->UMultiplicities(),
					thePatch->UDegree(),
					thePatch->IsUPeriodic()
				);
			return std::move(curve);
		}
		catch (const Standard_Failure& x)
		{
			FatalErrorIn(FunctionSIG)
				<< x.GetMessageString() << endl
				<< abort(FatalError);
		}
	}
	return Handle(Geom_BSplineCurve)();
}

Handle(Geom_BSplineCurve)
tnbLib::Cad_Tools::BoundaryCurveUn
(
	const Handle(Geom_BSplineSurface)& thePatch
)
{
	const auto& net = thePatch->Poles();
	TColgp_Array1OfPnt poles(1, net.ColLength());
	for (Standard_Integer i = 1; i <= net.ColLength(); i++)
	{
		const auto& pt = net.Value(i, net.RowLength());
		poles.SetValue(i, pt);
	}

	if (thePatch->Weights())
	{
		const auto& wnet = *thePatch->Weights();
		TColStd_Array1OfReal weights(1, wnet.ColLength());
		for (Standard_Integer i = 1; i <= wnet.ColLength(); i++)
		{
			weights.SetValue(i, wnet.Value(i, net.RowLength()));
		}

		try
		{
			Handle(Geom_BSplineCurve) curve =
				new Geom_BSplineCurve
				(
					poles, weights,
					thePatch->UKnots(), thePatch->UMultiplicities(),
					thePatch->UDegree(),
					thePatch->IsUPeriodic()
				);
			return std::move(curve);
		}
		catch (const Standard_Failure& x)
		{
			FatalErrorIn(FunctionSIG)
				<< x.GetMessageString() << endl
				<< abort(FatalError);
		}
	}
	else
	{
		try
		{
			Handle(Geom_BSplineCurve) curve =
				new Geom_BSplineCurve
				(
					poles,
					thePatch->UKnots(), thePatch->UMultiplicities(),
					thePatch->UDegree(),
					thePatch->IsUPeriodic()
				);
			return std::move(curve);
		}
		catch (const Standard_Failure& x)
		{
			FatalErrorIn(FunctionSIG)
				<< x.GetMessageString() << endl
				<< abort(FatalError);
		}
	}
	return Handle(Geom_BSplineCurve)();
}

Handle(Geom_BSplineCurve)
tnbLib::Cad_Tools::BoundaryCurveV0
(
	const Handle(Geom_BSplineSurface)& thePatch
)
{
	const auto& net = thePatch->Poles();
	TColgp_Array1OfPnt poles(1, net.RowLength());
	for (Standard_Integer i = 1; i <= net.RowLength(); i++)
	{
		const auto& pt = net.Value(1, i);
		poles.SetValue(i, pt);
	}

	if (thePatch->Weights())
	{
		const auto& wnet = *thePatch->Weights();
		TColStd_Array1OfReal weights(1, wnet.RowLength());
		for (Standard_Integer i = 1; i <= wnet.RowLength(); i++)
		{
			weights.SetValue(i, wnet.Value(1, i));
		}

		try
		{
			Handle(Geom_BSplineCurve) curve =
				new Geom_BSplineCurve
				(
					poles, weights,
					thePatch->VKnots(), thePatch->VMultiplicities(),
					thePatch->VDegree(),
					thePatch->IsVPeriodic()
				);
			return std::move(curve);
		}
		catch (const Standard_Failure& x)
		{
			FatalErrorIn(FunctionSIG)
				<< x.GetMessageString() << endl
				<< abort(FatalError);
		}
	}
	else
	{
		try
		{
			Handle(Geom_BSplineCurve) curve =
				new Geom_BSplineCurve
				(
					poles,
					thePatch->VKnots(), thePatch->VMultiplicities(),
					thePatch->VDegree(),
					thePatch->IsVPeriodic()
				);
			return std::move(curve);
		}
		catch (const Standard_Failure& x)
		{
			FatalErrorIn(FunctionSIG)
				<< x.GetMessageString() << endl
				<< abort(FatalError);
		}
	}
	return Handle(Geom_BSplineCurve)();
}

Handle(Geom_BSplineCurve)
tnbLib::Cad_Tools::BoundaryCurveVn
(
	const Handle(Geom_BSplineSurface)& thePatch
)
{
	const auto& net = thePatch->Poles();
	TColgp_Array1OfPnt poles(1, net.RowLength());
	for (Standard_Integer i = 1; i <= net.RowLength(); i++)
	{
		const auto& pt = net.Value(net.ColLength(), i);
		poles.SetValue(i, pt);
	}

	if (thePatch->Weights())
	{
		const auto& wnet = *thePatch->Weights();
		TColStd_Array1OfReal weights(1, wnet.RowLength());
		for (Standard_Integer i = 1; i <= wnet.RowLength(); i++)
		{
			weights.SetValue(i, wnet.Value(wnet.ColLength(), i));
		}

		try
		{
			Handle(Geom_BSplineCurve) curve =
				new Geom_BSplineCurve
				(
					poles, weights,
					thePatch->VKnots(), thePatch->VMultiplicities(),
					thePatch->VDegree(),
					thePatch->IsVPeriodic()
				);
			return std::move(curve);
		}
		catch (const Standard_Failure& x)
		{
			FatalErrorIn(FunctionSIG)
				<< x.GetMessageString() << endl
				<< abort(FatalError);
		}
	}
	else
	{
		try
		{
			Handle(Geom_BSplineCurve) curve =
				new Geom_BSplineCurve
				(
					poles,
					thePatch->VKnots(), thePatch->VMultiplicities(),
					thePatch->VDegree(),
					thePatch->IsVPeriodic()
				);
			return std::move(curve);
		}
		catch (const Standard_Failure& x)
		{
			FatalErrorIn(FunctionSIG)
				<< x.GetMessageString() << endl
				<< abort(FatalError);
		}
	}
	return Handle(Geom_BSplineCurve)();
}

std::shared_ptr<tnbLib::Entity2d_Triangulation> 
tnbLib::Cad_Tools::ParametricTriangulation
(
	const Pnt2d & theP0,
	const Pnt2d & theP1,
	const Standard_Integer theNx, 
	const Standard_Integer theNy
)
{
	if (theNx < 2)
	{
		FatalErrorIn("std::shared_ptr<AutLib::Entity2d_Triangulation> ParametricTriangulation()")
			<< "Invalid Data" << endl
			<< abort(FatalError);
	}

	if (theNy < 2)
	{
		FatalErrorIn("std::shared_ptr<AutLib::Entity2d_Triangulation> ParametricTriangulation()")
			<< "Invalid Data" << endl
			<< abort(FatalError);
	}

	const auto Dx = theP1.X() - theP0.X();
	const auto Dy = theP1.Y() - theP0.Y();

	const auto dx = Dx / (Standard_Real)(theNx - 1);
	const auto dy = Dy / (Standard_Real)(theNy - 1);

	auto tri = std::make_shared<Entity2d_Triangulation>();
	Debug_Null_Pointer(tri);

	auto& pts = tri->Points();
	pts.reserve(theNx*theNy);

	auto& indices = tri->Connectivity();
	indices.reserve((theNx - 1)*(theNy - 1) * 2);

	Standard_Integer k = 0;
	for (auto i = 0; i < theNx; i++)
	{
		for (auto j = 0; j < theNy; j++)
		{
			auto P0 = theP0 + Pnt2d(i*dx, j*dy);
			/*auto P1 = P0 + Pnt2d(dx, 0);
			auto P2 = P0 + Pnt2d(dx, dy);
			auto P3 = P0 + Pnt2d(0, dy);*/
			//cout << i << ", " << j << "  " << P0 << std::endl;
			pts.push_back(std::move(P0));
		}
	}

	for (auto i = 0; i < theNx - 1; i++)
	{
		for (auto j = 0; j < theNy - 1; j++)
		{
			auto i0 = j * theNx + i + 1;
			auto i1 = j * theNx + i + 2;
			auto i2 = (j + 1)*theNx + i + 2;

			auto j0 = i0;
			auto j1 = i2;
			auto j2 = (j + 1)*theNx + i + 1;

			connectivity::triple I0, I1;
			I0.Value(0) = i0;
			I0.Value(1) = i1;
			I0.Value(2) = i2;

			I1.Value(0) = j0;
			I1.Value(1) = j1;
			I1.Value(2) = j2;

			indices.push_back(std::move(I0));
			indices.push_back(std::move(I1));
		}
	}
	return std::move(tri);
}

std::shared_ptr<tnbLib::Entity3d_Triangulation> 
tnbLib::Cad_Tools::Triangulation
(
	const Geom_Surface & theSurface, 
	const Entity2d_Triangulation & theParametric
)
{
	const auto& pts0 = theParametric.Points();

	auto tri = std::make_shared<Entity3d_Triangulation>();
	Debug_Null_Pointer(tri);

	auto& pts = tri->Points();
	pts.reserve(pts.size());

	for (const auto& x : pts0)
	{
		auto pt = theSurface.Value(x.X(), x.Y());
		pts.push_back(std::move(pt));
	}

	tri->Connectivity() = theParametric.Connectivity();

	return std::move(tri);
}

std::shared_ptr<tnbLib::Entity3d_Triangulation> 
tnbLib::Cad_Tools::Triangulation
(
	const Handle(Geom_Surface)& theSurface, 
	const Standard_Integer theNx,
	const Standard_Integer theNy
)
{
	auto trimmed = Handle(Geom_BoundedSurface)::DownCast(theSurface);
	if (NOT trimmed)
	{
		FatalErrorIn("std::shared_ptr<Entity3d_Triangulation> Triangulation(...)")
			<< "Invalid Data: the surface is not bounded!" << endl
			<< " - first, convert the surface to RectangularTrimmedSurface then convert it to BSpline" << endl
			<< abort(FatalError);
	}

	Standard_Real U0, U1, V0, V1;
	trimmed->Bounds(U0, U1, V0, V1);

	auto para =
		ParametricTriangulation(Pnt2d(U0, V0), Pnt2d(U1, V1), theNx, theNy);

	auto tri = Triangulation(*theSurface, *para);

	return std::move(tri);
}

std::shared_ptr<tnbLib::Entity3d_Triangulation> 
tnbLib::Cad_Tools::Triangulation
(
	const Poly_Triangulation & theTriangulation
)
{
	auto triangulation = std::make_shared<Entity3d_Triangulation>();
	Debug_Null_Pointer(triangulation);

	auto& pts = triangulation->Points();
	auto& indices = triangulation->Connectivity();

	pts.reserve(theTriangulation.NbNodes());

	const auto& nodes = theTriangulation.Nodes();
	forThose(i, 1, nodes.Size())
	{
		pts.push_back(nodes.Value(i));
	}

	indices.reserve(theTriangulation.NbTriangles());

	const auto& tris = theTriangulation.Triangles();
	forThose(i, 1, tris.Size())
	{
		const auto& x = tris.Value(i);
		Standard_Integer i0, i1, i2;
		x.Get(i0, i1, i2);

		connectivity::triple I;
		I.Value(0) = i0;
		I.Value(1) = i1;
		I.Value(2) = i2;

		indices.push_back(std::move(I));
	}
	return std::move(triangulation);
}

std::shared_ptr<tnbLib::Entity2d_Triangulation>
tnbLib::Cad_Tools::ParaTriangulation
(
	const Poly_Triangulation & theTriangulation
)
{
	if (NOT theTriangulation.HasUVNodes())
	{
		FatalErrorIn(FunctionSIG)
			<< "the triangulation has no UNNodes!" << endl
			<< abort(FatalError);
	}
	auto triangulation = std::make_shared<Entity2d_Triangulation>();
	Debug_Null_Pointer(triangulation);

	auto& pts = triangulation->Points();
	auto& indices = triangulation->Connectivity();

	pts.reserve(theTriangulation.NbNodes());

	const auto& nodes = theTriangulation.UVNodes();
	forThose(i, 1, nodes.Size())
	{	
		pts.push_back(nodes.Value(i));
	}

	indices.reserve(theTriangulation.NbTriangles());

	const auto& tris = theTriangulation.Triangles();
	forThose(i, 1, tris.Size())
	{
		const auto& x = tris.Value(i);
		Standard_Integer i0, i1, i2;
		x.Get(i0, i1, i2);

		connectivity::triple I;
		I.Value(0) = i0;
		I.Value(1) = i1;
		I.Value(2) = i2;

		indices.push_back(std::move(I));
	}
	return std::move(triangulation);
}

std::shared_ptr<tnbLib::Entity2d_MetricMeshValue> 
tnbLib::Cad_Tools::CalcMetrics
(
	const Handle(Geom_Surface)& theSurface, 
	const Entity2d_Triangulation & theApprox
)
{
	auto meshV = std::make_shared<Entity2d_MetricMeshValue>();
	Debug_Null_Pointer(meshV);

	auto mesh = std::make_shared<Entity2d_Triangulation>(theApprox);
	std::vector<Entity2d_Metric1> ms;
	ms.reserve(theApprox.NbPoints());
	for (const auto& x : theApprox.Points())
	{
		auto m = CalcMetric(x, theSurface);
		ms.push_back(std::move(m));
	}
	meshV->ValuesRef() = std::move(ms);
	meshV->MeshRef() = std::move(mesh);
	return std::move(meshV);
}

Handle(Geom_Curve)
tnbLib::Cad_Tools::ConvertToTrimmed
(
	const Handle(Geom_Curve)& theCurve, 
	const Standard_Real u0,
	const Standard_Real u1
)
{
	Handle(Geom_Curve) trimmed =
		new Geom_TrimmedCurve(theCurve, u0, u1);
	return std::move(trimmed);
}

Handle(Geom_Surface)
tnbLib::Cad_Tools::ConvertToTrimmed
(
	const Handle(Geom_Surface)& theSurface,
	const Entity2d_Box & theBnd
)
{
#ifdef _DEBUG
	if (IsBounded(theSurface))
	{
		FatalErrorIn(FunctionSIG)
			<< "the surface is already trimmed!" << endl
			<< abort(FatalError);
	}
#endif // _DEBUG
	const auto u0 = theBnd.P0().X();
	const auto u1 = theBnd.P1().X();
	const auto v0 = theBnd.P0().Y();
	const auto v1 = theBnd.P1().Y();
	Handle(Geom_Surface) trimmed = 
		new Geom_RectangularTrimmedSurface(theSurface, u0, u1, v0, v1);
	return std::move(trimmed);
}

std::shared_ptr<tnbLib::TModel_Edge> 
tnbLib::Cad_Tools::GetEdge
(
	const TopoDS_Edge & theEdge,
	const TopoDS_Face & theFace
)
{
	Standard_Real u0, u1, U0, U1;
	TopLoc_Location pLoc, eLoc;
	auto patch = BRep_Tool::Surface(theFace, pLoc);

	if (NOT BRep_Tool::SameRange(theEdge))
	{
		BRepLib::SameRange(theEdge);
	}

	if (NOT BRep_Tool::SameParameter(theEdge))
	{
		BRepLib::SameParameter(theEdge);
	}

	if (NOT BRep_Tool::SameParameter(theEdge))
	{
		FatalErrorIn(FunctionSIG)
			<< "It's supposed that the edge has SameParameter flag" << endl
			<< abort(FatalError);
	}

	if (NOT BRep_Tool::SameRange(theEdge))
	{
		FatalErrorIn(FunctionSIG)
			<< "It's supposed that the edge has SameRange flag" << endl
			<< abort(FatalError);
	}

	auto pCurve0 = BRep_Tool::CurveOnSurface(theEdge, patch, pLoc, u0, u1);
	auto pCurve = Handle(Geom2d_Curve)::DownCast(pCurve0->Copy());

	auto Curve = BRep_Tool::Curve(theEdge, eLoc, U0, U1);

	if (theEdge.Orientation() IS_EQUAL TopAbs_REVERSED)
	{
		auto temp = u1;
		u1 = pCurve->ReversedParameter(u0);
		u0 = pCurve->ReversedParameter(temp);
		pCurve->Reverse();
	}

	if (NOT Pln_Tools::IsBounded(pCurve))
	{
		pCurve = Pln_Tools::ConvertToTrimmedCurve(pCurve, u0, u1);
	}

	auto curveOnPlane = std::make_shared<TModel_ParaCurve>(pCurve);

	std::shared_ptr<TModel_Edge> newEdge;

	if (Curve)
	{
		Curve = Handle(Geom_Curve)::DownCast(Curve->Copy());
		if (NOT IsBounded(Curve))
		{
			Curve = ConvertToTrimmed(Curve, U0, U1);
		}

		auto curveOnSurface = std::make_shared<TModel_Curve>(Curve);
		newEdge = std::make_shared<TModel_SegmentEdge>(curveOnSurface, curveOnPlane);
	}
	else
	{
		newEdge = std::make_shared<TModel_SingularEdge>(curveOnPlane);
	}
	return std::move(newEdge);
}

std::shared_ptr<tnbLib::TModel_Edge> 
tnbLib::Cad_Tools::GetEdge
(
	const Standard_Integer theIndex, 
	const TopoDS_Edge & theEdge, 
	const TopoDS_Face & theFace
)
{
	auto edge = GetEdge(theEdge, theFace);
	Debug_Null_Pointer(edge);

	edge->SetIndex(theIndex);
	return std::move(edge);
}

//std::shared_ptr<tnbLib::TModel_Surface> 
//tnbLib::Cad_Tools::GetSurface(const TopoDS_Face & theFace)
//{
//	NotImplemented;
//	return nullptr;
//}

std::shared_ptr<tnbLib::TModel_Surface> 
tnbLib::Cad_Tools::GetSurface
(
	const TopoDS_Face & theFace
)
{
	//const auto forwardFace = theFace;
	const auto forwardFace = TopoDS::Face(theFace.Oriented(TopAbs_FORWARD));

	auto cmpEdge = std::make_shared<TModel_CmpEdge>();
	Debug_Null_Pointer(cmpEdge);

	auto& outter_edges = cmpEdge->EdgesRef();

	const auto Tol = sysLib::tmodel_fix_wire_info->Tolerance();
	Standard_Integer K = 0;
	Standard_Integer wireIndex = 0;

	const auto outer_wire = BRepTools::OuterWire(forwardFace);

	if (outer_wire.IsNull())
	{
		FatalErrorIn(FunctionSIG)
			<< "Null outer wire" << endl
			<< abort(FatalError);
	}

	ShapeFix_Wire SFWF(outer_wire, forwardFace, Tol);

	SFWF.SetPrecision(sysLib::tmodel_fix_wire_info->Precision());
	SFWF.SetMaxTolerance(sysLib::tmodel_fix_wire_info->MaxTolerance());
	SFWF.SetMinTolerance(sysLib::tmodel_fix_wire_info->MinTolerance());

	SFWF.FixReorder();
	SFWF.ClosedWireMode() = Standard_True;
	SFWF.FixClosed();
	SFWF.FixConnected();

	SFWF.Perform();

	auto fixed_outer_wire = SFWF.Wire();

	for (
		BRepTools_WireExplorer anEdgeExp(fixed_outer_wire);
		anEdgeExp.More();
		anEdgeExp.Next()
		)
	{
		K++;

		auto edge = TopoDS::Edge(anEdgeExp.Current());
		auto new_edge = GetEdge(K, edge, forwardFace);

		outter_edges.push_back(new_edge);
	}

	auto outerWire = std::make_shared<TModel_Wire>(++wireIndex, cmpEdge);
	std::shared_ptr<std::vector<std::shared_ptr<TModel_Wire>>> Qwire;
	for (
		TopExp_Explorer aWireExp(forwardFace, TopAbs_WIRE);
		aWireExp.More();
		aWireExp.Next()
		)
	{
		auto wire = TopoDS::Wire(aWireExp.Current());

		if (wire.IsNull()) continue;
		if (wire IS_EQUAL outer_wire) continue;
		// has inner wire

		auto cmpEdge = std::make_shared<TModel_CmpEdge>();
		Debug_Null_Pointer(cmpEdge);

		auto& Inner_edges = cmpEdge->EdgesRef();

		ShapeFix_Wire SFWF(wire, forwardFace, Tol);

		SFWF.SetPrecision(sysLib::tmodel_fix_wire_info->Precision());
		SFWF.SetMaxTolerance(sysLib::tmodel_fix_wire_info->MaxTolerance());
		SFWF.SetMinTolerance(sysLib::tmodel_fix_wire_info->MinTolerance());

		SFWF.FixReorder();
		SFWF.ClosedWireMode() = Standard_True;
		SFWF.FixClosed();
		SFWF.FixConnected();

		SFWF.Perform();
		wire = SFWF.WireAPIMake();

		for (
			BRepTools_WireExplorer anEdgeExp(wire);
			anEdgeExp.More();
			anEdgeExp.Next()
			)
		{
			auto edge = TopoDS::Edge(anEdgeExp.Current());

			K++;

			Inner_edges.push_back(GetEdge(K, edge, forwardFace));
		}

		if (Inner_edges.empty())
		{
			FatalErrorIn("Cad3d_SolidTools::face_ptr Cad_Tools::GetSurface(const TopoDS_Face & theFace)")
				<< "Empty wire" << endl
				<< abort(FatalError);
		}

		auto innerWire = std::make_shared<TModel_Wire>(++wireIndex, cmpEdge);

		if (NOT Qwire) Qwire = std::make_shared<std::vector<std::shared_ptr<TModel_Wire>>>();
		Qwire->push_back(innerWire);
	}

	TopLoc_Location Location;
	auto geometry = BRep_Tool::Surface(forwardFace, Location);

	auto face =
		std::make_shared<TModel_Surface>(geometry, outerWire, Qwire);
	//face->SetFace(theFace);

	return std::move(face);
}

std::vector<std::shared_ptr<tnbLib::TModel_Surface>> 
tnbLib::Cad_Tools::GetSurfaces
(
	const TopoDS_Shape & theShape
)
{
	Standard_Integer K = 0;
	std::vector<std::shared_ptr<TModel_Surface>> list;
	for (
		TopExp_Explorer aFaceExp(theShape.Oriented(TopAbs_FORWARD), TopAbs_FACE);
		aFaceExp.More();
		aFaceExp.Next()
		)
	{
		auto raw = TopoDS::Face(aFaceExp.Current());

		if (raw.IsNull())
		{
			continue;
		}

		auto face = GetSurface(raw);

		face->SetIndex(++K);

		list.push_back(face);
	}

	return std::move(list);
}

std::shared_ptr<tnbLib::Cad_TModel> 
tnbLib::Cad_Tools::MakeSolid
(
	const TopoDS_Shape & theShape,
	const Standard_Real theTolerance
)
{
	auto surfaces = GetSurfaces(theShape);

	auto solid = MakeSolid(surfaces, theTolerance);

	Debug_Null_Pointer(solid);
	if (solid) solid->SetShape(theShape);

	return std::move(solid);
}

namespace tnbLib
{

	namespace tModel
	{

		static Standard_Real squareMaxDistance_1
		(
			const std::shared_ptr<TModel_Edge>& theEdge0,
			const std::shared_ptr<TModel_Edge>& theEdge1
		)
		{
			auto g0 = std::dynamic_pointer_cast<TModel_GeneratedEdge>(theEdge0);
			auto g1 = std::dynamic_pointer_cast<TModel_GeneratedEdge>(theEdge1);
			Debug_Null_Pointer(g0);
			Debug_Null_Pointer(g1);
			Debug_Null_Pointer(g0->Curve());
			Debug_Null_Pointer(g1->Curve());

			const auto& geometry0 = *g0->Curve();
			const auto& geometry1 = *g1->Curve();

			return SquareDistance(geometry0.Value_normParam(0.5), geometry1.Value_normParam(0.5));
		}

		static void MakeStaticChain
		(
			const std::vector<std::shared_ptr<TModel_Edge>>& Edges,
			Entity3d_Chain& Chain
		)
		{
			auto& Points = Chain.Points();
			auto& Indices = Chain.Connectivity();

			Points.resize(2 * Edges.size());
			Indices.reserve(Edges.size());

			Standard_Integer IP = 0;
			for (const auto& x : Edges)
			{
				Debug_Null_Pointer(x);
				auto g = std::dynamic_pointer_cast<TModel_GeneratedEdge>(x);
				Debug_Null_Pointer(g);
				Debug_Null_Pointer(g->Curve());

				const auto& curve = *g->Curve();

				Points[IP] = curve.FirstCoord();
				IP++;

				Points[IP] = curve.LastCoord();
				IP++;

				connectivity::dual edge;
				edge.Value(0) = IP - 1;
				edge.Value(1) = IP;

				Indices.push_back(edge);
			}
		}

		static void Pairing
		(
			const std::vector<std::shared_ptr<TModel_Edge>>& theEdges
		)
		{
			NotImplemented;
			//if (theEdges.size() < 2)
			//{
			//	FatalErrorIn("void Pairing(const edgeList& theEdges)")
			//		<< "Invalid Solid" << endl
			//		<< abort(FatalError);
			//}

			//Adt_AvlTree<std::shared_ptr<TModel_Edge>> tree;
			//tree.SetComparableFunction(&TModel_Edge::IsLess);

			//for (const auto& x : theEdges)
			//	tree.Insert(x);

			//if (tree.IsEmpty())
			//{
			//	FatalErrorIn("void Pairing(const edgeList& theEdges)")
			//		<< "Invalid Solid" << endl
			//		<< abort(FatalError);
			//}

			//std::shared_ptr<TModel_Edge> edge;
			//tree.Root(edge);
			//tree.Remove(edge);

			//while (NOT tree.IsEmpty())
			//{
			//	const auto& vtx0 = edge->Vtx0();
			//	const auto& vtx1 = edge->Vtx1();

			//	std::shared_ptr<TModel_Vertex> vtx;
			//	if (vtx0->NbEdges() <= vtx1->NbEdges())
			//		vtx = vtx0;
			//	else
			//		vtx = vtx1;

			//	const auto& compareList = vtx->Edges();
			//	auto v0 = vtx0->Index();
			//	auto v1 = vtx1->Index();

			//	if (edge->IsRing())
			//	{
			//		auto ring = std::dynamic_pointer_cast<TModel_RingEdge>(edge);
			//		Debug_Null_Pointer(ring);

			//		auto tol2 = ring->Presicion()*ring->Presicion();

			//		for (const auto& w_compare : compareList)
			//		{
			//			auto compare = w_compare.second.lock();
			//			Debug_Null_Pointer(compare);

			//			if (compare IS_EQUAL edge) continue;

			//			auto compareRing = std::dynamic_pointer_cast<TModel_RingEdge>(compare);
			//			if (compareRing)
			//			{
			//				if (squareMaxDistance_1(ring, compareRing) <= tol2)
			//				{
			//					edge->SetPairedEdge(compare);
			//					compare->SetPairedEdge(edge);

			//					tree.Remove(compare);
			//				}
			//			}
			//		}
			//	}
			//	else
			//	{
			//		std::vector<std::shared_ptr<TModel_Edge>> paired;

			//		Debug_Null_Pointer(edge->Curve());
			//		auto tol2 = edge->Presicion()*edge->Presicion();

			//		for (const auto& w_compare : compareList)
			//		{
			//			auto compare = w_compare.second.lock();
			//			Debug_Null_Pointer(compare);

			//			if (compare IS_EQUAL edge) continue;

			//			if (Geo_Tools::IsPairedTwoSegments(v0, v1, compare->Vtx0()->Index(), compare->Vtx1()->Index()))
			//			{
			//				if (squareMaxDistance_1(edge, compare) <= tol2)
			//				{
			//					paired.push_back(compare);
			//				}

			//				//paired.push_back(compare);
			//			}
			//		}

			//		/*if (paired.empty())
			//	{
			//		cout << "nothing found!" << std::endl;
			//	}*/
			//		if (paired.size() > 1)
			//		{
			//			if (edge->PairedEdge().lock())
			//			{
			//				FatalErrorIn("void Pairing(const edgeList& theEdges)")
			//					<< "the solid is not a manifold type"
			//					<< abort(FatalError);
			//			}
			//		}

			//		if (paired.size() IS_EQUAL 1)
			//		{
			//			edge->SetPairedEdge(paired[0]);
			//			paired[0]->SetPairedEdge(edge);
			//		}
			//	}

			//	if (tree.IsEmpty()) break;

			//	tree.Root(edge);
			//	tree.Remove(edge);
			//}
		}

		static void Assembly
		(
			const Entity3d_Chain& theChain,
			const std::vector<std::shared_ptr<TModel_Vertex>>& theVertices,
			const std::vector<std::shared_ptr<TModel_Edge>>& theEdges
		)
		{
			const auto& Indices = theChain.Connectivity();
			if (theEdges.size() NOT_EQUAL Indices.size())
			{
				FatalErrorIn("void Assembly()")
					<< "Contradictory Data" << endl
					<< abort(FatalError);
			}

			forThose(Index, 0, Indices.size() - 1)
			{
				auto v0 = Indices[Index].Value(0);
				auto v1 = Indices[Index].Value(1);

				auto vtx0 = theVertices[Index_Of(v0)];
				auto vtx1 = theVertices[Index_Of(v1)];

				Debug_Null_Pointer(vtx0);
				Debug_Null_Pointer(vtx1);

				Debug_Null_Pointer(theEdges[Index]);

				if (v0 IS_EQUAL v1)
				{
					auto g = std::dynamic_pointer_cast<TModel_RingEdge>(theEdges[Index]);
					Debug_Null_Pointer(g);

					g->Vtx() = vtx0;

					vtx0->ImportToEdges(theEdges[Index]->Index(), theEdges[Index]);
				}
				else
				{
					auto g = std::dynamic_pointer_cast<TModel_SegmentEdge>(theEdges[Index]);
					Debug_Null_Pointer(g);

					g->Vtx0() = vtx0;
					g->Vtx1() = vtx1;

					vtx0->ImportToEdges(theEdges[Index]->Index(), theEdges[Index]);
					vtx1->ImportToEdges(theEdges[Index]->Index(), theEdges[Index]);
				}				

				theEdges[Index]->SetIndex(Index + 1);
			}

			Pairing(theEdges);

			for (const auto& x : theVertices)
			{
				Debug_Null_Pointer(x);

				auto vertex = std::dynamic_pointer_cast<TModel_Vertex>(x);
				Debug_Null_Pointer(vertex);


				const auto& edgesAroundVertex = vertex->Edges();

				for (const auto& edge : edgesAroundVertex)
				{
					Debug_Null_Pointer(edge.second.lock());
					auto x = edge.second.lock();
					vertex->ImportToSurfaces_dup(x->Index(), x->Surface());
				}
			}
		}

		static void MakePointsOnSolid
		(
			const Entity3d_Chain& Chain,
			std::shared_ptr<TModel_CornerManager>& thePointsOnSolid,
			std::vector<std::shared_ptr<TModel_Vertex>>& thePts
		)
		{
			const auto& Points = Chain.Points();

			thePts.reserve(Points.size());

			Standard_Integer K = 0;
			for (const auto& x : Points)
			{
				auto vertex = std::make_shared<TModel_Vertex>(++K, x);
				thePts.push_back(vertex);
			}

			auto block = std::make_shared<Cad_BlockEntity<TModel_Vertex>>("Default Block Point", thePts);
			thePointsOnSolid = std::make_shared<TModel_CornerManager>("Default Block Point", block);
		}

		static void MakePairedEdges
		(
			const std::vector<std::shared_ptr<TModel_Edge>>& theEdges,
			std::shared_ptr<TModel_SegmentManager>& thePairedEdges
		)
		{
			NotImplemented;
			/*Adt_AvlTree<std::shared_ptr<TModel_Edge>> tree;
			tree.SetComparableFunction(&TModel_Edge::IsLess);

			tree.Insert(theEdges);

			std::shared_ptr<TModel_Edge> edge;
			tree.Root(edge);
			tree.Remove(edge);

			std::vector<std::shared_ptr<TModel_Paired>> QPaired;
			Standard_Integer k = 0;

			while (NOT tree.IsEmpty())
			{
				auto generated = std::dynamic_pointer_cast<TModel_GeneratedEdge>(edge);
				Debug_Null_Pointer(generated);

				auto w_paired = generated->PairedEdge();
				auto paired = std::dynamic_pointer_cast<TModel_GeneratedEdge>(w_paired.lock());
				Debug_Null_Pointer(paired);

				if (paired)
				{
					tree.Remove(paired);
				}

				auto pairedOnSolid = std::make_shared<TModel_Paired>(++k, edge, paired);
				QPaired.push_back(pairedOnSolid);

				generated->SetPaired(pairedOnSolid);
				if (paired) paired->SetPaired(pairedOnSolid);

				if (tree.IsEmpty()) break;

				tree.Root(edge);
				tree.Remove(edge);
			}

			auto block = std::make_shared<Cad_BlockEntity<TModel_Paired>>("Default Block Edge", QPaired);
			thePairedEdges = std::make_shared<TModel_SegmentManager>("Default Block Edge", block);*/
		}

		static void MarchingOnShell
		(
			const std::shared_ptr<TModel_Surface>& Face,
			Adt_AvlTree<std::shared_ptr<TModel_Surface>>& tree,
			std::vector<std::shared_ptr<TModel_Entity>>& QShell
		)
		{
			NotImplemented;
			/*tree.Remove(Face);
			QShell.push_back(Face);

			const auto edges = Face->RetrieveEdges();

			std::vector<std::shared_ptr<TModel_Edge>> pairedList;
			pairedList.reserve(edges.size());

			std::shared_ptr<TModel_Edge> null = nullptr;

			for (const auto& e : edges)
			{
				Debug_Null_Pointer(e);
				auto x = std::dynamic_pointer_cast<TModel_GeneratedEdge>(e);
				Debug_Null_Pointer(x);

				pairedList.push_back(x->PairedEdge().lock());
				x->SetPairedEdge(null);
			}

			for (const auto& x : pairedList)
			{
				if (x)
				{
					auto g = std::dynamic_pointer_cast<TModel_GeneratedEdge>(x);
					Debug_Null_Pointer(g);

					auto paired = std::dynamic_pointer_cast<TModel_GeneratedEdge>(g->PairedEdge().lock());
					if (paired)
					{
						Debug_Null_Pointer(paired->Surface().lock());
						MarchingOnShell(paired->Surface().lock(), tree, QShell);
					}
				}
			}*/
		}


		static void MakeFaces
		(
			const std::vector<std::shared_ptr<TModel_Surface>>& theList,
			std::shared_ptr<TModel_FaceManager>& theFaces
		)
		{
			std::vector<std::shared_ptr<TModel_Surface>> Faces(theList.size());
			forThose(Index, 0, theList.size() - 1)
				Faces[Index] = theList[Index];

			auto block = std::make_shared<Cad_BlockEntity<TModel_Surface>>("Default Block Surface", Faces);
			theFaces = std::make_shared<TModel_FaceManager>("Default Block Surface", block);
		}


		static void LinkEdges(const std::shared_ptr<TModel_SegmentManager>& theEdges)
		{
			NotImplemented;
			/*Debug_Null_Pointer(theEdges);

			std::vector<std::shared_ptr<TModel_Paired>> edges;
			theEdges->RetrieveEntitiesTo(edges);

			for (const auto& paired : edges)
			{
				Debug_Null_Pointer(paired);

				auto edge0 = std::dynamic_pointer_cast<TModel_GeneratedEdge>(paired->Edge0());
				auto edge1 = std::dynamic_pointer_cast<TModel_GeneratedEdge>(paired->Edge1());

				if (NOT edge0)
				{
					FatalErrorIn("void LinkEdges(const entityManager_ptr& theEdges)")
						<< "Null pointer has been encountered!" << endl
						<< abort(FatalError);
				}

				if (edge1)
				{
					edge0->SetPairedEdge(edge1);
					edge1->SetPairedEdge(edge0);
				}
			}*/
		}
	}
}

std::shared_ptr<tnbLib::Cad_TModel> 
tnbLib::Cad_Tools::MakeSolid
(
	const std::vector<std::shared_ptr<TModel_Surface>>& theSurfaces,
	const Standard_Real theTolerance
)
{
	auto solid = std::make_shared<Cad_TModel>();

	//auto box = BoundingBox(theSurfaces);

	const auto tol = theTolerance; /** box.Diameter();*/
	auto EdgesOnSolid = RetrieveNonSingularEdges(theSurfaces);

	Standard_Integer K = 0;
	for (auto& x : EdgesOnSolid)
	{
		x->SetIndex(++K);
		x->SetPrecision(tol);
	}

	Entity3d_Chain chain;
	tModel::MakeStaticChain(EdgesOnSolid, chain);

	Merge3d_Chain merge;
	merge.InfoAlg().SetRadius(tol);
	merge.Import(chain);

	merge.Perform();

	const auto& merged = *merge.Merged();

	std::vector<std::shared_ptr<TModel_Vertex>> vertices;
	tModel::MakePointsOnSolid(merged, solid->CornersRef(), vertices);

	Debug_Null_Pointer(solid->Corners());

	K = 0;
	for (auto& x : vertices)
	{
		++K;

		Debug_Null_Pointer(x);
		x->SetIndex(K);
		x->SetName("Vertex " + std::to_string(K));
	}

	tModel::Assembly(merged, vertices, EdgesOnSolid);

	tModel::MakePairedEdges(EdgesOnSolid, solid->SegmentsRef());

	Debug_Null_Pointer(solid->Segments());

	tModel::MakeFaces(theSurfaces, solid->FacesRef());

	Debug_Null_Pointer(solid->Faces());

	tModel::LinkEdges(solid->Segments());

	SetPrecision(solid);

	return std::move(solid);
}

std::vector<std::shared_ptr<tnbLib::TModel_Edge>> 
tnbLib::Cad_Tools::RetrieveNonSingularEdges
(
	const std::vector<std::shared_ptr<TModel_Surface>>& theSurfaces
)
{
	std::vector<std::shared_ptr<TModel_Edge>> gedges;
	for (const auto& x : theSurfaces)
	{
		Debug_Null_Pointer(x);
		const auto& face = *x;

		const auto edges = face.RetrieveEdges();
		for (const auto& edge : edges)
		{
			Debug_Null_Pointer(edge);
			if (NOT edge->IsDegenerated())
			{
				gedges.push_back(edge);
			}
		}
	}
	return std::move(gedges);
}

Handle(Poly_Triangulation)
tnbLib::Cad_Tools::RetrieveTriangulation
(
	const TopoDS_Face & theFace
)
{
	TopLoc_Location Loc;
	auto Triangulation = BRep_Tool::Triangulation(theFace, Loc);
	return std::move(Triangulation);
}

std::vector<TopoDS_Edge> 
tnbLib::Cad_Tools::RetrieveEdges
(
	const TopoDS_Shape & theShape
)
{
	std::vector<TopoDS_Edge> edges;
	for
		(
			TopExp_Explorer explorer(theShape, TopAbs_EDGE);
			explorer.More();
			explorer.Next()
			)
	{
		auto edge = TopoDS::Edge(explorer.Current());
		if (NOT edge.IsNull())
		{
			edges.push_back(edge);
		}
	}
	return std::move(edges);
}

#include <Pln_Tools.hxx>

std::vector<Handle(Geom2d_Curve)> 
tnbLib::Cad_Tools::RetrieveParaCurves
(
	const std::vector<TopoDS_Edge>& theEdges,
	const gp_Ax2 & theSystem
)
{
	Handle(Geom_Plane) plane = new Geom_Plane(gp_Pln(theSystem));
	Debug_Null_Pointer(plane);

	TopLoc_Location loc;

	std::vector<Handle(Geom2d_Curve)> curves;
	curves.reserve(theEdges.size());

	for (const auto& x : theEdges)
	{
		Standard_Real first, last;
		auto curve = BRep_Tool::CurveOnPlane(x, plane, loc, first, last);

		if (curve.IsNull())
		{
			FatalErrorIn("std::vector<Handle(Geom2d_Curve)> Cad_Tools::RetrieveParaCurves(Args...)")
				<< "Failed to Calculate the parametric curve" << endl
				<< abort(FatalError);
		}

		auto bounded = Pln_Tools::ConvertToTrimmedCurve(curve, first, last);
		Debug_Null_Pointer(bounded);

		curves.push_back(std::move(bounded));
	}
	return std::move(curves);
}

std::vector<Handle(Geom2d_Curve)> 
tnbLib::Cad_Tools::RetrieveParaCurves
(
	const std::vector<TopoDS_Edge>& theEdges, 
	const Handle(Geom_Surface) theSurface
)
{
	TopLoc_Location loc;

	std::vector<Handle(Geom2d_Curve)> curves;
	curves.reserve(theEdges.size());

	for (const auto& x : theEdges)
	{
		Standard_Real first, last;
		auto curve = BRep_Tool::CurveOnSurface(x, theSurface, loc, first, last);

		if (curve.IsNull())
		{
			FatalErrorIn("std::vector<Handle(Geom2d_Curve)> Cad_Tools::RetrieveParaCurves(Args...)")
				<< "Failed to Calculate the parametric curve" << endl
				<< abort(FatalError);
		}

		auto bounded = Pln_Tools::ConvertToTrimmedCurve(curve, first, last);
		Debug_Null_Pointer(bounded);

		curves.push_back(std::move(bounded));
	}
	return std::move(curves);
}

std::vector<std::shared_ptr<tnbLib::TModel_Edge>> 
tnbLib::Cad_Tools::RetrieveEdges(const std::vector<std::shared_ptr<TModel_Surface>>& theSurfaces)
{
	std::vector<std::shared_ptr<TModel_Edge>> edges;
	for (const auto& x : theSurfaces)
	{
		Debug_Null_Pointer(x);
		auto surfEdges = x->RetrieveEdges();
		for (auto& e : surfEdges)
		{
			edges.push_back(std::move(e));
		}
	}
	return std::move(edges);
}

std::vector<std::shared_ptr<tnbLib::TModel_Edge>> 
tnbLib::Cad_Tools::RetrieveFreeEdges
(
	const std::shared_ptr<Cad_TModel>& theSolid
)
{
	if (NOT theSolid)
	{
		FatalErrorIn(FunctionSIG)
			<< "the solid is null" << endl
			<< abort(FatalError);
	}

	std::vector<std::shared_ptr<TModel_Edge>> edges;
	for (const auto& x : theSolid->RetrieveSegments())
	{
		Debug_Null_Pointer(x);
		if (NOT x->IsManifold())
		{
			auto nonMan = std::dynamic_pointer_cast<TModel_nonManifoldPaired>(x);
			Debug_Null_Pointer(nonMan);

			if (nonMan->NbEdges() IS_EQUAL 1)
			{
				for (const auto& e : nonMan->Edges())
				{
					Debug_Null_Pointer(e.second);
					edges.push_back(e.second);
				}
			}
		}
	}
	return std::move(edges);
}

std::vector<std::shared_ptr<tnbLib::TModel_Paired>> 
tnbLib::Cad_Tools::RetrieveManifoldEdges
(
	const std::shared_ptr<Cad_TModel>& theSolid
)
{
	if (NOT theSolid)
	{
		FatalErrorIn(FunctionSIG)
			<< "the solid is null" << endl
			<< abort(FatalError);
	}

	std::vector<std::shared_ptr<TModel_Paired>> edges;
	for (const auto& x : theSolid->RetrieveSegments())
	{
		Debug_Null_Pointer(x);
		if (x->IsManifold())
		{
			edges.push_back(x);
		}
	}
	return std::move(edges);
}

std::vector<Handle(Poly_Triangulation)> 
tnbLib::Cad_Tools::RetrieveTriangulation
(
	const TopoDS_Shape & theShape
)
{
	std::vector<Handle(Poly_Triangulation)> tris;
	for
		(
			TopExp_Explorer Explorer(theShape, TopAbs_FACE);
			Explorer.More();
			Explorer.Next()
			)
	{
		auto tri = RetrieveTriangulation(TopoDS::Face(Explorer.Current()));
		if (tri)
			tris.push_back(tri);
	}
	return std::move(tris);
}

std::vector<std::shared_ptr<tnbLib::TModel_Vertex>> 
tnbLib::Cad_Tools::RetrieveVertices
(
	const std::shared_ptr<TModel_Surface>& theSurface
)
{
	std::vector<std::shared_ptr<TModel_Vertex>> vertices;
	const auto edges = theSurface->RetrieveEdges();
	std::map<Standard_Integer, std::shared_ptr<TModel_Vertex>> regMap;
	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);
		auto vtxs = x->RetrieveVertices();
		for (const auto& v : vtxs)
		{
			Debug_Null_Pointer(v);
			auto iter = regMap.find(v->Index());
			if (iter IS_EQUAL regMap.end())
			{
				auto paired = std::make_pair(v->Index(), v);
				auto insert = regMap.insert(std::move(paired));
				if (NOT insert.second)
				{
					// duplicate data has been detected [1/11/2022 Amir]
					// do nothing! [1/11/2022 Amir]
				}
			}
		}
	}
	vertices.reserve(regMap.size());
	for (const auto& x : regMap)
	{
		Debug_Null_Pointer(x.second);
		vertices.push_back(std::move(x.second));
	}
	return std::move(vertices);
}

std::vector<TopoDS_Face> 
tnbLib::Cad_Tools::RetrieveFaces
(
	const TopoDS_Shape & theShape
)
{
	std::vector<TopoDS_Face> faces;
	for
		(
			TopExp_Explorer Explorer(theShape, TopAbs_FACE);
			Explorer.More();
			Explorer.Next()
			)
	{
		auto face = TopoDS::Face(Explorer.Current());
		if (NOT face.IsNull())
		{
			faces.push_back(std::move(face));
		}
	}
	return std::move(faces);
}

tnbLib::Entity2d_Metric1 
tnbLib::Cad_Tools::CalcMetric
(
	const Pnt2d& thePnt,
	const Handle(Geom_Surface)& theSurface
)
{
	Debug_Null_Pointer(theSurface);

	gp_Vec D1U, D1V;
	gp_Pnt Pt;

	theSurface->D1(thePnt.X(), thePnt.Y(), Pt, D1U, D1V);

	Standard_Real A = D1U.Dot(D1U);
	Standard_Real B = D1U.Dot(D1V);
	Standard_Real C = D1V.Dot(D1V);

	Entity2d_Metric1 m(A, B, C);
	return std::move(m);
}

tnbLib::Entity2d_Metric1 
tnbLib::Cad_Tools::CalcMetric
(
	const Standard_Real theX,
	const Standard_Real theY,
	const Handle(Geom_Surface)& theSurface
)
{
	Debug_Null_Pointer(theSurface);

	gp_Vec D1U, D1V;
	gp_Pnt Pt;

	theSurface->D1(theX, theY, Pt, D1U, D1V);

	Standard_Real A = D1U.Dot(D1U);
	Standard_Real B = D1U.Dot(D1V);
	Standard_Real C = D1V.Dot(D1V);

	Entity2d_Metric1 m(A, B, C);
	return std::move(m);
}

tnbLib::Entity2d_Metric1
tnbLib::Cad_Tools::CalcMetric
(
	const Pnt2d& thePnt,
	const Handle(Geom_Surface)& theSurface,
	Standard_Real(*sizeFun)(const Pnt3d&)
)
{
	Debug_Null_Pointer(theSurface);

	gp_Vec D1U, D1V;
	gp_Pnt Pt;

	theSurface->D1(thePnt.X(), thePnt.Y(), Pt, D1U, D1V);

	Standard_Real A = D1U.Dot(D1U);
	Standard_Real B = D1U.Dot(D1V);
	Standard_Real C = D1V.Dot(D1V);

	const auto h = sizeFun(Pt);
	Debug_If_Condition(h <= gp::Resolution());

	const auto invH = 1.0 / (h * h);

	Entity2d_Metric1 m(invH * A, invH * B, invH * C);
	return std::move(m);
}

tnbLib::Entity2d_Metric1
tnbLib::Cad_Tools::CalcMetric
(
	const Standard_Real theX,
	const Standard_Real theY,
	const Handle(Geom_Surface)& theSurface,
	Standard_Real(*sizeFun)(const Pnt3d&)
)
{
	Debug_Null_Pointer(theSurface);

	gp_Vec D1U, D1V;
	gp_Pnt Pt;

	theSurface->D1(theX, theY, Pt, D1U, D1V);

	Standard_Real A = D1U.Dot(D1U);
	Standard_Real B = D1U.Dot(D1V);
	Standard_Real C = D1V.Dot(D1V);

	const auto h = sizeFun(Pt);
	Debug_If_Condition(h <= gp::Resolution());

	const auto invH = 1.0 / (h * h);

	Entity2d_Metric1 m(invH * A, invH * B, invH * C);
	return std::move(m);
}

Standard_Real 
tnbLib::Cad_Tools::CalcLength
(
	const Entity2d_Polygon & thePoly,
	const Geom_Surface & theSurf
)
{
#ifdef _DEBUG
	Entity2d_Polygon::Check(thePoly);
#endif // _DEBUG
	auto domain = ParametricDomain(theSurf);
	Standard_Real d = 0;
	const auto& pts = thePoly.Points();
	for (size_t i = 1; i < pts.size(); i++)
	{
		const auto& p0 = pts[i - 1];
		const auto& p1 = pts[i];

		auto P0 = CalcCoord(p0, theSurf);
		auto P1 = CalcCoord(p1, theSurf);

		d += Distance(P0, P1);
	}
	return d;
}

Standard_Real 
tnbLib::Cad_Tools::CalcSegmentLength
(
	const Pnt2d & theP0, 
	const Pnt2d & theP1, 
	const Geom_Surface & theSurf
)
{
	const auto p0 = CalcCoord(theP0, theSurf);
	const auto p1 = CalcCoord(theP1, theSurf);
	return p0.Distance(p1);
}

void tnbLib::Cad_Tools::Connect
(
	const std::shared_ptr<TModel_Surface>& theSurface
)
{
	Debug_Null_Pointer(theSurface);

	const auto edges = theSurface->RetrieveEdges();
	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);
		x->SetSurface(theSurface);
	}

	const auto vertices = Cad_Tools::RetrieveVertices(theSurface);
	for (const auto& x : vertices)
	{
		Debug_Null_Pointer(x);
		x->ImportToSurfaces(theSurface->Index(), theSurface);
	}
}

void tnbLib::Cad_Tools::Connect
(
	const std::shared_ptr<TModel_Edge>& theEdge
)
{
	Debug_Null_Pointer(theEdge);
	const auto vertices = theEdge->RetrieveVertices();
	for (const auto& x : vertices)
	{
		Debug_Null_Pointer(x);
		x->ImportToEdges(theEdge->Index(), theEdge);
	}
}

void tnbLib::Cad_Tools::Connect
(
	const std::shared_ptr<TModel_Wire>& theWire
)
{
	Debug_Null_Pointer(theWire);
	Debug_Null_Pointer(theWire->CmpEdge());

	const auto& edges = theWire->CmpEdge()->Edges();
	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);
		x->SetWire(theWire);
	}
}

void tnbLib::Cad_Tools::Connect
(
	const std::shared_ptr<TModel_Paired>& thePaired
)
{
	const auto& edges = thePaired->RetrieveEdges();
	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);
		auto g = std::dynamic_pointer_cast<TModel_GeneratedEdge>(x);
		Debug_Null_Pointer(g);

		g->SetPaired(thePaired);
	}
}

void tnbLib::Cad_Tools::Connect
(
	const std::shared_ptr<TModel_ManifoldPaired>& thePaired
)
{
	Debug_Null_Pointer(thePaired);
	const auto& e0 = thePaired->Edge0();
	const auto& e1 = thePaired->Edge1();

	Debug_Null_Pointer(e0);
	Debug_Null_Pointer(e1);

	auto g0 = std::dynamic_pointer_cast<TModel_GeneratedEdge>(e0);
	Debug_Null_Pointer(g0);

	auto g1 = std::dynamic_pointer_cast<TModel_GeneratedEdge>(e1);
	Debug_Null_Pointer(g1);

	g0->SetPairedEdge(g1);
	g1->SetPairedEdge(g0);
}

void tnbLib::Cad_Tools::Connect
(
	const std::shared_ptr<Cad_TModel>& theModel
)
{
	Debug_Null_Pointer(theModel);
	const auto surfaces = theModel->RetrieveFaces();

	for (const auto& x : surfaces)
	{
		Debug_Null_Pointer(x);
		Connect(x);

		const auto& outer = x->Outer();
		Debug_Null_Pointer(outer);

		Connect(outer);

		if (x->Inner())
		{
			for (const auto& wire : *x->Inner())
			{
				Connect(wire);
			}
		}

		auto edges = x->RetrieveEdges();
		for (const auto& e : edges)
		{
			Debug_Null_Pointer(e);
			Connect(e);
		}
	}

	const auto edges = theModel->RetrieveSegments();
	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);
		Connect(x);
	}

	const auto manifolds = Cad_Tools::RetrieveManifoldEdges(theModel);

	for (const auto& x : manifolds)
	{
		Debug_Null_Pointer(x);
		Connect(x);
	}
}

void tnbLib::Cad_Tools::SetPrecision
(
	const std::shared_ptr<Cad_TModel>& theSolid
)
{
	auto vertices = theSolid->RetrieveCorners();
	for (const auto& x : vertices)
	{
		Debug_Null_Pointer(x);
		x->SetPrecision(CalcPrecision(*x));
	}
}

void tnbLib::Cad_Tools::ExportToIGES
(
	const word & theUnit,
	const TopoDS_Shape & theShape, 
	const fileName & theName
)
{
	IGESControl_Controller::Init();

	IGESControl_Writer Writer(theUnit.c_str(), 0);
	Writer.AddShape(theShape);
	Writer.ComputeModel();

	Standard_Boolean OK = Writer.Write(theName.c_str());

	if (NOT OK)
	{
		FatalErrorIn("void ExportToIGES()")
			<< "Unable to export the model" << endl
			<< abort(FatalError);
	}
}

void tnbLib::Cad_Tools::ExportToSTEP
(
	const TopoDS_Shape & theShape, 
	const fileName & name
)
{
	STEPControl_Controller::Init();

	STEPControl_Writer Writer;
	Writer.Transfer(theShape, STEPControl_ManifoldSolidBrep);

	Standard_Boolean OK = Writer.Write(name.c_str());

	if (NOT OK)
	{
		FatalErrorIn("void ExportToSTEP()")
			<< "Unable to export the model" << endl
			<< abort(FatalError);
	}
}