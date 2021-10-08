#include <Cad_ConicApexMaker.hxx>

#include <Cad_PolesNetPrcssr.hxx>
#include <Geo_Tools.hxx>
#include <Entity_Segment.hxx>
#include <Pnt2d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <StdFail_NotDone.hxx>
#include <gp_Pln.hxx>
#include <gp_Lin.hxx>
#include <Geom_Plane.hxx>
#include <Geom_Line.hxx>
#include <Geom_BSplineSurface.hxx>
#include <GeomAPI_ProjectPointOnSurf.hxx>
#include <GeomAPI_ProjectPointOnCurve.hxx>

std::pair
<
	std::vector<typename tnbLib::Cad_ConicApexMaker::Pw>,
	std::vector<typename tnbLib::Cad_ConicApexMaker::Pw>
> 
tnbLib::Cad_ConicApexMaker::RetrieveBoundary() const
{
	auto prcssr = std::make_shared<Cad_PolesNetPrcssr>(Surface());
	Debug_Null_Pointer(prcssr);

	switch (theBoundary_)
	{
	case tnbLib::Cad_ConicApexMaker::bndPatch::U0:
	{
		auto B0 = prcssr->PoleRow(1);
		auto B1 = prcssr->FirstPoleRow();

		auto t = std::make_pair(std::move(B0), std::move(B1));
		return std::move(t);
	}
	case tnbLib::Cad_ConicApexMaker::bndPatch::Un:
	{
		auto B0 = prcssr->PoleRow(prcssr->NbRows() - 2);
		auto B1 = prcssr->LastPoleRow();

		auto t = std::make_pair(std::move(B0), std::move(B1));
		return std::move(t);
	}
	case tnbLib::Cad_ConicApexMaker::bndPatch::V0:
	{
		auto B0 = prcssr->PoleColumn(1);
		auto B1 = prcssr->FirstPoleColumn();

		auto t = std::make_pair(std::move(B0), std::move(B1));
		return std::move(t);
	}
	case tnbLib::Cad_ConicApexMaker::bndPatch::Vn:
	{
		auto B0 = prcssr->PoleColumn(prcssr->NbColumns() - 2);
		auto B1 = prcssr->LastPoleColumn();

		auto t = std::make_pair(std::move(B0), std::move(B1));
		return std::move(t);
	}
	default:
		FatalErrorIn(FunctionSIG)
			<< "unrecognized type of boundary has been detected!" << endl
			<< abort(FatalError);

		return std::make_pair(std::vector<Pw>(), std::vector<Pw>());
	}
}

std::vector<std::pair<Standard_Real, Standard_Integer>>
tnbLib::Cad_ConicApexMaker::RetrieveBoundaryKnots() const
{
	switch (theBoundary_)
	{
	case tnbLib::Cad_ConicApexMaker::bndPatch::U0:
	case tnbLib::Cad_ConicApexMaker::bndPatch::Un:
	{
		const auto& knots = Surface()->VKnots();
		const auto& mults = Surface()->VMultiplicities();

		std::vector<std::pair<Standard_Real, Standard_Integer>> Us;
		Us.reserve(knots.Size());
		for (size_t i = 1; i <= knots.Size(); i++)
		{
			auto paired = std::make_pair(knots.Value(i), mults.Value(i));
			Us.push_back(std::move(paired));
		}
		return std::move(Us);
	}
	case tnbLib::Cad_ConicApexMaker::bndPatch::V0:
	case tnbLib::Cad_ConicApexMaker::bndPatch::Vn:
	{
		const auto& knots = Surface()->UKnots();
		const auto& mults = Surface()->UMultiplicities();

		std::vector<std::pair<Standard_Real, Standard_Integer>> Us;
		Us.reserve(knots.Size());
		for (size_t i = 1; i <= knots.Size(); i++)
		{
			auto paired = std::make_pair(knots.Value(i), mults.Value(i));
			Us.push_back(std::move(paired));
		}
		return std::move(Us);
	}
	default:
		FatalErrorIn(FunctionSIG)
			<< "unrecognized type of boundary has been detected!" << endl
			<< abort(FatalError);
		return std::vector<std::pair<Standard_Real, Standard_Integer>>();
	}
}

Standard_Integer 
tnbLib::Cad_ConicApexMaker::RetrieveBoundaryDegree() const
{
	switch (theBoundary_)
	{
	case tnbLib::Cad_ConicApexMaker::bndPatch::U0:
	case tnbLib::Cad_ConicApexMaker::bndPatch::Un:
	{
		return Surface()->VDegree();
	}
	case tnbLib::Cad_ConicApexMaker::bndPatch::V0:
	case tnbLib::Cad_ConicApexMaker::bndPatch::Vn:
	{
		return Surface()->UDegree();
	}
	default:
		FatalErrorIn(FunctionSIG)
			<< "unrecognized type of boundary has been detected!" << endl
			<< abort(FatalError);
		return 0;
	}
}

