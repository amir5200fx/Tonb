#include <SectPx_ScatterRegistry.hxx>

#include <SectPx_RegObj.hxx>

DECLARE_SAVE_IMP(tnbLib::SectPx_ScatterRegistry)
{
	for (size_t i = 0; i < (size_t)SectPx_RegObjType::other; i++)
	{
		ar & theMaps[i];
	}
}

DECLARE_LOAD_IMP(tnbLib::SectPx_ScatterRegistry)
{
	for (size_t i = 0; i < (size_t)SectPx_RegObjType::other; i++)
	{
		ar & theMaps[i];
	}
}