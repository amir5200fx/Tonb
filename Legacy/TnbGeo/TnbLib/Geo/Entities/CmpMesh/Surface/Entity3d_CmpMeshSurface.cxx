#include <Entity3d_CmpMeshSurface.hxx>

#include <Geo_BoxTools.hxx>
#include <Entity2d_CmpConnect.hxx>

Standard_Integer
tnbLib::Entity3d_CmpMeshSurface::NbPoints() const
{
	return static_cast<Standard_Integer>(theCoords_.size());
}

Standard_Integer
tnbLib::Entity3d_CmpMeshSurface::NbElements() const
{
	return static_cast<Standard_Integer>(theIndices_.size());
}

std::vector<tnbLib::Pnt3d> tnbLib::Entity3d_CmpMeshSurface::GetElement(const Standard_Integer theIndex) const
{
	const auto& elm = theIndices_.at(theIndex);
	auto poly = elm->RetrievePolygon(Coords());
	return std::move(poly);
}

std::shared_ptr<tnbLib::Entity3d_Box>
tnbLib::Entity3d_CmpMeshSurface::CalcBoundingBox() const
{
	auto b = Geo_BoxTools::GetBox(Coords(), 0);
	auto t = std::make_shared<Entity3d_Box>(std::move(b));
	return std::move(t);
}

std::shared_ptr<tnbLib::Entity3d_CmpMeshSurface>
tnbLib::Entity3d_CmpMeshSurface::Copy() const
{
	auto coords = Coords();
	std::vector<std::shared_ptr<Entity2d_CmpConnect>> ids;
	ids.reserve(NbElements());
	for (const auto& x : this->Indices())
	{
		auto copy = x->Copy();
		ids.emplace_back(std::move(copy));
	}
	auto mesh = std::make_shared<Entity3d_CmpMeshSurface>(std::move(coords), std::move(ids));
	return std::move(mesh);
}

//#include <Entity2d_CmpMesh.cxx>
//
//void tnbLib::Entity3d_CmpMeshSurface::Add(const Entity3d_CmpMeshSurface& theMesh)
//{
//	for (const auto& x : theMesh.Coords())
//	{
//		theCoords_.emplace_back(x);
//	}
//	theIndices_ =
//		CombineConnectivities(this->Indices(), theMesh.Indices());
//}