#pragma once
#ifndef _Geo2d_BalPrTreeNode_Header
#define _Geo2d_BalPrTreeNode_Header

#include <Entity2d_BoxFwd.hxx>

#include <string>
#include <memory>

namespace tnbLib
{

	class Geo2d_BalPrTreeNode
	{

		/*Private Data*/

		std::shared_ptr<Entity2d_Box> theBox_;

	protected:

		// default constructor [11/9/2022 Amir]

		Geo2d_BalPrTreeNode()
		{}

		// constructors [11/9/2022 Amir]

		explicit Geo2d_BalPrTreeNode(const std::shared_ptr<Entity2d_Box>& theBox)
			: theBox_(theBox)
		{}

		Geo2d_BalPrTreeNode(std::shared_ptr<Entity2d_Box>&& theBox)
			: theBox_(std::move(theBox))
		{}

	public:

		// public functions and operators [11/9/2022 Amir]

		virtual ~Geo2d_BalPrTreeNode()
		{}

		virtual std::string Type() const = 0;

		const auto& Box() const
		{
			return theBox_;
		}

		void SetBox(const std::shared_ptr<Entity2d_Box>& theBox)
		{
			theBox_ = theBox;
		}

		void SetBox(std::shared_ptr<Entity2d_Box>&& theBox)
		{
			theBox_ = std::move(theBox);
		}
	};
}

#endif // !_Geo2d_BalPrTreeNode_Header
