#include <VoyageFun_ProfiledCalmResist.hxx>

#include <Voyage_Profile.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::VoyageFun_ProfiledCalmResist::VoyageFun_ProfiledCalmResist() = default;

Standard_Real
tnbLib::VoyageFun_ProfiledCalmResist::Value(const Standard_Real theVel) const
{
	Debug_Null_Pointer(theProfile_);
	if (NOT INSIDE(theVel, theProfile_->X0(), theProfile_->X1()))
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "the velocity exceeds the range of the profile." << endl
			<< " - veloity: " << theVel << endl
			<< " - lower: " << theProfile_->X0() << endl
			<< " - upper: " << theProfile_->X1() << endl
			<< abort(FatalError);
	}
	return theProfile_->Value(theVel);
}
