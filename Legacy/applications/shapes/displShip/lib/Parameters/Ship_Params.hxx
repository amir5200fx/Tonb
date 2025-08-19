#pragma once
#ifndef _Ship_Params_Header
#define _Ship_Params_Header

#include <Ship_Dimens.hxx>
#include <Ship_HullParams.hxx>
#include <Ship_StemParams.hxx>
#include <Ship_KeelParams.hxx>
#include <Ship_TransomParams.hxx>

namespace tnbLib
{

	class Ship_Params
	{

		/*Private Data*/

		Ship_Dimens theDimensions_;

		Ship_HullParams theHull_;

		Ship_KeelParams theKeel_;
		Ship_StemParams theStem_;
		Ship_TransomParams theTransom_;


	public:

		// default constructor [11/1/2022 Amir]

		Ship_Params()
		{}


		// constructors [11/1/2022 Amir]

		// public functions and operators [11/1/2022 Amir]

		const auto& Dimensions() const
		{
			return theDimensions_;
		}

		auto& DimensionsRef()
		{
			return theDimensions_;
		}

		const auto& Hull() const
		{
			return theHull_;
		}

		auto& HullRef()
		{
			return theHull_;
		}

		const auto& Keel() const
		{
			return theKeel_;
		}

		auto& KeelRef()
		{
			return theKeel_;
		}

		const auto& Stem() const
		{
			return theStem_;
		}

		auto& StemRef()
		{
			return theStem_;
		}

		const auto& Transom() const
		{
			return theTransom_;
		}

		auto& TransomRef()
		{
			return theTransom_;
		}

	};
}

#endif // !_Ship_Params_Header
