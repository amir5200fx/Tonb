#pragma once
#ifndef _MeshBLayer2d_Tools_Header
#define _MeshBLayer2d_Tools_Header

#include <MeshBLayer_Module.hxx>
#include <Vec2d.hxx>
#include <Pnt2d.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations [2/1/2023 Payvand]

	class MeshBLayer2d_Node;

	class MeshBLayer2d_Tools
	{

	public:

		static Pnt2d CalcPoint(const std::shared_ptr<MeshBLayer2d_Node>&, const Standard_Real h);

		static Vec2d CalcNormal(const std::shared_ptr<MeshBLayer2d_Node>&);

		static void CalcNormals(const std::vector<std::shared_ptr<MeshBLayer2d_Node>>);

	};
}

#endif // !_MeshBLayer2d_Tools_Header
