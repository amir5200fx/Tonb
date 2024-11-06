#pragma once
#ifndef _Aft3d_NodeCalculator_UniSize_Header
#define _Aft3d_NodeCalculator_UniSize_Header

#include <Aft3d_NodeCalculator.hxx>

namespace tnbLib
{
	namespace legLib
	{

		class Aft3d_NodeCalculator_UniSize
			: public Aft3d_NodeCalculator
		{

			/*Private Data*/

		public:

			// default constructor [6/1/2023 Payvand]

			Aft3d_NodeCalculator_UniSize()
			{}

			// constructors [6/1/2023 Payvand]


			// Public functions and operators [6/1/2023 Payvand]

			TnbLegMesh_EXPORT Pnt3d 
				CalcCoord
				(
					const Standard_Real theSize,
					const std::shared_ptr<Aft3d_Facet>& theFacet,
					const Aft3d_VolumeCore* theCore
				) const override;

		};
	}
}

#endif // !_Aft3d_NodeCalculator_UniSize_Header
