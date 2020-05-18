#pragma once
#ifndef _NVDVTVDV_Header
#define _NVDVTVDV_Header

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
	tnbLib::NVDVTVDV

Description
	tnbLib::NVDVTVDV

\*---------------------------------------------------------------------------*/

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <scalar.hxx>
#include <vector.hxx>
#include <tensor.hxx>

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class NVDVTVDV Declaration
	\*---------------------------------------------------------------------------*/

	class NVDVTVDV
	{

	public:

		typedef vector phiType;
		typedef tensor gradPhiType;

		// Null Constructor

		NVDVTVDV()
		{}


		// Member Functions

		scalar phict
		(
			const scalar faceFlux,
			const vector& phiP,
			const vector& phiN,
			const tensor& gradcP,
			const tensor& gradcN,
			const vector& d
		) const
		{
			vector gradfV = phiN - phiP;
			scalar gradf = gradfV & gradfV;

			scalar gradcf;

			if (faceFlux > 0)
			{
				gradcf = gradfV & (d & gradcP);
			}
			else
			{
				gradcf = gradfV & (d & gradcN);
			}

			// Stabilise for division
			gradcf = stabilise(gradcf, SMALL);

			return 1 - 0.5*gradf / gradcf;
		}


		scalar r
		(
			const scalar faceFlux,
			const vector& phiP,
			const vector& phiN,
			const tensor& gradcP,
			const tensor& gradcN,
			const vector& d
		) const
		{
			vector gradfV = phiN - phiP;
			scalar gradf = gradfV & gradfV;

			scalar gradcf;

			if (faceFlux > 0)
			{
				gradcf = gradfV & (d & gradcP);
			}
			else
			{
				gradcf = gradfV & (d & gradcN);
			}

			// Stabilise for division
			// Changed to SMALL to prevent FPE.  OB, 14/Jan/2011
			gradf = stabilise(gradf, SMALL);

			// New formulation.  Oliver Borm and Aleks Jemcov
			// HJ, 13/Jan/2011
			return max(2 * (gradcf / gradf) - 1, 0);
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_NVDVTVDV_Header
