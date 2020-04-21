#include <ISC08_RightLevCrit.hxx>

#include <Geo_Tools.hxx>
#include <Cad2d_CmptLib.hxx>
#include <Marine_Criterion.hxx>
#include <Marine_CriterionTable.hxx>
#include <MarineBase_Tools.hxx>
#include <Marine_System.hxx>
#include <HydStatic_rArmCurve.hxx>
#include <HydStatic_CmptLib.hxx>
#include <HydStatic_StbGraph.hxx>
#include <HydStatic_DFldCurve.hxx>
#include <HydStatic_GzQP.hxx>
#include <HydStatic_GM0Curve.hxx>
#include <error.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	const marineLib::Criterion_Standard ISC08_RightLevCrit::PHI_25(Geo_Tools::DegToRadian(25.0));
	const marineLib::Criterion_Standard ISC08_RightLevCrit::PHI_30(Geo_Tools::DegToRadian(30.0));
	const marineLib::Criterion_Standard ISC08_RightLevCrit::PHI_40(Geo_Tools::DegToRadian(40.0));

	const marineLib::Criterion_Standard ISC08_RightLevCrit::PHI_UPTO_30_MRAD(0.055);
	const marineLib::Criterion_Standard ISC08_RightLevCrit::PHI_UPTO_40_MRAD(0.09);
	const marineLib::Criterion_Standard ISC08_RightLevCrit::PHI_30_AND_40_MRAD(0.03);

	const marineLib::Criterion_Standard ISC08_RightLevCrit::MIN_RIGTHLEV_AT_PHI_30(0.2);
}

tnbLib::ISC08_RightLevCrit::ISC08_RightLevCrit()
{
}

tnbLib::ISC08_RightLevCrit::ISC08_RightLevCrit
(
	const std::shared_ptr<HydStatic_StbGraph>& theGZ
)
	: theStability_(theGZ)
{
}

