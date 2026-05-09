#include <AirfoilPx_PxCamberProfile_t1.hxx>

#include <Pln_Curve.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::profileLib::CamberProfile_t1)
{
	ar& boost::serialization::base_object<AirfoilPx_PxCamberProfile>(*this);

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

TNB_LOAD_IMPLEMENTATION(tnbLib::profileLib::CamberProfile_t1)
{
	ar& boost::serialization::base_object<AirfoilPx_PxCamberProfile>(*this);

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

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::profileLib::CamberProfile_t1);