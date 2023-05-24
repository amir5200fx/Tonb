#include <PtdShapeFit2d_AirfoilGlobal_t1.hxx>

#include <PtdShapeFit_Par.hxx>
#include <Geo_Serialization.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::curveLib::airfoilLib::Global_t1)
{
	ar& boost::serialization::base_object<PtdShapeFit2d_AirfoilGlobal>(*this);

	ar& theDir_;

	ar& theXo_;
	ar& theYo_;

	ar& theNoseAngle_;
	ar& theChordLen_;

	ar& theUpperMaxLoc_;
	ar& theUpperMax_;
	ar& theUpperNoseTight_;
	ar& theUpperMaxTight_;
	ar& theUpperMaxVel_;
	ar& theUpperTrailAngle_;
	ar& theUpperTrailVel_;

	ar& theLowerMaxLoc_;
	ar& theLowerMax_;
	ar& theLowerNoseTight_;
	ar& theLowerMaxTight_;
	ar& theLowerMaxVel_;
	ar& theLowerTrailAngle_;
	ar& theLowerTrailVel_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::curveLib::airfoilLib::Global_t1)
{
	ar& boost::serialization::base_object<PtdShapeFit2d_AirfoilGlobal>(*this);

	ar& theDir_;

	ar& theXo_;
	ar& theYo_;

	ar& theNoseAngle_;
	ar& theChordLen_;

	ar& theUpperMaxLoc_;
	ar& theUpperMax_;
	ar& theUpperNoseTight_;
	ar& theUpperMaxTight_;
	ar& theUpperMaxVel_;
	ar& theUpperTrailAngle_;
	ar& theUpperTrailVel_;

	ar& theLowerMaxLoc_;
	ar& theLowerMax_;
	ar& theLowerNoseTight_;
	ar& theLowerMaxTight_;
	ar& theLowerMaxVel_;
	ar& theLowerTrailAngle_;
	ar& theLowerTrailVel_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::curveLib::airfoilLib::Global_t1);