#pragma once
#ifndef _MeshBLayer2d_Element_Header
#define _MeshBLayer2d_Element_Header

#include <MeshBLayer2d_Entity.hxx>

namespace tnbLib
{

	// Forward Declarations [2/1/2023 Payvand]

	class MeshBLayer2d_Node;

	class MeshBLayer2d_Element
		: public MeshBLayer2d_Entity
	{

		/*Private Data*/

		std::shared_ptr<MeshBLayer2d_Node> theNode0_;
		std::shared_ptr<MeshBLayer2d_Node> theNode1_;
		std::shared_ptr<MeshBLayer2d_Node> theNode2_;

	public:

		// default constructor [2/1/2023 Payvand]

		MeshBLayer2d_Element()
		{}

		// Constructors [2/1/2023 Payvand]


		explicit MeshBLayer2d_Element(const Standard_Integer theIndex)
			: MeshBLayer2d_Entity(theIndex)
		{}

		MeshBLayer2d_Element
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<MeshBLayer2d_Node>& theNode0, 
			const std::shared_ptr<MeshBLayer2d_Node>& theNode1, 
			const std::shared_ptr<MeshBLayer2d_Node>& theNode2
		)
			: MeshBLayer2d_Entity(theIndex)
			, theNode0_(theNode0)
			, theNode1_(theNode1)
			, theNode2_(theNode2)
		{}


		// Public functions and operators [2/1/2023 Payvand]

		const auto& Node0() const
		{
			return theNode0_;
		}

		auto& Node0Ref()
		{
			return theNode0_;
		}

		const auto& Node1() const
		{
			return theNode1_;
		}

		auto& Node1Ref()
		{
			return theNode1_;
		}

		const auto& Node2() const
		{
			return theNode2_;
		}

		auto& Node2Ref()
		{
			return theNode2_;
		}

		void SetNode0(const std::shared_ptr<MeshBLayer2d_Node>& theNode)
		{
			theNode0_ = theNode;
		}

		void SetNode1(const std::shared_ptr<MeshBLayer2d_Node>& theNode)
		{
			theNode1_ = theNode;
		}

		void SetNode2(const std::shared_ptr<MeshBLayer2d_Node>& theNode)
		{
			theNode2_ = theNode;
		}

	};
}

#endif // !_MeshBLayer2d_Element_Header
