#pragma once
#ifndef _Pln_Vertex_Header
#define _Pln_Vertex_Header

#include <Global_AccessMethod.hxx>
#include <Pln_EntityPrecision.hxx>
#include <Pln_Entity.hxx>
#include <Pln_VertexAdaptor.hxx>
#include <Pnt2d.hxx>

#include <memory>
#include <map>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Edge;

	class Pln_Vertex
		: public Pln_VertexAdaptor
		, public Pln_Entity
		, public Pln_EntityPrecision
	{

		/*Private Data*/

		Pnt2d theCoord_;

	public:

		Pln_Vertex()
		{}

		Pln_Vertex(const Pnt2d& theCoord)
			: theCoord_(theCoord)
		{}

		Pln_Vertex
		(
			const Standard_Integer theIndex, 
			const word& theName,
			const Pnt2d& theCoord
		)
			: Pln_Entity(theIndex, theName)
			, theCoord_(theCoord)
		{}

		Standard_Boolean IsDangle() const;

		Standard_Boolean IsOrphan() const;

		Standard_Boolean IsRingPoint() const;

		Standard_Boolean IsManifold() const;

		Standard_Real Angle() const;

		void RetrieveEdgesTo(std::vector<std::weak_ptr<Pln_Edge>>& theEdges) const;

		static const Pnt2d& GetCoord(const std::shared_ptr<Pln_Vertex>& theVtx);

		//- Macros
		GLOBAL_ACCESS_SINGLE(Pnt2d, Coord)
	};
}

#include <Pln_VertexI.hxx>

#endif // !_Pln_Vertex_Header
