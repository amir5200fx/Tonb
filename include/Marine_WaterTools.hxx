#pragma once
#ifndef _Marine_WaterTools_Header
#define _Marine_WaterTools_Header

#include <Standard_Handle.hxx>
#include <Standard_TypeDef.hxx>
#include <Entity3d_BoxFwd.hxx>

class Geom_Curve;
class gp_Ax2;

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Wire;
	class Marine_Wave;
	class Marine_Section;
	class Marine_CmpSection;

	class Marine_WaterTools
	{

	public:

		static std::shared_ptr<Pln_Wire>
			WaterSection
			(
				const Handle(Geom_Curve)& theWaterCurve,
				const gp_Ax2& theSystem,
				const Standard_Real theZmin,
				const Standard_Real theMinTol,
				const Standard_Real theMaxTol
			);

		static std::vector<std::shared_ptr<Marine_Section>>
			WaterSections
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theBody,
				const Marine_Wave& theWave,
				const Entity3d_Box& theDomain,
				const Standard_Real theMinTol,
				const Standard_Real theMaxTol
			);

		static std::vector<std::shared_ptr<Marine_Section>>
			StillWaterSections
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theBody,
				const Standard_Real theZ,
				const Entity3d_Box& theDomain
			);

		static std::vector<std::shared_ptr<Marine_Section>>
			RetrieveNonDeepWLs
			(
				const Marine_CmpSection & theSection
			);
	};
}

#endif // !_Marine_WaterTools_Header
