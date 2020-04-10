#pragma once
#ifndef _HydStatic_CmptLib_Header
#define _HydStatic_CmptLib_Header

#include <Standard_TypeDef.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Marine_Body;
	class Marine_CmpSection;
	class Marine_GraphCurve;
	class HydStatic_BnjCurve;
	class HydStatic_Bonjean;
	class HydStatic_CrossCurves;
	class HydStatic_CrsCurve;
	class HydStatic_LeverArmPair;

	struct HydStatic_Bonjean_Entity;
	struct HydStatic_CrossCurves_Entity;

	namespace marineLib { struct xSectionParam; }

	class HydStatic_CmptLib
	{

	public:

		static Standard_Real 
			Draft
			(
				const Standard_Real x, 
				const Standard_Real theTa, 
				const Standard_Real xTa, 
				const Standard_Real theTf, 
				const Standard_Real xTf
			);

		static Standard_Real
			Draft
			(
				const Marine_CmpSection& theSect,
				const Standard_Real theTa, 
				const Standard_Real xTa, 
				const Standard_Real theTf, 
				const Standard_Real xTf
			);

		static std::vector<Standard_Real>
			RetrieveDrafts
			(
				const Marine_Body& theBody,
				const Standard_Real theTa, 
				const Standard_Real xTa, 
				const Standard_Real theTf, 
				const Standard_Real xTf
			);

		static std::vector<Standard_Real>
			RetrieveXs
			(
				const Marine_Body& theBody
			);

		static std::vector<std::shared_ptr<HydStatic_Bonjean_Entity>>
			RetrieveBnjCurves(const HydStatic_Bonjean& theBonjean);

		static std::vector<marineLib::xSectionParam>
			RetrieveAreas(const std::vector<std::shared_ptr<HydStatic_Bonjean_Entity>>& theCurves, const std::vector<Standard_Real>& theT);

		static std::vector<marineLib::xSectionParam>
			RetrieveAreas(const HydStatic_Bonjean& theBonjean, const Standard_Real theTa, const Standard_Real xTa, const Standard_Real theTf, const Standard_Real xTf);

		static std::vector<HydStatic_LeverArmPair>
			LeverArms(const std::vector<std::shared_ptr<HydStatic_CrossCurves_Entity>>& theCurves, const Standard_Real theVol);

		static std::vector<marineLib::xSectionParam>
			GZ(const std::vector<HydStatic_LeverArmPair>& thePairs, const Standard_Real theKG);
	};
}

#endif // !_HydStatic_CmptLib_Header
