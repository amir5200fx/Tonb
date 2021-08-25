#pragma once
#ifndef _TModel_FaceManager_Header
#define _TModel_FaceManager_Header

#include <Cad_EntityManager.hxx>

namespace tnbLib
{

	// Forward Declarations
	class TModel_Surface;

	typedef Cad_EntityManager<TModel_Surface>
		TModel_FaceManager;
}

#endif // !_TModel_FaceManager_Header
