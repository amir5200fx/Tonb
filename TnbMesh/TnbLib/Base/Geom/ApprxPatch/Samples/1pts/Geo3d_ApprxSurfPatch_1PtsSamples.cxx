#include <Geo3d_ApprxSurfPatch_1PtsSamples.hxx>

#include <Entity2d_Triangle.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const Standard_Real tnbLib::Geo3d_ApprxSurfPatch_1PtsSamples::onePerThree = 1.0 / 3.0;
const Standard_Integer tnbLib::Geo3d_ApprxSurfPatch_1PtsSamples::nbPts = 1;

tnbLib::Pnt2d 
tnbLib::Geo3d_ApprxSurfPatch_1PtsSamples::CalcPoint
(
	const Standard_Integer theIndex, 
	const Entity_Triangle<const Pnt2d&>& theTriangle
) const
{
	Debug_If_Condition_Message(NOT INSIDE(theIndex, 0, nbPts - 1), "out of range");

	const auto N1 = onePerThree;
	const auto N2 = onePerThree;
	const auto N3 = one - N1 - N2;

	const auto[x1, y1] = theTriangle.P0().Components();
	const auto[x2, y2] = theTriangle.P1().Components();
	const auto[x3, y3] = theTriangle.P2().Components();

	const auto x = N1 * x1 + N2 * x2 + N3 * x3;
	const auto y = N1 * y1 + N2 * y2 + N3 * y3;
	Pnt2d pt(x, y);
	return std::move(pt);
}

std::vector<tnbLib::Pnt2d> 
tnbLib::Geo3d_ApprxSurfPatch_1PtsSamples::RetrieveSamples(const Entity_Triangle<const Pnt2d &>& theTriangle) const
{
	std::vector<Pnt2d> pts;
	pts.push_back(CalcPoint(0, theTriangle));
	return std::move(pts);
}