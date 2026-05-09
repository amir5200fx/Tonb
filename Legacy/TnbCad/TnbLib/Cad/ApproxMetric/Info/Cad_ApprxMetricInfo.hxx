#pragma once
#ifndef _Cad_ApprxMetricInfo_Header
#define _Cad_ApprxMetricInfo_Header

#include <Cad_Module.hxx>
#include <Merge_PntInfo.hxx>
#include <Global_Serialization.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [12/30/2021 Amir]
	class Geo2d_SamplePoints;
	class Cad_ApprxMetricCriterion;

	class Cad_ApprxMetricInfo
	{

		/*Private Data*/

		Standard_Integer theMinLevel_;
		Standard_Integer theMaxLevel_;
		Standard_Integer theUnbalancing_;

		Merge_PntInfo theMergeInfo_;

		std::shared_ptr<Geo2d_SamplePoints> theSamples_;
		std::shared_ptr<Cad_ApprxMetricCriterion> theCriterion_;

		// private functions and operators [12/30/2021 Amir]

		TNB_SERIALIZATION(TnbCad_EXPORT);

	public:

		static TnbCad_EXPORT const std::string extension;

		static TnbCad_EXPORT const Standard_Integer DEFAULT_MIN_LEVEL;
		static TnbCad_EXPORT const Standard_Integer DEFAULT_MAX_LEVEL;
		static TnbCad_EXPORT const Standard_Integer DEFAULT_UNBALANCING;

		static TnbCad_EXPORT const std::shared_ptr<Geo2d_SamplePoints> DEFAULT_SAMPLES;
		static TnbCad_EXPORT const std::shared_ptr<Cad_ApprxMetricCriterion> DEFAULT_CRITERION;

		// default constructor [12/30/2021 Amir]

		TnbCad_EXPORT Cad_ApprxMetricInfo();


		// constructors [12/30/2021 Amir]


		// public functions and operators [12/30/2021 Amir]

		auto MinLevel() const
		{
			return theMinLevel_;
		}

		auto MaxLevel() const
		{
			return theMaxLevel_;
		}

		auto Unbalancing() const
		{
			return theUnbalancing_;
		}

		const auto& MergeInfo() const
		{
			return theMergeInfo_;
		}

		auto& MergeInfoRef()
		{
			return theMergeInfo_;
		}

		const auto& Samples() const
		{
			return theSamples_;
		}

		const auto& Criterion() const
		{
			return theCriterion_;
		}

		void SetMinLevel(const Standard_Integer lev)
		{
			theMinLevel_ = lev;
		}

		void SetMaxLevel(const Standard_Integer lev)
		{
			theMaxLevel_ = lev;
		}

		void SetUnbalancing(const Standard_Integer lev)
		{
			theUnbalancing_ = lev;
		}

		void OverrideSamples(const std::shared_ptr<Geo2d_SamplePoints>& theSamples)
		{
			theSamples_ = theSamples;
		}

		void OverrideSamples(std::shared_ptr<Geo2d_SamplePoints>&& theSamples)
		{
			theSamples_ = std::move(theSamples);
		}

		void OverrideCriterion(const std::shared_ptr<Cad_ApprxMetricCriterion>& theCriterion)
		{
			theCriterion_ = theCriterion;
		}

		void OverrideCriterion(std::shared_ptr<Cad_ApprxMetricCriterion>&& theCriterion)
		{
			theCriterion_ = std::move(theCriterion);
		}
	};
}

#endif // !_Cad_ApprxMetricInfo_Header
