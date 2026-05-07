#pragma once
#ifndef _Model_VesselProfileXs_Header
#define _Model_VesselProfileXs_Header

#include <vector>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	namespace modelLib
	{

		class VesselProfileXs
		{

			/*Private Data*/

			std::vector<Standard_Real> theXs_;

		protected:

			// default constructor [1/18/2023 Payvand]

			VesselProfileXs()
			{}

			// constructors [1/18/2023 Payvand]

			VesselProfileXs(const std::vector<Standard_Real>& theXs)
				: theXs_(theXs)
			{}

			VesselProfileXs(std::vector<Standard_Real>&& theXs)
				: theXs_(std::move(theXs))
			{}

		public:

			// Public functions and operators [1/18/2023 Payvand]

			const auto& Xs() const
			{
				return theXs_;
			}

			auto& XsRef()
			{
				return theXs_;
			}

			virtual Standard_Boolean IsDeck() const
			{
				return Standard_False;
			}

			virtual Standard_Boolean IsKeel() const
			{
				return Standard_False;
			}
		};
	}
}

#include <Model_VesselProfileXs_Deck.hxx>
#include <Model_VesselProfileXs_Keel.hxx>

#endif // !_Model_VesselProfileXs_Header
