#include <MarineRepairSect_AnalyzBody.hxx>

#include <MarineRepairSect_AnalyzSection.hxx>

Standard_Boolean 
tnbLib::MarineRepairSect_AnalyzBody::HasDefectSection() const
{
	for (const auto& x : Sections())
	{
		if (x->HasDefectSegment())
		{
			return Standard_True;
		}
	}
	return Standard_False;
}

Standard_Integer 
tnbLib::MarineRepairSect_AnalyzBody::CalcNbDefectSections() const
{
	Standard_Integer k = 0;
	for (const auto& x : Sections())
	{
		if (x->HasDefectSegment())
		{
			++k;
		}
	}
	return k;
}