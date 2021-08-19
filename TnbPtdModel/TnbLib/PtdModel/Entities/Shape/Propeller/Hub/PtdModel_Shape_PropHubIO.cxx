#include <PtdModel_Shape_PropHub.hxx>

#include <PtdModel_Face.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::ptdModel::Shape_PropHub)
{
	ar & boost::serialization::base_object<Shape_PropEntity>(*this);
	ar & theFaces_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::ptdModel::Shape_PropHub)
{
	ar & boost::serialization::base_object<Shape_PropEntity>(*this);
	ar & theFaces_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::ptdModel::Shape_PropHub);