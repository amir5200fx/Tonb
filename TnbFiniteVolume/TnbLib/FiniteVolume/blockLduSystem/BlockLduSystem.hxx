#pragma once
#ifndef _BlockLduSystem_Header
#define _BlockLduSystem_Header

#include <blockVectorNMatrices.hxx>
#include <VectorNFieldTypes.hxx>
#include <volVectorNFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of friend functions and operators

	template<class blockType, class sourceType>
	class BlockLduSystem;

	template<class blockType, class sourceType>
	Ostream& operator<<(Ostream&, const BlockLduSystem<blockType, sourceType>&);


	/*---------------------------------------------------------------------------*\
							Class BlockLduSystem Declaration
	\*---------------------------------------------------------------------------*/

	template<class blockType, class sourceType>
	class BlockLduSystem
		: public BlockLduMatrix<blockType>
	{
		// Private data

			//- Source term
		Field<sourceType> source_;


	public:

		// Constructors

			//- Construct given addressing
		explicit BlockLduSystem(const lduMesh&);

		//- Construct given addressing and source field
		BlockLduSystem(const lduMesh&, const Field<sourceType>&);

		//- Construct from components
		BlockLduSystem
		(
			const BlockLduMatrix<blockType>&,
			const Field<sourceType>&
		);

		//- Construct as copy
		BlockLduSystem(const BlockLduSystem<blockType, sourceType>&);


		// Destructor

		virtual ~BlockLduSystem()
		{}


		// Member functions

			//- Access

		Field<sourceType>& source()
		{
			return source_;
		}

		const Field<sourceType>& source() const
		{
			return source_;
		}


		// Member operators

		void operator=(const BlockLduSystem<blockType, sourceType>&);

		void negate();

		void operator+=(const BlockLduSystem<blockType, sourceType>&);
		void operator-=(const BlockLduSystem<blockType, sourceType>&);

		void operator*=(const scalarField&);
		void operator*=(const scalar);


		// Ostream operator

		friend Ostream& operator<< <blockType, sourceType>
			(
				Ostream&,
				const BlockLduSystem<blockType, sourceType>&
				);
	};


} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include <BlockLduSystem.cxx>
#   include <BlockLduSystemOperations.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_BlockLduSystem_Header
