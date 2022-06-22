#include <TModel_ParaCurve.hxx>

#include <Global_Macros.hxx>
#include <Entity2d_Box.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2d_Curve.hxx>
#include <Geom2d_BoundedCurve.hxx>

#include <Bnd_Box2d.hxx>
#include <BndLib_Add2dCurve.hxx>
#include <Pln_Tools.hxx>
#include <TModel_Tools.hxx>

std::shared_ptr<tnbLib::TModel_ParaCurve>
tnbLib::TModel_ParaCurve::Copy() const
{
	const auto& geom = Geometry();
	auto gc = Handle(Geom2d_Curve)::DownCast(geom->Copy());
	Debug_Null_Pointer(gc);

	auto c = std::make_shared<TModel_ParaCurve>(Index(), Name(), std::move(gc));
	return std::move(c);
}

std::shared_ptr<tnbLib::TModel_ParaCurve>
tnbLib::TModel_ParaCurve::Copy
(
	const gp_Trsf2d & t
) const
{
	auto c = Copy();
	Debug_Null_Pointer(c);

	const auto& geom = c->Geometry();
	Debug_Null_Pointer(geom);
	geom->Transform(t);

	return std::move(c);
}

std::pair
<
	std::shared_ptr<tnbLib::TModel_ParaCurve>,
	std::shared_ptr<tnbLib::TModel_ParaCurve>
>
tnbLib::TModel_ParaCurve::Split
(
	const Standard_Real thePar,
	const std::shared_ptr<TModel_ParaCurve>& theCurve
)
{
	auto t = TModel_Tools::Split(thePar, theCurve);
	return std::move(t);
}