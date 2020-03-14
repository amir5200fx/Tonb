#pragma once
#ifndef _sphereRefinement_Header
#define _sphereRefinement_Header

#include <objectRefinement.hxx>
#include <point.hxx>
#include <typeInfo.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class sphereRefinement Declaration
	\*---------------------------------------------------------------------------*/

	class sphereRefinement
		:
		public objectRefinement
	{
		// Private data
			//- centre of the sphere
		point centre_;

		//- radius of the sphere
		scalar radius_;

	public:

		//- Runtime type information
		TypeName("sphere");


		// Constructors

			//- Null construct
		sphereRefinement();

		//- Construct from name, cell size, centre and radius
		sphereRefinement
		(
			const word& name,
			const scalar cellSize,
			const direction additionalRefLevels,
			const point& centre,
			const scalar radius
		);

		//- Construct from dictionary
		sphereRefinement(const word& name, const dictionary& dict);

		//- Construct and return a clone
		virtual autoPtr<objectRefinement> clone
		(
			const sphereRefinement& sr
		) const
		{
			return autoPtr<objectRefinement>
				(
					new sphereRefinement
					(
						sr.name(),
						sr.cellSize(),
						sr.additionalRefinementLevels(),
						sr.centre_,
						sr.radius_
					)
					);
		}

		// Member Functions

			//- check if a boundBox intersects or is inside the object
		bool intersectsObject(const boundBox&) const;

		//- Return as dictionary of entries
		dictionary dict(bool ignoreType = false) const;

		// Write

		  //- Write
		void write(Ostream&) const;

		//- Write dictionary
		void writeDict(Ostream&, bool subDict = true) const;

		// Member Operators

			//- assign from dictionary
		void operator=(const dictionary&);

		// IOstream Operators

		Ostream& operator<<(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_sphereRefinement_Header
