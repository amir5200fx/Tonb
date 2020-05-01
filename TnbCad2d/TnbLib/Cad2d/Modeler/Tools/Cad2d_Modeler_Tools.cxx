#include <Cad2d_Modeler_Tools.hxx>

#include <Pnt2d.hxx>
#include <Vec2d.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Ring.hxx>

#include <Standard_Handle.hxx>
#include <Geom2d_Curve.hxx>
#include <GCE2d_MakeSegment.hxx>
#include <GCE2d_MakeArcOfCircle.hxx>
#include <GCE2d_MakeArcOfEllipse.hxx>
#include <GCE2d_MakeArcOfHyperbola.hxx>
#include <GCE2d_MakeArcOfParabola.hxx>
#include <GCE2d_MakeCircle.hxx>
#include <GCE2d_MakeEllipse.hxx>

namespace tnbLib
{

	std::shared_ptr<Pln_Edge> Make_Edge
	(
		const opencascade::handle<Geom2d_Curve>& geom,
		const Pnt2d& p0,
		const Pnt2d& p1
	)
	{
		auto v0 = std::make_shared<Pln_Vertex>(0, p0);
		Debug_Null_Pointer(v0);

		auto v1 = std::make_shared<Pln_Vertex>(1, p1);
		Debug_Null_Pointer(v1);

		auto curve = std::make_shared<Pln_Curve>(0, geom);
		Debug_Null_Pointer(curve);

		auto edge = std::make_shared<Pln_Edge>(std::move(v0), std::move(v1), std::move(curve));
		Debug_Null_Pointer(edge);

		return std::move(edge);
	}

	std::shared_ptr<Pln_Ring> Make_Ring
	(
		const opencascade::handle<Geom2d_Curve>& geom,
		const Pnt2d& theP
	)
	{
		auto v = std::make_shared<Pln_Vertex>(0, theP);
		Debug_Null_Pointer(v);

		auto curve = std::make_shared<Pln_Curve>(0, geom);
		Debug_Null_Pointer(curve);

		auto edge = std::make_shared<Pln_Ring>(v, std::move(curve));
		Debug_Null_Pointer(edge);

		return std::move(edge);
	}
}

