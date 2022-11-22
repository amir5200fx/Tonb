#pragma once
#ifndef _Geo2d_BalPrTreeLeafHub_Header
#define _Geo2d_BalPrTreeLeafHub_Header

#include <list>
#include <memory>

namespace tnbLib
{

	// Forward Declarations [11/9/2022 Amir]
	template<class T> class Geo2d_BalPrTreeLeaf;

	template<class T>
	class Geo2d_BalPrTreeLeafHub
	{

	public:

		typedef std::list<Geo2d_BalPrTreeLeaf<T>*> leafList;

	private:

		/*Private Data*/

		leafList theSNeighbors_;
		leafList theENeighbors_;
		leafList theNNeighbors_;
		leafList theWNeighbors_;

	public:

		// default constructor [11/9/2022 Amir]

		Geo2d_BalPrTreeLeafHub()
		{}

		// public functions and operators [11/9/2022 Amir]


		~Geo2d_BalPrTreeLeafHub()
		{
			theSNeighbors_.empty();
			theENeighbors_.empty();
			theNNeighbors_.empty();
			theWNeighbors_.empty();
		}

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

	};
}

#endif // !_Geo2d_BalPrTreeLeafHub_Header
