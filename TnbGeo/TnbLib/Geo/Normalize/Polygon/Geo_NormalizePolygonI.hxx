#pragma once
template<class Point>
inline void tnbLib::Geo_NormalizePolygon<Point>::Perform()
{
	if (NOT Polygon())
	{
		FatalErrorIn(FunctionSIG)
			<< "no polygon has been found." << endl
			<< abort(FatalError);
	}

	const auto& pts = Polygon()->Points();
	Geo_NormalizePts<Point> alg(pts);

	alg.Perform();
	Debug_If_Condition_Message(NOT alg.IsDone(), "the application is not performed.");

	auto poly = std::make_shared<Entity_Polygon<Point>>(alg.Normalized(), 0);
	NormalizedRef() = std::move(poly);

	Change_IsDone() = Standard_True;
}