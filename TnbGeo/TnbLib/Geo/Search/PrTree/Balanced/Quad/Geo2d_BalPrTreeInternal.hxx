#pragma once
#ifndef _Geo2d_BalPrTreeInternal_Header
#define _Geo2d_BalPrTreeInternal_Header

#include <Geo2d_BalPrTreeNode.hxx>
#include <Geo2d_BalPrTreeInternalHub.hxx>

namespace tnbLib
{

	class Geo2d_BalPrTreeInternal
		: public Geo2d_BalPrTreeNode
		, public Geo2d_BalPrTreeInternalHub
	{

		/*Private Data*/

	public:

		// default constructor [11/9/2022 Amir]

		Geo2d_BalPrTreeInternal()
		{}


		// constructors [11/9/2022 Amir]

		explicit Geo2d_BalPrTreeInternal(const std::shared_ptr<Entity2d_Box>& theBox)
			: Geo2d_BalPrTreeNode(theBox)
		{}

		Geo2d_BalPrTreeInternal(std::shared_ptr<Entity2d_Box>&& theBox)
			: Geo2d_BalPrTreeNode(std::move(theBox))
		{}


		// public functions and operators [11/9/2022 Amir]

		std::string Type() const override
		{
			return "internal";
		}

		/*~Geo2d_BalPrTreeInternal() override
		{}*/
	};
}

#endif // !_Geo2d_BalPrTreeInternal_Header
