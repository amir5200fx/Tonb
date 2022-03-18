#pragma once
#ifndef _Aft_OptNode_Adaptive_Header
#define _Aft_OptNode_Adaptive_Header

#include <Aft_OptNode.hxx>
#include <Aft_OptNode_AdaptiveTraits.hxx>

namespace tnbLib
{

	template<class FrontType, class SizeFun, class CorrAlg>
	class Aft_OptNode<FrontType, SizeFun, void, CorrAlg, void>
		: public Aft_OptNode_Calculator<FrontType, SizeFun>
	{

	public:

		typedef typename corrector_info_type_from_alg<CorrAlg>::infoType infoType;

	private:

		/*Private Data*/

		std::shared_ptr<infoType> theInfo_;

	public:


		// default constructor [3/1/2022 Amir]

		Aft_OptNode()
		{}


		// constructors [3/1/2022 Amir]

		explicit Aft_OptNode
		(
			const std::shared_ptr<infoType>& theCorrInfo
		)
			: theInfo_(theCorrInfo)
		{}


		// override functions and operators [3/1/2022 Amir]

		void Perform() override;


		// public functions and operators [3/2/2022 Amir]

		const auto& CorrInfo() const
		{
			return theInfo_;
		}
	};
}

#endif // !_Aft_OptNode_Adaptive_Header
