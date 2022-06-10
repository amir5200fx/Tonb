#pragma once
#ifndef _Cad_CharLength_Info_Header
#define _Cad_CharLength_Info_Header

#include <Cad_Module.hxx>

#include <Standard_TypeDef.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [6/6/2022 Amir]
	class NumAlg_AdaptiveInteg_Info;

	class Cad_CharLength_Info
	{

		/*Private Data*/

		Standard_Integer theNbU_;
		Standard_Integer theNbV_;

		std::shared_ptr<NumAlg_AdaptiveInteg_Info> theInfo_;

	public:

		static TnbCad_EXPORT const Standard_Integer DEFAULT_NB_U;
		static TnbCad_EXPORT const Standard_Integer DEFAULT_NB_V;

		static TnbCad_EXPORT const std::shared_ptr<NumAlg_AdaptiveInteg_Info> DEFAULT_INFO;

		// default constructor [6/6/2022 Amir]

		Cad_CharLength_Info()
			: theNbU_(DEFAULT_NB_U)
			, theNbV_(DEFAULT_NB_V)
			, theInfo_(DEFAULT_INFO)
		{}

		// constructors [6/6/2022 Amir]


		// public functions and operators [6/6/2022 Amir]

		auto NbU() const
		{
			return theNbU_;
		}

		auto NbV() const
		{
			return theNbV_;
		}

		const auto& IntegInfo() const
		{
			return theInfo_;
		}

		void SetNbU(const Standard_Integer n)
		{
			theNbU_ = n;
		}

		void SetNbV(const Standard_Integer n)
		{
			theNbV_ = n;
		}

		void OverrideInfo(const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo)
		{
			theInfo_ = theInfo;
		}
	};
}

#endif // !_Cad_CharLength_Info_Header
