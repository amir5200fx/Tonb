#pragma once
#ifndef _PtdModel_BladeInfo_Header
#define _PtdModel_BladeInfo_Header

#include <Standard_TypeDef.hxx>
#include <Global_Serialization.hxx>
#include <PtdModel_Module.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class PtdModel_BladeForm;
	class PtdModel_BladeGlobalPars;
	class PtdModel_Par;

	class PtdModel_BladeInfo
	{

		/*Private Data*/

		std::shared_ptr<PtdModel_BladeForm> theBladeForm_;
		std::shared_ptr<PtdModel_BladeGlobalPars> theGlobals_;

		Standard_Integer theNbSections_;
		Standard_Integer theNbSpans_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbPtdModel_EXPORT);


	public:

		//- default constructor

		PtdModel_BladeInfo()
		{}

		//- constructors


		//- public functions and operators

		const auto& BladeForm() const
		{
			return theBladeForm_;
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

		inline void SetBladeForm(const std::shared_ptr<PtdModel_BladeForm>&);
		inline void SetBladeForm(std::shared_ptr<PtdModel_BladeForm>&&);
		inline void SetGlobals(const std::shared_ptr<PtdModel_BladeGlobalPars>&);
		inline void SetGlobals(std::shared_ptr<PtdModel_BladeGlobalPars>&&);

	};
}

#include <PtdModel_BladeInfoI.hxx>

#endif // !_PtdModel_BladeInfo_Header
