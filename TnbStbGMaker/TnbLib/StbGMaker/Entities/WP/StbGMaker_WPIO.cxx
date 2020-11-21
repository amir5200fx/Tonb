#include <StbGMaker_WP.hxx>

#include <Cad2d_Modeler.hxx>

DECLARE_SAVE_IMP(tnbLib::StbGMaker_WP)
{
	ar & boost::serialization::base_object<StbGMaker_Entity>(*this);
	ar & theModeler_;
	ar & theX_;
}

DECLARE_LOAD_IMP(tnbLib::StbGMaker_WP)
{
	ar & boost::serialization::base_object<StbGMaker_Entity>(*this);
	ar & theModeler_;
	ar & theX_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::StbGMaker_WP);