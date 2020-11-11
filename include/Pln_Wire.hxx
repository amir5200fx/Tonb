#pragma once
#ifndef _Pln_Wire_Header
#define _Pln_Wire_Header

#include <Pln_Entity.hxx>
#include <Pln_WireAdaptor.hxx>
#include <Pln_WireAux.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <OFstream.hxx>

class gp_Trsf2d;

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Edge;
	class Pln_Curve;
	class Pln_Vertex;
	class Pln_CmpEdge;
	class Cad2d_Plane;
	class Geo_ApprxCurve_Info;

	class Pln_Wire
		: public Pln_Entity
		, public Pln_WireAdaptor
		, public Pln_WireAux
	{

		friend class Cad2d_Plane;

		using Pln_WireAux::BoundingBox;

		/*Private Data*/


		std::shared_ptr<Pln_CmpEdge> theEdges_;


		/*private functions and operators*/

		DECLARE_SAVE_LOAD_HEADER(TnbCad2d_EXPORT);


		auto& ChangeCmpEdge()
		{
			return theEdges_;
		}

		Entity2d_Box CalcBoundingBox(const Standard_Real theTol) const;

		void SetEdges(const std::shared_ptr<Pln_CmpEdge>&& theEdges);

		void CheckWire(const std::vector<std::shared_ptr<Pln_Edge>>& theEdges);

		void CreateWire(const std::shared_ptr<Pln_CmpEdge>& theEdge);

		void CreateWire(const std::shared_ptr<Pln_CmpEdge>&& theEdge);

		void CheckWireConsistency(const char* theName) const;

		void ForcedTransform(const gp_Trsf2d& t);

	public:

		Pln_Wire()
		{}

		Pln_Wire
		(
			const std::shared_ptr<Pln_CmpEdge>& theEdge
		);

		Pln_Wire
		(
			const std::shared_ptr<Pln_CmpEdge>&& theEdge
		);

		Pln_Wire
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<Pln_CmpEdge>& theEdge
		);

		Pln_Wire
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<Pln_CmpEdge>&& theEdge
		);

		Pln_Wire
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<Pln_CmpEdge>& theEdge
		);

		Pln_Wire
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<Pln_CmpEdge>&& theEdge
		);

		Standard_Integer NbEdges() const;

		Standard_Integer NbEntities
		(
			const Pln_EntityType t
		) const override;

		Standard_Boolean IsOrphan() const override;

		std::tuple<Standard_Real, Standard_Real> 
			BoundTolerance() const;

		Entity2d_Box BoundingBox
		(
			const Standard_Real Tol
		) const override;

		std::shared_ptr<Entity2d_Polygon>
			Polygon() const;

		const std::vector<std::shared_ptr<Pln_Edge>>& 
			Edges() const;

		const std::shared_ptr<Pln_CmpEdge>& 
			CmpEdge() const;

		std::vector<std::shared_ptr<Pln_Vertex>>
			RetrieveVertices() const;

		std::vector<std::shared_ptr<Pln_Curve>>
			RetrieveCurves() const;

		std::shared_ptr<Pln_Entity>
			Copy() const override;

		Pln_EntityType Type() const override;

		void Transform(const gp_Trsf2d& t) override;

		void RetrieveEntitiesTo
		(
			std::vector<std::shared_ptr<Pln_Entity>>& theEntities,
			const Pln_EntityType t
		) const override;

		void ApplyOrientation
		(
			const Pln_Orientation theOrient
		);

		void Reverse();

		void RetrieveVerticesTo
		(
			std::vector<std::shared_ptr<Pln_Vertex>>& theVertices
		) const;

		void RetrieveVerticesTo
		(
			std::vector<std::shared_ptr<Pln_Entity>>& theVertices
		) const;

		void RetrieveEdgesTo
		(
			std::vector<std::shared_ptr<Pln_Entity>>& theEdges
		) const;

		void RetrieveCurvesTo
		(
			std::vector<std::shared_ptr<Pln_Curve>>& theCurves
		) const;

		void Approx
		(
			const std::shared_ptr<Geo_ApprxCurve_Info>& theInfo
		) const;

		void ExportToPlt(OFstream& File) const;

		//- Static functions and operators

		/*static std::vector<std::shared_ptr<Pln_Wire>>
			RetrieveWires
			(
				const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
			);*/

		//static Pln_Orientation RetrieveOrientation(const Pln_Wire& theWire);
	};
}

#endif // !_Pln_Wire_Header
