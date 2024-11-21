#include <SectPx_KnotVector.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

#include <opencascade/BSplCLib.hxx>

void tnbLib::SectPx_KnotVector::SetDefaults()
{
	theU0_ = 0;
	theU1_ = 1.0;
}

std::vector<Standard_Real> 
tnbLib::SectPx_KnotVector::toKnots
(
	const std::vector<Standard_Real>& Ubar, 
	const Standard_Integer theDeg
)
{
	if (Ubar.size() < 2)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid knot vector" << endl
			<< abort(FatalError);
	}
	std::vector<Standard_Real> Us;
	Us.reserve(Ubar.size() + 2 * theDeg);

	const auto u0 = Ubar[0];
	const auto u1 = Ubar[Ubar.size() - 1];

	for (size_t i = 0; i < theDeg + 1; i++)
		Us.push_back(u0);

	for (size_t i = 1; i < Ubar.size() - 1; i++)
	{
		Us.push_back(Ubar[i]);
	}

	for (size_t i = 0; i < theDeg + 1; i++)
		Us.push_back(u1);

	Debug_If_Condition(Us.size() NOT_EQUAL Ubar.size() + 2 * theDeg);
	return std::move(Us);
}

std::tuple
<
	typename tnbLib::SectPx_KnotVector::knotList, 
	typename tnbLib::SectPx_KnotVector::multList
>
tnbLib::SectPx_KnotVector::Convert
(
	const std::vector<Standard_Real>& seqKnots
)
{
	knotList knots;
	multList mults;

	knotList knotSq(1, seqKnots.size());
	for (size_t i = 1; i <= seqKnots.size(); i++)
	{
		knotSq.SetValue(i, seqKnots[i - 1]);
	}

	BSplCLib::Knots(knotSq, knots, mults);
	auto t = std::make_tuple(std::move(knots), std::move(mults));
	return std::move(t);
}