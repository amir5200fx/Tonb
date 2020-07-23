#pragma once
//#include <Marine_SectionTypes.hxx>
#include <error.hxx>
#include <OSstream.hxx>
namespace tnbLib
{

	/*template<class SectionType>
	std::shared_ptr<Cad2d_Plane> MarineBase_Tools::ConvertToPlane
	(
		const Marine_OuterSection<SectionType>& theOuter
	)
	{
		const auto& inners = theOuter.Inners();

		std::vector<std::shared_ptr<Marine_Section>> sections;
		sections.reserve(inners.size());
		for (const auto& x : inners)
		{
			Debug_Null_Pointer(x.second);
			sections.push_back(x.second);
		}
		auto plane = ConvertToPlane(theOuter, sections);
		return std::move(plane);
	}*/
}