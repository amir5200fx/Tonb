#include <StbGMaker_Creator.hxx>

#include <StbGMaker_HullCreator.hxx>
#include <StbGMaker_TankCreator.hxx>
#include <StbGMaker_SailCreator.hxx>

DECLARE_SAVE_IMP(tnbLib::StbGMaker_Creator)
{
	ar & theHullCreator_;
	ar & theTankCreators_;
	ar & theSailCreators_;

	ar & theTankCounter_;
	ar & theSailCounter_;
}

DECLARE_LOAD_IMP(tnbLib::StbGMaker_Creator)
{
	ar & theHullCreator_;
	ar & theTankCreators_;
	ar & theSailCreators_;

	ar & theTankCounter_;
	ar & theSailCounter_;
}