#include <Marine_RepairSections.hxx>

#include <MarineRepairSect_AnalyzBody.hxx>
#include <MarineRepairSect_AnalyzSection.hxx>
#include <MarineRepairSect_CrossSegment.hxx>
#include <MarineRepairSect_HoverSegment.hxx>
#include <MarineRepairSect_OneEdgeMissSection.hxx>
#include <MarineRepairSect_TwoEdgeMissSection.hxx>
#include <MarineRepairSect_CmpSection.hxx>
#include <MarineRepairSect_FixedSection.hxx>
#include <MarineRepairSect_FixedBody.hxx>
#include <Pln_Edge.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::Marine_RepairSections::Perform()
{
	if (NOT Body())
	{
		FatalErrorIn(FunctionSIG)
			<< "no body has been loaded!" << endl
			<< abort(FatalError);
	}

	const auto& sections = Body()->Sections();

	std::vector<std::shared_ptr<MarineRepairSect_FixedSection>> fixedSections;
	fixedSections.reserve(sections.size());

	for (const auto& x : sections)
	{
		Debug_Null_Pointer(x);

		auto cmpSect = x->CalcCmpSection();
		Debug_Null_Pointer(cmpSect);

		auto curves = cmpSect->FillingCurves();

		auto fixedSection = std::make_shared<MarineRepairSect_FixedSection>(std::move(curves));
		Debug_Null_Pointer(fixedSection);

		fixedSections.push_back(std::move(fixedSection));
	}

	auto body = std::make_shared<MarineRepairSect_FixedBody>(std::move(fixedSections));
	theFixed_ = std::move(body);

	Change_IsDone() = Standard_True;
}