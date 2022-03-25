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
	class Cad2d_MergeCurves;

	class Pln_Edge
		: public Pln_Entity
		, public Pln_EdgeAdaptor
		, public Pln_EdgeGeom
	{

		/*Private Data*/


		/*private functions and operators*/


		TNB_SERIALIZATION(TnbCad2d_EXPORT);

	protected:

		typedef Pnt2d ptType;

		static TnbCad2d_EXPORT const std::string extension;

		//- default constructor


		//- constructors

		Pln_Edge
		(
			const Standard_Boolean Sense = Standard_True
		)
			: Pln_EdgeGeom(Sense)
		{}


		Pln_Edge
		(
			const std::shared_ptr<Pln_Curve>& theCurve,
			const Standard_Boolean Sense = Standard_True
		)
			: Pln_EdgeGeom(theCurve, Sense)
		{}

		Pln_Edge
		(
			const std::shared_ptr<Pln_Curve>&& theCurve,
			const Standard_Boolean Sense = Standard_True
		)
			: Pln_EdgeGeom(std::move(theCurve), Sense)
		{}

		Pln_Edge
		(
			const Standard_Integer theIndex,
			const Standard_Boolean Sense = Standard_True
		)
			: Pln_Entity(theIndex)
			, Pln_EdgeGeom(Sense)
		{}

		Pln_Edge
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Standard_Boolean Sense = Standard_True
		)
			: Pln_Entity(theIndex, theName)
			, Pln_EdgeGeom(Sense)
		{}

		Pln_Edge
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<Pln_Curve>& theCurve,
			const Standard_Boolean Sense = Standard_True
		)
			: Pln_Entity(theIndex, theName)
			, Pln_EdgeGeom(theCurve, Sense)
		{}

		Pln_Edge
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<Pln_Curve>&& theCurve,
			const Standard_Boolean Sense = Standard_True
		)
			: Pln_Entity(theIndex, theName)
			, Pln_EdgeGeom(std::move(theCurve), Sense)
		{}

	public:

		enum class edgePoint
		{
			first,
			last
		};

		//- public functions and operators

		virtual Standard_Boolean IsDangle() const = 0;
		//TnbCad2d_EXPORT Standard_Boolean IsOrphan() const override;

		TnbCad2d_EXPORT Standard_Integer NbEntities(const Pln_EntityType t) const override;

		virtual edgePoint GetPoint
		(
			const std::shared_ptr<Pln_Vertex>& theVertex
		) const = 0;

		TnbCad2d_EXPORT Standard_Real Parameter
		(
			const edgePoint theIndex
		) const;

		TnbCad2d_EXPORT Entity2d_Box BoundingBox(const Standard_Real Tol) const override;

		/*TnbCad2d_EXPORT std::shared_ptr<Pln_Entity>
			Copy() const override;*/

		TnbCad2d_EXPORT Pln_EntityType Type() const override;

		//- WARNING! the edge must be orphan for transforming
		//TnbCad2d_EXPORT void Transform(const gp_Trsf2d& t) override;

		/*TnbCad2d_EXPORT void RetrieveEntitiesTo
		(
			std::vector<std::shared_ptr<Pln_Entity>>& theEntities,
			const Pln_EntityType t
		) const override;*/

		virtual void Reverse
		(
			const Standard_Boolean ApplyToMesh
		) = 0;

		TnbCad2d_EXPORT void ExportToPlt(OFstream& File) const;

		//- virtual functions

		virtual std::shared_ptr<Pln_Vertex> Vertex(const edgePoint) const = 0;

		TnbCad2d_EXPORT std::shared_ptr<Pln_Vertex> FirstVtx() const;
		TnbCad2d_EXPORT std::shared_ptr<Pln_Vertex> LastVtx() const;

		virtual Standard_Boolean IsRing() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsSegment() const
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

		static inline Standard_Boolean
			IsLess
			(
				const std::shared_ptr<Pln_Edge>& theEdge0,
				const std::shared_ptr<Pln_Edge>& theEdge1
			);

		static TnbCad2d_EXPORT Standard_Boolean
			IsConnected
			(
				const std::shared_ptr<Pln_Edge>& theEdge0,
				const std::shared_ptr<Pln_Edge>& theEdge1,
				std::shared_ptr<Pln_Vertex>& theVtx
			);

	};
}

#include <Pln_EdgeI.hxx>

BOOST_CLASS_EXPORT_KEY(tnbLib::Pln_Edge);

#include <Pln_Segment.hxx>
#include <Pln_Ring.hxx>

#endif // !_Pln_Edge_Header
