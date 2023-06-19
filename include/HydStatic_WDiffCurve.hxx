#pragma once
#ifndef _HydStatic_WDiffCurve_Header
#define _HydStatic_WDiffCurve_Header

#include <HydStatic_HydCurve.hxx>
#include <HydStatic_GzQ.hxx>

#include <vector>

namespace tnbLib
{

	class HydStatic_WDiffCurve
		: public HydStatic_HydCurve
	{

		/*Private Data*/

		std::vector<HydStatic_GzQ> theQs_;

	public:

		TnbHydStatic_EXPORT HydStatic_WDiffCurve
		(
			const Handle(Geom2d_Curve)& theCurve
		);

		/*TnbHydStatic_EXPORT HydStatic_WDiffCurve
		(
			const Standard_Integer theIndex,
			const Handle(Geom2d_Curve)& theCurve
		);*/

		TnbHydStatic_EXPORT HydStatic_WDiffCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theCurve
		);


		auto& ChangeQs()
		{
			return theQs_;
		}

		const auto& Qs() const
		{
			return theQs_;
		}

		void SetQs
		(
			const std::vector<HydStatic_GzQ>&& theQs
		)
		{
			theQs_ = std::move(theQs);
		}
	};
}

#endif // !_HydStatic_WDiffCurve_Header
