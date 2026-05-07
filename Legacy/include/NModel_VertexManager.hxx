#pragma once
#ifndef _NModel_VertexManager_Header
#define _NModel_VertexManager_Header

#include <Cad_EntityManager.hxx>

namespace tnbLib
{

	// Forward Declarations
	class NModel_Vertex;

	typedef Cad_EntityManager<NModel_Vertex>
		NModel_VertexManager;
}

#endif // !_NModel_VertexManager_Header
