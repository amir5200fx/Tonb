#pragma once
/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | foam-extend: Open Source CFD
   \\    /   O peration     | Version:     4.0
	\\  /    A nd           | Web:         http://www.foam-extend.org
	 \\/     M anipulation  | For copyright notice see file Copyright
-------------------------------------------------------------------------------
License
	This file is part of foam-extend.

	foam-extend is free software: you can redistribute it and/or modify it
	under the terms of the GNU General Public License as published by the
	Free Software Foundation, either version 3 of the License, or (at your
	option) any later version.

	foam-extend is distributed in the hope that it will be useful, but
	WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with foam-extend.  If not, see <http://www.gnu.org/licenses/>.

Class
	regionCouplePointPatch

Description
	Dummy regionCouple patch for post-processing.  No functionality built in!

Author
	Hrvoje Jasak, Wikki Ltd.  All rights reserved

SourceFiles
	regionCouplePointPatch.C

\*---------------------------------------------------------------------------*/
#ifndef _regionCouplePointPatch_Header
#define _regionCouplePointPatch_Header

#include <coupledFacePointPatch.hxx>
#include <regionCouplePolyPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class regionCouplePointPatch Declaration
	\*---------------------------------------------------------------------------*/

	class regionCouplePointPatch
		:
		public coupledFacePointPatch
	{
		// Private data

			//- Local reference cast into the cyclic patch
		const regionCouplePolyPatch& regionCouplePolyPatch_;


		// Private Member Functions

			//- Disallow default construct as copy
		regionCouplePointPatch(const regionCouplePointPatch&);

		//- Disallow default assignment
		void operator=(const regionCouplePointPatch&);


	protected:

		// Protected Member Functions

			//- Initialise the calculation of the patch geometry
		virtual void initGeometry()
		{}

		//- Calculate mesh points
		virtual void calcGeometry()
		{}

		//- Correct patches after moving points
		virtual void movePoints()
		{}

		//- Initialise the update of the patch topology
		virtual void initUpdateMesh();

		//- Update of the patch topology
		virtual void updateMesh();


	public:

		typedef pointBoundaryMesh BoundaryMesh;


		//- Runtime type information
		TypeName(regionCouplePolyPatch::typeName_());


		// Constructors

			//- Construct from components
		regionCouplePointPatch
		(
			const polyPatch& patch,
			const pointBoundaryMesh& bm
		);


		// Destructor

		virtual ~regionCouplePointPatch();


		// Member Functions

			// Access

				//- Return true if coupled
		virtual bool coupled() const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_regionCouplePointPatch_Header
