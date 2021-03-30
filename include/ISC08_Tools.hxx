#pragma once
#ifndef _ISC08_Tools_Header
#define _ISC08_Tools_Header

#include <Standard_TypeDef.hxx>
#include <word.hxx>
#include <ISC08_Factor.hxx>
#include <ISC08_Parameter.hxx>
#include <HydStatic_CurveMakerType.hxx>
#include <HydStatic_rArmCurvesFwd.hxx>
#include <Marine_VesselParams.hxx>

#include <memory>
#include <tuple>

namespace tnbLib
{

	//- Forward Declarations
	struct ISC08_Table;
	class HydStatic_hArmCurve;
	
	namespace hydStcLib
	{
		class rArmCurve_Eff;
	}

	class ISC08_Tools
	{

	public:

		static TnbISC08_EXPORT std::shared_ptr<HydStatic_hArmCurve>
			HeelingArm
			(
				const isc08Lib::Lw& theLw2,
				const std::shared_ptr<hydStcLib::rArmCurve_Eff>& theEff
			);

		static TnbISC08_EXPORT Standard_Boolean
			CheckData
			(
				const marineLib::B& B, 
				const marineLib::TM& d
			);

		static TnbISC08_EXPORT Standard_Boolean
			CheckData
			(
				const marineLib::KG& KG, 
				const marineLib::TM& d
			);

		static TnbISC08_EXPORT Standard_Boolean
			CheckData
			(
				const isc08Lib::T& T
			);

		static TnbISC08_EXPORT Standard_Real
			Factor
			(
				const Standard_Real x, 
				const isc08Lib::BilgeBarCondition cond
			);

		static TnbISC08_EXPORT Standard_Real
			Table
			(
				const Standard_Real x, 
				const ISC08_Table& theTable
			);

		static TnbISC08_EXPORT void
			CheckTable
			(
				const ISC08_Table& theTable,
				const word& theName
			);

	};
}

#endif // !_ISC08_Tools_Header
