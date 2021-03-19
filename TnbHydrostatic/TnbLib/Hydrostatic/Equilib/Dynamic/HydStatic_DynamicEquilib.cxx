#include <HydStatic_DynamicEquilib.hxx>

#include <HydStatic_hArmCurve.hxx>
#include <HydStatic_rArmCurve.hxx>
#include <HydStatic_hAuCurve.hxx>
#include <HydStatic_rAuCurve.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2dAPI_InterCurveCurve.hxx>

#include <algorithm>

void tnbLib::HydStatic_DynamicEquilib::Perform()
{
	if (NOT Gz())
	{
		FatalErrorIn(FunctionSIG)
			<< " no Gz curve has been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT HeelingArm())
	{
		FatalErrorIn(FunctionSIG)
			<< " no Heeling Arm has been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Gz()->HasAuCurve())
	{
		FatalErrorIn(FunctionSIG)
			<< " no Au curve has been detected for the Gz curve!" << endl
			<< abort(FatalError);
	}

	if (NOT HeelingArm()->HasAuCurve())
	{
		FatalErrorIn(FunctionSIG)
			<< " no Au curve has been detected for the heeling arm curve!" << endl
			<< abort(FatalError);
	}

	const auto& gz = Gz()->AuCurve();
	const auto& heeling = HeelingArm()->AuCurve();

	const auto& gzCurve = gz->Geometry();
	const auto& heelingCurve = heeling->Geometry();

	Debug_Null_Pointer(gzCurve);
	Debug_Null_Pointer(heelingCurve);

	Geom2dAPI_InterCurveCurve alg(gzCurve, heelingCurve);
	if (alg.NbPoints())
	{
		auto& Qs = ChangePoints();
		Qs.reserve(alg.NbPoints());

		for (Standard_Integer i = 1; i <= alg.NbPoints(); i++)
		{
			auto value = alg.Point(i);

			gzQ Q(value.X(), value.Y());
			Qs.push_back(std::move(Q));
		}

		std::sort(Qs.begin(), Qs.end(), [](const gzQ& q0, const gzQ& q1)-> auto {return q0.Heel() < q1.Heel(); });
	}
	Change_IsDone() = Standard_True;
}