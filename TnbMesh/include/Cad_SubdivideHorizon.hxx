#pragma once
#ifndef _Cad_SubdivideHorizon_Header
#define _Cad_SubdivideHorizon_Header

#include <Global_Done.hxx>

#include <memory>
#include <map>
#include <list>
#include <vector>

#include <Standard_TypeDef.hxx>

#include "GModel_ParaCurve.hxx"

namespace tnbLib
{

	template<class PlnCurveType>
	class Cad_SubdivideHorizon
		: public Global_Done
	{

		/*Private Data*/


		// inputs [4/1/2022 Amir]

		std::shared_ptr<PlnCurveType> theHorizon_;

		// outputs [4/1/2022 Amir]
		std::list<Standard_Real> theParameters_;
		std::map<std::shared_ptr<PlnCurveType>, std::shared_ptr<std::list<Standard_Real>>>
			theCurvesToParameters_;

		// private functions and operators [4/1/2022 Amir]

		auto& ParametersRef()
		{
			return theParameters_;
		}

		auto& CurvesToParametersRef()
		{
			return theCurvesToParameters_;
		}

	public:

		// default constructor [4/1/2022 Amir]

		Cad_SubdivideHorizon()
		{}

		// constructors [4/1/2022 Amir]

		explicit Cad_SubdivideHorizon
		(
			const std::shared_ptr<PlnCurveType>& theCurve
		)
			: theHorizon_(theCurve)
		{}

		Cad_SubdivideHorizon
		(
			std::shared_ptr<PlnCurveType>&& theCurve
		)
			: theHorizon_(std::move(theCurve))
		{}

		// public functions and operators [4/1/2022 Amir]

		const auto& Horizon() const
		{
			return theHorizon_;
		}

		const auto& Parameters() const
		{
			return theParameters_;
		}

		const auto& CurvesToParameters() const
		{
			return theCurvesToParameters_;
		}

		void Perform(const std::vector<std::shared_ptr<PlnCurveType>>& theCurves);

		void LoadHorizon(const std::shared_ptr<PlnCurveType>& theCurve)
		{
			theHorizon_ = theCurve;
		}

		void LoadHorizon(std::shared_ptr<PlnCurveType>&& theCurve)
		{
			theHorizon_ = std::move(theCurve);
		}

		static std::map<std::shared_ptr<PlnCurveType>, std::shared_ptr<std::list<Standard_Real>>>
			Merge(const std::list<std::shared_ptr<Cad_SubdivideHorizon>>&);
	};
}

#include <Cad_SubdivideHorizonI.hxx>

#include <Cad_gSubdivideHorizon.hxx>

#endif // !_Cad_SubdivideHorizon_Header
