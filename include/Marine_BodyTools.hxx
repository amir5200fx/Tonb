#pragma once
#ifndef _Marine_BodyTools_Header
#define _Marine_BodyTools_Header

#include <Standard_TypeDef.hxx>
#include <Marine_SectionsFwd.hxx>
#include <Marine_BodiesFwd.hxx>
#include <Marine_BodyType.hxx>
#include <Marine_SailModelsFwd.hxx>
#include <Entity3d_BoxFwd.hxx>
#include <Entity2d_TriangulationFwd.hxx>
#include <Marine_Module.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <memory>
#include <vector>

class gp_Ax1;
class gp_Ax2d;

namespace tnbLib
{

	// Forward Declarations
	class Marine_WaterDomain;
	class Marine_CmpSection;
	class Marine_Shape;
	class Marine_Model;
	class NumAlg_AdaptiveInteg_Info;

	class Marine_BodyTools
	{

	public:

		static TnbMarine_EXPORT Entity3d_Box BoundingBox(const Marine_Body& theBody);

		static TnbMarine_EXPORT Standard_Boolean IsWetted(const Marine_Body& theBody);

		static TnbMarine_EXPORT Standard_Boolean IsDry(const Marine_Body& theBody);

		static TnbMarine_EXPORT Standard_Boolean IsTank(const Marine_Body& theBody);

		static TnbMarine_EXPORT Standard_Boolean IsSail(const Marine_Body& theBody);

		static TnbMarine_EXPORT Standard_Boolean IsDisplacer(const Marine_Body& theBody);

		static TnbMarine_EXPORT Standard_Real
			CalcLateralProjArea
			(
				const std::shared_ptr<Marine_Body>& theBody,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT Standard_Real 
			CalcLateralZbar
			(
				const std::shared_ptr<Marine_Body>& theBody,
				const Standard_Real z0, 
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT Standard_Real 
			CalcVolume
			(
				const Marine_Body& theBody, 
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static TnbMarine_EXPORT std::shared_ptr<marineLib::Body_Wetted> 
			WettedBody
			(
				const std::shared_ptr<Marine_Body>& theBody
			);

		static TnbMarine_EXPORT std::shared_ptr<marineLib::Body_Dry> 
			DryBody
			(
				const std::shared_ptr<Marine_Body>& theBody
			);

		static TnbMarine_EXPORT std::shared_ptr<marineLib::Body_Tank> 
			TankBody
			(
				const std::shared_ptr<Marine_Body>& theBody
			);

		static TnbMarine_EXPORT std::shared_ptr<marineLib::Body_Sail> 
			SailBody
			(
				const std::shared_ptr<Marine_Body>& theBody
			);

		static TnbMarine_EXPORT std::shared_ptr<marineLib::Body_Displacer> 
			DisplacerBody
			(
				const std::shared_ptr<Marine_Body>& theBody
			);

		static TnbMarine_EXPORT std::shared_ptr<Marine_Body>
			BodyCreator
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections,
				const Marine_BodyType t
			);

		static TnbMarine_EXPORT std::shared_ptr<Marine_Body>
			BodyCreator
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections,
				const std::shared_ptr<Marine_Shape>& theShape,
				const Marine_BodyType t
			);

		static TnbMarine_EXPORT std::shared_ptr<Marine_Body> 
			WettedBody
			(
				const std::shared_ptr<marineLib::Body_Displacer>& theBody, 
				const std::shared_ptr<Marine_WaterDomain>& theDomain
			);

		static TnbMarine_EXPORT std::shared_ptr<Marine_Body> 
			DryBody
			(
				const std::shared_ptr<marineLib::Body_Displacer>& theBody, 
				const std::shared_ptr<Marine_WaterDomain>& theDomain
			);

		static TnbMarine_EXPORT std::shared_ptr<Entity2d_Triangulation>
			RetrieveLateralProjArea
			(
				const std::shared_ptr<Marine_Body>& theBody
			);

		static TnbMarine_EXPORT std::shared_ptr<Entity2d_Triangulation>
			RetrieveLateralProjArea
			(
				const std::shared_ptr<Marine_Model>& theModel
			);

		static TnbMarine_EXPORT std::shared_ptr<Entity2d_Triangulation> 
			RetrieveLateralProjArea
			(
				const std::shared_ptr<marineLib::Model_Sail>& theSail
			);

		static TnbMarine_EXPORT void 
			WaterSectionOnBody
			(
				const std::shared_ptr<marineLib::BodyConstructor_Shape<marineLib::Body_Wetted>>& theBody,
				const std::shared_ptr<Marine_WaterDomain>& theDomain
			);

		static TnbMarine_EXPORT void 
			Heel
			(
				const std::shared_ptr<Marine_Body>& theBody,
				const gp_Ax1& theAx,
				const Standard_Real theAngle
			);

		static TnbMarine_EXPORT void 
			Heel
			(
				const std::shared_ptr<Marine_Body>& theBody, 
				const gp_Ax2d& theAx
			);

		static TnbMarine_EXPORT void 
			CheckTypeConsistency
			(
				const Marine_Body& theBody
			);

		static TnbMarine_EXPORT void 
			CheckTypeConsistency
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections
			);
	};
}

#endif // !_Marine_BodyTools_Header
