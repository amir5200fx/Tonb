#pragma once
#ifndef _Geo3d_ApprxSpaceNode_Internal_Header
#define _Geo3d_ApprxSpaceNode_Internal_Header

#include <Geo3d_ApprxSpaceNode.hxx>

namespace tnbLib
{

	class Geo3d_ApprxSpaceNode_Internal
		: public Geo3d_ApprxSpaceNode
	{

		/*Private Data*/

		Geo3d_ApprxSpaceNode* theFwdSw_;
		Geo3d_ApprxSpaceNode* theFwdSe_;
		Geo3d_ApprxSpaceNode* theFwdNe_;
		Geo3d_ApprxSpaceNode* theFwdNw_;

		Geo3d_ApprxSpaceNode* theBwdSw_;
		Geo3d_ApprxSpaceNode* theBwdSe_;
		Geo3d_ApprxSpaceNode* theBwdNe_;
		Geo3d_ApprxSpaceNode* theBwdNw_;

	public:

		// default constructor [6/24/2022 Amir]


		// constructors [6/24/2022 Amir]

		explicit Geo3d_ApprxSpaceNode_Internal(const Standard_Integer theLev)
			: Geo3d_ApprxSpaceNode(theLev)
			, theFwdNe_(0)
			, theFwdNw_(0)
			, theFwdSe_(0)
			, theFwdSw_(0)
			, theBwdNe_(0)
			, theBwdNw_(0)
			, theBwdSe_(0)
			, theBwdSw_(0)
		{}


		// public functions and operators [6/24/2022 Amir]

		auto FwdSw() const
		{
			return theFwdSw_;
		}

		auto& FwdSwRef()
		{
			return theFwdSw_;
		}

		auto FwdSe() const
		{
			return theFwdSe_;
		}

		auto& FwdSeRef()
		{
			return theFwdSe_;
		}

		auto FwdNe() const
		{
			return theFwdNe_;
		}

		auto& FwdNeRef()
		{
			return theFwdNe_;
		}

		auto FwdNw() const
		{
			return theFwdNw_;
		}

		auto& FwdNwRef()
		{
			return theFwdNw_;
		}

		auto BwdSw() const
		{
			return theBwdSw_;
		}

		auto& BwdSwRef()
		{
			return theBwdSw_;
		}

		auto BwdSe() const
		{
			return theBwdSe_;
		}

		auto& BwdSeRef()
		{
			return theBwdSe_;
		}

		auto BwdNe() const
		{
			return theBwdNe_;
		}

		auto& BwdNeRef()
		{
			return theBwdNe_;
		}

		auto BwdNw() const
		{
			return theBwdNw_;
		}

		auto& BwdNwRef()
		{
			return theBwdNw_;
		}
	};
}

#endif // !_Geo3d_ApprxSpaceNode_Internal_Header
