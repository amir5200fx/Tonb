#include <StbGMaker_IntplSect_Closer.hxx>

#include <gp_Pln.hxx>
#include <Marine_CmpSection.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::stbGmakerLib::IntplSect_Closer::Perform(const gp_Pln & thePln)
{
	const auto& loc = thePln.Location();

	Debug_Null_Pointer(Sect0());
	Debug_Null_Pointer(Sect1());

	const auto dx0 = std::abs(loc.X() - Sect0()->X());
	const auto dx1 = std::abs(loc.X() - Sect1()->X());

	if (dx0 < dx1)
	{
		ChangeInterpolated() = Sect0();
	}
	else
	{
		ChangeInterpolated() = Sect1();
	}

	Change_IsDone() = Standard_True;
}