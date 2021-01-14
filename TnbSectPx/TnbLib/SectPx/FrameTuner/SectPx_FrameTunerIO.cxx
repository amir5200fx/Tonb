#include <SectPx_FrameTuner.hxx>

#include <SectPx_ParRegistry.hxx>
#include <SectPx_FrameRegistry.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_FrameTuner)
{
	ar & boost::serialization::base_object<SectPx_Entity>(*this);
	ar & theParRegistry_;
	ar & theFrameReg_;
	ar & IsLoaded_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_FrameTuner)
{
	ar & boost::serialization::base_object<SectPx_Entity>(*this);
	ar & theParRegistry_;
	ar & theFrameReg_;
	ar & IsLoaded_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::SectPx_FrameTuner);

void tnbLib::SectPx_FrameTuner::PrintRegistry() const
{
	Debug_Null_Pointer(ParRegistry());
	ParRegistry()->Print(Info);

	Debug_Null_Pointer(FrameRegistry());
	FrameRegistry()->Print(Info);
}