#pragma once
#ifndef _Cad_MergeParaCurves_BoundaryNode_Header
#define _Cad_MergeParaCurves_BoundaryNode_Header

#include <Cad_MergeParaCurves_Node.hxx>

namespace tnbLib
{

	namespace cadLib
	{

		namespace mergeParaCurves
		{

			class BoundaryNode
				: public Node
			{

				/*Private Data*/

			public:

				// default constructor [6/4/2022 Amir]

				BoundaryNode()
				{}


				// constructors [6/4/2022 Amir]

				BoundaryNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
					: Node(theIndex, theCoord)
				{}


				// override functions and operators [6/4/2022 Amir]

				Standard_Boolean IsBoundary() const override
				{
					return Standard_True;
				}

				// public functions and operators [6/4/2022 Amir]
			};
		}
	}
}

#endif // !_Cad_MergeParaCurves_BoundaryNode_Header
