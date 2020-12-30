#include <Marine_WaterLineCurve.hxx>

#include <Pln_Tools.hxx>
#include <Pln_TangCurve.hxx>
#include <Cad2d_IntsctEntity_TangSegment.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2d_Curve.hxx>

tnbLib::Marine_WaterLineCurve::Marine_WaterLineCurve()
{
	// empty body
}

tnbLib::Marine_WaterLineCurve::Marine_WaterLineCurve
(
	const Standard_Integer theIndex,
	const Handle(Geom2d_Curve)& theGeom
)
	: Marine_HullCurve(theIndex, theGeom)
{
	// empty body
}

tnbLib::Marine_WaterLineCurve::Marine_WaterLineCurve
(
	const Handle(Geom2d_Curve)& theGeom
)
	: Marine_HullCurve(theGeom)
{
	// empty body
}

tnbLib::Marine_WaterLineCurve::Marine_WaterLineCurve
(
	const Standard_Integer theIndex,
	const word & theName,
	const Handle(Geom2d_Curve)& theGeom
)
	: Marine_HullCurve(theIndex, theName, theGeom)
{
	// empty body
}

std::shared_ptr<tnbLib::Pln_Curve>
tnbLib::Marine_WaterLineCurve::operator()
(
	const Handle(Geom2d_Curve)& theCurve
	) const
{
	auto curve = std::make_shared<Marine_WaterLineCurve>(theCurve);
	return std::move(curve);
}

std::shared_ptr<tnbLib::Pln_Curve>
tnbLib::Marine_WaterLineCurve::operator()
(
	Handle(Geom2d_Curve) && theCurve
	) const
{
	auto curve = std::make_shared<Marine_WaterLineCurve>(std::move(theCurve));
	return std::move(curve);
}

std::shared_ptr<tnbLib::Pln_Curve>
tnbLib::Marine_WaterLineCurve::Copy() const
{
	auto c = Handle(Geom2d_Curve)::DownCast(Geometry()->Copy());
	Debug_Null_Pointer(c);

	auto copy = std::make_shared<Marine_WaterLineCurve>(Index(), Name(), c);
	return std::move(copy);
}

std::tuple
<
	std::shared_ptr<tnbLib::Pln_Curve>,
	std::shared_ptr<tnbLib::Pln_Curve>
>
tnbLib::Marine_WaterLineCurve::Split
(
	const Standard_Real x
) const
{
	if (NOT INSIDE(x, FirstParameter(), LastParameter()))
	{
		FatalErrorIn("void Split()")
			<< "Invalid Parameter: " << x << endl
			<< " - First parameter: " << FirstParameter() << endl
			<< " - Last Parameter: " << LastParameter() << endl
			<< abort(FatalError);
	}

	Handle(Geom2d_Curve) C0, C1;
	Pln_Tools::SplitCurve(Geometry(), x, C0, C1);

	return
	{
		std::make_shared<Marine_WaterLineCurve>(C0) ,
		std::make_shared<Marine_WaterLineCurve>(C1)
	};
}

void tnbLib::Marine_WaterLineCurve::Split
(
	const Standard_Real x,
	std::shared_ptr<Pln_Curve>& theLeft,
	std::shared_ptr<Pln_Curve>& theRight
) const
{
	if (NOT INSIDE(x, FirstParameter(), LastParameter()))
	{
		FatalErrorIn("void Split()")
			<< "Invalid Parameter: " << x << endl
			<< " - First parameter: " << FirstParameter() << endl
			<< " - Last Parameter: " << LastParameter() << endl
			<< abort(FatalError);
	}

	Handle(Geom2d_Curve) C0, C1;
	Pln_Tools::SplitCurve(Geometry(), x, C0, C1);

	theLeft = std::make_shared<Marine_WaterLineCurve>(C0);
	theRight = std::make_shared<Marine_WaterLineCurve>(C1);
}

void tnbLib::Marine_WaterLineCurve::Split
(
	const Standard_Real x,
	Pnt2d & theCoord,
	std::shared_ptr<Pln_Curve>& theLeft,
	std::shared_ptr<Pln_Curve>& theRight
) const
{
	if (NOT INSIDE(x, FirstParameter(), LastParameter()))
	{
		FatalErrorIn("void Split()")
			<< "Invalid Parameter: " << x << endl
			<< " - First parameter: " << FirstParameter() << endl
			<< " - Last Parameter: " << LastParameter() << endl
			<< abort(FatalError);
	}

	Handle(Geom2d_Curve) C0, C1;
	Pln_Tools::SplitCurve(Geometry(), x, C0, C1);

	theCoord = Geometry()->Value(x);

	theLeft = std::make_shared<Marine_WaterLineCurve>(C0);
	theRight = std::make_shared<Marine_WaterLineCurve>(C1);
}

std::tuple
<
	std::shared_ptr<tnbLib::Pln_Curve>,
	std::shared_ptr<tnbLib::Pln_Curve>,
	std::shared_ptr<tnbLib::Pln_Curve>
>
tnbLib::Marine_WaterLineCurve::Split
(
	const Cad2d_IntsctEntity_TangSegment & x
) const
{
	const auto x0 = x.Parameter0();
	const auto x1 = x.Parameter1();

	auto[c0, c1] = this->Split(x0);
	auto[c2, c3] = c1->Split(x1);

	auto c2t = std::make_shared<Pln_TangCurve<Marine_WaterLineCurve>>(c2->Geometry());

	auto c = std::make_tuple(c0, c2t, c3);
	return std::move(c);
}