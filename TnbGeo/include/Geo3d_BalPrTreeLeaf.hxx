#pragma once
#ifndef _Geo3d_BalPrTreeLeaf_Header
#define _Geo3d_BalPrTreeLeaf_Header

#include <Geo3d_BalPrTreeNode.hxx>
#include <Geo3d_BalPrTreeBucket.hxx>
#include <Geo3d_BalPrTreeLeafHub.hxx>

namespace tnbLib
{

	template<class T>
	class Geo3d_BalPrTreeLeaf
		: public Geo3d_BalPrTreeNode
		, public Geo3d_BalPrTreeLeafHub<T>
		, public Geo3d_BalPrTreeBucket<T>
	{

		/*Private Data*/

		Geo3d_BalPrTreeNode* theFather_;

	public:

		// default constructor [7/5/2022 Amir]

		Geo3d_BalPrTreeLeaf()
			: theFather_(0)
		{}


		// constructors [7/5/2022 Amir]

		explicit Geo3d_BalPrTreeLeaf(const std::shared_ptr<Entity3d_Box>& theBox)
			: theFather_(0)
			, Geo3d_BalPrTreeNode(theBox)
		{}

		Geo3d_BalPrTreeLeaf(std::shared_ptr<Entity3d_Box>&& theBox)
			: theFather_(0)
			, Geo3d_BalPrTreeNode(std::move(theBox))
		{}

		// public functions and operators [7/5/2022 Amir]

		const auto& Father() const
		{
			return theFather_;
		}

		auto& FatherRef()
		{
			return theFather_;
		}

		void SetFather(Geo3d_BalPrTreeNode* theFather)
		{
			theFather_ = theFather;
		}
	};
}

#endif // !_Geo3d_BalPrTreeLeaf_Header
