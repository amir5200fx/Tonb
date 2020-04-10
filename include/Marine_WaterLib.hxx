#pragma once
#ifndef _Marine_WaterLib_Header
#define _Marine_WaterLib_Header

#include <Standard_Handle.hxx>
#include <Entity3d_BoxFwd.hxx>

class Geom_Curve;
class gp_Ax2;

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Geo_xDistb;
	class Pln_Wire;
	class Marine_Section;
	class Marine_CmpSection;
	class Marine_wCmpSection;
	class Marine_WettedBody;
	
	class Marine_WaterDomain;
	class Marine_WaterDomains;
	class Marine_Domain;
	class Marine_Wave;

	class Marine_WaterLib
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
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theModel, 
				const Marine_Wave& theWave, 
				const Entity3d_Box& theDomain, 
				const Standard_Real theMinTol, 
				const Standard_Real theMaxTol
			);

		static std::vector<std::shared_ptr<Marine_Section>>
			StillWaterSections
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theModel,
				const Standard_Real theZ,
				const Entity3d_Box& theDomain
			);

		static std::shared_ptr<Marine_WaterDomain>
			RetrieveStillWaterDomain
			(
				const std::shared_ptr<Marine_Domain>& theDomain, 
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theModel,
				const Standard_Real theZ
			);

		static std::shared_ptr<Marine_WaterDomains>
			RetrieveStillWaterDomains
			(
				const std::shared_ptr<Marine_Domain>& theDomain,
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theModel,
				const Geo_xDistb& theZ
			);

		static std::vector<std::shared_ptr<Marine_Section>>
			RetrieveWLs
			(
				const Marine_CmpSection& theSection
			);

		static const std::shared_ptr<Marine_CmpSection> &
			FUW
			(
				const Marine_WettedBody& theBody
			);

		static const std::shared_ptr<Marine_CmpSection> &
			AUW
			(
				const Marine_WettedBody& theBody
			);

		static const std::shared_ptr<Marine_CmpSection> & 
			FWL
			(
				const Marine_WettedBody& theBody
			);

		static const std::shared_ptr<Marine_CmpSection> & 
			AWL
			(
				const Marine_WettedBody& theBody
			);

	};
}

#endif // !_Marine_WaterLib_Header