tnbLib::Pnt3d
tnbLib::Cad_ConicApexMaker::RetrieveOrigin() const
{
	return theAxis_.Location();
}

namespace tnbLib
{

	const Pnt3d& RetrievePoint(const Cad_ConicApexMaker::Pw& pw)
	{
		return pw.first;
	}

	auto RetrieveWeight(const Cad_ConicApexMaker::Pw& pw)
	{
		return pw.second;
	}

	std::vector<Dir3d> CalcOrginNormals
	(
		const Dir3d& n0, 
		const gp_Ax1& ax,
		const Standard_Real dTheta,
		const Standard_Integer nth
	)
	{
		std::vector<Dir3d> normals;
		normals.reserve(nth);

		for (size_t i = 0; i < nth; i++)
		{
			auto theta = i * dTheta;

			gp_Trsf tr;
			tr.SetRotation(ax, theta);

			auto n = n0.Transformed(tr);
			normals.push_back(std::move(n));
		}
		return std::move(normals);
	}

	auto CalcSurfNormals
	(
		const std::vector<Cad_ConicApexMaker::Pw>& theBnds,
		const Pnt3d& origin,
		const std::vector<Dir3d>& ns
	)
	{
		std::vector<Dir3d> normals;
		normals.reserve(theBnds.size());

		for (size_t i = 0; i < theBnds.size(); i++)
		{
			Dir3d v(origin, RetrievePoint(theBnds[i]));
			auto n = ns[i].Crossed(v);
			normals.push_back(n);
		}
		return std::move(normals);
	}

	auto CreatePlane(const Pnt3d& origin, const Dir3d& normal)
	{
		gp_Pln pl(origin, normal);
		
		Handle(Geom_Plane) myPlane = new Geom_Plane(pl);
		return std::move(myPlane);
	}

	auto ProjectPoint(const Pnt3d& P3, const Handle(Geom_Plane)& pl)
	{
		GeomAPI_ProjectPointOnSurf alg;
		alg.Init(P3, pl);
		alg.Perform(P3);

		if (alg.NbPoints() NOT_EQUAL 1)
		{
			FatalErrorIn(FunctionSIG)
				<< "something went wrong!" << endl
				<< abort(FatalError);
		}
		Standard_Real u, v;
		alg.LowerDistanceParameters(u, v);

		Pnt2d pt(u, v);
		return std::move(pt);
	}

	Entity_Segment<Pnt2d> ProjectSegment(const Entity_Segment<const Pnt3d&>& seg, const Handle(Geom_Plane)& pl)
	{
		auto p0 = ProjectPoint(seg.P0(), pl);
		auto p1 = ProjectPoint(seg.P1(), pl);

		Entity_Segment<Pnt2d> seg2(std::move(p0), std::move(p1));
		return std::move(seg2);
	}

	Entity_Segment<Pnt2d> ProjectSegment(const Pnt3d& origin, const Dir3d& dir, const Handle(Geom_Plane)& pl)
	{
		auto pd = origin + Pnt3d(dir.XYZ());

		auto p0 = ProjectPoint(origin, pl);
		auto p1 = ProjectPoint(pd, pl);

		Entity_Segment<Pnt2d> seg(std::move(p0), std::move(p1));
		return std::move(seg);
	}

	auto CalcDir(const Entity_Segment<Pnt2d>& ent)
	{
		Dir2d dir(ent.P1(), ent.P0());
		return std::move(dir);
	}

	auto CalcCorner
	(
		const Pnt3d& B0, 
		const Pnt3d& B1, 
		const Pnt3d& origin,
		const Dir3d& dir, 
		const Handle(Geom_Plane)& pl,
		const Standard_Real tol
	)
	{
		try
		{
			auto e0 = ProjectSegment(Entity_Segment<const Pnt3d&>(B0, B1), pl);
			auto e1 = ProjectSegment(origin, dir, pl);

			auto intP = Geo_Tools::IntersectionTwoLines(e0.P0(), CalcDir(e0), e1.P0(), CalcDir(e1), tol);

			auto pnt = pl->Value(intP.X(), intP.Y());
			return std::move(pnt);
		}
		catch (const error& x)
		{
			FatalErrorIn(FunctionSIG)
				<< x.message() << endl
				<< abort(FatalError);
			return gp_Pnt();
		}
	}

