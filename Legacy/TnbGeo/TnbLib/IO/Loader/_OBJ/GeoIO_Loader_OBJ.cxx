#include <GeoIO_Loader_OBJ.hxx>

#include <Entity3d_Triangulation.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include "OBJ_Loader.h"

Standard_Integer 
tnbLib::ioLib::Loader_OBJ::NbMeshes() const
{
	CheckDone((*this));
	return Standard_Integer(theMeshes_.size());
}

const std::shared_ptr<tnbLib::Entity3d_Triangulation>& 
tnbLib::ioLib::Loader_OBJ::Mesh(const Standard_Integer theIndex) const
{
	CheckDone((*this));
	Debug_Bad_Index(theIndex, 0, theMeshes_.size() - 1);
	return theMeshes_.at(theIndex);
}

const std::vector<std::shared_ptr<tnbLib::Entity3d_Triangulation>>& 
tnbLib::ioLib::Loader_OBJ::Meshes() const
{
	CheckDone((*this));
	return theMeshes_;
}

namespace tnbLib
{

	auto RetrieveCoords(const objl::Mesh& theMesh)
	{
		std::vector<Pnt3d> coords;
		coords.reserve(theMesh.Vertices.size());
		for (const auto& x : theMesh.Vertices)
		{
			const auto& Pos = x.Position;
			Pnt3d pt(Pos.X, Pos.Y, Pos.Z);
			coords.push_back(std::move(pt));
		}
		return std::move(coords);
	}

	auto RetrieveConnectivities(const objl::Mesh& theMesh)
	{
		std::vector<connectivity::triple> tris;
		tris.reserve(theMesh.Indices.size());
		const auto& indices = theMesh.Indices;
		for (int j = 0; j < indices.size(); j += 3)
		{
			auto v0 = indices.at(j);
			auto v1 = indices.at(j + 1);
			auto v2 = indices.at(j + 2);

			connectivity::triple t;
			t.Value(0) = v0 + 1;
			t.Value(1) = v1 + 1;
			t.Value(2) = v2 + 1;

			tris.push_back(std::move(t));
		}
		return std::move(tris);
	}
}

void tnbLib::ioLib::Loader_OBJ::Perform()
{
	objl::Loader loader;

	auto loaded = loader.LoadFile(FileName());

	std::vector<std::shared_ptr<Entity3d_Triangulation>> meshes;
	meshes.reserve(loader.LoadedMeshes.size());
	if (loaded)
	{
		auto mesh = std::make_shared<Entity3d_Triangulation>();
		for (const auto& x : loader.LoadedMeshes)
		{
			auto coords = RetrieveCoords(x);
			auto indices = RetrieveConnectivities(x);

			mesh->Points() = std::move(coords);
			mesh->Connectivity() = std::move(indices);
		}
		meshes.push_back(std::move(mesh));
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "Failed to load the file: May have failed to find it or it was not an .obj file" << endl
			<< abort(FatalError);
	}
	theMeshes_ = std::move(meshes);
	Change_IsDone() = Standard_True;
}