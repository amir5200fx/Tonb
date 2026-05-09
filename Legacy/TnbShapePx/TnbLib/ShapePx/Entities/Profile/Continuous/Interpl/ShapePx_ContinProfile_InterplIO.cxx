#include <ShapePx_ContinProfile_Interpl.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::shapePxLib::ContinProfile_Interpl)
{
	ar & boost::serialization::base_object<ShapePx_ContinProfile>(*this);
	ar & boost::serialization::base_object<Global_Done>(*this);

	ar & theQs_;
	ar & theType_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::shapePxLib::ContinProfile_Interpl)
{
	ar & boost::serialization::base_object<ShapePx_ContinProfile>(*this);
	ar & boost::serialization::base_object<Global_Done>(*this);

	ar & theQs_;
	ar & theType_;

	if (IsDone())
	{
		Perform();
	}
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::shapePxLib::ContinProfile_Interpl);