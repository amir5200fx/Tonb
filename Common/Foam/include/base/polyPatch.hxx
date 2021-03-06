#pragma once
#ifndef _polyPatch_Header
#define _polyPatch_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
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
	tnbLib::polyPatch

Description
	A patch is a list of labels that address the faces in the global face list.

	The patch can calculate its own edges based on the global faces.
	Patch also contains all addressing between the faces.

SourceFiles
	polyPatch.C
	polyPatchNew.C

\*---------------------------------------------------------------------------*/

#include <patchIdentifier.hxx>
#include <primitivePatch.hxx>
#include <typeInfo.hxx>
#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	// Forward declaration of friend functions and operators

	class polyBoundaryMesh;
	class polyPatch;
	class PstreamBuffers;

	FoamBase_EXPORT Ostream& operator<<(Ostream&, const polyPatch&);


	/*---------------------------------------------------------------------------*\
							   Class polyPatch Declaration
	\*---------------------------------------------------------------------------*/

	class polyPatch
		:
		public patchIdentifier,
		public primitivePatch
	{
		// Private Data

			//- Start label of this patch in the polyMesh face list
		label start_;

		//- Reference to boundary mesh
		const polyBoundaryMesh& boundaryMesh_;


		// Demand-driven private data

			//- face-cell addressing
		mutable labelList::subList* faceCellsPtr_;

		//- Global edge addressing
		mutable labelList* mePtr_;


	protected:

		// Protected Member Functions

			//- Inherit movePoints from primitivePatch
		using primitivePatch::movePoints;

		// The polyPatch geometry initialisation is called by polyBoundaryMesh
		friend class polyBoundaryMesh;

		//- Initialise the calculation of the patch geometry
		virtual void initGeometry(PstreamBuffers&)
		{}

		//- Calculate the patch geometry
		virtual void calcGeometry(PstreamBuffers&)
		{}

		//- Initialise the patches for moving points
		virtual void initMovePoints(PstreamBuffers&, const pointField&)
		{}

		//- Correct patches after moving points
		FoamBase_EXPORT virtual void movePoints(PstreamBuffers&, const pointField& p);

		//- Initialise the update of the patch topology
		virtual void initUpdateMesh(PstreamBuffers&)
		{}

		//- Update of the patch topology
		FoamBase_EXPORT virtual void updateMesh(PstreamBuffers&);

		//- Clear geometry
		FoamBase_EXPORT virtual void clearGeom();


	public:

		//- Runtime type information
		//TypeName("patch");
		static const char* typeName_() { return "patch"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		//- Debug switch to disallow the use of genericPolyPatch
		static FoamBase_EXPORT int disallowGenericPolyPatch;


		// Declare run-time constructor selection tables

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			polyPatch,
			word,
			(
				const word& name,
				const label size,
				const label start,
				const label index,
				const polyBoundaryMesh& bm,
				const word& patchType
				),
				(name, size, start, index, bm, patchType)
		);*/

		typedef autoPtr<polyPatch> (*wordConstructorPtr)(const word& name, const label size, const label start,
		                                                 const label index, const polyBoundaryMesh& bm,
		                                                 const word& patchType);
		typedef HashTable<wordConstructorPtr, word, string::hash> wordConstructorTable;
		static FoamBase_EXPORT wordConstructorTable* wordConstructorTablePtr_;
		static FoamBase_EXPORT void constructwordConstructorTables();
		static FoamBase_EXPORT void destroywordConstructorTables();

		template <class polyPatchType>
		class addwordConstructorToTable
		{
		public:
			static autoPtr<polyPatch> New(const word& name, const label size, const label start, const label index,
			                              const polyBoundaryMesh& bm, const word& patchType)
			{
				return autoPtr<polyPatch>(new polyPatchType(name, size, start, index, bm, patchType));
			}

			addwordConstructorToTable(const word& lookup = polyPatchType::typeName)
			{
				constructwordConstructorTables();
				if (!wordConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "polyPatch" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addwordConstructorToTable() { destroywordConstructorTables(); }
		};

		template <class polyPatchType>
		class addRemovablewordConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<polyPatch> New(const word& name, const label size, const label start, const label index,
			                              const polyBoundaryMesh& bm, const word& patchType)
			{
				return autoPtr<polyPatch>(new polyPatchType(name, size, start, index, bm, patchType));
			}

			addRemovablewordConstructorToTable(const word& lookup = polyPatchType::typeName) : lookup_(lookup)
			{
				constructwordConstructorTables();
				wordConstructorTablePtr_->set(lookup, New);
			}

			~addRemovablewordConstructorToTable() { if (wordConstructorTablePtr_) { wordConstructorTablePtr_->erase(lookup_); } }
		};;

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			polyPatch,
			dictionary,
			(
				const word& name,
				const dictionary& dict,
				const label index,
				const polyBoundaryMesh& bm,
				const word& patchType
				),
				(name, dict, index, bm, patchType)
		);*/

		typedef autoPtr<polyPatch> (*dictionaryConstructorPtr)(const word& name, const dictionary& dict, const label index,
		                                                       const polyBoundaryMesh& bm, const word& patchType);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamBase_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamBase_EXPORT void constructdictionaryConstructorTables();
		static FoamBase_EXPORT void destroydictionaryConstructorTables();

		template <class polyPatchType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<polyPatch> New(const word& name, const dictionary& dict, const label index,
			                              const polyBoundaryMesh& bm, const word& patchType)
			{
				return autoPtr<polyPatch>(new polyPatchType(name, dict, index, bm, patchType));
			}

			adddictionaryConstructorToTable(const word& lookup = polyPatchType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "polyPatch" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class polyPatchType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<polyPatch> New(const word& name, const dictionary& dict, const label index,
			                              const polyBoundaryMesh& bm, const word& patchType)
			{
				return autoPtr<polyPatch>(new polyPatchType(name, dict, index, bm, patchType));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = polyPatchType::typeName) : lookup_(lookup)
			{
				constructdictionaryConstructorTables();
				dictionaryConstructorTablePtr_->set(lookup, New);
			}

			~addRemovabledictionaryConstructorToTable()
			{
				if (dictionaryConstructorTablePtr_) { dictionaryConstructorTablePtr_->erase(lookup_); }
			}
		};;


		// Constructors

			//- Construct from components
		FoamBase_EXPORT polyPatch
		(
			const word& name,
			const label size,
			const label start,
			const label index,
			const polyBoundaryMesh& bm,
			const word& patchType
		);

		//- Construct from dictionary
		FoamBase_EXPORT polyPatch
		(
			const word& name,
			const dictionary& dict,
			const label index,
			const polyBoundaryMesh& bm,
			const word& patchType
		);

		//- Copy constructor, resetting the boundary mesh
		FoamBase_EXPORT polyPatch(const polyPatch&, const polyBoundaryMesh&);

		//- Construct given the original patch and resetting the
		//  face list and boundary mesh information
		FoamBase_EXPORT polyPatch
		(
			const polyPatch& pp,
			const polyBoundaryMesh& bm,
			const label index,
			const label newSize,
			const label newStart
		);

		//- Construct given the original patch and a map
		FoamBase_EXPORT polyPatch
		(
			const polyPatch& pp,
			const polyBoundaryMesh& bm,
			const label index,
			const labelUList& mapAddressing,
			const label newStart
		);

		//- Copy constructor
		FoamBase_EXPORT polyPatch(const polyPatch&);

		// To avoid irritating warnings from clang
		using primitivePatch::clone;

		//- Construct and return a clone, resetting the boundary mesh
		virtual autoPtr<polyPatch> clone(const polyBoundaryMesh& bm) const
		{
			return autoPtr<polyPatch>(new polyPatch(*this, bm));
		}

		//- Construct and return a clone, resetting the face list
		//  and boundary mesh
		virtual autoPtr<polyPatch> clone
		(
			const polyBoundaryMesh& bm,
			const label index,
			const label newSize,
			const label newStart
		) const
		{
			return autoPtr<polyPatch>
				(
					new polyPatch(*this, bm, index, newSize, newStart)
					);
		}

		//- Construct and return a clone, resetting the face list
		//  and boundary mesh
		virtual autoPtr<polyPatch> clone
		(
			const polyBoundaryMesh& bm,
			const label index,
			const labelUList& mapAddressing,
			const label newStart
		) const
		{
			return autoPtr<polyPatch>
				(
					new polyPatch(*this, bm, index, mapAddressing, newStart)
					);
		}


		// Selectors

			//- Return a pointer to a new patch created on freestore from
			//  components
		static FoamBase_EXPORT autoPtr<polyPatch> New
		(
			const word& patchType,
			const word& name,
			const label size,
			const label start,
			const label index,
			const polyBoundaryMesh& bm
		);

		//- Return a pointer to a new patch created on freestore from
		//  dictionary
		static FoamBase_EXPORT autoPtr<polyPatch> New
		(
			const word& name,
			const dictionary& dict,
			const label index,
			const polyBoundaryMesh& bm
		);

		//- Return a pointer to a new patch created on freestore from
		//  dictionary
		static FoamBase_EXPORT autoPtr<polyPatch> New
		(
			const word& patchType,
			const word& name,
			const dictionary& dict,
			const label index,
			const polyBoundaryMesh& bm
		);


		//- Destructor
		FoamBase_EXPORT virtual ~polyPatch();


		// Member Functions

			//- Return start label of this patch in the polyMesh face list
		label start() const
		{
			return start_;
		}

		//- Return boundaryMesh reference
		FoamBase_EXPORT const polyBoundaryMesh& boundaryMesh() const;

		//- Return true if this patch is geometrically coupled (i.e. faces and
		//  points correspondence)
		virtual bool coupled() const
		{
			return false;
		}

		//- Return true if the given type is a constraint type
		static FoamBase_EXPORT bool constraintType(const word& pt);

		//- Return a list of all the constraint patch types
		static FoamBase_EXPORT wordList constraintTypes();

		//- Extract face cell data
		template<class T>
		const UIndirectList<T> patchInternalList
		(
			const UList<T>& internalValues
		) const
		{
			return UIndirectList<T>(internalValues, faceCells());
		}

		//- Slice list to patch
		template<class T>
		const typename List<T>::subList patchSlice(const UList<T>& l) const
		{
			return typename List<T>::subList(l, this->size(), start_);
		}

		//- Slice Field to patch
		template<class T>
		const typename Field<T>::subField patchSlice(const Field<T>& l) const
		{
			return typename Field<T>::subField(l, this->size(), start_);
		}


		//- Write the polyPatch data as a dictionary
		FoamBase_EXPORT virtual void write(Ostream&) const;


		// Geometric data; point list required

			//- Return face centres
		FoamBase_EXPORT const vectorField::subField faceCentres() const;

		//- Return face normals
		FoamBase_EXPORT const vectorField::subField faceAreas() const;

		//- Return face cell centres
		FoamBase_EXPORT tmp<vectorField> faceCellCentres() const;


		// Addressing into mesh

			//- Return face-cell addressing
		FoamBase_EXPORT const labelUList& faceCells() const;

		//- Return global edge index for local edges
		FoamBase_EXPORT const labelList& meshEdges() const;

		//- Clear addressing
		FoamBase_EXPORT virtual void clearAddressing();


		// Other patch operations

			//- Return label of face in patch from global face label
		inline label whichFace(const label l) const
		{
			return l - start_;
		}


		//- Initialize ordering for primitivePatch. Does not
		//  refer to *this (except for name() and type() etc.)
		FoamBase_EXPORT virtual void initOrder(PstreamBuffers&, const primitivePatch&) const;

		//- Return new ordering for primitivePatch.
		//  Ordering is -faceMap: for every face
		//  index of the new face -rotation:for every new face the clockwise
		//  shift of the original face. Return false if nothing changes
		//  (faceMap is identity, rotation is 0), true otherwise.
		FoamBase_EXPORT virtual bool order
		(
			PstreamBuffers&,
			const primitivePatch&,
			labelList& faceMap,
			labelList& rotation
		) const;


		// Member Operators

			//- Assignment
		FoamBase_EXPORT void operator=(const polyPatch&);


		// Ostream Operator

		friend FoamBase_EXPORT Ostream& operator<<(Ostream&, const polyPatch&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_polyPatch_Header
