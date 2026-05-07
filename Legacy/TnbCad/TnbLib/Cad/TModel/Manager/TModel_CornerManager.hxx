#pragma once
#ifndef _TModel_CornerManager_Header
#define _TModel_CornerManager_Header

#include <Cad_EntityManager.hxx>

namespace tnbLib
{

	// Forward Declarations
	class TModel_Vertex;

	typedef Cad_EntityManager<TModel_Vertex>
		TModel_CornerManager;
}

#endif // !_TModel_CornerManager_Header
