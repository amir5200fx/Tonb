#pragma once
#ifndef _surfacePatchIOList_Header
#define _surfacePatchIOList_Header

#include <surfacePatchList.hxx>
#include <regIOobject.hxx>
#include <faceList.hxx>
#include <className.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes

	/*---------------------------------------------------------------------------*\
							   Class surfacePatchIOList Declaration
	\*---------------------------------------------------------------------------*/

	class surfacePatchIOList
		:
		public surfacePatchList,
		public regIOobject
	{
		// Private data


		// Private Member Functions

			//- Disallow default bitwise copy construct
		surfacePatchIOList(const surfacePatchIOList&);

		//- Disallow default bitwise assignment
		void operator=(const surfacePatchIOList&);


	public:

		//- Runtime type information
		TypeName("surfacePatchIOList");


		// Static data members

			//- Static data someStaticData

		// Constructors

			//- Construct from IOobject
		explicit surfacePatchIOList(const IOobject& io);

		//- Construct from IOobject
		surfacePatchIOList(const IOobject& io, const surfacePatchList&);

		// Destructor

		~surfacePatchIOList();


		// Member Functions

			//- writeData member function required by regIOobject
		bool writeData(Ostream&) const;


		// Member Operators

		// Friend Functions

		// Friend Operators

		// IOstream Operators

		friend Ostream& operator<<(Ostream&, const surfacePatchIOList&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_surfacePatchIOList_Header
