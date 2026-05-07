#pragma once
#ifndef _Cad_MergeParaCurves_Ring_Header
#define _Cad_MergeParaCurves_Ring_Header

#include <Cad_MergeParaCurves_Link.hxx>

namespace tnbLib
{

	namespace cadLib
	{

		namespace mergeParaCurves
		{

			class Ring
				: public Link
			{

				/*Private Data*/

				std::shared_ptr<Node> theVtx_;

			public:

				// default constructor [6/3/2022 Amir]

				Ring()
				{}


				// constructors [6/3/2022 Amir]

				Ring(const Standard_Integer theIndex, const std::shared_ptr<Node>& theNode)
					: theVtx_(theNode)
				{}

				Ring(const Standard_Integer theIndex, std::shared_ptr<Node>&& theNode)
					: theVtx_(std::move(theNode))
				{}


				// override functions and operators [6/3/2022 Amir]

				Standard_Boolean IsRing() const override
				{
					return Standard_True;
				}

				// public functions and operators [6/3/2022 Amir]

				const auto& Vtx() const
				{
					return theVtx_;
				}

				void SetVtx(const std::shared_ptr<Node>& theNode)
				{
					theVtx_ = theNode;
				}

				void SetVtx(std::shared_ptr<Node>&& theNode)
				{
					theVtx_ = std::move(theNode);
				}
			};
		}
	}
}

#endif // !_Cad_MergeParaCurves_Ring_Header
