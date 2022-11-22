#pragma once
#ifndef _Geo3d_BalPrTreeInternal_Header
#define _Geo3d_BalPrTreeInternal_Header

#include <Geo3d_BalPrTreeNode.hxx>
#include <Geo3d_BalPrTreeInternalHub.hxx>

namespace tnbLib
{

	class Geo3d_BalPrTreeInternal
		: public Geo3d_BalPrTreeNode
		, public Geo3d_BalPrTreeInternalHub
	{

		/*Private Data*/

	public:

		// default constructor [7/5/2022 Amir]

		Geo3d_BalPrTreeInternal()
		{}


		// constructors [7/5/2022 Amir]

		explicit Geo3d_BalPrTreeInternal(const std::shared_ptr<Entity3d_Box>& theBox)
			: Geo3d_BalPrTreeNode(theBox)
		{}

		Geo3d_BalPrTreeInternal(std::shared_ptr<Entity3d_Box>&& theBox)
			: Geo3d_BalPrTreeNode(std::move(theBox))
		{}

		// public functions and operators [7/5/2022 Amir]


		/*~Geo3d_BalPrTreeInternal() override
		{}*/

		std::string Type() const override
		{
			return "internal";
		}

	};
}

#endif // !_Geo3d_BalPrTreeInternal_Header
