#pragma once
#ifndef _Aft2d_SolutionDataAnIso_Header
#define _Aft2d_SolutionDataAnIso_Header

#include <Aft2d_SolutionDataBase.hxx>
#include <Aft2d_MetricPrcsrAnIsoFwd.hxx>
#include <Aft2d_RegionPlaneAnIsoFwd.hxx>

namespace tnbLib
{

	class Aft2d_SolutionDataAnIso
		: public Aft2d_SolutionDataBase
	{

		/*Private Data*/

		std::shared_ptr<Aft2d_MetricPrcsrAnIso> theMetric_;

		// Results [12/1/2021 Amir]

		std::shared_ptr<Aft2d_RegionPlaneAnIso> theRegion_;

		// private functions and operators [12/1/2021 Amir]

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	public:


		// default constructor [12/1/2021 Amir]

		Aft2d_SolutionDataAnIso()
		{}


		//- constructors


		// public functions and operators [12/1/2021 Amir]

		Standard_Boolean IsAnIso() const override
		{
			return Standard_True;
		}

		const auto& Metric() const
		{
			return theMetric_;
		}

		void SetRegion(const std::shared_ptr<Aft2d_RegionPlaneAnIso>& theRegion)
		{
			theRegion_ = theRegion;
		}

		void SetRegion(std::shared_ptr<Aft2d_RegionPlaneAnIso>&& theRegion)
		{
			theRegion_ = std::move(theRegion);
		}

		void LoadMetric(const std::shared_ptr<Aft2d_MetricPrcsrAnIso>& theMetric)
		{
			theMetric_ = theMetric;
		}

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Aft2d_SolutionDataAnIso);

#endif // !_Aft2d_SolutionDataAnIso_Header
