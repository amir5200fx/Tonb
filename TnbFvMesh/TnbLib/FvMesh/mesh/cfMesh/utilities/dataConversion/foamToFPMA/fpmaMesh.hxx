#pragma once
#ifndef _fpmaMesh_Header
#define _fpmaMesh_Header

#include <polyMeshGen.hxx>
#include <OFstream.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class fpmaMesh Declaration
	\*---------------------------------------------------------------------------*/

	class fpmaMesh
	{
		// Private data


		// Private Member Functions

			//- Disallow default bitwise copy construct
		fpmaMesh(const fpmaMesh&);

		//- Disallow default bitwise assignment
		void operator=(const fpmaMesh&);

		void writePoints(OFstream& fpmaGeometryFile) const;

		void writeFaces(OFstream& fpmaGeometryFile) const;

		void writeCells(OFstream& fpmaGeometryFile) const;

		void writeSubsets(OFstream& fpmaGeometryFile) const;

	public:

		// Public data

		const polyMeshGen& mesh_;

		// Constructors

			//- Construct from polyMeshGen
		fpmaMesh(const polyMeshGen& mesh);


		// Destructor

		~fpmaMesh();


		// Member Functions

			// Access

			// Check

			// Edit

			// Write

		void write(OFstream& fpmaGeometryFile) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fpmaMesh_Header
