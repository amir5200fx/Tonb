#include <Entity3d_PolyhedralMesh.hxx>

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
