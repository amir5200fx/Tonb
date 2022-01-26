#pragma once
#ifndef _Cad2d_IdentRings_Link_Header
#define _Cad2d_IdentRings_Link_Header

#include <Cad2d_IdentRings_Entity.hxx>
#include <Cad2d_Module.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations [1/25/2022 Amir]
	class Pln_Edge;

	namespace cad2dLib
	{

		// Forward Declarations [1/24/2022 Amir]
		class IdentRings_Node;

		class IdentRings_Link
			: public IdentRings_Entity
		{

			/*Private Data*/

			std::vector<std::shared_ptr<Pln_Edge>> theEdges_;

		protected:

			// default constructor [1/24/2022 Amir]

			IdentRings_Link()
			{}

			// constructors [1/24/2022 Amir]

			IdentRings_Link
			(
				const Standard_Integer theIndex,
				const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
			)
				: IdentRings_Entity(theIndex)
				, theEdges_(theEdges)
			{}

			IdentRings_Link
			(
				const Standard_Integer theIndex,
				std::vector<std::shared_ptr<Pln_Edge>>&& theEdges
			)
				: IdentRings_Entity(theIndex)
				, theEdges_(std::move(theEdges))
			{}

		public:

			// public functions and operators [1/24/2022 Amir]

			const auto& Edges() const
			{
				return theEdges_;
			}

			virtual Standard_Boolean IsRing() const
			{
				return Standard_False;
			}

			virtual Standard_Boolean IsSegment() const
			{
				return Standard_False;
			}

			virtual void Attach() = 0;
			virtual void Detach() = 0;
		};
	}
}

#endif // !_Cad2d_IdentRings_Link_Header
