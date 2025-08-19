#include <SectPx_ScatterRegistry.hxx>

#include <SectPx_RegObj.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_ScatterRegistry)
{
	for (size_t i = 0; i < (size_t)SectPx_RegObjType::other; i++)
	{
		ar & theMaps[i];
	}
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_ScatterRegistry)
{
	for (size_t i = 0; i < (size_t)SectPx_RegObjType::other; i++)
	{
		ar & theMaps[i];
	}
}