#include <Cad_RailRevolve.hxx>

#include <Geo_Tools.hxx>
#include <Entity_Segment.hxx>
#include <Pnt2d.hxx>
#include <Pnt3d.hxx>
#include <Dir3d.hxx>
#include <Dir2d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Precision.hxx>
#include <gp_Pln.hxx>
#include <Geom_BSplineCurve.hxx>
#include <Geom_BSplineSurface.hxx>
#include <Geom_Plane.hxx>
#include <Geom_Line.hxx>
#include <GeomAPI_ProjectPointOnCurve.hxx>
#include <GeomAPI_ProjectPointOnSurf.hxx>
#include <GeomAPI_IntCS.hxx>
#include <TColgp_Array2OfPnt.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <TColStd_Array2OfReal.hxx>

namespace tnbLib
{

	auto Intersect(const Handle(Geom_Line)& theLine, const Handle(Geom_Surface)& theSurface)
	{
		GeomAPI_IntCS alg(theLine, theSurface);
		if (NOT alg.IsDone())
		{
			FatalErrorIn(FunctionSIG)
				<< "something went wrong: Unable to identify intersection of line and surface!" << endl
				<< abort(FatalError);
		}
		if (alg.NbPoints() NOT_EQUAL 1)
		{
			FatalErrorIn(FunctionSIG)
				<< "something went wrong: Unable to identify intersection of line and surface!" << endl
				<< abort(FatalError);
		}
		return alg.Point(1);
	}

	auto CalcNormalPlane(const Pnt3d& P0, const Pnt3d& P1, const Pnt3d& P2)
	{
		try
		{
			Dir3d d0(P0, P1);
			Dir3d d1(P0, P2);

			auto n = Dir3d(d0.Crossed(d1));
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

	auto CreatePlane(const Pnt3d& origin, const Dir3d& normal)
	{
		gp_Pln pl(origin, normal);

		Handle(Geom_Plane) myPlane = new Geom_Plane(pl);
		return std::move(myPlane);
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

	auto CalcDir(const Entity_Segment<Pnt2d>& ent)
	{
		Dir2d dir(ent.P1(), ent.P0());
		return std::move(dir);
	}

	auto CalcAngle(const Pnt3d& P0, const Pnt3d& P1, const Handle(Geom_Line)& l)
	{
		auto pp0 = ProjectPoint(P0, l);
		auto pp1 = ProjectPoint(P1, l);

		auto pln = CreatePlane(pp0, l->Lin().Direction());

		auto e0 = ProjectSegment(Entity_Segment<const Pnt3d&>(pp0, P0), pln);
		auto e1 = ProjectSegment(Entity_Segment<const Pnt3d&>(pp1, P1), pln);

		return CalcDir(e0).Angle(CalcDir(e1));
	}

	auto RetrieveWeights(const TColStd_Array1OfReal* theWeights, Standard_Integer theSize)
	{
		std::vector<Standard_Real> weights(theSize, 1.0);
		if (theWeights)
		{
			for (Standard_Integer i = 1; i < theSize; i++)
			{
				weights[i - 1] = theWeights->Value(i);
			}
		}
		return std::move(weights);
	}
}

void tnbLib::Cad_RailRevolve::Perform()
{
	if (NOT Generatrix())
	{
		FatalErrorIn(FunctionSIG)
			<< "no generatrix curve has been detected!" << endl
			<< abort(FatalError);
	}

	if (NOT Rail())
	{
		FatalErrorIn(FunctionSIG)
			<< "no rail curve has been detected!" << endl
			<< abort(FatalError);
	}

	const auto tol = Tolerance();

	const auto& genPoles = Generatrix()->Poles();
	const auto& railPoles = Rail()->Poles();

	for (int i = 1; i <= genPoles.Size(); i++)
	{
		std::cout << genPoles.Value(i) << std::endl;
	}

	for (int i = 1; i <= railPoles.Size(); i++)
	{
		std::cout << railPoles.Value(i) << std::endl;
	}

	auto genWeights = RetrieveWeights(Generatrix()->Weights(), genPoles.Size());
	auto railWeights = RetrieveWeights(Rail()->Weights(), railPoles.Size());

	Handle(Geom_Line) axLine = new Geom_Line(Axis());

	for (Standard_Integer i = 1; i <= railPoles.Size(); i++)
	{
		auto pt = ProjectPoint(railPoles.Value(i), axLine);
		if (pt.Distance(railPoles.Value(i)) <= tol)
		{
			FatalErrorIn(FunctionSIG)
				<< "Unable to revolve the curve!" << endl
				<< abort(FatalError);
		}
	}

	TColgp_Array2OfPnt Poles(1, railPoles.Size(), 1, genPoles.Size());
	TColStd_Array2OfReal Weights(1, railPoles.Size(), 1, genPoles.Size());

	for (Standard_Integer j = 1; j <= genPoles.Size(); j++)
	{
		Poles.SetValue(1, j, genPoles.Value(j));
		Weights.SetValue(1, j, genWeights[j - 1] * railWeights[0]);
	}

	for (Standard_Integer j = 1; j < railPoles.Size(); j++)
	{
		const auto& Q0 = railPoles.Value(j);
		const auto& Q1 = railPoles.Value(j + 1);

		std::vector<gp_Pnt> pts;
		pts.reserve(genPoles.Size());

		if (Q0.Distance(Q1) <= tol)
		{
			for (Standard_Integer i = 1; i <= genPoles.Size(); i++)
			{
				pts.push_back(Poles.Value(j, i));
			}
		}
		else
		{
			try
			{
				auto angle = CalcAngle(Q0, Q1, axLine);

				auto P1 = Q1;
				//pts.push_back(genPoles.Value(1));
				pts.push_back(railPoles.Value(j + 1));
				for (Standard_Integer i = 2; i <= genPoles.Size(); i++)
				{
					//const auto& pt = genPoles.Value(i);
					const auto& pt = Poles.Value(j, i);
					auto ppt = ProjectPoint(pt, axLine);

					if (ppt.Distance(pt) <= tol)
					{				
						pts.push_back(pt);
					}
					else
					{
						//const auto& P0 = genPoles.Value(i - 1);
						const auto& P0 = Poles.Value(j, i - 1);

						auto t = Dir3d(P0, P1);
						auto e = Dir3d(ppt, pt);
						e.Rotate(Axis(), angle);

						auto n = Axis().Direction().Crossed(e);
						auto pln = CreatePlane(ppt, n);

						Handle(Geom_Line) tLine = new Geom_Line(pt, t);
						auto rotatedPoint = Intersect(tLine, pln);

						pts.push_back(std::move(rotatedPoint));
					}
				}
			}
			catch (const Standard_Failure& x)
			{
				FatalErrorIn(FunctionSIG)
					<< x.GetMessageString() << endl
					<< abort(FatalError);
			}
		}
		
		for (Standard_Integer i = 0; i < pts.size(); i++)
		{
			Poles.SetValue(j + 1, i + 1, pts[i]);
			Weights.SetValue(j + 1, i + 1, /*railWeights[j + 1] **/ genWeights[i]);
		}
	}
	
	try
	{
		thePatch_ = new Geom_BSplineSurface
		(
			Poles, Weights,
			Rail()->Knots(),
			Generatrix()->Knots(),
			Rail()->Multiplicities(),
			Generatrix()->Multiplicities(),
			Rail()->Degree(),
			Generatrix()->Degree()
		);
	}
	catch (const Standard_Failure& x)
	{
		FatalErrorIn(FunctionSIG)
			<< x.GetMessageString() << endl
			<< abort(FatalError);
	}

	Change_IsDone() = Standard_True;
}