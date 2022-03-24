#pragma once
#ifndef _Pln_Ring_Header
#define _Pln_Ring_Header

#include <Pln_Edge.hxx>

namespace tnbLib
{

	class Pln_Ring
		: public Pln_Edge
	{

		friend class Cad2d_MergeCurves;

		/*Private Data*/

		std::shared_ptr<Pln_Vertex> theVtx_;


		/*private functions and operators*/

		auto& VtxRef()
		{
			return theVtx_;
		}

		TNB_SERIALIZATION(TnbCad2d_EXPORT);

	public:


		// default constructor [3/23/2022 Amir]

		Pln_Ring()
		{}


		// constructors [3/23/2022 Amir]

		Pln_Ring
		(
			const std::shared_ptr<Pln_Vertex>& theVtx,
			const Standard_Boolean Sense = Standard_True
		)
			: Pln_Edge(Sense)
			, theVtx_(theVtx)
		{}

		Pln_Ring
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<Pln_Vertex>& theVrtx,
			const std::shared_ptr<Pln_Curve>& theCurve,
			const Standard_Boolean Sense = Standard_True
		)
			: Pln_Edge(theIndex, theName, theCurve, Sense)
			, theVtx_(theVrtx)
		{}

		Pln_Ring
		(
			const Standard_Integer theIndex,
			const word& theName,
			std::shared_ptr<Pln_Vertex>&& theVrtx,
			std::shared_ptr<Pln_Curve>&& theCurve,
			const Standard_Boolean Sense = Standard_True
		)
			: Pln_Edge(theIndex, theName, std::move(theCurve), Sense)
			, theVtx_(std::move(theVrtx))
		{}

		Pln_Ring
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<Pln_Vertex>& theVrtx,
			const Standard_Boolean Sense = Standard_True
		)
			: Pln_Edge(theIndex, theName, Sense)
			, theVtx_(theVrtx)
		{}

		Pln_Ring
		(
			const Standard_Integer theIndex,
			const word& theName,
			std::shared_ptr<Pln_Vertex>&& theVrtx,
			const Standard_Boolean Sense = Standard_True
		)
			: Pln_Edge(theIndex, theName, Sense)
			, theVtx_(std::move(theVrtx))
		{}

		Pln_Ring
		(
			const std::shared_ptr<Pln_Vertex>& theVrtx,
			const std::shared_ptr<Pln_Curve>& theCurve,
			const Standard_Boolean Sense = Standard_True
		)
			: Pln_Edge(theCurve, Sense)
			, theVtx_(theVrtx)
		{}

		Pln_Ring
		(
			std::shared_ptr<Pln_Vertex>&& theVrtx,
			std::shared_ptr<Pln_Curve>&& theCurve,
			const Standard_Boolean Sense = Standard_True
		)
			: Pln_Edge(std::move(theCurve), Sense)
			, theVtx_(std::move(theVrtx))
		{}


		//- override virtual functions

		Standard_Boolean IsOrphan() const override;
		TnbCad2d_EXPORT Standard_Integer NbEntities(const Pln_EntityType t) const override;

		Standard_Boolean IsRing() const override
		{
			return Standard_True;
		}

		TnbCad2d_EXPORT void RetrieveEntitiesTo
		(
			std::vector<std::shared_ptr<Pln_Entity>>& theEntities,
			const Pln_EntityType t
		) const override;


		// public functions and operators [3/23/2022 Amir]

		const auto& Vtx() const
		{
			return theVtx_;
		}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Pln_Ring);

#endif // !_Pln_Ring_Header
