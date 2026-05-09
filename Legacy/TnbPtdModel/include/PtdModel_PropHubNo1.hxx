#pragma once
#ifndef _PtdModel_PropHubNo1_Header
#define _PtdModel_PropHubNo1_Header

#include <PtdModel_PropHub.hxx>

namespace tnbLib
{

	class PtdModel_PropHubNo1
		: public PtdModel_PropHub
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned /*file_version*/)
		{
			ar & boost::serialization::base_object<PtdModel_PropHub>(*this);
		}

		TnbPtdModel_EXPORT void Revolve() override;

	public:

		//- default constructor

		PtdModel_PropHubNo1()
		{}


		//- constructors

		TnbPtdModel_EXPORT PtdModel_PropHubNo1
		(
			const std::shared_ptr<PtdModel_PropBlade>& theBlade,
			const std::shared_ptr<PtdModel_PropHubPars>&,
			const std::shared_ptr<PtdModel_PropHubSection>& theSection
		);

		TnbPtdModel_EXPORT PtdModel_PropHubNo1
		(
			const Standard_Integer theIndex,
			const word& theName, 
			const std::shared_ptr<PtdModel_PropBlade>& theBlade, 
			const std::shared_ptr<PtdModel_PropHubPars>&,
			const std::shared_ptr<PtdModel_PropHubSection>& theSection
		);


		//- public functions and operators


	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::PtdModel_PropHubNo1);

#endif // !_PtdModel_PropHubNo1_Header
