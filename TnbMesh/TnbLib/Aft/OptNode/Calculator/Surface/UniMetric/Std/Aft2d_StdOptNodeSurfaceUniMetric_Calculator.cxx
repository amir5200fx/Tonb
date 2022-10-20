#include <Aft2d_StdOptNodeSurfaceUniMetric_Calculator.hxx>

#include <Aft2d_OptNodeSurface_Analytical.hxx>
#include <Aft2d_EdgeSurface.hxx>
#include <Aft2d_MetricPrcsrSurfaceUniMetric.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::Aft2d_StdOptNodeSurfaceUniMetric_Calculator::Perform()
{
#ifdef _DEBUG
	if (NOT Front())
	{
		FatalErrorIn(FunctionSIG)
			<< "no front entity has been found!" << endl
			<< abort(FatalError);
	}

	if (NOT MetricMap())
	{
		FatalErrorIn(FunctionSIG)
			<< "no metric map has been found!" << endl
			<< abort(FatalError);
	}

	if (NOT MetricMap()->MetricFunction())
	{
		FatalErrorIn(FunctionSIG)
			<< "no metric function has been found!" << endl
			<< abort(FatalError);
	}
#endif // _DEBUG

	if (Size() <= 0)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid element size has been detected" << endl
			<< abort(FatalError);
	}

	auto m = MetricMap()->CalcMetric(Front()->Centre());

	const auto& v0 = Front()->Node0()->Coord();
	const auto& v1 = Front()->Node1()->Coord();
	//const auto len = MetricMap()->CalcUnitDistance(v0, v1);

	Aft2d_OptNodeSurface_Analytical alg(Size(), 1.0, m, *Front());
	alg.Perform();
	Debug_If_Condition_Message(NOT alg.IsDone(), "the algorithm is not performed!");

	ChangeCoord() = alg.Coord();
	Change_IsDone() = Standard_True;
}