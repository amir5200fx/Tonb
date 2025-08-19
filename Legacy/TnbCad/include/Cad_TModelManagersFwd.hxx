#pragma once
#ifndef _Cad_TModelManagersFwd_Header
#define _Cad_TModelManagersFwd_Header

namespace tnbLib
{

	// Forward Declarations
	template<class EntityType>
	class Cad_EntityManager;

	class TModel_Vertex;
	class TModel_Paired;
	class TModel_Surface;

	typedef Cad_EntityManager<TModel_Vertex> TModel_CornerManager;
	typedef Cad_EntityManager<TModel_Paired> TModel_SegmentManager;
	typedef Cad_EntityManager<TModel_Surface> TModel_FaceManager;
}

#endif // !_Cad_TModelManagersFwd_Header
