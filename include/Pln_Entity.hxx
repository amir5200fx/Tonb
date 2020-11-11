#pragma once
#ifndef _Pln_Entity_Header
#define _Pln_Entity_Header

#include <Cad_Entity.hxx>
#include <Cad2d_Module.hxx>
#include <Pln_EntityType.hxx>
#include <Entity2d_BoxFwd.hxx>

#include <vector>

class gp_Trsf2d;

namespace tnbLib
{

	// Forward Declarations
	class Pln_Vertex;
	class Pln_Edge;
	class Pln_Wire;

	class Pln_Entity
		: public Cad_Entity
	{

		/*Private Data*/


		/*private functions and operators*/
		DECLARE_SAVE_LOAD_HEADER(TnbCad2d_EXPORT);

	protected:

		Pln_Entity()
		{}

		Pln_Entity(const Standard_Integer theIndex)
			: Cad_Entity(theIndex)
		{}

		Pln_Entity
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: Cad_Entity(theIndex, theName)
		{}

	public:

		std::vector<std::shared_ptr<Pln_Entity>> 
			RetrieveEntities
			(
				const Pln_EntityType t
			) const;

		virtual Standard_Integer NbEntities(const Pln_EntityType t) const = 0;	

		virtual Standard_Boolean IsOrphan() const = 0;

		virtual Entity2d_Box BoundingBox(const Standard_Real Tol) const = 0;

		virtual std::shared_ptr<Pln_Entity> Copy() const = 0;

		virtual Pln_EntityType Type() const = 0;

		virtual void Transform(const gp_Trsf2d&) = 0;

		virtual void RetrieveEntitiesTo
		(
			std::vector<std::shared_ptr<Pln_Entity>>& theEntities, 
			const Pln_EntityType t
		) const = 0;

		
	};
}

#endif // !_Pln_Entity_Header
