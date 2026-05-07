#include <Entity3d_PolyhedralMesh.hxx>

#include <Entity3d_CmpMesh.hxx>
#include <Entity3d_CmpConnect.hxx>

Standard_Integer tnbLib::Entity3d_PolyhedralMesh::Element::NbFaces() const
{
	return static_cast<Standard_Integer>(theFaces_.size());
}

Standard_Integer tnbLib::Entity3d_PolyhedralMesh::Element::NbNodes() const
{
	std::set<Standard_Integer> comp;
	for (const auto& f: theFaces_)
	{
		for (const auto i: f.Indices())
		{
			comp.insert(i);
		}
	}
	return static_cast<Standard_Integer>(comp.size());
}

std::vector<Standard_Integer> tnbLib::Entity3d_PolyhedralMesh::Element::NodeIds() const
{
	std::set<Standard_Integer> comp;
	for (const auto& f : theFaces_)
	{
		for (const auto i : f.Indices())
		{
			comp.insert(i);
		}
	}
	std::vector<Standard_Integer> ids;
	std::copy(comp.begin(), comp.end(), std::back_inserter(ids));
	return ids;
}

void tnbLib::Entity3d_PolyhedralMesh::Import(const Entity3d_CmpMesh& theCmpMesh)
{
	theCoords_ = theCmpMesh.Coords();
	std::vector<Element> elements;
	elements.reserve(theCmpMesh.Indices().size());
	for (const auto& elm: theCmpMesh.Indices())
	{
		std::vector<Face> faces;
		for (const auto& [ids]: elm->CalcFaces())
		{
			faces.emplace_back(ids);
		}
		elements.emplace_back(Element{ std::move(faces) });
	}
	theElements_ = std::move(elements);
}