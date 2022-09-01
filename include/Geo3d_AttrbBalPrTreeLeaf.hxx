#pragma once
#ifndef _Geo3d_AttrbBalPrTreeLeaf_Header
#define _Geo3d_AttrbBalPrTreeLeaf_Header

#include <Geo3d_BalPrTreeNode.hxx>
#include <Geo3d_BalPrTreeBucket.hxx>
#include <Geo3d_AttrbBalPrTreeLeafHub.hxx>
#include <Geo3d_AttrbBalPrTreeLeaf_Adaptor.hxx>

namespace tnbLib
{

	template<class T, class Attrb>
	class Geo3d_AttrbBalPrTreeLeaf
		: public Geo3d_BalPrTreeNode
		, public Geo3d_AttrbBalPrTreeLeafHub<T, Attrb>
		, public Geo3d_BalPrTreeBucket<T>
		, public Geo3d_AttrbBalPrTreeLeaf_Adaptor<Attrb>
	{

		/*Private Data*/

		Geo3d_BalPrTreeNode* theFather_;

	public:

		// default constructor [8/8/2022 Amir]

		Geo3d_AttrbBalPrTreeLeaf()
		{}

		// constructors [8/8/2022 Amir]

		explicit Geo3d_AttrbBalPrTreeLeaf(const std::shared_ptr<Entity3d_Box>& theBox)
			: theFather_(0)
			, Geo3d_BalPrTreeNode(theBox)
		{}

		Geo3d_AttrbBalPrTreeLeaf(std::shared_ptr<Entity3d_Box>&& theBox)
			: theFather_(0)
			, Geo3d_BalPrTreeNode(std::move(theBox))
		{}


		// public functions and operators [8/8/2022 Amir]

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

#endif // !_Geo3d_AttrbBalPrTreeLeaf_Header
