#pragma once
#ifndef _NModel_PairedManager_Header
#define _NModel_PairedManager_Header

#include <Cad_EntityManager.hxx>

namespace tnbLib
{

	// Forward Declarations
	class NModel_Segment;

	typedef Cad_EntityManager<NModel_Segment>
		NModel_SegmentManager;
}

#endif // !_NModel_PairedManager_Header