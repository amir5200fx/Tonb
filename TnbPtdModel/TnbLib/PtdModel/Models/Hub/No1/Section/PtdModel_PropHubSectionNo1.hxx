#pragma once
#ifndef _PtdModel_PropHubSectionNo1_Header
#define _PtdModel_PropHubSectionNo1_Header

#include <PtdModel_PropHubSection.hxx>

namespace tnbLib
{

	class PtdModel_PropHubSectionNo1
		: public PtdModel_PropHubSection
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<PtdModel_PropHubSection>(*this);
		}

	public:

		static TnbPtdModel_EXPORT Standard_Real DEFAULT_EPSILON;


		//- default constructor

		PtdModel_PropHubSectionNo1()
		{}

		//- constructors


		//- public functions and operators

		TnbPtdModel_EXPORT std::vector<std::shared_ptr<PtdModel_HubCurve>> 
			SectionCurves(const PtdModel_PropHub&) const override;
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::PtdModel_PropHubSectionNo1);

#endif // !_PtdModel_PropHubSectionNo1_Header
