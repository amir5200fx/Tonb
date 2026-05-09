#include <SectPx_UniKnots.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

#include <opencascade/BSplCLib.hxx>

//std::vector<Standard_Real> 
//tnbLib::SectPx_UniKnots::CreateKnots
//(
//	const std::vector<std::shared_ptr<SectPx_Coord>>& theCoords, 
//	const Standard_Integer degree
//) const
//{
//	const auto n = (Standard_Integer)theCoords.size();
//	const auto p = degree;
//
//	if (n - p < 0)
//	{
//		FatalErrorIn(FunctionSIG)
//			<< "impractical situation has been occurred!" << endl
//			<< "n = " << n << endl
//			<< "p = " << p << endl
//			<< abort(FatalError);
//	}
//
//	std::vector<Standard_Real> Ubar;
//	Ubar.reserve(n - p);
//
//	if (U1() <= U0())
//	{
//		FatalErrorIn(FunctionSIG)
//			<< "U1 parameter is less than U0" << endl
//			<< "U0 = " << U0() << endl
//			<< "U1 = " << U1() << endl
//			<< abort(FatalError);
//	}
//
//	const auto du = (U1() - U0()) / (Standard_Real)(n - p + 1);
//
//	for (size_t i = 0; i < n - p; i++)
//	{
//		auto u = i * du + U0();
//		Ubar.push_back(u);
//	}
//
//	auto Us = toKnots(Ubar, p);
//	return std::move(Us);
//}

std::vector<Standard_Real>
tnbLib::SectPx_UniKnots::CreateKnots
(
	const std::vector<Pnt2d>& theCoords,
	const Standard_Integer degree
) const
{
	const auto n = (Standard_Integer)theCoords.size();
	const auto p = degree;

	if (n - p < 0)
	{
		FatalErrorIn(FunctionSIG)
			<< "impractical situation has been occurred!" << endl
			<< "n = " << n << endl
			<< "p = " << p << endl
			<< abort(FatalError);
	}

	std::vector<Standard_Real> Ubar;
	Ubar.reserve(n - p);

	if (U1() <= U0())
	{
		FatalErrorIn(FunctionSIG)
			<< "U1 parameter is less than U0" << endl
			<< "U0 = " << U0() << endl
			<< "U1 = " << U1() << endl
			<< abort(FatalError);
	}

	const auto du = (U1() - U0()) / (Standard_Real)(n - p + 1);

	for (size_t i = 0; i < n - p; i++)
	{
		auto u = i * du + U0();
		Ubar.push_back(u);
	}

	auto Us = toKnots(Ubar, p);
	return std::move(Us);
}