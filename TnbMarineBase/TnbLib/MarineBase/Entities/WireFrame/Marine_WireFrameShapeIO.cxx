#include <Marine_WireFrameShape.hxx>

#include <Marine_Body.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Marine_WireFrameShape)
{
	ar & boost::serialization::base_object<Marine_CoordinatedEntity>(*this);
	ar & Body();
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Marine_WireFrameShape)
{
	ar & boost::serialization::base_object<Marine_CoordinatedEntity>(*this);
	ar & ChangeBody();
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Marine_WireFrameShape);