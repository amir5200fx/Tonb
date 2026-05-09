#pragma once
#ifndef _NModel_Vertex_Header
#define _NModel_Vertex_Header

#include <Cad_EntityPrecision.hxx>
#include <Global_AccessMethod.hxx>
#include <NModel_Entity.hxx>
#include <NModel_VertexAdaptor.hxx>
#include <Pnt3d.hxx>

namespace tnbLib
{

	class NModel_Vertex
		: public NModel_Entity
		, public NModel_VertexAdaptor
	{

		/*Private Data*/

		Pnt3d theCoord_;

	public:

		NModel_Vertex
		(
			const Standard_Integer theIndex
		)
			: NModel_Entity(theIndex)
		{}

		NModel_Vertex
		(
			const Standard_Integer theIndex,
			const Pnt3d& theCoord
		)
			: NModel_Entity(theIndex)
			, theCoord_(theCoord)
		{}

		NModel_Vertex
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Pnt3d& theCoord
		)
			: NModel_Entity(theIndex, theName)
			, theCoord_(theCoord)
		{}

		Standard_Integer NbRings() const;

		Standard_Boolean IsOrphan() const;

		//- Macros
		GLOBAL_ACCESS_SINGLE(Pnt3d, Coord)
	};
}

#endif // !_NModel_Vertex_Header