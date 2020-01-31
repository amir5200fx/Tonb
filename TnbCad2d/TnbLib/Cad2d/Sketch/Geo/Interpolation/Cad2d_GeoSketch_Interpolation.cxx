#include <Cad2d_GeoSketch_Interpolation.hxx>

#include <error.hxx>
#include <OSstream.hxx>

Standard_Boolean 
tnbLib::Cad2d_GeoSketch_Interpolation::HasPoint
(
	const Standard_Integer theIndex
) const
{
	auto iter = thePts_.find(theIndex);
	if (iter IS_EQUAL thePts_.end())
	{
		return Standard_False;
	}
	return Standard_True;
}

void tnbLib::Cad2d_GeoSketch_Interpolation::LoadPoint
(
	const Standard_Integer theIndex,
	const Pnt2d & thePt
)
{
	auto insert = thePts_.insert(std::make_pair(theIndex, thePt));
	if (NOT insert.second)
	{
		FatalErrorIn("void LoadPoint(const Standard_Integer theIndex, const Pnt2d& thePt)")
			<< "duplicate data!" << endl
			<< abort(FatalError);
	}
}

void tnbLib::Cad2d_GeoSketch_Interpolation::RemovePoint(const Standard_Integer theIndex)
{
	auto iter = thePts_.find(theIndex);
	if (iter IS_EQUAL thePts_.end())
	{
		FatalErrorIn("void RemovePoint(const Standard_Integer theIndex)")
			<< "the item is not in the map!" << endl
			<< abort(FatalError);
	}
	thePts_.erase(iter);
}

#include <Standard_Handle.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <Geom2dAPI_Interpolate.hxx>
#include <TColgp_HArray1OfPnt2d.hxx>

void tnbLib::Cad2d_GeoSketch_Interpolation::Perform
(
	const Standard_Real theTol
)
{
	if (Points().size() < 3)
	{
		FatalErrorIn("void Perform()")
			<< "Not enough offset points" << endl
			<< abort(FatalError);
	}

	Handle(TColgp_HArray1OfPnt2d) Q = new TColgp_HArray1OfPnt2d(1, thePts_.size());
	Standard_Integer K = 0;
	for (const auto& x : Points())
	{
		Q->SetValue(K + 1, x.second);

		++K;
	}

	Geom2dAPI_Interpolate interp(Q, Standard_False, theTol);
	interp.Perform();

	const auto& curve = interp.Curve();

	ChangeGeometry() =
		new Geom2d_TrimmedCurve
		(
			curve,
			curve->FirstParameter(),
			curve->LastParameter()
		);

	Change_IsDone() = Standard_True;
}

void tnbLib::Cad2d_GeoSketch_Interpolation::Perform
(
	const Standard_Real theTol, 
	const Vec2d & theFirst,
	const Vec2d & theLast,
	const Standard_Boolean Scale
)
{
	if (Points().size() < 3)
	{
		FatalErrorIn("void Perform()")
			<< "Not enough offset points" << endl
			<< abort(FatalError);
	}

	Handle(TColgp_HArray1OfPnt2d) Q = new TColgp_HArray1OfPnt2d(1, thePts_.size());
	Standard_Integer K = 0;
	for (const auto& x : Points())
	{
		Q->SetValue(K + 1, x.second);

		++K;
	}

	Geom2dAPI_Interpolate interp(Q, Standard_False, theTol);

	interp.Load(theFirst, theLast, Scale);
	interp.Perform();

	const auto& curve = interp.Curve();

	ChangeGeometry() =
		new Geom2d_TrimmedCurve
		(
			curve,
			curve->FirstParameter(),
			curve->LastParameter()
		);

	Change_IsDone() = Standard_True;
}