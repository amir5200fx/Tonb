#include <SectPx_FrameTuner.hxx>

#include <SectPx_FrameRegistry.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_FrameTuner)
{
	ar & boost::serialization::base_object<SectPx_Entity>(*this);
	ar & theFrameReg_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_FrameTuner)
{
	ar & boost::serialization::base_object<SectPx_Entity>(*this);
	ar & theFrameReg_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::SectPx_FrameTuner);