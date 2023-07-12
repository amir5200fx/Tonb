#pragma once
#include <MarineBase_Tools.hxx>
#include <HydStatic_CurveMaker.hxx>
#include <HydStatic_GzQP.hxx>

#include <vector>

namespace tnbLib
{

	template<class CurveType>
	inline std::shared_ptr<CurveType>
		HydStatic_Tools::MakeRightCurve
		(
			const std::vector<marineLib::xSectionParam>& theQs,
			const hydStcLib::CurveMakerType t
		)
	{
		const auto curve = MarineBase_Tools::Curve(theQs);

		const auto rArm = hydStcLib::MakeCurve<CurveType>(std::move(curve), t);

		std::vector<HydStatic_GzQP> Qs;
		Qs.reserve(theQs.size());

		for (const auto& x : theQs)
		{
			HydStatic_GzQP par(x.x, x.value, 0);
			Qs.push_back(std::move(par));
		}

		rArm->SetQs(std::move(Qs));
		return std::move(rArm);
	}
}