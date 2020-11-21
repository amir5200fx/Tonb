#pragma once
#ifndef _Marine_SectTools_Header
#define _Marine_SectTools_Header

#include <Standard_Handle.hxx>
#include <Standard_TypeDef.hxx>
#include <Entity3d_BoxFwd.hxx>
#include <Marine_CmpSectionType.hxx>
#include <Marine_SectionType.hxx>
#include <Marine_SectionsFwd.hxx>
#include <Marine_Module.hxx>

#include <memory>
#include <vector>

class gp_Ax2;
class Geom2d_Curve;
class TopoDS_Shape;
class gp_Pln;

namespace tnbLib
{

	// Forward Declarations
	class Marine_CmpSection;
	class Cad2d_Plane;
	class Pln_Curve;
	class Pln_Wire;

	class Marine_SectTools
	{

	public:

		static TnbMarine_EXPORT Standard_Boolean 
			IsOuter
			(
				const std::shared_ptr<Marine_Section>& theSection
			);

		static TnbMarine_EXPORT Standard_Boolean 
			IsInner
			(
				const std::shared_ptr<Marine_Section>& theSection
			);

		//- throw an exception if the section is inner
		static TnbMarine_EXPORT Standard_Integer
			NbInners
			(
				const std::shared_ptr<Marine_Section>& theSection
			);

		static TnbMarine_EXPORT Standard_Boolean 
			HasInnerSection
			(
				const std::shared_ptr<Marine_Section>& theSection
			);

		static TnbMarine_EXPORT Standard_Boolean 
			HasInnerSection
			(
				const Marine_CmpSection& theSection
			);

		//- throw an exception if the section is inner
		static TnbMarine_EXPORT std::vector<std::shared_ptr<Marine_Section>> 
			RetrieveInners
			(
				const std::shared_ptr<Marine_Section>& theSection
			);

		static TnbMarine_EXPORT std::shared_ptr<marineLib::Section_Dry>
			DrySection
			(
				const std::shared_ptr<Marine_Section>& theSection
			);

		static TnbMarine_EXPORT std::shared_ptr<marineLib::Section_Wetted> 
			WettedSection
			(
				const std::shared_ptr<Marine_Section>& theSection
			);

		static TnbMarine_EXPORT std::shared_ptr<marineLib::Section_Displacer> 
			DisplacerSection
			(
				const std::shared_ptr<Marine_Section>& theSection
			);

		static TnbMarine_EXPORT std::shared_ptr<marineLib::Section_Sail> 
			SailSection
			(
				const std::shared_ptr<Marine_Section>& theSection
			);

		static TnbMarine_EXPORT std::shared_ptr<marineLib::Section_Tank>
			TankSection
			(
				const std::shared_ptr<Marine_Section>& theSection
			);

		static TnbMarine_EXPORT std::shared_ptr<marineLib::Section_WaterLine> 
			WaterLineSection
			(
				const std::shared_ptr<Marine_Section>& theSection
			);

		static TnbMarine_EXPORT std::shared_ptr<marineLib::Section_Water> 
			WaterSection
			(
				const std::shared_ptr<Marine_Section>& theSection
			);

		//- throw an exception if the section is inner
		static TnbMarine_EXPORT std::shared_ptr<Cad2d_Plane> 
			ConvertToPlane
			(
				const std::shared_ptr<Marine_Section>& theSection
			);

		static TnbMarine_EXPORT std::shared_ptr<Marine_Section> 
			ConvertToSection
			(
				const std::shared_ptr<Cad2d_Plane>& thePlane,
				const Marine_SectionType t
			);

		static TnbMarine_EXPORT std::vector<std::shared_ptr<Cad2d_Plane>>
			RetrievePalnes
			(
				const std::shared_ptr<Marine_CmpSection>& theSection
			);

		static TnbMarine_EXPORT std::shared_ptr<Marine_CmpSection> 
			ConvertToComposite
			(
				const std::shared_ptr<Marine_Section>& theSect
			);

		static TnbMarine_EXPORT std::vector<std::shared_ptr<Marine_Section>>
			SectionCreator
			(
				const std::vector<std::shared_ptr<Pln_Curve>>& theCurves,
				const gp_Ax2& theSystem,
				const Marine_SectionType& t,
				const Standard_Real theMinTol,
				const Standard_Real theMaxTol
			);

		static TnbMarine_EXPORT std::vector<std::shared_ptr<Marine_Section>>
			SectionCreator
			(
				const std::vector<Handle(Geom2d_Curve)>& theCurves,
				const gp_Ax2& theSystem,
				const Marine_SectionType& t,
				const Standard_Real theMinTol,
				const Standard_Real theMaxTol
			);

