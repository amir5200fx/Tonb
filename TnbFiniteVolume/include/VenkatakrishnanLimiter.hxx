#pragma once
#ifndef _VenkatakrishnanLimiter_Header
#define _VenkatakrishnanLimiter_Header

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
	VenkatakrishnanLimiter

Description
	Venkatakrishnan differentiable limiter

Author
	Aleksandar Jemcov
	Rewrite by Hrvoje Jasak

\*---------------------------------------------------------------------------*/

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <scalar.hxx>

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					  Class VenkatakrishnanLimiter Declaration
	\*---------------------------------------------------------------------------*/

	class VenkatakrishnanLimiter
	{
		// Private data

			//- Limiter value
		scalar k_;


	public:

		// Constructor

			//- Construct null
		VenkatakrishnanLimiter()
			:
			k_(5)
		{}

		//- Set scalar limiter value
		inline void limiter
		(
			scalar& lim,
			const scalar& cellVolume,
			const scalar& deltaOneMax,
			const scalar& deltaOneMin,
			const scalar& extrapolate
		)
		{
			scalar epsilonSquare = pow3(k_)*cellVolume;

			if (mag(extrapolate) < SMALL)
			{
				// Limiter remains unchanged
				return;
			}
			else if (extrapolate > VSMALL)
			{
				lim = max
				(
					0,
					min
					(
					(
						(sqr(deltaOneMax) + epsilonSquare)*extrapolate
						+ 2 * sqr(extrapolate)*deltaOneMax
						) /
						stabilise
						(
							extrapolate*
							(
								sqr(deltaOneMax)
								+ 2 * sqr(extrapolate)
								+ deltaOneMax * extrapolate
								+ epsilonSquare
								),
							SMALL
						),
						lim
					)
				);
			}
			else if (extrapolate < VSMALL)
			{
				lim = max
				(
					0,
					min
					(
					(
						(sqr(deltaOneMin) + epsilonSquare)*extrapolate
						+ 2 * sqr(extrapolate)*deltaOneMin
						) /
						stabilise
						(
							extrapolate*
							(
								sqr(deltaOneMin)
								+ 2 * sqr(extrapolate)
								+ deltaOneMin * extrapolate
								+ epsilonSquare
								),
							SMALL
						),
						lim
					)
				);
			}
		}

		//- Set Type limiter
		template<class Type>
		inline void limiter
		(
			Type& lim,
			const scalar& cellVolume,
			const Type& deltaOneMax,
			const Type& deltaOneMin,
			const Type& extrapolate
		)
		{
			for (direction cmpt = 0; cmpt < Type::nComponents; cmpt++)
			{
				limiter
				(
					lim.component(cmpt),
					cellVolume,
					deltaOneMax.component(cmpt),
					deltaOneMin.component(cmpt),
					extrapolate.component(cmpt)
				);
			}
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib


#endif // !_VenkatakrishnanLimiter_Header
