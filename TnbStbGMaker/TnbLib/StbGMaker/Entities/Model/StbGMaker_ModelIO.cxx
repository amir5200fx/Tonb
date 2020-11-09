#include <StbGMaker_Model.hxx>

#include <Marine_Models.hxx>

DECLARE_SAVE_IMP(tnbLib::StbGMaker_Model)
{
	ar & boost::serialization::base_object<StbGMaker_Entity>(*this);
	ar & theHull_;
	ar & theTanks_;
	ar & theSails_;
}

DECLARE_LOAD_IMP(tnbLib::StbGMaker_Model)
{
	ar & boost::serialization::base_object<StbGMaker_Entity>(*this);
	ar & theHull_;
	ar & theTanks_;
	ar & theSails_;
}