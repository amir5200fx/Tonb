#pragma once
#ifndef _Marine_BodyTools_Header
#define _Marine_BodyTools_Header

#include <Standard_TypeDef.hxx>
#include <Marine_SectionsFwd.hxx>
#include <Marine_BodiesFwd.hxx>
#include <Marine_BodyType.hxx>
#include <Entity3d_BoxFwd.hxx>

#include <memory>
#include <vector>

class gp_Ax1;
class gp_Ax2d;

namespace tnbLib
{

	// Forward Declarations
	class Marine_WaterDomain;
	class Marine_CmpSection;

	class Marine_BodyTools
	{

	public:

		static Entity3d_Box BoundingBox(const Marine_Body& theBody);

		static Standard_Boolean IsWetted(const Marine_Body& theBody);

		static Standard_Boolean IsDry(const Marine_Body& theBody);

		static Standard_Boolean IsTank(const Marine_Body& theBody);

		static Standard_Boolean IsSail(const Marine_Body& theBody);

		static Standard_Boolean IsDisplacer(const Marine_Body& theBody);

		static std::shared_ptr<marineLib::Body_Wetted> 
			WettedBody
			(
				const std::shared_ptr<Marine_Body>& theBody
			);

		static std::shared_ptr<marineLib::Body_Dry> 
			DryBody
			(
				const std::shared_ptr<Marine_Body>& theBody
			);

		static std::shared_ptr<marineLib::Body_Tank> 
			TankBody
			(
				const std::shared_ptr<Marine_Body>& theBody
			);

		static std::shared_ptr<marineLib::Body_Sail> 
			SailBody
			(
				const std::shared_ptr<Marine_Body>& theBody
			);

		static std::shared_ptr<marineLib::Body_Displacer> 
			DisplacerBody
			(
				const std::shared_ptr<Marine_Body>& theBody
			);

		static std::shared_ptr<Marine_Body>
			BodyCreator
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections,
				const Marine_BodyType t
			);

		static std::shared_ptr<Marine_Body> 
			WettedBody
			(
				const std::shared_ptr<marineLib::Body_Displacer>& theBody, 
				const std::shared_ptr<Marine_WaterDomain>& theDomain
			);

		static std::shared_ptr<Marine_Body> 
			DryBody
			(
				const std::shared_ptr<marineLib::Body_Displacer>& theBody, 
				const std::shared_ptr<Marine_WaterDomain>& theDomain
			);

		static void Heel(const std::shared_ptr<Marine_Body>& theBody, const gp_Ax1& theAx, const Standard_Real theAngle);

		static void Heel(const std::shared_ptr<Marine_Body>& theBody, const gp_Ax2d& theAx);

		static void CheckTypeConsistency(const Marine_Body& theBody);

		static void CheckTypeConsistency(const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections);
	};
}

#endif // !_Marine_BodyTools_Header