void tnbLib::ISC08_RightLevCrit::Perform()
{
	if (NOT Stablity())
	{
		FatalErrorIn("void tnbLib::ISC08_RightLevCrit::Perform()")
			<< "no stability curve is loaded!" << endl
			<< abort(FatalError);
	}

	const auto& rightArm = Stablity()->RightingArm();
	if (NOT rightArm)
	{
		FatalErrorIn("void tnbLib::ISC08_RightLevCrit::Perform()")
			<< "no righting arm curve is loaded!" << endl
			<< abort(FatalError);
	}

	auto table = std::make_shared<Marine_CriterionTable>();
	Debug_Null_Pointer(table);

	table->SetName("Criteria regarding righting lever curve properties");
	auto& rows = table->ChangeTable();

	Standard_Integer nbCrit = 0;

	auto up_to_30_gz = HydStatic_ArmCurve::Clip(rightArm, 0, PHI_30());
	Debug_Null_Pointer(up_to_30_gz);

	/*2.2.1 the area under the righting lever curve (GZ) shall not
			be less than 0.055 meter-radians up to phi = 30 deg
			angle of heel and not less than 0.09 meter-radians up
			to phi = 40 deg or the angle of down-flooding phif if
			this angle is less than 40 deg. (~ p. 19/277)*/

	const auto& gz_geom_up_to_30 = up_to_30_gz->Geometry();
	Debug_Null_Pointer(gz_geom_up_to_30);

	const auto area_up_to_30 = 
		marineLib::Criterion_Value
		(
			Cad2d_CmptLib::AreaUnderCurve(gz_geom_up_to_30, 0, sysLib::gl_marine_integration_info)
		);

	const auto area_up_to_30_expln = 
		marineLib::Criterion_Epln
		(
			"The area under the righting lever curve (GZ curve) shall not be less than 0.055 meter-radians"
		);

	const auto crit = std::make_shared<Marine_Criterion>(++nbCrit, "righting lever criterion no. 1");
	Debug_Null_Pointer(crit);

	crit->SetExpln(std::move(area_up_to_30_expln));
	crit->SetValue(std::move(area_up_to_30));
	crit->SetStandard(ISC08_RightLevCrit::PHI_UPTO_30_MRAD);

	if (area_up_to_30() < ISC08_RightLevCrit::PHI_UPTO_30_MRAD())
	{
		crit->SetStatus(marineLib::Criterion_Status::PASS);
	}
	else
	{
		crit->SetStatus(marineLib::Criterion_Status::FAIL);
	}

	rows.push_back(std::move(crit));

	const auto& downFlooding = Stablity()->DwnFlooding();
	if (NOT downFlooding)
	{
		FatalErrorIn("void tnbLib::ISC08_RightLevCrit::Perform()")
			<< "no down flooding curve is loaded!" << endl
			<< abort(FatalError);
	}
	/*down-flooding angle: phif*/
	const auto phif = std::min(PHI_40(), downFlooding->DownFloodingAngle());

	/*	Additionally, the area under the righting lever curve (GZ curve) between the angles of heel of 
		30° and 40° or between 30° and phif, if this angle is less than 40°, shall not be less than 
		0.03 metre-radians. */

	const auto between_30_phif_gz = HydStatic_ArmCurve::Clip(rightArm, PHI_30(), phif);
	Debug_Null_Pointer(between_30_phif_gz);

	const auto& gz_geom_between_30_phif = between_30_phif_gz->Geometry();
	Debug_Null_Pointer(gz_geom_between_30_phif);

	const auto area_between_30_phif = 
		marineLib::Criterion_Value
		(
			Cad2d_CmptLib::AreaUnderCurve(gz_geom_between_30_phif, 0, sysLib::gl_marine_integration_info)
		);

	const auto area_between_30_phif_expln = 
		marineLib::Criterion_Epln
		(
			"The area under the righting lever curve (GZ curve) between the angles of heel of 30 deg and phif deg shall not be less than 0.03 meter-radians"
		);

	const auto crit2 = std::make_shared<Marine_Criterion>(++nbCrit, "righting lever criterion no. 2");
	Debug_Null_Pointer(crit2);

	crit2->SetExpln(std::move(area_between_30_phif_expln));
	crit2->SetValue(std::move(area_between_30_phif));
	crit2->SetStandard(ISC08_RightLevCrit::PHI_30_AND_40_MRAD);

	if (area_between_30_phif() < ISC08_RightLevCrit::PHI_30_AND_40_MRAD())
	{
		crit2->SetStatus(marineLib::Criterion_Status::FAIL);
	}
	else
	{
		crit2->SetStatus(marineLib::Criterion_Status::PASS);
	}

	rows.push_back(std::move(crit2));

	const auto area_up_to_phif = 
		marineLib::Criterion_Value
		(
			area_up_to_30() + 
			area_between_30_phif()
		);

	const auto area_up_to_phif_expln = 
		marineLib::Criterion_Epln
		(
			"The area under the righting lever curve (GZ curve) shall not be less than 0.09 meter-radians up to phif"
		);

	const auto crit3 = std::make_shared<Marine_Criterion>(++nbCrit, "righting lever criterion no. 3");
	Debug_Null_Pointer(crit3);

	crit3->SetExpln(std::move(area_up_to_phif_expln));
	crit3->SetValue(std::move(area_up_to_phif));
	crit3->SetStandard(ISC08_RightLevCrit::PHI_UPTO_40_MRAD);

	if (area_up_to_phif() < ISC08_RightLevCrit::PHI_UPTO_40_MRAD())
	{
		crit3->SetStatus(marineLib::Criterion_Status::FAIL);
	}
	else
	{
		crit3->SetStatus(marineLib::Criterion_Status::PASS);
	}

	rows.push_back(std::move(crit3));

	/* The righting lever GZ shall be at least 0.2 m at an angle of heel equal to or greater than 30 deg*/
	const auto min_gz_at_30 = marineLib::Criterion_Value(up_to_30_gz->MaxHeel());
	const auto min_gz_at_30_expln = 
		marineLib::Criterion_Epln
		(
			"The righting lever GZ shall be at least 0.2 m at an angle of heel equal to or greater than 30 deg"
		);

	const auto crit4 = std::make_shared<Marine_Criterion>(++nbCrit, "righting lever criterion no. 4");
	Debug_Null_Pointer(crit4);

	crit4->SetExpln(std::move(min_gz_at_30_expln));
	crit4->SetValue(std::move(min_gz_at_30));
	crit4->SetStandard(ISC08_RightLevCrit::MIN_RIGTHLEV_AT_PHI_30);

	if (min_gz_at_30() < ISC08_RightLevCrit::MIN_RIGTHLEV_AT_PHI_30())
	{
		crit4->SetStatus(marineLib::Criterion_Status::FAIL);
	}
	else
	{
		crit4->SetStatus(marineLib::Criterion_Status::PASS);
	}

	rows.push_back(std::move(crit4));

	/* calculate the max point of the GZ curve*/
	const auto maxPt = HydStatic_CmptLib::CalcMaxRightingArm(*rightArm);

	/*The maximum righting lever shall occur at an angle of heel not less than 25°*/
	const auto max_gz_heel = marineLib::Criterion_Value(maxPt.Heel());
	const auto max_gz_heel_expln = 
		marineLib::Criterion_Epln
		(
			"The maximum righting lever shall occur at an angle of heel not less than 25 deg"
		);

	const auto crit5 = std::make_shared<Marine_Criterion>(++nbCrit, "righting lever criterion no. 5");
	Debug_Null_Pointer(crit5);

	crit5->SetExpln(std::move(max_gz_heel_expln));
	crit5->SetValue(std::move(max_gz_heel));
	crit5->SetStandard(ISC08_RightLevCrit::PHI_25);

	if (max_gz_heel() < ISC08_RightLevCrit::PHI_25())
	{
		crit5->SetStatus(marineLib::Criterion_Status::FAIL);
	}
	else
	{
		crit5->SetStatus(marineLib::Criterion_Status::PASS);
	}

	rows.push_back(std::move(crit5));

	const auto& gm0_curve = Stablity()->GM0();
	if (NOT gm0_curve)
	{
		FatalErrorIn("void tnbLib::ISC08_RightLevCrit::Perform()")
			<< "no GM0 curve is loaded!" << endl
			<< abort(FatalError);
	}

	/*The initial meta centric height GM0 shall not be less than 0.15 m*/
	const auto gm0 = 
		marineLib::Criterion_Value
		(
			gm0_curve->GM0()
		);
	const auto gm0_expln = 
		marineLib::Criterion_Epln
		(
			"The initial meta centric height GM0 shall not be less than 0.15 m"
		);

	const auto crit6 = std::make_shared<Marine_Criterion>(++nbCrit, "righting lever criterion no. 6");
	Debug_Null_Pointer(crit6);

	crit6->SetExpln(std::move(gm0_expln));
	crit6->SetValue(std::move(gm0));
	crit6->SetStandard(ISC08_RightLevCrit::MIN_GM0);

	if (gm0() < ISC08_RightLevCrit::MIN_GM0())
	{
		crit6->SetStatus(marineLib::Criterion_Status::FAIL);
	}
	else
	{
		crit6->SetStatus(marineLib::Criterion_Status::PASS);
	}

	rows.push_back(std::move(crit6));

	Change_IsDone() = Standard_True;
}