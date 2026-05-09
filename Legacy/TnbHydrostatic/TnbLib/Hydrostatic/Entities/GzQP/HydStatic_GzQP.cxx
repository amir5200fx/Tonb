#include <HydStatic_GzQP.hxx>

std::shared_ptr<tnbLib::HydStatic_GzQ> 
tnbLib::HydStatic_GzQP::Mirrored(const Pnt2d & theO) const
{
	const auto pt = GetPt();
	const auto mPt = pt.Mirrored(theO);
	const auto q = std::make_shared<HydStatic_GzQP>(mPt.X(), mPt.Y(), Parameter());
	return std::move(q);
}

std::shared_ptr<tnbLib::HydStatic_GzQ> 
tnbLib::HydStatic_GzQP::Mirrored(const gp_Ax2d & theAx) const
{
	const auto pt = GetPt();
	const auto mPt = pt.Mirrored(theAx);
	const auto q = std::make_shared<HydStatic_GzQP>(mPt.X(), mPt.Y(), Parameter());
	return std::move(q);
}