		static TnbMarine_EXPORT std::shared_ptr<Marine_Section>
			SectionCreator
			(
				const std::shared_ptr<Pln_Wire>& theOuter, 
				const gp_Ax2& theSystem,
				const Marine_SectionType& t
			);

		static TnbMarine_EXPORT std::shared_ptr<Marine_Section>
			SectionCreator
			(
				const std::shared_ptr<Pln_Wire>& theOuter,
				const Marine_SectionType& t
			);

		static TnbMarine_EXPORT std::vector<std::shared_ptr<Marine_Section>>
			SectionCreator
			(
				const TopoDS_Shape& theEdges,
				const gp_Ax2& theSystem,
				const Marine_SectionType& t,
				const Standard_Real theMinTol,
				const Standard_Real theMaxTol
			);

		static TnbMarine_EXPORT Standard_Boolean 
			IsXSection
			(
				const std::shared_ptr<Marine_Section>& theSection
			);

		static TnbMarine_EXPORT Standard_Boolean 
			IsDry
			(
				const Marine_CmpSection& theSect
			);

		static TnbMarine_EXPORT Standard_Boolean 
			IsWetted
			(
				const Marine_CmpSection& theSect
			);

		static TnbMarine_EXPORT Standard_Boolean 
			IsDisplacer
			(
				const Marine_CmpSection& theSect
			);

		static TnbMarine_EXPORT Standard_Boolean 
			IsSail
			(
				const Marine_CmpSection& theSect
			);

		static TnbMarine_EXPORT Standard_Boolean 
			IsTank
			(
				const Marine_CmpSection& theSect
			);

		static TnbMarine_EXPORT Standard_Boolean 
			IsWaterLine
			(
				const Marine_CmpSection& theSect
			);

		static TnbMarine_EXPORT Standard_Boolean 
			IsWater
			(
				const Marine_CmpSection& theSect
			);

		static TnbMarine_EXPORT Standard_Boolean 
			SameDirection
			(
				const Marine_CmpSection& theSect0,
				const Marine_CmpSection& theSect1
			);

		static TnbMarine_EXPORT gp_Pln 
			gpPln
			(
				const Marine_Section& theSect
			);

		static TnbMarine_EXPORT gp_Pln 
			gpPln
			(
				const Marine_CmpSection& theSect
			);

		static TnbMarine_EXPORT Entity3d_Box
			BoundingBox
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theModel
			);

		static TnbMarine_EXPORT std::shared_ptr<Marine_CmpSection>
			CmpSectionCreator
			(
				const std::vector<std::shared_ptr<Marine_Section>>& theSections
			);

		static TnbMarine_EXPORT std::shared_ptr<Marine_Section> 
			FitTankToHull
			(
				const std::shared_ptr<Marine_Section>& theTank, 
				const std::shared_ptr<Marine_Section>& theHull
			);

		static TnbMarine_EXPORT std::shared_ptr<Marine_Section>
			FitTankToHull
			(
				const std::shared_ptr<Marine_Section>& theTank, 
				const std::shared_ptr<Marine_CmpSection>& theHull
			);

		template<class SectionType>
		static std::vector<std::shared_ptr<Marine_Section>> 
			RetrieveInners
			(
				const marineLib::OuterSection<SectionType>& theSection
			);

		template<>
		static TnbMarine_EXPORT std::vector<std::shared_ptr<Marine_Section>> 
			RetrieveInners<marineLib::Section_Water>
			(
				const marineLib::OuterSection<marineLib::Section_Water>& theSection
				);

		template<class SectionType>
		struct CreateSection
		{
			static std::shared_ptr<Marine_Section> _
			(
				const std::shared_ptr<Pln_Wire>& theOuter,
				const std::shared_ptr<std::vector<std::shared_ptr<Pln_Wire>>>& theInners
			);
		};

		template<>
		struct CreateSection<marineLib::Section_Water>
		{
			static TnbMarine_EXPORT std::shared_ptr<Marine_Section> _(const std::shared_ptr<Pln_Wire>& theOuter);
		};

		static TnbMarine_EXPORT void SetLocation(const std::shared_ptr<Marine_CmpSection>& theSection, const Standard_Real x);

		static TnbMarine_EXPORT void CheckTypeConsistency
		(
			const std::shared_ptr<Marine_Section>& theSect
		);

		static TnbMarine_EXPORT void CheckTypeConsistency
		(
			const Marine_CmpSection& theSect
		);

		static TnbMarine_EXPORT void CheckInnerSection(const std::shared_ptr<Marine_Section>& theSection);

		static TnbMarine_EXPORT void CheckInnerSection(const Marine_CmpSection& theSect);
	};
}

#include <Marine_SectToolsI.hxx>

#endif // !_Marine_SectTools_Header
