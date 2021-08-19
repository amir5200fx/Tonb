#include <PtdModel_Shape_PropBlades.hxx>

#include <PtdModel_Shape_PropBlade.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::ptdModel::Shape_PropBlades)
{
	ar & boost::serialization::base_object<Shape_PropEntity>(*this);

	ar & theParent_;
	ar & theChildren_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::ptdModel::Shape_PropBlades)
{
	ar & boost::serialization::base_object<Shape_PropEntity>(*this);

	ar & theParent_;
	ar & theChildren_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::ptdModel::Shape_PropBlades);