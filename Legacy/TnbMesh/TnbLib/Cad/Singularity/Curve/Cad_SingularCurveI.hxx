#pragma once
template<class CurveType>
inline Standard_Boolean 
tnbLib::Cad_SingularCurve<CurveType>::IsSingular() const
{
	return Standard_True;
}

template<class CurveType>
inline void tnbLib::Cad_SingularCurve<CurveType>::OrientWith
(
	const std::shared_ptr<CurveType>& theCurve
)
{
	const auto[P0, P1] = CurveType::BoundCoords();
	const auto Q = theCurve->LastCoord();

	//std::cout << "dis1: " << Q.Distance(P1) << ",  dis0: " << Q.Distance(P0) << std::endl;
	if (Q.Distance(P1) < Q.Distance(P0))
	{
		//std::cout << "reverse..." << std::endl;
		CurveType::Reverse();
	}
}