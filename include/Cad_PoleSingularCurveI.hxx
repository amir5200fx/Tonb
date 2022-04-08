#pragma once
#ifdef _DEBUG
#include <TnbError.hxx>
#include <OSstream.hxx>
#endif // _DEBUG
template<class CurveType>
inline void tnbLib::Cad_PoleSingularCurve<CurveType>::CalcSubcurves() const
{
#ifdef _DEBUG
	FatalErrorIn(FunctionSIG)
		<< "It's not supposed to be called!" << endl
		<< abort(FatalError);
#endif // !_DEBUG
}