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

std::vector<tnbLib::Entity3d_CmpConnect::Face> tnbLib::Entity3d_CmpConnect_ExtrudedPolygon::CalcFaces() const
{
	std::vector<Face> faces;
	const auto n = NbCmpts() / 2;
	for (Standard_Integer i = 0; i < n; i++)
	{
		const auto i0 = i;
		const auto i1 = (i + 1) % n;
		const auto i2 = i1 + n;
		const auto i3 = i0 + n;
		faces.emplace_back(Face{ {theCmpts_.at(i0), theCmpts_.at(i1), theCmpts_.at(i2), theCmpts_.at(i3)} });
	}
	{// the lower face
		std::vector<Standard_Integer> ids;
		for (Standard_Integer i = 0; i < n; i++)
		{
			ids.emplace_back(theCmpts_.at(i));
		}
		std::reverse(ids.begin(), ids.end());
		faces.emplace_back(Face{ std::move(ids) });
	}
	{// the upper face
		std::vector<Standard_Integer> ids;
		for (Standard_Integer i = 0; i < n; i++)
		{
			ids.emplace_back(theCmpts_.at(i + n));
		}
		faces.emplace_back(Face{ std::move(ids) });
	}
	return faces;
}

std::shared_ptr<tnbLib::Entity3d_CmpConnect> tnbLib::Entity3d_CmpConnect_ExtrudedPolygon::Copy() const
{
	return std::make_shared<Entity3d_CmpConnect_ExtrudedPolygon>(this->Array());
}
