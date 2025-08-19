#include <Voyage_Profile.hxx>

#include <Geo_InterplFunction.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::Voyage_Profile::Voyage_Profile(const std::shared_ptr<Geo_InterplFunction>& theFun)
	: theFunc_(theFun)
{
	const auto samples = theFun->RetrieveSamples();
	theX0_ = FirstItem(samples).first;
	theX1_ = LastItem(samples).first;
}

tnbLib::Voyage_Profile::Voyage_Profile(std::shared_ptr<Geo_InterplFunction>&& theFun)
	: theFunc_(std::move(theFun))
{
	const auto samples = theFunc_->RetrieveSamples();
	theX0_ = FirstItem(samples).first;
	theX1_ = LastItem(samples).first;
}

Standard_Real tnbLib::Voyage_Profile::X0() const
{
	return theX0_;
}

Standard_Real tnbLib::Voyage_Profile::X1() const
{
	return theX1_;
}

Standard_Real tnbLib::Voyage_Profile::Value(const Standard_Real x) const
{
	return theFunc_->Value(x);
}

