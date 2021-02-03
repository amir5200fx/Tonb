#pragma once
#ifndef _Marine_WaterTools_Header
#define _Marine_WaterTools_Header

#include <Standard_Handle.hxx>
#include <Standard_TypeDef.hxx>
#include <Entity3d_BoxFwd.hxx>
#include <Marine_Module.hxx>

class Geom_Curve;
class gp_Ax2;

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Pnt2d;
	class Pln_Wire;
	class Marine_Water;
	class Marine_Wave;
	class Marine_Section;
	class Marine_CmpSection;
	class Marine_Domain;

	class Marine_WaterTools
	{

	public:

		static TnbMarine_EXPORT Handle(Geom_Curve) 
			WaterLine
			(
				const Marine_Wave& theWave,
				const gp_Ax2& theSys
			);

		static TnbMarine_EXPORT std::shared_ptr<Pln_Wire>
			WaterSection
			(
				const Handle(Geom_Curve)& theWaterCurve,
				const gp_Ax2& theSystem,
				const Standard_Real theZmin,
				const Standard_Real theMinTol,
				const Standard_Real theMaxTol
			);

		static std::shared_ptr<Pln_Wire> WaterSection(const Pnt2d& theP0, const Pnt2d& theP1);

		static TnbMarine_EXPORT std::shared_ptr<Pln_Wire> 
			WaterSection
			(
				const Marine_Wave& theWave,
				const gp_Ax2& theSys, 
				const Standard_Real theZmin, 
				const Standard_Real theMinTol, 
				const Standard_Real theMaxTol
			);

		static TnbMarine_EXPORT std::shared_ptr<Marine_Section>
			WaterSection
			(
				const Marine_Wave& theWave, 
				const Marine_CmpSection& section, 
				const Standard_Real theMinTol, 
				const Standard_Real theMaxTol
			);

		static TnbMarine_EXPORT std::vector<std::shared_ptr<Marine_Section>>
			WaterSections
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theBody,
				const Marine_Wave& theWave,
				const Entity3d_Box& theDomain,
				const Standard_Real theMinTol,
				const Standard_Real theMaxTol
			);

		static TnbMarine_EXPORT std::vector<std::shared_ptr<Marine_Section>>
			StillWaterSections
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theBody,
				const Standard_Real theZ,
				const Entity3d_Box& theDomain
			);

		static TnbMarine_EXPORT std::shared_ptr<Marine_Water>
			StillWater
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theBody, 
				const Standard_Real theZ,
				const Entity3d_Box& theDomain
			);

		static TnbMarine_EXPORT std::shared_ptr<Marine_Water>
			Water
			(
				const std::vector<std::shared_ptr<Marine_Section>>& theSections
			);

		static TnbMarine_EXPORT std::shared_ptr<Marine_Water>
			Water
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theBody, 
				const std::shared_ptr<Marine_Wave>& theWave, 
				const Entity3d_Box& theDomain,
				const Standard_Real theMinTol, 
				const Standard_Real theMaxTol
			);

		static TnbMarine_EXPORT std::shared_ptr<Marine_Wave> 
			FlatWave
			(
				const std::shared_ptr<Marine_Domain>& theDomain,
				const Standard_Real theZ
			);

		static TnbMarine_EXPORT std::vector<std::shared_ptr<Marine_Section>>
			RetrieveNonDeepWLs
			(
				const Marine_CmpSection & theSection
			);
	};
}

#endif // !_Marine_WaterTools_Header
