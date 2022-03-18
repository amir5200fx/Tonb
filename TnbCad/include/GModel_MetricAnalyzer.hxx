#pragma once
#ifndef _GModel_MetricAnalyzer_Header
#define _GModel_MetricAnalyzer_Header

#include <Global_Done.hxx>
#include <Global_Serialization.hxx>
#include <Entity2d_MetricMeshValueFwd.hxx>
#include <Cad_Module.hxx>

#include <memory>
#include <map>

namespace tnbLib
{

	// Forward Declarations [12/29/2021 Amir]
	class Cad_GModel;
	class GModel_Surface;
	class Cad_ApprxMetricInfo;

	class GModel_MetricAnalyzer
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<Cad_GModel> theModel_;
		
		std::map<Standard_Integer, std::shared_ptr<Entity2d_MetricMeshValue>>
			theMetrics_;


		std::shared_ptr<Cad_ApprxMetricInfo> theGlobalInfo_;
		std::map<Standard_Integer, std::shared_ptr<Cad_ApprxMetricInfo>> theInfos_;

		// private functions and operators [12/30/2021 Amir]

		TNB_SERIALIZATION(TnbCad_EXPORT);

	public:

		static TnbCad_EXPORT unsigned short verbose;

		static const TnbCad_EXPORT std::string extension;

		static TnbCad_EXPORT const std::shared_ptr<Cad_ApprxMetricInfo> DEFAULT_INFO;

		// default constructor [12/29/2021 Amir]

		GModel_MetricAnalyzer()
			: theGlobalInfo_(DEFAULT_INFO)
		{}


		// constructors [12/29/2021 Amir]

		GModel_MetricAnalyzer(const std::shared_ptr<Cad_GModel>& theModel)
			: theModel_(theModel)
			, theGlobalInfo_(DEFAULT_INFO)
		{}

		GModel_MetricAnalyzer(std::shared_ptr<Cad_GModel>&& theModel)
			: theModel_(std::move(theModel))
			, theGlobalInfo_(DEFAULT_INFO)
		{}

		// public functions and operators [12/29/2021 Amir]

		const auto& Model() const
		{
			return theModel_;
		}

		const auto& Metrics() const
		{
			return theMetrics_;
		}

		const auto& GlobalInfo() const
		{
			return theGlobalInfo_;
		}

		const auto& Infos() const
		{
			return theInfos_;
		}

		auto& InfosRef()
		{
			return theInfos_;
		}

		TnbCad_EXPORT void Perform();

		void SetModel(const std::shared_ptr<Cad_GModel>& theModel)
		{
			theModel_ = theModel;
		}

		void SetModel(std::shared_ptr<Cad_GModel>&& theModel)
		{
			theModel_ = std::move(theModel);
		}

		void OverrideGlobalInfo(const std::shared_ptr<Cad_ApprxMetricInfo>& theInfo)
		{
			theGlobalInfo_ = theInfo;
		}

		void OverrideGlobalInfo(std::shared_ptr<Cad_ApprxMetricInfo>&& theInfo)
		{
			theGlobalInfo_ = std::move(theInfo);
		}
	};
}

#endif // !_GModel_MetricAnalyzer_Header
