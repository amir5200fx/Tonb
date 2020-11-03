#include <Marine_WireFrameShape_Shape.hxx>

#include <Marine_Shape.hxx>

DECLARE_SAVE_IMP(tnbLib::marineLib::WireFrameShape_Shape)
{
	ar & boost::serialization::base_object<Marine_WireFrameShape>(*this);
	ar & Shape();
}

DECLARE_LOAD_IMP(tnbLib::marineLib::WireFrameShape_Shape)
{
	ar & boost::serialization::base_object<Marine_WireFrameShape>(*this);
	ar & ChangeShape();
}