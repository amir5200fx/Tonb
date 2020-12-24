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


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<HydStatic_HydCurve>(*this);
			ar & theHeel_;
		}

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

	protected:


		//- default constructor for serializing
		HydStatic_CrsCurve()
		{}

	public:


		//- constructors

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


		//- public functions and operators

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


BOOST_CLASS_EXPORT_KEY(tnbLib::HydStatic_CrsCurve);

#endif // !_HydStatic_CrsCurve_Header
