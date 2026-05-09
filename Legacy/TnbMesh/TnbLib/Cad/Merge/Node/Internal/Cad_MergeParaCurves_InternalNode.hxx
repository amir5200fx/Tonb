#pragma once
#ifndef _Cad_MergeParaCurves_InternalNode_Header
#define _Cad_MergeParaCurves_InternalNode_Header

#include <Cad_MergeParaCurves_Node.hxx>

namespace tnbLib
{

	namespace cadLib
	{

		namespace mergeParaCurves
		{

			class InternalNode
				: public Node
			{

				/*Private Data*/

			public:

				// default constructor [6/4/2022 Amir]

				InternalNode()
				{}

				// constructors [6/4/2022 Amir]

				InternalNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
					: Node(theIndex, theCoord)
				{}


				// override functions and operators [6/4/2022 Amir]

				Standard_Boolean IsInternal() const override
				{
					return Standard_True;
				}

				// public functions and operators [6/4/2022 Amir]
			};
		}
	}
}

#endif // !_Cad_MergeParaCurves_InternalNode_Header
