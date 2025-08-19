#pragma once
#ifndef _NModel_SurfaceManager_Header
#define _NModel_SurfaceManager_Header

#include <Cad_EntityManager.hxx>

namespace tnbLib
{

	// Forward Declarations
	class NModel_Surface;

	typedef Cad_EntityManager<NModel_Surface>
		NModel_SurfaceManager;
}

#endif // !_NModel_SurfaceManager_Header