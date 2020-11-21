#include <StbGMaker_GeometricSailCreator_Shape.hxx>

#include <Marine_Shape_Sail.hxx>

DECLARE_SAVE_IMP(tnbLib::stbGmakerLib::GeometricSailCreator_Shape)
{
	ar & boost::serialization::base_object<StbGMaker_GeometricSailCreator>(*this);
	ar & boost::serialization::base_object<StbGMaker_Alg>(*this);
	ar & theShape_;
}

DECLARE_LOAD_IMP(tnbLib::stbGmakerLib::GeometricSailCreator_Shape)
{
	ar & boost::serialization::base_object<StbGMaker_GeometricSailCreator>(*this);
	ar & boost::serialization::base_object<StbGMaker_Alg>(*this);
	ar & theShape_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::stbGmakerLib::GeometricSailCreator_Shape);