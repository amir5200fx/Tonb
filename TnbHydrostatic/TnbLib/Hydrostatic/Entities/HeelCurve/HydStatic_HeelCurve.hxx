#pragma once
#ifndef _HydStatic_HeelCurve_Header
#define _HydStatic_HeelCurve_Header

#include <HydStatic_HydCurve.hxx>
#include <HydStatic_GzQP.hxx>

namespace tnbLib
{

	// Forward Declarations
	class HydStatic_CmptLib;

	class HydStatic_HeelCurve
		: public HydStatic_HydCurve
	{

		friend class HydStatic_CmptLib;

		/*Private Data*/

		HydStatic_GzQP theQ_;


		void SetGZ(const HydStatic_GzQP&& theQ)
		{
			theQ_ = std::move(theQ);
		}

		void SetGZ(const HydStatic_GzQP& theQ)
		{
			theQ_ = theQ;
		}

		auto& ChangeGZ()
		{
			return theQ_;
		}

	protected:

		HydStatic_HeelCurve
		(
			const Handle(Geom2d_Curve)& theCurve
		);

		HydStatic_HeelCurve
		(
			const Standard_Integer theIndex,
			const Handle(Geom2d_Curve)& theCurve
		);

		HydStatic_HeelCurve
		(
			const Standard_Integer theIndex, 
			const word& theName,
			const Handle(Geom2d_Curve)& theCurve
		);

	public:

		const auto& GZ() const
		{
			return theQ_;
		}
	};
}

#endif // !_HydStatic_HeelCurve_Header
