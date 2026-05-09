#include <Marine_Modeler_Tools.hxx>

#include <Pln_CurveTools.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Ring.hxx>
#include <Marine_PlnCurves.hxx>

#include <opencascade/Geom2d_Curve.hxx>

std::shared_ptr<tnbLib::Pln_Curve> 
tnbLib::marineLib::Modeler_Tools::MakeCurve
(
	const Handle(Geom2d_Curve)& geom, 
	const curveType t
)
{
	switch (t)
	{
	case curveType::displacer:
	{
		auto curve = std::make_shared<Marine_DisplacerCurve>(0, geom);
		return std::move(curve);
	}
	case curveType::sail:
	{
		auto curve = std::make_shared<Marine_SailCurve>(0, geom);
		return std::move(curve);
	}
	case curveType::tank:
	{
		auto curve = std::make_shared<Marine_TankCurve>(0, geom);
		return std::move(curve);
	}
	case curveType::water:
	{
		auto curve = std::make_shared<Marine_WaterCurve>(0, geom);
		return std::move(curve);
	}
	case curveType::waterLine:
	{
		auto curve = std::make_shared<Marine_WaterLineCurve>(0, geom);
		return std::move(curve);
	}
	case curveType::wetted:
	{
		auto curve = std::make_shared<Marine_WettedCurve>(0, geom);
		return std::move(curve);
	}
	case curveType::dry:
	{
		auto curve = std::make_shared<Marine_DryCurve>(0, geom);
		return std::move(curve);
	}
	default:
		FatalErrorIn(FunctionSIG)
			<< "undefined curve type!" << endl
			<< abort(FatalError);
		break;
	}
	return nullptr;
}

std::shared_ptr<tnbLib::Pln_Curve>
tnbLib::marineLib::Modeler_Tools::MakeCurve
(
	Handle(Geom2d_Curve)&& geom,
	const curveType t
)
{
	switch (t)
	{
	case curveType::displacer:
	{
		auto curve = std::make_shared<Marine_DisplacerCurve>(0, std::move(geom));
		return std::move(curve);
	}
	case curveType::sail:
	{
		auto curve = std::make_shared<Marine_SailCurve>(0, std::move(geom));
		return std::move(curve);
	}
	case curveType::tank:
	{
		auto curve = std::make_shared<Marine_TankCurve>(0, std::move(geom));
		return std::move(curve);
	}
	case curveType::water:
	{
		auto curve = std::make_shared<Marine_WaterCurve>(0, std::move(geom));
		return std::move(curve);
	}
	case curveType::waterLine:
	{
		auto curve = std::make_shared<Marine_WaterLineCurve>(0, std::move(geom));
		return std::move(curve);
	}
	case curveType::wetted:
	{
		auto curve = std::make_shared<Marine_WettedCurve>(0, std::move(geom));
		return std::move(curve);
	}
	case curveType::dry:
	{
		auto curve = std::make_shared<Marine_DryCurve>(0, std::move(geom));
		return std::move(curve);
	}
	default:
		FatalErrorIn(FunctionSIG)
			<< "undefined curve type!" << endl
			<< abort(FatalError);
		break;
	}
	return nullptr;
}

std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::marineLib::Modeler_Tools::MakeEdge
(
	const Handle(Geom2d_Curve)& geom,
	const Pnt2d & p0, 
	const Pnt2d & p1, 
	const curveType t
)
{
	auto v0 = std::make_shared<Pln_Vertex>(0, p0);
	Debug_Null_Pointer(v0);

	auto v1 = std::make_shared<Pln_Vertex>(1, p1);
	Debug_Null_Pointer(v1);

	auto curve = MakeCurve(geom, t);
	Debug_Null_Pointer(curve);

	auto edge = std::make_shared<Pln_Segment>(std::move(v0), std::move(v1), std::move(curve));
	Debug_Null_Pointer(edge);

	return std::move(edge);
}

std::shared_ptr<tnbLib::Pln_Ring> 
tnbLib::marineLib::Modeler_Tools::MakeRing
(
	const Handle(Geom2d_Curve)& geom,
	const Pnt2d & theP,
	const curveType t
)
{
	auto v = std::make_shared<Pln_Vertex>(0, theP);
	Debug_Null_Pointer(v);

	auto curve = MakeCurve(geom, t);
	Debug_Null_Pointer(curve);

	auto edge = std::make_shared<Pln_Ring>(v, std::move(curve));
	Debug_Null_Pointer(edge);

	return std::move(edge);
}

