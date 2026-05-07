#include <Geo3d_ApprxSurfPatch_3PtsSamples.hxx>

#include <Entity2d_Triangle.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const Standard_Real tnbLib::Geo3d_ApprxSurfPatch_3PtsSamples::twoPerThree = 2.0 / 3.0;
const Standard_Real tnbLib::Geo3d_ApprxSurfPatch_3PtsSamples::onePerSix = 1.0 / 6.0;

const Standard_Integer tnbLib::Geo3d_ApprxSurfPatch_3PtsSamples::nbPts = 3;

tnbLib::Pnt2d 
tnbLib::Geo3d_ApprxSurfPatch_3PtsSamples::CalcPoint
(
	const Standard_Integer theIndex,
	const Entity_Triangle<const Pnt2d&>& theTriangle
) const
{
	Debug_If_Condition_Message(NOT INSIDE(theIndex, 0, nbPts - 1), "out of range");

	const auto N1 = twoPerThree;
	const auto N2 = onePerSix;
	const auto N3 = onePerSix;

	const auto id0 = theIndex;
	const auto id1 = (theIndex + 1) % 3;
	const auto id2 = (id1 + 1) % 3;

	const auto[x1, y1] = theTriangle.Vertex(id0).Components();
	const auto[x2, y2] = theTriangle.Vertex(id1).Components();
	const auto[x3, y3] = theTriangle.Vertex(id2).Components();

	const auto x = N1 * x1 + N2 * x2 + N3 * x3;
	const auto y = N1 * y1 + N2 * y2 + N3 * y3;
	Pnt2d pt(x, y);
	return std::move(pt);
}

std::vector<tnbLib::Pnt2d> 
tnbLib::Geo3d_ApprxSurfPatch_3PtsSamples::RetrieveSamples
(
	const Entity_Triangle<const Pnt2d &>& theTriangle
) const
{
	std::vector<Pnt2d> pts;
	pts.reserve(3);
	pts.push_back(CalcPoint(0, theTriangle));
	pts.push_back(CalcPoint(0, theTriangle));
	pts.push_back(CalcPoint(0, theTriangle));
	return std::move(pts);
}