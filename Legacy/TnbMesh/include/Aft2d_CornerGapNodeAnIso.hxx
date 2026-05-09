#pragma once
#ifndef _Aft2d_CornerGapNodeAnIso_Header
#define _Aft2d_CornerGapNodeAnIso_Header

#include <Aft2d_CornerGapNodeAnIsoFwd.hxx>
#include <Aft2d_GapNodeTemplate.hxx>
#include <Aft2d_CornerNodeAnIso.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT std::shared_ptr<Aft2d_BndEdgeAnIso>
		Aft2d_CornerGapNodeAnIso::BlowThisUp();
}

#endif // !_Aft2d_CornerGapNodeAnIso_Header
