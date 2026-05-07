#pragma once
#ifndef _Model_VesselProfileXs_Deck_Header
#define _Model_VesselProfileXs_Deck_Header

#include <Model_VesselProfileXs.hxx>

namespace tnbLib
{

	namespace modelLib
	{

		namespace vesselLib
		{

			class DeckProfileXs
				: public VesselProfileXs
			{

				/*Private Data*/

			public:

				// default constructor [1/18/2023 Payvand]

				DeckProfileXs()
				{}

				// Constructors [1/18/2023 Payvand]

				DeckProfileXs(const std::vector<Standard_Real>& theXs)
					: VesselProfileXs(theXs)
				{}

				DeckProfileXs(std::vector<Standard_Real>&& theXs)
					: VesselProfileXs(std::move(theXs))
				{}


				// Public functions and operators [1/18/2023 Payvand]

				Standard_Boolean IsDeck() const override
				{
					return Standard_True;
				}

			};
		}
	}
}

#endif // !_Model_VesselProfileXs_Deck_Header
