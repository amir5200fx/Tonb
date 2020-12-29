#pragma once
#ifndef _Pln_Ring_Header
#define _Pln_Ring_Header

#include <Pln_Edge.hxx>

namespace tnbLib
{

	class Pln_Ring
		: public Pln_Edge
	{

		/*Private Data*/


		/*private functions and operators*/

		TNB_SERIALIZATION(TnbCad2d_EXPORT);

	public:

		Pln_Ring()
		{}

		Pln_Ring
		(
			const std::shared_ptr<Pln_Vertex>& theVtx,
			const Standard_Boolean Sense = Standard_True
		)
			: Pln_Edge(theVtx, theVtx, Sense)
		{}

		Pln_Ring
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<Pln_Vertex>& theVrtx,
			const std::shared_ptr<Pln_Curve>& theCurve,
			const Standard_Boolean Sense = Standard_True
		)
			: Pln_Edge(theIndex, theName, theVrtx, theVrtx, theCurve, Sense)
		{}

		Pln_Ring
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<Pln_Vertex>& theVrtx,
			const std::shared_ptr<Pln_Curve>&& theCurve,
			const Standard_Boolean Sense = Standard_True
		)
			: Pln_Edge(theIndex, theName, theVrtx, theVrtx, std::move(theCurve), Sense)
		{}

		Pln_Ring
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<Pln_Vertex>& theVrtx,
			const Standard_Boolean Sense = Standard_True
		)
			: Pln_Edge(theIndex, theVrtx, theVrtx, Sense)
		{}

		Pln_Ring
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<Pln_Vertex>& theVrtx,
			const Standard_Boolean Sense = Standard_True
		)
			: Pln_Edge(theIndex, theName, theVrtx, theVrtx, Sense)
		{}

		Pln_Ring
		(
			const std::shared_ptr<Pln_Vertex>& theVrtx,
			const std::shared_ptr<Pln_Curve>& theCurve,
			const Standard_Boolean Sense = Standard_True
		)
			: Pln_Edge(theVrtx, theVrtx, theCurve, Sense)
		{}

		Pln_Ring
		(
			const std::shared_ptr<Pln_Vertex>& theVrtx,
			const std::shared_ptr<Pln_Curve>&& theCurve,
			const Standard_Boolean Sense = Standard_True
		)
			: Pln_Edge(theVrtx, theVrtx, std::move(theCurve), Sense)
		{}


		//- override virtual functions

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
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Pln_Ring);

#endif // !_Pln_Ring_Header
