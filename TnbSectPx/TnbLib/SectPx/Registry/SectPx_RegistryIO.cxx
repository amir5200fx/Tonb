#include <SectPx_Registry.hxx>

#include <SectPx_CountRegistry.hxx>
#include <SectPx_ScatterRegistry.hxx>
#include <SectPx_ParRegistry.hxx>
#include <SectPx_FrameRegistry.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_Registry)
{
	ar & theCounter_;
	ar & theFrames_;
	ar & theParameter_;
	ar & theScatter_;
	ar & theFrameCounter_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_Registry)
{
	ar & theCounter_;
	ar & theFrames_;
	ar & theParameter_;
	ar & theScatter_;
	ar & theFrameCounter_;
}
