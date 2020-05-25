#pragma once
#ifndef _surfaceMesh_Header
#define _surfaceMesh_Header

#include <GeoMesh.hxx>
#include <fvMesh.hxx>
#include <primitiveMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class surfaceMesh Declaration
	\*---------------------------------------------------------------------------*/

	class surfaceMesh
		:
		public GeoMesh<fvMesh>
	{

	public:

		explicit surfaceMesh(const fvMesh& mesh)
			:
			GeoMesh<fvMesh>(mesh)
		{}

		label size() const
		{
			return size(mesh_);
		}

		static label size(const Mesh& mesh)
		{
			return mesh.nInternalFaces();
		}

		const surfaceVectorField& C()
		{
			return mesh_.Cf();
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_surfaceMesh_Header
