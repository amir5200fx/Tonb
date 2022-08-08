#pragma once
#ifndef _Geo3d_BalPrTreeLeafHub_Header
#define _Geo3d_BalPrTreeLeafHub_Header

#include <list>
#include <memory>

namespace tnbLib
{

	// Forward Declarations [7/5/2022 Amir]
	template<class T> class Geo3d_BalPrTreeLeaf;

	template<class T>
	class Geo3d_BalPrTreeLeafHub
	{

	public:

		typedef std::list<Geo3d_BalPrTreeLeaf<T>*> leafList;

	private:

		/*Private Data*/

		leafList theSNeighbors_;
		leafList theENeighbors_;
		leafList theNNeighbors_;
		leafList theWNeighbors_;
		leafList theFNeighbors_;
		leafList theBNeighbors_;

	public:

		// default constructor [7/5/2022 Amir]

		Geo3d_BalPrTreeLeafHub()
		{}


		// public functions and operators [7/5/2022 Amir]

		const auto& SNeighbors() const
		{
			return theSNeighbors_;
		}

		auto& SNeighborsRef()
		{
			return theSNeighbors_;
		}

		const auto& ENeighbors() const
		{
			return theENeighbors_;
		}

		auto& ENeighborsRef()
		{
			return theENeighbors_;
		}

		const auto& NNeighbors() const
		{
			return theNNeighbors_;
		}

		auto& NNeighborsRef()
		{
			return theNNeighbors_;
		}

		const auto& WNeighbors() const
		{
			return theWNeighbors_;
		}

		auto& WNeighborsRef()
		{
			return theWNeighbors_;
		}

		const auto& FNeighbors() const
		{
			return theFNeighbors_;
		}

		auto& FNeighborsRef()
		{
			return theFNeighbors_;
		}

		const auto& BNeighbors() const
		{
			return theBNeighbors_;
		}

		auto& BNeighborsRef()
		{
			return theBNeighbors_;
		}

	};
}

#endif // !_Geo3d_BalPrTreeLeafHub_Header
