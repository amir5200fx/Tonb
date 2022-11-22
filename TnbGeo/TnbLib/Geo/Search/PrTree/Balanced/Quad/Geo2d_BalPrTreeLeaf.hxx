#pragma once
#ifndef _Geo2d_BalPrTreeLeaf_Header
#define _Geo2d_BalPrTreeLeaf_Header

#include <Geo2d_BalPrTreeNode.hxx>
#include <Geo2d_BalPrTreeBucket.hxx>
#include <Geo2d_BalPrTreeLeafHub.hxx>

namespace tnbLib
{

	template<class T>
	class Geo2d_BalPrTreeLeaf
		: public Geo2d_BalPrTreeNode
		, public Geo2d_BalPrTreeLeafHub<T>
		, public Geo2d_BalPrTreeBucket<T>
	{

		/*Private Data*/

		Geo2d_BalPrTreeNode* theFather_;

	public:

		// default constructor [11/9/2022 Amir]

		Geo2d_BalPrTreeLeaf()
		{}


		// constructors [11/9/2022 Amir]

		explicit Geo2d_BalPrTreeLeaf(const std::shared_ptr<Entity2d_Box>& theBox)
			: Geo2d_BalPrTreeNode(theBox)
			, theFather_(0)
		{}

		Geo2d_BalPrTreeLeaf(std::shared_ptr<Entity2d_Box>&& theBox)
			: Geo2d_BalPrTreeNode(std::move(theBox))
			, theFather_(0)
		{}


		// Public functions and operators [11/9/2022 Amir]

		/*~Geo2d_BalPrTreeLeaf() override
		{
			theFather_ = 0;
		}*/

		std::string Type() const override
		{
			return "leaf";
		}


		const auto& Father() const
		{
			return theFather_;
		}

		auto& FatherRef()
		{
			return theFather_;
		}

		void SetFather(Geo2d_BalPrTreeNode* theFather)
		{
			theFather_ = theFather;
		}
	};
}

#endif // !_Geo2d_BalPrTreeLeaf_Header
