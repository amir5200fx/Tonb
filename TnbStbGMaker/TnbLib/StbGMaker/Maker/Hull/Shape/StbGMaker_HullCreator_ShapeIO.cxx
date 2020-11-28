#include <StbGMaker_HullCreator_Shape.hxx>

#include <Marine_Shapes.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::stbGmakerLib::HullCreator_Shape)
{
	ar & boost::serialization::base_object<StbGMaker_HullCreator>(*this);
	ar & theHull_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::stbGmakerLib::HullCreator_Shape)
{
	ar & boost::serialization::base_object<StbGMaker_HullCreator>(*this);
	ar & theHull_;
}