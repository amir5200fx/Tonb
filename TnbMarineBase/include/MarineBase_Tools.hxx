#pragma once
#ifndef _MarineBase_Tools_Header
#define _MarineBase_Tools_Header

#include <Standard_TypeDef.hxx>
#include <Standard_Handle.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Entity3d_BoxFwd.hxx>
#include <dimensionedScalar.hxx>
#include <Marine_SectionsFwd.hxx>
#include <Marine_BodiesFwd.hxx>
#include <Marine_xSectionParam.hxx>
#include <Marine_Module.hxx>
#include <Marine_PlnCurvesFwd.hxx>
#include <Marine_EnvtParams.hxx>
#include <Marine_CoeffParam_Cw.hxx>

#include <memory>
#include <vector>

class gp_Pln;
class Geom2d_Curve;
class Geom_Curve;
class gp_Ax22d;
class gp_Ax2d;
class gp_Ax1;
class gp_Ax2;

namespace tnbLib
{

	// Forward Declarations
	class Marine_CmpSection;
	class Marine_Wave;
	class Marine_WaterDomain;
	class Marine_Domain;
	class Marine_Graph;
	class Cad3d_TModel;
	class NumAlg_AdaptiveInteg_Info;
	class Pnt2d;
	class Pnt3d;
	class Pln_Wire;
	class Geo_xDistb;
	class Cad2d_Plane;

	class MarineBase_Tools
	{

	public:

		static unsigned int MIN_NB_POINTS_INTERPOLATION;

		static TnbMarine_EXPORT Pnt3d 
			CalcOxyz
			(
				const Entity3d_Box& theDomain
			);

		//- the coefficient Cw depends on the form and configuration of the sail area.
		//- an average value for Cw is 1.2. 
		static TnbMarine_EXPORT marineLib::Pressure 
			CalcWindPressure
			(
				const marineLib::coeff::Cw& theAeroResisCoeff, 
				const marineLib::Density& theRho,
				const marineLib::Velocity& theVel
			);

		static TnbMarine_EXPORT std::vector<Standard_Real> 
			Tessellate
			(
				const std::vector<Standard_Real>& theXs,
				const unsigned int theCriterion
			);

		static TnbMarine_EXPORT std::vector<marineLib::xSectionParam> 
			SteffenTessellation
			(
				const std::vector<marineLib::xSectionParam>& theQ
			);

		static TnbMarine_EXPORT Entity2d_Box 
			CalcBoundingBox2D
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections
			);

