#pragma once
#ifndef _Cad_CurveLength_Header
#define _Cad_CurveLength_Header

#include <Standard_Handle.hxx>
#include <Cad_Module.hxx>
#include <Global_Done.hxx>

// Forward Declarations [1/16/2022 Amir]
class Geom_Curve;

#include <memory>

namespace tnbLib
{

	// Forward Declarations [1/16/2022 Amir]
	class NumAlg_AdaptiveInteg_Info;

	class Cad_CurveLength
		: public Global_Done
	{

		/*Private Data*/

		// inputs [1/16/2022 Amir]

		Handle(Geom_Curve) theCurve_;

		std::shared_ptr<NumAlg_AdaptiveInteg_Info> theInfo_;

		// result [1/16/2022 Amir]
		Standard_Real theLength_;

	public:


		static TnbCad_EXPORT const std::shared_ptr<NumAlg_AdaptiveInteg_Info> DEFAULT_INFO;

		// default constructor [1/16/2022 Amir]

		Cad_CurveLength()
			: theInfo_(DEFAULT_INFO)
			, theLength_(0)
		{}

		// constructors [1/16/2022 Amir]

		explicit Cad_CurveLength(const Handle(Geom_Curve)& theCurve)
			: theCurve_(theCurve)
			, theInfo_(DEFAULT_INFO)
			, theLength_(0)
		{}

		Cad_CurveLength
		(
			const Handle(Geom_Curve)& theCurve, 
			const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
		)
			: theCurve_(theCurve)
			, theInfo_(theInfo)
			, theLength_(0)
		{}


		// public functions and operators [1/16/2022 Amir]

		const auto& Geometry() const
		{
			return theCurve_;
		}

		const auto& IntegInfo() const
		{
			return theInfo_;
		}

		Standard_Real Result() const;

		TnbCad_EXPORT void Perform();
		TnbCad_EXPORT void Perform(const Standard_Real theLower, const Standard_Real theUpper);

		void SetGeometry(const Handle(Geom_Curve)& theCurve)
		{
			theCurve_ = theCurve;
		}

		void OverrideIntegInfo(const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo)
		{
			theInfo_ = theInfo;
		}

		void OverrideIntegInfo(std::shared_ptr<NumAlg_AdaptiveInteg_Info>&& theInfo)
		{
			theInfo_ = std::move(theInfo);
		}
	};
}

#endif // !_Cad_CurveLength_Header