#include <AirfoilPx_PxThickProfile_t1.hxx>

#include <Pln_Curve.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::profileLib::PxThick_t1)
{
	ar& boost::serialization::base_object<AirfoilPx_PxThickProfile>(*this);

	ar& theMax_;
	ar& theMaxLoc_;

	ar& theLeadSteep_;
	ar& theLeadSteepThight_;
	ar& theLeadSteepWeight_;

	ar& theTrailSteep_;
	ar& theTrailSteepThight_;
	ar& theTrailSteepWeight_;

	ar& theCurve_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::profileLib::PxThick_t1)
{
	ar& boost::serialization::base_object<AirfoilPx_PxThickProfile>(*this);

	ar& theMax_;
	ar& theMaxLoc_;

	ar& theLeadSteep_;
	ar& theLeadSteepThight_;
	ar& theLeadSteepWeight_;

	ar& theTrailSteep_;
	ar& theTrailSteepThight_;
	ar& theTrailSteepWeight_;

	ar& theCurve_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::profileLib::PxThick_t1);