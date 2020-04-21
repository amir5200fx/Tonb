#include <HydStatic_ArmCurve.hxx>

#include <Pnt2d.hxx>
#include <Pln_Tools.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <gp_Lin2d.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>

tnbLib::HydStatic_ArmCurve::HydStatic_ArmCurve
(
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_HydCurve(theCurve)
{
}

tnbLib::HydStatic_ArmCurve::HydStatic_ArmCurve
(
	const Standard_Integer theIndex, 
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_HydCurve(theIndex, theCurve)
{
}

tnbLib::HydStatic_ArmCurve::HydStatic_ArmCurve
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_HydCurve(theIndex, theName, theCurve)
{
}

Standard_Boolean
tnbLib::HydStatic_ArmCurve::IsIntersect
(
	const Standard_Real thePhi
) const
{
	const auto h0 = MinHeel();
	const auto h1 = MaxHeel();

	return INSIDE(thePhi, h0, h1);
}

Standard_Real 
tnbLib::HydStatic_ArmCurve::MinHeel() const
{
	Debug_Null_Pointer(Geometry());
	const auto& g = *Geometry();

	auto p = g.Value(g.FirstParameter());
	return p.Y();
}

Standard_Real 
tnbLib::HydStatic_ArmCurve::MaxHeel() const
{
	Debug_Null_Pointer(Geometry());
	const auto& g = *Geometry();

	auto p = g.Value(g.LastParameter());
	return p.Y();
}

Standard_Real 
tnbLib::HydStatic_ArmCurve::Value
(
	const Standard_Real thePhi
) const
{
	if (NOT IsIntersect(thePhi))
	{
		FatalErrorIn("Standard_Real Value(const Standard_Real thePhi) const")
			<< "Found no intersection" << endl
			<< abort(FatalError);
	}

	Handle(Geom2d_Line) l =
		new Geom2d_Line(gp_Pnt2d(thePhi, 0), gp_Dir2d(0, 1));
	Debug_Null_Pointer(l);

	Geom2dAPI_InterCurveCurve Int(l, Geometry());
	if (Int.NbPoints() NOT_EQUAL 1)
	{
		FatalErrorIn("Standard_Real Value(const Standard_Real thePhi) const")
			<< "Invalid data" << endl
			<< abort(FatalError);
	}

	auto value = Int.Point(0);
	return value.Y();
}

namespace tnbLib
{

	Standard_Real Parameter(const Standard_Real thePhi, const Handle(Geom2d_Curve)& theCurve)
	{
		Handle(Geom2d_Line) l =
			new Geom2d_Line(gp_Pnt2d(thePhi, 0), gp_Dir2d(0, 1));
		Debug_Null_Pointer(l);

		auto Int = std::make_shared<Geom2dAPI_InterCurveCurve>(theCurve, l);
		Debug_Null_Pointer(Int);
		if (Int->NbPoints() NOT_EQUAL 1)
		{
			FatalErrorIn("Standard_Real Parameter(const Standard_Real thePhi, const Handle(Geom2d_Curve)& theCurve)")
				<< "Invalid data" << endl
				<< abort(FatalError);
		}

		return Int->Intersector().Point(0).ParamOnFirst();
	}
}

#include <HydStatic_hArmCurve.hxx>
#include <HydStatic_rArmCurve.hxx>

std::shared_ptr<tnbLib::HydStatic_ArmCurve> 
tnbLib::HydStatic_ArmCurve::Clip
(
	const std::shared_ptr<HydStatic_ArmCurve>& theCurve,
	const Standard_Real theH0,
	const Standard_Real theH1
)
{
	if (NOT theCurve->IsIntersect(theH0))
	{
		FatalErrorIn("std::shared_ptr<HydStatic_ArmCurve> Clip(const HydStatic_ArmCurve& theCurve, const Standard_Real theH0, const Standard_Real theH1)")
			<< "Found no intersection" << endl
			<< abort(FatalError);
	}

	if (NOT theCurve->IsIntersect(theH1))
	{
		FatalErrorIn("std::shared_ptr<HydStatic_ArmCurve> Clip(const HydStatic_ArmCurve& theCurve, const Standard_Real theH0, const Standard_Real theH1)")
			<< "Found no intersection" << endl
			<< abort(FatalError);
	}

	const auto p0 = Parameter(theH0, theCurve->Geometry());
	const auto p1 = Parameter(theH1, theCurve->Geometry());

	Handle(Geom2d_TrimmedCurve) trimmed = new Geom2d_TrimmedCurve(theCurve->Geometry(), p0, p1);
	
	if (std::dynamic_pointer_cast<HydStatic_hArmCurve>(theCurve))
	{
		auto clipped = std::make_shared<HydStatic_hArmCurve>(trimmed);
		return std::move(clipped);
	}
	else if (std::dynamic_pointer_cast<HydStatic_rArmCurve>(theCurve))
	{
		auto clipped = std::make_shared<HydStatic_rArmCurve>(trimmed);
		return std::move(clipped);
	}
	else
	{
		FatalErrorIn("std::shared_ptr<HydStatic_ArmCurve> Clip(Args...)")
			<< "invalid arm curve!" << endl
			<< abort(FatalError);
		return nullptr;
	}
}