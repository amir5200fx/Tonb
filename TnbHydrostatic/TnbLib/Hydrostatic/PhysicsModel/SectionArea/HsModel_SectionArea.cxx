#include <HsModel_SectionArea.hxx>

#include <error.hxx>
#include <OSstream.hxx>

tnbLib::HsModel_SectionArea::HsModel_SectionArea()
{
}

void tnbLib::HsModel_SectionArea::Perform()
{
	if (NOT Body())
	{
		FatalErrorIn("void HsModel_SectionArea::Perform()")
			<< "the model is not loaded!" << endl
			<< abort(FatalError);
	}


}