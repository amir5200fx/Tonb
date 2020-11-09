#include <StbGMaker_TankCreator_Shape.hxx>

#include <Marine_Shape_Tank.hxx>

DECLARE_SAVE_IMP(tnbLib::stbGmakerLib::TankCreator_Shape)
{
	ar & boost::serialization::base_object<StbGMaker_TankCreator>(*this);
	ar & theTank_;
}

DECLARE_LOAD_IMP(tnbLib::stbGmakerLib::TankCreator_Shape)
{
	ar & boost::serialization::base_object<StbGMaker_TankCreator>(*this);
	ar & theTank_;
}