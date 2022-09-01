#pragma once
#ifndef _Geo3d_AttrbBalPrTreeLeafHub_Header
#define _Geo3d_AttrbBalPrTreeLeafHub_Header

#include <set>
#include <memory>

namespace tnbLib
{

	// Forward Declarations [8/8/2022 Amir]
	template<class T, class Attrb> class Geo3d_AttrbBalPrTreeLeaf;

	template<class T, class Attrb>
	class Geo3d_AttrbBalPrTreeLeafHub
	{

	public:

		typedef std::set<Geo3d_AttrbBalPrTreeLeaf<T, Attrb>*> leafSet;

	private:

		/*Private Data*/

		leafSet theSNeighbors_;
		leafSet theENeighbors_;
		leafSet theNNeighbors_;
		leafSet theWNeighbors_;
		leafSet theFNeighbors_;
		leafSet theBNeighbors_;

	public:


		// default constructor [8/8/2022 Amir]

		Geo3d_AttrbBalPrTreeLeafHub()
		{}


		// constructors [8/8/2022 Amir]


		// public functions and operators [8/8/2022 Amir]

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

#endif // !_Geo3d_AttrbBalPrTreeLeafHub_Header
