#pragma once
namespace tnbLib
{

	template<class CurveType>
	inline std::shared_ptr<CurveType> 
		Cad_ParaGapCurve<CurveType>::CreateCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theGeometry
		) const
	{
		return std::make_shared<Cad_ParaGapCurve>(theIndex, theName, theGeometry);
	}
}