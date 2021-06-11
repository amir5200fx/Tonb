#pragma once
#ifndef _PtdModel_WingGlobalPars_Header
#define _PtdModel_WingGlobalPars_Header

#include <PtdModel_GlobalPars.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class PtdModel_Par;

	class PtdModel_WingGlobalPars
		: public PtdModel_GlobalPars
	{

		/*Private Data*/

		std::shared_ptr<PtdModel_Par> theSpan_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbPtdModel_EXPORT);

	public:

		//- default constructor

		PtdModel_WingGlobalPars()
		{}

		//- constructors

		TnbPtdModel_EXPORT PtdModel_WingGlobalPars(const std::shared_ptr<PtdModel_Par>&);
		TnbPtdModel_EXPORT PtdModel_WingGlobalPars(std::shared_ptr<PtdModel_Par>&&);

		//- public functions and operators

		const auto& SpanLength() const
		{
			return theSpan_;
		}

		inline void SetSpanLength(const std::shared_ptr<PtdModel_Par>&);
		inline void SetSpanLength(std::shared_ptr<PtdModel_Par>&&);

	};
}

#include <PtdModel_WingGlobalParsI.hxx>

#endif // !_PtdModel_WingGlobalPars_Header
