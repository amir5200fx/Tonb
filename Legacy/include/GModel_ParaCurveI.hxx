#pragma once
namespace tnbLib
{

	inline std::shared_ptr<GModel_ParaCurve>
		tnbLib::GModel_ParaCurve::CreateCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theGeometry
		) const
	{
		return std::make_shared<GModel_ParaCurve>(theIndex, theName, theGeometry);
	}
}