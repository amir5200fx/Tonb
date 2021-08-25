#include <Marine_RepairSection.hxx>

#include <MarineRepairSect_Section.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::Marine_RepairSection::Perform()
{
	if (NOT Section())
	{
		FatalErrorIn(FunctionSIG)
			<< "no section has been loaded!" << endl
			<< abort(FatalError);
	}

	auto curves = Section()->FillingCurves();
	theCurves_ = std::move(curves);

	Change_IsDone() = Standard_True;
}