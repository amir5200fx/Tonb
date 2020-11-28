#include <StbGMaker_WP.hxx>

#include <Cad2d_Modeler.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::StbGMaker_WP)
{
	ar & boost::serialization::base_object<StbGMaker_Entity>(*this);
	ar & theModeler_;
	ar & theX_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::StbGMaker_WP)
{
	ar & boost::serialization::base_object<StbGMaker_Entity>(*this);
	ar & theModeler_;
	ar & theX_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::StbGMaker_WP);