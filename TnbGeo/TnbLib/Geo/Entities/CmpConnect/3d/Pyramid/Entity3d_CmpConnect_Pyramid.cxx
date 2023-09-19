#include <Entity3d_CmpConnect_Pyramid.hxx>

#include <Pnt3d.hxx>

tnbLib::Entity3d_CmpConnect_Pyramid::Entity3d_CmpConnect_Pyramid(const connectivity::quintuple& theQuin)
	: theCmpts_
	({
		theQuin.Value(0),
		theQuin.Value(1),
		theQuin.Value(2),
		theQuin.Value(3),
		theQuin.Value(4)
		})
{}

Standard_Boolean tnbLib::Entity3d_CmpConnect_Pyramid::IsPyramid() const
{
	return Standard_True;
}

Standard_Integer tnbLib::Entity3d_CmpConnect_Pyramid::NbCmpts() const { return nbCmpts; }
tnbLib::Entity3d_CmpConnect::ElmType tnbLib::Entity3d_CmpConnect_Pyramid::ElementType() const { return ElmType::pyramid; }
std::vector<Standard_Integer>
tnbLib::Entity3d_CmpConnect_Pyramid::Components() const
{
	std::vector<Standard_Integer> indices;
	std::copy(theCmpts_.begin(), theCmpts_.end(), std::back_inserter(indices));
	return std::move(indices);
}

std::vector<tnbLib::Pnt3d>
tnbLib::Entity3d_CmpConnect_Pyramid::RetrievePolygon(const std::vector<Pnt3d>& theCoords) const
{
	std::vector<Pnt3d> coords;
	coords.reserve(nbCmpts);
	for (const auto i : theCmpts_)
	{
		coords.emplace_back(theCoords.at(Index_Of(i)));
	}
	return std::move(coords);
}

std::shared_ptr<tnbLib::Entity3d_CmpConnect>
tnbLib::Entity3d_CmpConnect_Pyramid::Copy() const
{
	auto t = std::make_shared<Entity3d_CmpConnect_Pyramid>(this->Array());
	return std::move(t);
}
