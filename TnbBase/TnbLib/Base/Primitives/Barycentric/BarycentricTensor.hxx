#pragma once
#ifndef _BarycentricTensor_Header
#define _BarycentricTensor_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2017-2018 OpenFOAM Foundation
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
	Foam::BarycentricTensor

Description
	Templated 4x3 tensor derived from VectorSpace. Has 12 components. Can
	represent a barycentric transformation as a matrix-barycentric inner-
	product. Can alternatively represent an inverse barycentric transformation
	as a vector-matrix inner-product.

SourceFiles
	BarycentricTensorI.H

\*---------------------------------------------------------------------------*/

#include <Barycentric.hxx>
#include <tensor.hxx>

#endif // !_BarycentricTensor_Header
