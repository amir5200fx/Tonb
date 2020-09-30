#pragma once
#ifndef _Marine_WaterLib_Header
#define _Marine_WaterLib_Header

#include <Standard_Handle.hxx>
#include <Entity3d_BoxFwd.hxx>
#include <Marine_BodiesFwd.hxx>

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
	
	class Marine_WaterDomain;
	class Marine_MultLevWaterDomain;
	class Marine_Domain;
	class Marine_Water;
	class Marine_Wave;

	class Marine_WaterLib
	{

	public:

		static std::shared_ptr<Marine_Domain> 
			Domain
			(
				const marineLib::Body_Displacer& theBody
			);

		static std::shared_ptr<Marine_Domain> 
			Domain
			(
				const marineLib::Body_Tank& theBody
			);

		//- Throw an exception if the body is not a hull or a tank
		/*static std::shared_ptr<Marine_Water> 
			StillWater
			(
				const Marine_Body& theBody,
				const Marine_Domain& theDomain,
				const Standard_Real theZ
			);*/

		//- Throw an exception if the body is not a displacer or a tank
		static std::shared_ptr<Marine_WaterDomain>
			StillWaterDomain
			(
				const std::shared_ptr<Marine_Body>& theBody,
				const std::shared_ptr<Marine_Domain>& theDomain,
				const Standard_Real theZ
			);

		static std::shared_ptr<Marine_WaterDomain>
			StillWaterDomain
			(
				const marineLib::Body_Displacer& theBody,
				const std::shared_ptr<Marine_Domain>& theDomain,
				const Standard_Real theZ			
			);

		static std::shared_ptr<Marine_WaterDomain>
			StillWaterDomain
			(
				const marineLib::Body_Tank& theBody,
				const std::shared_ptr<Marine_Domain>& theDomain,
				const Standard_Real theZ
			);

		static std::shared_ptr<Marine_MultLevWaterDomain>
			MultiLevelsStillWaterDomain
			(
				const std::shared_ptr<Marine_Body>& theBody,
				const std::shared_ptr<Marine_Domain>& theDomain,
				const Geo_xDistb& theZ
			);

		static std::shared_ptr<Marine_MultLevWaterDomain>
			MultiLevelsStillWaterDomain
			(
				const marineLib::Body_Displacer& theBody,
				const std::shared_ptr<Marine_Domain>& theDomain,
				const Geo_xDistb& theZ
			);

		static std::shared_ptr<Marine_MultLevWaterDomain>
			MultiLevelsStillWaterDomain
			(
				const marineLib::Body_Tank& theBody,
				const std::shared_ptr<Marine_Domain>& theDomain,
				const Geo_xDistb& theZ
			);

		static std::shared_ptr<Marine_WaterDomain>
			WaterDomain
			(
				const std::shared_ptr<Marine_Body>& theBody,
				const Marine_Wave& theWave,
				const std::shared_ptr<Marine_Domain>& theDomain,
				const Standard_Real theMinTol,
				const Standard_Real theMaxTol
			);

		static std::shared_ptr<Marine_WaterDomain>
			WaterDomain
			(
				const marineLib::Body_Displacer& theBody,
				const Marine_Wave& theWave,
				const std::shared_ptr<Marine_Domain>& theDomain,
				const Standard_Real theMinTol,
				const Standard_Real theMaxTol
			);

		static std::shared_ptr<Marine_WaterDomain>
			WaterDomain
			(
				const marineLib::Body_Tank& theBody,
				const Marine_Wave& theWave,
				const std::shared_ptr<Marine_Domain>& theDomain,
				const Standard_Real theMinTol,
				const Standard_Real theMaxTol
			);

		static const std::shared_ptr<Marine_CmpSection> &
			FUW
			(
				const marineLib::Body_Wetted& theBody
			);

		static const std::shared_ptr<Marine_CmpSection> &
			AUW
			(
				const marineLib::Body_Wetted& theBody
			);

		static const std::shared_ptr<Marine_CmpSection> & 
			FWL
			(
				const marineLib::Body_Wetted& theBody
			);

		static const std::shared_ptr<Marine_CmpSection> & 
			AWL
			(
				const marineLib::Body_Wetted& theBody
			);

	};
}

#endif // !_Marine_WaterLib_Header
