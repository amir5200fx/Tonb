#pragma once
#ifndef _PtdModel_PropHubParsNo1_Header
#define _PtdModel_PropHubParsNo1_Header

#include <PtdModel_PropHubPars.hxx>
#include <PtdModel_Module.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class PtdModel_Par;

	class PtdModel_PropHubParsNo1
		: public PtdModel_PropHubPars
	{

		/*Private Data*/

		std::shared_ptr<PtdModel_Par> theOffset_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbPtdModel_EXPORT);


	protected:

		//- default constructor

		PtdModel_PropHubParsNo1()
		{}

	public:


		//- constructors

		PtdModel_PropHubParsNo1
		(
			const std::shared_ptr<PtdModel_Par>& theOffset
		)
			: theOffset_(theOffset)
		{}

		PtdModel_PropHubParsNo1
		(
			std::shared_ptr<PtdModel_Par>&& theOffset
		)
			: theOffset_(theOffset)
		{}


		//- public functions and operators

		const auto& Offset() const
		{
			return theOffset_;
		}

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::PtdModel_PropHubParsNo1);

#endif // !_PtdModel_PropHubParsNo1_Header
