#include <Mesh2d_SizeMapShape.hxx>

#include <Cad2d_Plane.hxx>
#include <Discret_CurveInfo.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh2d_SizeMapShape)
{
	ar& boost::serialization::base_object<Mesh2d_SizeMapVolume>(*this);
	ar& theInfo_;
	ar& theNbSamples_;
	ar& theSize_;
	ar& theVolume_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh2d_SizeMapShape)
{
	ar& boost::serialization::base_object<Mesh2d_SizeMapVolume>(*this);
	ar& theInfo_;
	ar& theNbSamples_;
	ar& theSize_;
	ar& theVolume_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Mesh2d_SizeMapShape);