std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::cad2dLib::Modeler_Tools::MakeSegment
(
	const Pnt2d & theP0,
	const Pnt2d & theP1
)
{
	GCE2d_MakeSegment maker(theP0, theP1);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();

		auto edge = Make_Edge(geom, theP0, theP1);
		Debug_Null_Pointer(edge);

		return std::move(edge);
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::cad2dLib::Modeler_Tools::MakeSegment
(
	const Pnt2d & theP0,
	const Standard_Real theAngle, 
	const Standard_Real theLength
)
{
	const auto V = theLength* gp_Dir2d(cos(theAngle), sin(theAngle));
	Pnt2d P1(theP0.X() + V.X(), theP0.Y() + V.Y());

	auto edge = MakeSegment(theP0, P1);
	return std::move(edge);
}

std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::cad2dLib::Modeler_Tools::MakeCircArc
(
	const Pnt2d & theP0, 
	const Pnt2d & theP1,
	const Pnt2d & theP2
)
{
	GCE2d_MakeArcOfCircle maker(theP0, theP1, theP2);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();

		auto edge = 
			Make_Edge
			(
				geom, geom->Value(geom->FirstParameter()), 
				geom->Value(geom->LastParameter())
			);

		Debug_Null_Pointer(edge);

		return std::move(edge);
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::cad2dLib::Modeler_Tools::MakeCircArc
(
	const Pnt2d & theP0, 
	const Vec2d & theV0,
	const Pnt2d & theP1
)
{
	GCE2d_MakeArcOfCircle maker(theP0, theV0, theP1);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();

		auto edge =
			Make_Edge
			(
				geom, geom->Value(geom->FirstParameter()),
				geom->Value(geom->LastParameter())
			);

		Debug_Null_Pointer(edge);

		return std::move(edge);
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::cad2dLib::Modeler_Tools::MakeCircArc
(
	const gp_Circ2d & theCirc, 
	const Standard_Real theAlpha0, 
	const Standard_Real theAlpha1
)
{
	GCE2d_MakeArcOfCircle maker(theCirc, theAlpha0, theAlpha1);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();

		auto edge =
			Make_Edge
			(
				geom, geom->Value(geom->FirstParameter()),
				geom->Value(geom->LastParameter())
			);

		Debug_Null_Pointer(edge);

		return std::move(edge);
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::cad2dLib::Modeler_Tools::MakeCircArc
(
	const gp_Circ2d & theCirc, 
	const Pnt2d & theP0, 
	const Pnt2d & theP1
)
{
	GCE2d_MakeArcOfCircle maker(theCirc, theP0, theP1);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();

		auto edge =
			Make_Edge
			(
				geom, geom->Value(geom->FirstParameter()),
				geom->Value(geom->LastParameter())
			);

		Debug_Null_Pointer(edge);

		return std::move(edge);
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::cad2dLib::Modeler_Tools::MakeElipsArc
(
	const gp_Elips2d & theElips, 
	const Standard_Real theAlpha0, 
	const Standard_Real theAlpha1
)
{
	GCE2d_MakeArcOfEllipse maker(theElips, theAlpha0, theAlpha1);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();

		auto edge =
			Make_Edge
			(
				geom, geom->Value(geom->FirstParameter()),
				geom->Value(geom->LastParameter())
			);

		Debug_Null_Pointer(edge);

		return std::move(edge);
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Edge>
tnbLib::cad2dLib::Modeler_Tools::MakeElipsArc
(
	const gp_Elips2d & theElips,
	const Pnt2d & theP0,
	const Pnt2d & theP1
)
{
	GCE2d_MakeArcOfEllipse maker(theElips, theP0, theP1);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();

		auto edge =
			Make_Edge
			(
				geom, geom->Value(geom->FirstParameter()),
				geom->Value(geom->LastParameter())
			);

		Debug_Null_Pointer(edge);

		return std::move(edge);
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::cad2dLib::Modeler_Tools::MakeHyprArc
(
	const gp_Hypr2d & theHypr,
	const Standard_Real theAlpha0,
	const Standard_Real theAlpha1
)
{
	GCE2d_MakeArcOfHyperbola maker(theHypr, theAlpha0, theAlpha1);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();

		auto edge =
			Make_Edge
			(
				geom, geom->Value(geom->FirstParameter()),
				geom->Value(geom->LastParameter())
			);

		Debug_Null_Pointer(edge);

		return std::move(edge);
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::cad2dLib::Modeler_Tools::MakeHyprArc
(
	const gp_Hypr2d & theHypr, 
	const Pnt2d & theP0, 
	const Pnt2d & theP1
)
{
	GCE2d_MakeArcOfHyperbola maker(theHypr, theP0, theP1);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();

		auto edge =
			Make_Edge
			(
				geom, geom->Value(geom->FirstParameter()),
				geom->Value(geom->LastParameter())
			);

		Debug_Null_Pointer(edge);

		return std::move(edge);
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::cad2dLib::Modeler_Tools::MakeParbCurve
(
	const gp_Parab2d & theParab, 
	const Standard_Real theAlpha0, 
	const Standard_Real theAlpha1
)
{
	GCE2d_MakeArcOfParabola maker(theParab, theAlpha0, theAlpha1);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();

		auto edge =
			Make_Edge
			(
				geom, geom->Value(geom->FirstParameter()),
				geom->Value(geom->LastParameter())
			);

		Debug_Null_Pointer(edge);

		return std::move(edge);
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::cad2dLib::Modeler_Tools::MakeParabCurve
(
	const gp_Parab2d & theParab,
	const Pnt2d & theP0,
	const Pnt2d & theP1
)
{
	GCE2d_MakeArcOfParabola maker(theParab, theP0, theP1);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();

		auto edge =
			Make_Edge
			(
				geom, geom->Value(geom->FirstParameter()),
				geom->Value(geom->LastParameter())
			);

		Debug_Null_Pointer(edge);

		return std::move(edge);
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Ring>
tnbLib::cad2dLib::Modeler_Tools::MakeCircle
(
	const gp_Circ2d & C
)
{
	GCE2d_MakeCircle maker(C);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();

		auto edge =
			Make_Ring
			(
				geom, geom->Value(geom->FirstParameter())
			);

		Debug_Null_Pointer(edge);

		return std::move(edge);
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Ring>
tnbLib::cad2dLib::Modeler_Tools::MakeCircle
(
	const gp_Circ2d & C,
	const Pnt2d & theP
)
{
	GCE2d_MakeCircle maker(C, theP);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();

		auto edge =
			Make_Ring
			(
				geom, geom->Value(geom->FirstParameter())
			);

		Debug_Null_Pointer(edge);

		return std::move(edge);
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Ring>
tnbLib::cad2dLib::Modeler_Tools::MakeCircle
(
	const Pnt2d & theP0, 
	const Pnt2d & theP1, 
	const Pnt2d & theP2
)
{
	GCE2d_MakeCircle maker(theP0, theP1, theP2);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();

		auto edge =
			Make_Ring
			(
				geom, geom->Value(geom->FirstParameter())
			);

		Debug_Null_Pointer(edge);

		return std::move(edge);
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Ring>
tnbLib::cad2dLib::Modeler_Tools::MakeCircle
(
	const Pnt2d & theC, 
	const Standard_Real theRadius
)
{
	GCE2d_MakeCircle maker(theC, theRadius);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();

		auto edge =
			Make_Ring
			(
				geom, geom->Value(geom->FirstParameter())
			);

		Debug_Null_Pointer(edge);

		return std::move(edge);
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Ring>
tnbLib::cad2dLib::Modeler_Tools::MakeCircle
(
	const Pnt2d & theC, 
	const Pnt2d & theP
)
{
	GCE2d_MakeCircle maker(theC, theP);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();

		auto edge =
			Make_Ring
			(
				geom, geom->Value(geom->FirstParameter())
			);

		Debug_Null_Pointer(edge);

		return std::move(edge);
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Ring> 
tnbLib::cad2dLib::Modeler_Tools::MakeEllipse
(
	const gp_Elips2d & E
)
{
	GCE2d_MakeEllipse maker(E);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();

		auto edge =
			Make_Ring
			(
				geom, geom->Value(geom->FirstParameter())
			);

		Debug_Null_Pointer(edge);

		return std::move(edge);
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<tnbLib::Pln_Ring> 
tnbLib::cad2dLib::Modeler_Tools::MakeEllipse
(
	const Pnt2d & theS0, 
	const Pnt2d & theS1,
	const Pnt2d & theCenter
)
{
	GCE2d_MakeEllipse maker(theS0, theS1, theCenter);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();

		auto edge =
			Make_Ring
			(
				geom, geom->Value(geom->FirstParameter())
			);

		Debug_Null_Pointer(edge);

		return std::move(edge);
	}
	else
	{
		return nullptr;
	}
}