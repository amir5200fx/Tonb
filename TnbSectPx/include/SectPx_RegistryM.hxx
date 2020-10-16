#pragma once
#ifndef _SectPx_RegistryM_Header
#define _SectPx_RegistryM_Header

#define SELECT_PAR_FROM_REGISTRY(REGISTRY, PAR_ID)			\
	std::dynamic_pointer_cast<SectPx_Par>(REGISTRY->SelectObj(PAR_ID))

#define SELECT_PARCLOUD_FROM_REGISTRY(REGISTRY, PAR_ID)			\
	std::dynamic_pointer_cast<SectPx_ParCloud>(REGISTRY->SelectObj(PAR_ID))

#endif // !_SectPx_RegistryM_Header
