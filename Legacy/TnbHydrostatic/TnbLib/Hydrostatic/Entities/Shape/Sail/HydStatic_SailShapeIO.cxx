#include <HydStatic_SailShape.hxx>

#include <Marine_Model_Sail.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::HydStatic_SailShape)
{
	ar & boost::serialization::base_object<HydStatic_Shape>(*this);

	ar & theSail_;

	ar & theArea_;
	ar & theZ_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::HydStatic_SailShape)
{
	ar & boost::serialization::base_object<HydStatic_Shape>(*this);

	ar & theSail_;

	ar & theArea_;
	ar & theZ_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::HydStatic_SailShape);