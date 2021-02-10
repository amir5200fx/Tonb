#include <ShapePx_ContinProfile_ThreePoints.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::shapePxLib::ContinProfile_ThreePoints)
{
	ar & boost::serialization::base_object<ContinProfile_Linear>(*this);
	ar & boost::serialization::base_object<Global_Done>(*this);

	ar & theQ2_;
	ar & theType_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::shapePxLib::ContinProfile_ThreePoints)
{
	ar & boost::serialization::base_object<ContinProfile_Linear>(*this);
	ar & boost::serialization::base_object<Global_Done>(*this);

	ar & theQ2_;
	ar & theType_;

	if (IsDone())
	{
		Perform();
	}
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::shapePxLib::ContinProfile_ThreePoints);