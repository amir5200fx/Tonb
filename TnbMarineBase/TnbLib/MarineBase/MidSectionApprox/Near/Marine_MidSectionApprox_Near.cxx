#include <Marine_MidSectionApprox_Near.hxx>

#include <Marine_Body_Displacer.hxx>
#include <Marine_CmpSection.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::marineLib::MidSectionApprox_Near::Perform(const Standard_Real xSect)
{
	if (NOT Body())
	{
		FatalErrorIn(FunctionSIG)
			<< "no body is loaded!" << endl
			<< abort(FatalError);
	}

	const auto& sections = Body()->Sections();
	if (sections.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "no section is found" << endl
			<< abort(FatalError);
	}

	std::shared_ptr<Marine_CmpSection> sect;
	Standard_Real xmin = RealLast();
	for (const auto& x : sections)
	{
		if (ABS(x->X() - xSect) < xmin)
		{
			sect = x;
			xmin = ABS(x->X() - xSect);
		}
	}

	SectionRef() = std::move(sect);
	Change_IsDone() = Standard_True;
}