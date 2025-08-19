#pragma once
#ifndef _Cad_MetricRepair_Info_Header
#define _Cad_MetricRepair_Info_Header

#include <Cad_Module.hxx>

#include <Standard_TypeDef.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [6/4/2022 Amir]
	class NumAlg_AdaptiveInteg_Info;

	class Cad_MetricRepair_Info
	{

		/*Private Data*/

		Standard_Real theMaxDet_;

		std::shared_ptr<NumAlg_AdaptiveInteg_Info> theIntegInfo_;

	public:


		static TnbCad_EXPORT const Standard_Real DEFAULT_MAX_DETERMINANT;
		static TnbCad_EXPORT const std::shared_ptr<NumAlg_AdaptiveInteg_Info> DEFAULT_INTEG_INFO;

		// default constructor [6/4/2022 Amir]

		Cad_MetricRepair_Info()
			: theMaxDet_(DEFAULT_MAX_DETERMINANT)
			, theIntegInfo_(DEFAULT_INTEG_INFO)
		{}

		// constructors [6/4/2022 Amir]


		// public functions and operators [6/4/2022 Amir]

		auto MaxDet() const
		{
			return theMaxDet_;
		}

		const auto& IntegInfo() const
		{
			return theIntegInfo_;
		}

		void SetMaxDet(const Standard_Real theDet)
		{
			theMaxDet_ = theDet;
		}

		void OverrideIntegInfo(const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo)
		{
			theIntegInfo_ = theInfo;
		}

		void OverrideIntegInfo(std::shared_ptr<NumAlg_AdaptiveInteg_Info>&& theInfo)
		{
			theIntegInfo_ = std::move(theInfo);
		}

	};
}

#endif // !_Cad_MetricRepair_Info_Header
