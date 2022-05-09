#include <Aft2d_StdOptNodeSurface_Calculator.hxx>

#include <Aft2d_OptNodeSurface_Analytical.hxx>
#include <Aft2d_EdgeSurface.hxx>
#include <Aft2d_NodeSurface.hxx>
#include <Aft2d_MetricPrcsrSurface.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

//tnbLib::Pnt2d 
//tnbLib::Aft2d_StdOptNodeSurface_Calculator::CorrectCoord
//(
//	const Pnt2d & theCentre,
//	const Pnt2d & theCoord, 
//	const Entity2d_Box & theDomain
//)
//{
//	static const auto cte = (1.0 - EPS6);
//
//	const auto& p0 = theDomain.P0();
//	const auto& p1 = theDomain.P1();
//
//	const auto xmin = p0.X();
//	const auto xmax = p1.X();
//	const auto ymin = p0.Y();
//	const auto ymax = p1.Y();
//
//	const auto x0 = theCentre.X();
//	const auto y0 = theCentre.Y();
//
//	const auto du = theCoord - theCentre;
//	const auto dx = du.X();
//	const auto dy = du.Y();
//
//	const auto x = theCoord.X();
//	if (x > xmax)
//	{
//		const auto y = y0 + (dy / dx)*(xmax - x0);
//		const auto du1 = Pnt2d(xmax, y) - theCentre;
//
//		auto newPoint = theCentre + cte * du1;
//		return std::move(newPoint);
//	}
//
//	if (x < xmin)
//	{
//		const auto y = y0 + (dy / dx)*(xmin - x0);
//		const auto du1 = Pnt2d(xmin, y) - theCentre;
//
//		auto newPoint = theCentre + cte * du1;
//		return std::move(newPoint);
//	}
//
//	const auto y = theCoord.Y();
//	if (y > ymax)
//	{
//		const auto x = x0 + (dx / dy)*(ymax - y0);
//		const auto du1 = Pnt2d(x, ymax) - theCentre;
//
//		auto newPoint = theCentre + cte * du1;
//		return std::move(newPoint);
//	}
//
//	if (y < ymin)
//	{
//		const auto x = x0 + (dx / dy)*(ymin - y0);
//		const auto du1 = Pnt2d(x, ymin) - theCentre;
//
//		auto newPoint = theCentre + cte * du1;
//		return std::move(newPoint);
//	}
//
//	FatalErrorIn(FunctionSIG)
//		<< "unpredictable condition is occurred!" << endl
//		<< abort(FatalError);
//	return Pnt2d::null;
//}

void tnbLib::Aft2d_StdOptNodeSurface_Calculator::Perform()
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

	const auto m = MetricMap()->CalcMetric(Front()->Centre());

	const auto& v0 = Front()->Node0()->Coord();
	const auto& v1 = Front()->Node1()->Coord();
	const auto len = MetricMap()->CalcUnitDistance(v0, v1);
	Aft2d_OptNodeSurface_Analytical alg(Size(), len, m, *Front());
	alg.Perform();
	Debug_If_Condition_Message(NOT alg.IsDone(), "the algorithm is not performed!");

	ChangeCoord() = alg.Coord();
	Change_IsDone() = Standard_True;
}