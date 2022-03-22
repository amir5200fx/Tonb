#pragma once
#ifndef _Pln_Vertex_Header
#define _Pln_Vertex_Header

#include <Global_AccessMethod.hxx>
#include <Pln_EntityPrecision.hxx>
#include <Pln_Entity.hxx>
#include <Pln_VertexAdaptor.hxx>
#include <Pnt2d.hxx>

class gp_Trsf2d;

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


		/*private functions and operators*/

		TNB_SERIALIZATION(TnbCad2d_EXPORT);

	public:

		typedef Pnt2d ptType;


		//- default constructor

		Pln_Vertex()
		{}


		//- constructors

		Pln_Vertex
		(
			const Pnt2d& theCoord
		)
			: theCoord_(theCoord)
		{}

		Pln_Vertex
		(
			Pnt2d&& theCoord
		)
			: theCoord_(std::move(theCoord))
		{}

		Pln_Vertex
		(
			const Standard_Integer theIndex,
			const Pnt2d& theCoord
		)
			: Pln_Entity(theIndex)
			, theCoord_(theCoord)
		{}

		Pln_Vertex
		(
			const Standard_Integer theIndex,
			Pnt2d&& theCoord
		)
			: Pln_Entity(theIndex)
			, theCoord_(std::move(theCoord))
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

		Pln_Vertex
		(
			const Standard_Integer theIndex,
			const word& theName,
			Pnt2d&& theCoord
		)
			: Pln_Entity(theIndex, theName)
			, theCoord_(std::move(theCoord))
		{}


		//- public functions and operators

		inline Standard_Boolean IsDangle() const;

		TnbCad2d_EXPORT Standard_Boolean IsRingPoint() const;
		TnbCad2d_EXPORT Standard_Boolean IsManifold() const;

		TnbCad2d_EXPORT Standard_Real Angle() const;
		TnbCad2d_EXPORT Standard_Real CalcGap() const;

		TnbCad2d_EXPORT std::shared_ptr<Pln_Edge> BackWardEdge() const;
		TnbCad2d_EXPORT std::shared_ptr<Pln_Edge> ForwardEdge() const;

		inline Standard_Integer NbEntities(const Pln_EntityType t) const override;

		TnbCad2d_EXPORT Standard_Boolean IsOrphan() const override;

		TnbCad2d_EXPORT Entity2d_Box BoundingBox(const Standard_Real Tol) const override;

		TnbCad2d_EXPORT std::shared_ptr<Pln_Entity>
			Copy() const override;

		TnbCad2d_EXPORT Pln_EntityType Type() const override;

		TnbCad2d_EXPORT void Transform(const gp_Trsf2d& t) override;

		TnbCad2d_EXPORT void RetrieveEntitiesTo
		(
			std::vector<std::shared_ptr<Pln_Entity>>& theEntities,
			const Pln_EntityType t
		) const override;


		//- virtual functions

		virtual Standard_Boolean IsCutter() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsIntersect() const
		{
			return Standard_False;
		}

		//- static functions

		static inline const Pnt2d&
			GetCoord
			(
				const std::shared_ptr<Pln_Vertex>& theVtx
			);

		static inline Standard_Boolean
			IsLess
			(
				const std::shared_ptr<Pln_Vertex>& theVtx0,
				const std::shared_ptr<Pln_Vertex>& theVtx1
			);

		//- Macros
		GLOBAL_ACCESS_SINGLE(Pnt2d, Coord)
	};
}

#include <Pln_VertexI.hxx>

BOOST_CLASS_EXPORT_KEY(tnbLib::Pln_Vertex);

#endif // !_Pln_Vertex_Header
