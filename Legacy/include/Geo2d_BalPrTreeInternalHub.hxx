#pragma once
#ifndef _Geo2d_BalPrTreeInternalHub_Header
#define _Geo2d_BalPrTreeInternalHub_Header

namespace tnbLib
{

	// Forward Declarations [11/9/2022 Amir]
	class Geo2d_BalPrTreeNode;

	class Geo2d_BalPrTreeInternalHub
	{

	public:

		typedef Geo2d_BalPrTreeNode node;

	private:

		/*Private Data*/

		node* theSwPtr_;
		node* theSePtr_;
		node* theNePtr_;
		node* theNwPtr_;

	public:

		// default constructor [11/9/2022 Amir]

		Geo2d_BalPrTreeInternalHub()
			: theSwPtr_(0)
			, theSePtr_(0)
			, theNwPtr_(0)
			, theNePtr_(0)
		{}


		// constructors [11/9/2022 Amir]


		~Geo2d_BalPrTreeInternalHub()
		{
			theSwPtr_ = 0;
			theSePtr_ = 0;
			theNwPtr_ = 0;
			theNePtr_ = 0;
		}

		auto Sw() const
		{
			return theSwPtr_;
		}

		auto& SwRef()
		{
			return theSwPtr_;
		}

		auto Se() const
		{
			return theSePtr_;
		}

		auto& SeRef()
		{
			return theSePtr_;
		}

		auto Ne() const
		{
			return theNePtr_;
		}

		auto& NeRef()
		{
			return theNePtr_;
		}

		auto Nw() const
		{
			return theNwPtr_;
		}

		auto& NwRef()
		{
			return theNwPtr_;
		}
	};
}

#endif // !_Geo2d_BalPrTreeInternalHub_Header