	auto ProjectPoint(const Pnt3d& pt, const Handle(Geom_Line)& l)
	{
		GeomAPI_ProjectPointOnCurve alg;
		alg.Init(pt, l);
		alg.Perform(pt);

		if (alg.NbPoints() NOT_EQUAL 1)
		{
			FatalErrorIn(FunctionSIG)
				<< "something went wrong: unable to calculate the projected point" << endl
				<< abort(FatalError);
		}
		return alg.NearestPoint();
	}

	auto CalcNormalBoundaryOfSurf(const Pnt3d& p0, const Pnt3d& p1, const gp_Ax1& ax)
	{
		try
		{
			Handle(Geom_Line) line = new Geom_Line(ax);

			auto pp0 = ProjectPoint(p0, line);
			auto pp1 = ProjectPoint(p1, line);

			auto v0 = p0 - pp0;
			auto v1 = p1 - pp1;
			auto n = Dir3d(CrossProduct(v0, v1).XYZ());
			return std::move(n);
		}
		catch (const Standard_Failure& x)
		{
			FatalErrorIn(FunctionSIG)
				<< x.GetMessageString() << endl
				<< abort(FatalError);
			return Dir3d();
		}
	}

	auto ReverseBoundary(const Pnt3d& p0, const Pnt3d& p1, const gp_Ax1& ax)
	{
		auto n = CalcNormalBoundaryOfSurf(p0, p1, ax);
		if (n.Dot(ax.Direction()) < 0.0)
		{
			return Standard_True;
		}
		else
		{
			return Standard_False;
		}
	}

	auto RetrieveVectorBoundaryOfSurf(const std::vector<Cad_ConicApexMaker::Pw>& Bs, const Standard_Real tol)
	{
		for (size_t i = 1; i < Bs.size(); i++)
		{
			const auto& b0 = RetrievePoint(Bs[i - 1]);
			const auto& b1 = RetrievePoint(Bs[i]);

			if (b0.Distance(b1) <= tol)
			{
				/*do nothing*/
			}
			else
			{
				auto p0 = b0;
				auto p1 = b1;

				auto t = std::make_pair(std::move(p0), std::move(p1));
				return std::move(t);
			}
		}
		FatalErrorIn(FunctionSIG)
			<< "invalid boundary edge has been detected!" << endl
			<< abort(FatalError);
		return std::make_pair(Pnt3d(), Pnt3d());
	}

	auto HasToReverseBoundaryEdge
	(
		const std::vector<Cad_ConicApexMaker::Pw>& Bs, 
		const gp_Ax1& ax,
		const Standard_Real tol
	)
	{
		const auto[p0, p1] = RetrieveVectorBoundaryOfSurf(Bs, tol);

		if (ReverseBoundary(p0, p1, ax))
		{
			return Standard_True;
		}
		return Standard_False;
	}

	auto CalcSpanAngle
	(
		const std::vector<Cad_ConicApexMaker::Pw>& theBnds, 
		const gp_Ax1& ax,
		const Standard_Real tol
	)
	{
		const auto& P0 = RetrievePoint(FirstItem(theBnds));
		const auto& P1 = RetrievePoint(LastItem(theBnds));

		Handle(Geom_Line) line = new Geom_Line(ax);
		auto pp0 = ProjectPoint(P0, line);
		auto pp1 = ProjectPoint(P1, line);

		Vec3d v0(pp0, P0);
		Vec3d v1(pp1, P1);

		if (v0.Magnitude() <= tol)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "null magnitude vector has been detected!" << endl
				<< abort(FatalError);
		}

