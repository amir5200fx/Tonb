#pragma once
#ifndef _Geo_MetricPrcsr_Base_Header
#define _Geo_MetricPrcsr_Base_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <Mesh_Module.hxx>
#include <Geo_MetricPrcsr_Traits.hxx>

namespace tnbLib
{

	template<class MetricFun>
	class Geo_MetricPrcsr_Base
		: public Global_Indexed
		, public Global_Named
	{

	public:

		typedef typename geo_metric_processor_info_type<MetricFun>::type info;

	private:

		/*Private Data*/

		Standard_Real theDimSize_;

		std::shared_ptr<info> theInfo_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	protected:


		//- default constructor


		Geo_MetricPrcsr_Base()
		{}


		//- constructors

		Geo_MetricPrcsr_Base
		(
			const std::shared_ptr<info>& theInfo
		)
			: theInfo_(theInfo)
			, theDimSize_(RealLast())
		{}

		Geo_MetricPrcsr_Base
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<info>& theInfo
		)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
			, theInfo_(theInfo)
			, theDimSize_(RealLast())
		{}

		// Protected functions and operators [10/17/2022 Amir]

		void OverrideBaseInfo(const std::shared_ptr<info>& theInfo)
		{
			theInfo_ = theInfo;
		}

	public:


		//- public functions and operators

		const std::shared_ptr<info>& Info() const
		{
			return theInfo_;
		}

		auto DimSize() const
		{
			return theDimSize_;
		}

		void SetDimSize(const Standard_Real theSize)
		{
			theDimSize_ = theSize;
		}

		void OverrideInfo
		(
			const std::shared_ptr<info>& theInfo
		)
		{
			theInfo_ = theInfo;
		}

	};
}

#include <Geo_MetricPrcsrInfo.hxx>
#include <Geo_MetricPrcsrAnIsoInfo.hxx>

namespace tnbLib
{
	BOOST_SERIALIZATION_ASSUME_ABSTRACT(Geo_MetricPrcsrInfo);
	BOOST_SERIALIZATION_ASSUME_ABSTRACT(Geo2d_MetricPrcsrAnIsoInfo);
	BOOST_SERIALIZATION_ASSUME_ABSTRACT(Geo3d_MetricPrcsrAnIsoInfo);
}

#endif // !_Geo_MetricPrcsr_Base_Header
