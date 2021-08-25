#include <MarineRepairSect_CmpSection.hxx>

#include <MarineRepairSect_Section.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::vector<std::shared_ptr<tnbLib::Pln_Curve>> 
tnbLib::MarineRepairSect_CmpSection::FillingCurves() const
{
	std::vector<std::shared_ptr<Pln_Curve>> allCurves;
	for (const auto& x : Sections())
	{
		Debug_Null_Pointer(x);
		auto curves = x->FillingCurves();
		
		for (auto& c : curves)
		{
			allCurves.push_back(std::move(c));
		}
	}
	return std::move(allCurves);
}