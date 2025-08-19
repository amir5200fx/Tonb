#pragma once
#ifndef _Cad_MergeParaCurves_SuperRing_Header
#define _Cad_MergeParaCurves_SuperRing_Header

#include <Cad_MergeParaCurves_SuperLink.hxx>

namespace tnbLib
{

	namespace cadLib
	{

		namespace mergeParaCurves
		{

			class SuperRing
				: public SuperLink
			{

				/*Private Data*/

				std::shared_ptr<SuperNode> theVtx_;

			public:

				// default constructor [6/4/2022 Amir]

				SuperRing()
				{}


				// constructors [6/4/2022 Amir]


				// public functions and operators [6/4/2022 Amir]

				const auto& Vtx() const
				{
					return theVtx_;
				}

				void SetVtx(const std::shared_ptr<SuperNode>& theNode)
				{
					theVtx_ = theNode;
				}

				void SetVtx(std::shared_ptr<SuperNode>&& theNode)
				{
					theVtx_ = std::move(theNode);
				}
			};
		}
	}
}

#endif // !_Cad_MergeParaCurves_SuperRing_Header
