#include <PtdShapeFit2d_Airfoil_t1.hxx>

#include <PtdShapeFit_Par.hxx>
#include <Geo_Serialization.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::airfoilLib::Type1)
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
	ar& theLeadThickSteep_;
	ar& theLeadThickTight_;
	ar& theLeadThickWeight_;
	ar& theTrailThickSteep_;
	ar& theTrailThickTight_;
	ar& theTrailThickWeight_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::airfoilLib::Type1)
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
	ar& theLeadThickSteep_;
	ar& theLeadThickTight_;
	ar& theLeadThickWeight_;
	ar& theTrailThickSteep_;
	ar& theTrailThickTight_;
	ar& theTrailThickWeight_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::airfoilLib::Type1);