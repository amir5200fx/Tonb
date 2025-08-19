#include <StbGMaker_Creator.hxx>

#include <StbGMaker_HullCreator.hxx>
#include <StbGMaker_TankCreator.hxx>
#include <StbGMaker_SailCreator.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::StbGMaker_Creator)
{
	ar & theHullCreator_;
	ar & theTankCreators_;
	ar & theSailCreators_;

	ar & theTankCounter_;
	ar & theSailCounter_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::StbGMaker_Creator)
{
	ar & theHullCreator_;
	ar & theTankCreators_;
	ar & theSailCreators_;

	ar & theTankCounter_;
	ar & theSailCounter_;
}