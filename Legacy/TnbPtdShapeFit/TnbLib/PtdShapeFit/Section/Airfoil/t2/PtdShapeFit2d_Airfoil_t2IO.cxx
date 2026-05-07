#include <PtdShapeFit2d_Airfoil_t2.hxx>

#include <PtdShapeFit_Par.hxx>
#include <Geo_Serialization.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::airfoilLib::Type2)
{
	ar& boost::serialization::base_object<PtdShapeFit2d_Airfoil>(*this);

	ar& theDir_;

	ar& theNbPoints_;

	ar& theXo_;
	ar& theYo_;

	ar& theChordLen_;

	ar& theMaxCamb_;
	ar& theMaxCambLoc_;
	ar& theLeadCambSteep_;
	ar& theLeadCambTight_;
	ar& theLeadCambWeight_;
	ar& theTrailCambSteep_;
	ar& theTrailCambTight_;
	ar& theTrailCambWeight_;

	ar& theMaxThick_;
	ar& theMaxThickLoc_;
	ar& theLeadThickSteepTight1_;
	ar& theLeadThickSteepTight2_;
	ar& theTrailThickSteep_;
	ar& theTrailThickSteepTight_;
	ar& theTrailThickSteepVelocity_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::airfoilLib::Type2)
{
	ar& boost::serialization::base_object<PtdShapeFit2d_Airfoil>(*this);

	ar& theDir_;

	ar& theNbPoints_;

	ar& theXo_;
	ar& theYo_;

	ar& theChordLen_;

	ar& theMaxCamb_;
	ar& theMaxCambLoc_;
	ar& theLeadCambSteep_;
	ar& theLeadCambTight_;
	ar& theLeadCambWeight_;
	ar& theTrailCambSteep_;
	ar& theTrailCambTight_;
	ar& theTrailCambWeight_;

	ar& theMaxThick_;
	ar& theMaxThickLoc_;
	ar& theLeadThickSteepTight1_;
	ar& theLeadThickSteepTight2_;
	ar& theTrailThickSteep_;
	ar& theTrailThickSteepTight_;
	ar& theTrailThickSteepVelocity_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::airfoilLib::Type2);