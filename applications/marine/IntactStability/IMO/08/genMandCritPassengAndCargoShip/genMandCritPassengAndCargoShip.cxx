#include <HydStatic_rArmCurve_Eff.hxx>

#include <MarineBase_Tools.hxx>
#include <Marine_System.hxx>
#include <HydStatic_CmptLib.hxx>
#include <HydStatic_rArmCurve_Eff.hxx>
#include <HydStatic_hArmCurve.hxx>
#include <HydStatic_GzQP2.hxx>
#include <HydStatic_UniformSpacing.hxx>
#include <ISC08_Model.hxx>
#include <ISC08_CmptLib.hxx>
#include <ISC08_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static isc08Lib::P windPress(504.0);
	static isc08Lib::g gravity(9.806);
	static isc08Lib::BilgeBarCondition bilgeCond;
	static isc08Lib::FloodAngle floodAngle(40.0);

	static const unsigned int DEFAULT_NB_SECTIONS = 30;

	static std::shared_ptr<ISC08_Model> myModel;


	static isc08Lib::T rollPeriod;
	static isc08Lib::Lw lw1;
	static isc08Lib::Lw lw2;
	static isc08Lib::Phi phi0;
	static isc08Lib::Phi phi1;
	static isc08Lib::Phi phi2;

	static std::shared_ptr<HydStatic_hArmCurve> lw1Curve;
	static std::shared_ptr<HydStatic_hArmCurve> lw2Curve;

	enum class HeelSide
	{
		PORT,
		STARBOARD
	};

	static HeelSide heelSide;

	void checkModel()
	{
		if (NOT myModel)
		{
			FatalErrorIn(FunctionSIG)
				<< "no model has been loaded, yet!" << endl
				<< abort(FatalError);
		}
	}

	isc08Lib::Lw calcLw1(const std::shared_ptr<ISC08_Model>& model)
	{
		const auto& properties = model->Properties();
		const auto& params = model->VesselParameters();

		const auto& area = properties.LateralArea();
		const auto& z = properties.VerticalDistance();
		const auto& displm = params.Displacement();

		auto lw = ISC08_CmptLib::CalcWindHeelingLever(windPress, area, z, gravity, displm);
		return std::move(lw);
	}

	isc08Lib::Lw calcLw2(const isc08Lib::Lw& lw)
	{
		isc08Lib::Lw lw_2(1.5*lw());
		return std::move(lw_2);
	}

	isc08Lib::T calcRollingPeriod(const std::shared_ptr<ISC08_Model>& model)
	{
		//const auto& properties = myModel->Properties();
		const auto& params = myModel->VesselParameters();

		const auto& b = params.B();
		const auto& tm = params.TM();
		const auto& lwl = params.LWL();
		const auto& gm = params.GM();

		auto t = ISC08_CmptLib::CalcRollingPeriod(b, tm, lwl, gm);
		return std::move(t);
	}

	isc08Lib::Phi calcPhi1(const std::shared_ptr<ISC08_Model>& model, const isc08Lib::T& roll, const isc08Lib::BilgeBarCondition cond)
	{
		const auto& properties = model->Properties();
		const auto& params = model->VesselParameters();

		const auto& b = params.B();
		const auto& tm = params.TM();
		const auto& cb = params.CB();
		const auto& lwl = params.LWL();
		const auto& kg = params.KG();
		
		const auto& ak = properties.Ak();
		
		auto phi = ISC08_CmptLib::CalcAngleOfRoll(b, tm, cb, lwl, kg, ak, roll, cond);
		return std::move(phi);
	}

	isc08Lib::Phi calcPhi
	(
		const std::shared_ptr<HydStatic_hArmCurve>& hArm,
		const std::shared_ptr<HydStatic_rArmCurve>& rArm
	)
	{
		auto Qs = HydStatic_CmptLib::CalcStaticalStabilityPoints(*rArm, *hArm);
		if (Qs.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "found no static angle of heel" << endl
				<< abort(FatalError);
		}
		for (const auto& x : Qs)
		{
			if (x.Heel() >= 0.0)
			{
				isc08Lib::Phi phi(x.Heel());
				return std::move(phi);
			}
		}
		FatalErrorIn(FunctionSIG)
			<< "found no static angle of heel" << endl
			<< abort(FatalError);
		isc08Lib::Phi phi(0);
		return std::move(phi);
	}

	bool checkCriteria(const unsigned int nbSections)
	{
		checkModel();

		const auto& gzEff = myModel->GZeff();
		if (NOT gzEff)
		{
			FatalErrorIn(FunctionSIG)
				<< "no GZ curve has been found" << endl
				<< abort(FatalError);
		}

		lw1 = calcLw1(myModel);
		lw2 = calcLw2(lw1);
		lw1Curve = ISC08_Tools::HeelingArm(lw1, gzEff);
		lw2Curve = ISC08_Tools::HeelingArm(lw2, gzEff);

		rollPeriod = calcRollingPeriod(myModel);

		phi0 = calcPhi(lw1Curve, gzEff);
		phi1 = calcPhi1(myModel, rollPeriod, bilgeCond);

		const auto heel0 = phi0() - phi1();

		phi2 = calcPhi(lw2Curve, gzEff);
		const auto heel1 = phi2();

		auto heel2 = (Standard_Real)50.0;
		if (floodAngle() < heel2)
			heel2 = floodAngle();

		auto spacing = std::make_shared<HydStatic_UniformSpacing>(std::max(nbSections, DEFAULT_NB_SECTIONS));
		Debug_Null_Pointer(spacing);

		spacing->SetLower(heel0);
		spacing->SetUpper(heel1);

		auto areaQ0 = HydStatic_CmptLib::CalcAreaBetween(lw2Curve, gzEff, spacing);
		auto area0 = MarineBase_Tools::CalcArea(areaQ0, sysLib::gl_marine_integration_info);

		auto areaQ1 = HydStatic_CmptLib::CalcAreaBetween(lw2Curve, gzEff, spacing);
		auto area1 = MarineBase_Tools::CalcArea(areaQ1, sysLib::gl_marine_integration_info);

		return area0 < area1;
	}
}