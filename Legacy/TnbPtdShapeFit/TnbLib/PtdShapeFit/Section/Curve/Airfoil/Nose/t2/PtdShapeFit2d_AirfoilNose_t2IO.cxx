#include <PtdShapeFit2d_AirfoilNose_t2.hxx>

#include <PtdShapeFit_Par.hxx>
#include <Geo_Serialization.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::curveLib::airfoilLib::Type2)
{
	ar& boost::serialization::base_object<PtdShapeFit2d_AirfoilNose>(*this);

	ar& theDir_;

	ar& theXo_;
	ar& theYo_;

	ar& theNoseAngle_;

	ar& theUpperMaxLoc_;
	ar& theUpperMax_;
	ar& theUpperMaxAngle_;
	ar& theUpperNoseTight_;
	ar& theUpperTight_;

	ar& theLowerMaxLoc_;
	ar& theLowerMax_;
	ar& theLowerMaxAngle_;
	ar& theLowerNoseTight_;
	ar& theLowerTight_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::curveLib::airfoilLib::Type2)
{
	ar& boost::serialization::base_object<PtdShapeFit2d_AirfoilNose>(*this);

	ar& theDir_;

	ar& theXo_;
	ar& theYo_;

	ar& theNoseAngle_;

	ar& theUpperMaxLoc_;
	ar& theUpperMax_;
	ar& theUpperMaxAngle_;
	ar& theUpperNoseTight_;
	ar& theUpperTight_;

	ar& theLowerMaxLoc_;
	ar& theLowerMax_;
	ar& theLowerMaxAngle_;
	ar& theLowerNoseTight_;
	ar& theLowerTight_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::curveLib::airfoilLib::Type2);