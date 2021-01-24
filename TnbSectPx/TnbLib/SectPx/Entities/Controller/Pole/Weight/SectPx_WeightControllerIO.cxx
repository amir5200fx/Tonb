#include <SectPx_WeightController.hxx>

#include <SectPx_Par.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::sectPxLib::WeightController)
{
	ar & boost::serialization::base_object<SectPx_PoleController>(*this);
	ar & theWeight_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::sectPxLib::WeightController)
{
	ar & boost::serialization::base_object<SectPx_PoleController>(*this);
	ar & theWeight_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::sectPxLib::WeightController);