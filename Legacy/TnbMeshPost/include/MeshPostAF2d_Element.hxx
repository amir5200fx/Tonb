#pragma once
#ifndef _MeshPostAF2d_Element_Header
#define _MeshPostAF2d_Element_Header

#include <MeshPostAF2d_ElementBase.hxx>

namespace tnbLib
{

	class MeshPostAF2d_Element
		: public MeshPostAF2d_ElementBase
	{

		/*Private Data*/

	public:

		// default constructor [8/31/2023 aamir]

		MeshPostAF2d_Element()
		{}

		// constructors [8/31/2023 aamir]

		MeshPostAF2d_Element(const Standard_Integer theIndex)
			: MeshPostAF2d_ElementBase(theIndex)
		{}

		MeshPostAF2d_Element
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<MeshPostAF2d_Node>& theNode0, 
			const std::shared_ptr<MeshPostAF2d_Node>& theNode1, 
			const std::shared_ptr<MeshPostAF2d_Node>& theNode2
		)
			: MeshPostAF2d_ElementBase(theIndex, theNode0, theNode1, theNode2)
		{}


		// Public functions and operators [8/31/2023 aamir]

	};
}

#endif // !_MeshPostAF2d_Element_Header
