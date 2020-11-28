#include <Marine_WireFrameShape_Shape.hxx>

#include <Marine_Shape.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::marineLib::WireFrameShape_Shape)
{
	ar & boost::serialization::base_object<Marine_WireFrameShape>(*this);
	ar & Shape();
}

TNB_LOAD_IMPLEMENTATION(tnbLib::marineLib::WireFrameShape_Shape)
{
	ar & boost::serialization::base_object<Marine_WireFrameShape>(*this);
	ar & ChangeShape();
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::marineLib::WireFrameShape_Shape);