		static TnbMarine_EXPORT Entity3d_Box 
			CalcBoundingBox
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections
			);


		/*template<class SectionType>
		static TnbMarine_EXPORT std::shared_ptr<Cad2d_Plane> 
			ConvertToPlane
			(
				const Marine_OuterSection<SectionType>& theOuter
			);

		template<>
		static TnbMarine_EXPORT std::shared_ptr<Cad2d_Plane> 
			ConvertToPlane
			(
				const Marine_OuterSection<Marine_WaterSection>& theWater
			);*/

		static TnbMarine_EXPORT Handle(Geom2d_Curve)
			Curve
			(
				const std::vector<marineLib::xSectionParam>& theQ,
				const Standard_Boolean tessellation = Standard_True
			);


		static TnbMarine_EXPORT Standard_Real 
			CalcBWL
			(
				const Marine_CmpSection& theSection
			);

		static TnbMarine_EXPORT Standard_Real
			CalcArea
			(
				const std::vector<marineLib::xSectionParam>& theQ,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT Standard_Real 
			CalcArea
			(
				const std::shared_ptr<Marine_Section>& theSection,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT Standard_Real
			CalcArea
			(
				const Marine_CmpSection& theSection,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT Standard_Real 
			CalcIx
			(
				const std::shared_ptr<Marine_Section>& theSection,
				const Standard_Real y0,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT Standard_Real 
			CalcIx
			(
				const Marine_CmpSection& theSection,
				const Standard_Real y0,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT Standard_Real 
			CalcIy
			(
				const std::shared_ptr<Marine_Section>& theSection, 
				const Standard_Real x0, 
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT Standard_Real
			CalcIy
			(
				const Marine_CmpSection& theSection,
				const Standard_Real x0,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT Standard_Real
			CalcMx
			(
				const std::shared_ptr<Marine_Section>& theSection,
				const Standard_Real x0,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT Standard_Real
			CalcMy
			(
				const std::shared_ptr<Marine_Section>& theSection,
				const Standard_Real x0,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT Standard_Real
			CalcMx
			(
				const Marine_CmpSection& theSection,
				const Standard_Real y0,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT Standard_Real
			CalcMy
			(
				const Marine_CmpSection& theSection,
				const Standard_Real x0,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT std::vector<marineLib::xSectionParam>
			CalcIx
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections,
				const Standard_Real y0,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT std::vector<marineLib::xSectionParam>
			CalcIy
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections,
				const Standard_Real x0,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT std::vector<marineLib::xSectionParam>
			CalcMx
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections,
				const Standard_Real y0, 
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT std::vector<marineLib::xSectionParam>
			CalcMy
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections,
				const Standard_Real x0,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT Standard_Real
			CalcWettedArea
			(
				const Marine_CmpSection& theSection,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT Pnt2d
			CalcCentre
			(
				const std::shared_ptr<Marine_Section>& theSection,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT Pnt2d
			CalcCentre
			(
				const Marine_CmpSection& theSection,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT Standard_Real
			CalcXCentre
			(
				const std::shared_ptr<Marine_Section>& theSection,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT Standard_Real
			CalcYCentre
			(
				const std::shared_ptr<Marine_Section>& theSection,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT Standard_Real
			CalcXCentre
			(
				const Marine_CmpSection& theSection,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT Standard_Real
			CalcYCentre
			(
				const Marine_CmpSection& theSection,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT std::vector<marineLib::xSectionParam>
			CalcVolume
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT Standard_Real
			CalcWaterCurveLength
			(
				const marineLib::Section_Wetted& theSection,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT Entity2d_Box 
			RetrieveRectangle
			(
				const Marine_WaterCurve& theCurve, 
				const Standard_Real xs, 
				const Standard_Real dx
			);

		static TnbMarine_EXPORT std::pair<Standard_Real, Standard_Real>
			CalcWaterCurveIx
			(
				const Marine_WaterCurve& theCurve, 
				const Standard_Real y0, 
				const Standard_Real xs, 
				const Standard_Real dx
			);

		static TnbMarine_EXPORT std::pair<Standard_Real, Standard_Real>
			CalcWaterCurveIy
			(
				const Marine_WaterCurve& theCurve,
				const Standard_Real x0, 
				const Standard_Real xs,
				const Standard_Real dx
			);

		static TnbMarine_EXPORT std::pair<Standard_Real, Standard_Real>
			CalcWaterCurveMx
			(
				const Marine_WaterCurve& theCurve, 
				const Standard_Real y0, 
				const Standard_Real xs, 
				const Standard_Real dx
			);

		static TnbMarine_EXPORT std::pair<Standard_Real, Standard_Real>
			CalcWaterCurveMy
			(
				const Marine_WaterCurve& theCurve, 
				const Standard_Real x0, 
				const Standard_Real xs, 
				const Standard_Real dx
			);

		static TnbMarine_EXPORT std::pair<Standard_Real, Standard_Real>
			CalcWaterCurveIx
			(
				const marineLib::Section_Wetted& theSection,
				const Standard_Real y0, 
				const Standard_Real xs,
				const Standard_Real dx
			);

		static TnbMarine_EXPORT std::pair<Standard_Real, Standard_Real>
			CalcWaterCurveIy
			(
				const marineLib::Section_Wetted& theSection,
				const Standard_Real x0,
				const Standard_Real xs, 
				const Standard_Real dx
			);

		static TnbMarine_EXPORT std::pair<Standard_Real, Standard_Real>
			CalcWaterCurveMx
			(
				const marineLib::Section_Wetted& theSection, 
				const Standard_Real y0,
				const Standard_Real xs, 
				const Standard_Real dx
			);

		static TnbMarine_EXPORT std::pair<Standard_Real, Standard_Real>
			CalcWaterCurveMy
			(
				const marineLib::Section_Wetted& theSection,
				const Standard_Real x0, 
				const Standard_Real xs,
				const Standard_Real dx
			);

		static TnbMarine_EXPORT Standard_Real
			CalcWaterCurveLength
			(
				const Marine_CmpSection& theSection,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT std::pair<Standard_Real, Standard_Real>
			CalcWaterCurveIx
			(
				const Marine_CmpSection& theSection,
				const Standard_Real xs,
				const Standard_Real y0,
				const Standard_Real dx
			);

		static TnbMarine_EXPORT std::pair<Standard_Real, Standard_Real>
			CalcWaterCurveIy
			(
				const Marine_CmpSection& theSection, 
				const Standard_Real xs,
				const Standard_Real x0, 
				const Standard_Real dx
			);

		static TnbMarine_EXPORT std::pair<Standard_Real, Standard_Real>
			CalcWaterCurveMx
			(
				const Marine_CmpSection& theSection,
				const Standard_Real xs,
				const Standard_Real y0, 
				const Standard_Real dx
			);

		static TnbMarine_EXPORT std::pair<Standard_Real, Standard_Real>
			CalcWaterCurveMy
			(
				const Marine_CmpSection& theSection,
				const Standard_Real xs,
				const Standard_Real x0,
				const Standard_Real dx
			);

		/*static TnbMarine_EXPORT Standard_Real
			CalcWaterCurveBreadth
			(
				const marineLib::Section_Wetted& theSection
			);

		static TnbMarine_EXPORT Standard_Real
			CalcWaterCurveBreadth
			(
				const Marine_CmpSection& theSection
			);*/

		static TnbMarine_EXPORT Standard_Real
			CalcWettedHullCurveLength
			(
				const marineLib::Section_Wetted& theSection,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT Standard_Real
			CalcWettedHullCurveLength
			(
				const Marine_CmpSection& theSection,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT std::vector<marineLib::xSectionParam>
			CalcWettedHullSurfaceArea
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT std::vector<marineLib::xSectionParam>
			CalcWaterPlaneArea
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT std::vector<marineLib::xSectionParam> 
			CalcWaterPlaneIx
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections, 
				const Standard_Real y0
			);

		static TnbMarine_EXPORT std::vector<marineLib::xSectionParam> 
			CalcWaterPlaneIy
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections,
				const Standard_Real x0
			);

		static TnbMarine_EXPORT std::vector<marineLib::xSectionParam> 
			CalcWaterPlaneMx
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections, 
				const Standard_Real y0
			);

		static TnbMarine_EXPORT std::vector<marineLib::xSectionParam> 
			CalcWaterPlaneMy
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections,
				const Standard_Real x0
			);

		static TnbMarine_EXPORT Pnt3d
			CalcCentreProductVolume
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT void
			Heel
			(
				const std::shared_ptr<Marine_CmpSection>& theSection,
				const gp_Ax2d& theAx
			);

		static TnbMarine_EXPORT void
			Heel
			(
				const std::shared_ptr<Marine_Section>& theSection,
				const gp_Ax2d& theAx
			);

		static TnbMarine_EXPORT void
			Heel
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theModel,
				const gp_Ax2d& theAx
			);

		static TnbMarine_EXPORT void
			Heel
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theModel,
				const gp_Ax1& theAx, 
				const Standard_Real theAngle
			);

		static TnbMarine_EXPORT std::shared_ptr<Geo_xDistb>
			HeelDistb
			(
				const Standard_Real theDeg0,
				const Standard_Real theDeg1, 
				const Standard_Integer theNbHeels
			);

		/*static TnbMarine_EXPORT std::shared_ptr<Pln_Wire>
			WaterSection
			(
				const Handle(Geom_Curve)& theWaterCurve,
				const gp_Ax2& theSystem,
				const Standard_Real theZmin,
				const Standard_Real theMinTol,
				const Standard_Real theMaxTol
			);*/

		/*static TnbMarine_EXPORT std::vector<std::shared_ptr<Marine_Section>>
			WaterSections
			(
				const Marine_CrossSection& theModel,
				const Marine_Wave& theWave,
				const Entity3d_Box& theDomain,
				const Standard_Real theMinTol,
				const Standard_Real theMaxTol
			);*/

		/*static TnbMarine_EXPORT std::vector<std::shared_ptr<Marine_Section>>
			StillWaterSections
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theModel, 
				const Standard_Real theZ,
				const Entity3d_Box& theDomain
			);*/


		/*static TnbMarine_EXPORT std::vector<marineLib::xSectionParam>
			CrossCurve
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections,
				const Entity3d_Box& theDomain,
				const Standard_Real theZmin,
				const Standard_Real theZmax,
				const Standard_Integer nbZ,
				const gp_Ax1& theK,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);*/

		/*static TnbMarine_EXPORT std::shared_ptr<Marine_WaterDomain>
			RetrieveStillWaterDomain
			(
				const std::shared_ptr<Marine_Domain>& theDomain,
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theModel,
				const Standard_Real theZ
			);*/

		/*static TnbMarine_EXPORT std::vector<std::shared_ptr<Marine_WaterDomain>>
			RetrieveStillWaterDomains
			(
				const std::shared_ptr<Marine_Domain>& theDomain,
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theModel,
				const Standard_Real theZmin,
				const Standard_Real theZmax,
				const Standard_Integer nbZ
			);

		static TnbMarine_EXPORT std::vector<std::shared_ptr<Marine_WaterDomain>>
			RetrieveStillWaterDomains
			(
				const std::shared_ptr<Marine_Domain>& theDomain,
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theModel,
				const Geo_xDistb& theZ
			);*/

		/*static TnbMarine_EXPORT Standard_Real
			CalcWetVolume
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);*/

		/*static TnbMarine_EXPORT std::shared_ptr<Marine_CmpSection>
			CreateSection
			(
				const Cad3d_TModel& theModel, 
				const gp_Pln& thePlane,
				const Standard_Boolean ParallelFalg = Standard_False
			);*/

		static TnbMarine_EXPORT std::shared_ptr<Marine_Graph>
			CreateGraph
			(
				const Handle(Geom2d_Curve)& theCurve
			);

		static TnbMarine_EXPORT void Check_xCmptSections
		(
			const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections
		);
	};
}

#include <MarineBase_ToolsI.hxx>

#endif // !_MarineBase_Tools_Header
