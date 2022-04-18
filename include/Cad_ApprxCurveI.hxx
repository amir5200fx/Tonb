#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
template<class CurveType, bool RandSamples>
inline void tnbLib::Cad_ApprxCurve<CurveType, RandSamples>::Perform()
{
	if (NOT Curve())
	{
		FatalErrorIn(FunctionSIG)
			<< "no curve has been loaded!" << endl
			<< abort(FatalError);
	}
	const auto geom = Curve()->Geometry();
	Debug_Null_Pointer(geom);

	const auto fprm = Curve()->FirstParameter();
	const auto lprm = Curve()->LastParameter();

	auto alg = 
		std::make_shared<Geo_ApprxCurve<Handle(geomType), RandSamples>>
		(geom, fprm, lprm, AlgInfo());
	Debug_Null_Pointer(alg);

	alg->Perform();
	Debug_If_Condition_Message(NOT alg->IsDone(), "the application is not performed");

	PolygonRef() = alg->Chain();

	Change_IsDone() = Standard_True;
}