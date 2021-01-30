#include <StbGMaker_Model.hxx>

#include <Marine_Models.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::StbGMaker_Model)
{
	ar & boost::serialization::base_object<StbGMaker_Entity>(*this);
	ar & theHull_;
	ar & theTanks_;
	ar & theSails_;

	ar & theWeight_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::StbGMaker_Model)
{
	ar & boost::serialization::base_object<StbGMaker_Entity>(*this);
	ar & theHull_;
	ar & theTanks_;
	ar & theSails_;

	ar & theWeight_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::StbGMaker_Model);