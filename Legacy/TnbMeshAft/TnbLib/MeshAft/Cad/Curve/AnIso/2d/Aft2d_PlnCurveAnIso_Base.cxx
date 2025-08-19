#include <Aft2d_PlnCurveAnIso_Base.hxx>

#include <Mesh2d_CurveAnIso.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2d_Curve.hxx>

template<>
std::shared_ptr<tnbLib::Entity2d_Chain>
tnbLib::Mesh_PlnCurve_Base::Mesh<tnbLib::Geo2d_SizeFunction, tnbLib::Geo2d_MetricFunction>
(
	const Handle(Geom2d_Curve)& theCurve,
	const Standard_Real theU0,
	const Standard_Real theU1,
	const std::shared_ptr<Geo2d_MetricPrcsrAnIso>& theMap,
	const std::shared_ptr<Mesh_Curve_Info>& theInfo
	)
{
	Mesh2d_CurveAnIso alg(theCurve, theU0, theU1, theMap, theInfo);

	if (NOT alg.Geometry())
	{
		FatalErrorIn(FunctionSIG)
			<< "No curve has been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT alg.MetricMap())
	{
		FatalErrorIn(FunctionSIG)
			<< "No size map has been loaded!" << endl
			<< abort(FatalError);
	}

	alg.Perform();
	Debug_If_Condition_Message(NOT alg.IsDone(), "the algorithm has not been performed!");

	auto mesh = alg.Mesh();
	return std::move(mesh);
}