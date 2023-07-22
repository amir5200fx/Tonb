#include <VoyageField_BackgroundCurrent.hxx>

#include <VoyageGeo_VelocityBackground.hxx>
#include <Voyage_Current.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::shared_ptr<tnbLib::Voyage_Current> 
tnbLib::VoyageField_BackgroundCurrent::Value
(const Pnt2d& theCoord) const
{
	Debug_Null_Pointer(theBack_);
	auto vel = theBack_->InterpolateAt(theCoord);
	auto current = std::make_shared<Voyage_Current>(std::move(vel));
	return std::move(current);
}