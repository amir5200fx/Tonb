#pragma once
#ifndef _Cad_MergeParaCurves_IntsctNode_Header
#define _Cad_MergeParaCurves_IntsctNode_Header

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	namespace cadLib
	{

		namespace mergeParaCurves
		{

			// Forward Declarations [6/4/2022 Amir]
			class Pnt2d;

			template<class NodeType>
			class IntsctNode
				: public NodeType
			{

				/*Private Data*/

			public:

				// default constructor [6/4/2022 Amir]

				IntsctNode()
				{}

				// constructors [6/4/2022 Amir]

				IntsctNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
					: NodeType(theIndex, theCoord)
				{}

				IntsctNode(const Standard_Integer theIndex, Pnt2d&& theCoord)
					: NodeType(theIndex, std::move(theCoord))
				{}

				// public functions and operators [6/4/2022 Amir]
			};
		}
	}
}

#endif // !_Cad_MergeParaCurves_IntsctNode_Header

