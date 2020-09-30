#include <Marine_Water.hxx>

#include <Marine_Section_Water.hxx>

tnbLib::Marine_Water::Marine_Water
(
	const std::vector<std::shared_ptr<marineLib::Section_Water>>& theSections
)
	: Marine_Entity(0, "water")
{
	auto& sections = theSections_;
	sections.reserve(theSections.size());

	for (const auto& x : theSections)
	{
		sections.push_back(x);
	}
}

tnbLib::Marine_Water::Marine_Water
(
	std::vector<std::shared_ptr<marineLib::Section_Water>>&& theSections
)
	: Marine_Entity(0, "water")
{
	auto& sections = theSections_;
	sections.reserve(theSections.size());

	for (const auto& x : theSections)
	{
		sections.push_back(std::move(x));
	}
	theSections.clear();
}

tnbLib::Marine_Water::Marine_Water
(
	const Standard_Integer theIndex, 
	const word & theName,
	const std::vector<std::shared_ptr<marineLib::Section_Water>>& theSections
)
	: Marine_Entity(theIndex, theName)
{
	auto& sections = theSections_;
	sections.reserve(theSections.size());

	for (const auto& x : theSections)
	{
		sections.push_back(x);
	}
}

tnbLib::Marine_Water::Marine_Water
(
	const Standard_Integer theIndex, 
	const word & theName, 
	std::vector<std::shared_ptr<marineLib::Section_Water>>&& theSections
)
	: Marine_Entity(theIndex, theName)
{
	auto& sections = theSections_;
	sections.reserve(theSections.size());

	for (const auto& x : theSections)
	{
		sections.push_back(std::move(x));
	}
	theSections.clear();
}