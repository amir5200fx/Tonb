#pragma once
#ifndef _HydStatic_CrsCurvesGraphOps_Header
#define _HydStatic_CrsCurvesGraphOps_Header

#include <Standard_TypeDef.hxx>
#include <HydStatic_CurveMakerType.hxx>
#include <HydStatic_Module.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class HydStatic_CrsCurveQ;
	class HydStatic_CrsCurve;

	class HydStatic_CrsCurvesGraphOps
	{

	public:

		template<class CrsCurveType>
		static Standard_Real GetMinDisplv(const std::vector<std::shared_ptr<CrsCurveType>>&);
		template<class CrsCurveType>
		static Standard_Real GetMaxDisplv(const std::vector<std::shared_ptr<CrsCurveType>>&);

		template<>
		static TnbHydStatic_EXPORT Standard_Real GetMinDisplv<HydStatic_CrsCurve>(const std::vector<std::shared_ptr<HydStatic_CrsCurve>>&);
		template<>
		static TnbHydStatic_EXPORT Standard_Real GetMaxDisplv<HydStatic_CrsCurve>(const std::vector<std::shared_ptr<HydStatic_CrsCurve>>&);
		template<>
		static TnbHydStatic_EXPORT Standard_Real GetMinDisplv<HydStatic_CrsCurveQ>(const std::vector<std::shared_ptr<HydStatic_CrsCurveQ>>&);
		template<>
		static TnbHydStatic_EXPORT Standard_Real GetMaxDisplv<HydStatic_CrsCurveQ>(const std::vector<std::shared_ptr<HydStatic_CrsCurveQ>>&);

		template<class CrsCurveType>
		static std::shared_ptr<CrsCurveType> ClipCurve(const std::shared_ptr<CrsCurveType>&, const Standard_Real x0, const Standard_Real x1, const hydStcLib::CurveMakerType t);

		template<>
		static TnbHydStatic_EXPORT std::shared_ptr<HydStatic_CrsCurve> 
			ClipCurve<HydStatic_CrsCurve>
			(
				const std::shared_ptr<HydStatic_CrsCurve>&, 
				const Standard_Real x0, 
				const Standard_Real x1, 
				const hydStcLib::CurveMakerType t
				);

		template<>
		static TnbHydStatic_EXPORT std::shared_ptr<HydStatic_CrsCurveQ> 
			ClipCurve<HydStatic_CrsCurveQ>
			(
				const std::shared_ptr<HydStatic_CrsCurveQ>&,
				const Standard_Real x0,
				const Standard_Real x1,
				const hydStcLib::CurveMakerType t
				);

	};
}

#endif // !_HydStatic_CrsCurvesGraphOps_Header
