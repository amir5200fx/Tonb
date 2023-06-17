#include <PtdShapeFit2d_TypedAirfoil.hxx>

#include <PtdShapeFit_Par.hxx>
#include <PtdShapeFit2d_TypedAirfoil_Offsets.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::PtdShapeFit2d_TypedAirfoil)
{
	ar& boost::serialization::base_object<PtdShapeFit2d_Airfoil>(*this);

	ar& theDir_;
	
	ar& theXo_;
	ar& theYo_;
	ar& theAngle_;

	ar& theChordLen_;

	ar& theOffsets_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::PtdShapeFit2d_TypedAirfoil)
{
	ar& boost::serialization::base_object<PtdShapeFit2d_Airfoil>(*this);

	ar& theDir_;

	ar& theXo_;
	ar& theYo_;
	ar& theAngle_;

	ar& theChordLen_;

	ar& theOffsets_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::PtdShapeFit2d_TypedAirfoil);