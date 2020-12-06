#pragma once
#ifndef _cellShape_Header
#define _cellShape_Header

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
	tnbLib::cellShape

Description
	An analytical geometric cellShape.

	The optional collapse functionality changes the cellModel to the
	correct type after removing any duplicate points.

SourceFiles
	cellShapeI.H
	cellShape.C
	cellShapeIO.C
	cellShapeEqual.C

\*---------------------------------------------------------------------------*/

#include <pointField.hxx>
#include <labelList.hxx>
#include <cellModel.hxx>
#include <autoPtr.hxx>
#include <InfoProxy.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class cell;

	// Forward declaration of friend functions and operators

	class cellShape;
	FoamBase_EXPORT bool operator==(const cellShape&, const cellShape&);
	FoamBase_EXPORT Istream& operator>>(Istream&, cellShape&);
	FoamBase_EXPORT Ostream& operator<<(Ostream&, const cellShape&);


	/*---------------------------------------------------------------------------*\
							  Class cellShape Declaration
	\*---------------------------------------------------------------------------*/

	class cellShape
		:
		public labelList
	{
		// Private Data

			//- Access to the cellShape's model
		const cellModel *m;


	public:

		// Constructors

			//- Construct null
		inline cellShape();

		//- Construct from components
		inline cellShape
		(
			const cellModel&,
			const labelList&,
			const bool doCollapse = false
		);

		//- Construct from components
		inline cellShape
		(
			const word& model,
			const labelList&,
			const bool doCollapse = false
		);

		//- Construct from Istream
		inline cellShape(Istream& is);

		//- Clone
		inline autoPtr<cellShape> clone() const;


		// Member Functions

			//- Return the points corresponding to this cellShape
		inline pointField points(const pointField& meshPoints) const;

		//- Model reference
		inline const cellModel& model() const;

		//- Mesh face labels of this cell (in order of model)
		inline labelList meshFaces(const faceList& allFaces, const cell&) const;

		//- Mesh edge labels of this cell (in order of model)
		inline labelList meshEdges
		(
			const edgeList& allEdges,
			const labelList&
		) const;

		//- Faces of this cell
		inline faceList faces() const;

		//- Collapsed faces of this cell
		inline faceList collapsedFaces() const;

		//- Number of faces
		inline label nFaces() const;

		//- Edges of this cellShape
		inline edgeList edges() const;

		//- Number of edges
		inline label nEdges() const;

		//- Number of points
		inline label nPoints() const;

		//- Centroid of the cell
		inline point centre(const pointField&) const;

		//- Return info proxy.
		//  Used to print token information to a stream
		tnbLib::InfoProxy<cellShape> info() const
		{
			return *this;
		}

		//- Scalar magnitude
		inline scalar mag(const pointField&) const;

		//- Collapse shape to correct one after removing duplicate vertices
		FoamBase_EXPORT void collapse();


		// Friend Operators

		friend FoamBase_EXPORT bool operator==(const cellShape&, const cellShape&);


		// IOstream Operators

		friend FoamBase_EXPORT Istream& operator>>(Istream&, cellShape&);
		friend FoamBase_EXPORT Ostream& operator<<(Ostream&, const cellShape&);
	};


	template<>
	FoamBase_EXPORT Ostream& operator<<(Ostream& os, const InfoProxy<cellShape>& ip);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <cellShapeI.hxx>

#endif // !_cellShape_Header
