#pragma once
#include <Pln_Curve.hxx>
#include <Pln_Wire.hxx>
#include <Marine_Section_Constructor.hxx>
namespace tnbLib
{

	template<class SectionType>
	std::vector<std::shared_ptr<Marine_Section>> 
		Marine_SectTools::RetrieveInners
		(
			const marineLib::OuterSection<SectionType>& outer
		)
	{
		const auto& innersMap = outer.Inners();

		std::vector<std::shared_ptr<Marine_Section>> inners;
		inners.reserve(innersMap.size());

		for (const auto& x : innersMap)
		{
			Debug_Null_Pointer(x.second);
			inners.push_back(x.second);
		}
		return std::move(inners);
	}

	template<class SectionType>
	std::shared_ptr<Marine_Section> 
		Marine_SectTools::CreateSection<SectionType>::_
		(
			const std::shared_ptr<Pln_Wire>& theOuter, 
			const std::shared_ptr<std::vector<std::shared_ptr<Pln_Wire>>>& theInners
		)
	{
		auto sect = std::make_shared<marineLib::OuterSection<SectionType>>(theOuter->Index(), theOuter);
		Debug_Null_Pointer(sect);

		if (theInners)
		{
			for (const auto& x : *theInners)
			{
				Debug_Null_Pointer(x);

				auto inner = std::make_shared<marineLib::InnerSection<SectionType>>(x->Index(), x);
				Debug_Null_Pointer(inner);

				sect->ImportToInners(inner->Index(), std::move(inner));
			}
		}

		return std::move(sect);
	}
}