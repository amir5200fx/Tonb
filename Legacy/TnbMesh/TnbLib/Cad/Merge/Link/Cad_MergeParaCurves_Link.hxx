#pragma once
#ifndef _Cad_MergeParaCurves_Link_Header
#define _Cad_MergeParaCurves_Link_Header

#include <Cad_MergeParaCurves_Entity.hxx>

#include <vector>

namespace tnbLib
{

	namespace cadLib
	{

		namespace mergeParaCurves
		{

			// Forward Declarations [6/3/2022 Amir]
			class Node;

			class Link
				: public Entity
			{

				/*Private Data*/

			protected:

				// default constructor [6/3/2022 Amir]

				Link()
				{}


				// constructors [6/3/2022 Amir]

				explicit Link(const Standard_Integer theIndex)
					: Entity(theIndex)
				{}

			public:

				// public functions and operators [6/3/2022 Amir]

				// the second node is null if the link is ring [6/4/2022 Amir]
				virtual std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> RetrieveNodes() const = 0;

				virtual Standard_Boolean IsSegment() const
				{
					return Standard_False;
				}

				virtual Standard_Boolean IsRing() const
				{
					return Standard_False;
				}
			};
		}
	}
}

#endif // !_Cad_MergeParaCurves_Link_Header
