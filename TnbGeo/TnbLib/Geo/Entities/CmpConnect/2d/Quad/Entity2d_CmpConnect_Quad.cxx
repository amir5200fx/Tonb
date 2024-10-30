#include <Entity2d_CmpConnect_Quad.hxx>

#include <Pnt3d.hxx>
#include <Pnt2d.hxx>

tnbLib::Entity2d_CmpConnect_Quad::Entity2d_CmpConnect_Quad(const connectivity::quadruple& theQaud)
	: theCmpts_({theQaud.Value(0), theQaud.Value(1), theQaud.Value(2), theQaud.Value(3)})
{
	// empty body
}

Standard_Boolean tnbLib::Entity2d_CmpConnect_Quad::IsQuadrilateral() const
{
	return Standard_True;
}

Standard_Integer
tnbLib::Entity2d_CmpConnect_Quad::NbCmpts() const
{
	return nbCmpts;
}

tnbLib::Entity2d_CmpConnect::ElmType
tnbLib::Entity2d_CmpConnect_Quad::ElementType() const
{
	return ElmType::quadrilateral;
}

std::vector<Standard_Integer>
tnbLib::Entity2d_CmpConnect_Quad::Components() const
{
	std::vector<Standard_Integer> indices;
	std::copy(theCmpts_.begin(), theCmpts_.end(), std::back_inserter(indices));
	return std::move(indices);
}

std::vector<tnbLib::Pnt3d>
tnbLib::Entity2d_CmpConnect_Quad::RetrievePolygon(const std::vector<Pnt3d>& theCoords) const
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
tnbLib::Entity2d_CmpConnect_Quad::RetrievePolygon
(
	const std::vector<Pnt2d>& theCoords
) const
{
	std::vector<Pnt2d> coords;
	coords.reserve(nbCmpts);
	for (const auto i:theCmpts_)
	{
		coords.emplace_back(theCoords.at(Index_Of(i)));
	}
	return std::move(coords);
}

std::shared_ptr<tnbLib::Entity2d_CmpConnect>
tnbLib::Entity2d_CmpConnect_Quad::Copy() const
{
	auto t = std::make_shared<Entity2d_CmpConnect_Quad>(this->Array());
	return std::move(t);
}

void tnbLib::Entity2d_CmpConnect_Quad::Update(const std::vector<Standard_Integer>& indices)
{
	for (int i = 0; i < nbCmpts; i++)
	{
		theCmpts_.at(i) = indices.at(theCmpts_.at(i) - 1);
	}
}
