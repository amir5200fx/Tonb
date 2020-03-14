#pragma once
#ifndef _meshOctreeCubeBasic_Header
#define _meshOctreeCubeBasic_Header

#include <meshOctreeCubeCoordinates.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Class meshOctreeCubeBasic Declaration
	\*---------------------------------------------------------------------------*/

	class meshOctreeCubeBasic
		: public meshOctreeCubeCoordinates
	{
		// Private data
			//- cube type
		direction cubeType_;

		//- processor to which the cube belongs to
		short procNo_;

	public:

		// Constructors
			//- Null constructor
		inline meshOctreeCubeBasic();

		//- Construct from coordinates
		explicit inline meshOctreeCubeBasic
		(
			const meshOctreeCubeCoordinates&
		);

		//- Construct from coordinates and cube type
		inline meshOctreeCubeBasic
		(
			const meshOctreeCubeCoordinates& cc,
			const direction cubeType,
			const short procNo = ALLPROCS
		);

		// Destructor

		~meshOctreeCubeBasic()
		{}

		// Enumerators

		enum typesOfCubes
		{
			UNKNOWN = 1,
			OUTSIDE = 2,
			DATA = 4,
			INSIDE = 8,
			ALLPROCS = -2,
			OTHERPROC = -3
		};

		// Member functions
			//- return type
		inline direction cubeType() const;

		//- set cube type
		inline void setCubeType(const direction);

		//- return processor number
		inline short procNo() const;

		//- set processor number
		inline void setProcNo(const short);

		//- return coordinates in the octree
		inline const meshOctreeCubeCoordinates& coordinates() const;

		// Member operators

		inline void operator=(const meshOctreeCubeBasic&);

		// Friend operators

		friend inline Ostream& operator<<
			(
				Ostream&,
				const meshOctreeCubeBasic&
				);

		friend inline Istream& operator>>
			(
				Istream&,
				meshOctreeCubeBasic&
				);
	};

	//- Specify data associated with meshOctreeCubeBasic type is contiguous
	template<>
	inline bool contiguous<meshOctreeCubeBasic>() {
		return true;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <meshOctreeCubeBasicI.hxx>

#endif // !_meshOctreeCubeBasic_Header
