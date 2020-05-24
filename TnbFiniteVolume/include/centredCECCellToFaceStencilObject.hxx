#pragma once
#ifndef _centredCECCellToFaceStencilObject_Header
#define _centredCECCellToFaceStencilObject_Header

#include <extendedCentredCellToFaceStencil.hxx>
#include <CECCellToFaceStencil.hxx>
#include <MeshObject.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
				  Class centredCECCellToFaceStencilObject Declaration
	\*---------------------------------------------------------------------------*/

	class centredCECCellToFaceStencilObject
		:
		public MeshObject<fvMesh, centredCECCellToFaceStencilObject>,
		public extendedCentredCellToFaceStencil
	{

	public:

		TypeName("centredCECCellToFaceStencil");

		// Constructors

			//- Construct from uncompacted face stencil
		explicit centredCECCellToFaceStencilObject
		(
			const fvMesh& mesh
		)
			:
			MeshObject<fvMesh, centredCECCellToFaceStencilObject>(mesh),
			extendedCentredCellToFaceStencil(CECCellToFaceStencil(mesh))
		{
			if (extendedCellToFaceStencil::debug)
			{
				Info << "Generated centred stencil " << type()
					<< nl << endl;
				writeStencilStats(Info, stencil(), map());
			}
		}


		// Destructor

		virtual ~centredCECCellToFaceStencilObject()
		{}


		// Member functions

			//- Delete the stencil when the mesh moves
		virtual bool movePoints() const
		{
			deleteObject();
			return true;
		}

		//- Delete the stencil when mesh updates
		virtual bool updateMesh(const mapPolyMesh&) const
		{
			deleteObject();
			return true;
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_centredCECCellToFaceStencilObject_Header
