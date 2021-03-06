#include <ShapePx_ContinProfile_OffsetCustom.hxx>

#include <SectPx_ExtrProfile.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::shapePxLib::ContinProfile_OffsetCustom)
{
	ar & boost::serialization::base_object<ContinProfile_Custom>(*this);
	ar & boost::serialization::base_object<Global_Done>(*this);

	ar & theQ_;
	ar & theType_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::shapePxLib::ContinProfile_OffsetCustom)
{
	ar & boost::serialization::base_object<ContinProfile_Custom>(*this);
	ar & boost::serialization::base_object<Global_Done>(*this);

	ar & theQ_;
	ar & theType_;

	if (IsDone())
	{
		Perform();
	}
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::shapePxLib::ContinProfile_OffsetCustom);