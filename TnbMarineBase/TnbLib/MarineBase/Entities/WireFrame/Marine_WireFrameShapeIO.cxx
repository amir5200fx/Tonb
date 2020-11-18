#include <Marine_WireFrameShape.hxx>

#include <Marine_Body.hxx>

DECLARE_SAVE_IMP(tnbLib::Marine_WireFrameShape)
{
	ar & boost::serialization::base_object<Marine_CoordinatedEntity>(*this);
	ar & Body();
}

DECLARE_LOAD_IMP(tnbLib::Marine_WireFrameShape)
{
	ar & boost::serialization::base_object<Marine_CoordinatedEntity>(*this);
	ar & ChangeBody();
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Marine_WireFrameShape);