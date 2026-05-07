#include <HydStatic_CrsCurvesGraph.hxx>

#include <HydStatic_CrsCurve.hxx>

#include <Standard_Real.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <Geom2d_Curve.hxx>

namespace tnbLib
{

	hydStcLib::CurveMakerType GetType(const std::vector<std::shared_ptr<HydStatic_CrsCurve>>& theCurves)
	{
		Debug_If_Condition(theCurves.empty());
		const auto t = hydStcLib::RetrieveType(theCurves[0]);
#ifdef _DEBUG
		for (const auto& x : theCurves)
		{
			if (hydStcLib::RetrieveType(x) NOT_EQUAL t)
			{
				FatalErrorIn(FunctionSIG)
					<< "the type of the curves must be the same" << endl
					<< abort(FatalError);
			}
		}
#endif // _DEBUG
		return t;
	}
}

void tnbLib::HydStatic_CrsCurvesGraph::SetMinDispv(const Standard_Real x)
{
	theMinDispv_ = x;
}

void tnbLib::HydStatic_CrsCurvesGraph::SetMaxDispv(const Standard_Real x)
{
	theMaxDispv_ = x;
}

void tnbLib::HydStatic_CrsCurvesGraph::CheckIsDone() const
{
	if (NOT IsDone())
	{
		FatalErrorIn(FunctionSIG)
			<< "the algorithm is not performed!" << endl
			<< abort(FatalError);
	}
}

Standard_Boolean 
tnbLib::HydStatic_CrsCurvesGraph::IsInside(const Standard_Real x) const
{
	CheckIsDone();
	return (Standard_Boolean)INSIDE(x, theMaxDispv_, theMaxDispv_);
}

Standard_Real
tnbLib::HydStatic_CrsCurvesGraph::MinDispv() const
{
	CheckIsDone();
	return theMinDispv_;
}

Standard_Real
tnbLib::HydStatic_CrsCurvesGraph::MaxDispv() const
{
	CheckIsDone();
	return theMaxDispv_;
}

void tnbLib::HydStatic_CrsCurvesGraph::CheckVolume(const Standard_Real x) const
{
	CheckIsDone();

	if (NOT IsInside(x))
	{
		FatalErrorIn(FunctionSIG)
			<< " the volume exceeds the span of the graph!" << endl
			<< " - volume: " << x << endl
			<< " - lower: " << theMinDispv_ << endl
			<< " - upper: " << theMaxDispv_ << endl
			<< abort(FatalError);
	}
}