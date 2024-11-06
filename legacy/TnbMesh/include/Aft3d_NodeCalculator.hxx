#pragma once
#ifndef _Aft3d_NodeCalculator_Header
#define _Aft3d_NodeCalculator_Header

#include <Mesh_Module.hxx>

#include <memory>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	// Forward Declarations [6/1/2023 Payvand]
	class Pnt3d;

	namespace legLib
	{
		// Forward Declarations [6/1/2023 Payvand]
		class Aft3d_VolumeCore;
		class Aft3d_Facet;

		class Aft3d_NodeCalculator
		{

			/*Private Data*/

		protected:

			// default constructor [6/1/2023 Payvand]

			Aft3d_NodeCalculator()
			{}

			// constructors [6/1/2023 Payvand]


		public:

			// Public functions and operators [6/1/2023 Payvand]

			virtual Pnt3d CalcCoord(const Standard_Real theSize, const std::shared_ptr<Aft3d_Facet>& theFacet,
			                        const Aft3d_VolumeCore* theCore) const = 0;

		};
	}
}

#endif // !_Aft3d_NodeCalculator_Header
