#pragma once
#ifndef _regionFunctionObject_Header
#define _regionFunctionObject_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2016-2019 OpenFOAM Foundation
	 \\/     M anipulation  |
-------------------------------------------------------------------------------
License
	This file is part of OpenFOAM.

	OpenFOAM is free software: you can redistribute it and/or modify it
	under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
	ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
	FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
	for more details.

	You should have received a copy of the GNU General Public License
	along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
	tnbLib::functionObjects::regionFunctionObject

Description
	Specialization of tnbLib::functionObject for a region and providing a
	reference to the region tnbLib::objectRegistry.

See also
	tnbLib::functionObject

SourceFiles
	regionFunctionObject.C

\*---------------------------------------------------------------------------*/

#include <tmp.hxx>  // added by amir
#include <functionObject.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class objectRegistry;

	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
							 Class regionFunctionObject Declaration
		\*---------------------------------------------------------------------------*/

		class regionFunctionObject
			:
			public functionObject
		{

		protected:

			// Protected member data

				//- Reference to the Time
			const Time& time_;

			//- Reference to the region objectRegistry
			const objectRegistry& obr_;


			// Protected member functions

				//- Find field in the objectRegistry
			template<class ObjectType>
			bool foundObject(const word& fieldName) const;

			//- Lookup object from the objectRegistry
			template<class ObjectType>
			const ObjectType& lookupObject(const word& fieldName) const;

			//- Lookup non-const object reference from the objectRegistry
			template<class ObjectType>
			ObjectType& lookupObjectRef(const word& fieldName);

			//- Store the given field in the objectRegistry under the given name
			template<class ObjectType>
			bool store
			(
				word& fieldName,
				const tmp<ObjectType>& tfield,
				bool cacheable = false
			);

			//- Write field if present in objectRegistry
			FoamBase_EXPORT bool writeObject(const word& fieldName)
			{
				NotImplemented;

				return false;
			}// Commented by Amin
			

			//- Clear field from the objectRegistry if present
			FoamBase_EXPORT bool clearObject(const word& fieldName);


		public:

			//- Runtime type information
			//TypeName("regionFunctionObject");
			static const char* typeName_() { return "regionFunctionObject"; }
			static FoamBase_EXPORT const ::tnbLib::word typeName;
			static FoamBase_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from Time and dictionary.
				//  The region objectRegistry is looked-up runTime with the name
				//  looked-up from the dictionary (defaults to polyMesh::defaultRegion)
			FoamBase_EXPORT regionFunctionObject
			(
				const word& name,
				const Time& runTime,
				const dictionary& dict
			);

			//- Construct from the region objectRegistry and dictionary
			FoamBase_EXPORT regionFunctionObject
			(
				const word& name,
				const objectRegistry& obr,
				const dictionary& dict
			);

			//- Disallow default bitwise copy construction
			FoamBase_EXPORT regionFunctionObject(const regionFunctionObject&) = delete;


			//- Destructor
			FoamBase_EXPORT virtual ~regionFunctionObject();


			// Member Functions

				//- Read optional controls
			FoamBase_EXPORT virtual bool read(const dictionary&);


			// Member Operators

				//- Disallow default bitwise assignment
			FoamBase_EXPORT void operator=(const regionFunctionObject&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <regionFunctionObjectI.hxx>

//#ifdef NoRepository
//#include <regionFunctionObjectTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_regionFunctionObject_Header
