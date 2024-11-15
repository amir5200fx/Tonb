#include <Entity2d_CmpConnect_Triangle.hxx>

#include <Pnt3d.hxx>
#include <Pnt2d.hxx>

tnbLib::Entity2d_CmpConnect_Triangle::Entity2d_CmpConnect_Triangle(const connectivity::triple& theTri)
{
	theCmpts_ = { theTri.Value(0), theTri.Value(1), theTri.Value(2) };
}

Standard_Boolean tnbLib::Entity2d_CmpConnect_Triangle::IsTriangle() const
{
	return Standard_True;
}

Standard_Integer tnbLib::Entity2d_CmpConnect_Triangle::NbCmpts() const
{
	return static_cast<Standard_Integer>(nbCmpts);
}

tnbLib::Entity2d_CmpConnect::ElmType
tnbLib::Entity2d_CmpConnect_Triangle::ElementType() const
{
	return ElmType::triangle;
}

std::vector<Standard_Integer>
tnbLib::Entity2d_CmpConnect_Triangle::Components() const
{
	std::vector<Standard_Integer> indices;
	std::copy(theCmpts_.begin(), theCmpts_.end(), std::back_inserter(indices));
	return std::move(indices);
}

std::vector<tnbLib::Pnt3d>
tnbLib::Entity2d_CmpConnect_Triangle::RetrievePolygon(const std::vector<Pnt3d>& theCoords) const
{
	std::vector<Pnt3d> coords;
	coords.reserve(nbCmpts);
	for (const auto i : theCmpts_)
	{
		coords.emplace_back(theCoords.at(Index_Of(i)));
	}
	return std::move(coords);
}

std::vector<tnbLib::Pnt2d>
tnbLib::Entity2d_CmpConnect_Triangle::RetrievePolygon
(
	const std::vector<Pnt2d>& theCoords
) const
{
	std::vector<Pnt2d> coords;
	coords.reserve(nbCmpts);
	for (const auto i : theCmpts_)
	{
		coords.emplace_back(theCoords.at(Index_Of(i)));
	}
	return std::move(coords);
}

std::shared_ptr<tnbLib::Entity2d_CmpConnect>
tnbLib::Entity2d_CmpConnect_Triangle::Copy() const
{
	auto t = std::make_shared<Entity2d_CmpConnect_Triangle>(this->Array());
	return std::move(t);
}

void tnbLib::Entity2d_CmpConnect_Triangle::Update(const std::vector<Standard_Integer>& indices)
{
	for (auto& i : theCmpts_)
	{
		i = indices.at(i - 1);
	}
}

void tnbLib::Entity2d_CmpConnect_Triangle::Update(const std::map<Standard_Integer, Standard_Integer>& indices)
{
	for (auto& i: theCmpts_)
	{
		i = indices.at(i);
	}
}
