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


		/*private functions and operators*/


		auto& ChangeVtx0()
		{
			return theVtx0_;
		}

		auto& ChangeVtx1()
		{
			return theVtx1_;
		}

		TNB_SERIALIZATION(TnbCad2d_EXPORT);

	public:

		typedef Pnt2d ptType;

		//- default constructor

		Pln_Edge()
		{}


		//- constructors

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


		//- public functions and operators

		TnbCad2d_EXPORT Standard_Boolean IsDangle() const;

		TnbCad2d_EXPORT Standard_Boolean IsOrphan() const override;

		TnbCad2d_EXPORT Standard_Integer NbEntities(const Pln_EntityType t) const override;

		TnbCad2d_EXPORT Standard_Integer GetIndex
		(
			const std::shared_ptr<Pln_Vertex>& theVertex
		) const;

		TnbCad2d_EXPORT Standard_Real Parameter
		(
			const Standard_Integer theIndex
		) const;

		const auto& Vtx0() const
		{
			return theVtx0_;
		}

		const auto& Vtx1() const
		{
			return theVtx1_;
		}

		TnbCad2d_EXPORT Entity2d_Box BoundingBox(const Standard_Real Tol) const override;

		TnbCad2d_EXPORT std::shared_ptr<Pln_Entity>
			Copy() const override;

		TnbCad2d_EXPORT Pln_EntityType Type() const override;

		//- WARNING! the edge must be orphan for transforming
		TnbCad2d_EXPORT void Transform(const gp_Trsf2d& t) override;

		TnbCad2d_EXPORT void RetrieveEntitiesTo
		(
			std::vector<std::shared_ptr<Pln_Entity>>& theEntities,
			const Pln_EntityType t
		) const override;

		TnbCad2d_EXPORT void Reverse
		(
			const Standard_Boolean ApplyToMesh = Standard_True
		);

		TnbCad2d_EXPORT void ExportToPlt(OFstream& File) const;

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

#endif // !_Pln_Edge_Header
