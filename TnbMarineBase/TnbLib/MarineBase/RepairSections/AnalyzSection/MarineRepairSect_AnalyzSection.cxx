#include <MarineRepairSect_AnalyzSection.hxx>

#include <MarineRepairSect_CmpSection.hxx>
#include <MarineRepairSect_Sections.hxx>
#include <MarineRepairSect_Segments.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Boolean 
tnbLib::MarineRepairSect_AnalyzSection::HasDefectSegment() const
{
	for (const auto& x : Segments())
	{
		Debug_Null_Pointer(x);
		if (NOT x->IsRing())
		{
			return Standard_True;
		}
	}
	return Standard_False;
}

Standard_Integer 
tnbLib::MarineRepairSect_AnalyzSection::CalcNbDefectSegments() const
{
	Standard_Integer k = 0;
	for (const auto& x : Segments())
	{
		Debug_Null_Pointer(x);
		if (NOT x->IsRing())
		{
			++k;
		}
	}
	return k;
}

std::shared_ptr<tnbLib::MarineRepairSect_CmpSection> 
tnbLib::MarineRepairSect_AnalyzSection::CalcCmpSection() const
{
	std::vector<std::shared_ptr<MarineRepairSect_Section>> sections;
	std::vector<std::shared_ptr<Cad2d_RemoveNonManifold::Segment>> nonRings;
	for (const auto& x : Segments())
	{
		if (x->IsRing())
		{
			auto sect = std::make_shared<MarineRepairSect_RingSection>(x);
			sections.push_back(std::move(sect));
		}
		else
		{
			nonRings.push_back(x);
		}
	}

	if (nonRings.size() IS_EQUAL 1)
	{
		auto segment = std::make_shared<MarineRepairSect_CrossSegment>(nonRings[0]);
		auto sect = std::make_shared<MarineRepairSect_OneEdgeMissSection>(std::move(segment));
		sections.push_back(std::move(sect));
	}
	else if (nonRings.size() IS_EQUAL 2)
	{
		auto segment0 = std::make_shared<MarineRepairSect_HoverSegment>(nonRings[0]);
		auto segment1 = std::make_shared<MarineRepairSect_HoverSegment>(nonRings[1]);
		auto sect = std::make_shared<MarineRepairSect_TwoEdgeMissSection>(std::move(segment0), std::move(segment1));
		sections.push_back(std::move(sect));
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "unidentified type of defect has been detected!" << endl
			<< " - unable to fix this type of errors!" << endl
			<< abort(FatalError);
	}

	auto cmpSect = std::make_shared<MarineRepairSect_CmpSection>(std::move(sections));
	return std::move(cmpSect);
}