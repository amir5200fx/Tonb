#include <Cad_gLineSingularCurve.hxx>

#include <GModel_ParaCurve.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
std::pair
<
	std::shared_ptr<tnbLib::Aft2d_gPlnCurveSurface>,
	std::shared_ptr<tnbLib::Aft2d_gPlnCurveSurface>
> 
tnbLib::Cad_gLineSingularCurve::Split(const Standard_Real x) const
{
	Debug_Null_Pointer(Curve());
	auto[c0, c1] = GModel_ParaCurve::Split(x, Curve());
	if (NOT c0)
	{
		FatalErrorIn(FunctionSIG)
			<< "the curve is null" << endl
			<< abort(FatalError);
	}
	if (NOT c1)
	{
		FatalErrorIn(FunctionSIG)
			<< "the curve is null" << endl
			<< abort(FatalError);
	}
	auto C0 = std::make_shared<Cad_gLineSingularCurve>(std::move(c0));
	auto C1 = std::make_shared<Cad_gLineSingularCurve>(std::move(c1));
	auto t = std::make_pair(std::move(C0), std::move(C1));
	return std::move(t);
}