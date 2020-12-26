#include <HydStatic_FloatBody.hxx>

#include <Marine_Body_Dry.hxx>
#include <Marine_Body_Wetted.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::HydStatic_FloatBody)
{
	ar & boost::serialization::base_object<HydStatic_Entity>(*this);
	Marine_Body::Save(ar, theDry_);
	std::cout << "wettttted" << std::endl;
	Marine_Body::Save(ar, theWetted_);
	std::cout << "wettttted1" << std::endl;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::HydStatic_FloatBody)
{
	ar & boost::serialization::base_object<HydStatic_Entity>(*this);
	std::shared_ptr<Marine_Body> dry, wetted;
	Marine_Body::Load(ar, dry);
	Marine_Body::Load(ar, wetted);

	theDry_ = std::dynamic_pointer_cast<marineLib::Body_Dry>(dry);
	theWetted_ = std::dynamic_pointer_cast<marineLib::Body_Wetted>(wetted);
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::HydStatic_FloatBody);