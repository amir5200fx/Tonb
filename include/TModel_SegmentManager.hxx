#pragma once
#ifndef _TModel_SegmentManager_Header
#define _TModel_SegmentManager_Header

#include <Cad_EntityManager.hxx>

namespace tnbLib
{

	// Forward Declarations
	class TModel_Paired;

	typedef Cad_EntityManager<TModel_Paired>
		TModel_SegmentManager;
}

#endif // !_TModel_SegmentManager_Header
