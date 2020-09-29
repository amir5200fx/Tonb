#pragma once
#ifndef _Pln_Edge_Header
#define _Pln_Edge_Header

#include <Pln_Entity.hxx>
#include <Pln_EdgeAdaptor.hxx>
#include <Pln_EdgeGeom.hxx>
#include <OFstream.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Vertex;
	class Pln_Curve;
	class Pln_Wire;
	class Pln_CmpEdge;

	class Pln_Edge
		: public Pln_Entity
		, public Pln_EdgeAdaptor
		, public Pln_EdgeGeom
	{

		/*Private Data*/

		std::shared_ptr<Pln_Vertex> theVtx0_;
		std::shared_ptr<Pln_Vertex> theVtx1_;

	public:

		typedef Pnt2d ptType;

		Pln_Edge()
		{}

		Pln_Edge
		(
			const std::shared_ptr<Pln_Vertex>& theVtx0, 
			const std::shared_ptr<Pln_Vertex>& theVtx1,
			const Standard_Boolean Sense = Standard_True
		)
			: theVtx0_(theVtx0)
			, theVtx1_(theVtx1)
			, Pln_EdgeGeom(Sense)
		{}

		Pln_Edge
		(
			const std::shared_ptr<Pln_Vertex>&& theVtx0,
			const std::shared_ptr<Pln_Vertex>&& theVtx1,
			const Standard_Boolean Sense = Standard_True
		)
			: theVtx0_(std::move(theVtx0))
			, theVtx1_(std::move(theVtx1))
			, Pln_EdgeGeom(Sense)
		{}

		Pln_Edge
		(
			const std::shared_ptr<Pln_Vertex>& theVtx0,
			const std::shared_ptr<Pln_Vertex>& theVtx1,
			const std::shared_ptr<Pln_Curve>& theCurve,
			const Standard_Boolean Sense = Standard_True
		)
			: Pln_EdgeGeom(theCurve, Sense)
			, theVtx0_(theVtx0)
			, theVtx1_(theVtx1)
		{}

		Pln_Edge
		(
			const std::shared_ptr<Pln_Vertex>&& theVtx0,
			const std::shared_ptr<Pln_Vertex>&& theVtx1,
			const std::shared_ptr<Pln_Curve>&& theCurve,
			const Standard_Boolean Sense = Standard_True
		)
			: Pln_EdgeGeom(std::move(theCurve), Sense)
			, theVtx0_(std::move(theVtx0))
			, theVtx1_(std::move(theVtx1))
		{}

		Pln_Edge
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<Pln_Vertex>& theVtx0,
			const std::shared_ptr<Pln_Vertex>& theVtx1,
			const Standard_Boolean Sense = Standard_True
		)
			: Pln_Entity(theIndex)
			, Pln_EdgeGeom(Sense)
			, theVtx0_(theVtx0)
			, theVtx1_(theVtx1)
		{}

		Pln_Edge
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<Pln_Vertex>&& theVtx0,
			const std::shared_ptr<Pln_Vertex>&& theVtx1,
			const Standard_Boolean Sense = Standard_True
		)
			: Pln_Entity(theIndex)
			, Pln_EdgeGeom(Sense)
			, theVtx0_(std::move(theVtx0))
			, theVtx1_(std::move(theVtx1))
		{}

		Pln_Edge
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<Pln_Vertex>& theVtx0,
			const std::shared_ptr<Pln_Vertex>& theVtx1,
			const Standard_Boolean Sense = Standard_True
		)
			: Pln_Entity(theIndex, theName)
			, Pln_EdgeGeom(Sense)
			, theVtx0_(theVtx0)
			, theVtx1_(theVtx1)
		{}

		Pln_Edge
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<Pln_Vertex>&& theVtx0,
			const std::shared_ptr<Pln_Vertex>&& theVtx1,
			const Standard_Boolean Sense = Standard_True
		)
			: Pln_Entity(theIndex, theName)
			, Pln_EdgeGeom(Sense)
			, theVtx0_(std::move(theVtx0))
			, theVtx1_(std::move(theVtx1))
		{}

		Pln_Edge
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<Pln_Vertex>& theVtx0,
			const std::shared_ptr<Pln_Vertex>& theVtx1,
			const std::shared_ptr<Pln_Curve>& theCurve,
			const Standard_Boolean Sense = Standard_True
		)
			: Pln_Entity(theIndex, theName)
			, Pln_EdgeGeom(theCurve, Sense)
			, theVtx0_(theVtx0)
			, theVtx1_(theVtx1)
		{}

		Pln_Edge
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<Pln_Vertex>&& theVtx0,
			const std::shared_ptr<Pln_Vertex>&& theVtx1,
			const std::shared_ptr<Pln_Curve>&& theCurve,
			const Standard_Boolean Sense = Standard_True
		)
			: Pln_Entity(theIndex, theName)
			, Pln_EdgeGeom(std::move(theCurve), Sense)
			, theVtx0_(std::move(theVtx0))
			, theVtx1_(std::move(theVtx1))
		{}

		Standard_Boolean IsDangle() const;

		Standard_Boolean IsOrphan() const override;

		Standard_Integer NbEntities(const Pln_EntityType t) const override;

		Standard_Integer GetIndex
		(
			const std::shared_ptr<Pln_Vertex>& theVertex
		) const;

		Standard_Real Parameter
		(
			const Standard_Integer theIndex
		) const;

		const std::shared_ptr<Pln_Vertex>& Vtx0() const
		{
			return theVtx0_;
		}

		const std::shared_ptr<Pln_Vertex>& Vtx1() const
		{
			return theVtx1_;
		}

		Entity2d_Box BoundingBox(const Standard_Real Tol) const override;

		std::shared_ptr<Pln_Entity>
			Copy() const override;

		Pln_EntityType Type() const override;

		//- WARNING! the edge must be orphan for transforming
		void Transform(const gp_Trsf2d& t) override;

		void RetrieveEntitiesTo
		(
			std::vector<std::shared_ptr<Pln_Entity>>& theEntities,
			const Pln_EntityType t
		) const override;

		void Reverse
		(
			const Standard_Boolean ApplyToMesh = Standard_True
		);

		void ExportToPlt(OFstream& File) const;

		//- virtual functions

		virtual Standard_Boolean IsRing() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsCutter() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsIntersect() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsTangential() const
		{
			return Standard_False;
		}

		//- static functions

		static Standard_Boolean
			IsLess
			(
				const std::shared_ptr<Pln_Edge>& theEdge0,
				const std::shared_ptr<Pln_Edge>& theEdge1
			);

		static Standard_Boolean 
			IsConnected
			(
				const std::shared_ptr<Pln_Edge>& theEdge0, 
				const std::shared_ptr<Pln_Edge>& theEdge1,
				std::shared_ptr<Pln_Vertex>& theVtx
			);

	};
}

#include <Pln_EdgeI.hxx>

#endif // !_Pln_Edge_Header
