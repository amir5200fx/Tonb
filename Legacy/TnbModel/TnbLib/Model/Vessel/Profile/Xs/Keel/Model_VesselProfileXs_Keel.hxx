#pragma once
#ifndef _Model_VesselProfileXs_Keel_Header
#define _Model_VesselProfileXs_Keel_Header

#include <Model_VesselProfileXs.hxx>

namespace tnbLib
{

	namespace modelLib
	{

		namespace vesselLib
		{

			class KeelProfileXs
				: public VesselProfileXs
			{

				/*Private Data*/

			public:

				// default constructor [1/18/2023 Payvand]

				KeelProfileXs()
				{}

				// Constructors [1/18/2023 Payvand]

				KeelProfileXs(const std::vector<Standard_Real>& theXs)
					: VesselProfileXs(theXs)
				{}

				KeelProfileXs(std::vector<Standard_Real>&& theXs)
					: VesselProfileXs(std::move(theXs))
				{}


				// Public functions and operators [1/18/2023 Payvand]

				Standard_Boolean IsKeel() const override
				{
					return Standard_True;
				}

			};
		}
	}
}

#endif // !_Model_VesselProfileXs_Keel_Header
