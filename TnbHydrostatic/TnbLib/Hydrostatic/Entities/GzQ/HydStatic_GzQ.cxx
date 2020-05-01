#include <HydStatic_GzQ.hxx>

tnbLib::Pnt2d 
tnbLib::HydStatic_GzQ::GetPt() const
{
	const auto pt = Pnt2d(Heel(), LeverArm());
	return std::move(pt);
}

std::shared_ptr<tnbLib::HydStatic_GzQ>
tnbLib::HydStatic_GzQ::Mirrored
(
	const Pnt2d & theO
) const
{
	const auto pt = GetPt();
	const auto mPt = pt.Mirrored(theO);
	const auto q = std::make_shared<HydStatic_GzQ>(mPt.X(), mPt.Y());
	return std::move(q);
}

std::shared_ptr<tnbLib::HydStatic_GzQ>
tnbLib::HydStatic_GzQ::Mirrored
(
	const gp_Ax2d & theAx
) const
{
	const auto pt = GetPt();
	const auto mPt = pt.Mirrored(theAx);
	const auto q = std::make_shared<HydStatic_GzQ>(mPt.X(), mPt.Y());
	return std::move(q);
}