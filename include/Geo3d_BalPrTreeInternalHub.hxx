#pragma once
#ifndef _Geo3d_BalPrTreeInternalHub_Header
#define _Geo3d_BalPrTreeInternalHub_Header

namespace tnbLib
{

	// Forward Declarations [7/5/2022 Amir]
	class Geo3d_BalPrTreeNode;

	class Geo3d_BalPrTreeInternalHub
	{

	public:

		typedef Geo3d_BalPrTreeNode node;

	private:

		/*Private Data*/

		node* theFwdSwPtr_;
		node* theFwdSePtr_;
		node* theFwdNePtr_;
		node* theFwdNwPtr_;

		node* theBwdSwPtr_;
		node* theBwdSePtr_;
		node* theBwdNePtr_;
		node* theBwdNwPtr_;

	protected:

		// default constructor [7/5/2022 Amir]

		Geo3d_BalPrTreeInternalHub()
			: theFwdSwPtr_(0)
			, theFwdSePtr_(0)
			, theFwdNePtr_(0)
			, theFwdNwPtr_(0)
			, theBwdSwPtr_(0)
			, theBwdSePtr_(0)
			, theBwdNePtr_(0)
			, theBwdNwPtr_(0)
		{}


		// constructors [7/5/2022 Amir]

	public:

		// public functions and operators [7/5/2022 Amir]

		auto FwdSw() const
		{
			return theFwdSwPtr_;
		}

		auto& FwdSwRef()
		{
			return theFwdSwPtr_;
		}

		auto FwdSe() const
		{
			return theFwdSePtr_;
		}

		auto& FwdSeRef()
		{
			return theFwdSePtr_;
		}

		auto FwdNe() const
		{
			return theFwdNePtr_;
		}

		auto& FwdNeRef()
		{
			return theFwdNePtr_;
		}

		auto FwdNw() const
		{
			return theFwdNwPtr_;
		}

		auto& FwdNwRef()
		{
			return theFwdNwPtr_;
		}

		auto BwdSw() const
		{
			return theBwdSwPtr_;
		}

		auto& BwdSwRef()
		{
			return theBwdSwPtr_;
		}

		auto BwdSe() const
		{
			return theBwdSePtr_;
		}

		auto& BwdSeRef()
		{
			return theBwdSePtr_;
		}

		auto BwdNe() const
		{
			return theBwdNePtr_;
		}

		auto& BwdNeRef()
		{
			return theBwdNePtr_;
		}

		auto BwdNw() const
		{
			return theBwdNwPtr_;
		}

		auto& BwdNwRef()
		{
			return theBwdNwPtr_;
		}
	};
}

#endif // !_Geo3d_BalPrTreeInternalHub_Header
