#include <Entity2d_CmpConnect_Polygon.hxx>

#include <Pnt3d.hxx>
#include <Pnt2d.hxx>

Standard_Boolean tnbLib::Entity2d_CmpConnect_Polygon::IsPolygon() const
{
	return Standard_True;
}

Standard_Integer tnbLib::Entity2d_CmpConnect_Polygon::NbCmpts() const
{
	return static_cast<Standard_Integer>(theCmpts_.size());
}

tnbLib::Entity2d_CmpConnect::ElmType tnbLib::Entity2d_CmpConnect_Polygon::ElementType() const
{
	return ElmType::polygon;
}

std::vector<Standard_Integer> tnbLib::Entity2d_CmpConnect_Polygon::Components() const
{
	return theCmpts_;
}

std::vector<tnbLib::Pnt2d> tnbLib::Entity2d_CmpConnect_Polygon::RetrievePolygon(const std::vector<Pnt2d>& theCoords) const
{
	std::vector<Pnt2d> coords;
	coords.reserve(NbCmpts());
	for (const auto i : theCmpts_)
	{
		coords.emplace_back(theCoords.at(Index_Of(i)));
	}
	return std::move(coords);
}

std::vector<tnbLib::Pnt3d> tnbLib::Entity2d_CmpConnect_Polygon::RetrievePolygon(const std::vector<Pnt3d>& theCoords) const
{
	std::vector<Pnt3d> coords;
	coords.reserve(NbCmpts());
	for (const auto i : theCmpts_)
	{
		coords.emplace_back(theCoords.at(Index_Of(i)));
	}
	return std::move(coords);
}

std::shared_ptr<tnbLib::Entity2d_CmpConnect> tnbLib::Entity2d_CmpConnect_Polygon::Copy() const
{
	return std::make_shared<Entity2d_CmpConnect_Polygon>(Components());
}
