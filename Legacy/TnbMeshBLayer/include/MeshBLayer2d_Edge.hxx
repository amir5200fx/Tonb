#pragma once
#ifndef _MeshBLayer2d_Edge_Header
#define _MeshBLayer2d_Edge_Header

#include <MeshBLayer2d_Entity.hxx>

namespace tnbLib
{

	// Forward Declarations [1/31/2023 Payvand]

	class MeshBLayer2d_Node;

	class MeshBLayer2d_Edge
		: public MeshBLayer2d_Entity
	{

		/*Private Data*/

		std::shared_ptr<MeshBLayer2d_Node> theNode0_;
		std::shared_ptr<MeshBLayer2d_Node> theNode1_;

	protected:

		// default constructor [1/31/2023 Payvand]

		MeshBLayer2d_Edge()
		{}


		// constructors [1/31/2023 Payvand]

		explicit MeshBLayer2d_Edge(const Standard_Integer theIndex)
			: MeshBLayer2d_Entity(theIndex)
		{}

		MeshBLayer2d_Edge
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<MeshBLayer2d_Node>& theNode0, 
			const std::shared_ptr<MeshBLayer2d_Node>& theNode1
		)
			: MeshBLayer2d_Entity(theIndex)
			, theNode0_(theNode0)
			, theNode1_(theNode1)
		{}


	public:

		// Public functions and operators [1/31/2023 Payvand]

		virtual Standard_Boolean IsBoundary() const;
		virtual Standard_Boolean IsInner() const;

		const auto& Node0() const
		{
			return theNode0_;
		}

		const auto& Node1() const
		{
			return theNode1_;
		}

		void SetNode0(const std::shared_ptr<MeshBLayer2d_Node>&);
		void SetNode1(const std::shared_ptr<MeshBLayer2d_Node>&);
		
	};
}

#endif // !_MeshBLayer2d_Edge_Header