std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::marineLib::Modeler_Tools::MakeSegment
(
	const Pnt2d & theP0,
	const Pnt2d & theP1, 
	const curveType t
)
{
	auto curve = Pln_CurveTools::MakeSegment(theP0, theP1);
	if (curve)
	{
		auto edge = MakeEdge(curve, theP0, theP1, t);
		Debug_Null_Pointer(edge);
		return std::move(edge);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< " no curves has been created!" << endl
			<< abort(FatalError);
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Edge>
tnbLib::marineLib::Modeler_Tools::MakeSegment
(
	const Pnt2d & theP0,
	const Standard_Real theAngle,
	const Standard_Real theLength,
	const curveType t
)
{
	const auto V = theLength * gp_Dir2d(cos(theAngle), sin(theAngle));
	Pnt2d P1(theP0.X() + V.X(), theP0.Y() + V.Y());

	auto edge = MakeSegment(theP0, P1, t);
	return std::move(edge);
}

std::shared_ptr<tnbLib::Pln_Edge>
tnbLib::marineLib::Modeler_Tools::MakeCircArc
(
	const Pnt2d & theP0,
	const Pnt2d & theP1,
	const Pnt2d & theP2,
	const curveType t
)
{
	auto geom = Pln_CurveTools::MakeCircArc(theP0, theP1, theP2);
	if (geom)
	{
		auto edge =
			MakeEdge
			(
				geom, geom->Value(geom->FirstParameter()),
				geom->Value(geom->LastParameter()), t
			);
		return std::move(edge);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< " no curves has been created!" << endl
			<< abort(FatalError);
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Edge>
tnbLib::marineLib::Modeler_Tools::MakeCircArc
(
	const Pnt2d & theP0,
	const Vec2d & theV0,
	const Pnt2d & theP1,
	const curveType t
)
{
	auto geom = Pln_CurveTools::MakeCircArc(theP0, theV0, theP1);
	if (geom)
	{
		auto edge =
			MakeEdge
			(
				geom, geom->Value(geom->FirstParameter()),
				geom->Value(geom->LastParameter()), t
			);
		return std::move(edge);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< " no curves has been created!" << endl
			<< abort(FatalError);
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Edge>
tnbLib::marineLib::Modeler_Tools::MakeCircArc
(
	const gp_Circ2d & theCirc,
	const Standard_Real theAlpha0,
	const Standard_Real theAlpha1,
	const curveType t
)
{
	auto geom = Pln_CurveTools::MakeCircArc(theCirc, theAlpha0, theAlpha1);
	if (geom)
	{
		auto edge =
			MakeEdge
			(
				geom, geom->Value(geom->FirstParameter()),
				geom->Value(geom->LastParameter()), t
			);
		return std::move(edge);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< " no curves has been created!" << endl
			<< abort(FatalError);
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Edge>
tnbLib::marineLib::Modeler_Tools::MakeCircArc
(
	const gp_Circ2d & theCirc,
	const Pnt2d & theP0,
	const Pnt2d & theP1,
	const curveType t
)
{
	auto geom = Pln_CurveTools::MakeCircArc(theCirc, theP0, theP1);
	if (geom)
	{
		auto edge =
			MakeEdge
			(
				geom, geom->Value(geom->FirstParameter()),
				geom->Value(geom->LastParameter()), t
			);
		return std::move(edge);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< " no curves has been created!" << endl
			<< abort(FatalError);
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Edge>
tnbLib::marineLib::Modeler_Tools::MakeElipsArc
(
	const gp_Elips2d & theElips,
	const Standard_Real theAlpha0,
	const Standard_Real theAlpha1,
	const curveType t
)
{
	auto geom = Pln_CurveTools::MakeElipsArc(theElips, theAlpha0, theAlpha1);
	if (geom)
	{
		auto edge =
			MakeEdge
			(
				geom, geom->Value(geom->FirstParameter()),
				geom->Value(geom->LastParameter()), t
			);
		return std::move(edge);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< " no curves has been created!" << endl
			<< abort(FatalError);
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Edge>
tnbLib::marineLib::Modeler_Tools::MakeElipsArc
(
	const gp_Elips2d & theElips,
	const Pnt2d & theP0,
	const Pnt2d & theP1,
	const curveType t
)
{
	auto geom = Pln_CurveTools::MakeElipsArc(theElips, theP0, theP1);
	if (geom)
	{
		auto edge =
			MakeEdge
			(
				geom, geom->Value(geom->FirstParameter()),
				geom->Value(geom->LastParameter()), t
			);
		return std::move(edge);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< " no curves has been created!" << endl
			<< abort(FatalError);
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Edge>
tnbLib::marineLib::Modeler_Tools::MakeHyprArc
(
	const gp_Hypr2d & theHypr,
	const Standard_Real theAlpha0,
	const Standard_Real theAlpha1,
	const curveType t
)
{
	auto geom = Pln_CurveTools::MakeHyprArc(theHypr, theAlpha0, theAlpha1);
	if (geom)
	{
		auto edge =
			MakeEdge
			(
				geom, geom->Value(geom->FirstParameter()),
				geom->Value(geom->LastParameter()), t
			);
		return std::move(edge);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< " no curves has been created!" << endl
			<< abort(FatalError);
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Edge>
tnbLib::marineLib::Modeler_Tools::MakeHyprArc
(
	const gp_Hypr2d & theHypr,
	const Pnt2d & theP0,
	const Pnt2d & theP1,
	const curveType t
)
{
	auto geom = Pln_CurveTools::MakeHyprArc(theHypr, theP0, theP1);
	if (geom)
	{
		auto edge =
			MakeEdge
			(
				geom, geom->Value(geom->FirstParameter()),
				geom->Value(geom->LastParameter()), t
			);
		return std::move(edge);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< " no curves has been created!" << endl
			<< abort(FatalError);
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Edge>
tnbLib::marineLib::Modeler_Tools::MakeParbArc
(
	const gp_Parab2d & theParab,
	const Standard_Real theAlpha0,
	const Standard_Real theAlpha1,
	const curveType t
)
{
	auto geom = Pln_CurveTools::MakeParbArc(theParab, theAlpha0, theAlpha1);
	if (geom)
	{
		auto edge =
			MakeEdge
			(
				geom, geom->Value(geom->FirstParameter()),
				geom->Value(geom->LastParameter()), t
			);
		return std::move(edge);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< " no curves has been created!" << endl
			<< abort(FatalError);
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Edge>
tnbLib::marineLib::Modeler_Tools::MakeParabArc
(
	const gp_Parab2d & theParab,
	const Pnt2d & theP0,
	const Pnt2d & theP1,
	const curveType t
)
{
	auto geom = Pln_CurveTools::MakeParbArc(theParab, theP0, theP1);
	if (geom)
	{
		auto edge =
			MakeEdge
			(
				geom, geom->Value(geom->FirstParameter()),
				geom->Value(geom->LastParameter()), t
			);
		return std::move(edge);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< " no curves has been created!" << endl
			<< abort(FatalError);
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Ring>
tnbLib::marineLib::Modeler_Tools::MakeCircle
(
	const gp_Circ2d & c,
	const curveType t
)
{
	auto geom = Pln_CurveTools::MakeCircle(c);
	if (geom)
	{
		auto edge =
			MakeRing
			(
				geom, geom->Value(geom->FirstParameter()), t
			);
		return std::move(edge);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< " no curves has been created!" << endl
			<< abort(FatalError);
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Ring>
tnbLib::marineLib::Modeler_Tools::MakeCircle
(
	const gp_Circ2d & C,
	const Pnt2d & theP,
	const curveType t
)
{
	auto geom = Pln_CurveTools::MakeCircle(C, theP);
	if (geom)
	{
		auto edge =
			MakeRing
			(
				geom, geom->Value(geom->FirstParameter()), t
			);
		return std::move(edge);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< " no curves has been created!" << endl
			<< abort(FatalError);
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Ring>
tnbLib::marineLib::Modeler_Tools::MakeCircle
(
	const Pnt2d & theP0,
	const Pnt2d & theP1,
	const Pnt2d & theP2,
	const curveType t
)
{
	auto geom = Pln_CurveTools::MakeCircle(theP0, theP1, theP2);
	if (geom)
	{
		auto edge =
			MakeRing
			(
				geom, geom->Value(geom->FirstParameter()), t
			);
		return std::move(edge);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< " no curves has been created!" << endl
			<< abort(FatalError);
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Ring>
tnbLib::marineLib::Modeler_Tools::MakeCircle
(
	const Pnt2d & theC,
	const Standard_Real theRadius,
	const curveType t
)
{
	auto geom = Pln_CurveTools::MakeCircle(theC, theRadius);
	if (geom)
	{
		auto edge =
			MakeRing
			(
				geom, geom->Value(geom->FirstParameter()), t
			);
		return std::move(edge);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< " no curves has been created!" << endl
			<< abort(FatalError);
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Ring>
tnbLib::marineLib::Modeler_Tools::MakeCircle
(
	const Pnt2d & theC,
	const Pnt2d & theP,
	const curveType t
)
{
	auto geom = Pln_CurveTools::MakeCircle(theC, theP);
	if (geom)
	{
		auto edge =
			MakeRing
			(
				geom, geom->Value(geom->FirstParameter()), t
			);
		return std::move(edge);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< " no curves has been created!" << endl
			<< abort(FatalError);
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Ring>
tnbLib::marineLib::Modeler_Tools::MakeEllipse
(
	const gp_Elips2d & E,
	const curveType t
)
{
	auto geom = Pln_CurveTools::MakeEllipse(E);
	if (geom)
	{
		auto edge =
			MakeRing
			(
				geom, geom->Value(geom->FirstParameter()), t
			);
		return std::move(edge);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< " no curves has been created!" << endl
			<< abort(FatalError);
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Ring>
tnbLib::marineLib::Modeler_Tools::MakeEllipse
(
	const Pnt2d & theS0,
	const Pnt2d & theS1,
	const Pnt2d & theCenter,
	const curveType t
)
{
	auto geom = Pln_CurveTools::MakeEllipse(theS0, theS1, theCenter);
	if (geom)
	{
		auto edge =
			MakeRing
			(
				geom, geom->Value(geom->FirstParameter()), t
			);
		return std::move(edge);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< " no curves has been created!" << endl
			<< abort(FatalError);
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Edge>
tnbLib::marineLib::Modeler_Tools::Interpolation
(
	const std::vector<Pnt2d>& theQ,
	const curveType t,
	const Standard_Boolean thePeriodic,
	const Standard_Real theTol
)
{
	auto geom = Pln_CurveTools::Interpolation(theQ, thePeriodic, theTol);
	auto edge =
		MakeEdge
		(
			geom,
			geom->Value(geom->FirstParameter()),
			geom->Value(geom->LastParameter()), t
		);
	return std::move(edge);
}

std::shared_ptr<tnbLib::Pln_Edge>
tnbLib::marineLib::Modeler_Tools::Interpolation
(
	const std::vector<Pnt2d>& theQ,
	const Vec2d & theFirst,
	const Vec2d & theLast,
	const curveType t,
	const Standard_Boolean thePeriodic,
	const Standard_Real theTol,
	const Standard_Boolean theScale
)
{
	auto geom =
		Pln_CurveTools::Interpolation
		(
			theQ, theFirst, theLast,
			thePeriodic, theTol, theScale
		);
	auto edge =
		MakeEdge
		(
			geom,
			geom->Value(geom->FirstParameter()),
			geom->Value(geom->LastParameter()), t
		);
	return std::move(edge);
}

std::vector<std::shared_ptr<tnbLib::Pln_Edge>>
tnbLib::marineLib::Modeler_Tools::MakeRectangular
(
	const Pnt2d & theP0,
	const Pnt2d & theP1,
	const curveType t
)
{
	std::vector<std::shared_ptr<Pln_Edge>> edges;
	edges.reserve(4);

	auto p0 = theP0;
	auto p1 = Pnt2d(theP1.X(), theP0.Y());
	auto p2 = theP1;
	auto p3 = Pnt2d(theP0.X(), theP1.Y());

	auto e0 = MakeSegment(p0, p1, t);
	auto e1 = MakeSegment(p1, p2, t);
	auto e2 = MakeSegment(p2, p3, t);
	auto e3 = MakeSegment(p3, p0, t);

	edges.push_back(std::move(e0));
	edges.push_back(std::move(e1));
	edges.push_back(std::move(e2));
	edges.push_back(std::move(e3));

	return std::move(edges);
}

void tnbLib::marineLib::Modeler_Tools::CheckCurveType
(
	const std::shared_ptr<Pln_Curve>& theCurve,
	const curveType t
)
{
	switch (t)
	{
	case curveType::displacer:
	{
		auto c = std::dynamic_pointer_cast<Marine_DisplacerCurve>(theCurve);
		if (NOT c)
		{
			FatalErrorIn(FunctionSIG)
				<< "the curve is not displacer!" << endl
				<< abort(FatalError);
		}
		break;
	}
	case curveType::sail:
	{
		auto c = std::dynamic_pointer_cast<Marine_SailCurve>(theCurve);
		if (NOT c)
		{
			FatalErrorIn(FunctionSIG)
				<< "the curve is not sail!" << endl
				<< abort(FatalError);
		}
		break;
	}
	case curveType::tank:
	{
		auto c = std::dynamic_pointer_cast<Marine_TankCurve>(theCurve);
		if (NOT c)
		{
			FatalErrorIn(FunctionSIG)
				<< "the curve is not tank!" << endl
				<< abort(FatalError);
		}
		break;
	}
	default:
		FatalErrorIn(FunctionSIG)
			<< "undefined plane curve!" << endl
			<< abort(FatalError);
		break;
	}
}