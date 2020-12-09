#pragma once
#ifndef _HydStatic_AuCurve_Header
#define _HydStatic_AuCurve_Header

#include <HydStatic_HydCurve.hxx>
#include <HydStatic_GzQ.hxx>

#include <vector>

namespace tnbLib
{

	class HydStatic_AuCurve
		: public HydStatic_HydCurve
	{

		/*Private Data*/

		std::vector<HydStatic_GzQ> theQs_;

	protected:

		TnbHydStatic_EXPORT HydStatic_AuCurve
		(
			const Handle(Geom2d_Curve)& theCurve
		);

		TnbHydStatic_EXPORT HydStatic_AuCurve
		(
			const Handle(Geom2d_Curve)&& theCurve
		);

		TnbHydStatic_EXPORT HydStatic_AuCurve
		(
			const Standard_Integer theIndex, 
			const Handle(Geom2d_Curve)& theCurve
		);

		TnbHydStatic_EXPORT HydStatic_AuCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theCurve
		);

	public:

		auto& ChangeQs()
		{
			return theQs_;
		}

		const auto& Qs() const
		{
			return theQs_;
		}

		void SteQs
		(
			const std::vector<HydStatic_GzQ>&& theQs
		)
		{
			theQs_ = std::move(theQs);
		}

	};
}

#endif // !_HydStatic_AuCurve_Header
