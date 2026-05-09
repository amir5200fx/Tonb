#include <StbGMaker_TankCreator_Shape.hxx>

#include <Marine_Shape_Tank.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::stbGmakerLib::TankCreator_Shape)
{
	ar & boost::serialization::base_object<StbGMaker_TankCreator>(*this);
	ar & theTank_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::stbGmakerLib::TankCreator_Shape)
{
	ar & boost::serialization::base_object<StbGMaker_TankCreator>(*this);
	ar & theTank_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::stbGmakerLib::TankCreator_Shape);