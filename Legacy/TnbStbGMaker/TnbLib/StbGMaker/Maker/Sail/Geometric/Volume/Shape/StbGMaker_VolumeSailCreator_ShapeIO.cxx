#include <StbGMaker_VolumeSailCreator_Shape.hxx>

#include <Marine_Shape_Sail.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::stbGmakerLib::VolumeSailCreator_Shape)
{
	ar & boost::serialization::base_object<StbGMaker_VolumeSailCreator>(*this);
	ar & boost::serialization::base_object<StbGMaker_Alg>(*this);
	ar & theShape_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::stbGmakerLib::VolumeSailCreator_Shape)
{
	ar & boost::serialization::base_object<StbGMaker_VolumeSailCreator>(*this);
	ar & boost::serialization::base_object<StbGMaker_Alg>(*this);
	ar & theShape_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::stbGmakerLib::VolumeSailCreator_Shape);