#pragma once
#ifndef _Aft_OptNodeAnIso_Standard_Header
#define _Aft_OptNodeAnIso_Standard_Header

#include <Aft_OptNode.hxx>
#include <Aft_OptNodeAnIso_Traits.hxx>
#include <GeoMetricFun2d_UniformFwd.hxx>

namespace tnbLib
{

	template<class FrontType, class SizeFun, class MetricFun>
	class Aft_OptNode<FrontType, SizeFun, MetricFun>
		: public Aft_OptNode_Calculator<FrontType, SizeFun, MetricFun>
	{

	public:

		typedef Aft_OptNode_Calculator<FrontType, SizeFun, MetricFun> base;
		typedef typename info_type_from_aniso_optNode_alg<Aft_OptNode<FrontType, SizeFun, MetricFun>>::infoType infoType;

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

		// public functions and operators [3/5/2022 Amir]

		const auto& CalculatorInfo() const
		{
			return theInfo_;
		}

	};


	// NO info. is needed for a uniform metric [3/11/2023 Payvand]
	template<class FrontType, class SizeFun>
	class Aft_OptNode<FrontType, SizeFun, GeoMetricFun2d_Uniform>
		: public Aft_OptNode_Calculator<FrontType, SizeFun, GeoMetricFun2d_Uniform>
	{

		/*Private Data*/


		// Private functions and operators [3/10/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& boost::serialization::base_object
				<Aft_OptNode_Calculator<FrontType, SizeFun, GeoMetricFun2d_Uniform>>(*this);
		}

	public:

		typedef Aft_OptNode_Calculator<FrontType, SizeFun, GeoMetricFun2d_Uniform>
			base;

		// default constructor [3/8/2022 Amir]

		Aft_OptNode()
		{}


		// constructors [3/8/2022 Amir]


		// override functions and operators [3/8/2022 Amir]

		void Perform() override;

		// public functions and operators [3/8/2022 Amir]

	};
}

#endif // !_Aft_OptNodeAnIso_Standard_Header
