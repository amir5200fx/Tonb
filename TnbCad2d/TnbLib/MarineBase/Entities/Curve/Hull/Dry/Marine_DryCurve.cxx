#include <Marine_DryCurve.hxx>

#include <Pln_Tools.hxx>
#include <Pln_TangCurve.hxx>
#include <Cad2d_IntsctEntity_TangSegment.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2d_Curve.hxx>

tnbLib::Marine_DryCurve::Marine_DryCurve()
{
	// empty body
}

tnbLib::Marine_DryCurve::Marine_DryCurve
(
	const Standard_Integer theIndex,
	const Handle(Geom2d_Curve)& theGeom
)
	: Marine_HullCurve(theIndex, theGeom)
{
	// empty body
}

tnbLib::Marine_DryCurve::Marine_DryCurve
(
	const Handle(Geom2d_Curve)& theGeom
)
	: Marine_HullCurve(theGeom)
{
	// empty body
}

tnbLib::Marine_DryCurve::Marine_DryCurve
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
tnbLib::Marine_DryCurve::operator()
(
	const Handle(Geom2d_Curve)& theCurve
	) const
{
	auto curve = std::make_shared<Marine_DryCurve>(theCurve);
	return std::move(curve);
}

std::shared_ptr<tnbLib::Pln_Curve>
tnbLib::Marine_DryCurve::operator()
(
	Handle(Geom2d_Curve) && theCurve
	) const
{
	auto curve = std::make_shared<Marine_DryCurve>(std::move(theCurve));
	return std::move(curve);
}

std::shared_ptr<tnbLib::Pln_Curve>
tnbLib::Marine_DryCurve::Copy() const
{
	auto c = Handle(Geom2d_Curve)::DownCast(Geometry()->Copy());
	Debug_Null_Pointer(c);

	auto copy = std::make_shared<Marine_DryCurve>(Index(), Name(), c);
	return std::move(copy);
}

std::tuple
<
	std::shared_ptr<tnbLib::Pln_Curve>,
	std::shared_ptr<tnbLib::Pln_Curve>
>
tnbLib::Marine_DryCurve::Split
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
		std::make_shared<Marine_DryCurve>(C0) ,
		std::make_shared<Marine_DryCurve>(C1)
	};
}

void tnbLib::Marine_DryCurve::Split
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

	theLeft = std::make_shared<Marine_DryCurve>(C0);
	theRight = std::make_shared<Marine_DryCurve>(C1);
}

void tnbLib::Marine_DryCurve::Split
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

	theLeft = std::make_shared<Marine_DryCurve>(C0);
	theRight = std::make_shared<Marine_DryCurve>(C1);
}

std::tuple
<
	std::shared_ptr<tnbLib::Pln_Curve>,
	std::shared_ptr<tnbLib::Pln_Curve>,
	std::shared_ptr<tnbLib::Pln_Curve>
>
tnbLib::Marine_DryCurve::Split
(
	const Cad2d_IntsctEntity_TangSegment & x
) const
{
	const auto x0 = x.Parameter0();
	const auto x1 = x.Parameter1();

	std::shared_ptr<Pln_Curve> c0, c1;

	if (std::abs(x0 - FirstParameter()) <= gp::Resolution())
	{
		c0 = nullptr;
		c1 = std::dynamic_pointer_cast<Pln_Curve>(This());
	}
	else
	{
		auto[c0x, c1x] = this->Split(x0);

		c0 = std::move(c0x);
		c1 = std::move(c1x);
	}

	std::shared_ptr<Pln_Curve> c2, c3;
	if (std::abs(x1 - LastParameter()) <= gp::Resolution())
	{
		c3 = nullptr;
		c2 = std::dynamic_pointer_cast<Pln_Curve>(This());
	}
	else
	{
		auto[c2x, c3x] = c1->Split(x1);

		c2 = std::move(c2x);
		c3 = std::move(c3x);
	}

	auto c2t = std::make_shared<Pln_TangCurve<Marine_DryCurve>>(c2->Geometry());

	auto c = std::make_tuple(c0, c2t, c3);
	return std::move(c);
}