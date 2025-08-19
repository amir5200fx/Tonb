#pragma once
#ifndef _PtdModel_WingInfo_Header
#define _PtdModel_WingInfo_Header

#include <Standard_TypeDef.hxx>
#include <Global_Serialization.hxx>
#include <PtdModel_Module.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class PtdModel_Forms;
	class PtdModel_Par;
	class PtdModel_WingGlobalPars;

	class PtdModel_WingInfo
	{

		/*Private Data*/

		std::shared_ptr<PtdModel_Forms> theForms_;
		std::shared_ptr<PtdModel_WingGlobalPars> theGlobals_;

		Standard_Integer theNbSections_;
		Standard_Integer theNbSpans_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbPtdModel_EXPORT);

	public:

		//- default constructor

		PtdModel_WingInfo()
		{}


		//- constructors


		//- public functions and operators

		const auto& Forms() const
		{
			return theForms_;
		}

		const auto& Globals() const
		{
			return theGlobals_;
		}

		auto NbSections() const
		{
			return theNbSections_;
		}

		auto NbSpans() const
		{
			return theNbSpans_;
		}


		inline void SetNbSections(const Standard_Integer);
		inline void SetNbSpans(const Standard_Integer);

		inline void SetForms(const std::shared_ptr<PtdModel_Forms>&);
		inline void SetForms(std::shared_ptr<PtdModel_Forms>&&);
		inline void SetLength(const std::shared_ptr<PtdModel_WingGlobalPars>&);
		inline void SetLength(std::shared_ptr<PtdModel_WingGlobalPars>&&);

	};
}

#include <PtdModel_WingInfoI.hxx>

#endif // !_PtdModel_WingInfo_Header
