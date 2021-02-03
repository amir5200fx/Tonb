#include <HydStatic_HydCurvesGraph.hxx>

#include <Standard_Real.hxx>
#include <HydStatic_HydGphCurve.hxx>

tnbLib::HydStatic_HydCurvesGraph::HydStatic_HydCurvesGraph
(
	const Standard_Integer theIndex, 
	const word & theName
)
	: HydStatic_Entity(theIndex, theName)
{
	//- empty body
}

namespace tnbLib
{

	Standard_Real CalcMinT(const std::vector<std::shared_ptr<HydStatic_HydGphCurve>>& theCurves)
	{
		Standard_Real maxVal = RealFirst();
		for (const auto& x : theCurves)
		{
			Debug_Null_Pointer(x);
			auto f = x->Draft0();
			if (f > maxVal)
			{
				maxVal = f;
			}
		}
		return maxVal;
	}

	Standard_Real CalcMaxT(const std::vector<std::shared_ptr<HydStatic_HydGphCurve>>& theCurves)
	{
		Standard_Real minVal = RealLast();
		for (const auto& x : theCurves)
		{
			Debug_Null_Pointer(x);
			auto f = x->Draft1();
			if (f < minVal)
			{
				minVal = f;
			}
		}
		return minVal;
	}
}

void tnbLib::HydStatic_HydCurvesGraph::Perform
(
	std::vector<std::shared_ptr<HydStatic_HydGphCurve>>&& theCurves
)
{
	if (theCurves.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "no curve has been loaded" << endl
			<< abort(FatalError);
	}
	theTmin_ = CalcMinT(theCurves);
	theTmax_ = CalcMaxT(theCurves);

	theCurves_ = std::move(theCurves);

	Change_IsDone() = Standard_True;
}