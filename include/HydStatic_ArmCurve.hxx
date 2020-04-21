#pragma once
#ifndef _HydStatic_ArmCurve_Header
#define _HydStatic_ArmCurve_Header

#include <HydStatic_HydCurve.hxx>
#include <HydStatic_GzQ.hxx>

#include <vector>

namespace tnbLib
{

	class HydStatic_ArmCurve
		: public HydStatic_HydCurve
	{

		/*Private Data*/

		std::vector<HydStatic_GzQ> theQs_;

	protected:

		HydStatic_ArmCurve
		(
			const Handle(Geom2d_Curve)& theCurve
		);

		HydStatic_ArmCurve
		(
			const Standard_Integer theIndex,
			const Handle(Geom2d_Curve)& theCurve
		);

		HydStatic_ArmCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theCurve
		);

	public:

		Standard_Boolean IsIntersect(const Standard_Real thePhi) const;

		Standard_Real MinHeel() const;

		Standard_Real MaxHeel() const;

		Standard_Real Value(const Standard_Real thePhi) const;

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

		static std::shared_ptr<HydStatic_ArmCurve> 
			Clip
			(
				const std::shared_ptr<HydStatic_ArmCurve>& theCurve, 
				const Standard_Real theH0,
				const Standard_Real theH1
			);
	};
}

#endif // !_HydStatic_ArmCurve_Header
