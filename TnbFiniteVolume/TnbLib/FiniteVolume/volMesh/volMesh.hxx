#pragma once
#ifndef _volMesh_Header
#define _volMesh_Header

#include <GeoMesh.hxx>
#include <fvMesh.hxx>
#include <primitiveMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class volMesh Declaration
	\*---------------------------------------------------------------------------*/

	class volMesh
		:
		public GeoMesh<fvMesh>
	{

	public:

		// Constructors

			//- Construct from fvMesh
		explicit volMesh(const fvMesh& mesh)
			:
			GeoMesh<fvMesh>(mesh)
		{}


		// Member Functions

			//- Return size
		label size() const
		{
			return size(mesh_);
		}

		//- Return size
		static label size(const Mesh& mesh)
		{
			return mesh.nCells();
		}

		//- Return cell centres
		const volVectorField& C()
		{
			return mesh_.C();
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_volMesh_Header
