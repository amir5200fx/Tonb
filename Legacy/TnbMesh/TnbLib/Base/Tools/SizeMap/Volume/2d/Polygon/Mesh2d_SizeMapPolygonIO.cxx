#include <Mesh2d_SizeMapPolygon.hxx>

#include <Entity2d_Polygon.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh2d_SizeMapPolygon)
{
	ar& boost::serialization::base_object<Mesh2d_SizeMapVolume>(*this);
	ar& theVolume_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh2d_SizeMapPolygon)
{
	ar& boost::serialization::base_object<Mesh2d_SizeMapVolume>(*this);
	ar& theVolume_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Mesh2d_SizeMapPolygon)