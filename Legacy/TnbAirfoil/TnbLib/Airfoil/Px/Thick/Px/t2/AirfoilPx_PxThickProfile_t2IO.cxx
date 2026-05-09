#include <AirfoilPx_PxThickProfile_t2.hxx>

#include <Pln_Curve.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::profileLib::PxThick_t2)
{
	ar& boost::serialization::base_object<AirfoilPx_PxThickProfile>(*this);

	ar& theMax_;
	ar& theMaxLoc_;

	ar& theLeadSteepTight1_;
	ar& theLeadSteepTight2_;

	ar& theTrailSteepTight_;
	ar& theTrailSteep_;
	ar& theTrailSteepVelocity_;

	ar& theCurve_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::profileLib::PxThick_t2)
{
	ar& boost::serialization::base_object<AirfoilPx_PxThickProfile>(*this);

	ar& theMax_;
	ar& theMaxLoc_;

	ar& theLeadSteepTight1_;
	ar& theLeadSteepTight2_;

	ar& theTrailSteepTight_;
	ar& theTrailSteep_;
	ar& theTrailSteepVelocity_;

	ar& theCurve_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::profileLib::PxThick_t2);