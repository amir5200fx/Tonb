#pragma once
#ifndef _Aft_OptNode_Header
#define _Aft_OptNode_Header

#include <Aft_OptNode_Calculator.hxx>
#include <Aft_OptNodeAnIso_Traits.hxx>

namespace tnbLib
{

	template<class FrontType, class SizeFun, class MetricFun, class CorrAlg = void, class AltrAlg = void>
	class Aft_OptNode
		: public Aft_OptNode_Calculator<FrontType, SizeFun, MetricFun>
	{

	public:

		typedef Aft_OptNode_Calculator<FrontType, SizeFun, MetricFun> base;
		typedef typename info_type_from_aniso_optNode_alg<Aft_OptNode<FrontType, SizeFun, MetricFun, CorrAlg, AltrAlg>>::infoType infoType;

	private:

		/*Private Data*/

		std::shared_ptr<infoType> theInfo_;

		std::shared_ptr<AltrAlg> theAlterAlg_;

		// Private functions and operators [3/10/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			Info << "It's not supposed to be called this function." << endl;
			NotImplemented;
		}

	public:

		// default constructor [3/1/2022 Amir]

		Aft_OptNode()
		{}

		// constructors [3/1/2022 Amir]

		Aft_OptNode
		(
			const std::shared_ptr<AltrAlg>& theAlterAlg,
			const std::shared_ptr<infoType>& theInfo
		)
			: theInfo_(theInfo)
			, theAlterAlg_(theAlterAlg)
		{}

		// override functions and operators [3/1/2022 Amir]

		void Perform() override;


		// public functions and operators [5/8/2022 Amir]

		const auto& AlterAlg() const
		{
			return theAlterAlg_;
		}

		const auto& GetInfo() const
		{
			return theInfo_;
		}

		void SetInfo(const std::shared_ptr<infoType>& theInfo)
		{
			theInfo_ = theInfo;
		}

		void SetAlterAlg(const std::shared_ptr<AltrAlg>& theAlg)
		{
			theAlterAlg_ = theAlg;
		}

	};


	
}

#include <Aft_OptNodeI.hxx>

#include <Aft_OptNode_Uniform.hxx>
#include <Aft_OptNode_Adaptive.hxx>
#include <Aft_OptNodeAnIso_Standard.hxx>
#include <Aft_OptNodeAnIso_Adaptive.hxx>

#endif // !_Aft_OptNode_Header
