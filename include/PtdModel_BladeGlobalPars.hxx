#pragma once
#ifndef _PtdModel_BladeGlobalPars_Header
#define _PtdModel_BladeGlobalPars_Header

#include <PtdModel_GlobalPars.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class PtdModel_Par;

	class PtdModel_BladeGlobalPars
		: public PtdModel_GlobalPars
	{

		/*Private Data*/

		std::shared_ptr<PtdModel_Par> theDiameter_;
		std::shared_ptr<PtdModel_Par> theHubRadius_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbPtdModel_EXPORT);

	public:

		//- default constructor

		PtdModel_BladeGlobalPars()
		{}

		//- constructors

		PtdModel_BladeGlobalPars
		(
			const std::shared_ptr<PtdModel_Par>& theDia, 
			const std::shared_ptr<PtdModel_Par>& theHubRadius
		)
			: theDiameter_(theDia)
			, theHubRadius_(theHubRadius)
		{}

		PtdModel_BladeGlobalPars
		(
			std::shared_ptr<PtdModel_Par>&& theDia,
			std::shared_ptr<PtdModel_Par>&& theHubRadius
		)
			: theDiameter_(std::move(theDia))
			, theHubRadius_(std::move(theHubRadius))
		{}


		//- public functions and operators

		const auto& Diameter() const
		{
			return theDiameter_;
		}

		const auto& HubRadius() const
		{
			return theHubRadius_;
		}


		inline void SetDiameter(const std::shared_ptr<PtdModel_Par>&);
		inline void SetDiameter(std::shared_ptr<PtdModel_Par>&&);
		inline void SetHubRadius(const std::shared_ptr<PtdModel_Par>&);
		inline void SetHubRadius(std::shared_ptr<PtdModel_Par>&&);
	};
}

#include <PtdModel_BladeGlobalParsI.hxx>

#endif // !_PtdModel_BladeGlobalPars_Header

