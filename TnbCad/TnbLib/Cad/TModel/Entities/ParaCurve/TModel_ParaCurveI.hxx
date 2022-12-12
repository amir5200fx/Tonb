#pragma once
namespace tnbLib
{

	inline std::shared_ptr<TModel_ParaCurve> 
		TModel_ParaCurve::CreateCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theGeometry
		) const
	{
		return std::make_shared<TModel_ParaCurve>(theIndex, theName, theGeometry);
	}
}