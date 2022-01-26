#pragma once
#ifndef _Cad2d_IdentRings_Node_Header
#define _Cad2d_IdentRings_Node_Header

#include <Cad2d_IdentRings_Entity.hxx>
#include <Cad2d_IdentRings_NodeAdaptor.hxx>

#include <memory>
#include <map>

namespace tnbLib
{

	// Forward Declarations [1/24/2022 Amir]
	class Pln_Vertex;

	namespace cad2dLib
	{

		// Forward Declarations [1/24/2022 Amir]
		class IdentRings_Link;

		class IdentRings_Node
			: public IdentRings_Entity
			, public IdentRings_NodeAdaptor
		{

			/*Private Data*/

			std::shared_ptr<Pln_Vertex> theVertex_;

		public:

			// default constructor [1/24/2022 Amir]

			IdentRings_Node()
			{}

			// constructors [1/24/2022 Amir]

			IdentRings_Node
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<Pln_Vertex>& theVtx
			)
				: IdentRings_Entity(theIndex)
				, theVertex_(theVtx)
			{}

			IdentRings_Node
			(
				const Standard_Integer theIndex,
				std::shared_ptr<Pln_Vertex>&& theVtx
			)
				: IdentRings_Entity(theIndex)
				, theVertex_(std::move(theVtx))
			{}

			// public functions and operators [1/24/2022 Amir]

			const auto& Vtx() const
			{
				return theVertex_;
			}

			void SetVertex(const std::shared_ptr<Pln_Vertex>& theVtx)
			{
				theVertex_ = theVtx;
			}

			void SetVertex(std::shared_ptr<Pln_Vertex>&& theVtx)
			{
				theVertex_ = std::move(theVtx);
			}
		};
	}
}

#endif // !_Cad2d_IdentRings_Node_Header
