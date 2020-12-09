#pragma once
#ifndef _HydStatic_CrsCurve_Header
#define _HydStatic_CrsCurve_Header

#include <HydStatic_HydCurve.hxx>

namespace tnbLib
{

	// Forward Declarations
	class HydStatic_CrossCurves;

	class HydStatic_CrsCurve
		: public HydStatic_HydCurve
	{

		friend class HydStatic_CrossCurves;

		/*Private Data*/

		Standard_Real theHeel_;


		auto& ChangeHeel()
		{
			return theHeel_;
		}

		void SetHeel
		(
			const Standard_Real theHeel
		)
		{
			theHeel_ = theHeel;
		}

	public:

		TnbHydStatic_EXPORT HydStatic_CrsCurve
		(
			const Handle(Geom2d_Curve)& theCurve,
			const Standard_Real theHeel
		);

		TnbHydStatic_EXPORT HydStatic_CrsCurve
		(
			const Standard_Integer theIndex,
			const Handle(Geom2d_Curve)& theCurve,
			const Standard_Real theHeel
		);

		TnbHydStatic_EXPORT HydStatic_CrsCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theCurve,
			const Standard_Real theHeel
		);

		auto Heel() const
		{
			return theHeel_;
		}	

		TnbHydStatic_EXPORT Standard_Boolean IsIntersect(const Standard_Real theVolume) const;

		TnbHydStatic_EXPORT Standard_Real LeverArm0() const;

		TnbHydStatic_EXPORT Standard_Real LeverArm1() const;

		TnbHydStatic_EXPORT Standard_Real Value(const Standard_Real theVolume) const;

		
	};
}

#endif // !_HydStatic_CrsCurve_Header
