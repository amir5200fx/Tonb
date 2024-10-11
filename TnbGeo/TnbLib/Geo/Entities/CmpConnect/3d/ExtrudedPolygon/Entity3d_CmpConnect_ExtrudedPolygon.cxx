#include <Entity3d_CmpConnect_ExtrudedPolygon.hxx>

#include <Pnt3d.hxx>

Standard_Boolean tnbLib::Entity3d_CmpConnect_ExtrudedPolygon::IsExtrudedPolygon() const
{
	return Standard_True;
}

Standard_Integer tnbLib::Entity3d_CmpConnect_ExtrudedPolygon::NbCmpts() const
{
	return static_cast<Standard_Integer>(theCmpts_.size());
}

tnbLib::Entity3d_CmpConnect::ElmType tnbLib::Entity3d_CmpConnect_ExtrudedPolygon::ElementType() const
{
	return ElmType::extruded_polygon;
}

std::vector<Standard_Integer> tnbLib::Entity3d_CmpConnect_ExtrudedPolygon::Components() const
{
	return theCmpts_;
}

std::vector<tnbLib::Pnt3d> tnbLib::Entity3d_CmpConnect_ExtrudedPolygon::RetrievePolygon(const std::vector<Pnt3d>& theCoords) const
{
	std::vector<Pnt3d> coords;
	coords.reserve(NbCmpts());
	for (const auto i : theCmpts_)
	{
		coords.emplace_back(theCoords.at(Index_Of(i)));
	}
	return coords;
}

std::shared_ptr<tnbLib::Entity3d_CmpConnect> tnbLib::Entity3d_CmpConnect_ExtrudedPolygon::Copy() const
{
	return std::make_shared<Entity3d_CmpConnect_ExtrudedPolygon>(this->Array());
}
