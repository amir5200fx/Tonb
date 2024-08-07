#pragma once
#ifndef _Aft_OptNodeAnIso_Adaptive_Header
#define _Aft_OptNodeAnIso_Adaptive_Header

#include <Aft_OptNode.hxx>
#include <Aft_OptNodeAnIso_Traits.hxx>

namespace tnbLib
{

	template<class FrontType, class SizeFun, class MetricFun, class CorrAlg>
	class Aft_OptNode<FrontType, SizeFun, MetricFun, CorrAlg>
		: public Aft_OptNode_Calculator<FrontType, SizeFun, MetricFun>
	{

	public:

		typedef Aft_OptNode_Calculator<FrontType, SizeFun, MetricFun> base;
		typedef typename info_type_from_aniso_optNode_alg<Aft_OptNode<FrontType, SizeFun, MetricFun, CorrAlg>>::infoType infoType;

	private:

		/*Private Data*/

		std::shared_ptr<infoType> theInfo_;


		// Private functions and operators [3/10/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			Info << "this function is not supposed to be called." << endl;
			NotImplemented;
		}

	protected:

		// default constructor [3/5/2022 Amir]

		Aft_OptNode()
		{}

	public:


		// constructors [3/5/2022 Amir]

		explicit Aft_OptNode
		(
			const std::shared_ptr<infoType>& theInfo
		)
			: theInfo_(theInfo)
		{}

		// override functions and operators [3/5/2022 Amir]

		void Perform() override;

		// public functions [3/5/2022 Amir]

		const auto& GetInfo() const
		{
			return theInfo_;
		}

	};
}

#endif // !_Aft_OptNodeAnIso_Adaptive_Header