		if (v1.Magnitude() <= tol)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "null magnitude vector has been detected!" << endl
				<< abort(FatalError);
		}

		auto cross = v0.Crossed(v1);
		if (cross.Magnitude() <= tol)
		{
			if (v0.Dot(v1) >= 0)
			{
				auto t = std::make_pair(Dir3d(v0), 2 * M_PI);
				return std::move(t);
			}
			else
			{
				auto t = std::make_pair(Dir3d(v0), M_PI);
				return std::move(t);
			}
		}
		else
		{
			if (cross.Dot(ax.Direction()) <= 0.0)
			{
				auto t = std::make_pair(Dir3d(v0), 2 * M_PI - v0.Angle(v1));
				return std::move(t);
			}
			else
			{
				auto t = std::make_pair(Dir3d(v0), v0.Angle(v1));
				return std::move(t);
			}
		}
	}

	auto RetrievePoles
	(
		const std::vector<Cad_ConicApexMaker::Pw>& Bs, 
		const std::vector<Pnt3d>& corners,
		const Pnt3d& origin
	)
	{
		const auto nbU = (Standard_Integer)Bs.size();
		const auto nbV = (Standard_Integer)3;
		TColgp_Array2OfPnt poles(1, nbU, 1, nbV);
		for (Standard_Integer i = 1; i <= nbU; i++)
		{
			poles.SetValue(i, 1, origin);
			poles.SetValue(i, 2, corners[i - 1]);
			poles.SetValue(i, 3, RetrievePoint(Bs[i - 1]));
		}
		return std::move(poles);
	}

	auto RetrieveWeights(const std::vector<Cad_ConicApexMaker::Pw>& Bs)
	{
		const auto nbU = (Standard_Integer)Bs.size();
		const auto nbV = (Standard_Integer)3;

		TColStd_Array2OfReal ws(1, nbU, 1, nbV);
		for (Standard_Integer i = 1; i <= nbU; i++)
		{
			ws.SetValue(i, 1, 1.0);
			ws.SetValue(i, 2, 1.0);
			ws.SetValue(i, 3, RetrieveWeight(Bs[i - 1]));
		}
		return std::move(ws);
	}

	auto RetrieveKnots(const std::vector<std::pair<Standard_Real, Standard_Integer>>& knots)
	{
		TColStd_Array1OfReal Us(1, (Standard_Integer)knots.size());
		for (Standard_Integer i = 1; i <= knots.size(); i++)
		{
			Us.SetValue(i, knots[i - 1].first);
		}

		TColStd_Array1OfInteger mul(1, (Standard_Integer)knots.size());
		for (Standard_Integer i = 1; i <= knots.size(); i++)
		{
			mul.SetValue(i, knots[i - 1].second);
		}
		auto t = std::make_pair(std::move(Us), std::move(mul));
		return std::move(t);
	}

	auto CreateApex
	(
		const std::vector<Cad_ConicApexMaker::Pw>& Bs, 
		const std::vector<std::pair<Standard_Real, Standard_Integer>>& knots, 
		const Standard_Integer bDeg, 
		const std::vector<Pnt3d>& corners, 
		const Pnt3d& origin
	)
	{
		const auto poles = RetrievePoles(Bs, corners, origin);
		const auto weights = RetrieveWeights(Bs);
		const auto[uKnots, uMults] = RetrieveKnots(knots);

		const auto vDeg = 2;
		TColStd_Array1OfReal vKnots(1, 2);
		vKnots.SetValue(1, 0.0);
		vKnots.SetValue(2, 1.0);

		TColStd_Array1OfInteger vMults(1, 2);
		vMults.SetValue(1, 3);
		vMults.SetValue(2, 3);

		try
		{
			Handle(Geom_BSplineSurface) mySurf = 
				new Geom_BSplineSurface
				(
					poles, weights, uKnots, 
					vKnots, uMults, vMults, bDeg,
					vDeg);
			return std::move(mySurf);
		}
		catch (const Standard_Failure&)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "unable to create bspline surface" << endl
				<< abort(FatalError);
			Handle(Geom_BSplineSurface) mySurf;
			return mySurf;
		}
	}
}

void tnbLib::Cad_ConicApexMaker::Perform()
{
	if (NOT Surface())
	{
		FatalErrorIn(FunctionSIG)
			<< "no surface has been loaded!" << endl
			<< abort(FatalError);
	}

	auto prcssr = std::make_shared<Cad_PolesNetPrcssr>(Surface());
	Debug_Null_Pointer(prcssr);

	auto[B0, B1] = RetrieveBoundary();

	const auto nbPoles = (Standard_Integer)B1.size();
	if (nbPoles < 2)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid nb. of poles has been detected!" << endl
			<< abort(FatalError);
	}

	if (HasToReverseBoundaryEdge(B1, Axis(), Tolerance()))
	{
		std::reverse(B0.begin(), B0.end());
		std::reverse(B1.begin(), B1.end());
	}

	const auto origin = RetrieveOrigin();
	
	const auto[N0, spanAngle] = CalcSpanAngle(B1, Axis(), Tolerance());

	const auto dTheta = spanAngle / (Standard_Real)(nbPoles - 1);

	const auto normals = CalcOrginNormals(N0, Axis(), dTheta, nbPoles);
	const auto normSurfs = CalcSurfNormals(B1, origin, normals);

	std::vector<Pnt3d> corners;
	corners.reserve(nbPoles);
	for (size_t i = 0; i < B1.size(); i++)
	{
		const auto& b0 = RetrievePoint(B0[i]);
		const auto& b1 = RetrievePoint(B1[i]);

		auto pln = CreatePlane(origin, normSurfs[i]);

		auto corner = CalcCorner(b0, b1, origin, normals[i], pln, Tolerance());
		corners.push_back(std::move(corner));
	}

	auto mySurf = CreateApex(B1, RetrieveBoundaryKnots(), RetrieveBoundaryDegree(), corners, origin);
	theApex_ = std::move(mySurf);

	Change_IsDone() = Standard_True;
}
