#pragma once
#ifndef _SectPx_PointMakerM_Header
#define _SectPx_PointMakerM_Header

#define SELECT_MASTER_FROM_PNTMAKER(PNT_MAKER, PNT_ID)  \
	std::dynamic_pointer_cast<SectPx_MasterPnt>(PNT_MAKER->SelectPnt(PNT_ID))

#endif // !_SectPx_PointMakerM_Header
