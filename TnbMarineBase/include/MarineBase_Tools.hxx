#pragma once
#ifndef _MarineBase_Tools_Header
#define _MarineBase_Tools_Header

#include <Standard_TypeDef.hxx>
#include <Standard_Handle.hxx>

#include <memory>
#include <vector>

class gp_Pln;
class Geom2d_Curve;
class gp_Ax22d;
class gp_Ax2d;
class gp_Ax1;

namespace tnbLib
{

	// Forward Declarations
	class Marine_CmpSection;
	class Marine_Section;
	class Marine_CrossSection;
	class Cad3d_TModel;
	class NumAlg_AdaptiveInteg_Info;
	class Pnt2d;
	class Pnt3d;

	namespace marineLib
	{

		struct xSectionParam
		{
			Standard_Real x;
			Standard_Real value;
		};
	}

	class MarineBase_Tools
	{

	public:

		static Handle(Geom2d_Curve)
			Curve
			(
				const std::vector<marineLib::xSectionParam>& theQ
			);

		static Standard_Real
			CalcArea
			(
				const std::vector<marineLib::xSectionParam>& theQ,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static Standard_Real 
			CalcArea
			(
				const Marine_Section& theSection,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static Standard_Real
			CalcArea
			(
				const Marine_CmpSection& theSection,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static Standard_Real
			CalcWetArea
			(
				const Marine_CmpSection& theSection,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static Pnt2d
			CalcCentre
			(
				const Marine_Section& theSection, 
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static Pnt2d
			CalcCentre
			(
				const Marine_CmpSection& theSection,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static Pnt2d
			CalcWetCentre
			(
				const Marine_CmpSection& theSection, 
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static Standard_Real
			CalcVolume
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static Pnt3d
			CalcCentreProductVolume
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static void
			Heel
			(
				const std::shared_ptr<Marine_CmpSection>& theSection,
				const gp_Ax2d& theAx
			);

		static void
			Heel
			(
				const std::shared_ptr<Marine_Section>& theSection,
				const gp_Ax2d& theAx
			);

		static void
			Heel
			(
				const std::shared_ptr<Marine_CrossSection>& theModel, 
				const gp_Ax1& theAx, 
				const Standard_Real theAngle
			);

		/*static Standard_Real
			CalcWetVolume
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);*/

		static std::shared_ptr<Marine_CmpSection>
			CreateSection
			(
				const Cad3d_TModel& theModel, 
				const gp_Pln& thePlane,
				const Standard_Boolean ParallelFalg = Standard_False
			);


	};
}

#endif // !_MarineBase_Tools_Header
