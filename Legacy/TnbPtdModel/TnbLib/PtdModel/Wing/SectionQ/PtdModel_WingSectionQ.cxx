#include <PtdModel_WingSectionQ.hxx>

tnbLib::PtdModel_WingSectionQ::UpperFace::UpperFace(std::vector<Pnt2d>&& pts)
{
	Points = std::move(pts);
}

tnbLib::PtdModel_WingSectionQ::LowerFace::LowerFace(std::vector<Pnt2d>&& pts)
{
	Points = std::move(pts);
}