#pragma once
#ifndef _fvc_Header
#define _fvc_Header

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

Namespace
	Foam::fvc

Description
	Namespace of functions to calculate explicit derivatives.

\*---------------------------------------------------------------------------*/

#include <fv.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <surfaceInterpolate.hxx>
#include <fvcVolumeIntegrate.hxx>
#include <fvcSurfaceIntegrate.hxx>
#include <fvcAverage.hxx>
#include <fvcReconstruct.hxx>
#include <fvcDdt.hxx>
#include <fvcDDtTotal.hxx>
#include <fvcD2dt2.hxx>
#include <fvcDiv.hxx>
#include <fvcFlux.hxx>
#include <fvcGrad.hxx>
#include <fvcMagSqrGradGrad.hxx>
#include <fvcSnGrad.hxx>
#include <fvcCurl.hxx>
#include <fvcLaplacian.hxx>
#include <fvcSup.hxx>
#include <fvcMeshPhi.hxx>

#include <fvcAdjDiv.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fvc_Header
