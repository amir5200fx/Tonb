#include <PtdShapeFit2d_AirfoilLeading_t1.hxx>

#include <PtdShapeFit_Par.hxx>
#include <Geo_Serialization.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::curveLib::airfoilLib::Leading_t1)
{
	ar& boost::serialization::base_object<PtdShapeFit2d_AirfoilLeading>(*this);

	ar& theDir_;

	ar& theXo_;
	ar& theYo_;

	ar& theNoseAngle_;

	ar& theUpperMaxLoc_;
	ar& theUpperMax_;
	ar& theUpperMaxAngle_;
	std::cout << theUpperMaxAngle_ << std::endl;
	ar& theUpperTight_;
	std::cout << theUpperTight_ << std::endl;
	ar& theUpperWeight0_;
	ar& theUpperWeight1_;
	ar& theUpperWeight2_;

	ar& theLowerMaxLoc_;
	ar& theLowerMax_;
	ar& theLowerMaxAngle_;
	ar& theLowerTight_;
	ar& theLowerWeight0_;
	ar& theLowerWeight1_;
	ar& theLowerWeight2_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::curveLib::airfoilLib::Leading_t1)
{
	ar& boost::serialization::base_object<PtdShapeFit2d_AirfoilLeading>(*this);

	ar& theDir_;

	ar& theXo_;
	ar& theYo_;

	ar& theNoseAngle_;

	ar& theUpperMaxLoc_;
	ar& theUpperMax_;
	ar& theUpperMaxAngle_;
	std::cout << theUpperMaxAngle_ << std::endl;
	ar& theUpperTight_;
	std::cout << theUpperTight_ << std::endl;
	ar& theUpperWeight0_;
	ar& theUpperWeight1_;
	ar& theUpperWeight2_;

	ar& theLowerMaxLoc_;
	ar& theLowerMax_;
	ar& theLowerMaxAngle_;
	ar& theLowerTight_;
	ar& theLowerWeight0_;
	ar& theLowerWeight1_;
	ar& theLowerWeight2_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::curveLib::airfoilLib::Leading_t1);