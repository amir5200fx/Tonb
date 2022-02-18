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

		TNB_SERIALIZATION(TnbCad2d_EXPORT);


		// private functions and operators [2/3/2022 Amir]

		auto& ChangeCmpEdge()
		{
			return theEdges_;
		}

		TnbCad2d_EXPORT Entity2d_Box CalcBoundingBox(const Standard_Real theTol) const;

		TnbCad2d_EXPORT void SetEdges(const std::shared_ptr<Pln_CmpEdge>&& theEdges);

		TnbCad2d_EXPORT void CheckWire(const std::vector<std::shared_ptr<Pln_Edge>>& theEdges);

		TnbCad2d_EXPORT void CreateWire(const std::shared_ptr<Pln_CmpEdge>& theEdge);

		TnbCad2d_EXPORT void CreateWire(const std::shared_ptr<Pln_CmpEdge>&& theEdge);

		TnbCad2d_EXPORT void CheckWireConsistency(const char* theName) const;

		TnbCad2d_EXPORT void ForcedTransform(const gp_Trsf2d& t);

	public:

		static TnbCad2d_EXPORT const std::string extension;

		// default constructor [2/3/2022 Amir]

		Pln_Wire()
		{}


		// constructors [2/3/2022 Amir]

		TnbCad2d_EXPORT Pln_Wire
		(
			const std::shared_ptr<Pln_CmpEdge>& theEdge
		);

		TnbCad2d_EXPORT Pln_Wire
		(
			const std::shared_ptr<Pln_CmpEdge>&& theEdge
		);

		TnbCad2d_EXPORT Pln_Wire
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<Pln_CmpEdge>& theEdge
		);

		TnbCad2d_EXPORT Pln_Wire
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<Pln_CmpEdge>&& theEdge
		);

		TnbCad2d_EXPORT Pln_Wire
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<Pln_CmpEdge>& theEdge
		);

		TnbCad2d_EXPORT Pln_Wire
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<Pln_CmpEdge>&& theEdge
		);


		// public functions and operators [2/3/2022 Amir]

		TnbCad2d_EXPORT Standard_Integer NbEdges() const;

		TnbCad2d_EXPORT Standard_Integer NbEntities
		(
			const Pln_EntityType t
		) const override;

		TnbCad2d_EXPORT Standard_Boolean IsOrphan() const override;

		TnbCad2d_EXPORT std::tuple<Standard_Real, Standard_Real>
			BoundTolerance() const;

		TnbCad2d_EXPORT Entity2d_Box BoundingBox
		(
			const Standard_Real Tol
		) const override;

		TnbCad2d_EXPORT std::shared_ptr<Entity2d_Polygon>
			Polygon() const;

		TnbCad2d_EXPORT const std::vector<std::shared_ptr<Pln_Edge>>&
			Edges() const;

		TnbCad2d_EXPORT const std::shared_ptr<Pln_CmpEdge>&
			CmpEdge() const;

		TnbCad2d_EXPORT std::vector<std::shared_ptr<Pln_Vertex>>
			RetrieveVertices() const;

		TnbCad2d_EXPORT std::vector<std::shared_ptr<Pln_Curve>>
			RetrieveCurves() const;

		TnbCad2d_EXPORT std::shared_ptr<Pln_Entity>
			Copy() const override;

		TnbCad2d_EXPORT Pln_EntityType Type() const override;

		TnbCad2d_EXPORT void Transform(const gp_Trsf2d& t) override;

		TnbCad2d_EXPORT void RetrieveEntitiesTo
		(
			std::vector<std::shared_ptr<Pln_Entity>>& theEntities,
			const Pln_EntityType t
		) const override;

		TnbCad2d_EXPORT void ApplyOrientation
		(
			const Pln_Orientation theOrient
		);

		TnbCad2d_EXPORT void Reverse();

		TnbCad2d_EXPORT void RetrieveVerticesTo
		(
			std::vector<std::shared_ptr<Pln_Vertex>>& theVertices
		) const;

		TnbCad2d_EXPORT void RetrieveVerticesTo
		(
			std::vector<std::shared_ptr<Pln_Entity>>& theVertices
		) const;

		TnbCad2d_EXPORT void RetrieveEdgesTo
		(
			std::vector<std::shared_ptr<Pln_Entity>>& theEdges
		) const;

		TnbCad2d_EXPORT void RetrieveCurvesTo
		(
			std::vector<std::shared_ptr<Pln_Curve>>& theCurves
		) const;

		TnbCad2d_EXPORT void Approx
		(
			const std::shared_ptr<Geo_ApprxCurve_Info>& theInfo
		) const;

		TnbCad2d_EXPORT void ExportToPlt(OFstream& File) const;

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
