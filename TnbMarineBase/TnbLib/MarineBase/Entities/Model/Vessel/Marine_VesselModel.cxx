#include <Marine_VesselModel.hxx>

#include <Marine_CmpSection.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <algorithm>

namespace tnbLib
{

	Standard_Boolean 
		compareX
		(
			const std::shared_ptr<Marine_CmpSection>& theSection0, 
			const std::shared_ptr<Marine_CmpSection>& theSection1
		)
	{
		Debug_Null_Pointer(theSection0);
		Debug_Null_Pointer(theSection1);

		return theSection0->CoordinateSystem().Location().X() 
			< theSection1->CoordinateSystem().Location().X();
	}
}

Standard_Integer 
tnbLib::Marine_VesselModel::NbSections() const
{
	return (Standard_Integer)theSections_.size();
}

std::vector<std::shared_ptr<tnbLib::Marine_CmpSection>> 
tnbLib::Marine_VesselModel::SortedSections() const
{
	const auto& sections = Sections();

	std::vector<std::shared_ptr<tnbLib::Marine_CmpSection>> sorted;
	sorted.reserve(NbSections());

	for (const auto& x : sections)
	{
		Debug_Null_Pointer(x.second);
		sorted.push_back(x.second);
	}

	std::sort(sorted.begin(), sorted.end(), compareX);

	return std::move(sorted);
}

void tnbLib::Marine_VesselModel::ImportSection
(
	const Standard_Integer theIndex, 
	const std::shared_ptr<Marine_CmpSection>& theSection
)
{
	auto insert = theSections_.insert(std::make_pair(theIndex, theSection));
	if (NOT insert.second)
	{
		FatalErrorIn("void tnbLib::Marine_VesselModel::ImportSection(Args...)")
			<< "duplicate data" << endl
			<< abort(FatalError);
	}
}

void tnbLib::Marine_VesselModel::RemoveSection
(
	const Standard_Integer theIndex
)
{
	theSections_.erase(theIndex);
}