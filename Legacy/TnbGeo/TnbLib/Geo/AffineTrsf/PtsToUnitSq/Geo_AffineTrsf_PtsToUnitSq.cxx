#include <Geo_AffineTrsf_PtsToUnitSq.hxx>

#include <Geo_BoxTools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::Pnt2d 
tnbLib::geoLib::AffineTrsf_PtsToUnitSqObj::CalcTrsfPoint(const Pnt2d & theQ) const
{
	auto x = theQ;
	x.X() -= theXmin_;
	x.X() *= (1.0 / theDx_);

	x.Y() -= theYmin_;
	x.Y() *= (1.0 / theDy_);
	return std::move(x);
}

tnbLib::Pnt2d 
tnbLib::geoLib::AffineTrsf_PtsToUnitSqObj::CalcInvTrsfPoint(const Pnt2d & theQ) const
{
	auto x = theQ;

	x.X() *= theDx_;
	x.X() += theXmin_;

	x.Y() *= theDy_;
	x.Y() += theYmin_;
	return std::move(x);
}

Standard_Real 
tnbLib::geoLib::AffineTrsf_PtsToUnitSqObj::CalcTrsfX(const Standard_Real theX) const
{
	auto x = theX;
	x -= theXmin_;
	x *= (1.0 / theDx_);
	return x;
}

Standard_Real
tnbLib::geoLib::AffineTrsf_PtsToUnitSqObj::CalcTrsfY(const Standard_Real theX) const
{
	auto x = theX;
	x -= theYmin_;
	x *= (1.0 / theDy_);
	return x;
}

Standard_Real 
tnbLib::geoLib::AffineTrsf_PtsToUnitSqObj::CalcInvX(const Standard_Real theX) const
{
	auto x = theX;
	x *= theDx_;
	x += theXmin_;
	return x;
}

Standard_Real
tnbLib::geoLib::AffineTrsf_PtsToUnitSqObj::CalcInvY(const Standard_Real theX) const
{
	auto x = theX;
	x *= theDy_;
	x += theYmin_;
	return x;
}

const tnbLib::geoLib::AffineTrsf_PtsToUnitSqObj & 
tnbLib::geoLib::AffineTrsf_PtsToUnitSq::TrsfObj() const
{
	if (NOT IsDone())
	{
		FatalErrorIn(FunctionSIG)
			<< "the algorithm is not performed!" << endl
			<< abort(FatalError);
	}
	return theObj_;
}

void tnbLib::geoLib::AffineTrsf_PtsToUnitSq::Perform()
{
	auto b = Geo_BoxTools::GetBox(thePts_, 0);

	theObj_.theXmin_ = b.P0().X();
	theObj_.theXmax_ = b.P1().X();
	theObj_.theYmin_ = b.P0().Y();
	theObj_.theYmax_ = b.P1().Y();

	b.Length(theObj_.theDx_, theObj_.theDy_);

	if (theObj_.theDx_ <= 1.0E-6)
	{
		theObj_.theDx_ = 1.0;
	}

	if (theObj_.theDy_ <= 1.0E-6)
	{
		theObj_.theDy_ = 1.0;
	}

	Change_IsDone() = Standard_True;
}

std::vector<tnbLib::Pnt2d> 
tnbLib::geoLib::AffineTrsf_PtsToUnitSq::CalcTrsfPoints(const std::vector<Pnt2d>& theQs) const
{
	if (NOT IsDone())
	{
		FatalErrorIn(FunctionSIG)
			<< "the algorithm is not performed!" << endl
			<< abort(FatalError);
	}
	std::vector<Pnt2d> Qs;
	Qs.reserve(theQs.size());
	for (const auto& x : theQs)
	{
		auto pt = theObj_.CalcTrsfPoint(x);
		Qs.push_back(std::move(pt));
	}
	return std::move(Qs);
}